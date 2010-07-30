// quantifier.cc - routines for manipulating quantified term.
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
// $Id: quantifier.cc,v 1.5 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

//
// Check if object is a list of object variables
//
//
// psi_quant(term)
// Succeeds if term is a quantified term.
// mode(in)
//
Thread::ReturnValue
Thread::psi_quant(Object *& object1)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  return BOOL_TO_RV(pval1.getTerm()->isQuantifiedTerm());
}

//
// psi_quantifier(term, quantifier)
// Return the quantifier of a quantified term.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_quantifier(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getTerm()->isQuantifiedTerm())
    {
      if (! pval1.getSubstitutionBlockList()->isNil())
	{
	  return RV_FAIL;
	}

      object2 = 
	OBJECT_CAST(QuantifiedTerm *, pval1.getTerm())->getQuantifier();
      
      return RV_SUCCESS;
    }
  else if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
// psi_bound_var(term, variables)
// Return the bound variables of a quantified term.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_bound_var(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getTerm()->isQuantifiedTerm())
    {
      if (! pval1.getSubstitutionBlockList()->isNil())
	{
	  return RV_FAIL;
	}

      object2 =
	OBJECT_CAST(QuantifiedTerm *, pval1.getTerm())->getBoundVars();

      return RV_SUCCESS;
    }
  else if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
// psi_body(term, body)
// Return the body of a quantified term.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_body(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getTerm()->isQuantifiedTerm())
    {
      if (! pval1.getSubstitutionBlockList()->isNil())
	{
	  return RV_FAIL;
	}
      
      object2 = 
	OBJECT_CAST(QuantifiedTerm *, pval1.getTerm())->getBody();

      return RV_SUCCESS;
    }
  else if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
//
// psi_quantify(term, quantifier, variables, body)
// term is the quantified term made up from quantifier, variables and body.
// mode(in,in,in,in)
//
Thread::ReturnValue
Thread::psi_quantify(Object *& object1,
		     Object *& object2,
		     Object *& object3,
		     Object *& object4)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  if (val1->isQuantifiedTerm())
    {
      QuantifiedTerm *quantified_term =
	OBJECT_CAST(QuantifiedTerm *, val1);
      Object* quant = quantified_term->getQuantifier();
      Object* bvars = quantified_term->getBoundVars();
      Object* body = quantified_term->getBody();

      return BOOL_TO_RV(unify(object2, quant) &&
			unify(object3, bvars) &&
			unify(object4, body));
    }
  else
    {
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  assert(object4->variableDereference()->hasLegalSub());
      Object* val2 = heap.dereference(object2);
      Object* val3 = heap.dereference(object3);
      Object* val4 = heap.dereference(object4);

      if (!heap.isBindingList(val3))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
      
      QuantifiedTerm *quantified_term = heap.newQuantifiedTerm();

      if (val2->isVariable())
	{
	  OBJECT_CAST(Variable *, val2)->setOccursCheck();
	}
      if (val3->isVariable())
	{
	  OBJECT_CAST(Variable *, val3)->setOccursCheck();
		}
      if (val4->isVariable())
	{
	  OBJECT_CAST(Variable *, val4)->setOccursCheck();
	}

      if (! checkBinder(val3, AtomTable::nil))
	{
	  return RV_FAIL;
	}

      quantified_term->setQuantifier(val2);
      quantified_term->setBoundVars(val3);
      quantified_term->setBody(val4);
      return BOOL_TO_RV(unify(quantified_term, val1));
    }
}

//
// psi_check_binder(bound_list, object variables list)
// Ensure the object variables in the bound list mutually distinct and the
// object variables in object variables list are distinct from those in bound
// list.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_check_binder(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* ovlist1 = heap.dereference(object1);
  Object* ovlist2 = heap.dereference(object2);

  if (! heap.isBindingList(ovlist2))
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  if (! ovlist2->isList())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  return BOOL_TO_RV(checkBinder(ovlist1, ovlist2));
}



