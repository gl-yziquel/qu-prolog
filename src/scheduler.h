// scheduler.h -
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
// $Id: scheduler.h,v 1.3 2002/06/07 00:35:02 qp Exp $

#ifndef	SCHEDULER_H
#define	SCHEDULER_H

#include <list>

#include "atom_table.h"
#include "block.h"
#include "code.h"
#include "cond_list.h"
#include "defs.h"
#include "icm_message.h"
#include "manager.h"
#include "pred_table.h"
#include "sched_rec.h"
#include "scheduler_status.h"
#include "signals.h"
#include "status.h"
#include "string_qp.h"
#include "thread_qp.h"
#include "thread_options.h"
#include "thread_table.h"

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
  list<SchedRec *> run_queue;			// Things to (try to) run
  list<SchedRec *> suspended_queue;		// Things not to (try to) run

  // Blocked things
  list<SchedRec *> blocked_io_queue;		// Blocked waiting on IO
  BlockedIO blocked_io_info;			// FDs involved in blocking

  list<SchedRec *> blocked_icm_queue;		// Blocked waiting on QPNS

  list<SchedRec *> blocked_retry_queue;	// Blocked waiting on retry

  list<SchedRec *> blocked_wait_queue;		// Blocked waiting on change

  list<SchedRec *> timeout_queue;		// Blocked waiting on timeout

  word32 last_process_blocked_wait;		// Stamp of last call to
						// ProcessBlockedWait()

  //
  // Perform actions between thread executions.
  // Return true if any threads were woken.
  //
  bool InterQuantum(CondList<ICMMessage *>&, ThreadTable&);

  //
  // Process all threads that have a timeout on some blocked operation.
  // Return true if any threads were woken.
  //
  bool ProcessTimeouts(void);

  //
  // Process all threads that are blocked on an IO operation.
  // Return true if any threads were woken.
  //
  bool ProcessBlockedIO(void);

  //
  // Process all threads that are blocked waiting to retry.
  // Return true if any threads were woken.
  //
  bool ProcessBlockedRetry(void);

  // 
  // Return true if any threads were woken.
  //
  bool ProcessBlockedICM(CondList<ICMMessage *>&, ThreadTable&);


  //
  // Return true if any threads were woken (generally returns true).
  //
  bool ProcessBlockedWait(void);

  //
  // Set up and execute a signal handling thread.
  //
  Thread::ReturnValue HandleSignal(ThreadTable&, ThreadOptions&);

  // Shuffle a message onto a thread's message queue
  bool ShuffleMessage(ICMMessage *, ThreadTable&);

  // Is IO ready for a blocked thread?
  bool ReadyIO(SchedRec *);

public:
  Scheduler(void);
	    
  ~Scheduler(void);

  // Do the scheduling.
  int32 Schedule(CondList<ICMMessage *>& icm_message_queue,
		 PredTab&, Signals&, ThreadOptions&, ThreadTable&);

  list<SchedRec *>& RunQueue(void) { return run_queue; }
  list<SchedRec *>& SuspendedQueue(void) { return suspended_queue; }
  list<SchedRec *>& TimeoutQueue(void) { return timeout_queue; }

  SchedulerStatus& Status(void) { return scheduler_status; }

  // Sleeps waiting for IO or ICM to become ready.
  Thread::ReturnValue Sleep(CondList<ICMMessage *>&, ThreadTable&, 
			    Signals&, ThreadOptions&);

  void block_icm(Thread*);

  void deleteTimeout(Thread*);

  void insertThread(Thread*, SchedRec*);

  void resetThread(Thread*);
};

#endif	// SCHEDULER_H




