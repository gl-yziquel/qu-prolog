// thread_escapes.cc - Multi-threading support primitives.
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
// $Id: thread_escapes.cc,v 1.18 2003/09/28 07:53:37 qp Exp $

#include <errno.h>

#include "config.h"

#include "global.h"
#include "thread_qp.h"
#include "thread_decode.h"
#include "thread_table.h"
#include "timeval.h"

// @internaldoc
// @pred '$thread_fork'(Name, Goal, ThreadSizes)
// @mode '$thread_fork'(?, +, +) is semidet
// @type '$thread_fork'(atom, goal, ThreadSizes)
// @description
// Create a new thread, with the given goal and whose data areas are the 
// specified sizes.
//
// ThreadSizes is a structure:
//   '$thread_sizes'(HeapSize, ScratchpadSize, BindingTrailSize, 
//                   ObjectTrailSize, IPTrailSize, TagTrailSize, 
//                   RefTrailSize, EnvSize, ChoiceSize, NameSize, IPSize)
// where all the sizes are integers and the units they describe can be 
// found in the description of thread_new/3.
//
// The call will fail if a thread cannot be created.
// @end pred

Thread::ReturnValue
Thread::psi_thread_fork(Object *& name_arg,
			Object *& goal_arg,
			Object *& sizes_arg)
{
  Object* argN = heap.dereference(name_arg);
  Object* argG = heap.dereference(goal_arg);
  Object* argS = heap.dereference(sizes_arg);
  
  // Check to see the name is instantiated and is an atom.
  if (!argN->isVariable() && !argN->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  // Check the goal
  if (argG->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // Check and decode the sizes.
  int heap_size; 
  int scratchpad_size;
  int binding_trail_size;
  int object_trail_size;
  int ip_trail_size;
  int tag_trail_size;
  int ref_trail_size;
  int env_size;
  int choice_size;
  int name_table_size;
  int ip_table_size;
  
  DECODE_DEFAULTS_ARG(heap, argS, 3,
		      heap_size,
		      scratchpad_size,
		      binding_trail_size,
		      object_trail_size,
		      ip_trail_size,
		      tag_trail_size,
		      ref_trail_size,
		      env_size,
		      choice_size,
		      name_table_size,
		      ip_table_size);

  // Allocate storage.
  Thread *thread = new Thread(this,	// This thread is the parent
			      scratchpad_size,
			      heap_size,
			      binding_trail_size,
			      object_trail_size,
			      ip_trail_size,
			      tag_trail_size,
			      ref_trail_size,
			      env_size,
			      choice_size,
			      name_table_size,
			      ip_table_size);
			      //*thread_options);

  const ThreadTableLoc loc = thread_table->AddID(thread);
  if (loc == (ThreadTableLoc) -1)
    {
      delete thread;

      PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 1);
    }

  thread->TInfo().SetID(loc);

  // If the thread has a symbol...
  if (argN->isAtom())
    {
      //
      // Set up the thread's symbol.
      //
      const char *symbol = atoms->getAtomString(OBJECT_CAST(Atom*, argN));

      // If nothing else has this name already...
      if (thread_table->LookupName(symbol) == (ThreadTableLoc) -1)
	{
	  // Nothing else has this name already.
	  const bool success = thread_table->AddName(symbol, loc);
	  if (success)
	    {
	      thread->TInfo().SetSymbol(symbol);
	    }
	  else
            {
              delete thread;
              thread_table->RemoveID(loc);

              PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 1);
            }
	}
      else
	{
	  delete thread;

	  thread_table->RemoveID(loc);

	  PSI_ERROR_RETURN(EV_VALUE, 1);
	}
    }
  else
    {
      // The thread neads a name
      const char *symbol = thread_table->MakeName(loc).c_str();
      thread->TInfo().SetSymbol(symbol);
      if (!unify(argN, atoms->add(symbol)))
	{
	  return (RV_FAIL);
	}
    }

  // Now set up the thread's initial goal

  // Copy the goal onto the target thread's heap.
  thread->TInfo().Goal() =  heap.copyTerm(argG, thread->heap);
  
  // Set the initial PC to the standard thread entry code.
  // thread->Execute() will wait until this is set before
  // moving into its main loop.
  thread->programCounter =
    predicates->getCode(predicates->lookUp(atoms->add("$thread_start"), 0,
					   atoms, code)
			).getPredicate(code);

  if (thread->programCounter == NULL)
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 0);
    }
  
  thread_table->IncLive();

