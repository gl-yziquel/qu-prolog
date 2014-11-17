// buffers.cc - Contains buffer management code.
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
// $Id: buffers.cc,v 1.6 2006/01/31 23:17:49 qp Exp $

#include	<stdio.h>
#include	<string.h>

//#include "copy_term.h"
//#include "heap.h"
//#include "heap_buffer.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// The pseudo-instructions given below provide the interface to the scratchpad
// for the implementation of findall and simplifying substitutions.
//

//
// psi_alloc_buffer(buffer)
// Return the allocated buffer.
// mode(out)
//
Thread::ReturnValue
Thread::psi_alloc_buffer(Object *& object1)
{
  //
  // Allocate the buffer.
  //
  object1 = heap.newInteger(buffers.allocate(heap.getTop(), 
					    scratchpad.getTop()));

  return (RV_SUCCESS);
}


//
// psi_dealloc_buffer(buffer)
// Trim the scratchpad and deallocate the buffer.
// mode(in)
//
Thread::ReturnValue
Thread::psi_dealloc_buffer(Object *& object1)
{
  Object* buffer = heap.dereference(object1);

  assert(buffer->isNumber());
  assert(buffer->getInteger() >= 0);

  word32 bindex = (word32)(buffer->getInteger());

  scratchpad.setTop(buffers.getStart(bindex));
  buffers.deallocate(bindex);
  return(RV_SUCCESS);
}

//
// psi_copy_term_from_buffer(buffer, term)
// Copy the term from the start of the buffer to the heap and return
// the copied term.
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_copy_term_from_buffer(Object *& object1, Object *& object2)
{
  Object* buffer = heap.dereference(object1);

  assert(buffer->isNumber());
  assert(buffer->getInteger() >= 0);

  word32 bindex = (word32)(buffer->getInteger()); 

  if (buffers.getCount(bindex) == 0)
    {
      assert(buffers.getTailAddress(bindex) == NULL);
      object2 = AtomTable::nil;
    }
  else
    {
      assert(buffers.getTailAddress(bindex) != NULL);
      *(buffers.getTailAddress(bindex)) = AtomTable::nil;
      object2 = scratchpad.copyTerm(buffers.getTerm(bindex), heap);
    }
  return (RV_SUCCESS);
}
//
// psi_copy_to_buffer_tail(buffer, term, share)
// Copy the term to the buffer and add to the end of the buffer list.
// The term will be shared if share is true.
// mode(in, in, in)
//
Thread::ReturnValue
Thread::psi_copy_to_buffer_tail(Object *& object1, Object *& object2, 
				Object *& object3)
{
  Object* buffer = heap.dereference(object1);
  Object* share = heap.dereference(object3);
  Object* copy;

  assert(buffer->isNumber());
  assert(buffer->getInteger() >= 0);

  assert(share->isAtom());

  word32 bindex = (word32)(buffer->getInteger()); 

  Cons* cons = scratchpad.newCons();

  if (share == AtomTable::success)  // use structure sharing
    {
      copy = heap.copyShareTerm(object2, scratchpad, heap.getBase(),
				buffers.getInitialTop(bindex));
    }
  else
    {
      copy = heap.copyTerm(object2, scratchpad);
    }
  //
  // Update scratchpad list
  //
  cons->setHead(copy);
  if (buffers.getCount(bindex) == 0)
    {
      assert(reinterpret_cast<heapobject*>(cons) 
		   == buffers.getStart(bindex));
    }
  else
    {
      *(buffers.getTailAddress(bindex)) = cons;
    }
  buffers.setTailAddress(bindex, cons->getTailAddress());   
  buffers.incCount(bindex);
  return (RV_SUCCESS);
}

//
// psi_copy_obvar_to_buffer_tail(buffer, obvar)
// Copy the obvar to the buffer and add to the end of the buffer list.
// The obvar is not dereferenced.
// mode(in, in)
//
Thread::ReturnValue
Thread::psi_copy_obvar_to_buffer_tail(Object *& object1, Object *& object2) 
{
  Object* obvar = object2;

  Object* buffer = heap.dereference(object1);
  assert(buffer->isNumber());
  assert(buffer->getInteger() >= 0);
  word32 bindex = (word32)(buffer->getInteger()); 

  assert(obvar != NULL);
  
  // Dereference down to the object variable.
  while (obvar->isVariable()) 
    {
      //
      // While still an (ob)variable, hence referring to something else,
      // move to what it's referring to
      //
      Object* n = OBJECT_CAST(Reference*, obvar)->getReference();
      assert(n != NULL);
      if ( n == obvar ) 
          {
	    break; // An unbound (ob)variable
	  }
      obvar = n;
    }
  assert(obvar->isObjectVariable());
  
  Cons* cons = scratchpad.newCons();
  cons->setHead(obvar);
  if (buffers.getCount(bindex) == 0)
    {
      assert(reinterpret_cast<heapobject*>(cons) 
		   == buffers.getStart(bindex));
    }
  else
    {
      *(buffers.getTailAddress(bindex)) = cons;
    }
  buffers.setTailAddress(bindex, cons->getTailAddress());   
  buffers.incCount(bindex);
  return (RV_SUCCESS);
}

