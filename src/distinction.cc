// distinction.cc - Contains a set of functions for dealing with distinctness 
//		    information associated with the object variable.
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: distinction.cc,v 1.5 2006/01/31 23:17:50 qp Exp $

// #include "atom_table.h"
#include "thread_qp.h"

//
// Set two object variables to be distinct from each other.
//
void
Thread::setDistinctObjectVariable(ObjectVariable *object_variable1,
				  ObjectVariable *object_variable2)
{
  assert(object_variable1->getReference() == object_variable1);
  assert(object_variable2->getReference() == object_variable2);

 updateAndTrailObject(reinterpret_cast<heapobject*>(object_variable1),
		       heap.newCons(object_variable2, 
				    object_variable1->getDistinctness()),
		       ObjectVariable::DistinctnessOffset);
}

void
Thread::setDistinct(ObjectVariable *object_variable1,
		    ObjectVariable *object_variable2)
{
  setDistinctObjectVariable(object_variable1, object_variable2);
  setDistinctObjectVariable(object_variable2, object_variable1);
}



//
// Set all the range elements to be mutually disjoint from each other.
// Assume the range are newly created object variables.
//
void
Thread::setMutualDistinctRanges(SubstitutionBlock *sub_block)
{
  for (size_t i = 2; i <= sub_block->getSize(); i++)
    {
      assert(sub_block->getRange(i)->isObjectVariable());

      ObjectVariable *irange 
	= OBJECT_CAST(ObjectVariable* , sub_block->getRange(i)); 

      assert(irange->getReference() == irange);

      for (size_t j = 1; j < i; j++)
	{
	  assert(sub_block->getRange(j)->isObjectVariable());
   
	  ObjectVariable *jrange 
	    = OBJECT_CAST(ObjectVariable*, sub_block->getRange(j));

	  assert(jrange->getReference() == jrange);
	  
	  setDistinct(irange, jrange);
	}
    }
}

//
// If there is no distinctness information between the object variable
// and a domain, set the object variable to be distinct from the domain.
// Fail, if the object variable is equal to any domain.
// NOTE:
//	ObjectVariable should be dereferenced before this function is called.
//
bool 
Thread::generateDistinction(ObjectVariable *object_variable,
			    Object *sub_block_list)
{
  assert(sub_block_list->isNil() ||
	       (sub_block_list->isCons() &&
		OBJECT_CAST(Cons*, sub_block_list)->isSubstitutionBlockList()));
  assert(object_variable->getReference() == object_variable);
  
  for (Object *s = sub_block_list;
       s->isCons();
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      assert(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub_block 
	= OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s)->getHead());

      for (size_t i = 1; i <= sub_block->getSize(); i++)
	{
	  assert(sub_block->getDomain(i)->isObjectVariable());

	  ObjectVariable *domain 
	    = OBJECT_CAST(ObjectVariable*, 
			  sub_block->getDomain(i)->variableDereference());
	  assert(domain->isObjectVariable());
	  if (object_variable == domain)
	    {
	      return false;
	    }
	  else if (! object_variable->distinctFrom(domain)) 
	    {
	      setDistinct(object_variable, domain);
	    }
	}
    }
  return true;
}


//
// Check objvar is distinct from all the bound variables.
//
bool
Thread::distinctBoundList(ObjectVariable *object_variable, Object *bound_list)
{
  assert(object_variable->variableDereference() == object_variable);
  for (bound_list = bound_list->variableDereference();
       bound_list->isCons();
       bound_list 
	 = OBJECT_CAST(Cons *, bound_list)->getTail()->variableDereference())
    {
      Object *bound
	= OBJECT_CAST(Cons *, bound_list)->getHead()->variableDereference();
  
      assert(bound->isObjectVariable());
      
      ObjectVariable *bound_object_variable = 
	OBJECT_CAST(ObjectVariable *, bound);
      if (object_variable == bound_object_variable)
	{
	  return false;
	}
      else if (! object_variable->distinctFrom(bound_object_variable)) 
	{
	  //
	  // Set them distinct.
	  //
	  setDistinct(object_variable, bound_object_variable);
	}
    }
  
  return true;
}

//
// Ensure the object variables in the bound variable list are mutually
// distinct.
//
bool
Thread::checkBinder(Object *bound_list, Object* so_far)
{
  for (bound_list = bound_list->variableDereference();
       bound_list->isCons();
       bound_list 
	 = OBJECT_CAST(Cons*, bound_list)->getTail()->variableDereference()
       )
    {
      Object *object
	= OBJECT_CAST(Cons*, bound_list)->getHead()->variableDereference();
      
      if (object->isStructure())
	{
	  //
	  // The binder is ObjVar:Term.
	  //
	  assert(OBJECT_CAST(Structure*, object)->getArity() == 2);
	  assert(OBJECT_CAST(Structure*, object)->getFunctor() 
		       == AtomTable::colon);
	  
	  object = OBJECT_CAST(Structure*, object)->getArgument(1)->variableDereference();
	}
	  
      if(!object->isObjectVariable())
	{
          return false;
        }

      
      ObjectVariable *object_variable = 
	OBJECT_CAST(ObjectVariable *, object);
      if (! distinctBoundList(object_variable, so_far))
	{
	  return false;
	}
      
      so_far = heap.newCons(object_variable, so_far);
    }
  if (bound_list->isVariable())
    {
      //
      // Impose the constraint for bound variables.
      //
      Structure *problem = heap.newStructure(2);
      
      problem->setFunctor(AtomTable::checkBinder);
      problem->setArgument(1, bound_list);
      problem->setArgument(2, so_far);
      
      delayProblem(problem, OBJECT_CAST(Reference*, bound_list));
    }
  
  return true;
}











