// scheduler.cc - Schedule execution of threads.
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
// $Id: scheduler.cc,v 1.30 2003/10/03 01:19:40 qp Exp $

#include <algorithm>

#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>

#include "global.h"
#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "errors.h"
#include "icm_handle.h"
#include "icm_message.h"
#include "io_qp.h"
#include "manager.h"
#include "pred_table.h"
#include "protos.h"
#include "scheduler.h"
#include "thread_qp.h"
#include "thread_condition.h"
#include "thread_table.h"

//
// Determine the length of the scheduler quantum.
//

#ifdef DEBUG_SCHED
static const int32 TIME_SLICE_SECS = 1L;
static const int32 TIME_SLICE_USECS = 0L;
#else
static const int32 TIME_SLICE_SECS = 0L;
static const int32 TIME_SLICE_USECS = 100000L;
#endif

//
// Maximum length to sleep when all threads are blocked.
//
#if defined(DEBUG_SCHED) || defined(DEBUG_IO)
static const int32 SLEEP_USECS = 1000000L;
#else
static const int32 SLEEP_USECS = TIME_SLICE_USECS;
#endif

static void handle_timeslice(int);

Scheduler::Scheduler(ThreadOptions& to, ThreadTable& tt, 
		     Signals& s, PredTab& p)
  : thread_options(to), thread_table(tt), signals(s), predicates(p)
{
  //
  // Allow time slicing.
  //
  scheduler_status.setEnableTimeslice();
  theTimeouts = 0;
}

Scheduler::~Scheduler(void) { }

extern int* sigint_pipe;

bool
Scheduler::poll_fds(int32 poll_timeout)
{
  fd_set rfds, wfds;
  FD_ZERO(&rfds);
  FD_ZERO(&wfds);
  //int max_fd = 0;
  int max_fd = sigint_pipe[0];
  FD_SET(sigint_pipe[0], &rfds);
  for(list<BlockingObject *>::iterator iter = blocked_queue.begin();
	   iter != blocked_queue.end();
	   iter++)
    {
      (*iter)->updateFDSETS(&rfds, &wfds, max_fd);
    }

  for (list <MessageChannel*>::iterator iter = message_channels.begin();
       iter != message_channels.end();
       iter++)
    {
      (*iter)->updateFDSETS(&rfds, &wfds, max_fd);
    }

  int result;
  if (poll_timeout == 0)
    {
      result = select(max_fd + 1, &rfds, &wfds, NULL, NULL) > 0;
    }
  else
    {
      timeval timeout = { poll_timeout, 0 };

      result = select(max_fd + 1, &rfds, &wfds, NULL, &timeout) > 0;
    }

  return result > 0;

}

Thread::ReturnValue
Scheduler::Sleep(bool doPoll)
{
#ifdef DEBUG_BLOCK
  cerr << __FUNCTION__ << " Sleeping" << endl;
#endif
  while (! InterQuantum())
    {
      // Were there any signals while we were napping?
      if (signals.Status().testSignals())
	{
#ifdef DEBUG_SCHED
	  cerr << __FUNCTION__ << " Start signal handler" << endl;
#endif
	  const Thread::ReturnValue result = HandleSignal();
#ifdef DEBUG_SCHED
	  cerr << __FUNCTION__ << " Stop signal handler" << endl;
#endif
	  return result;
	}
      int timeout;
      if (doPoll) timeout = 1;
      else if (theTimeouts > 0) timeout = theTimeouts;
      else timeout = 0;
      if (poll_fds(timeout))
	{
	  break;
	}
#ifdef DEBUG_SCHED
      cerr << "End poll" << endl;
#endif
    }
#ifdef DEBUG_BLOCK
  cerr << __FUNCTION__ << " Finished sleeping" << endl;
#endif
  return Thread::RV_SUCCESS;
}

//
// Perform all the inter quantum actions:
//	Process messages
// 	Check on threads blocked on IO
//	Check on threads blocked on ICM
//	Check on threads blocked on waits
//	Check on threads waiting on timeouts
//
bool
Scheduler::InterQuantum(void)
{
#ifdef DEBUG_SCHED
  cerr << "InterQuantum" << endl;
#endif
  // First shuffle any new messages
  (void)ShuffleAllMessages();

  // 
  // Was anything actually done?
  //
  theTimeouts = 0;
  return processBlockedThreads();
}


