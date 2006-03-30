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
Thread::check_env(EnvLoc env)
{
  while ((env != envStack.firstEnv()))
    {
      assert(!envStack.gc_isMarkedEnv(env) );
      for (int i = (int)(envStack.getNumYRegs(env))-1; i >= 0; i--)
	{
	  if ( envStack.yReg(env, i) == NULL || 
	       !heap.isHeapPtr(reinterpret_cast<heapobject*>(envStack.yReg(env, i)))) continue;
	  if (!check_term(envStack.yReg(env, i))) 
	    {
	      Object* start = envStack.yReg(env, i);
	      cerr << "CE = " << currentEnvironment << " env = " << env << endl;
	      cerr << " i = " << i << " loc = " << (word32)start << " offset = "<< reinterpret_cast<heapobject*>(start) - heap.getBase() << endl;
for (int i = -10; i < 10; i++)
cerr << (word32)((reinterpret_cast<heapobject*>(start) + i)) << " : " << (word32)(*(reinterpret_cast<heapobject*>(start) + i))  << endl;
cerr << endl;

	      return false;
	    }
	}
      env = envStack.getPreviousEnv(env);
    }
  return true;
}

bool 
Thread::check_choice(ChoiceLoc choiceloc)
{
  while (true)
    { 
      if (!check_env(choiceStack.currentEnv(choiceloc))) return false;
      for (int i =  (int)(choiceStack.getNumArgs(choiceloc))-1; i >= 0; i--)
	{
	    if ( choiceStack.getXreg(choiceloc, i)== NULL || 
		!heap.isHeapPtr(reinterpret_cast<heapobject*>(choiceStack.getXreg(choiceloc, i)))) continue;
	  if (!check_term(choiceStack.getXreg(choiceloc, i))) return false;
	}
      if (choiceloc == choiceStack.firstChoice())
	{
	  return true;
	}
      choiceloc = choiceStack.previousChoicePoint(choiceloc);
    }
  return true;
}

