// substitution.cc - Contains a set of functions for dealing 
//		    with Qu-Prolog substitution. 
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
// $Id: substitution.cc,v 1.10 2002/07/26 00:39:58 qp Exp $

//#include "atom_table.h"
#include "heap_qp.h"
#include "thread_qp.h"

//
// Copy the spine of a list of substitutions up to the stop point.
// tail_list specifies the new tail of copied version.
//
Object *
Heap::copySubSpine(Object *input_list,
		   Object *stop_list,
		   Object *tail_list)
{
  DEBUG_ASSERT(input_list != NULL);
  DEBUG_ASSERT(stop_list != NULL);
  DEBUG_ASSERT(tail_list != NULL);
  DEBUG_ASSERT(input_list->isNil() ||
	       (input_list->isCons() && 
		OBJECT_CAST(Cons*, input_list)->isSubstitutionBlockList()));
  DEBUG_ASSERT(stop_list->isNil() ||
	       (stop_list->isCons() && 
		OBJECT_CAST(Cons*,stop_list)->isSubstitutionBlockList()));
  DEBUG_ASSERT(tail_list->isNil() ||
	       (tail_list->isCons() && 
		OBJECT_CAST(Cons*, tail_list)->isSubstitutionBlockList()));

  if (input_list == stop_list)
    {
      //
      // Stop point has been reached, return the specified tail.
      // 
      return tail_list;
    }
  else if (input_list->isNil())
    {
      // Should not really get here if stop_list is there
      DEBUG_ASSERT(false);
      return AtomTable::nil;
    }
  else
    {
      // Copy the rest of substitution.
      Object *copy_list = 
	copySubSpine(OBJECT_CAST(Cons *, input_list)->getTail(), 
		     stop_list,
		     tail_list);
      
      DEBUG_ASSERT(OBJECT_CAST(Cons*, input_list)->getHead()->isSubstitutionBlock());
      return newSubstitutionBlockList(OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons *, input_list)->getHead()), copy_list);
    }
}

//
// This function is called from unify. It is to simplify unification problem.
// Example 1.
//	If the unification problem is:
//		[v3/z] * [x/v2] * [v2/y] * [v1/w] * X = t
//
//	Invert will make:
//		X = [w/v1] * [y/v2] * [v2/x] * [z/v3] * t,
//
//	and generate not_free_in problems:
//
//		[v3/z] * [x/v2] * [v2/y] * w not_free_in t
//			 [v3/z] * [x/v2] * y not_free_in t
//					   z not_free_in t
//		
//
// Example 2.
//	If the unification problem is:
//		[v1/y1, v2/y2] * [w1/v3, w2/v4] * [v5/z1, v6/z2] * X = t
//
//	Invert will make:
//		X = [z1/v5, z2/v6] * [v3/w1, v4/w2] * [y1/v1, y2/v2] * t
//
//	and generate not_free_in problems:
//
//			[v1/y1, v2/y2] * [w1/v3, w2/v4] * z1 not_free_in t
//			[v1/y1, v2/y2] * [w1/v3, w2/v4] * z2 not_free_in t
//							  y1 not_free_in t
//							  y2 not_free_in t
//
// NOTE: The order of the inverted substitution is IMPORTANT.
//	 If the original domain is an object variable, a free_in 
//	 test must be done.
//	
bool
Heap::invert(Thread& th, Object *sub_list, PrologValue& term)
{
  DEBUG_ASSERT(sub_list->isNil() ||
	       (sub_list->isCons() && 
		OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList() &&
		OBJECT_CAST(Cons*, sub_list)->isInvertible()));

  Object *inverted_sub_list = AtomTable::nil;
  
  // Swap domains and ranges, and swap pointers in substitution 'sub'.
  for (Object *list = sub_list;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      
      DEBUG_ASSERT(sub->getSize() > 0);
      
      // Set up the inverted substitution block
      SubstitutionBlock *inverted_sub = 
	newSubstitutionBlock(sub->getSize());
      inverted_sub->makeInvertible();
      
      // Check whether the first domain is local object variable.
      // If it is the case then all the other domains are local
      // object variables, and there is no need to check them all.
      const bool do_freeness = ! sub->getDomain(1)->isLocalObjectVariable();
      
      for (size_t i = 1; i <= sub->getSize(); i++)
	{
	  // Invert domains and ranges.
          DEBUG_ASSERT(sub->getRange(i)->isObjectVariable());
	  inverted_sub->setDomain(i, sub->getRange(i));
	  inverted_sub->setRange(i, sub->getDomain(i));
	  if (do_freeness)
	    {
	      // Do free in test for ordinary object variable.
	      PrologValue object_variable(OBJECT_CAST(Cons*, list)->getTail(),
					  sub->getDomain(i));
	      if (! th.internalNotFreeIn(object_variable, term))
		{
		  return false;
		}
	    }
	  inverted_sub_list = newSubstitutionBlockList(inverted_sub,
						       inverted_sub_list);
	}
    }
  // Add term substitution to the right of inverted substitution - 'sub'.
  term.setSubstitutionBlockList(
         appendSubstitutionBlockLists(term.getSubstitutionBlockList(), 
				      inverted_sub_list));
  return true;
}

