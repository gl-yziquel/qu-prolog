// qem.cc - Main function for the QuAM emulator.
//
// ##Copyright##
// 
// Copyright (C) 2000, 20001
// Software Verification Research Centre
// The University of Queensland
// Australia 4072
// 
// email: svrc@it.uq.edu.au
// 
// The Qu-Prolog 6.0 System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000,2001 by The University of Queensland, 
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
// 	written consent from the SVRC; and
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
// For information on commercial use of this software contact the SVRC.
// 
// ##Copyright##
//
// $Id: qem.cc,v 1.9 2002/07/09 02:00:51 qp Exp $

#include <typeinfo>

#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

#include <sys/types.h>
#include <string.h>

#include <stdio.h>

#include "config.h"

#include "atom_table.h"
#include "code.h"
#include "cond_list.h"
#include "defs.h"
#include "executable.h"
#include "icm_aux.h"
#include "icm_environment.h"
#include "icm_message_handler.h"
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
#include "unix_thread.h"

const char *Program = "qem";

AtomTable *atoms = NULL;
Object **lib_path = NULL;
Code *code = NULL;
ICMEnvironment *icm_environment = NULL;
IOManager *iom = NULL;
SocketManager *sockm = NULL;
CondList<ICMMessage *> *incoming_icm_message_queue = NULL;
PredTab *predicates = NULL;
QemOptions *qem_options = NULL;
RecordDB *record_db = NULL;
Scheduler *scheduler = NULL;
SchedulerStatus *scheduler_status = NULL;
Signals *signals = NULL;
ThreadTable *thread_table = NULL;
ThreadOptions *thread_options = NULL;
char *process_symbol = NULL;
char *icm_address = NULL;
int icm_port = 0;

pthread_t *interrupt_handler_thread = NULL;