#ifdef DEBUG_MT
  cerr.form("%s Thread %ld, %ld now live\n",
	    __FUNCTION__, thread->TInfo().ID(), thread_table->Live());
  //      heap.DisplayTerm(cerr, *atoms, argG);
#endif
  
  // The thread is now runnable.
  thread->Condition(RUNNABLE);

  // Add it to the run queue
  scheduler->insertThread(this, thread);

  return RV_SUCCESS;
}

// @doc
// @pred thread_symbol(Thread, Name)
// @mode thread_symbol(+, -) is det
// @mode thread_symbol(-, +) is det
// @type thread_symbol(thread, atom)
// @description
// The thread has name Name.
// @end pred
// @ed doc
Thread::ReturnValue
Thread::psi_thread_symbol(Object *& thread_arg, Object *& name_arg)
{
  Object* nameT = heap.dereference(name_arg);
  Object* argT = heap.dereference(thread_arg); // Thread id

  if (nameT->isAtom())
    {
      const string symbol(atoms->getAtomString(OBJECT_CAST(Atom*, nameT)));
      ThreadTableLoc loc = thread_table->LookupName(symbol);
      if (loc == (ThreadTableLoc) -1)
	{
	  return RV_FAIL;
	}
      else
	{
	  return BOOL_TO_RV(unify(argT, heap.newNumber((u_long) loc)));
	}
    }
  else
    {
      Thread *thread;
      DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

      if (! thread->TInfo().SymbolSet())
	{
	  return RV_FAIL;
	}
      
      return BOOL_TO_RV(unify(nameT, atoms->add(thread->TInfo().Symbol().c_str())));
    }
}

// @doc
// @pred thread_set_symbol(Name)
// @mode thread_set_symbol(+) is det
// @type thread_set_symbol(atom)
// @description
// Set the symbolic name for this thread to Name.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_set_symbol(Object *& name_arg)
{
  Object* argN = heap.dereference(name_arg);
 
  if (argN->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (!argN->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  const string new_symbol(atoms->getAtomString(OBJECT_CAST(Atom*, argN)));

  // No change?
  if (TInfo().SymbolSet() && TInfo().Symbol() == new_symbol)
    {
      return RV_SUCCESS;
    }

  if (thread_table->LookupName(new_symbol) == (ThreadTableLoc) -1)
    {
      //
      // Thread with this name doesn't alreay exist.
      //

      // If there was already a symbol for this thread...
      // if (TInfo().SymbolSet())
// 	{
// 	  // Remove previous entry from thread table.
// 	  thread_table->RemoveName(TInfo().Symbol());
// 	}

      // Add the new entry to the thread table
      const bool success =
	thread_table->AddName(new_symbol, TInfo().ID());
      if (success)
	{
	  // Set the new information.
	  TInfo().SetSymbol(new_symbol);
	}
      else
	{
	  PSI_ERROR_RETURN(EV_VALUE, 1);
	}
    }
  else
    {
      // A thread of this name already exists
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }

  return RV_SUCCESS;
}

// @doc
// @pred thread_goal(Goal)
// @mode thread_goal(-) is semidet
// @type thread_goal(gcomp)
// @description
// Get the starting goal of the current thread.
//
// Fails if no starting goal has been specified for the thread.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_goal(Object *& goal_arg)
{
  if (TInfo().Initial())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 0);
    }

  if (TInfo().Goal() == NULL)
    {
      return RV_FAIL;
    }
  else
    {
      goal_arg = TInfo().Goal();

      return RV_SUCCESS;
    }
}
/*
// @doc
// @pred thread_set_goal(Thread, Goal)
// @type thread_set_goal(thread, gcomp)
// @mode thread_set_goal(+, +) is semidet
// @description
// Set the goal of Thread to be Goal, and run the thread.
//
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_set_goal(Object *& thread_arg,
			    Object *& goal_arg)
{
  Object* argT = heap.dereference(thread_arg);
  Object* argG = heap.dereference(goal_arg);

  if (argG->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  // If the thread is an initial thread, we can't alter its goal.
  if (thread->TInfo().Initial())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 2);
    }

  // Must be a new thread for this to work.
  if (thread->Condition() == NEW)
    {
      // Copy the goal onto the target thread's heap.
      thread->TInfo().Goal() =  heap.copyTerm(argG, thread->heap);

      // Set the initial PC to the standard thread entry code.
      // thread->Execute() will wait until this is set before
      // moving into its main loop.
      thread->programCounter =
	predicates->getCode(predicates->lookUp(atoms->add("$thread_start"), 0,
					       atoms, code)
			   ).getPredicate(code);

      if (thread->programCounter == NULL)
	{
	  PSI_ERROR_RETURN(EV_NOT_PERMITTED, 0);
	}

      thread_table->IncLive();

#ifdef DEBUG_MT
      cerr.form("%s Thread %ld, %ld now live\n",
		__FUNCTION__, thread->TInfo().ID(), thread_table->Live());
      //      heap.DisplayTerm(cerr, *atoms, argG);
#endif

      // The thread is now runnable.
      thread->Condition(RUNNABLE);

      // Add it to the run queue
      scheduler->insertThread(this, thread);

      // Away we go!
      return RV_SUCCESS;
    }
  else
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
}
*/
// @doc
// @pred thread_is_thread(Thread)
// @mode thread_is_thread(+) is semidet
// @type thread_is_thread(thread)
// @description
// Succeeds if Thread is a valid thread id and the thread that it refers
// to is an existing thread.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_is_thread(Object *& thread_arg)
{
  Object* argT = heap.dereference(thread_arg);

  Thread *thread;
  const ErrorValue ev = decode_thread(heap, argT, *thread_table, &thread);

  return ev == EV_NO_ERROR ? RV_SUCCESS : RV_FAIL;
}

