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
// $Id: scheduler.cc,v 1.15 2002/08/25 23:35:10 qp Exp $

#include <algorithm>

#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>

#include "global.h"
#include "atom_table.h"
#include "code.h"
#include "cond_list.h"
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

Scheduler::Scheduler(void)
  : last_process_blocked_wait(0)
{
  //
  // Allow time slicing.
  //
  scheduler_status.setEnableTimeslice();
}

Scheduler::~Scheduler(void) { }

Thread::ReturnValue
Scheduler::Sleep(CondList<ICMMessage *>& icm_message_queue,
	         ThreadTable& thread_table,
		 Signals& signals,
		 ThreadOptions& thread_options)
{
#ifdef DEBUG_BLOCK
  cerr.form("%s Sleeping\n", __FUNCTION__);
#endif
  while (! InterQuantum(icm_message_queue, thread_table))
    {
      if (blocked_io_info.Poll(SLEEP_USECS))
	{
	  break;
	}
      // Were there any signals while we were napping?
      if (signals.Status().testSignals())
	{
#ifdef DEBUG_SCHED
  cerr.form("%s Start signal handler\n", __FUNCTION__);
#endif
	  const Thread::ReturnValue result = 
	    HandleSignal(thread_table, thread_options);
#ifdef DEBUG_SCHED
  cerr.form("%s Exit signal handler\n", __FUNCTION__);
#endif
	  return result;
	}
    }
#ifdef DEBUG_BLOCK
  cerr.form("%s Finished sleeping\n", __FUNCTION__);
#endif
  return Thread::RV_SUCCESS;
}

//
// Perform all the inter quantum actions:
// 	Check on threads blocked on IO
//	Check on threads blocked on ICM
//	Check on threads blocked on waits
//	Check on threads waiting on timeouts
//	Process ICM messages
//
bool
Scheduler::InterQuantum(CondList<ICMMessage *>& icm_message_queue,
			ThreadTable& thread_table)
{
  // 
  // Was anything actually done?
  //
  bool result = false;
  
  // Check things that might timeout
  result = result || ProcessTimeouts();
  
  // Check things blocked on IO
  result = result || ProcessBlockedIO();
  
  // And things that are waiting on ICM messages
  result = result || ProcessBlockedICM(icm_message_queue,
				       thread_table);
  
  // And things waiting for changes in data areas
  result = result || ProcessBlockedWait();

  return result;
}

// Argument needs to be a SchedRec * since we're called from
// a generic algorithm running over a list<SchedRec *>
static bool
sched_rec_removed(SchedRec *sr)
{
  return sr->Removed();
}

int32
Scheduler::Schedule(CondList<ICMMessage *>& icm_message_queue,
		    PredTab& predicates,
		    Signals& signals,
		    ThreadOptions& thread_options,
		    ThreadTable& thread_table)
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

  const char *symbol = thread_table.MakeName(first);
  atoms->add(symbol);
  thread->TInfo().SetSymbol(symbol);

  SchedRec *first_rec = new SchedRec(*thread);

  run_queue.push_back(first_rec);

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
#if !(defined(SOLARIS) || defined(FREEBSD))
  sa.sa_restorer = NULL;
#endif // !(defined(SOLARIS) || defined(FREEBSD))

  SYSTEM_CALL_LESS_ZERO(sigaction(SIGTIMESLICE, &sa, NULL));
#ifdef SOLARIS
  SYSTEM_CALL_LESS_ZERO(timer_create(CLOCK_REALTIME, &se, &timerid));
