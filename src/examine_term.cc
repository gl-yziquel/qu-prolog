// examine_term.cc - The QU-Prolog functions which have to do with examining
//		     or testing the type of a term. 
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
// $Id: examine_term.cc,v 1.7 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

//
// psi_collect_vars(term, list)
// Collect all the variables (and object_variables) in term into list
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_collect_vars(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* varlist = AtomTable::nil;

  heap.collect_term_vars(val1, varlist);
  heap.resetCollectedVarList(varlist);
  object2 = varlist;

  return(RV_SUCCESS);
}

//
// psi_var(term)
// True if term is a variable, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_var(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isVariable())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isVariable()));
}

//
// psi_atom(term)
// True if term is an atom, false otherwise
// mode(in)
//
Thread::ReturnValue 
Thread::psi_atom(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  return (BOOL_TO_RV(val1->isAtom()));
}

//
// psi_integer(term)
// True if term is an integer, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_integer(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isInteger()));
}

//
// psi_float(term)
// True if term is a float, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_float(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isDouble()));
}

//
// psi_atomic(term)
// True if term is atomic, false otherwise
// mode(in)
//
Thread::ReturnValue 
Thread::psi_atomic(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return (BOOL_TO_RV(val1->isAtom() || val1->isNumber()));
}

// psi_any_variable(term)
// True if term is a variable or object variable, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_any_variable(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isAnyVariable())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isAnyVariable()));
}

//
// psi_simple(term)
// True if term is any variable or atomic, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_simple(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isAnyVariable() || val1->isConstant())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isAnyVariable()));
}

//
// psi_nonvar(term)
// True if term is not a variable, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_nonvar(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isVariable())
    {
      return RV_FAIL;
    }
  else if (!val1->isSubstitution())
    {
      return RV_SUCCESS;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(!pval1.getTerm()->isVariable()));
}

//
// psi_std_var(term)
// True if term is a variable with no subs, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_std_var(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isVariable()));
}

//
// psi_std_compound(term)
// True if term is compound with an atom functor, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_std_compound(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1); 

  if (val1->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, val1);
      return(BOOL_TO_RV(str->getFunctor()->isAtom()));
    }
  else
    {
      return (BOOL_TO_RV(val1->isCons()));
    }
}


//
// psi_std_nonvar(term)
// True if term is atomic or std_compound, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_std_nonvar(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1); 

  
  if (val1->isAtom() || val1->isNumber())
    {
      return(RV_SUCCESS);
    }
  else if (val1->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, val1);
      return(BOOL_TO_RV(str->getFunctor()->isAtom()));
    }
  else
    {
      return (BOOL_TO_RV(val1->isList()));
    }
}

//
// psi_list(term)
// True if term is a list, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_list(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  if (val1->isList())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isList()));
}

// psi_string(term)
// True if term is a string, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_string(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isString() || (val1 == AtomTable::nil)));
}

//
// psi_fast_simplify(term, simpterm)
// do a simple term simplification
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_fast_simplify(Object *& object1, Object *& object2)
{
  PrologValue pv(object1);
  (void)occursCheckAndSimplify(ALL_CHECK, pv, object2, NULL);
  return RV_SUCCESS;
}