int32
Scheduler::Schedule(void)
{
  Thread *thread = new Thread(NULL, thread_options);

  thread->programCounter =
    predicates.getCode(predicates.lookUp(atoms->getAtom(atoms->lookUp("$start")), 0, atoms, code)).getPredicate(code);

  const ThreadTableLoc first = thread_table.AddID(thread);
  if (first == (ThreadTableLoc) -1)
    {
      Fatal(__FUNCTION__, "Couldn't add initial thread to thread table");
    }

  thread_table.IncLive();
  thread->TInfo().SetID(first);

  thread->Condition(ThreadCondition::RUNNABLE);

  const char *symbol = thread_table.MakeName(first).c_str();
  atoms->add(symbol);
  thread->TInfo().SetSymbol(symbol);

  run_queue.push_back(thread);

  //
  // Get the timeslicing signal happening.
  //
#ifdef SOLARIS
  timer_t timerid;
  struct sigevent se;
  se.sigev_notify = SIGEV_SIGNAL;
  se.sigev_signo = SIGTIMESLICE;
  se.sigev_value.sival_int = 0;
#endif // SOLARIS

  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGTIMESLICE);

  struct sigaction sa;
  sa.sa_handler = handle_timeslice;
  sa.sa_mask = sigs;
  sa.sa_flags = SA_RESTART;
#if !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))
  sa.sa_restorer = NULL;
#endif // !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))

  SYSTEM_CALL_LESS_ZERO(sigaction(SIGTIMESLICE, &sa, NULL));
#ifdef SOLARIS
  SYSTEM_CALL_LESS_ZERO(timer_create(CLOCK_REALTIME, &se, &timerid));