//
// Used to invert sub to transform sub * x not_free_in term into
// x not_free_in sub-1 * term .
//
// NOTE: no extra not_free_in conditions are added.
//	
void
Heap::invertWithoutNFI(Object *sub, PrologValue& term)
{
  DEBUG_ASSERT(sub->isNil() ||
	       (sub->isCons() && 
		OBJECT_CAST(Cons*, sub)->isSubstitutionBlockList()));

  Object *inverted_sub_list = AtomTable::nil;
  
  // Swap domains and ranges, and swap pointers in substitution 'sub'.
  for (Object *list = sub;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      
      DEBUG_ASSERT(sub->getSize() > 0);
      
      // Set up the inverted substitution block
      SubstitutionBlock *inverted_sub = newSubstitutionBlock(sub->getSize());
      inverted_sub->makeInvertible();
      
      for (size_t i = 1; i <= sub->getSize(); i++) 
	{
	  // Invert domains and ranges.
          DEBUG_ASSERT(sub->getRange(i)->isObjectVariable());
	  inverted_sub->setDomain(i, sub->getRange(i));
	  inverted_sub->setRange(i, sub->getDomain(i));
	}
      
      inverted_sub_list = newSubstitutionBlockList(inverted_sub,
						   inverted_sub_list);
    }
  
  
  // Add term substitution to the right of inverted substitution - 'sub'.
  term.setSubstitutionBlockList(appendSubstitutionBlockLists(term.getSubstitutionBlockList(), inverted_sub_list));
}

//
// If a term has a non-empty substitution, create a new SUBSTITUTION_OPERATOR
// and assign substitution and term. If term has an empty substitution then 
// just return the term part.
// 
Object *
Heap::prologValueToObject(PrologValue& term)
{
  if (term.getSubstitutionBlockList()->isNil())
    {
      return term.getTerm();
    }
  else
    {
      Substitution *sub = newSubstitution();
      
      sub->setSubstitutionBlockList(term.getSubstitutionBlockList());
      sub->setTerm(term.getTerm());
      
      return sub;
    }
}

//
// Check whether the local object variable occurs in a range position
// of any substitution from the composition of substitutions. 
//	
bool
Heap::isLocalInRange(Object *local_object_variable,
		     Object *sub_list)
{
  DEBUG_ASSERT(local_object_variable->isLocalObjectVariable());
  DEBUG_ASSERT(sub_list->isNil() ||
	       (sub_list->isCons() && 
		OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList()));
  
  for (Object *list = sub_list;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      DEBUG_ASSERT(sub->getSize() > 0);
      
      // Check whether the first range is a local object variable.
      // If it is the case then all the other ranges are local
      // object variables, so search for the local object variable
      // among ranges, otherwise skip to the next substitution.
      if (sub->getRange(1)->isLocalObjectVariable())
	{
	  // Search for the local object variable as a range. 
	  for (size_t i = 1; i <= sub->getSize(); i++)
	    {
	      if (local_object_variable == sub->getRange(i)) 
		{
		  return true;
		}
	    }
	}
    } 
  return false;
}

