// free_in.cc -	"free_in" escape test functions.
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
// $Id: free_in.cc,v 1.5 2006/01/31 23:17:50 qp Exp $

#include        "thread_qp.h"
 
//
// psi_not_free_in(object_variable, term)
// Execute the not free in constraint.  The problem can succeed, fail or delay.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in(Object *& object1, Object *& object2)
{
  assert(object2->hasLegalSub());
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
  
  assert(obvar->isObjectVariable());

  quick_tidy_check = true;
  bool result = notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), pval2);
  quick_tidy_check = false;
  return (BOOL_TO_RV(result));
}

//
// psi_not_free_in_var_simplify(object_variable, var)
// Simplify the substitution associated with var and apply not free in.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in_var_simplify(Object *& object1, Object *& object2)
{
  assert(object2->hasLegalSub());
  PrologValue	pval2(object2);
  
  Object* obvar = object1->variableDereference();
  heap.prologValueDereference(pval2);

#ifndef NDEBUG
  Object *sub_block_list = pval2.getSubstitutionBlockList();
  assert(! sub_block_list->isNil());
  assert(OBJECT_CAST(Cons* , sub_block_list)->getTail()->isNil());
#endif
  assert(obvar->isObjectVariable()); 


  if (pval2.getTerm()->isAnyVariable())
    {
      quick_tidy_check = true;
      bool result = notFreeInVarSimp(OBJECT_CAST(ObjectVariable*, obvar),pval2);
      quick_tidy_check = false;
      return(BOOL_TO_RV(result));
    }
  else
    {
      quick_tidy_check = true;
      bool result = notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), pval2);
      quick_tidy_check = false;
      return(BOOL_TO_RV(result));
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
  assert(ov->isObjectVariable());
  assert(term->hasLegalSub());
  PrologValue pv(term);
  quick_tidy_check = true;
  bool result = notFreeInNFISimp(OBJECT_CAST(ObjectVariable*, ov), pv);
  quick_tidy_check = false;
  return(BOOL_TO_RV(result));
}  

//
// is_not_free_in
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_is_not_free_in(Object*& obvar, Object*& term)
{
  Object* ov = obvar->variableDereference();
  assert(ov->isObjectVariable());
  assert(term->hasLegalSub());
  PrologValue pv(term);
  quick_tidy_check = true;
  truth3 result = freeness_test(OBJECT_CAST(ObjectVariable*, ov), pv);
  quick_tidy_check = false;
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
  assert(ov->isObjectVariable());
  assert(term->hasLegalSub());
  PrologValue pv(term);
  quick_tidy_check = true;
  truth3 result = freeness_test(OBJECT_CAST(ObjectVariable*, ov), pv);
  quick_tidy_check = false;
  return(BOOL_TO_RV(result == true));
}  





