// gc.cc - Garbage collector.
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
// $Id: gc.cc,v 1.9 2003/08/06 23:42:34 qp Exp $

#include "global.h"
#include "gc.h"
#include "heap_qp.h"
#include "objects.h"


//
// The following garbage collector is absed on the paper
// "Garbage Collection for Prolog Based on WAM" by
// Appleby, Carlsson, Haridi and Sahlin.
//
// The algorithm is slightly modified because of the differences between
// the Qu-Prolog data structures and those of the standard WAM.
//
// The important differences are:
// 1. QP uses pointers to objects rather than objects themselves - e.g. X
//    registers and the arguments of structures are pointers to objects.
// 2. Each QP object is a tagged word followed by the "arguments" of the
//    object. So, for example, an unbound variable is a tagged word followed by
//    a pointer to the tagged word. This means that the whole object is 
//    processed at the same time - typically requiring a loop over the
//    "arguments".
//
// 
// -------------------------
//
// Marking phase.
//
// -------------------------

#ifdef DEBUG

//
// Code for checking the heap during and after GC
//

// 
// Check that the GC bits on each work in the heap is unset
//
bool check_after_GC(Heap& heap)
{
  for (heapobject* ptr = heap.getBase(); ptr < heap.getTop(); ptr++)
    {
      if ((*ptr & Object::GC_Mask) != 0)
	{
	  cerr << "Mask error Bits = " << (*ptr & Object::GC_Mask) << endl;
	  return false;
	}
    }
  return true;
}

bool check_term(Object* term)
{
  if (term == NULL) return false;

    switch (term->utag())
    {
    case Object::uVar:
      {
      Object* n  = OBJECT_CAST(Reference*, term)->getReference();
      if (n == term) return true;
      return (check_term(n));
      }
      break;
    case Object::uObjVar:
      {
	Object* n = OBJECT_CAST(Reference*, term)->getReference();
      if (n == term) return true;
      return (check_term(n));
      }
      break;
    case Object::uStruct:
      {
	Structure* s = OBJECT_CAST(Structure *, term);
      for (int i = 0; i <= s->getArity(); i++)
	{
	  if (!check_term(s->getArgument(i)))return false;
	}
      return true;
      }
      break;
    case Object::uCons:
      {
	Cons* l = OBJECT_CAST(Cons *, term);
      return (check_term(l->getHead()) && check_term(l->getTail()));
      }
      break;
    case Object::uQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm *, term);
      return (check_term(q->getQuantifier()) && 
	      check_term(q->getBoundVars()) && check_term(q->getBody()));
      }
      break;
    case Object::uConst:
      return true;
      break;
    case Object::uSubst:
      {
	Substitution* s = OBJECT_CAST(Substitution *, term);
      return(check_term(s->getTerm()) && check_term(s->getSubstitutionBlockList()));
      }
      break;
    case Object::uSubsBlock:
      {
	SubstitutionBlock * s = OBJECT_CAST(SubstitutionBlock *, term);
      for (int i = 1; i <= s->getSize(); i++)
	{
	  if (!check_term(s->getDomain(i)) || !check_term(s->getRange(i)) )return false;
	}
      return true;
      }
      break;
    default:
      return false;
    }
}

bool check_heap2(Heap& heap)
{
  for (heapobject* ptr = heap.getBase(); ptr < heap.getTop(); )
    {
      Object* term =  reinterpret_cast<Object*>(ptr);
      if (!check_term(term)) return false;
      ptr += term->size_dispatch();
    }
  return true;

}

#endif // DEBUG


