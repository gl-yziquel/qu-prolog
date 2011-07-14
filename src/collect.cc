// collect.cc -
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: collect.cc,v 1.5 2006/01/31 23:17:49 qp Exp $

#include "heap_qp.h"

//
// Collect all (ob)vars from sub into varlist
//
void
Heap::collect_sub_vars(Object* sub, Object*& varlist)
{
  assert(sub->isCons());

  Object* sublist = sub;

  while (sublist->isCons())
    {
      assert(OBJECT_CAST(Cons*, sublist)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* subblock
	= OBJECT_CAST(SubstitutionBlock*, 
		      OBJECT_CAST(Cons*, sublist)->getHead());
      u_int size = static_cast<u_int>(subblock->getSize());

      for (u_int i = 1; i <= size; i++)
	{
	  collect_term_vars(subblock->getRange(i), varlist);
	  collect_term_vars(subblock->getDomain(i), varlist);
	}
      sublist = OBJECT_CAST(Cons*, sublist)->getTail();
    }
  return;
}

//
// Collect all (ob)vars from term into varlist
//
void
Heap::collect_term_vars(Object* term, Object*& varlist)
{
  assert(term->variableDereference()->hasLegalSub());
  term = dereference(term);

  switch (term->tTag())
    {
    case Object::tVar:
    case Object::tObjVar:
      if (!OBJECT_CAST(Reference*, term)->isCollected() &&
	  !term->isLocalObjectVariable())
	{
	  OBJECT_CAST(Reference*, term)->setCollectedFlag();
	  Cons* newlist = newCons(term, varlist);
	  varlist = newlist;
	}
      break;
    case Object::tCons:
      while (term->isCons())
	{
	  collect_term_vars(OBJECT_CAST(Cons*, term)->getHead(), varlist);
  assert(OBJECT_CAST(Cons*, term)->getTail()->variableDereference()->hasLegalSub());
	  term = dereference(OBJECT_CAST(Cons*, term)->getTail());
	}
      collect_term_vars(term, varlist);
      break;
    case Object::tStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	u_int arity = static_cast<u_int>(str->getArity());
	collect_term_vars(str->getFunctor(), varlist);
	for (u_int i = 1; i <= arity; i++)
	  {
	    collect_term_vars(str->getArgument(i), varlist);
	  }
      }
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, term);
	collect_term_vars(quant->getQuantifier(), varlist);
	collect_term_vars(quant->getBoundVars(), varlist);
	collect_term_vars(quant->getBody(), varlist);
      } 
     break;
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      break;
    case Object::tSubst:
      collect_sub_vars(OBJECT_CAST(Substitution*, term)->getSubstitutionBlockList(), varlist);
      collect_term_vars(OBJECT_CAST(Substitution*, term)->getTerm(), varlist);
      break;
    default:
      assert(false);
      break;
    }
  return;
}

//
// Reset collected flag on all variables in list.
//
void
Heap::resetCollectedVarList(Object* varlist)
{
  while (varlist->isCons())
    {
      Object* head = OBJECT_CAST(Cons*, varlist)->getHead();
      assert(head->isAnyVariable());
      assert(OBJECT_CAST(Reference*, head)->isCollected());
      OBJECT_CAST(Reference*, head)->unsetCollectedFlag();
      varlist = OBJECT_CAST(Cons*, varlist)->getTail();
    }
  assert(varlist->isNil());
  return;
}