#endif // SOLARIS
			 
  (void) InterQuantum();

  while (! run_queue.empty())		// Something to run?
    {
#ifdef DEBUG_SCHED
      cerr << __FUNCTION__ << "  Threads in run_queue = [";
      for (list<Thread *>::iterator iter = run_queue.begin();
	   iter != run_queue.end();
	   iter++)
	{
	  cerr << (*iter)->TInfo().ID() << " ";
	}
      cerr << ']' << endl;
#endif

      size_t blocked = 0;	// Number of threads that have blocked so far

      //
      // Walk down the run queue, attempting to execute threads as we go...
      //
      for (list<Thread *>::iterator iter = run_queue.begin();
	   iter != run_queue.end();
	   // iterator is incremented at the end of the loop
	   )
	{
	  Thread& thread = **iter;
	  
	  if (thread.Condition() == Thread::EXITED)
	    {
	      // remove from blocked queue
	      for (list<BlockingObject *>::iterator biter 
		     = blocked_queue.begin();
		   biter != blocked_queue.end();
		   // iterator is advanced in loop
		   )
		{
		  if ((*biter)->getThread() == &thread)
		    {
		      delete *biter;
		      biter = blocked_queue.erase(biter);
		    }
		  else
		    {
		      biter++;
		    }
		}

	      thread_table.RemoveID(thread.TInfo().ID());
	      thread_table.DecLive();
	      delete &thread;
	      
	      // Did it exit while executing in a forbid/permit section?
	      if (scheduler_status.testEnableTimeslice())
		{
		  // No. It's exited nicely.
	          iter = run_queue.erase(iter);
		}
	      else
		{
		  // Yes. It's exited unwisely.
		  Fatal(__FUNCTION__, "Thread exited during forbid/permit section");
		}
	      continue;
	    }

	  BlockStatus& bs = thread.getBlockStatus();

#ifdef DEBUG_SCHED
	  cerr << __FUNCTION__ << " Trying thread: " 
	       << thread.TInfo().ID() << endl;
#endif	// DEBUG_SCHED

	  // Can we run the thread?
	  if (bs.isBlocked())
	    {
#ifdef DEBUG_BLOCK
	      cerr << __FUNCTION__ << "... previously blocked";
#endif	// DEBUG_BLOCK

	      // No, try another
              // Are we in a forbid/permit section?
              if (scheduler_status.testEnableTimeslice())
		{
#ifdef DEBUG_BLOCK
		  cerr << endl;
#endif

	          blocked++;
	          iter++;
		}
	      else
		{
#ifdef DEBUG_BLOCK
		  cerr << " in forbid/permit section" << endl;
#endif

		  const Thread::ReturnValue result = Sleep(false);
		  if (result == Thread::RV_HALT)
		    {
		      return 0;
		    }
		}
	      continue;
	    }
	  
	  //
	  // Enable the timer for timeslicing
	  //
	  if (scheduler_status.testEnableTimeslice())
	    {
	      scheduler_status.resetTimeslice();
	      
	      //
	      // Initialise the timer.
	      //
#ifdef SOLARIS
	      struct itimerspec set_timerval =
	      {
		{ 0, 0 },
		{ TIME_SLICE_SECS, TIME_SLICE_USECS }
	      };
#else
	      itimerval set_timerval = 
	      {
		{ 0, 0 },
		{ TIME_SLICE_SECS, TIME_SLICE_USECS }
	      };
#endif // SOLARIS

#ifdef DEBUG_SCHED	      
	      cerr << __FUNCTION__ 
		   << " Initialising the timer ("
		   << TIME_SLICE_SECS
		   << " secs, "
		   << TIME_SLICE_USECS
		   << " usecs)" << endl;
#endif
#ifdef SOLARIS
	      SYSTEM_CALL_LESS_ZERO(timer_settime(timerid, 0, &set_timerval,
	      				  (itimerspec *)NULL));
#else
	      SYSTEM_CALL_LESS_ZERO(setitimer(ITIMER,
					      &set_timerval,
					      (itimerval *) NULL));
#endif // SOLARIS
	    }

	  //
	  // Run the thread until it drops out, for whatever reason
	  //
#ifdef DEBUG_SCHED
	  cerr << __FUNCTION__
	       << " Start execution of thread " 
	       << thread.TInfo().ID() << endl;
#endif // DEBUG_SCHED
	  const Thread::ReturnValue result = thread.Execute();
#ifdef DEBUG_SCHED
	  cerr << __FUNCTION__
	       << " Exit execution of thread "
	       << thread.TInfo().ID() << endl;
#endif // DEBUG_SCHED

	  {
#ifdef SOLARIS
	    struct itimerspec unset_timerval =
	    { 
	      { 0, 0 },
	      { 0, 0 }
	    };

	    SYSTEM_CALL_LESS_ZERO(timer_settime(timerid, 0, &unset_timerval,
						(itimerspec *)NULL));
#else
	    itimerval clear_timerval = 
	    { 
	      { 0, 0 },
	      { 0, 0 }
	    };
	    
	    	    SYSTEM_CALL_LESS_ZERO(setitimer(ITIMER,
	    			    &clear_timerval,
	    			    (itimerval *) NULL));
#endif // SOLARIS
		    
	  }
	  
	  //
	  // Figure out why execute() exited and take appropriate action.
	  //
	  switch (result)
	    {
	    case Thread::RV_TIMESLICE:
	      //
	      // The timer expired during the thread's execute loop.
	      // This is the normal case ... simply go to the next thread.
	      //
#ifdef DEBUG_SCHED
	      cerr << "RV_TIMESLICE" << endl;
#endif
	      break;
	    case Thread::RV_EXIT:
	      //
	      // The thread exited via a call to thread_exit.
	      //
#ifdef DEBUG_SCHED
	      cerr << "RV_EXIT" << endl;
#endif
	      {
		// Clobber the thread.
		thread_table.RemoveID(thread.TInfo().ID());
		thread_table.DecLive();
		delete &thread;
		break;
	      }
	    case Thread::RV_HALT:
#ifdef DEBUG_SCHED
	      cerr << "RV_HALT" << endl;
#endif
	      // TO DO: Extract exit status from thread's X registers.
	      // TO DO: Mustn't just exit here! (Remember the ICM CS.)
	      return 0;
	      break;
	    case Thread::RV_BLOCK:
#ifdef DEBUG_SCHED
	      cerr << "RV_BLOCK" << endl;
#endif
	      //
	      // The thread attempted an operation that would have blocked.
	      //
	      {
		//
		// Another blocked thread.
		//
		blocked++;
		break;
	      }
	    case Thread::RV_SIGNAL:
	      {
#ifdef DEBUG_SCHED
		cerr << "RV_SIGNAL" << endl;
#endif
		//
		// Set up and execute a thread that executes the appropriate
		// signal handler. Then, continue with the thread that was
		// being executed.
		//
		const Thread::ReturnValue result = HandleSignal();
		if (result == Thread::RV_HALT)
		  {
		    return 0;
		  }
	      }
	      break;
	    case Thread::RV_YIELD:
#ifdef DEBUG_SCHED
	      cerr << "RV_YIELD" << endl;
#endif
	      // Nothing really needs to happen here.
	      break;
	    default:
#ifdef DEBUG_SCHED
	      cerr << __FUNCTION__ << " Exit with result " << result << endl;
#endif	// DEBUG_SCHED
	      
	      return(result);
	      break;
	    }

	  // Advance the iterator if appropriate.

	  // Did the thread exit?
	  if (result == Thread::RV_EXIT)
	    {
	      // Did it exit while executing in a forbid/permit section?
	      if (scheduler_status.testEnableTimeslice())
		{
		  // No. It's exited nicely.
		  // delete *iter;
	          iter = run_queue.erase(iter);
		}
	      else
		{
		  // Yes. It's exited unwisely.
		  Fatal(__FUNCTION__, "Thread exited during forbid/permit section");
		}
	    }
	  // Was the thread in a forbid/permit block?
	  else if (scheduler_status.testEnableTimeslice())
	    {
	      // No. It's ok to go to another thread.
	      iter++;
	    }
          // Thread was executing in a forbid/permit section.
	  // Did it block?
	  else if (result == Thread::RV_BLOCK)
	    {
#ifdef DEBUG_BLOCK
	      cerr << __FUNCTION__ 
		   << " Thread " << thread.TInfo().ID()
		   << " blocked in forbid/permit section" << endl;
#endif

	      // Sleep until something useful happens (maybe).
		  const Thread::ReturnValue result = Sleep(false);
		  if (result == Thread::RV_HALT)
		    {
		      return 0;
		    }
	      // Iterator isn't advanced.
	    }
          // If anything else happened...
	  else
	    {
	      // Do the inter-quantum actions anyway.
	      (void) InterQuantum();
	      // Iterator isn't advanced.

	    }
	  (void)ShuffleAllMessages(); // XXXXXX
	}

#ifdef DEBUG_SCHED
      cerr << __FUNCTION__ << "  blocked = " << blocked
	   << "(" << run_queue.size() << " in run_queue)" << endl;
#endif

      // If none of the threads was runnable...
      if (! run_queue.empty() && blocked == run_queue.size())
	{
	  const Thread::ReturnValue result = Sleep(false);
	  if (result == Thread::RV_HALT)
	    {
	      return 0;
	    }
	}

      //
      // Set up for next traversal of the run time queue
      //
      (void) InterQuantum();

    }

  return 0;
}