bool 
Thread::check_ip_trail()
{
  for (int i = 0; i < (int)(ipTrail.getTop()); i++)
    {
      UpdatableObject uobj = ipTrail.getEntry(i);
      if (uobj.getOldValue() == NULL || 
	  !heap.isHeapPtr(reinterpret_cast<heapobject*>(uobj.getOldValue()))) continue;
      if (!check_term(uobj.getOldValue())) return false;;
    }
  return true;
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
Thread::check_obj_trail()
{
  for (int i = 0; i < (int)(objectTrail.getTop()); i++)
    {
      UpdatableObject uobj = objectTrail.getEntry(i);
      if (!heap.isHeapPtr(uobj.getAddress()))
        {
          // Must be  a name table entry
          continue;
        }
      // It's a heap pointer
      if (heap.isHeapPtr(reinterpret_cast<heapobject*>(uobj.getOldValue())))
	{
	  if (!check_term(uobj.getOldValue())) return false;
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

  assert(check_env(currentEnvironment));
  assert(check_choice(currentChoicePoint));
  assert(check_ip_trail());
  assert(check_ips());
  assert(check_name());
  assert(check_obj_trail());
  return true;

}

//
// Check heap for correct pointers
//
bool Thread::check_heap(Heap& heap, AtomTable* atoms)
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
          heapobject* ptrval = reinterpret_cast<heapobject*>(*ptr);
          if (((ptrval < heap.getBase()) || (ptrval > heap.getTop())) 
              && ((ptrval < atombase) || (ptrval > atomtop)))
            {
              if (var->isLong())
                {
                  ptr++;
                  continue;
                }
              if (var->isDouble())
                {
                  ptr += 2;
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
		      
              cerr << hex << (word32)(ptr - i) << endl;
              for (int j = 0; j < size; j++)
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

#endif // DEBUG

void
Thread::gc_mark_registers(word32 arity, int32& total_marked)
{
  for (u_int i = 0; i < arity; i++)
    {
      gc_mark_pointer(X[i], total_marked, heap);
    }
  for (u_int i = arity; i < NUMBER_X_REGISTERS; i++)
    {
      X[i] = AtomTable::nil;
    }
}

void 
Thread::gc_mark_environments(EnvLoc env, int32& total_marked)
{
  while (true)
    {
      if (envStack.gc_isMarkedEnv(env))
	{
	  return;
	}
      for (int i = (int)(envStack.getNumYRegs(env))-1; i >= 0; i--)
	{
	  gc_mark_pointer(envStack.yReg(env, i), total_marked, heap);
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
Thread::gc_mark_choicepoints(ChoiceLoc choiceloc, int32& total_marked)
{
  while (true)
    { 
      gc_mark_environments(choiceStack.currentEnv(choiceloc), total_marked);
      for (int i =  (int)(choiceStack.getNumArgs(choiceloc))-1; i >= 0; i--)
	{
	  gc_mark_pointer(choiceStack.getXreg(choiceloc, i), 
			  total_marked, heap);
	}
      if (choiceloc == choiceStack.firstChoice())
	{
	  return;
	}
      choiceloc = choiceStack.previousChoicePoint(choiceloc);
    }
}

void
Thread::gc_mark_ip_trail(int32& total_marked)
{
  for (int i = 0; i < (int)(ipTrail.getTop()); i++)
    {
      UpdatableObject uobj = ipTrail.getEntry(i);
      gc_mark_pointer(uobj.getOldValue(), total_marked, heap);
    }
}

void
Thread::gc_mark_ips(int32& total_marked)
{
  for (int i = 0; i < (int)(ipTable.allocatedSize()); i++)
    {
      if (! ipTable.getEntry(i).isEmpty())
	{
	  gc_mark_pointer(ipTable.getEntry(i).getValue(), total_marked, heap);
	}
    }
}

void 
Thread:: gc_mark_names(int32& total_marked)
{
  for (int i = 0; i < (int)(names.allocatedSize()); i++)
    {
      if (! names.getEntry(i).isEmpty())
	{
	  gc_mark_pointer(names.getEntry(i).getValue(), total_marked, heap);
	}
    }
}

void
Thread::gc_mark_object_trail(int32& total_marked)
{
  for (int i = 0; i < (int)(objectTrail.getTop()); i++)
    {
      UpdatableObject uobj = objectTrail.getEntry(i);
      if (!heap.isHeapPtr(uobj.getAddress()))
        {
          // Must be  a name table entry
          continue;
        }
  assert(uobj.getAddress() < heap.getTop());
      // It's a heap pointer
      if (reinterpret_cast<Object*>(uobj.getAddress())->gc_isMarked())
        {
          if (heap.isHeapPtr(reinterpret_cast<heapobject*>(uobj.getOldValue()))
               && !uobj.getOldValue()->gc_isMarked())
            {
  assert(reinterpret_cast<heapobject*>(uobj.getOldValue()) < heap.getTop());
              gc_mark_pointer(uobj.getOldValue(), total_marked, heap);
            }
        }
    }
}

void 
Thread::gc_marking_phase(word32 arity, int32& total_marked)
{
  Object* tmp = heap.newShort(0);
  tmp->gc_mark();
  total_marked++;
  gc_mark_registers(arity, total_marked);
  gc_mark_environments(currentEnvironment, total_marked);
  //assert(check_env(currentEnvironment));
  gc_mark_choicepoints(currentChoicePoint, total_marked);
  gc_mark_ip_trail(total_marked);
  gc_mark_ips(total_marked);
  gc_mark_names(total_marked);
  gc_mark_object_trail(total_marked);
}

void
Thread::gc_sweep_registers(word32 arity)
{
  for (int i = 0; i < (int)(arity); i++)
    {
      if (heap.isHeapPtr(reinterpret_cast<heapobject*>(X[i])))
	{
  assert(reinterpret_cast<heapobject*>(X[i]) < heap.getTop());
	  into_relocation_chain(reinterpret_cast<heapobject*>(X[i]),
				reinterpret_cast<heapobject*>(X+i));
	}
    }
}

void
Thread::gc_sweep_binding_trail(void)
{
  for (int i = (int)(bindingTrail.getTop())-1; i >= 0; i--)
    {
      assert(heap.isHeapPtr(bindingTrail.getEntry(i)));
  assert(bindingTrail.getEntry(i) < heap.getTop());
      assert(reinterpret_cast<Object*>(bindingTrail.getEntry(i))->gc_isMarked());
      into_relocation_chain(bindingTrail.getEntry(i),
			    reinterpret_cast<heapobject*>(bindingTrail.fetchAddr(i)));
    }
}

void
Thread::gc_sweep_tag_trail(void)
{
  for (int i = (int)(tagTrail.getTop())-1; i >= 0; i--)
    {
       if (tagTrail.getEntry(i).getAddress() != NULL && reinterpret_cast<Object*>(tagTrail.getEntry(i).getAddress())->gc_isMarked())
	{
	  into_relocation_chain(tagTrail.getEntry(i).getAddress(), tagTrail.getEntry(i).getAddressAddr());
	}
      else
	{
	  tagTrail.getEntry(i).setAddress(NULL);
	}
    }
}

void
Thread::gc_sweep_object_trail(void)
{
  for (int i = (int)(objectTrail.getTop())-1; i >= 0; i--)
    {
      if (!heap.isHeapPtr(objectTrail.getEntry(i).getAddress()))
	{
	  // Must be  a name table entry
	  continue;
	}
  assert(objectTrail.getEntry(i).getAddress() < heap.getTop());
      // It's a heap pointer     
      if (reinterpret_cast<Object*>(objectTrail.getEntry(i).getAddress())->gc_isMarked())
	{
	  into_relocation_chain(objectTrail.getEntry(i).getAddress(), 
				objectTrail.getEntry(i).getAddressAddr());
	  if (heap.isHeapPtr(reinterpret_cast<heapobject*>(objectTrail.getEntry(i).getOldValue())))
	    {
  assert(reinterpret_cast<heapobject*>(objectTrail.getEntry(i).getOldValue()) < heap.getTop());
	      assert(objectTrail.getEntry(i).getOldValue()->gc_isMarked());
	      into_relocation_chain(reinterpret_cast<heapobject*>(objectTrail.getEntry(i).getOldValue()), objectTrail.getEntry(i).getOldVAddr());
	    }
	}
      else
	{
	  objectTrail.getEntry(i).setAddress(NULL);
	  objectTrail.getEntry(i).setOldValue(NULL);
	}
    }
}

void
Thread::gc_sweep_ip_trail(void)
{
  for (int i = (int)(ipTrail.getTop())-1; i >= 0; i--)
    {
      if(heap.isHeapPtr(ipTrail.getEntry(i).getAddress()))
        {
          assert(ipTrail.getEntry(i).getAddress() < heap.getTop());
          assert(reinterpret_cast<Object*>(ipTrail.getEntry(i).getAddress())->gc_isMarked());
          into_relocation_chain(ipTrail.getEntry(i).getAddress(), 
			        ipTrail.getEntry(i).getAddressAddr());
        }
      
      if (ipTrail.getEntry(i).getOldValue() != NULL &&
	  heap.isHeapPtr(reinterpret_cast<heapobject*>(ipTrail.getEntry(i).getOldValue())))
	{
	  assert(reinterpret_cast<heapobject*>(ipTrail.getEntry(i).getOldValue()) < heap.getTop());
	  assert(ipTrail.getEntry(i).getOldValue()->gc_isMarked());
	  into_relocation_chain(reinterpret_cast<heapobject*>(ipTrail.getEntry(i).getOldValue()), ipTrail.getEntry(i).getOldVAddr());
	}
    }
}

void
Thread::gc_sweep_names(void)
{
  for (int i = 0; i < (int)(names.allocatedSize()); i++)
    {
      if (! names.getEntry(i).isEmpty())
	{
	  if (names.getEntry(i).getValue()->gc_isMarked())
	    {
	      into_relocation_chain(reinterpret_cast<heapobject*>(names.getEntry(i).getValue()), reinterpret_cast<heapobject*>(names.getEntry(i).getValueAddr()));
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
	  assert(ipTable.getEntry(i).getValue()->gc_isMarked());
	  into_relocation_chain(reinterpret_cast<heapobject*>(ipTable.getEntry(i).getValue()), reinterpret_cast<heapobject*>(ipTable.getEntry(i).getValueAddr()));
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
  assert(reinterpret_cast<heapobject*>(envStack.yReg(env,i)) < heap.getTop());
	      assert(envStack.yReg(env,i)->gc_isMarked());
	      into_relocation_chain(reinterpret_cast<heapobject*>(envStack.yReg(env,i)), envStack.yRegAddr(env,i));
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
Thread::gc_sweep_choicepoints(ChoiceLoc choiceloc, int32& total_marked)
{
  while (true)
    {
      gc_sweep_environments(choiceStack.currentEnv(choiceloc));
      for (int i = choiceStack.getNumArgs(choiceloc)-1; i >= 0; i--)
	{
	  if (heap.isHeapPtr(reinterpret_cast<heapobject*>(choiceStack.getXreg(choiceloc, i))))
	    {
  assert(reinterpret_cast<heapobject*>(choiceStack.getXreg(choiceloc, i)) < heap.getTop());
	      assert(choiceStack.getXreg(choiceloc, i)->gc_isMarked());
	      into_relocation_chain(reinterpret_cast<heapobject*>(choiceStack.getXreg(choiceloc, i)), choiceStack.getXregAddr(choiceloc, i));
	    }
	}

      if (!reinterpret_cast<Object*>(choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop())->gc_isMarked())
	{
	  int32 size = static_cast<int32>(reinterpret_cast<Object*>(choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop())->size_dispatch());
	  *(choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop()) = Short::Zero | Object::GC_M;
          heapobject* ptr = choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop();
	  for (int i = 1; i < size; i++)
	    {
	      *(ptr+i) = Short::Zero;
	    }
	  total_marked++;
	}
      into_relocation_chain(choiceStack.getHeapAndTrailsState(choiceloc).getSavedTop(), choiceStack.getHeapAndTrailsState(choiceloc).getSavedTopAddr()); 

      if (choiceloc == choiceStack.firstChoice())
	{
	  return;
	}
      choiceloc = choiceStack.previousChoicePoint(choiceloc);
    }
}


void
Thread::gc_compaction_phase(word32 arity, int32& total_marked)
{
  gc_sweep_registers(arity);
  gc_sweep_binding_trail();
  gc_sweep_tag_trail();
  gc_sweep_object_trail();
  gc_sweep_ip_trail();
  gc_sweep_names();
  gc_sweep_ips(); 
  gc_sweep_environments(currentEnvironment);
   gc_sweep_choicepoints(currentChoicePoint, total_marked);
   if (!reinterpret_cast<Object*>(heap.getSavedTop())->gc_isMarked())
    {
	  *(heap.getSavedTop()) = Short::Zero | Object::GC_M;
	  total_marked++;
    }
  into_relocation_chain(heap.getSavedTop(), heap.getSavedTopAddr());
  gc_compact_heap(total_marked, heap);
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

  cerr << endl << "=========== The binding trail ======" << endl;
  bindingTrail.printMe(*atoms);

  cerr << endl << "=========== The IP trail ===========" << endl;
  ipTrail.printMe(*atoms);

  cerr << endl << "=========== The object trail =======" << endl;
  objectTrail.printMe(*atoms);

  cerr << endl << "=========== The tag trail ==========" << endl;
  tagTrail.printMe(*atoms);

  cerr << endl << "=========== The name table =========" << endl;
  names.printMe(*atoms);

  cerr << endl << "=========== The IP table ===========" << endl;
  ipTable.printMe(*atoms);
  cerr << endl << "=========== The heap ===============" << endl;
  cerr << "savedTOS = " << hex << (word32)(heap.getSavedTop()) << dec << endl;
heap.printMe(*atoms);
}

//
// Check that after the mark phase no F bits are set and M bits are set
// only on tag words.
//
bool check_after_mark_GC(Heap &heap)
{
  for (heapobject* tp = heap.getBase(); tp < heap.getBase() + 188593; )
    {
      if (!(tp < heap.getTop()))
	{
	  cerr << "over top" << endl;
	  break;
	}
      int32 size = reinterpret_cast<Object*>(tp)->size_dispatch();
      cerr << hex << (word32)(tp) << " : " << (word32)(*tp) << " size = " << dec << size << endl;
      if (tp > heap.getBase() + 188500)
	{
	  cerr << "---------------------" << endl;
	  cerr << hex << (word32)(tp) << " : " << (word32)(*tp) << " size = " << dec << size << endl;
	  for (int32 i = 1; i < size; i++)
	    {
	      cerr << hex << (word32)(tp+i) << " : " << (word32)(*(tp+i)) << dec << endl;
	    }
	}
      tp += size;
    }
  cerr << "..............." << endl;
  for (heapobject* ptr = heap.getBase(); ptr < heap.getTop(); )
    {
      if (ptr > heap.getBase() + 188575)
	{
	  heapobject* tp = ptr;
	  while (tp < heap.getBase() + 188593)
	    {
	      int32 size = reinterpret_cast<Object*>(tp)->size_dispatch();
	      cerr << "---------------------" << endl;
	      cerr << hex << (word32)(tp) << " : " << (word32)(*tp) << " size = " << dec << size << endl;
	      for (int32 i = 1; i < size; i++)
		{
		  cerr << hex << (word32)(tp+i) << " : " << (word32)(*(tp+i)) << dec << endl;
		}
	      tp += size;
	    }
	}
      if ((*ptr & Object::GC_Mask) == 0)
	{
	  // Unmarked object - check args
	  int32 size = reinterpret_cast<Object*>(ptr)->size_dispatch();
	  for (int32 i = 1; i < size; i++)
	    {
	      if ((*(ptr+i) & Object::GC_Mask) != 0)
		{
		  cerr << "Bit set in unmarked object size = " << size << endl;
		  cerr << hex << (word32)(heap.getBase()) << dec << endl;
		  cerr << hex << (word32)(ptr+i) << " : " << (word32)(*(ptr+i)) << dec << endl;
		  return false;
		}
	    }
	  ptr += size;
	}
      else
	{
	  if ((*ptr & Object::GC_F) != 0)
	    {
	      cerr << "F bit set" << (word32)(*ptr) << endl;
	      return false;
	    }
	  int32 size = reinterpret_cast<Object*>(ptr)->size_dispatch();
	  for (int32 i = 1; i < size; i++)
	    {
	      if ((*(ptr+i) & Object::GC_Mask) != 0)
		{
		  cerr << "Bit set in marked object" << endl;
		  return false;
		}
	    }
	  ptr += size;
	}
    }
  return true;
}

#endif //DEBUG

void 
Thread::gc(word32 arity)
{
  status.resetDoGC();
  int32 total_marked = 0;

  bool print_gc_stats = (getenv("QP_GC") != NULL);

  if (print_gc_stats)
    {
      cerr << "GC START - heap size = " 
         << (word32)(heap.getTop() - heap.getBase()) << endl;
    }

  assert(check_heap(heap, atoms));
  //  assert(check_env(currentEnvironment));
  // assert(check_heap2(heap));
  gc_marking_phase(arity, total_marked);

  assert(check_heap(heap, atoms));
  gc_compaction_phase(arity, total_marked);

  assert(check_heap(heap, atoms));
  //assert(check_env(currentEnvironment));
  //assert(check_heap2(heap));


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



