// temperature.cc - routines for handling freeze and thaw.
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
// $Id: temperature.cc,v 1.5 2005/11/26 23:34:31 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

//
// Freeze(thaw) vars in sub adding newly frozen(thawed) vars to varlist.
// If do_freeze is true then vars are frozen otherwise thawed.
// If get_vars is true then vars are collected into varlist.
//
void
Thread::freeze_thaw_sub(Object* sub, Object*& varlist,
			bool do_freeze, bool get_vars)
{
  assert(sub->isCons());
  assert(OBJECT_CAST(Cons*, sub)->isSubstitutionBlockList());

  for (;sub->isCons();sub = OBJECT_CAST(Cons*, sub)->getTail() )
    {
      assert(OBJECT_CAST(Cons*, sub)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* subblock 
	= OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());
      
      for (size_t i = 1; i <= subblock->getSize(); i++)
        {
	  freeze_thaw_term(subblock->getRange(i), varlist, 
			   do_freeze, get_vars);
          freeze_thaw_term(subblock->getDomain(i), 
			   varlist, do_freeze, get_vars);
	}
    }
  return;
}

//
//  Freeze(thaw) vars in term adding newly frozen(thawed) vars to varlist.
// If do_freeze is true then vars are frozen otherwise thawed.
// If get_vars is true then vars are collected into varlist.
//
void
Thread::freeze_thaw_term(Object* term, Object*& varlist,
			 bool do_freeze, bool get_vars)
{
  term = heap.dereference(term);
  switch (term->utag())
    {
    case Object::uVar:
    case Object::uObjVar:
      if (!term->isLocalObjectVariable())
	{
	  if (do_freeze && OBJECT_CAST(Reference*, term)->isThawed())
	    {
	      trailTag(term);
	      OBJECT_CAST(Reference*, term)->freeze();
	      if (get_vars)
		{
		  Cons* temp = heap.newCons(term, varlist);
		  varlist = temp;
		}
	    }
	  else if (!do_freeze && OBJECT_CAST(Reference*, term)->isFrozen())
	    {
	      trailTag(term);
	      OBJECT_CAST(Reference*, term)->thaw();
	      if (get_vars)
		{
		  Cons* temp = heap.newCons(term, varlist);
		  varlist = temp;
		}
	    }
	}
      break;

    case Object::uCons:
      {
	Object* list = term;
	for (; list->isCons();
	     list = heap.dereference(OBJECT_CAST(Cons*, list)->getTail()))
	  {
	    freeze_thaw_term(OBJECT_CAST(Cons*, list)->getHead(), 
			     varlist, do_freeze, get_vars);
	  }
	if (!list->isConstant())
	  {
	    freeze_thaw_term(list, varlist, do_freeze, get_vars);
	  }
      }
      break;

    case Object::uStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	if (!str->getFunctor()->isConstant())
	  {
	    freeze_thaw_term(str->getFunctor(), varlist, do_freeze, get_vars);
	  }
	
	for (size_t i = 1; i <= str->getArity(); i++)
	  {
	    freeze_thaw_term(str->getArgument(i), varlist, 
			     do_freeze, get_vars);
	  }
      }
      break;

    case Object::uQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, term);
	if (!quant->getQuantifier()->isConstant())
	  {
	    freeze_thaw_term(quant->getQuantifier(), varlist, 
			     do_freeze, get_vars);
	  }
	freeze_thaw_term(quant->getBoundVars(), varlist, do_freeze, get_vars);
	freeze_thaw_term(quant->getBody(), varlist, do_freeze, get_vars);
      }
	break;

    case Object::uConst:
      break;

    case Object::uSubst:
      freeze_thaw_sub(OBJECT_CAST(Substitution*, 
				   term)->getSubstitutionBlockList(), 
		      varlist, do_freeze, get_vars);
      freeze_thaw_term(OBJECT_CAST(Substitution*, term)->getTerm(), 
		       varlist, do_freeze, get_vars);
      break;
      
    default:
      assert(false);
      break;
    }
}

//
// psi_freeze_term(term)
// Set the temperature tag of all variables in term  to freeze.
// mode(in)
//
Thread::ReturnValue	
Thread::psi_freeze_term(Object *& object1)
{
  Object* dummy = AtomTable::nil;
  freeze_thaw_term(object1, dummy, true, false);
  
  return RV_SUCCESS;
}

//
// psi_freeze_term(term,list)
// Set the temperature tag of all variables in term  to freeze.
// All variables that are frozen by this operation are returned in list.
// mode(in,out)
//
Thread::ReturnValue	
Thread::psi_freeze_term(Object *& object1, Object *& object2)
{
  Object* varlist = AtomTable::nil;
  freeze_thaw_term(object1, varlist, true, true);
  
  object2 = varlist;

  return RV_SUCCESS;
}

//
// psi_thaw_term(term)
// Set the temperature tag of all variables in term  to thaw.
// mode(in)
//
Thread::ReturnValue	
Thread::psi_thaw_term(Object *& object1)
{
  Object* dummy = AtomTable::nil;
  freeze_thaw_term(object1, dummy, false, false);
  
  return RV_SUCCESS;
}

//
// psi_thaw_term(term,list)
// Set the temperature tag of all variables in term  to thaw.
// All variables that are frozen by this operation are returned in list.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_thaw_term(Object *& object1, Object *& object2)
{
  Object* varlist = AtomTable::nil;
  freeze_thaw_term(object1, varlist, false, true);

  object2 = varlist;
  return RV_SUCCESS;
}

//
// psi_freeze_var(term)
// Set the temperature tag of a (object) variable to freeze.
// mode(in)
//
Thread::ReturnValue
Thread::psi_freeze_var(Object *& object1)
{
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval1);
    }

  if (! pval1.getTerm()->isAnyVariable() ||
      ! pval1.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object* object = pval1.getTerm();
  if (OBJECT_CAST(Reference *, object)->isThawed())
    {
      trailTag(object);
      OBJECT_CAST(Reference*, object)->freeze();
    }

  return RV_SUCCESS;
}

//
// psi_thaw_var(term)
// Set the temperature tag of a (object) variable to thaw.
// mode(in)
//
Thread::ReturnValue
Thread::psi_thaw_var(Object *& object1)
{
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval1);
    }

  if (! pval1.getTerm()->isAnyVariable() ||
      ! pval1.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object* object = pval1.getTerm();
  if (OBJECT_CAST(Reference *, object)->isFrozen())
    {     
      trailTag(object);
      OBJECT_CAST(Reference*, object)->thaw();
    }
  return RV_SUCCESS;
}

//
// psi_frozen_var(term)
// Succeed if the (object) variable is frozen.
// mode(in)
//
Thread::ReturnValue
Thread::psi_frozen_var(Object *& object1)
{
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  return BOOL_TO_RV(pval1.getTerm()->isAnyVariable() &&
		    OBJECT_CAST(Reference *, pval1.getTerm())->isFrozen());
}

//
// psi_thawed_var(term)
// Succeed if the (object) variable is thawed.
// mode(in)
//
Thread::ReturnValue
Thread::psi_thawed_var(Object *& object1)
{
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  return BOOL_TO_RV(pval1.getTerm()->isAnyVariable() &&
		    OBJECT_CAST(Reference *, pval1.getTerm())->isThawed());
}









