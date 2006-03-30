// structrure.cc - Contains functions which retrieve information from and
//                 build up structures.
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
// $Id: structure.cc,v 1.6 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
 
// psi_compound(term)
// Succeed if term is a structure or a list.
// mode(in)
//
Thread::ReturnValue
Thread::psi_compound(Object *& object1)
{
  assert(object1->hasLegalSub());
  PrologValue	pval1(object1);
  
  heap.prologValueDereference(pval1);
  
  return(pval1.getTerm()->isAnyStructure()? RV_SUCCESS : RV_FAIL);
}

// psi_functor(Structure, Functor, Arity)
// mode(in,in,in)
//
Thread::ReturnValue 
Thread::psi_functor(Object *& object1, Object *& object2, Object *& object3)
{
  int 		arity = 0, i;

  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);
  
  if (val1->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, val1);
      Object* arity_object = heap.newNumber(static_cast<long>(str->getArity()));
      return BOOL_TO_RV(unify(val2, str->getFunctor()) && 
		        unify(val3, arity_object));
    }   
  else if (val1->isCons())
    {
       Object* arity_object = heap.newNumber(2);
       return BOOL_TO_RV(unify(val2, AtomTable::cons) && 
			 unify(val3, arity_object));
    } 
  else if (val3->isNumber())
    {
      arity =  val3->getNumber();
      if ((arity < 0) || (arity > (signed) ARITY_MAX))
	{
	  PSI_ERROR_RETURN(EV_RANGE, 3);
	}
      else if (arity == 0)
	{
	  //
	  // a zero arity structure
	  //
	  return BOOL_TO_RV(unify(val1, val2));
	}
      else if (arity == 2 && val2 == AtomTable::cons)
	{
	  //
	  // a list
	  //
	  Variable* head = heap.newVariable();
	  head->setOccursCheck();
	  Variable* tail = heap.newVariable();
	  tail->setOccursCheck();
	  Cons* list = heap.newCons(head, tail);
	  return BOOL_TO_RV(unify(val1, list));
	}
      else
	{
	  if (val2->isVariable())
	    {
	      OBJECT_CAST(Variable*, val2)->setOccursCheck();
	    }
	  Structure* str = heap.newStructure(arity);
	  str->setFunctor(val2);
	  //
	  // initialise all arguments in the structure.
	  //
	  for (i = 1; i <= arity; i++)
	    {
	      Variable* arg = heap.newVariable();
	      arg->setOccursCheck();
	      str->setArgument(i, arg);
	    }
	  return BOOL_TO_RV(unify(val1, str));
	}
    }
  else if (val1->isConstant())
    {
      Object* arity_object = heap.newNumber(0);
      return BOOL_TO_RV(unify(val2, val1) && 
			unify(val3, arity_object));
    }   
  else if (val1->isSubstitution())
    {
      assert(val1->hasLegalSub());
      PrologValue pval(val1);
      heap.prologValueDereference(pval);
      if (pval.getTerm()->isStructure())
	{     
	  Structure* str = OBJECT_CAST(Structure*, pval.getTerm());
	  Object* arity_object = heap.newNumber(static_cast<long>(str->getArity()));
          assert(pval.getSubstitutionBlockList()->isCons());
	  Object* funct 
	    = heap.newSubstitution(pval.getSubstitutionBlockList(),
				   str->getFunctor());
	  return 
	    BOOL_TO_RV(unify(val2, funct) && 
		       unify(val3, arity_object));
	}
      else if (pval.getTerm()->isCons())
	{
	  Object* arity_object = heap.newNumber(2);
	  return 
	    BOOL_TO_RV(unify(val2, AtomTable::cons) &&
		       unify(val3, arity_object));
	}
      else if (pval.getTerm()->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 3);
	}	 
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
    }     
  else // instantiation or type error
    {
      if (val1->isVariable() && val3->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 3);
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
      
    }
}