void gc_mark_pointer(Object* start, int32& total_marked, Heap& heap)
{

  if (start == NULL || 
      !heap.isHeapPtr(reinterpret_cast<heapobject*>(start)) ||
      start->gc_isMarked())
    {

      // Nothing to do
      return;
    }
  DEBUG_CODE(
  {
    if (!check_term(start))
      {
	//  Structure* ss = OBJECT_CAST(Structure*, start);
	//  ss->setArgument(1, AtomTable::nil);
	start->printMe_dispatch(*atoms,false);
      }
  }
  );

  DEBUG_ASSERT(reinterpret_cast<heapobject*>(start) < heap.getTop());
  // Mark the object (by marking the tag word)
  start->gc_mark();
  total_marked += start->size_dispatch();
  if (start->isNumber())
    {
      // If the object is a number then there are no chains to follow
      return;
    }

  // Set the F bits on all the "arguments" of the object.
  // NOTE: it is assumed that the "arguments" are all pointers to objects
  start->gc_setfs();

  // Initialize for marking
  heapobject* current = start->last();
DEBUG_ASSERT(current != NULL);
  Object* next = reinterpret_cast<Object*>(*current & ~Object::GC_Mask);
DEBUG_ASSERT(next != NULL);
  *current = reinterpret_cast<heapobject>(start) | (*current & Object::GC_Mask);
  
  DEBUG_ASSERT((*(reinterpret_cast<heapobject*>(start)) & Object::GC_F) == 0);
 forward:
  {
    DEBUG_ASSERT(next != NULL);
    DEBUG_ASSERT((*(reinterpret_cast<heapobject*>(next)) & Object::GC_F) == 0);
    if (next->gc_isMarked() || 
	!heap.isHeapPtr(reinterpret_cast<heapobject*>(next)))
      {
	// no more marking required on this chain
	goto backward;
      }
  DEBUG_ASSERT(reinterpret_cast<heapobject*>(next) < heap.getTop());
    // Mark the object in the chain
    next->gc_mark();
    total_marked += next->size_dispatch();
    if (next->isNumber())
      {
	goto backward;
      }
    next->gc_setfs();

    // Move to the next chain object

DEBUG_ASSERT(current != NULL);
    heapobject* tmp = current;
    current = next->last();
DEBUG_ASSERT(current != NULL);
    next = reinterpret_cast<Object*>(*current & ~Object::GC_Mask);
DEBUG_ASSERT(next != NULL);
    *current = reinterpret_cast<heapobject>(tmp) | (*current & Object::GC_Mask);
    goto forward;
  }

 backward:
  {
DEBUG_ASSERT(next != NULL);
DEBUG_ASSERT(current != NULL);
    DEBUG_ASSERT(( *(reinterpret_cast<heapobject*>(next)) & Object::GC_F) == 0);
    DEBUG_ASSERT((*current & Object::GC_F) == Object::GC_F);
    // re-reverse the pointer 
    heapobject* tmp = 
      reinterpret_cast<heapobject*>(*current & ~Object::GC_Mask);
DEBUG_ASSERT(tmp != NULL);
    *current = reinterpret_cast<heapobject>(next);
DEBUG_ASSERT(current != NULL);
    // Move the previous "argument" of the object
    current--;
    //
    // Deal with NULL pointers - the (non-)names of (obj)vars.
    //
    while (*current == Object::GC_F)
      {
        *current = 0;
	current--;
      }
DEBUG_ASSERT(current != NULL);
    if (current == reinterpret_cast<heapobject*>(start))
      {
	// returned to the start - finished marking
	DEBUG_ASSERT(check_term(start));
	return;
      }
    if ((*current & Object::GC_F) == 0)
      {
	// Finished processing the "arguments"
	// Step back in the chain
	next = reinterpret_cast<Object*>(current);
DEBUG_ASSERT(next != NULL);
	current = tmp;
DEBUG_ASSERT(current != NULL);
	goto backward;
      }
    // Otherwise move into the new "argument" chain for marking.
DEBUG_ASSERT(current != NULL);
    next = reinterpret_cast<Object*>(*current & ~Object::GC_Mask);
DEBUG_ASSERT(next != NULL);
    *current = 
      reinterpret_cast<heapobject>(tmp) | (*current & Object::GC_Mask);
    goto forward;
  }
}
	      
// -------------------------
//
// Compaction phase.
//
// -------------------------