// @doc
// @pred thread_is_runnable(Thread)
// @type thread_is_runnable(thread)
// @mode thread_is_runnable(+) is semidet
// @description
// Succeeds iff the Thread is runnable.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_is_runnable(Object *& thread_arg)
{
  Object* argT = heap.dereference(thread_arg);	// Thread

  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  return BOOL_TO_RV(thread->Condition() == RUNNABLE);
}

// @doc
// @pred thread_is_suspended(Thread)
// @mode thread_is_suspended(+) is semidet
// @type thread_is_suspended(thread)
// @description
// Succeeds iff the Thread is suspended.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_is_suspended(Object *& thread_id_cell)
{
  Object* thread_id_arg = heap.dereference(thread_id_cell);
  
  Thread *thread;
  DECODE_THREAD_ARG(heap, thread_id_arg, *thread_table, 1, thread);
  
  return BOOL_TO_RV(thread->Condition() == SUSPENDED);
}

// @doc
// @pred thread_tid(Thread)
// @type thread_tid(thread)
// @mode thread_tid(-) is det
// @description
// Thread is the identifier of the current thread.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_tid(Object *& thread_arg)
{
  thread_arg = heap.newNumber((u_long) TInfo().ID());
  
  return RV_SUCCESS;
}

// @internaldoc
// @pred thread_exit
// @mode thread_exit is no-return
// @type thread_exit
// @description
// End execution of the current thread.
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_thread_exit(void)
{
  refTrail.backtrackTo(0);
  DEBUG_ASSERT(Condition() == RUNNABLE);

  // If the thread is the initial thread then exit the application.
  if (TInfo().Initial())
    {
      return RV_HALT;
    }
  Condition(EXITED);

#ifdef DEBUG_MT
  cerr.form("%s %ld\n", __FUNCTION__, TInfo().ID());
#endif

  if (TInfo().SymbolSet())
    {
      // Remove entry from thread table.
      thread_table->RemoveName(TInfo().Symbol());
    }
  return RV_EXIT;
}

// @internaldoc
// @pred signal_thread_exit
// @mode signal_thread_exit is no-return
// @type signal_thread_exit
// @description
// End execution of the signal processing thread.
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_signal_thread_exit(void)
{
  return RV_EXIT;
}

