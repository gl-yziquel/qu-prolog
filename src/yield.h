// yield.h - The Qu-Prolog yield procedures. 
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
// $Id: yield.h,v 1.3 2005/06/29 22:05:35 qp Exp $

#ifndef	YIELD_H
#define	YIELD_H

private:
typedef bool (*YieldCond)(Heap*, PrologValue&, Object *);

//
// Check whether the substitution list yields the term.
//
bool yield(Object *term, Object *sub_block_list,
	   YieldCond, ThreadStatus&);

//
// Extra condition for yield constant.
//
static bool yieldConstantCond(Heap* heapPtr, PrologValue& range, 
                              Object *constant)
{
  return (range.getTerm()->isConstant() &&
	  constant->equalConstants(range.getTerm()));
}

//
// Extra condition for yield variable.
//
static bool yieldVarCond(Heap* heapPtr, PrologValue& range, Object *variable)
{
  return (variable == range.getTerm());
}      

//
// Extra condition for yield structure.
//
static bool yieldStructureCond(Heap*, PrologValue&, Object *);

//
// Extra condition for yield list.
//
static bool yieldListCond(Heap* heapPtr, PrologValue& range, Object*)
{
  return range.getTerm()->isCons();
}

//
// Extra condition for yield quantifier.
//
static bool yieldQuantifierCond(Heap*, PrologValue&, Object *);

public:
//
// Check whether the substitution yields the constant.
//
bool yieldConstant(Object *constant,
		   Object *sub_block_list, 
		   ThreadStatus& status)
{
  return yield(constant, sub_block_list, &yieldConstantCond, status); 
}

//
// Check whether the substitution yields the variable.
//
bool yieldVariable(Object *variable,
		   Object *sub_block_list, 
		   ThreadStatus& status)
{
  return yield(variable, sub_block_list, &yieldVarCond, status); 
}

//
// Check whether the substitution yields the structure.
// 
bool yieldStructure(Object *structure,
		    Object *sub_block_list,
		    ThreadStatus& status)
{
  return yield(structure, sub_block_list, &yieldStructureCond, status); 
}

//
// Check whether the substitution yields the list.
// 
bool yieldList(Object *list,
	       Object *sub_block_list, 
	       ThreadStatus& status)
{
  return yield(list, sub_block_list, &yieldListCond, status); 
}

//
// Check whether the substitution yields the quantifier.
// 
bool yieldQuantifier(Object *quantified_term,
		     Object *sub_block_list,
		     ThreadStatus& status)
{
  return yield(quantified_term, sub_block_list, &yieldQuantifierCond, status); 
}

//
// Check whether the substitution yields the object variable.
//
bool yieldObjectVariable(Object *ObjectVariable,
			 Object *sub_block_list,
			 ThreadStatus& status);

#endif	// YIELD_H

