// gc_escapes.cc - Garbage collector.
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
// $Id: gc_escapes.cc,v 1.21 2006/01/31 23:17:50 qp Exp $

#include <stdlib.h>

#include "global.h"
#include "gc.h"
#include "thread_qp.h"
 
#ifdef QP_DEBUG


bool 
Thread::check_trail()
{
  return (bindingTrail.check(heap) &&
	  otherTrail.check(heap));
}

bool 
Thread::check_ips()
{
  for (int i = 0; i < (int)(ipTable.allocatedSize()); i++)
    {
      if (! ipTable.getEntry(i).isEmpty())
	{
  if (ipTable.getEntry(i).getValue() == NULL || 
      !heap.isHeapPtr(reinterpret_cast<heapobject*>(ipTable.getEntry(i).getValue()))) continue;
	  if (!check_term(ipTable.getEntry(i).getValue())) return false;
	}
    }
  return true;
}

bool 
Thread::check_name()
{
  for (int i = 0; i < (int)(names.allocatedSize()); i++)
    {
      if (! names.getEntry(i).isEmpty())
	{	 
	  if (names.getEntry(i).getValue() == NULL || 
	      !heap.isHeapPtr(reinterpret_cast<heapobject*>(names.getEntry(i).getValue()))) continue;
	  if (!check_term(names.getEntry(i).getValue())) return false;
	}
    }
  return true;
}

bool 
Thread::check_heap2(Heap& heap)
{
  for (heapobject* ptr = heap.getBase(); ptr < heap.getTop(); )
    {
      Object* term =  reinterpret_cast<Object*>(ptr);
      if (!check_term(term)) return false;
      ptr += term->size_dispatch();
    }

  assert(check_ips());
  assert(check_name());
  return check_trail();
}

//
// Check heap for correct pointers
//
bool Thread::check_heap(Heap& heap, AtomTable* atoms, GCBits& gcbits)
{
  heapobject* atombase = reinterpret_cast<heapobject*>(atoms->getAddress(0));
  heapobject* atomtop = reinterpret_cast<heapobject*>(atoms->getAddress(atoms->size()));
  for (heapobject* ptr = heap.getBase(); ptr < heap.getTop(); )
    {
      
      int size = reinterpret_cast<Object*>(ptr)->size_dispatch();
      Object* var = reinterpret_cast<Object*>(ptr);
      ptr++;
      for (int i = 1; i < size; i++)
        {
	  if (var->isLong())
	    {
	      ptr++;
	      continue;
	    }
	  if (var->isDouble())
	    {
	      ptr ++;
	      continue;
	    }
	  if (var->isAnyVariable() && (i == 2))
	    {
	      ptr++;
	      continue;
	    }
	  if (var->isSubstitutionBlock() && (*ptr == 0))
	    {
	      ptr++;
	      continue;
	    }
	  
          heapobject* ptrval = reinterpret_cast<heapobject*>(*ptr);
          if (((ptrval < heap.getBase()) || (ptrval > heap.getTop())) 
              && ((ptrval < atombase) || (ptrval > atomtop)))
            {
 		      
              cerr << hex << (word32)(ptr - i) << " size = " << size << endl;
              for (int j = 0; j <= i; j++)
                {
                  cerr << hex << (word32)(ptr - i + j)  << " : " << (word32)(*(ptr -i + j)) << endl;
                }
              cerr << dec << endl;
	      reinterpret_cast<Object*>(ptr - i)->printMe_dispatch(*atoms);
	      cerr << endl << "PREVIOUS" << endl;
	      for (int j = 0; j < 20; j++)
		{
		  cerr << hex << (word32)(ptr - 20 + j)  << " : " << (word32)(*(ptr -20 + j)) << dec << endl;
		}
              return false;
            }
          ptr++;
        }
    }
  for (int i = 0; i < (int)(ipTable.allocatedSize()); i++)
    {
      if (! ipTable.getEntry(i).isEmpty())
        {
          Object* o = ipTable.getEntry(i).getValue();
          heapobject* h = reinterpret_cast<heapobject*>(o);
          if (((h < heap.getBase()) || (h > heap.getTop()))
              && ((h < atombase) || (h > atomtop)))
            {
              return false;
            }
        }
    }
  
  return true;
}