// @doc
// @pred thread_suspend(Thread)
// @mode thread_suspend(+) is det
// @type thread_suspend(thread)
// @description
// No longer supported.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_suspend(Object *& thread_id_cell)
{
#if 0
  Object* thread_id_arg = heap.dereference(thread_id_cell);      // Thread id

  Thread *thread;
  DECODE_THREAD_ARG(heap, thread_id_arg, *thread_table, 1, thread);
  
  SchedRec *sched_rec = new SchedRec(*thread);

  switch (thread->Condition())
    {
    case NEW:
      //
      // A brand new thread needs to be put somewhere.
      //
      scheduler->SuspendedQueue().push_back(sched_rec);
      thread->Condition(SUSPENDED);

      return RV_SUCCESS;
      break;
    case RUNNABLE:
      for (list<SchedRec *>::iterator iter = scheduler->RunQueue().begin();
	   iter != scheduler->RunQueue().end();
	   iter++)
	{
	  SchedRec& sr = **iter;
	  if (&sr.Thr() == thread)
	    {
	      delete *iter;
	      scheduler->RunQueue().erase(iter);

	      break;
	    }
	}

      scheduler->SuspendedQueue().push_back(sched_rec);

      thread->Condition(SUSPENDED);

      //
      // scheduler->RunQueue() has been tinkered with, so it's a good
      // idea to tell it to start from the top.
      //
      scheduler->Status().setRestart();

      return (thread->TInfo().ID() == TInfo().ID()) ?
	RV_TIMESLICE : RV_SUCCESS;
      break;
    case SUSPENDED:
      return RV_SUCCESS;
      break;
    case EXITED:
      return RV_FAIL;
      break;
    }

  DEBUG_ASSERT(false);
  return RV_FAIL;
#else
  PSI_ERROR_RETURN(EV_UNSUPPORTED, 0);
#endif
}

// @doc
// @pred thread_resume(Thread)
// @mode thread_resume(+) is det
// @type thread_resume(thread)
// @description
// No longer supported.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_resume(Object *& thread_id_cell)
{
#if 0
  Object* thread_id_arg = heap.dereference(thread_id_cell);

  Thread *thread;
  DECODE_THREAD_ARG(heap, thread_id_arg, *thread_table, 1, thread);

  SchedRec *sched_rec = new SchedRec(*thread);

  switch (thread->Condition())
    {
    case NEW:
      //
      // A brand new thread needs to be put somewhere.
      //
      scheduler->RunQueue().push_back(sched_rec);
      thread->Condition(RUNNABLE);

      //
      // Sched->RunQueue() has been tinkered with, so it's a good
      // idea to tell it to start from the top.
      //
      scheduler->Status().setRestart();

      return RV_SUCCESS;
      break;
    case SUSPENDED:
      //
      // Move the thread from the suspended queue to the run queue.
      //
      for (list<SchedRec *>::iterator iter = scheduler->SuspendedQueue().begin();
	   iter != scheduler->SuspendedQueue().end();
	   iter++)
	{
	  SchedRec& sr = **iter;
	  if (&sr.Thr() == thread)
	    {
	      delete *iter;
	      scheduler->SuspendedQueue().erase(iter);

	      break;
	    }
	}
	      
      scheduler->RunQueue().push_back(sched_rec);
      thread->Condition(RUNNABLE);

      //
      // Sched->RunQueue() has been tinkered with, so it's a good
      // idea to tell it to start from the top.
      //
      scheduler->Status().setRestart();

      return RV_SUCCESS;
      break;
    case RUNNABLE:
      //
      // No action.
      //
      return RV_SUCCESS;
      break;
    default:
      return RV_FAIL;
      break;
    } 

  DEBUG_ASSERT(false);
  return RV_FAIL;
#else
  PSI_ERROR_RETURN(EV_UNSUPPORTED, 0);
#endif
}

// @user
// @pred thread_wait(Conditions)
// @type thread_wait(list(thread_wait_condition))
// @type thread_wait(+) is det
// @description
// Wait on the given set of conditions. Execution resumes when
// any condition is satisified. If a condition isn't specified,
// its default is used.
//
// The available conditions are:
// 	db(boolean) - Wait on database change. (Default: true.)
//	record_db(boolean) - Wait on record database change. (Default: true.)
//	time(integer) - Wait for the specified number of seconds. 
// @end pred
// @end user
Thread::ReturnValue
Thread::psi_thread_wait(Object *& conditions_arg)
{
  Object* argS = heap.dereference(conditions_arg);
  
  bool db_flag = false;
  bool record_db_flag = false;
  time_t timeout = (time_t) -1;

  DECODE_THREAD_CONDITIONS_ARG(heap, *atoms, argS, 1,
			       db_flag,
			       record_db_flag,
			       timeout);
  if (block_status.isRestarted())
    {
      return RV_SUCCESS;
    }
  else if (db_flag || record_db_flag)
    {
      BlockingWaitObject* bwo = new BlockingWaitObject(this, code, timeout);
      scheduler->blockedQueue().push_back(bwo);
      block_status.setBlocked();
      return RV_BLOCK;
    }
  else 
    {
      BlockingTimeoutObject* bto = new BlockingTimeoutObject(this, timeout);
      scheduler->blockedQueue().push_back(bto);
      block_status.setBlocked();
      return RV_BLOCK;
    }
}

