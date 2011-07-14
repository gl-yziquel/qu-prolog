// scheduler.h -
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: scheduler.h,v 1.13 2006/02/14 02:40:09 qp Exp $

#ifndef	SCHEDULER_H
#define	SCHEDULER_H

#include <list>

#include "atom_table.h"
#include "block.h"
#include "code.h"
#include "defs.h"
#include "manager.h"
#include "pred_table.h"
//#include "sched_rec.h"
#include "scheduler_status.h"
#include "signals.h"
#include "status.h"
//#include "string_qp.h"
#include "thread_qp.h"
#include "thread_options.h"
#include "thread_table.h"
#include "timeout.h"

#define SIGTIMESLICE (SIGVTALRM)
#define ITIMER (ITIMER_VIRTUAL)

class Thread;

class Scheduler
{
private:
  SchedulerStatus scheduler_status;

  //
  // Queues
  //
  list<Thread *> run_queue;			// Threads to run

  list<BlockingObject *> blocked_queue;		// Blocked threads

  list <MessageChannel*> message_channels;       // All the message channels

  ThreadOptions& thread_options;

  ThreadTable& thread_table;

  Signals& signals;

  PredTab& predicates;

#ifdef WIN32
  UINT_PTR timerptr;
#endif

  Timeval theTimeouts;           // Calculated in IterQuantum to determine of 
	                         // Sleep is a block or a timeout

  Thread::ReturnValue run_timer_goal(Thread* thread);

  //
  // Perform actions between thread executions.
  // Return true if any threads were woken.
  //
  bool InterQuantum(void);

  //
  // Process all blocked threads.
  // Return true if any threads were woken.
  //
  bool processBlockedThreads(void);
  
  //
  // Set up and execute a signal handling thread.
  //
  Thread::ReturnValue HandleSignal();
  
  // Shuffle all the messages onto thread's message queues
  bool ShuffleAllMessages(void);
  
  // Look for fd's that are ready
  bool poll_fds(Timeval&);

public:
  Scheduler(ThreadOptions& to, ThreadTable& tt, Signals& s, PredTab& p);
	    
  ~Scheduler(void);

  // Do the scheduling.
  int32 Schedule(void);

  list<Thread *>& runQueue(void) { return run_queue; }
  list<BlockingObject *>& blockedQueue(void) { return blocked_queue; }

  SchedulerStatus& Status(void) { return scheduler_status; }

  list <MessageChannel*>& getChannels(void) { return message_channels; }

  // Sleeps waiting for IO or messages to become ready.
  Thread::ReturnValue Sleep();

  void insertThread(Thread*, Thread*);
  void deleteThread(Thread*);
  void resetThread(Thread*);
};

#ifdef WIN32
//void CALLBACK win32_handle_timer_wrapper(HWND hWnd, UINT nMsg,

//                           UINT_PTR nIDEvent, DWORD dwTime);
#endif

#endif	// SCHEDULER_H