bool check_heap_marked(Heap& heap, GCBits& gcbits)
{
  int index = 0;
  heapobject* hptr = heap.getBase();
  while (hptr < heap.getTop())
    {
      Object* term = reinterpret_cast<Object*>(hptr);
      int size = term->size_dispatch();
      if (gcbits.isSet(index))
	{
	  if (!term->isNumber())
	    {
	      for (int i = 1; i < size; i++)
		{
		  heapobject* argp = reinterpret_cast<heapobject*>(*hptr);
		  if ((argp != NULL) && heap.isHeapPtr(argp))
		    {
		      if (!gcbits.isSet(argp - heap.getBase() )) 
			{
			  cerr << "xxx" << endl;
			  return false;
			}
		    }
		}
	    }
	}
      index++;
      for (int i = 1; i < size; i++)
	{
	  if (gcbits.isSet(index))
	    {
	      cerr << "val = " << (u_int)(*hptr) << endl;
	      cerr << "val+1 = " << (u_int)(*(hptr+1)) << endl;
	      cerr << "heap offset = " << (hptr - heap.getBase());
	      cerr << "  index = " << index << endl;
	      return false;
	    }
	  index++;
	}
      hptr += size;
    }
  return true;
}

#endif // DEBUG

void
Thread::gc_mark_registers(word32 arity)
{
  for (u_int i = 0; i < arity; i++)
    {
      assert(!X[i]->isSubstitutionBlock());
      gc_mark_pointer(X[i], heap, gcstack, gcbits);
    }
  for (u_int i = arity; i < NUMBER_X_REGISTERS; i++)
    {
      X[i] = AtomTable::nil;
    }
}

void 
Thread::gc_mark_environments(EnvLoc env)
{
  while (true)
    {
      if (envStack.gc_isMarkedEnv(env))
	{
	  return;
	}
      for (int i = (int)(envStack.getNumYRegs(env))-1; i >= 0; i--)
	{
	  assert(!envStack.yReg(env, i)->isSubstitutionBlock());
	  gc_mark_pointer(envStack.yReg(env, i), heap, gcstack, gcbits);
	}
      envStack.gc_markEnv(env);
      if (env == envStack.firstEnv())
	{
	  return;
	}
      env = envStack.getPreviousEnv(env);
    }
}

void
Thread::gc_mark_choicepoints(ChoiceLoc choiceloc)
{
  while (true)
    { 
      gc_mark_environments(choiceStack.currentEnv(choiceloc));
      for (int i =  (int)(choiceStack.getNumArgs(choiceloc))-1; i >= 0; i--)
	{
	  assert(!choiceStack.getXreg(choiceloc, i)->isSubstitutionBlock());
	  gc_mark_pointer(choiceStack.getXreg(choiceloc, i), 
			  heap, gcstack, gcbits);
	}
      if (choiceloc == choiceStack.firstChoice())
	{
	  return;
	}
      choiceloc = choiceStack.previousChoicePoint(choiceloc);
    }
}

void
Thread::gc_mark_trail()
{
  otherTrail.gc_mark(heap, gcstack, gcbits);
}

void
Thread::gc_mark_ips()
{
  for (int i = 0; i < (int)(ipTable.allocatedSize()); i++)
    {
      if (! ipTable.getEntry(i).isEmpty())
	{
	  assert(!ipTable.getEntry(i).getValue()->isSubstitutionBlock());
	  gc_mark_pointer(ipTable.getEntry(i).getValue(), 
			  heap, gcstack, gcbits);
	}
    }
}

void 
Thread:: gc_mark_names()
{
  for (int i = 0; i < (int)(names.allocatedSize()); i++)
    {
      if (! names.getEntry(i).isEmpty())
	{
	  assert(!names.getEntry(i).getValue()->isSubstitutionBlock());
	  gc_mark_pointer(names.getEntry(i).getValue(), 
			  heap, gcstack, gcbits);
	}
    }
}



