// yield.cc -	The Qu-Prolog yield procedures. 
//		A substitution can yield a specified term if one of the 
//		following is true:
//		   1. The specified term is in the range.
//		   2. A variable is in the range.
//		   3. An thawed object variable is in the range and its 
//		      substitution yields the specified term.
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
// $Id: yield.cc,v 1.5 2006/01/31 23:17:52 qp Exp $

#include        "heap_qp.h"

//
// Check whether the substitution yields the term.
//
bool
Heap::yield(Object *term,
	    Object *sub_block_list,
	    YieldCond cond,
	    ThreadStatus& status)
{
  assert(sub_block_list->isNil() ||
	       (sub_block_list->isCons() && 
		OBJECT_CAST(Cons *,sub_block_list)->isSubstitutionBlockList()));

  for (Object *s = sub_block_list;
       s->isCons();
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      assert(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub_block = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s)->getHead());

      if (sub_block->isInvertible())
	{
	  //
	  // All ranges are object variables, so the 
	  // substitution cannot yield the term.
	  // 
	  continue;
	}
      else
	{
	  assert(sub_block->getSize() > 0);

	  for (size_t i = 1; i <= sub_block->getSize(); i++)
	    {
              assert(sub_block->getRange(i)->hasLegalSub());
	      PrologValue range(sub_block->getRange(i));
	      prologValueDereference(range);

	      if ((range.getTerm()->isVariable() && 
		   (status.testHeatWave() ||
		    ! OBJECT_CAST(Variable*, range.getTerm())->isFrozen())) || 
		  (*cond)(this, range, term) ||
		  (range.getTerm()->isObjectVariable() &&
		   yield(term, range.getSubstitutionBlockList(), cond, status)))
		{
		  //
		  // Frozen variable is like a constant 
		  // which is always different from any 
		  // other. Object variable cannot be 
		  // bound to other then object variable,
		  // so only substitution can yield the
		  // term.
		  //
		  return true;
		}
	    }
	}
    }
  return false;
}

//
// Extra condition for yield structure.
//
bool
Heap::yieldStructureCond(Heap* heapPtr, PrologValue& range,
			 Object *str)
{
  assert(str->isStructure());
  Structure* structure = OBJECT_CAST(Structure*, str);
  if (! (range.getTerm()->isStructure() &&
	 OBJECT_CAST(Structure *, range.getTerm())->getArity() == structure->getArity())) 
    {
      return false;
    }
  else
    {
      Structure *range_structure = OBJECT_CAST(Structure *, range.getTerm());

      PrologValue range_fn(range.getSubstitutionBlockList(),
			   range_structure->getFunctor());
  
      heapPtr->prologValueDereference(range_fn);
      PrologValue struct_fn(heapPtr->dereference(structure->getFunctor()));

      return (! range_fn.getTerm()->isAtom() || 
	      ! struct_fn.getTerm()->isAtom() || 
	      range_fn.getTerm() == struct_fn.getTerm());
    }
}

//
// Extra condition for yield quantifier.
//
bool
Heap::yieldQuantifierCond(Heap* heapPtr, PrologValue& range,
			  Object *q)
{
  assert(q->isQuantifiedTerm());
  QuantifiedTerm* quantified_term = OBJECT_CAST(QuantifiedTerm*, q);
  if (! range.getTerm()->isQuantifiedTerm())
    {
      return false;
    }
  else
    {
      QuantifiedTerm *range_quantified_term =
	OBJECT_CAST(QuantifiedTerm *, range.getTerm());

      PrologValue range_q(range.getSubstitutionBlockList(),
			  range_quantified_term->getQuantifier());
      heapPtr->prologValueDereference(range_q);

      PrologValue quant_q(quantified_term->getQuantifier());

      return (! range_q.getTerm()->isAtom() || 
	      ! quant_q.getTerm()->isAtom() || 
	      range_q.getTerm() == quant_q.getTerm());
    }
}

//
// Check whether the substitution yields the object variable.
//
bool
Heap::yieldObjectVariable(Object *object_variable,
			  Object *sub_block_list,
			  ThreadStatus& status)
{
  assert(object_variable->isObjectVariable());
  for (Object *s = sub_block_list;
       s->isCons();
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      assert(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s)->getHead());
      assert(sub->getSize() > 0);

      for (size_t i = 1; i <= sub->getSize(); i++)
	{
          assert(sub->getRange(i)->variableDereference()->hasLegalSub());
	  PrologValue range(dereference(sub->getRange(i)));

	  if ((range.getTerm()->isVariable() && 
	       (status.testHeatWave() || 
		! OBJECT_CAST(Variable*, range.getTerm())->isFrozen())) || 
	      (range.getTerm()->isObjectVariable() &&
	       (! range.getTerm()->distinctFrom(object_variable) ||
		yieldObjectVariable(object_variable,
				    range.getSubstitutionBlockList(),
				    status))))
	    {
	      return true;
	    }
	}
    }

  return false;
}