// @internaldoc
// @pred '$thread_defaults'(ThreadSizes)
// @mode '$thread_defaults'(-) is det
// @type '$thread_defaults'(ThreadSizes)
// @description
// Get the current default sizes for the data areas of a newly created thread.
//
// ThreadSizes is described in '$thread_new'/3.
//
// Implemented directly by pseudo-instruction.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_defaults(Object *& sizes_arg)
{
  Structure* str = heap.newStructure(11);
  str->setFunctor(AtomTable::thread_defaults);
  str->setArgument(1, heap.newNumber(thread_options->HeapSize()));
  str->setArgument(2, heap.newNumber(thread_options->ScratchpadSize()));
  str->setArgument(3, heap.newNumber(thread_options->BindingTrailSize()));
  str->setArgument(4, heap.newNumber(thread_options->ObjectTrailSize()));
  str->setArgument(5, heap.newNumber(thread_options->IPTrailSize()));
  str->setArgument(6, heap.newNumber(thread_options->TagTrailSize()));
  str->setArgument(7, heap.newNumber(thread_options->RefTrailSize()));
  str->setArgument(8, heap.newNumber(thread_options->EnvironmentStackSize()));
  str->setArgument(9, heap.newNumber(thread_options->ChoiceStackSize()));
  str->setArgument(10, heap.newNumber(thread_options->NameTableSize()));
  str->setArgument(11, heap.newNumber(thread_options->IPTableSize()));
  
  sizes_arg = str;
  return RV_SUCCESS;
}