//
// Copy the substitution block before any destructive processing is
// performed.  The range elements are replaced by $'s.
// Only the part of the substitution up to size is copied.
//
Object *
Heap::copySubstitutionBlockWithDollars(Object *sub_list, size_t size)
{
  DEBUG_ASSERT(sub_list->isNil() ||
	       (sub_list->isCons() &&
		OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList()));
  
  if (size == 0)
    {
      return (OBJECT_CAST(Cons*, sub_list)->getTail());
    }
  DEBUG_ASSERT(OBJECT_CAST(Cons*, sub_list)->getHead()->isSubstitutionBlock());
  SubstitutionBlock *sub = OBJECT_CAST(SubstitutionBlock*,
				       OBJECT_CAST(Cons*, sub_list)->getHead());
  
  SubstitutionBlock *new_sub = newSubstitutionBlock(size);
  
  for (size_t i = 1; i <= size; i++)
    {
      new_sub->setDomain(i, sub->getDomain(i)); 
      new_sub->setRange(i, AtomTable::dollar);
    }
  
  return newSubstitutionBlockList(new_sub, 
				  OBJECT_CAST(Cons*, sub_list)->getTail());
}



//
// Test to see if an object variable is NFI in the ranges of inner subs
// or term part of a substituted term
//
bool
Heap::canRemove(Thread& th, Object* obvar, int index, 
		SubstitutionBlock** subarray, Object* term)
{
  obvar = obvar->variableDereference();
  DEBUG_ASSERT(obvar->isObjectVariable());
  ObjectVariable* ov = OBJECT_CAST(ObjectVariable*, obvar);
  for (int i = index; i >= 0; i--)
    {
      if (subarray[i] == NULL)
        {
          continue;
        }
      size_t size = subarray[i]->getSize();
      bool found = false;
      for (size_t j = 1; j <= size; j++)
	{
	  if (!th.fastNFITerm(ov, subarray[i]->getRange(j)->variableDereference()))
	    {
	      return false;
	    }
	  if (subarray[i]->getDomain(j) == ov)
	    {
	      found = true;
	    }
	}
      if (found)
	{
	  return true;
	}
    }
  return th.fastNFITerm(ov, term->variableDereference());
}

//
// Remove useless entry from a substitution wherever it is possible.
// Assumed to be (Prolog) dereferenced and the term part is either
// a variable or object variable.