void 
Thread::gc_marking_phase(word32 arity)
{
  assert(check_heap_marked(heap, gcbits));
  Object* tmp = heap.newShort(0);
  gcbits.set((heapobject*)tmp - heap.getBase());
  assert(check_heap_marked(heap, gcbits));
  gc_mark_registers(arity);
  assert(check_heap_marked(heap, gcbits));
  gc_mark_environments(currentEnvironment);
  assert(check_heap_marked(heap, gcbits));
  gc_mark_choicepoints(currentChoicePoint);
  assert(check_heap_marked(heap, gcbits));
  gc_mark_ips();
  assert(check_heap_marked(heap, gcbits));
  gc_mark_names();
  assert(check_heap_marked(heap, gcbits));
  gc_mark_trail();
  assert(check_heap_marked(heap, gcbits));
}

void
Thread::gc_sweep_registers(word32 arity)
{
  for (int i = 0; i < (int)(arity); i++)
    {
      if (heap.isHeapPtr(reinterpret_cast<heapobject*>(X[i])))
	{
	  threadGC(reinterpret_cast<heapobject*>(X+i));
	}
    }
}

void
Thread::gc_sweep_trail(void)
{
  bindingTrail.gc_sweep(heap, gcbits);
  otherTrail.gc_sweep(heap, gcbits);
}

void
Thread::gc_sweep_names(void)
{
  int last = heap.getTop() - heap.getBase();
  for (int i = 0; i < (int)(names.allocatedSize()); i++)
    {
      if (! names.getEntry(i).isEmpty())
	{
	  int index = reinterpret_cast<heapobject*>(names.getEntry(i).getValue()) - heap.getBase();
	  if ((index >= 0) && (index < last) && gcbits.isSet(index))
	    {
	      threadGC(reinterpret_cast<heapobject*>(names.getEntry(i).getValueAddr()));
	    }
	  else
	    {
	     *(names.getEntry(i).getValueAddr()) = 0;
	    }
	}
    }
}

void
Thread::gc_sweep_ips(void)
{
  for (int i = 0; i < (int)(ipTable.allocatedSize()); i++)
    {
      if (! ipTable.getEntry(i).isEmpty())
	{
	  threadGC(reinterpret_cast<heapobject*>(ipTable.getEntry(i).getValueAddr()));
	}
    }
}

void
Thread::gc_sweep_environments(EnvLoc env)
{
  while (true)
    {
      if (!envStack.gc_isMarkedEnv(env))
	{
	  return;
	}
      envStack.gc_unmarkEnv(env);
      for (int i = envStack.getNumYRegs(env)-1; i >= 0; i--)
	{
	  if (heap.isHeapPtr(reinterpret_cast<heapobject*>(envStack.yReg(env,i))))
	    {
	      assert(gcbits.isSet(reinterpret_cast<heapobject*>(envStack.yReg(env,i)) - heap.getBase()));
	      threadGC(envStack.yRegAddr(env,i));
	    }
	}
      if (env == envStack.firstEnv())
	{
	  return;
	}
      env = envStack.getPreviousEnv(env);
    }
}

void
Thread::gc_sweep_choicepoints(ChoiceLoc choiceloc)
{
  while (true)
    {
      gc_sweep_environments(choiceStack.currentEnv(choiceloc));
      for (int i = choiceStack.getNumArgs(choiceloc)-1; i >= 0; i--)
	{
	  if (heap.isHeapPtr(reinterpret_cast<heapobject*>(choiceStack.getXreg(choiceloc, i))))
	    {
	      assert(gcbits.isSet(reinterpret_cast<heapobject*>(choiceStack.getXreg(choiceloc, i)) - heap.getBase()));
	      threadGC(choiceStack.getXregAddr(choiceloc, i));
	    }
	}

      if (!gcbits.isSet(choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop() - heap.getBase()))
	{
	  int32 size = static_cast<int32>(reinterpret_cast<Object*>(choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop())->size_dispatch());

          heapobject* ptr = choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop();

	  gcbits.set(ptr - heap.getBase());
	  for (int i = 0; i < size; i++)
	    {
	      *(ptr+i) = Short::Zero;
	    }
	}
      threadGC(choiceStack.getHeapAndTrailsState(choiceloc).getSavedTopAddr()); 

      if (choiceloc == choiceStack.firstChoice())
	{
	  return;
	}
      choiceloc = choiceStack.previousChoicePoint(choiceloc);
    }
}


