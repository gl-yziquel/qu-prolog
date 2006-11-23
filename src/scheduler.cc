// scheduler.cc - Schedule execution of threads.
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
// $Id: scheduler.cc,v 1.38 2006/03/30 22:50:31 qp Exp $

#include <algorithm>

#include <time.h>
#include <sys/types.h>
#ifndef WIN32
        #include <sys/time.h>
#endif
#include <signal.h>

#include "global.h"
#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "errors.h"
#ifdef ICM_DEF
#include "icm_handle.h"
#include "icm_message.h"
#endif
#include "io_qp.h"
#include "manager.h"
#include "pred_table.h"
#include "protos.h"
#include "scheduler.h"
#include "thread_qp.h"
#include "thread_condition.h"
#include "thread_table.h"

#ifdef WIN32
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <io.h>
#endif

//
// Determine the length of the scheduler quantum.
//

#ifdef DEBUG_SCHED
static const int32 TIME_SLICE_SECS = 1L;
static const int32 TIME_SLICE_USECS = 1000000L;
#else
static const int32 TIME_SLICE_SECS = 0L;
#ifdef WIN32
static const int32 TIME_SLICE_USECS = 1000L;
#else
static const int32 TIME_SLICE_USECS = 100000L;
#endif
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
  : thread_options(to), thread_table(tt), signals(s), 
    predicates(p),theTimeouts((time_t) -1, 0)
{
  //
  // Allow time slicing.
  //
  scheduler_status.setEnableTimeslice();
}

Scheduler::~Scheduler(void) { }

extern int* sigint_pipe;

bool Scheduler::poll_fds(Timeval& poll_timeout)
{
#ifndef WIN32
  fd_set rfds, wfds;
  FD_ZERO(&rfds);
  FD_ZERO(&wfds);

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
      (*iter)->processTimeouts(poll_timeout);
    }
#endif

#ifdef WIN32
       // We need to turn these fd sets into Handle arrays. So...
        HANDLE* handles;

        int hcount=1;
        handles = new HANDLE[blocked_queue.size()+1];
        handles[0] = (HANDLE)_get_osfhandle(sigint_pipe[0]);

        for(list<BlockingObject *>::iterator iter = blocked_queue.begin();
                        iter != blocked_queue.end();
                        iter++)
        {
                handles[hcount] = (HANDLE)_get_osfhandle((*iter)->getFD());
                hcount++;
        }

#endif


  int result;
  if (poll_timeout.isForever())
    {
      // Remember, select only works on sockets in windows
#ifdef WIN32
      result = WaitForMultipleObjects(hcount + 1, handles, true, NULL)
 > 0;
#else
      result = select(max_fd + 1, &rfds, &wfds, NULL, NULL) > 0;
#endif
    }
  else
    {
      struct timeval timeout = {poll_timeout.Sec(), poll_timeout.MicroSec()};
#ifdef WIN32
      result = WaitForMultipleObjects(hcount + 1, handles, true,
                   timeout.tv_usec / 1000 + timeout.tv_sec*1000 ) > 0;
#else
      result = select(max_fd + 1, &rfds, &wfds, NULL, &timeout) > 0;
#endif
    }

#ifdef WIN32
    //Free up stuff
    delete [] handles;
    handles = NULL;

    if (result == WAIT_FAILED) { cerr << GetLastError() << endl; }
#endif

  return result > 0;

}

Thread::ReturnValue
Scheduler::Sleep()
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
      if (poll_fds(theTimeouts))
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
  theTimeouts.setTime((time_t) -1, 0);
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

#ifdef WIN32
  timerptr = SetTimer(NULL, NULL, 500, &win32_handle_timer_wrapper);
#else
  // Who'd have thought it?! Here's a case where
  // Windows > Unix for C++. Unlike Unix, in
  // Windows you don't need to create the timer
  // ahead of time - you create it and set it
  // simultaneously.

  // Search for "SetTimer" to see where this
  // is done. (Or setitimer for some unices).

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
#endif

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
	  
	  if (thread.Condition() == ThreadCondition::EXITED)
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

		  const Thread::ReturnValue result = Sleep();
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
#ifndef WIN32
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
#endif //WIN32

#ifdef DEBUG_SCHED	      
	      cerr << __FUNCTION__ 
		   << " Initialising the timer ("
		   << TIME_SLICE_SECS
		   << " secs, "
		   << TIME_SLICE_USECS
		   << " usecs)" << endl;
#endif
#ifdef WIN32 //Alright, let's create AND set the timer CHEESE
             timerptr = SetTimer(0, timerptr, TIME_SLICE_USECS, 
                                 &win32_handle_timer_wrapper);
#else
#ifdef SOLARIS
	      SYSTEM_CALL_LESS_ZERO(timer_settime(timerid, 0, &set_timerval,
	      				  (itimerspec *)NULL));
#else
	      SYSTEM_CALL_LESS_ZERO(setitimer(ITIMER,
					      &set_timerval,
					      (itimerval *) NULL));
#endif // SOLARIS
#endif // WIN32
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
#ifdef WIN32 //Now we need to kill the timer
            (void)KillTimer(0, timerptr);
#else
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
#endif
		    
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
		  const Thread::ReturnValue result = Sleep();
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
	  const Thread::ReturnValue result = Sleep();
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
#ifndef WIN32 // This doesn't do ANYTHING
        char buff[128];
        read(sigint_pipe[0], buff, 120);
#else
        // This may have been removed by the tokeniser,
        // should we be in the position of fake EOF.
        if (!_eof(sigint_pipe[0]))
        {
                char buff[128];
                read(sigint_pipe[0], buff, 120);
        }
#endif

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
  thread->Condition(ThreadCondition::RUNNABLE);

#ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << "  Start execution of signal handler" << endl;
#endif

  Thread::ReturnValue result;

  while (true)
    {
      result = thread->Execute();
      if (result == Thread::RV_BLOCK)
	{
	  Sleep();
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
  assert(false);
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

#ifdef WIN32
static VOID CALLBACK win32_handle_timer_wrapper(HWND hWnd, UINT nMsg,
                UINT_PTR nIDEvent, DWORD dwTime)
{
        //cerr << "Handling a timeslice..." << endl;
        handle_timeslice(0);
}
#endif

static void
handle_timeslice(int)
{
#ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << endl;
#endif

  extern Scheduler *scheduler;
  scheduler->Status().setTimeslice();
}