#endif // SOLARIS
			 
  (void) InterQuantum(icm_message_queue, thread_table);

  while (! run_queue.empty())		// Something to run?
    {
#ifdef DEBUG_SCHED
      cerr.form("%s Threads in run_queue = [", __FUNCTION__);
      for (list<SchedRec *>::iterator iter = run_queue.begin();
	   iter != run_queue.end();
	   iter++)
	{
	  cerr.form("%ld ", (*iter)->Thr().TInfo().ID());
	}
      cerr << ']' << endl;
#endif

      size_t blocked = 0;	// Number of threads that have blocked so far

      //
      // Walk down the run queue, attempting to execute threads as we go...
      //
      for (list<SchedRec *>::iterator iter = run_queue.begin();
	   iter != run_queue.end();
	   // iterator is incremented at the end of the loop
	   )
	{
	  SchedRec& sched_rec = **iter;
	  Thread& thread = sched_rec.Thr();
	  
	  BlockStatus& bs = thread.getBlockStatus();

#ifdef DEBUG_SCHED
	  cerr.form("%s Trying thread: %ld\n",
		    __FUNCTION__, thread.TInfo().ID());
#endif	// DEBUG_SCHED

	  // Can we run the thread?
	  if (bs.IsBlocked() && !bs.IsRestarted())
	    {
#ifdef DEBUG_BLOCK
	      cerr << __FUNCTION__ << "... previously blocked, not restarted";
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

		  const Thread::ReturnValue result = 
		    Sleep(icm_message_queue, thread_table, 
			  signals, thread_options);
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
	      cerr.form("%s Initialising the timer (%ld secs, %ld usecs)\n",
			__FUNCTION__, TIME_SLICE_SECS, TIME_SLICE_USECS);
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

	  SYSTEM_CALL_NON_ZERO(pthread_sigmask(SIG_UNBLOCK, &sigs, NULL));
	  
	  //
	  // Run the thread until it drops out, for whatever reason
	  //
#ifdef DEBUG_SCHED
	  cerr.form("%s Start execution of thread %ld\n", __FUNCTION__, thread.TInfo().ID());
#endif // DEBUG_SCHED
	  const Thread::ReturnValue result = thread.Execute();
#ifdef DEBUG_SCHED
	  cerr.form("%s Exit execution of thread %ld\n", __FUNCTION__, thread.TInfo().ID());
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
DEBUG_CODE(
  for (list<SchedRec *>::iterator titer = timeout_queue.begin();
       titer != timeout_queue.end(); titer++)
    {
      DEBUG_ASSERT(!(sched_rec == **titer));
    }
  for (list<SchedRec *>::iterator titer = blocked_io_queue.begin();
       titer != blocked_io_queue.end(); titer++)
    {
      DEBUG_ASSERT(!(sched_rec == **titer));
    }
  for (list<SchedRec *>::iterator titer = blocked_wait_queue.begin();
       titer != blocked_wait_queue.end(); titer++)
    {
//    cerr << "debug: " << (word32)(*titer) << endl;
      DEBUG_ASSERT(!(sched_rec == **titer));
    }
);
		// Clobber the associated thread.
		Thread* th = &sched_rec.Thr();
		thread_table.RemoveID(th->TInfo().ID());
		thread_table.DecLive();
		delete th;

		// Get rid of the scheduler information.
		// delete *iter;
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

		// Does the block have an associated timeout?
		BlockStatus& bs = thread.getBlockStatus();
		
		if (bs.IsTimeout())
		  {
#if defined(DEBUG_BLOCK) || defined(DEBUG_TIMEOUT)
		    cerr.form("%s Thread %ld has blocked on timeout %ld\n",
			      __FUNCTION__, bs.IsTimeout());
#endif

		    list<SchedRec *>::iterator timeout_iter = timeout_queue.begin();
		    for ( ;
		         timeout_iter != timeout_queue.end();
		         timeout_iter++)
		      {
			if (**timeout_iter == sched_rec)
			  {
			    break;
			  }
		      }

		    if (timeout_iter == timeout_queue.end())
                      {
		        // Update the list of blocked threads with timeouts
		        SchedRec *sr = new SchedRec(thread, bs.Timeout());
		        sr->Block();
                        list<SchedRec *>::iterator timeout_insert_iter =
			  timeout_queue.begin();
			for ( ;
			     timeout_insert_iter != timeout_queue.end();
			     timeout_insert_iter++)
			  {
		   	    if ((**timeout_insert_iter).Timeout() > bs.Timeout())
			      {
			        break;
			      }
			  }

			timeout_queue.insert(timeout_insert_iter, sr);
		      }
		    else
		      {
			bs.setTimeout((**timeout_iter).Timeout());
		      }
		  }
		if (bs.testBlockWait())
		  {
#if defined(DEBUG_BLOCK) || defined(DEBUG_TIMEOUT)
		    cerr.form("%s Thread %ld blocks on wait\n",
			      __FUNCTION__, thread.TInfo().ID());
#endif
		    SchedRec *sr = new SchedRec(thread);
		    blocked_wait_queue.push_back(sr);

		    bs.resetRestartWait();
		  }
		
		// Did the thread block waiting on io?
		else if (bs.testBlockIO())
		  {
#if defined(DEBUG_BLOCK) || defined(DEBUG_IO)
		    cerr.form("%s Thread %ld blocks on IO (%ld %ld)\n",
			      __FUNCTION__, thread.TInfo().ID(), 
			      bs.getFD(), bs.getIOType());
#endif
		    // Update the list of blocked threads waiting on io
		    SchedRec *sr = new SchedRec(thread);
		    sr->Block();
		    blocked_io_queue.push_back(sr);
		    blocked_io_info.Add(bs.getFD(), bs.getIOType());

		    // Clear the restart flag, which will be set when
		    // the io operation can be restarted.
		    bs.resetRestartIO();
		  }
		// Did the thread block waiting on icm?
		else if (bs.testBlockICM())
		  {
#if defined(DEBUG_BLOCK) || defined(DEBUG_ICM)
		    cerr.form("%s Thread %ld blocks on ICM\n",
			      __FUNCTION__, thread.TInfo().ID());
#endif
		    SchedRec *sr = new SchedRec(thread);
		    blocked_icm_queue.push_back(sr);

		    // Clear the restart flag, which will be set when
		    // the icm operation can be restarted.
		    bs.resetRestartICM();
		  }
		else
		  {
		    // Should never happen!
		    DEBUG_ASSERT(false);
		  }
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
		const Thread::ReturnValue result = 
		  HandleSignal(thread_table, thread_options);
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
	      cerr.form("%s Exit with result %ld\n", __FUNCTION__, result);
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
		  delete *iter;
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
	      cerr.form("%s Thread %ld blocked in forbid/permit section\n",
			__FUNCTION__, thread.TInfo().ID()); 
#endif

	      // Sleep until something useful happens (maybe).
		  const Thread::ReturnValue result = 
		    Sleep(icm_message_queue, thread_table, 
			  signals, thread_options);
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
	      (void) InterQuantum(icm_message_queue, thread_table);
	      // Iterator isn't advanced.
	    }
	}

#ifdef DEBUG_SCHED
      cerr.form("%s blocked = %ld (%ld in run_queue)\n",
		__FUNCTION__, blocked, run_queue.size());
#endif

      // If none of the threads was runnable...
      if (! run_queue.empty() && blocked == run_queue.size())
	{
	  const Thread::ReturnValue result = 
	    Sleep(icm_message_queue, thread_table, signals, thread_options);
	  if (result == Thread::RV_HALT)
	    {
	      return 0;
	    }
	}

      //
      // Set up for next traversal of the run time queue
      //
      (void) InterQuantum(icm_message_queue, thread_table);
    }

  return 0;
}