void
Thread::gc_compaction_phase(word32 arity)
{
  gc_sweep_registers(arity);
  gc_sweep_trail();
  gc_sweep_names();
  gc_sweep_ips(); 
  gc_sweep_environments(currentEnvironment);
  gc_sweep_choicepoints(currentChoicePoint);
  if (!gcbits.isSet(heap.getSavedTop() - heap.getBase()))
    {
	  *(heap.getSavedTop()) = Short::Zero;
	  gcbits.set(heap.getSavedTop() - heap.getBase());
    }
  threadGC(heap.getSavedTopAddr());
  update_forward_pointers(heap, gcbits);
  update_backward_pointers(heap, gcbits);
}

#ifdef QP_DEBUG
void
Thread::dump_choices(ChoiceLoc choiceloc)
{
  while (true)
    {
      HeapAndTrailsChoice htc = choiceStack.getHeapAndTrailsState(choiceloc);
      cerr << "Choice [" << choiceloc << "]" << endl;
      cerr << "SavedTOS = " << hex << (word32)(htc.getSavedTop()) << dec << endl;
      envStack.printMe(*atoms, choiceStack.currentEnv(choiceloc));
      cerr << "Choice X regs" << endl;
      for (int i = choiceStack.getNumArgs(choiceloc)-1; i >= 0; i--)
	{
	  cerr << "X[" << i << "]" << endl;
	  choiceStack.getXreg(choiceloc, i)->printMe_dispatch(*atoms);
	  cerr << endl;
	}
      if (choiceloc == choiceStack.firstChoice())
	{
	  return;
	}
      choiceloc = choiceStack.previousChoicePoint(choiceloc);
    }
}

void
Thread::dump_areas(word32 arity)
{
  cerr << "=========== The current X regs =========" << endl;
  for (int i = 0; i < (int)(arity); i++)
    {
      cerr << "X[" << i << "] :" << endl;
      X[i]->printMe_dispatch(*atoms);
      cerr << endl;
    }

  cerr << endl << "=========== The Env stack ==========" << endl;
  envStack.printMe(*atoms, currentEnvironment);

  cerr << endl << "=========== The CP stack  ==========" << endl;
  dump_choices(currentChoicePoint);

#if 0
  cerr << endl << "=========== The binding trail ======" << endl;
  bindingTrail.printMe(*atoms);

  cerr << endl << "=========== The IP trail ===========" << endl;
  ipTrail.printMe(*atoms);

  cerr << endl << "=========== The object trail =======" << endl;
  objectTrail.printMe(*atoms);

  cerr << endl << "=========== The tag trail ==========" << endl;
  tagTrail.printMe(*atoms);
#endif
  cerr << endl << "=========== The name table =========" << endl;
  names.printMe(*atoms);

  cerr << endl << "=========== The IP table ===========" << endl;
  ipTable.printMe(*atoms);
  cerr << endl << "=========== The heap ===============" << endl;
  cerr << "savedTOS = " << hex << (word32)(heap.getSavedTop()) << dec << endl;
heap.printMe(*atoms);
}


#endif //DEBUG

void 
Thread::gc(word32 arity)
{
  status.resetDoGC();

  bool print_gc_stats = (getenv("QP_GC") != NULL);

  if (print_gc_stats)
    {
      cerr << "GC START - heap size = " 
         << (word32)(heap.getTop() - heap.getBase()) << endl;
    }

  assert(check_heap(heap, atoms, gcbits));
  //  assert(check_env(currentEnvironment));
  // assert(check_heap2(heap));
  assert(otherTrail.check(heap));
  gc_marking_phase(arity);

  assert(otherTrail.check(heap));
  assert(check_heap(heap, atoms, gcbits));
  gc_compaction_phase(arity);

  assert(check_heap(heap, atoms, gcbits));
  //assert(check_env(currentEnvironment));
  assert(check_heap2(heap));


  if (print_gc_stats)
    {
      cerr << "GC END   - heap size = " 
           << (word32)(heap.getTop() - heap.getBase()) << endl;
    }

  if (heap.doGarbageCollection())
    {
      Fatal(__FUNCTION__, "Garbage collection did not recover enough space");
    }
}

Thread::ReturnValue
Thread::psi_gc(void)
{
  status.setDoGC();
  return RV_SUCCESS;
}



