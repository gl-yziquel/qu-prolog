// system.cc - Functions which use system to call CShell commands and 
//             syscall to call system commands.
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
// $Id: system.cc,v 1.15 2004/03/19 04:54:19 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
#include "system_support.h"

#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#if defined(FREEBSD) || defined(MACOSX)
#include        <pthread.h>
#include        <signal.h>
#include <sys/wait.h>
#endif //defined(FREEBSD) || defined(MACOSX)

extern AtomTable *atoms;

extern	"C"	int mkstemp(char *);

#if defined(FREEBSD) || defined(MACOSX)
extern char **environ;
int bsd_system (char *command) {
  int pid, status;
  
  if (command == 0)
    return 1;
  pid = fork();
  if (pid == -1)
    return -1;
  if (pid == 0) {
    signal(SIGVTALRM, SIG_IGN);
    char *argv[4];
    argv[0] = "sh";
    argv[1] = "-c";
    argv[2] = command;
    argv[3] = 0;
    execve("/bin/sh", argv, environ);
    exit(127);
  }
  do {
    if (waitpid(pid, &status, 0) == -1) {
      if (errno != EINTR)
	return -1;
    } else
      return status;
  } while(1);
}

#endif //defined(FREEBSD) || defined(MACOSX)

//
// psi_system(constant, var).
// X0 is a string for CShell commands. X1 is unified with the return
// value from the call to the function system.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_system(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);

  DEBUG_ASSERT(val1->isAtom());

#if defined(FREEBSD) || defined(MACOSX)
  object2 = 
    heap.newNumber(bsd_system(atoms->getAtomString(val1)));
#else
  object2 = 
    heap.newNumber(system(atoms->getAtomString(val1)));
#endif //defined(FREEBSD) || defined(MACOSX)

  return (RV_SUCCESS);
}

//
// psi_access(atom, integer, var)
// Check the file in X0 whether has the mode in X1.  Return the result in X2.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_access(Object *& object1, Object *& object2, Object *& object3)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  DEBUG_ASSERT(val1->isAtom());
  DEBUG_ASSERT(val2->isShort());
  
  object3 = 
    heap.newNumber(access(wordexp(atoms->getAtomString(val1)).c_str(),
			   val2->getNumber()));
  return(RV_SUCCESS);
} 

//
// psi_chdir(atom)
// Change directory to dir given by the argument
// mode(in)
//
Thread::ReturnValue	
Thread::psi_chdir(Object *& object1)
{
  Object* val1 = heap.dereference(object1);
  if (!val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  return (BOOL_TO_RV(chdir(wordexp(atoms->getAtomString(val1)).c_str()) == 0));
}

//
// psi_mktemp(atom, var)
// Return a temporary file name.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_mktemp(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);

  DEBUG_ASSERT(val1->isAtom());
  
  strcpy(atom_buf1, atoms->getAtomString(val1));
  (void)(mkstemp(atom_buf1));
  object2 = atoms->add(atom_buf1);
  
  return(RV_SUCCESS);
}

//
// psi_realtime(-Integer)
//
// Returns system time.
//
Thread::ReturnValue
Thread::psi_realtime(Object *& time_arg)
{
  time_arg = heap.newNumber(time((time_t *) NULL));
  return RV_SUCCESS;
}