bool
Scheduler::processBlockedThreads(void)
{
  int woken = 0;	// Keep track of number of woken threads
      
  for (list<BlockingObject *>::iterator iter = blocked_queue.begin();
       iter != blocked_queue.end();
       // iterator is advanced in loop
       )
    {
      if ((*iter)->unblock(theTimeouts))
	{
	  woken++;
	  delete *iter;
	  iter = blocked_queue.erase(iter);
	}
      else
	{
	  iter++;
	}
    }
  return woken > 0;
}

bool
Scheduler::ShuffleAllMessages(void)
{
  //
  // Distribute the messages that are waiting.
  //

  bool msg_found = false;
  for (list <MessageChannel*>::iterator iter = message_channels.begin();
       iter != message_channels.end();
       iter++)
    {
      if ((*iter)->ShuffleMessages())
	{
	  msg_found = true;
	}
    }
  return msg_found;
}

Thread::ReturnValue
Scheduler::HandleSignal(void)
{
  char buff[128];
  read(sigint_pipe[0], buff, 120);

  Thread *thread = new Thread(NULL, thread_options);

  const ThreadTableLoc loc = thread_table.AddID(thread);
  if (loc == (ThreadTableLoc) -1)
    {
      delete thread;
      Fatal(__FUNCTION__, "Couldn't create signal handler thread\n");
    }

  thread->TInfo().SetID(loc);

  Atom* sig_atom = atoms->add("handle_signal");
  Atom* predicate = atoms->add("$signal_thread_exit");
  Object* problem = thread->BuildCall(predicate, 0);
  thread->programCounter = thread->HandleInterrupt(problem);

  thread->TInfo().Goal() =  sig_atom;
  thread_table.IncLive();
  thread->Condition(Thread::RUNNABLE);

#ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << "  Start execution of signal handler" << endl;
#endif

  Thread::ReturnValue result;

  while (true)
    {
      result = thread->Execute();
      if (result == Thread::RV_BLOCK)
	{
	  Sleep(false);
	}
      else
	{
	  break;
	}
    }

#ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << "  Stop execution of signal handler" << endl;
#endif

  thread_table.RemoveID(thread->TInfo().ID());
  thread_table.DecLive();
  delete thread;

  return result;
}

//
// Insert new thread's record before thread in run queue
//
void Scheduler::insertThread(Thread* th, Thread* newth)
{
  for (list<Thread *>::iterator iter = run_queue.begin();
       iter != run_queue.end();
       iter++
       )
    {
      if (**iter == *th)
	{
	  // this makes it insert after parent iter++;
	  (void) run_queue.insert(iter, newth);
	  return;
	}
    }
  DEBUG_ASSERT(false);
}

//
// Reset the thread by removing the thread from the
// blocked queue and clear block status.
//
void Scheduler::resetThread(Thread* th)
{
  // Remove from blocked queue
  //
  for (list<BlockingObject *>::iterator iter = blocked_queue.begin();
       iter != blocked_queue.end();
       iter++
       )
    {
      BlockingObject& blockingObj = **iter;
      if (blockingObj.getThread() == th)
	{
	  delete *iter;
	  (void) blocked_queue.erase(iter);
	  break;
	}
    }
  th->getBlockStatus().setRunnable();
}

static void
handle_timeslice(int)
{
#ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << endl;
#endif

  extern Scheduler *scheduler;
  scheduler->Status().setTimeslice();
}




