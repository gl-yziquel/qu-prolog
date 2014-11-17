 // statistics.cc - Return statistical information.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: statistics.cc,v 1.5 2005/03/08 00:35:14 qp Exp $

#include <limits.h>
#ifdef WIN32
        #include <io.h>
        #include <time.h>
#else
        #include <unistd.h>
        #include <sys/times.h>
        #include <time.h>
#endif

#include "config.h"

#include "atom_table.h"
#include "code.h"
#include "thread_decode.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern Code *code;
extern PredTab *predicates;

#ifndef	CLK_TCK
#define	CLK_TCK	sysconf(_SC_CLK_TCK)
#endif	// CLK_TCK

//
// psi_cputime(var)
// Get the time in milliseconds since the system was
// started up.
//
Thread::ReturnValue
Thread::psi_cputime(Object *& object1)
{
#ifdef WIN32
  clock_t msec;
  msec = clock() * 1000 / CLOCKS_PER_SEC;
#else
  struct        tms     usage;
  int32 msec;
  times(&usage);
  msec = (usage.tms_utime + usage.tms_stime) * 1000 / CLK_TCK;
#endif
  object1 = heap.newInteger(msec);
  return RV_SUCCESS;
}

//
// Return the amount of space used and available in a stack.
//
Thread::ReturnValue
Thread::return_stack_stat(const FixedSizeStack& stack, Object *& object1) 
{
  word32  size = stack.sizeOfStack();

  Structure* stats = heap.newStructure(3);
  stats->setFunctor(atoms->add("stat"));
  stats->setArgument(1, heap.newInteger(size));
  stats->setArgument(2, heap.newInteger(stack.allocatedSize() - size));
  stats->setArgument(3, heap.newInteger(stack.maxUsage()));

  object1 = stats;
 
  return RV_SUCCESS;
}
//
// Return the amount of space used and available in the trail.
//
Thread::ReturnValue
Thread::return_stack_stat(const BindingTrail& trail, Object *& object1) 
{
  word32  used = trail.usedTrail();

  Structure* stats = heap.newStructure(3);
  stats->setFunctor(atoms->add("stat"));
  stats->setArgument(1, heap.newInteger(used));
  stats->setArgument(2, heap.newInteger(trail.allocatedSize() - used));
  stats->setArgument(3, heap.newInteger(trail.maxUsage()));

  object1 = stats;
 
  return RV_SUCCESS;
}
//
// Return the amount of space used and available in the trail.
//
Thread::ReturnValue
Thread::return_stack_stat(const OtherTrail& trail, Object *& object1) 
{
  word32  used = trail.usedTrail();

  Structure* stats = heap.newStructure(3);
  stats->setFunctor(atoms->add("stat"));
  stats->setArgument(1, heap.newInteger(used));
  stats->setArgument(2, heap.newInteger(trail.allocatedSize() - used));
  stats->setArgument(3, heap.newInteger(trail.maxUsage()));

  object1 = stats;
 
  return RV_SUCCESS;
}

//
// Return the amount of space used and available in a heap.
//
Thread::ReturnValue
Thread::return_heap_stat(Heap& hp, Object *& object1) 
{
  word32  size = static_cast<word32>(hp.getTop() - hp.getBase());

  Structure* stats = heap.newStructure(3);
  stats->setFunctor(atoms->add("stat"));
  stats->setArgument(1, heap.newInteger(size));
  stats->setArgument(2, heap.newInteger(hp.allocatedSize() - size));
  stats->setArgument(3, heap.newInteger(hp.maxUsage()));

  object1 = stats;
 
  return RV_SUCCESS;
}

//
// Return the amount of space used and available in the code area.
//
Thread::ReturnValue
Thread::return_code_stat(Code& code, Object *& object1, 
			  Object *& object2, Object *& object3)
{
  word32  size = static_cast<word32>(code.getTop() - code.getBase());

  object1 = heap.newInteger(size);
  object2 = heap.newInteger(code.allocatedSize() - size);
  object3 = heap.newInteger(size);
 
  return RV_SUCCESS;
}

//
// Return the amount of space used and available in a hash table.
//
Thread::ReturnValue
Thread::return_table_stat(FixedSizeHashTable& table, 
			  Object *& object1)
{
  word32 size = table.sizeOfTable();

  Structure* stats = heap.newStructure(2);
  stats->setFunctor(atoms->add("stat"));
  stats->setArgument(1, heap.newInteger(size));
  stats->setArgument(2, heap.newInteger(table.allocatedSize() - size));

  object1 = stats;

  return RV_SUCCESS;
}

