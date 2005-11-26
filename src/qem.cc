// qem.cc - Main function for the QuAM emulator.
//
// ##Copyright##
// 
// Copyright (C) 2000-2004
// School of Information Technology and Electrical Engineering
// The University of Queensland
// Australia 4072
// 
// email: pjr@itee.uq.edu.au
// 
// The Qu-Prolog System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000-2004 by The University of Queensland, 
// Queensland 4072 Australia
// 
// Permission to use, copy and distribute this software and associated
// documentation for any non-commercial purpose and without fee is hereby 
// granted, subject to the following conditions:
// 
// 1. 	that the above copyright notice and this permission notice and 
// 	warranty disclaimer appear in all copies and in supporting 
// 	documentation; 
// 
// 2.	that the name of the University of Queensland not be used in 
// 	advertising or publicity pertaining to distribution of the software 
// 	without specific, written prior permission; 
// 
// 3.	that users of this software should be responsible for determining the 
// 	fitness of the software for the purposes for which the software is 
// 	employed by them; 
// 
// 4. 	that no changes to the system or documentation are subsequently 
// 	made available to third parties or redistributed without prior 
// 	written consent from the ITEE; and
// 
// The University of Queensland disclaims all warranties with regard to this
// software, including all implied warranties of merchantability and fitness
// to the extent permitted by law. In no event shall the University of 
// Queensland be liable for any special, indirect or consequential damages or 
// any damages whatsoever resulting from loss of use, data or profits, whether 
// in an action of contract, negligence or other tortious action, arising out 
// of or in connection with the use or performance of this software.
// 
// THE UNIVERSITY OF QUEENSLAND MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR
// SUITABILITY OF THIS MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS",
// WITHOUT ANY EXPRESSED OR IMPLIED WARRANTIES.
// 
// 
// For information on commercial use of this software contact ITEE.
// 
// ##Copyright##
//
// $Id: qem.cc,v 1.30 2005/11/26 23:34:30 qp Exp $

#include <typeinfo>

#include <stdlib.h>
#ifdef WIN32
        #include <io.h>
        #include <fcntl.h>
        #include <signal.h>
        #define _WINSOCKAPI_
        #include <windows.h>
#else
        #include <unistd.h>
        #include <sys/utsname.h>
#endif

#include <fcntl.h>

#include <sys/types.h>
#include <string.h>

#include <stdio.h>

#include "config.h"

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "elvin_env.h"
#include "executable.h"
#ifdef ICM_DEF
#include "icm_aux.h"
#include "icm_environment.h"
#endif
#include "interrupt_handler.h"
#include "io_qp.h"
#include "pred_table.h"
#include "protos.h"
#include "qem.h"
#include "qem_options.h"
#include "signals.h"
#include "record_ref_table.h"
#include "scheduler_status.h"
#include "scheduler.h"
#include "thread_qp.h"
#include "thread_options.h"
#include "thread_table.h"

const char *Program = "qem";

//
// Handler for out of memory via new
//
//typedef void (*new_handler) ();
//new_handler set_new_handler(new_handler p) throw();

void noMoreMemory()
{
   cerr << "No more memory available for " << Program << endl;
   abort();
}

AtomTable *atoms = NULL;
Object **lib_path = NULL;
Code *code = NULL;
IOManager *iom = NULL;
SocketManager *sockm = NULL;
PredTab *predicates = NULL;
QemOptions *qem_options = NULL;
RecordDB *record_db = NULL;
Scheduler *scheduler = NULL;
SchedulerStatus *scheduler_status = NULL;
Signals *signals = NULL;
ThreadTable *thread_table = NULL;
ThreadOptions *thread_options = NULL;
char *process_symbol = NULL;
#ifdef ICM_DEF
char *icm_address = NULL;
#endif
int icm_port = 0;

ICMMessageChannel* icm_channel = NULL;
ICMEnvironment* icm_environment = NULL;

#ifdef ELVIN_DEF
ElvinMessageChannel* elvin_channel = NULL;
#endif // ELVIN_DEF

// In order that signals to unblock selects we create a pipe and write to
// it when a signal arrives. By putting the read end of the pipe in
// the file descriptor set of the select, the select will unblock
// when a signal arrives. 
int *sigint_pipe;

// SIGINT signal handler
static void
handle_sigint(int)
{
  extern Signals *signals;
  extern int *sigint_pipe;
  if (signals != NULL)
    {
      char buff[128];
      buff[0] = 'a';
      write(sigint_pipe[1], buff, 1);
      signals->Increment(SIGINT);
      signals->Status().setSignals();
    } else {
      cerr << "Signals are null" << endl;
    }
#ifdef WIN32
//Otherwise we can only use the handler once - yet another undoc'd windows oddity
     (void)signal(SIGINT, handle_sigint);
#endif

}