// Argument needs to be a SchedRec * since it's being called from a 
// generic algorithm working over a list<SchedRec *>
static bool
sched_rec_unblocked(SchedRec *sr)
{
#ifdef DEBUG_BLOCK
  if (! sr->Blocked())
    {
      cerr.form("%s Thread %ld unblocked\n",
		__FUNCTION__, sr->Thr().TInfo().ID());
    }
#endif

  return ! sr->Blocked();
}

bool
Scheduler::ProcessTimeouts(void)
{
  const time_t now = time(NULL);
      
  int woken = 0;	// Keep track of number of woken threads
      
  for (list<SchedRec *>::iterator iter = timeout_queue.begin();
       iter != timeout_queue.end() && (*iter)->Timeout() <= now;
       // iterator is advanced in loop
       woken++)
    {
      SchedRec& sched_rec = **iter;
      
      sched_rec.Unblock();
      
      Thread& thread = sched_rec.Thr();
      
#if defined(DEBUG_BLOCK) && defined(DEBUG_TIMEOUT)
      cerr.form("%s Thread %ld timed out\n",
		__FUNCTION__, sched_rec.Thr().TInfo().ID());
#endif
      
      BlockStatus& bs = thread.getBlockStatus();
      
      bs.SetTimedOut();
      
      // A timeout will often be associated with an IO or ICM block,
      // so check for these...
      //
      // We restart them since we want them to run, so that they can
      // detect the timeout and fail.
      //
      // We also remove them from the other blocked queues because
      // no one else will do the cleaning up!
      if (bs.testBlockIO())
	{
	  bs.setRestartIO();
	  
	  for (list<SchedRec *>::iterator blocked_io_iter = blocked_io_queue.begin();
	       blocked_io_iter != blocked_io_queue.end();
	       blocked_io_iter++)
	    {
	      if (**blocked_io_iter == sched_rec)
		{
	  	  delete *blocked_io_iter;
	  	  (void) blocked_io_queue.erase(blocked_io_iter);
	  	  blocked_io_info.Remove(bs.getFD(), bs.getIOType());
		  break;
		}
	    }
	}
      else if (bs.testBlockICM())
	{
	  bs.setRestartICM();
	  
	  for (list<SchedRec *>::iterator blocked_icm_iter = blocked_icm_queue.begin();
	       blocked_icm_iter != blocked_icm_queue.end();
	       blocked_icm_iter++)
	    {
	      if (**blocked_icm_iter == sched_rec)
		{
	  	  delete *blocked_icm_iter;
	  	  (void) blocked_icm_queue.erase(blocked_icm_iter);
		  break;
		}
	    }
	}
      else if (bs.testBlockWait())
        {
          bs.setRestartWait();

          for (list<SchedRec *>::iterator blocked_wait_iter = blocked_wait_queue.begin();
	       blocked_wait_iter != blocked_wait_queue.end();
	       blocked_wait_iter++)
	    {
	      if (**blocked_wait_iter == sched_rec)
		{
		  delete *blocked_wait_iter;
		  (void) blocked_wait_queue.erase(blocked_wait_iter);
		  break;
		}
	    }
	}
//      else
//	{
//	  DEBUG_ASSERT(false);
//	}

      // Grab back storage.
      delete *iter;
      iter = timeout_queue.erase(iter);
    }

#ifdef DEBUG_TIMEOUT
  cerr.form("%s woken = %ld\n", __FUNCTION__, woken);
#endif

  return woken > 0;
}