//
// psi_arg(N, Str, Arg)
// mode(in,in,out)
//
Thread::ReturnValue 
Thread::psi_arg(Object *& object1, Object *& object2, Object *& object3)
{
  int32 arity, i;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (val1->isShort())
    {
      i = val1->getNumber();
      if (val2->isStructure())
	{
	  Structure* str = OBJECT_CAST(Structure*, val2);
	  arity = static_cast<int32>(str->getArity());
	  if ((i <= 0) || (i > arity))
	    {
	      PSI_ERROR_RETURN(EV_RANGE, 1);
	    }
	  object3 = str->getArgument(i);
	  return RV_SUCCESS;
	}
      else if (val2->isCons())
	{
	  Cons* list = OBJECT_CAST(Cons*, val2);
	  if (i == 1) 
	    {
	      object3 = list->getHead();
	      return RV_SUCCESS;
	    }
	  else if (i == 2)
	    {
	      object3 = list->getTail();
	      return RV_SUCCESS;
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_RANGE, 1);
	    }
	}
      else if (val2->isSubstitution())
	{
          assert(val2->hasLegalSub());
	  PrologValue pval(val2);
	  heap.prologValueDereference(pval);
	  if (pval.getTerm()->isStructure())
	    {
	      Structure* str = OBJECT_CAST(Structure*, pval.getTerm());
	      arity = static_cast<int32>(str->getArity());
	      if ((i <= 0) || (i > arity))
		{
		  PSI_ERROR_RETURN(EV_RANGE, 1);
		}
              assert(pval.getSubstitutionBlockList()->isCons());
	      object3 = heap.newSubstitution(pval.getSubstitutionBlockList(),
					     str->getArgument(i));
	      return RV_SUCCESS;
	    }
	  else if(pval.getTerm()->isCons())
	    {
	      Cons* list = OBJECT_CAST(Cons*, pval.getTerm());
	      if (i == 1) 
		{
                  assert(pval.getSubstitutionBlockList()->isCons());
		  object3
		    = heap.newSubstitution(pval.getSubstitutionBlockList(),
					   list->getHead());
		  return RV_SUCCESS;
		}
	      else if (i == 2)
		{
                  assert(pval.getSubstitutionBlockList()->isCons());
		  object3 
		    = heap.newSubstitution(pval.getSubstitutionBlockList(),
					   list->getTail());
		  return RV_SUCCESS;
		}
	      else
		{
		  PSI_ERROR_RETURN(EV_RANGE, 1);
		} 
	    }
	  else if(pval.getTerm()->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 2);
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 2);
	    }
	}
      else
	{
	  if (val2->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 2);
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 2);
	    }
	}
    }
  else
    {
      if (val1->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 1);
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
    }
}


//
// psi_put_structure(F, N, Str)
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_put_structure(Object *& object1, Object *& object2, 
			  Object *& object3)
{
  int32 		arity, i;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  arity =  val2->getNumber();
  
  if((arity <= 0) || (arity > (signed) ARITY_MAX))
    {
      PSI_ERROR_RETURN(EV_RANGE, 2);
    }
  
  if (arity == 2 && val1 == AtomTable::cons)
    {
      //
      // a list
      //
      Cons* list = heap.newCons(AtomTable::nil, AtomTable::nil);
      object3 = list;
      return(RV_SUCCESS);
    }
  else
    {
      if (val1->isVariable())
	{
	  OBJECT_CAST(Variable*, val1)->setOccursCheck();
	}
      Structure* str = heap.newStructure(arity);
      str->setFunctor(val1);
      //
      // zero all arguments in the structure.
      //
      for (i = 1; i <= arity; i++)
	{
	  str->setArgument(i, AtomTable::nil);
	}
      object3 = str;
      return(RV_SUCCESS);
    }
}
//
// psi_set_argument(F, N, Arg)
// mode(in,in,in)
//
Thread::ReturnValue 
Thread::psi_set_argument(Object *& object1, Object *& object2, Object *& object3)
{
  int32 		arity, i;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  Object* funct = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);

  assert(val2->isShort());
  
  i = val2->getNumber();

  if (funct->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, funct);
      arity = static_cast<int32>(str->getArity());
      
      assert((i > 0) && (i <= arity));
      
      if(val3->isVariable())
	{
	  OBJECT_CAST(Variable*, val3)->setOccursCheck();
	}
      str->setArgument(i, val3);
    }
  else if (funct->isCons())
    {
      Cons* list = OBJECT_CAST(Cons*, funct);
      assert((i > 0) && (i <= 2));
      if (i == 1)
	{
	  if(val3->isVariable())
	    {
	      OBJECT_CAST(Variable*, val3)->setOccursCheck();
	    }
	  list->setHead(val3);
	}
      else // i == 2
	{
	  if(val3->isVariable())
	    {
	      OBJECT_CAST(Variable*, val3)->setOccursCheck();
	    }
	  list->setTail(val3);
	}
    }
  else
    {
      assert(false);
    }
  return(RV_SUCCESS);
}