void gc_compact_heap(int32 marked, Heap& heap)
{
  //
  // "Upward" phase.
  //
  // Start at the top of the heap and scan down looking for downward pointers.
  //
  heapobject* dest = heap.getBase() + marked;

  for (heapobject* ptr = heap.getTop() - 1;
       ptr >= heap.getBase(); --ptr)
    {
      if ((*ptr & Object::GC_M) == 0)
	{
	  continue;
	}
      
      if ((*ptr & Object::GC_F) == Object::GC_F)
	{
	  // We have reached the end of some relocation chain.
	  // The size of the object is determined and the
	  // chain is relocated using the final destination of the object.
	  //
	  heapobject* end_of_chain = 
	    unfold_chain(reinterpret_cast<heapobject*>(*ptr & ~Object::GC_Mask));
	  int32 size = 
	    reinterpret_cast<Object*>(end_of_chain)->size_dispatch();
	  update_relocation_chain(ptr, dest - size);
	}

      if ((*ptr & Object::GC_M) == Object::GC_M)
	{
	  // We have reached a marked object - look at each "argument"
	  int32 size = reinterpret_cast<Object*>(ptr)->size_dispatch();
	  dest -= size;
	  if (reinterpret_cast<Object*>(ptr)->isNumber())
	    {
	      continue;
	    }
	  for (heapobject* curr = ptr+size-1; curr > ptr; --curr)
	    {
	      heapobject* tmp = 
		reinterpret_cast<heapobject*>(*curr & ~Object::GC_Mask);
	      
	      if (!heap.isHeapPtr(tmp))
		{
		  continue;
		}
  DEBUG_ASSERT(reinterpret_cast<heapobject*>(tmp) < heap.getTop());
	      if (tmp < ptr)
		{
		  into_relocation_chain(tmp, curr);
		}
	      // The "argument" points at the object - an unbound ref
	      else if (tmp == ptr)
		{
		  *curr = reinterpret_cast<heapobject>(dest) | 
	                  (*curr & Object::GC_Mask);
		}
	    }
	  // We assume there are no "immediate" cyclic objects
	  // other than unbound refs. This means that the F bit should 
	  // not be set at this point. If this is not the case use
	  // update_relocation_chain(ptr, dest);
	  DEBUG_ASSERT((*ptr & Object::GC_F) != Object::GC_F);
	}
    }

  // "Downward" phase
  // Start at the base of the heap and work up - put objects in their
  // new positions and take care of upward pointers.

  dest = heap.getBase();
  for (heapobject* ptr = heap.getBase(); ptr < heap.getTop(); )
    {
      if ((*ptr & Object::GC_M) == 0)
	{
	  ptr++;
	  continue;
	}

      // relocate if we hit the end of a chain
      update_relocation_chain(ptr, dest);

      int32 size = reinterpret_cast<Object*>(ptr)->size_dispatch();

      *dest = *ptr & ~Object::GC_Mask;
      dest++;
      if (reinterpret_cast<Object*>(ptr)->isLong())
	{
	  // Move the long to its new place
	  *dest = *(ptr+1) & ~Object::GC_Mask;
	  dest++;
	  ptr += size;
	  continue;
	}
      // Move the "arguments" of the object
      for (heapobject* curr = ptr+1; curr < ptr+size; curr++)
	{
	  heapobject* tmp = 
	    reinterpret_cast<heapobject*>(*curr & ~Object::GC_Mask);
	  if (heap.isHeapPtr(tmp) && tmp > curr)
	    {
  DEBUG_ASSERT(reinterpret_cast<heapobject*>(tmp) < heap.getTop());
	      into_relocation_chain(tmp, dest);
	    }
	  else
	    {
	      *dest = reinterpret_cast<heapobject>(tmp);
	    }
	  *dest &= ~Object::GC_M;
	  dest++;
	}
      ptr += size;
    }
  // Finished - reset the top of heap.
  heap.setTop(heap.getBase() + marked - 1);
  DEBUG_ASSERT(check_after_GC(heap));
}