bool
Scheduler::ProcessBlockedIO(void)
{
  bool unblocked = false;
  for (list<SchedRec *>::iterator iter = blocked_io_queue.begin();
       iter != blocked_io_queue.end();
       )
    {
      SchedRec& sched_rec = **iter;

      Thread& thread = sched_rec.Thr();

      BlockStatus& bs = thread.getBlockStatus();
      
      if (is_ready(bs.getFD(), bs.getIOType()) 
          || thread.Condition() == ThreadCondition::EXITED)
	{
#if defined(DEBUG_BLOCK) && defined(DEBUG_IO)
	  cerr.form("%s Thread %ld unblocked on IO (%ld %ld)\n",
		    __FUNCTION__, sched_rec.Thr().TInfo().ID(),
		    bs.getFD(), bs.getIOType());
#endif

	  // Yes... mark it to be restarted
	  bs.setRestartIO();
	  
	  // Update the information about which IO channels are being
	  // waited on.
	  blocked_io_info.Remove(bs.getFD(), bs.getIOType());
	  
	  sched_rec.Unblock();
	  unblocked = true;
          delete *iter;
	  iter = blocked_io_queue.erase(iter);
	}
      else
	{
	  iter++;
	}
    }
  
#ifdef DEBUG_IO
  cerr.form("%s unblocked = %ld\n", __FUNCTION__, unblocked ? 1 : 0);
#endif

  return unblocked;
}