// Most of the data structures are dynamically allocated for 2 reasons:
// 1) The stack for the process might blow out;
// 2) In the future, we might consider ``detaching'' all the QuProlog threads.
int
main(int32 argc, char** argv)
{
  // Block all signals, except the one used for time slicing.
  sigset_t sigs;

  sigemptyset(&sigs);
  sigaddset(&sigs, SIGINT);

  SYSTEM_CALL_NON_ZERO(pthread_sigmask(SIG_SETMASK, &sigs, NULL));

  // Signal communication structure
  signals = new Signals;
  if (signals == NULL)
    {
      OutOfMemory(Program);
    }


  // Spin off signal processing thread
  pthread_t int_hand = thread_create(interrupt_handler, signals);
  interrupt_handler_thread = &int_hand;


  // Parse the options.
  qem_options = new QemOptions(argc, argv);
  if (qem_options == NULL)
    {
      OutOfMemory(Program);
    }

  if (! qem_options->Valid())
    {
      Usage(Program, qem_options->Usage());
    }

  thread_options = new ThreadOptions(*qem_options);
  if (thread_options == NULL)
    {
      OutOfMemory(Program);
    }
 
  // Allocate areas in the Qu-Prolog Abstract Machine.
  atoms = new AtomTable(qem_options->AtomTableSize(),
			qem_options->StringTableSize(),
			0);
  if (atoms == NULL)
    {
      OutOfMemory(Program);
    }

  predicates = new PredTab(atoms, qem_options->PredicateTableSize());
  if (predicates == NULL)
    {
      OutOfMemory(Program);
    }

  code = new Code(qem_options->CodeSize());
  if (code == NULL)
    {
      OutOfMemory(Program);
    }

  record_db = new RecordDB(qem_options->RecordDBSize(), 0); 
  if (record_db == NULL)
    {
      OutOfMemory(Program);
    }

  // Load executable file.
  LoadExecutable(qem_options->QxFile(), *code, *atoms, *predicates);

  // Library path.
  lib_path = new Object*;
  if (lib_path == NULL)
    {
      OutOfMemory(Program);
    }

  const char *lp = getenv("QPLIBPATH");
  if (lp == NULL)
    {
      Fatal(Program, "QPLIBPATH is undefined.");
    }
  *lib_path = atoms->add(lp);

  // I/O management.

  // Set standard in to be non-blocking.
  setbuf(stdin, NULL);
//  fflush(stdout);
  setvbuf(stdout, NULL, _IOLBF, 0);
//  fflush(stderr);
  setvbuf(stderr, NULL, _IONBF, 0);

  Stream *current_input_stream = new Stream((istream *)&cin, qp_fileno(cin));
  Stream *current_output_stream = new Stream((ostream *)&cout, qp_fileno(cout));
  Stream *current_error_stream = new Stream((ostream *)&cerr, qp_fileno(cerr));
  if (current_input_stream == NULL ||
      current_output_stream == NULL ||
      current_error_stream == NULL)
    {
      OutOfMemory(Program);
    }

  iom = new IOManager(current_input_stream,
		      current_output_stream,
		      current_error_stream);
  if (iom == NULL)
    {
      OutOfMemory(Program);
    }

  sockm = new SocketManager();

  if (sockm == NULL)
    {
      OutOfMemory(Program);
    }


  scheduler_status = new SchedulerStatus;
  if (scheduler_status == NULL)
    {
      OutOfMemory(Program);
    }

  // Build the scheduler.
  scheduler = new Scheduler;
  if (scheduler == NULL)
    {
      OutOfMemory(Program);
    }

  // Thread table.
  thread_table = new ThreadTable(qem_options->ThreadTableSize());
  if (thread_table == NULL)
    {
      OutOfMemory(Program);
    }

  // This has to be created regardless of the ICM status - the 
  // scheduler looks for messages there anyway.
  // TO DO: Fix this situation.
  incoming_icm_message_queue = new CondList<ICMMessage *>;
  if (incoming_icm_message_queue == NULL)
    {
      OutOfMemory(Program);
    }

#ifdef ICM_DEF
  icmConn icm_conn;
  pthread_t icm_incoming_message_handler_thread = 0;

  process_symbol = qem_options->ProcessSymbol();
  icm_address = qem_options->ICMServer();
  icm_port = qem_options->ICMPort();

  if (process_symbol != NULL)
    {
#ifdef DEBUG_ICM
      cerr.form("%s Before starting ICM\n", __FUNCTION__);
#endif

      // Start up communications
      const icmStatus icm_status = icmInitComms(qem_options->ICMPort(),
						qem_options->ICMServer(),
						&icm_conn);
      if (icm_status == icmFailed)
	{
	  Fatal(Program, "Couldn't contact ICM communications server");
	}
      else if (icm_status == icmError)
	{
	  Fatal(Program, "ICM communications refused connection");
	}
      
      icm_environment = new ICMEnvironment(icm_conn, *incoming_icm_message_queue);
      if (icm_environment == NULL)
	{
	  OutOfMemory(Program);
	}
      
      icm_environment->Register(process_symbol);

      // Start the handling of ICM messages.
      icm_incoming_message_handler_thread = 
	thread_create(incoming_icm_message_handler, icm_environment);

#ifdef DEBUG_ICM
      cerr.form("%s After starting ICM\n", __FUNCTION__);
#endif
    }
#endif // ICM_DEF
    
#ifdef DEBUG_SCHED
  cerr.form("%s Before scheduler->Scheduler()\n", Program);
#endif

  // Run threads.
  scheduler->Schedule(*incoming_icm_message_queue,
		      *predicates, *signals, *thread_options, *thread_table);

#ifdef DEBUG_SCHED
  cerr.form("%s After scheduler->Scheduler()\n", Program);
#endif
  
  thread_cancel(*interrupt_handler_thread);
  
#ifdef ICM_DEF
  if (process_symbol != NULL)
    {
#ifdef DEBUG_ICM
      cerr.form("%s Before shutting down ICM\n", Program);
#endif
      
      icm_environment->Unregister();
      pthread_join(icm_incoming_message_handler_thread, NULL);
      icmCloseComms(icm_conn);
      
#ifdef DEBUG_ICM
      cerr.form("%s After shutting down ICM\n", Program);
#endif
    }
#endif // ICM_DEF

  exit(EXIT_SUCCESS);
}