// Most of the data structures are dynamically allocated for 2 reasons:
// 1) The stack for the process might blow out;
// 2) In the future, we might consider ``detaching'' all the QuProlog threads.
int
main(int32 argc, char** argv)
{
  // set the out-of-memory handler
  std::set_new_handler(noMoreMemory);

  //http://www.codersource.net/win32_createnamedpipe.html
  //http://www-106.ibm.com/developerworks/linux/library/l-rt4/?open&t=grl,l=252,p=pipes
  //Pipes in windows are 1000x more complex and painful than this.
  sigint_pipe = new int[2];
#ifdef WIN32
  _pipe(sigint_pipe, 256, _O_BINARY);
//  SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
#else
  pipe(sigint_pipe);
  fcntl(sigint_pipe[0], F_SETFL, O_NONBLOCK);
#endif

  // Signal communication structure
  signals = new Signals;

#ifdef WIN32
(void) signal(SIGINT, handle_sigint);
#else
  // SIGINT signal handler
  //  
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGINT);

  struct sigaction sa;
  sa.sa_handler = handle_sigint;
  sa.sa_mask = sigs;
  sa.sa_flags = SA_RESTART;
#if !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))
  sa.sa_restorer = NULL;
#endif // !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))
  SYSTEM_CALL_LESS_ZERO(sigaction(SIGINT, &sa, NULL));
  //
  // End of SIGINT signal handler
#endif

  // Parse the options.
  qem_options = new QemOptions(argc, argv);

  if (! qem_options->Valid())
    {
      Usage(Program, qem_options->Usage());
    }

  thread_options = new ThreadOptions(*qem_options);
 
  // Allocate areas in the Qu-Prolog Abstract Machine.
  atoms = new AtomTable(qem_options->AtomTableSize(),
			qem_options->StringTableSize(),
			0);
  predicates = new PredTab(atoms, qem_options->PredicateTableSize());

  code = new Code(qem_options->CodeSize());

  record_db = new RecordDB(qem_options->RecordDBSize(), 0); 

  // Load executable file.
  LoadExecutable(qem_options->QxFile(), *code, *atoms, *predicates);

  // Library path.
  lib_path = new Object*;

  const char *lp = getenv("QPLIBPATH");
  if (lp == NULL)
    {
      Fatal(Program, " QPLIBPATH is undefined.");
    }
  *lib_path = atoms->add(lp);

  // I/O management.

  // Set standard in to be non-blocking.
#ifdef WIN32
  setvbuf(stdin, NULL, _IONBF, 0);
#else
  setbuf(stdin, NULL);
#endif
//  fflush(stdout);
  setvbuf(stdout, NULL, _IOLBF, 0);
//  fflush(stderr);
  setvbuf(stderr, NULL, _IONBF, 0);

#ifdef WIN32
  QPifdstream *current_input_stream = new QPifdstream(_fileno(stdin));
#else
  QPifdstream *current_input_stream = new QPifdstream(fileno(stdin));
#endif
  QPostream *current_output_stream = new QPostream(&cout);
  QPostream *current_error_stream = new QPostream(&cerr);

  iom = new IOManager(current_input_stream,
		      current_output_stream,
		      current_error_stream);

  sockm = new SocketManager();

  scheduler_status = new SchedulerStatus;

  // Thread table.
  thread_table = new ThreadTable(qem_options->ThreadTableSize());

  // Build the scheduler.
  scheduler 
    = new Scheduler(*thread_options, *thread_table, *signals, *predicates);

#ifdef ICM_DEF
  initICMIo();
  icmConn icm_conn;

  process_symbol = qem_options->ProcessSymbol();
  icm_address = qem_options->ICMServer();
  icm_port = qem_options->ICMPort();

  if (process_symbol != NULL)
    {
#ifdef DEBUG_ICM
      cerr << "Before starting ICM" << endl;
#endif

      // Start up communications
      const icmStatus icm_status = icmInitComms(qem_options->ICMPort(),
						qem_options->ICMServer(),
						&icm_conn);
      if (icm_status == icmFailed)
	{
	  Fatal(Program, " Couldn't contact ICM communications server");
	}
      else if (icm_status == icmError)
	{
	  Fatal(Program, " ICM communications refused connection");
	}
      
      // Set up icm and register
      icm_environment = new ICMEnvironment(icm_conn);
      
      if (!icm_environment->Register(process_symbol))
	{
	  Fatal(Program, " Cannot register process with ICM");
	}


      // Create a channel for ICM messages
      icm_channel = 
	new ICMMessageChannel(*icm_environment, *thread_table, *iom, *signals);

      // Add ICM channel to scheduler channels
      scheduler->getChannels().push_back(icm_channel);
      assert(process_symbol != NULL);
    }
#endif // ICM_DEF
    
#ifdef DEBUG_SCHED
  printf("%s Before scheduler->Scheduler()\n", Program);
#endif

  // Run threads.
  scheduler->Schedule();

#ifdef DEBUG_SCHED
  printf("%s After scheduler->Scheduler()\n", Program);
#endif
  
#ifdef ICM_DEF
  if (process_symbol != NULL)
    {
#ifdef DEBUG_ICM
      printf("%s Before shutting down ICM\n", Program);
#endif
      
      icm_environment->Unregister();
      
#ifdef DEBUG_ICM
      printf("%s After shutting down ICM\n", Program);
#endif
    }
#endif // ICM_DEF

  exit(EXIT_SUCCESS);
}