bool 
Scheduler::ShuffleMessage(ICMMessage *icm_message,
			  ThreadTable& thread_table)
{
#ifdef ICM_DEF
  char *icm_target;
  
  (void) icmAnalyseHandle(icm_message->Recipient(),
			  &icm_target, NULL, NULL, NULL, NULL);
  
  ICMIncomingTarget target(icm_target);
  
  ThreadTableLoc id = (ThreadTableLoc) -1;
  if (target.IsID())
    {
      id = target.ID();
#ifdef DEBUG_ICM
      cerr.form("%s Message for thread %ld\n", __FUNCTION__, id);
#endif
    }
  else if (target.IsSymbol())
    {
      id = thread_table.LookupName(target.Symbol());
      if (id == (ThreadTableLoc) -1)
	{
	  return false;
	}
#ifdef DEBUG_ICM
      cerr.form("%s Message for thread %s = %ld\n",
		__FUNCTION__, target.Symbol(), id);
#endif
    }
  
  if (!thread_table.IsValid(id))
    {
      return false;
    }
  else
    {
      Thread* thread = thread_table.LookupID(id);
      if (thread == NULL)
	{
	  return false;
	}
      thread->ICMQueue().push_back(icm_message);
      return true;
    }
#else // ICM_DEF
  return false;
#endif // ICM_DEF
}
      
// Argument needs to be a SchedRec * since we're being called from
// a generic algorithm working over a list<SchedRec *>
static bool
ready_icm(SchedRec *sr)
{
  Thread& thread = sr->Thr();
  
  BlockStatus& bs = thread.getBlockStatus();

#if defined(DEBUG_BLOCK) || defined(DEBUG_ICM)
cerr.form("%s Thread %ld testing for ready ready for ICM bs.QueueSize = %ld ICMQueueSize = %ld\n",
		__FUNCTION__, sr->Thr().TInfo().ID(),
	  bs.QueueSize(), thread.ICMQueue().size());
#endif  
  if (bs.QueueSize() != thread.ICMQueue().size() 
      || thread.Condition() == ThreadCondition::EXITED)
    {
      // Yes... mark it to be restarted
#if defined(DEBUG_BLOCK) || defined(DEBUG_ICM)
      cerr.form("%s Thread %ld marked as ready for ICM\n",
		__FUNCTION__, sr->Thr().TInfo().ID());
#endif

      bs.setRestartICM();
     
      return true;
    }
  else
    {
      return false;
    }
}

bool
Scheduler::ProcessBlockedICM(CondList<ICMMessage *>& icm_message_queue,
			     ThreadTable& thread_table)
{
  //
  // Distribute the messages that are waiting.
  //
  if (icm_message_queue.Trylock())
    {
      for (list<ICMMessage *>::iterator iter = icm_message_queue.begin();
	   iter != icm_message_queue.end(); )
	{
	  ICMMessage *icm_message = *iter;
	  if (ShuffleMessage(icm_message, thread_table))
	    {
	      iter = icm_message_queue.erase(iter);
	    }
	  else
	    {
	      iter++;
	    }
	}

      icm_message_queue.Unlock();

      bool unblocked = false;
      for (list<SchedRec *>::iterator iter = blocked_icm_queue.begin();
           iter != blocked_icm_queue.end();
	   )
	{
	  if (ready_icm(*iter))
	    {
	      unblocked = true;
	      delete *iter;
	      iter = blocked_icm_queue.erase(iter);
	    }
	  else
	    {
	      iter++;
	    }
	}

#ifdef DEBUG_ICM
      cerr.form("%s unblocked = %ld\n", __FUNCTION__, unblocked ? 1 : 0);
#endif

      return unblocked;
    }
  else
    {
      // No messages were delivered, no threads were unblocked.
      return false;
    }
}

// Argument needs to be a SchedRec * since we're being called from
// a genetic algorithm working over a list<SchedRec *>
static void
restart_wait(SchedRec *sr)
{
  Thread& thread = sr->Thr();

#if defined(DEBUG_BLOCK) && defined(DEBUG_TIMEOUT)
  cerr.form("%s Checking %ld\n",
	    __FUNCTION__, sr->Thr().TInfo().ID());
#endif

  thread.getBlockStatus().setRestartWait();
}

