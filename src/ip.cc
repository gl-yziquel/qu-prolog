// ip.cc - Routines for manipulating implicit parameters, which must be an atom.
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
// $Id: ip.cc,v 1.11 2006/01/31 23:17:50 qp Exp $


#include "atom_table.h"
#include "thread_qp.h"
extern AtomTable *atoms;
//
// The IP array size is a power of 2
//
const size_t ip_array_size = 128;

//
// We use the following idea from BinProlog to minimize trail usage.
// The data structures used are as follows
//
//  IPtable                  heap
//
//  |       |                  |        |
//  |       |                  |        |
//  |Ref:   |-----+            |        |
//  |       |     +----------->|value(*)|
//  |       |                  |        |
//  |       |                  |        |
//  |       |                  |        |
//
//  After each ip_set the value at (*) is above the saved top of stack
//  I.E. above the last choice point.
//  This means that at the start of each ip_set we can determine when
//  trailing needs to take place by simply comparing the pointer from the IP
//  and the saved top of heap. If the pointer is below saved TOH
//  then trailing is required, otherwise it is not required.
//  If trailing is required, a reference is created, that replaces
//  the value in the IPtable (and is trailed).
//  The value is placed in the heap at the place pointed to by the 
//  new reference.
//  If no trailing is required the value at (*) is replaced by 
//  the new value (not trailed).
//
//  The structures used for IP arrays are as follows
//
//  IPtable                  heap
//
//  |       |                  | ...    |
//  |       |            (arg1)| Ref    | --> list (on heap)
//  |Struct |-----+            | arity  |
//  |       |     +----------->|$iparray|
//  |       |                  |        |
//  |       |                  |        |
//  |       |                  |        |
//
//  The lists on the heap are of the form [$iparray(Val,Hash)...]
//  where Hash is the atomic value input as an offset into the array
//  Val is the value of this entry and has the same properties as the
//  Val of a simple IP (in terms of trail optimization).
//
// Note: There are three possibilities for the value of in the IPtable
// (before dereferencing)
// 1. NULL          - no value present
// 2. A variable*   - an ordinary IP
// 3. A structure*  - an array IP


// psi_ip_set(key, value)
// Assign a value for an implicit parameter.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_ip_set(Object *& object1, Object *& object2)
{
  Object *name_object = heap.dereference(object1);

  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  Object *current_value = ipTable.getImplicitPara(name_object);
  if (current_value != NULL && current_value->isStructure() && 
      OBJECT_CAST(Structure *, current_value)->getFunctor() 
      == AtomTable::arrayIP)
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *new_value = object2->variableDereference();
  if (current_value == NULL ||
      (heap.getSavedTop() > reinterpret_cast<heapobject*>(current_value)))
    {
      Variable *var = heap.newVariable();
      var->setReference(new_value);
      ipTable.setImplicitPara(name_object, var, *this);
    }
  else
    {
      assert(current_value->isVariable());
      OBJECT_CAST(Variable*, current_value)->setReference(new_value);
    }

  return RV_SUCCESS;
}