// @internaldoc
// @pred '$thread_set_defaults'(ThreadSizes)
// @mode '$thread_set_defaults'(+) is det
// @type '$thread_set_defaults'(thread_sizes)
// @description
// Set the default sizes for the code areas of a newly created thread.
//
// ThreadSizes is described in '$thread_new'/3.
//
// Implemented direcly by pseudo-instruction.
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_thread_set_defaults(Object *& sizes_arg)
{
  Object* argS = heap.dereference(sizes_arg);
  
  int heap_size;
  int scratchpad_size;
  int binding_trail_size;
  int object_trail_size;
  int ip_trail_size;
  int tag_trail_size;
  int ref_trail_size;
  int env_size;
  int choice_size;
  int name_table_size;
  int ip_table_size;
  
  DECODE_DEFAULTS_ARG(heap, argS, 1,
		      heap_size,
		      scratchpad_size,
		      binding_trail_size,
		      object_trail_size,
		      ip_trail_size,
		      tag_trail_size,
		      ref_trail_size,
		      env_size,
		      choice_size,
		      name_table_size,
		      ip_table_size);

  // At this point, all the sizes are >= 0
  thread_options->HeapSize((u_long) heap_size);  
  thread_options->ScratchpadSize((u_long) scratchpad_size);
  thread_options->BindingTrailSize((u_long) binding_trail_size);
  thread_options->ObjectTrailSize((u_long) object_trail_size);
  thread_options->IPTrailSize((u_long) ip_trail_size);
  thread_options->TagTrailSize((u_long) tag_trail_size);
  thread_options->RefTrailSize((u_long) ref_trail_size);
  thread_options->EnvironmentStackSize((u_long) env_size);
  thread_options->ChoiceStackSize((u_long) choice_size);
  thread_options->NameTableSize((u_long) name_table_size);
  thread_options->IPTableSize((u_long) ip_table_size);
  
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_thread_errno(Object *& errno_arg)
{
  errno_arg = heap.newNumber(errno);
  
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_thread_yield(void)
{
  return RV_YIELD;
}

Thread::ReturnValue
Thread::psi_thread_is_initial_thread(void)
{
  return BOOL_TO_RV(TInfo().Initial());
}

//
// Get the list of current thread ID's.
// mode (out)
//
Thread::ReturnValue
Thread::psi_current_threads(Object*& thread_ids)
{
  Object* list = AtomTable::nil;

  for (ThreadTableLoc loc = 0; loc < thread_table->Size(); loc++)
    {
      if (thread_table->LookupID(loc) != NULL)
	{
	  Cons* tmplist = heap.newCons(heap.newNumber(loc), list);
	  list = tmplist;
	}
    }
  thread_ids = list;
  return RV_SUCCESS;
}


// @doc
// @pred threadID_goal(ThreadID, Goal)
// @mode threadID_goal(+, -) is semidet
// @type threadID_goal(thread, gcomp)
// @description
// Get the starting goal of the current thread.
//
// The initial thread returns the atom initial.
// A thread without a goal returns the atom none.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_threadID_goal(Object*& thread_id_cell, Object *& goal_arg)
{
  Object* thread_id_arg = heap.dereference(thread_id_cell); 
  Thread *thread;
  DECODE_THREAD_ARG(heap, thread_id_arg, *thread_table, 1, thread); 
  if (thread->TInfo().Initial())
    {
      goal_arg = atoms->add("initial");
    }

  if (thread->TInfo().Goal() == NULL)
    {
      goal_arg = atoms->add("none");
    }
  else
    {
      goal_arg = thread->TInfo().Goal();
    }
  return RV_SUCCESS;
}                     

// @doc
// @pred thread_exit(Thread)
// @mode thread_exit(+) is det
// @description
// Exit the given thread.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_exit(Object *& thread_id_cell)
{
  Object* thread_id_arg = heap.dereference(thread_id_cell);

  Thread *thread;
  DECODE_THREAD_ARG(heap, thread_id_arg, *thread_table, 1, thread);

  DEBUG_ASSERT(thread->Condition() == RUNNABLE);

  thread->refTrail.backtrackTo(0);
  //
  // If the thread is the initial thread then exit the application.
  if (thread->TInfo().Initial())
    {
      return RV_HALT;
    }

  thread->Condition(EXITED);

#ifdef DEBUG_MT
  cerr.form("%s %ld\n", __FUNCTION__, thread->TInfo().ID());
#endif

  if (thread->TInfo().SymbolSet())
    {
      // Remove entry from thread table.
      thread_table->RemoveName(thread->TInfo().Symbol());
    }
  return RV_SUCCESS;
}

// @doc
// @pred thread_throw(Thread, ThrowPattern)
// @type thread_throw(thread, term)
// @mode thread_throw(+, +) is semidet
// @description
// Throw the pattern in the thread.
//
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_throw(Object *& thread_arg,
			    Object *& throw_arg)
{
  Object* argT = heap.dereference(thread_arg);
  Object* throw_obj = heap.dereference(throw_arg);

  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  // Must be a runnable thread for this to work.
  if (thread->Condition() == RUNNABLE)
    {
      // Copy the goal onto the target thread's heap.

      // Set the initial PC to the standard thread entry code.
      // thread->Execute() will wait until this is set before
      // moving into its main loop.
      thread->programCounter =
	predicates->getCode(predicates->lookUp(atoms->add("throw"), 1,
					       atoms, code)
			   ).getPredicate(code);

      if (thread->programCounter == NULL)
	{
	  PSI_ERROR_RETURN(EV_NOT_PERMITTED, 0);
	}
      thread->XRegs()[0] =  heap.copyTerm(throw_obj, thread->heap);
      scheduler->resetThread(thread);
      return RV_SUCCESS;
    }
  else
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
}


// @doc
// @pred thread_push_goal(Thread, Goal)
// @type thread_push_goal(thread, term)
// @mode thread_push_goal(+, +) is semidet
// @description
// Push call(Goal) to the front of the current goal conjunct of
// the given thread.
//
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_thread_push_goal(Object *& thread_arg,
			    Object *& goal_arg)
{
  Object* argT = heap.dereference(thread_arg);
  Object* goal_obj = heap.dereference(goal_arg);

  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  // Cannot push a goal to yourself.
  if (this == thread)
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 0);
    }
  // Must be a runnable thread for this to work.
  if (thread->Condition() == RUNNABLE)
    {
      // Copy the goal onto the target thread's heap.
      Object* goal = heap.copyTerm(goal_obj, thread->heap);
      
      Object* saved_goal;
      if (!thread->getCurrentGoal(saved_goal))
	{
	  PSI_ERROR_RETURN(EV_NOT_PERMITTED, 0);
	}
      thread->programCounter =
	predicates->getCode(predicates->lookUp(atoms->add("$handle_push_goal"), 2, atoms, code)).getPredicate(code);

      if (thread->programCounter == NULL)
	{
	  PSI_ERROR_RETURN(EV_NOT_PERMITTED, 0);
	}
      thread->XRegs()[0] = goal;
      thread->XRegs()[1] = saved_goal;
      scheduler->resetThread(thread);
      return RV_SUCCESS;
    }
  else
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
}




