// free_in.cc -	"free_in" escape test functions.
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
// $Id: free_in.cc,v 1.3 2001/09/20 03:22:06 qp Exp $

#include        "thread_qp.h"
 
//
// psi_not_free_in(object_variable, term)
// Execute the not free in constraint.  The problem can succeed, fail or delay.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object2->hasLegalSub());
  PrologValue	pval2(object2);
  
  Object* obvar = object1->variableDereference();
  
  if (obvar->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (!obvar->isObjectVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
      
  heap.prologValueDereference(pval2);
  
  DEBUG_ASSERT(obvar->isObjectVariable());
  
  return (BOOL_TO_RV(notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), pval2)));
}

//
// psi_not_free_in_var_simplify(object_variable, var)
// Simplify the substitution associated with var and apply not free in.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in_var_simplify(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object2->hasLegalSub());
  PrologValue	pval2(object2);
  
  Object* obvar = object1->variableDereference();
  heap.prologValueDereference(pval2);

DEBUG_CODE(
{
  Object *sub_block_list = pval2.getSubstitutionBlockList();
  DEBUG_ASSERT(! sub_block_list->isNil());
  DEBUG_ASSERT(OBJECT_CAST(Cons* , sub_block_list)->getTail()->isNil());
}
);
  DEBUG_ASSERT(obvar->isObjectVariable()); 


  if (pval2.getTerm()->isAnyVariable())
    {
      return(BOOL_TO_RV(notFreeInVarSimp(OBJECT_CAST(ObjectVariable*, obvar),
				         pval2)));
    }
  else
    {
      return(BOOL_TO_RV(notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), 
                                  pval2)));
    }
}

Thread::ReturnValue
Thread::psi_addExtraInfoToVars(Object*& term)
{
  addExtraInfoToVars(term);
  return RV_SUCCESS;
}

//
// Call notFreeInNFISimp
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in_nfi_simp(Object*& obvar, Object*& term)
{
  Object* ov = obvar->variableDereference();
  DEBUG_ASSERT(ov->isObjectVariable());
  DEBUG_ASSERT(term->hasLegalSub());
  PrologValue pv(term);
 
  return(BOOL_TO_RV(notFreeInNFISimp(OBJECT_CAST(ObjectVariable*, ov), pv)));
}  

//
// is_not_free_in
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_is_not_free_in(Object*& obvar, Object*& term)
{
  Object* ov = obvar->variableDereference();
  DEBUG_ASSERT(ov->isObjectVariable());
  DEBUG_ASSERT(term->hasLegalSub());
  PrologValue pv(term);
 
  truth3 result = freeness_test(OBJECT_CAST(ObjectVariable*, ov), pv);
  
  return(BOOL_TO_RV(result == false));
}  


//
// is_free_in
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_is_free_in(Object*& obvar, Object*& term)
{
  Object* ov = obvar->variableDereference();
  DEBUG_ASSERT(ov->isObjectVariable());
  DEBUG_ASSERT(term->hasLegalSub());
  PrologValue pv(term);
 
  truth3 result = freeness_test(OBJECT_CAST(ObjectVariable*, ov), pv);
  
  return(BOOL_TO_RV(result == true));
}  