bool
Scheduler::ProcessBlockedWait(void)
{
  const word32 now = code->GetStamp();

  if (now > last_process_blocked_wait)
    {
      last_process_blocked_wait = now;

      // Set a restart for everything on the queue.
      (void) for_each(blocked_wait_queue.begin(),
		      blocked_wait_queue.end(),
		      restart_wait);

      // If there were more than 0 things on the queue, something was done.
      const bool unblocked = ! blocked_wait_queue.empty();

      // Clobber the queue.
      for (list<SchedRec *>::iterator iter = blocked_wait_queue.begin();
           iter != blocked_wait_queue.end(); )
        {
          for (list<SchedRec *>::iterator t_iter = timeout_queue.begin();
	       t_iter != timeout_queue.end();
	       t_iter++)
	    {
	      if (**t_iter == **iter)
		{
		  delete *t_iter;
		  (void) timeout_queue.erase(t_iter);
		  break;
		}
	    }
           delete *iter;
           iter = blocked_wait_queue.erase(iter);
        }

#ifdef DEBUG_RETRY
      cerr.form("%s unblocked = %ld\n", __FUNCTION__, unblocked ? 1 : 0);
#endif

      return unblocked;
    }
  else
    {
      return false;
    }
}

Thread::ReturnValue
Scheduler::HandleSignal(ThreadTable& thread_table, 
			ThreadOptions& thread_options)
{
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
  cerr.form("%s Start execution of signal handler\n", __FUNCTION__);
#endif
  const Thread::ReturnValue result = thread->Execute();
#ifdef DEBUG_SCHED
  cerr.form("%s Stop execution of signal handler\n", __FUNCTION__);
#endif

  thread_table.RemoveID(thread->TInfo().ID());
  thread_table.DecLive();
  delete thread;

  return result;
}

void
Scheduler::block_icm(Thread* th)
{
  SchedRec *sr = new SchedRec(*th);
  blocked_icm_queue.push_back(sr);
}

//
// Delete the timeout for the given thread (if any).
//
void Scheduler::deleteTimeout(Thread* th)
{
  for (list<SchedRec *>::iterator iter = timeout_queue.begin();
       iter != timeout_queue.end();
       iter++
       )
    {
      SchedRec& sched_rec = **iter;
      if (sched_rec.Thr() == *th)
	{
	  delete *iter;
	  (void) timeout_queue.erase(iter);
	  break;
	}
    }
}

//
// Insert new thread's record before thread in run queue
//
void Scheduler::insertThread(Thread* th, SchedRec* newrec)
{
  for (list<SchedRec *>::iterator iter = run_queue.begin();
       iter != run_queue.end();
       iter++
       )
    {
      SchedRec& sched_rec = **iter;
      if (sched_rec.Thr() == *th)
	{
	  // this makes it insert after parent iter++;
	  (void) run_queue.insert(iter, newrec);
	  return;
	}
    }
  DEBUG_ASSERT(false);
}

//
// Reset the thread by removing the thread from all timeout and
// blocked queues and clear block status.
//
void Scheduler::resetThread(Thread* th)
{
  // Remove from timeout queue
  //
  for (list<SchedRec *>::iterator iter = timeout_queue.begin();
       iter != timeout_queue.end();
       iter++
       )
    {
      SchedRec& sched_rec = **iter;
      if (sched_rec.Thr() == *th)
	{
	  delete *iter;
	  (void) timeout_queue.erase(iter);
	  break;
	}
    }
  // Remove from blocked IO queue
  //
  for (list<SchedRec *>::iterator iter = blocked_io_queue.begin();
       iter != blocked_io_queue.end();
       iter++
       )
    {
      SchedRec& sched_rec = **iter;
      if (sched_rec.Thr() == *th)
	{
	  delete *iter;
	  (void) blocked_io_queue.erase(iter);
	  break;
	}
    }
  // Remove from blocked ICM queue
  //
  for (list<SchedRec *>::iterator iter = blocked_icm_queue.begin();
       iter != blocked_icm_queue.end();
       iter++
       )
    {
      SchedRec& sched_rec = **iter;
      if (sched_rec.Thr() == *th)
	{
	  delete *iter;
	  (void) blocked_icm_queue.erase(iter);
	  break;
	}
    }
  // Remove from blocked wait queue
  //
  for (list<SchedRec *>::iterator iter = blocked_wait_queue.begin();
       iter != blocked_wait_queue.end();
       iter++
       )
    {
      SchedRec& sched_rec = **iter;
      if (sched_rec.Thr() == *th)
	{
	  delete *iter;
	  (void) blocked_wait_queue.erase(iter);
	  break;
	}
    }
  // clear flags
  th->getBlockStatus().Clear();
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