// psi_ip_setA(key, hashVal, value)
// Assign a value for an array implicit parameter.
// mode(in,in,in)
//
Thread::ReturnValue
Thread::psi_ip_setA(Object *& object1, Object *& object2, Object *& object3)
{
  Object *name_object = heap.dereference(object1);
  
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *hash_val = heap.dereference(object2);

  /* get IP offset */
  if (hash_val->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (! hash_val->isConstant())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
    /* set value */
  Object *new_value = object3->variableDereference();
  Object *current_value = ipTable.getImplicitPara(name_object);
  
  size_t array_size;
  if (current_value == NULL) 
    {
      current_value = heap.newStructure(ip_array_size);
      OBJECT_CAST(Structure*, current_value)->setFunctor(AtomTable::arrayIP);
      
      array_size = ip_array_size;
      for (size_t i = 1; i <= ip_array_size; i++)
	{
	  OBJECT_CAST(Structure*, current_value)->setArgument(i, AtomTable::nil);
	}

      ipTable.setImplicitPara(name_object, current_value, *this);
    }
  else
    {
      if (! current_value->isStructure() || 
	  OBJECT_CAST(Structure *, current_value)->getFunctor() 
	  != AtomTable::arrayIP)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      array_size = OBJECT_CAST(Structure *, current_value)->getArity();
    }
  
  const long offset = 1 +
    static_cast<long>((hash_val->isNumber() ?
      (hash_val->getNumber() & (array_size-1))
    : ((reinterpret_cast<word32>(hash_val) >> 2) & (array_size-1))));

  Object *array_val_list = 
    OBJECT_CAST(Structure*, current_value)->getArgument(offset)->variableDereference();

  Object *array_ptr = array_val_list;

  for (;
       array_ptr->isCons();
       array_ptr = OBJECT_CAST(Cons *, array_ptr)->getTail()
       )
    {
      assert(OBJECT_CAST(Cons *, array_ptr)->getHead()->isStructure());
      
      Structure *array_val_head = 
	OBJECT_CAST(Structure *, OBJECT_CAST(Cons *, array_ptr)->getHead());

      Object *list_hash = array_val_head->getArgument(2);

      if (list_hash == hash_val ||
	  (hash_val->isNumber() && list_hash->isNumber() &&
	   hash_val->getNumber() == list_hash->getNumber()))
	{
	  break;
	}
    }

  if (array_ptr->isNil())
    {
      // no value for this offset
      Structure *new_array_val_head = heap.newStructure(2);
      
      new_array_val_head->setFunctor(AtomTable::arrayIP);
      new_array_val_head->setArgument(2, hash_val);

      Variable* ipvar = heap.newVariable();
      ipvar->setReference(new_value);

      new_array_val_head->setArgument(1, ipvar);

      Object *new_array_val_list = heap.newCons(new_array_val_head,
						array_val_list);

      assert(current_value->isStructure());
      updateAndTrailIP(reinterpret_cast<heapobject*>(current_value), 
		       new_array_val_list, offset+1);
    }
  else
    {
      assert(array_ptr->isCons());
      Structure *array_val_head = 
	OBJECT_CAST(Structure *, 
		    OBJECT_CAST(Cons *, array_ptr)->getHead());

      if (heap.getSavedTop() >
	  reinterpret_cast<heapobject*>(array_val_head->getArgument(1)))
	{
	  Variable* ipvar = heap.newVariable();
	  ipvar->setReference(new_value);
	  // The 2 below is the offset to the first arg of the struct
	  updateAndTrailIP(reinterpret_cast<heapobject*>(array_val_head), 
			   ipvar, 2);
	}
      else
	{
	  Object* old = array_val_head->getArgument(1);
	  assert(old->isVariable());
	  OBJECT_CAST(Variable*, old)->setReference(new_value);
	}
    }
  
  return RV_SUCCESS;
}


//
// psi_ip_lookup(key, value)
// Look up the value of an implicit parameter.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_ip_lookup(Object *& object1, Object *& object2)
{
  Object *name_object = heap.dereference(object1);

  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *current_value = ipTable.getImplicitPara(name_object);
  if (current_value != NULL &&
      current_value->isStructure() && 
      OBJECT_CAST(Structure*, current_value)->getFunctor()
      == AtomTable::arrayIP)
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (current_value == NULL)
    {
      Variable* ip_var = heap.newVariable();
      Variable* new_ref = heap.newVariable();
      ip_var->setReference(new_ref);
      
      ipTable.setImplicitPara(name_object, ip_var, *this);

      current_value = new_ref;
    }

  object2 = current_value->variableDereference();

  return RV_SUCCESS;
}

// psi_ip_lookupA(key, hash_val, value)
// Lookup a value for an array implicit parameter.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_ip_lookupA(Object *& object1, Object *& object2, Object *& object3)
{
  Object *name_object = heap.dereference(object1);
  Object *hash_val = heap.dereference(object2);
  Object *current_ip_val;

  /* get IP array name */
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  /* get IP offset */
  if (hash_val->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (! hash_val->isConstant())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  /* lookup value */
  Object *current_value = ipTable.getImplicitPara(name_object);
  
  size_t array_size;
  if (current_value == NULL)
    {
      current_value = heap.newStructure(ip_array_size);
      OBJECT_CAST(Structure*, current_value)->setFunctor(AtomTable::arrayIP);
      
      for (size_t i = 1; i <= ip_array_size; i++)
	{
	  OBJECT_CAST(Structure*, current_value)->setArgument(i, AtomTable::nil);
	}

      array_size = ip_array_size;
      ipTable.setImplicitPara(name_object, current_value, *this);
    }
  else
    {
      if (! current_value->isStructure() || 
	  OBJECT_CAST(Structure*, current_value)->getFunctor() 
	  != AtomTable::arrayIP)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      array_size = OBJECT_CAST(Structure*, current_value)->getArity();
    }
  
  const int32 offset = 1 +
    static_cast<int32>((hash_val->isNumber()
     ? hash_val->getNumber() & (array_size-1) 
     : (reinterpret_cast<word32>(hash_val) >> 2) & (array_size-1)));
  
  Object *array_val_list = 
    OBJECT_CAST(Structure*, current_value)->getArgument(offset)->variableDereference();
  Object *array_ptr = array_val_list;

  assert(array_ptr->isList());

  for (;
       array_ptr->isCons();
       array_ptr = OBJECT_CAST(Cons*, array_ptr)->getTail()->variableDereference())
    {
      Object *array_val_head =  
	OBJECT_CAST(Cons*, array_ptr)->getHead()->variableDereference();

      assert(array_val_head->isStructure());

      Object *list_hash = 
	OBJECT_CAST(Structure*, array_val_head)->getArgument(2)->variableDereference();

      if (list_hash == hash_val ||
	  (hash_val->isNumber() && list_hash->isNumber() &&
	   hash_val->getNumber() == list_hash->getNumber()))
	{
	  object3 = OBJECT_CAST(Structure*, array_val_head)->getArgument(1)->variableDereference();
	  return RV_SUCCESS;
	}
    }

  assert(array_ptr->isNil());

  // no value for this offset
  Structure* array_val_head = heap.newStructure(2);
  array_val_head->setFunctor(AtomTable::arrayIP);
  array_val_head->setArgument(2, hash_val);
      
  Variable *new_ref = heap.newVariable();
  Variable *ip_var = heap.newVariable(new_ref);
  ip_var->setReference(new_ref);
  array_val_head->setArgument(1, ip_var);
  
  current_ip_val = ip_var;
  
  Cons *new_array_val_list = heap.newCons(array_val_head, array_val_list);
  
  assert(current_value->isStructure());

  updateAndTrailIP(reinterpret_cast<heapobject*>(current_value), 
		   new_array_val_list, offset+1);
  object3 = new_ref;
  return(RV_SUCCESS);
}


// psi_ip_array_clear(key)
// Clear (initilize) an IP array.
// mode(in)
//
Thread::ReturnValue
Thread::psi_ip_array_clear(Object *& object1)
{
  Object *name_object = heap.dereference(object1);
  
  /* get IP array name */
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  /* clear (init) array */

  // check if IP is not already in use as an non-array IP
  Object* old = ipTable.getImplicitPara(name_object);
  if (old != NULL && !old->isStructure())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  size_t array_size;
  if (old == NULL)
    {
      array_size = ip_array_size;
    }
  else
    {
      array_size = OBJECT_CAST(Structure*, old)->getArity();
    }
  Structure *ip_array_struct = heap.newStructure(array_size);
  ip_array_struct->setFunctor(AtomTable::arrayIP);
  
  for (size_t i = 1; i <= array_size; i++)
    {
      ip_array_struct->setArgument(i, AtomTable::nil);
    }
  
  ipTable.setImplicitPara(name_object, ip_array_struct, *this);

  return RV_SUCCESS;
}

// psi_ip_array_init(key, size)
// Initilize an IP array to size.
// mode(in, in)
//
Thread::ReturnValue 
Thread::psi_ip_array_init(Object *& object1, Object *& object2)
{
  Object *name_object = heap.dereference(object1);
  
  /* get IP array name */
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  Object *size_object = heap.dereference(object2);
  
  /* get IP array size */
  if (size_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (! size_object->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  int size = size_object->getNumber();
  if (size <= 0)
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  // Calculate power of 2 >= size
  size_t array_size = 1;
  size--;
  while (size > 0)
    {
      size >>= 1;
      array_size <<= 1;
    } 

  // Create new IP array
  Structure *ip_array_struct = heap.newStructure(array_size);
  ip_array_struct->setFunctor(AtomTable::arrayIP);
  
  for (size_t i = 1; i <= array_size; i++)
    {
      ip_array_struct->setArgument(i, AtomTable::nil);
    }
  
  ipTable.setImplicitPara(name_object, ip_array_struct, *this);

  return RV_SUCCESS;
}