//
// psi_stat_choice(thread, var, var)
// Return the amount of space used and available, and maximum usage
// in choice point stack.
//
Thread::ReturnValue
Thread::psi_stat_choice(Object *& object1, Object *& object2, Object *& object3)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  object3 = AtomTable::success;
  return(return_stack_stat(thread->TheChoiceStack(), object2));
}

//
// psi_stat_global(var, var, var)
// Return the amount of space used and available, and maximum usage in heap.
//
Thread::ReturnValue
Thread::psi_stat_global(Object *& object1, Object *& object2, Object *& object3)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  object3 = AtomTable::success;
  return(return_heap_stat(thread->TheHeap(), object2));
}

//
// psi_stat_local(var, var, var)
// Return the amount of space used and available, and maximum usage
// in environment stack.
//
Thread::ReturnValue
Thread::psi_stat_local(Object *& object1, Object *& object2, Object *& object3)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  object3 = AtomTable::success;
  return(return_stack_stat(thread->EnvStack(), object2));
}

//
// psi_stat_binding_trail(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the binding trail.
//
Thread::ReturnValue
Thread::psi_stat_binding_trail(Object *& object1, Object *& object2, Object *& object3)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  object3 = AtomTable::success;
  return(return_stack_stat(thread->TheBindingTrail(), object2));
}

//
// psi_stat_other_trail(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the object trail.
//
Thread::ReturnValue
Thread::psi_stat_other_trail(Object *& object1, Object *& object2, Object *& object3)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  object3 = AtomTable::success;
  return(return_stack_stat(thread->TheOtherTrail(), object2));
}


//
// psi_stat_code(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the code area.
//
Thread::ReturnValue
Thread::psi_stat_code(Object *& object1, Object *& object2, Object *& object3)
{
  return(return_code_stat(*code, object1, object2, object3));
}

//
// psi_stat_string(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the string table.
//
Thread::ReturnValue
Thread::psi_stat_string(Object *& object1, Object *& object2, Object *& object3)
{
  object1 = AtomTable::success;
  object3 = AtomTable::success;
  return(return_stack_stat(atoms->getStringTable(), object2));
}

//
// psi_stat_ip_table(var, var)
// Return the amount of space used and availabe in the IP table.
//
Thread::ReturnValue
Thread::psi_stat_ip_table(Object *& object1, Object *& object2)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  return(return_table_stat(thread->getIPTable(), object2));
}

//
// psi_stat_name(var, var)
// Return the amount of space used and availabe in the name table.
//
Thread::ReturnValue
Thread::psi_stat_name(Object *& object1, Object *& object2)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  return(return_table_stat(thread->getNames(), object2));
}

//
// psi_stat_atom(var, var)
// Return the amount of space used and availabe in the atom table.
//
Thread::ReturnValue
Thread::psi_stat_atom(Object *& object1, Object *& object2)
{
  object2 = AtomTable::success;
  return(return_table_stat(*atoms, object1));
}
//
// psi_stat_scratchpad(thread, var)
// Return the space info for the scratchpad.
//
Thread::ReturnValue
Thread::psi_stat_scratchpad(Object *& object1, Object *& object2, 
			    Object *& object3)
{
  Object* argT = heap.dereference(object1);
  Thread *thread;
  DECODE_THREAD_ARG(heap, argT, *thread_table, 1, thread);

  object3 = AtomTable::success;
  return(return_heap_stat(thread->TheScratchpad(), object2));
}
//
// psi_stat_predicate(var, var)
// Return the amount of space used and availabe in the predicate table.
//
Thread::ReturnValue
Thread::psi_stat_predicate(Object *& object1, Object *& object2)
{
  object2 = AtomTable::success;
  return(return_table_stat(*predicates, object1));
}

//
// psi_stat_memory(var)
// Return the total amount of space allocated by the operating system.
//
Thread::ReturnValue
Thread::psi_stat_memory(Object *& object1)
{
#if 0
  object1 = heap.newInteger((char *)(sbrk(0)) - BeforeAllocation);
#else	// 0
  object1 = heap.newInteger(0);
#endif	// 0

  return RV_SUCCESS;
}

//
// psi_stat_program(var)
// Return the amount of space used by code area and various tables.
//
Thread::ReturnValue
Thread::psi_stat_program(Object *& object1)
{
  object1 = heap.newInteger(code->size() + atoms->size() * Atom::size() 
			   + predicates->size() * sizeof(PredEntry));

  return RV_SUCCESS;
}