//
// psi_gmtime(?Integer, ?timestruct)
//
// psi_gmtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form 
// gmt_time(Year, Mth, Day, Hours, Mins, Secs)
Thread::ReturnValue
Thread::psi_gmtime(Object *& time_obj, Object *& time_struct)
{
  Object* time_arg = heap.dereference(time_obj);
  Object* time_struct_arg = heap.dereference(time_struct);
  if (time_arg->isNumber())
    {
      time_t etime = (time_t)time_arg->getNumber();
      struct tm *tmtime = gmtime(&etime);
      Structure* t_struct = heap.newStructure(6);
      t_struct->setFunctor(atoms->add("gmt_time"));
      t_struct->setArgument(1, heap.newNumber(tmtime->tm_year));
      t_struct->setArgument(2, heap.newNumber(tmtime->tm_mon));
      t_struct->setArgument(3, heap.newNumber(tmtime->tm_mday));
      t_struct->setArgument(4, heap.newNumber(tmtime->tm_hour));
      t_struct->setArgument(5, heap.newNumber(tmtime->tm_min));
      t_struct->setArgument(6, heap.newNumber(tmtime->tm_sec));

      return BOOL_TO_RV(unify(t_struct, time_struct_arg));
    }
  else
    {
      if (!time_arg->isVariable())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      if (!time_struct_arg->isStructure())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      Structure* t_struct = OBJECT_CAST(Structure*, time_struct_arg);
      if ((t_struct->getArity() != 6) || 
	  (t_struct->getFunctor()->variableDereference() 
	   != atoms->add("gmt_time")))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      struct tm tmtime;
      Object* arg1 = t_struct->getArgument(1)->variableDereference();
      if (!arg1->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_year = arg1->getNumber();
      Object* arg2 = t_struct->getArgument(2)->variableDereference();
      if (!arg2->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mon = arg2->getNumber();
      Object* arg3 = t_struct->getArgument(3)->variableDereference();
      if (!arg3->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mday = arg3->getNumber();
      Object* arg4 = t_struct->getArgument(4)->variableDereference();
      if (!arg4->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_hour = arg4->getNumber();
      Object* arg5 = t_struct->getArgument(5)->variableDereference();
      if (!arg5->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_min = arg5->getNumber();
      Object* arg6 = t_struct->getArgument(6)->variableDereference();
      if (!arg6->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_sec = arg6->getNumber();

      tmtime.tm_isdst = 0;

      // Remember the current value for the TZ environment variable
      char* oldTZ = getenv("TZ");
      // Set TZ to UTC time
      (void)putenv("TZ=UTC");
      // In UTC time localtime and gmtime are the same and so mktime gives
      // the inverse of gmtime
      time_t etime = mktime(&tmtime);
      // Reset the TZ variable
      char envstring[1000];
      sprintf(envstring, "TZ=%s", oldTZ);
      (void)putenv(envstring);
      if (etime == (time_t)(-1))
        {
          PSI_ERROR_RETURN(EV_TYPE, 2);
        }
      Object* timet = heap.newNumber(etime);

      return BOOL_TO_RV(unify(time_arg, timet));
    }
}

//
// psi_localtime(?Integer, ?timestruct)
//
// psi_localtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form 
// local_time(Year, Mth, Day, Hours, Mins, Secs, isdst)
Thread::ReturnValue
Thread::psi_localtime(Object *& time_obj, Object *& time_struct)
{
  Object* time_arg = heap.dereference(time_obj);
  Object* time_struct_arg = heap.dereference(time_struct);
  if (time_struct_arg->isVariable())
    {
      if (time_arg->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 1);
	}
      if (!time_arg->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      time_t etime = (time_t)time_arg->getNumber();
      struct tm *tmtime = localtime(&etime);
      Structure* t_struct = heap.newStructure(7);
      t_struct->setFunctor(atoms->add("local_time"));
      t_struct->setArgument(1, heap.newNumber(tmtime->tm_year));
      t_struct->setArgument(2, heap.newNumber(tmtime->tm_mon));
      t_struct->setArgument(3, heap.newNumber(tmtime->tm_mday));
      t_struct->setArgument(4, heap.newNumber(tmtime->tm_hour));
      t_struct->setArgument(5, heap.newNumber(tmtime->tm_min));
      t_struct->setArgument(6, heap.newNumber(tmtime->tm_sec));
      t_struct->setArgument(7, heap.newNumber(tmtime->tm_isdst));

      return BOOL_TO_RV(unify(t_struct, time_struct_arg));
    }
  else
    {
      if (!time_arg->isVariable() && !time_arg->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      if (!time_struct_arg->isStructure())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      Structure* t_struct = OBJECT_CAST(Structure*, time_struct_arg);
      if ((t_struct->getArity() != 7) || 
	  (t_struct->getFunctor()->variableDereference() 
	   != atoms->add("local_time")))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      struct tm tmtime;
      Object* arg1 = t_struct->getArgument(1)->variableDereference();
      if (!arg1->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_year = arg1->getNumber();
      Object* arg2 = t_struct->getArgument(2)->variableDereference();
      if (!arg2->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mon = arg2->getNumber();
      Object* arg3 = t_struct->getArgument(3)->variableDereference();
      if (!arg3->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mday = arg3->getNumber();
      Object* arg4 = t_struct->getArgument(4)->variableDereference();
      if (!arg4->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_hour = arg4->getNumber();
      Object* arg5 = t_struct->getArgument(5)->variableDereference();
      if (!arg5->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_min = arg5->getNumber();
      Object* arg6 = t_struct->getArgument(6)->variableDereference();
      if (!arg6->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_sec = arg6->getNumber();
      Object* arg7 = t_struct->getArgument(7)->variableDereference();
      if (!arg7->isNumber())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_isdst = arg7->getNumber();
      
      time_t etime = mktime(&tmtime);
      if (etime == (time_t)(-1))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      Object* timet = heap.newNumber(etime);
      return BOOL_TO_RV(unify(time_arg, timet));
    }
}

// @user
// @pred signal_to_atom(SignalNumber, SignalAtom)
// @type signal_to_atom(integer, atom)
// @mode signal_to_atom(+, -) is det
// @description
// Takes a signal number and maps it to the appropriate signal string.
// @end pred
// @end user
Thread::ReturnValue
Thread::psi_signal_to_atom(Object *& signum, Object *& sigatom)
{
  Object* signum_arg = heap.dereference(signum);

  if (signum_arg->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!signum_arg->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  const int sig = signum_arg->getNumber();

  if (sig <= 0 || sig > NSIG)
    {
      PSI_ERROR_RETURN(EV_RANGE, 1);
    }

  char *str = NULL;

  switch (sig)
    {
      //    case SIGHUP: str = "SIGHUP"; break;
    case SIGINT: str = "SIGINT"; break;
#if 0
    case SIGQUIT: str = "SIGQUIT"; break;
    case SIGILL: str = "SIGILL"; break;
    case SIGTRAP: str = "SIGTRAP"; break;
    case SIGIOT: str = "SIGIOT"; break;
#if SIGABRT != SIGIOT
    case SIGABRT: str = "SIGABRT"; break;
#endif	// SIGABRT != SIGIOT
#ifdef SIGEMT
    case SIGEMT: str = "SIGEMT"; break;
#endif	// SIGEMT
    case SIGFPE: str = "SIGFPE"; break;
    case SIGKILL: str = "SIGKILL"; break;
    case SIGBUS: str = "SIGBUS"; break;
    case SIGSEGV: str = "SIGSEGV"; break;
#ifdef SIGSYS
    case SIGSYS: str = "SIGSYS"; break;
#endif	// SIGSYS
    case SIGPIPE: str = "SIGPIPE"; break;
    case SIGALRM: str = "SIGALRM"; break;
    case SIGTERM: str = "SIGTERM"; break;
    case SIGUSR1: str = "SIGUSR1"; break;
    case SIGUSR2: str = "SIGUSR2"; break;
	// SIGCLD
    case SIGCHLD: str = "SIGCHLD"; break;
#ifdef SIGPWR
    case SIGPWR: str = "SIGPWR"; break;
#endif	// SIGPWR
    case SIGWINCH: str = "SIGWINCH"; break;
    case SIGURG: str = "SIGURG"; break;
#ifdef SIGPOLL
    case SIGPOLL: str = "SIGPOLL"; break;
#endif	// SIGPOLL
#if SIGIO != SIGPOLL
    case SIGIO: str = "SIGIO"; break;
#endif	// SIGIO != SIGPOLL
    case SIGSTOP: str = "SIGSTOP"; break;
    case SIGTSTP: str = "SIGTSTP"; break;
    case SIGCONT: str = "SIGCONT"; break;
    case SIGTTIN: str = "SIGTTIN"; break;
    case SIGTTOU: str = "SIGTTOU"; break;
    case SIGVTALRM: str = "SIGVTALRM"; break;
    case SIGPROF: str = "SIGPROF"; break;
    case SIGXCPU: str = "SIGXCPU"; break;
    case SIGXFSZ: str = "SIGXFSZ"; break;
#ifdef SIGWAITING
    case SIGWAITING: str = "SIGWAITING"; break;
#endif	// SIGWAITING
#ifdef SIGLWP
    case SIGLWP: str = "SIGLWP"; break;
#endif	// SIGLWP
#ifdef SIGFREEZE
    case SIGFREEZE: str = "SIGFREEZE"; break;
#endif	// SIGFREEZE
#ifdef SIGTHAW
    case SIGTHAW: str = "SIGTHAW"; break;
#endif	// SIGTHAW
#ifdef SIGSTKFLT
    case SIGSTKFLT: str = "SIGSTKFLT"; break;
#endif 	// SIGSTKFLT
#ifdef SIGUNUSED
    case SIGUNUSED: str = "SIGUNUSED"; break;
#endif	// SIGUNUSED
#ifdef SIGINFO
    case SIGINFO: str = "SIGINFO"; break;
#endif	// SIGINFO
#endif // 0
    default:
      return RV_FAIL;
      break;
    }

  sigatom = atoms->add(str);

  return RV_SUCCESS;
}

// @doc
// @pred nsig(NSIG)
// @type nsig(integer)
// @mode nsig(-) is det
// @description
// Returns the number of signals on this machine.
// @end pred
// @end user
Thread::ReturnValue
Thread::psi_nsig(Object *& nsig)
{
  nsig = heap.newNumber(NSIG);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_strerror(Object *& errno_arg, Object *& string_arg)
{
  Object* errno_arg_value = heap.dereference(errno_arg);
  if (errno_arg_value->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!errno_arg_value->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  const char *str = strerror(errno_arg_value->getNumber());
  if (str == NULL)
    {
      PSI_ERROR_RETURN(EV_VALUE, 1);
    }

  string_arg = atoms->add(str);

  return RV_SUCCESS;
}










