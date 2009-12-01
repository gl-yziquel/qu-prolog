// delay_qp.h - Routines for placing different types of problem in delay queue.
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: delay_qp.h,v 1.4 2002/03/22 02:48:41 qp Exp $

#ifndef	DELAY_QP_H
#define	DELAY_QP_H

public:

enum  delaytype      { NOSIMPNFI , NFI, BOTH };

//
// Given a unification problem
// [tm/xm,...,t1/x1]A = [un/yn,.../u1/y1]A
// make xi nfi A if [[un/yn,.../u1/y1] does not yield ti 
// 
bool stripUnmatchedSubsFirst(PrologValue& var1, PrologValue& var2);

inline void stripUnmatchedSubs(PrologValue& var1, PrologValue& var2)
{
  if (stripUnmatchedSubsFirst(var1, var2) ||
      stripUnmatchedSubsFirst(var2, var1))
    {
      heap.prologValueDereference(var1);
      heap.prologValueDereference(var2);
      if (var1.getSubstitutionBlockList()->isCons())
	{
	  heap.dropSubFromTerm(*this, var1);
	}
      if (var2.getSubstitutionBlockList()->isCons())
	{
	  heap.dropSubFromTerm(*this, var2);
	}
    }
}

//
// Generate not_free_in constraints for the ranges and term.
//
void generateNFIConstraints(ObjectVariable *, PrologValue&);

//
// Remove any sub of the form [vm/xm, ..., v1/x1] from term1 or term2 that is
// not cancelled  by a later sub or does not have a corresponding (uncancelled)
// sub in the other term.
// Add subs of the form [ym/vm, ..., y1/v1] to both sides for any uncancelled
// subs.
bool balanceLocals(PrologValue&, PrologValue&);

//
// Check if delayed problem is associated with variable.
//
bool isDelayProblem(Object *, Object *);

//
// Add the delayed problem to the delayed queue associated with the variable.
//
void delayProblem(Object *, Object *);

//
// Delay an unification problem.
//
void delayUnify(PrologValue&, PrologValue&, Object *);

//
// Delay a not free in problem.
//
void delayNFI(ObjectVariable *,
	      PrologValue&,
	      Object *);

//
// Check for a not free in problem.
//
bool isDelayNFI(Object *, Object *);

//
// Wake up any delayed problems associated with the given (object) reference.
//
void wakeUpDelayedProblems(Object *);


//
// Retry the delayed problems - 
// type = NOSIMPNFI then retry only NFI problems but don't simplify 
// type = NFI then retry NFI problems 
// type = BOTH then retry NFI and = problems
//
bool retry_delays(delaytype type = NOSIMPNFI);

#endif	// DELAY_QP_H