//
// psi_make_sub_from_buffer(buffer, term, substitution)
// The buffer contains a list representing a substitution block.
// A substitution block is built on the heap from shared copies of the domain
// and range elements in the buffer. The substitution block is turned into
// a substitution block list and applied to term to produce substitution.
//
// mode(in, in, out)
//
Thread::ReturnValue
Thread::psi_make_sub_from_buffer(Object *& object1, Object *& object2, 
				 Object *& object3)
{
  Object* buffer = heap.dereference(object1);

  assert(buffer->isNumber());
  assert(buffer->getInteger() >= 0);

  word32 bindex = (word32)(buffer->getInteger()); 

  u_int count = buffers.getCount(bindex);

  if (count == 0)
    {
      object3 = object2;
    }
  else
    {
      assert(count % 2 == 0);
      count = count/2;

      assert(reinterpret_cast<Object*>(buffers.getStart(bindex))->isCons());
      Cons* cons = reinterpret_cast<Cons*>(buffers.getStart(bindex));

      SubstitutionBlock* subblock = heap.newSubstitutionBlock(count);
      for (u_int i = 1; ; i++)
	{
	  //
	  // Assume the domain element is already on the heap
	  //
	  assert(cons->getHead()->isObjectVariable());
	  subblock->setDomain(i, cons->getHead());
	  assert(cons->getTail()->isCons());
	  cons = OBJECT_CAST(Cons*, cons->getTail());
	  subblock->setRange(i, scratchpad.copyShareTerm(cons->getHead(), 
							 heap,
							 heap.getBase(),
							 buffers.getInitialTop(bindex)));
	  if (i == count)
	    {
	      break;
	    }
	  assert(cons->getTail()->isCons());
	  cons = OBJECT_CAST(Cons*, cons->getTail());
	}
      Cons* sub = heap.newSubstitutionBlockList(subblock, AtomTable::nil);
      object3 = heap.newSubstitution(sub, object2);
    }
  return (RV_SUCCESS);
}

//
// psi_buffer_set_domains_apart(buffer, obvar)
// Make all the domain elements in the sub in the buffer different from obvar.
//
// mode(in, in)
//
Thread::ReturnValue
Thread::psi_buffer_set_domains_apart(Object *& object1, Object *& object2)
{
  Object* buffer = heap.dereference(object1);
  assert(object2->variableDereference()->isObjectVariable());
  ObjectVariable* obvar = 
    OBJECT_CAST(ObjectVariable*, object2->variableDereference());

  assert(buffer->isNumber());
  assert(buffer->getInteger() >= 0);

  word32 bindex = (word32)(buffer->getInteger()); 

  u_int count = buffers.getCount(bindex);

  if (count == 0)
    {
      return RV_SUCCESS;
    }
  else
    {
      assert(count % 2 == 0);
      count = count/2;

      assert(reinterpret_cast<Object*>(buffers.getStart(bindex))->isCons());
      Cons* cons = reinterpret_cast<Cons*>(buffers.getStart(bindex));

      for (u_int i = 1; ; i++)
	{
	  //
	  // Assume the domain element is already on the heap
	  //
	  assert(cons->getHead()->isObjectVariable());
	  ObjectVariable* dom = OBJECT_CAST(ObjectVariable*, cons->getHead()->variableDereference());
	  if (obvar == dom)
	    {
	      return RV_FAIL;
	    }
	  if (!obvar->distinctFrom(dom))
	    {
	      setDistinct(obvar, dom);
	    }
	  
	  if (i == count)
	    {
	      break;
	    }
	  assert(cons->getTail()->isCons());
	  cons = OBJECT_CAST(Cons*, cons->getTail());
	  
	  assert(cons->getTail()->isCons());
	  cons = OBJECT_CAST(Cons*, cons->getTail());
	}
    }
  return (RV_SUCCESS);
}

//
// Copy a term directly in the heap.
//
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_copy_term(Object *& source, Object *& copy)
{
  copy = heap.copyTerm(source, heap);
  return RV_SUCCESS;
}











