// equal_escape.cc - an escape function to call fastEqual.
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
// $Id: equal_escape.cc,v 1.6 2006/01/31 23:17:50 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
#include "truth3.h"

//
// psi_fast_equal(term1,term2,status)
// returns true iff term1 and term2 have the same structure.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_fast_equal(Object *& object1, Object *& object2, Object *& object3)
{
  truth3		res;
  assert(object1->hasLegalSub());
  assert(object2->hasLegalSub());
  PrologValue  pval1(object1);
  PrologValue  pval2(object2);

  res = heap.fastEqual(pval1, pval2);
  if (res == false)
    {
      return(RV_FAIL);
    }
  else if (res == true)
    {
      object3 = AtomTable::success;
    }
  else
    {
      object3 = AtomTable::unsure;
    }
  
  return(RV_SUCCESS);
}


//
// psi_equal_equal(term1,term2)
// returns true iff term1 == term2 .
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_equal_equal(Object *& term1, Object *& term2)
{
  PrologValue  pval1(term1);
  PrologValue  pval2(term2);
  heap.prologValueDereference(pval1);
  heap.prologValueDereference(pval2);

  int counter = 0;
  quick_tidy_check = true;
  bool result = equalEqual(pval1, pval2, counter);
  quick_tidy_check = false;
  return BOOL_TO_RV(result);
}


//
// psi_simplify_term(term1,term2)
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_simplify_term(Object *& term1, Object *& term2)
{
  PrologValue pterm(term1);
  quick_tidy_check = true;
  (void)simplify_term(pterm, term2);
  quick_tidy_check = false;
  return RV_SUCCESS;
}


//
// psi_simplify_term3(term1,term2, issimp)
// mode(in,out,out)
//
Thread::ReturnValue
Thread::psi_simplify_term3(Object *& term1, Object *& term2, Object *& issimp)
{
  PrologValue pterm(term1);
  quick_tidy_check = true;
  bool result = simplify_term(pterm, term2);
  quick_tidy_check = false;
  if (result)
    {
      issimp = AtomTable::success;
    }
  else
    {
      issimp = AtomTable::failure;
    }
  return RV_SUCCESS;
}

//
// test for term1 \= term2
//
// mode(in, in)
//
Thread::ReturnValue
Thread::psi_not_equal(Object *& term1, Object *& term2)
{
  // Save state
  heapobject* savesavedtop = heap.getSavedTop();
  heapobject* savedHT = heap.getTop();
  TrailLoc savedBindingTrailTop = bindingTrail.getTop();
  TrailLoc savedOtherTrailTop = otherTrail.getTop();
  heap.setSavedTop(savedHT);

  bool result = unify(term1, term2);

  // Restore state
  heap.setTop(savedHT);
  bindingTrail.backtrackTo(savedBindingTrailTop);
  assert(bindingTrail.check(heap));
  otherTrail.backtrackTo(savedOtherTrailTop);
  assert(otherTrail.check(heap));

  if (result) return RV_FAIL;
  else return RV_SUCCESS;
}