void
Heap::dropSubFromTerm(Thread& th, PrologValue& pterm)
{
  DEBUG_CODE({
    Object* remterm = pterm.getTerm();
    Object* remsub = pterm.getSubstitutionBlockList();
    prologValueDereference(pterm);
    DEBUG_ASSERT(remterm == pterm.getTerm());
    DEBUG_ASSERT(remsub == pterm.getSubstitutionBlockList());
  }
	     );
  Object* term = pterm.getTerm();
  Object *sub = pterm.getSubstitutionBlockList();

  bool changed = false;

  DEBUG_ASSERT(!sub->isNil());

  // get the number of sub blocks
  int size = 0;
  for (Object* tmp = sub;
       tmp->isCons();
       tmp = OBJECT_CAST(Cons *, tmp)->getTail())
    {
      size++;
    }

  SubstitutionBlock* subarray[size];

  // Fill subarray with blocks
  int index = 0;
  for (;
       sub->isCons();
       sub = OBJECT_CAST(Cons *, sub)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, sub)->getHead()->isSubstitutionBlock());
      subarray[index++] = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, sub)->getHead());
    }

  // Process the sub blocks
  for (int i = 0; i < size; i++)
    {
      if (subarray[i]->getDomain(1)->isLocalObjectVariable())
	{
	  // check if matching sub
	  bool found = false;
	  for (int j = i-1; j >= 0; j--)
	    {
	      if ((subarray[j] != NULL)
		  && (subarray[j]->getRange(1) == subarray[i]->getDomain(1)))
		{
		  found = true;
		  break;
		}
	    }
	  // If there is no matching sub then this sub can be removed
	  if (!found)
	    {
	      subarray[i] = NULL;
	      changed = true;
	    }
	}
      else if (subarray[i]->getRange(1)->isLocalObjectVariable())
	{
	  //
	  // To preserve the invariant that substitutions with
	  // locals as a single unit.  Entries within a
	  // substitution cannot be removed one by one.
	  // This is an attempt to remove the whole block for
	  // s*A.  s*x is handled by dereference as part of the
	  // substitution evaluation process.
	  //
	  
	  bool remove = true;
	  for (int k = subarray[i]->getSize(); k > 0; k--)
	    {
	      if (!canRemove(th, subarray[i]->getDomain(k), i-1, 
			     subarray, term))
		{
		  remove = false;
		  break;
		}
	    }
	  if (remove)
	    {
	      subarray[i] = NULL;
	      changed = true;
	    }
	}
      else
	{
	  // try to remove individual components of a sub
	  int blocksize = subarray[i]->getSize();
	  Object* doms[blocksize];
	  Object* rans[blocksize];
	  for (int k = 0; k < blocksize; k++)
	    {
	      doms[k] = subarray[i]->getDomain(k+1)->variableDereference();
	      rans[k] = subarray[i]->getRange(k+1)->variableDereference();
	    }
	  int finalsize = blocksize;
	  // Remove entries which have no effect - i.e. they are
	  // NFI in inner sub and term
	  for (int k = 0; k < blocksize; k++)
	    {
	      if (canRemove(th, doms[k], i-1, subarray, term))
		{
		  doms[k] = NULL;
		  finalsize--;
		  changed = true;
		}
	    }
	  // Now try and remove entries of the form x/x
	  for (int k = 0; k < blocksize; k++)
	    {
	      if (doms[k] == rans[k])
		{
		  DEBUG_ASSERT(doms[k] != NULL);
		  bool del = true;
		  for (int p = k-1; p >= 0; p--)
		    {
		      DEBUG_ASSERT(doms[k] == doms[k]->variableDereference());
		      if (doms[p] == NULL)
			{
			  continue;
			}
		      if (!OBJECT_CAST(ObjectVariable*, doms[k])->distinctFrom(doms[p]))
			{
			  del = false;
			  break;
			}
		    }
		  if (del)
		    {
		      doms[k] = NULL;
		      finalsize--;
		      changed = true;
		    }
		}
	    }
	  if (finalsize == 0)
	    {
	      subarray[i] = NULL;
	    }
	  else
	    {
	      DEBUG_ASSERT(finalsize > 0);
	      subarray[i] = newSubstitutionBlock(finalsize);
	      int pos = 1;
	      for (int k = 0; k < blocksize; k++)
		{
		  if (doms[k] != NULL)
		    {
		      subarray[i]->setDomain(pos, doms[k]);
		      subarray[i]->setRange(pos, rans[k]);
		      pos++;
		    }
		}
	    }
	}
    }
	  
  if (changed)
    {
      // Rebuild sub
      Object* subst = AtomTable::nil;
      for (int i = size-1; i >= 0; i--)
	{
	  if (subarray[i] != NULL)
	    {
	      subst = newSubstitutionBlockList(subarray[i], subst);
	    }
	}
      pterm.setSubstitutionBlockList(subst);
      th.TheHeap().prologValueDereference(pterm);
      if (term != pterm.getTerm() &&
	  pterm.getSubstitutionBlockList()->isCons())
	{
	  dropSubFromTerm(th, pterm);
	}
      DEBUG_ASSERT(pterm.getTerm() == pterm.getTerm()->variableDereference());
    }
}

