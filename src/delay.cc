// delay.cc - Routines for placing different types of problem in delay queue.
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
// $Id: delay.cc,v 1.10 2002/03/27 23:23:47 qp Exp $

// #include "atom_table.h"
#include "global.h"
#include "objects.h"
#include "thread_qp.h"

//
// The Layout of Delayed Problems
//
// +------------+     
// | VARIABLE   |                   +------------+   +------------+
// +------------+                   | STRUCTURE	-+-> |     ,/2    |
// | DELAY LIST | ----------------> | LIST     | |   | REFERENCE -+-> (status)
// +------------+   		    +----------+-+   |		 -+-> (problem)
//      ^	            		       |     +------------+
//      |		         	       v
//      |		        	       ...
//      |
//      |	        	+------------+
//      |		        |     ,/2    |<-+
//      |             (status)<-+- REFERENCE |  |
//	+-----------------------+- REFERENCE |  |
//				+------------+  |
//						|
//			+-------+   +-----------++
// $delayed_problems =	| LIST -+-> | STRUCTURE	||
//			+-------+   | LIST      -+--> ...
//				    +------------+
//
// New delayed problem is added to the front of list associated with 
// the variable.
// New delayed variable is added to the front of $delayed_problems.
//


//
// Given a unification problem
// [tm/xm,...,t1/x1]A = [un/yn,.../u1/y1]A
// make xi nfi A if [[un/yn,.../u1/y1] does not yield ti 
// 
bool
Thread::stripUnmatchedSubsFirst(PrologValue& var1, PrologValue& var2)
{
  // First check if sub of var1 is more than one sub block.
  // If so then compress into a single sub.
  Object *sub_list = var1.getSubstitutionBlockList();
  if (!sub_list->isCons())
    {
      //empty sub so do nothing
      return false;
    }
  size_t size = 0;
  for ( ; sub_list->isCons();
	sub_list = OBJECT_CAST(Cons *, sub_list)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, sub_list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub 
	= OBJECT_CAST(SubstitutionBlock*,
		      OBJECT_CAST(Cons *, sub_list)->getHead());
      size += sub->getSize();
    }
  Object* doms[size];
  Object* rans[size];
  size_t position = 0;
  sub_list = var1.getSubstitutionBlockList();
  for ( ; sub_list->isCons();
	sub_list = OBJECT_CAST(Cons *, sub_list)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, sub_list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub 
	= OBJECT_CAST(SubstitutionBlock*,
		      OBJECT_CAST(Cons *, sub_list)->getHead());
      size_t subsize = sub->getSize();
      for (size_t i = 1; i <= subsize; i++)
	{
	  Object* domain = sub->getDomain(i)->variableDereference();
	  // check if domain is local
	  if (domain->isLocalObjectVariable())
	    {
	      size--;
	      continue;
	    }
	  // check if domain already listed in doms
	  bool found = false;
	  for (size_t j = 0; j < position; j++)
	    {
	      if (domain == doms[j])
		{
		  found = true;
		  break;
		}
	    }
	  if (!found)
	    {
	      doms[position] = domain; 
	      PrologValue range(OBJECT_CAST(Cons *, sub_list)->getTail(),
				sub->getRange(i));
	      heap.prologValueDereference(range);
	      rans[position] = heap.prologValueToObject(range);
	      position++;
	    }
	  else
	    {
	      size--;
	    }
	}
    }
  DEBUG_ASSERT(size > 0);
  bool found = false;
  
  int finalsize = size;
  for (int i = 0; i < (int)size; i++)
    {
      PrologValue sub_t(rans[i]);
      heap.prologValueDereference(sub_t);
      Object* term = sub_t.getTerm();
      bool makenfi = false;
      switch(term->utag()) 
	{
	case Object::uVar:
	  {
	    makenfi = 
	      (term->isFrozenVariable() &&
	       !heap.yieldVariable(term, var2.getSubstitutionBlockList(),
				   status));
	  }
	  break;
	case Object::uCons:
	  {
	    makenfi = 
	      (!heap.yieldList(term, var2.getSubstitutionBlockList(),
			       status));
	  }
	  break;
	case Object::uStruct:
	  {
	    makenfi = 
	      (!heap.yieldStructure(term, var2.getSubstitutionBlockList(),
				    status));
	  }
	  break;
	case Object::uQuant:
	  {
	    makenfi =
	      (!heap.yieldQuantifier(term, 
				     var2.getSubstitutionBlockList(),
				     status));
	  }
	  break;
	case Object::uConst:
	  {
	    makenfi = 
	      (!heap.yieldConstant(term, var2.getSubstitutionBlockList(),
				   status));
	  }
	  break;
	default:
	  break;
	}
      if (makenfi)
	{
	  found = true;
          int count = 0;
          for (int j = 0; j < i; j++)
            {
              if (doms[j] != NULL)
                {
                  count++;
                }
            }
          DEBUG_ASSERT(doms[i]->isObjectVariable());
          ObjectVariable* objdom = OBJECT_CAST(ObjectVariable*, doms[i]);
          if (count == 0)
            {
	      PrologValue temp_term(var1.getTerm());
#ifdef DEBUG
	      DEBUG_ASSERT(notFreeIn(objdom, temp_term));
#else
	      (void)notFreeIn(objdom, temp_term);
#endif
            }
          else
            {
	      SubstitutionBlock *newsub = heap.newSubstitutionBlock(count);
              int pos = 1;
              for (int j = 0; j < i; j++)
                {
                  if (doms[j] != NULL)
                    {
                      newsub->setDomain(pos, doms[j]);
                      newsub->setRange(pos,AtomTable::dollar);
                      pos++;
                    }
                }
	      Object* new_sub_list = heap.newSubstitutionBlockList(newsub, AtomTable::nil);
	      PrologValue temp_term(new_sub_list, var1.getTerm());
#ifdef DEBUG
	      DEBUG_ASSERT(notFreeIn(objdom, temp_term));
#else
	      (void)notFreeIn(objdom, temp_term);
#endif
            }
          doms[i] = NULL;
          finalsize--;
	}
    }
  if (found)
    {
      DEBUG_CODE({
	int count = 0;
	for (int j = 0; j < (int)size; j++)
	  {
	    if (doms[j] != NULL)
	      {
		count++;
	      }
	  }
	DEBUG_ASSERT(count == finalsize);
      });
      
      if (finalsize == 0)
	{
	  var1.setSubstitutionBlockList(AtomTable::nil);
	}
      else
	{
          SubstitutionBlock *newsub = heap.newSubstitutionBlock(finalsize);
          int pos = 1;
          for (int j = 0; j < (int)size; j++)
	    {
	      if (doms[j] != NULL)
	        {
	          newsub->setDomain(pos, doms[j]);
	          newsub->setRange(pos, rans[j]);
                  pos++;
	        }
	    }
          Object* new_sub_list = heap.newSubstitutionBlockList(newsub, AtomTable::nil);
	  var1.setSubstitutionBlockList(new_sub_list);
	} 
    }
  return (found);
}

//
// Remove any sub of the form [vm/xm, ..., v1/x1] from term1 or term2 that is
// not cancelled  by a later sub or does not have a corresponding (uncancelled)
// sub in the other term.
// Add subs of the form [ym/vm, ..., y1/v1] to both sides for any uncancelled
// subs.
bool
Thread::balanceLocals(PrologValue& term1, PrologValue& term2)
{
  Object *sub1 = term1.getSubstitutionBlockList();
  Object *sub2 = term2.getSubstitutionBlockList();

  // get the number of sub  blocks for term1
  int size1 = 0;
  for (Object* tmp = sub1;
       tmp->isCons();
       tmp = OBJECT_CAST(Cons *, tmp)->getTail())
    {
      size1++;
    }
  // get the number of sub  blocks for term2
  int size2 = 0;
  for (Object* tmp = sub2;
       tmp->isCons();
       tmp = OBJECT_CAST(Cons *, tmp)->getTail())
    {
      size2++;
    }
  // arrays for storing blocks - double the size to cope with added subs
  SubstitutionBlock* sub1array[size1 * 2];
  SubstitutionBlock* sub2array[size2 * 2];

  // Fill in sub1array
  int index = 0;
  for (;
       sub1->isCons();
       sub1 = OBJECT_CAST(Cons *, sub1)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, sub1)->getHead()->isSubstitutionBlock());
      sub1array[index++] = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, sub1)->getHead());
    }
  DEBUG_ASSERT(index == size1);
  // Fill in sub2array
  index = 0;
  for (;
       sub2->isCons();
       sub2 = OBJECT_CAST(Cons *, sub2)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, sub2)->getHead()->isSubstitutionBlock());
      sub2array[index++] = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, sub2)->getHead());
    }
  DEBUG_ASSERT(index == size2);

  bool changed1 = false;
  bool changed2 = false;

  int saved_size1 = size1;
  int saved_size2 = size2;

  // Look through term1 subs - start from outer subs and
  // work inwards
  for (int i = size1-1; i >= 0; i--)
    {
      Object* range = sub1array[i]->getRange(1);
      if (range->isLocalObjectVariable())
	{
	  // look for cancelling sub in term1
	  bool found = false;
	  for (int j = size1-1; j > i; j--)
	    {
	      if ((sub1array[j] != NULL) && 
		  (sub1array[j]->getDomain(1) == range))
		{
		  found = true;
		  break;
		}
	    }
	  if (found)
	    {
	      continue;
	    }
	  // not found so look through term2 subs
	  for (int j = size2-1; j >= 0; j--)
	    {
	      if (sub2array[j]->getDomain(1) == range)
		{
		  break;
		}
	      if (sub2array[j]->getRange(1) == range)
		{
		  found = true;
		  break;
		}
	    }
	  if (found)
	    {
	      // the cancelling sub is in term2 so add a sub 
	      SubstitutionBlock *new_sub = 
		heap.newSubstitutionBlock(sub1array[i]->getSize());
	      new_sub->makeInvertible();
	      
	      for (size_t k = 1; k <= sub1array[i]->getSize(); k++)
		{
		  ObjectVariable *object_variable = heap.newObjectVariable();

		  new_sub->setDomain(k, sub1array[i]->getRange(k));
		  new_sub->setRange(k, object_variable);

		  generateNFIConstraints(object_variable, term1);
		  for (int m = saved_size1; m < size1; m++)
		    {
		      for (size_t n = 1; n <= sub1array[m]->getSize(); n++)
			{
			  PrologValue t(sub1array[m]->getRange(n));
			  (void)notFreeIn(object_variable, t);
			}
		    }
		  generateNFIConstraints(object_variable, term2);
		  for (int m = saved_size2; m < size2; m++)
		    {
		      for (size_t n = 1; n <= sub2array[m]->getSize(); n++)
			{
			  PrologValue t(sub2array[m]->getRange(n));
			  (void)notFreeIn(object_variable, t);
			}
		    }
		}
	      
	      setMutualDistinctRanges(new_sub);
	      sub1array[size1++] = new_sub;
	      sub2array[size2++] = new_sub;
	      changed1 = true;
	      changed2 = true;
	    }
	  else
	    {
	      // remove sub and add appropriate NFI constraints
	      for (size_t k = 1; k <= sub1array[i]->getSize(); k++)
		{
		  PrologValue domain(sub1array[i]->getDomain(k));
		  Object* subst = AtomTable::nil;
		  for (int m = i-1; m >= 0; m--)
		    {
		      if (sub1array[m] != NULL)
			{
			  subst = 
			    heap.newSubstitutionBlockList(sub1array[m], subst);
			}
		    }
		  PrologValue tmp(subst, term1.getTerm());
		  if (! internalNotFreeIn(domain, tmp))
		    {
		      // Free locals can't be removed.
		      return false;
		    }
		}
	      sub1array[i] = NULL;
	      changed1 = true;
	    }
	}
    }
  // Look through term2 subs
  for (int i = saved_size2-1; i >= 0; i--)
    {
      Object* range = sub2array[i]->getRange(1);
      if (range->isLocalObjectVariable())
	{
	  // look for cancelling sub in term2
	  bool found = false;
	  for (int j = size2-1; j > i; j--)
	    {
	      if ((sub2array[j] != NULL) && 
		  (sub2array[j]->getDomain(1) == range))
		{
		  found = true;
		  break;
		}
	    }
	  if (found)
	    {
	      continue;
	    }
	  // not found so look through term1 subs
	  for (int j = size1-1; j >= 0; j--)
	    {
	      if (sub1array[j] == NULL)
		{
		  continue;
		}
	      if (sub1array[j]->getDomain(1) == range)
		{
		  break;
		}
#ifdef DEBUG
	      if (sub1array[j]->getRange(1) == range)
		{
		  found = true;
		  break;
		}
#endif // DEBUG
	    }
	  DEBUG_ASSERT(!found);
	  // remove sub and add appropriate NFI constraints
	  for (size_t k = 1; k <= sub2array[i]->getSize(); k++)
	    {
	      PrologValue domain(sub2array[i]->getDomain(k));
	      Object* subst = AtomTable::nil;
	      for (int m = i-1; m >= 0; m--)
		{
		  if (sub2array[m] != NULL)
		    {
		      subst = heap.newSubstitutionBlockList(sub2array[m], subst);
		    }
		}
	      PrologValue tmp(subst, term2.getTerm());
	      if (! internalNotFreeIn(domain, tmp))
		{
		  // Free locals can't be removed.
		  return false;
		}
	    }
	  sub2array[i] = NULL;
	  changed2 = true;
	}
    }
  if (changed1)
    {
      Object* subst = AtomTable::nil;
      for (int m = size1-1; m >= 0; m--)
	{
	  if (sub1array[m] != NULL)
	    {
	      subst = heap.newSubstitutionBlockList(sub1array[m], subst);
	    }
	}
      term1.setSubstitutionBlockList(subst);
    }
  if (changed2)
    {
      Object* subst = AtomTable::nil;
      for (int m = size2-1; m >= 0; m--)
	{
	  if (sub2array[m] != NULL)
	    {
	      subst = heap.newSubstitutionBlockList(sub2array[m], subst);
	    }
	}
      term2.setSubstitutionBlockList(subst);
    }  
  return true; 
}


//
// Generate not_free_in constraints for the ranges and term.
//
void
Thread::generateNFIConstraints(ObjectVariable *object_variable,
			       PrologValue& term)
{
  heap.prologValueDereference(term);
  // Generate object_variable not_free_in all vars of term.term.
  Object* tm = term.getTerm();
  switch (tm ->utag())
    {
    case Object::uVar:
    case Object::uObjVar:
      {
	PrologValue t(tm);
	(void)(notFreeIn(object_variable, t));
      }
      break;
    case Object::uCons:
      {
	PrologValue h(OBJECT_CAST(Cons*, tm)->getHead());
        generateNFIConstraints(object_variable, h);
       	PrologValue t(OBJECT_CAST(Cons*, tm)->getTail());
        generateNFIConstraints(object_variable, t); 
      }
      break;
    case Object::uStruct:
      {
	Structure* st = OBJECT_CAST(Structure*, tm);
	for (size_t i = 0; i <= st->getArity(); i++)
	  {
	    PrologValue t(st->getArgument(i));
	    generateNFIConstraints(object_variable, t);
	  }
      }
      break;
    case Object::uConst:
      break;

    case Object::uQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm*, tm);
	PrologValue qt(q->getQuantifier());
	generateNFIConstraints(object_variable, qt);
	PrologValue qv(q->getBoundVars());
	generateNFIConstraints(object_variable, qv);
	PrologValue qb(q->getBody());
	generateNFIConstraints(object_variable, qb);
      }
      break;
    default:
      DEBUG_ASSERT(false);
      break;
    }

  // For each domian and range that is not a local object variable, generate a
  // not_free_in constraint.
  for (Object *sub_list = term.getSubstitutionBlockList();
       sub_list->isCons();
       sub_list = OBJECT_CAST(Cons *, sub_list)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, sub_list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub 
	= OBJECT_CAST(SubstitutionBlock*, 
		      OBJECT_CAST(Cons *, sub_list)->getHead());
      DEBUG_ASSERT(sub->getSize() > 0);

      for (size_t i = 1; i <= sub->getSize(); i++)
        {
          Object *range = sub->getRange(i);
          if (! range->isLocalObjectVariable())
	    {
	      PrologValue ran_t(range);
	      generateNFIConstraints(object_variable, ran_t);
            }
          Object *domain = sub->getDomain(i);
          if (! domain->isLocalObjectVariable())
	    {
	      PrologValue dom_t(domain);
	      (void)(notFreeIn(object_variable, dom_t));
	    }
	}
    }
}



//
// Add the delayed problem to the delayed queue associated with the variable.
//
void
Thread::delayProblem(Object *problem, Object *var)
{
  DEBUG_ASSERT(var->isAnyVariable());

  DEBUG_ASSERT(! problem->isAnyVariable());

  // If the delay problems list for the variable is empty, then
  // we have to add the variable to the $delay_problem implicit 
  // parameter.
  
  if (var->isVariable())
    {
      var = addExtraInfo(OBJECT_CAST(Variable*, var->variableDereference()));
    }
  Object *new_prob = OBJECT_CAST(Reference*, var)->getDelays();
  if (new_prob->isNil())
    {
      Object *current_value = ipTable.getImplicitPara(AtomTable::delays);
      Object *delay_prob =
	heap.newDelay(var, current_value->variableDereference());
      if (heap.getSavedTop() > reinterpret_cast<heapobject*>(current_value))
	{
	  Variable *var = heap.newVariable();
	  var->setReference(delay_prob);
	  ipTable.setImplicitPara(AtomTable::delays, var, *this);
	}
      else
	{
	  DEBUG_ASSERT(current_value->isVariable());
	  OBJECT_CAST(Variable*, current_value)->setReference(delay_prob);
	}  
    }

  // Scan through the delayed problems of the variable checking to see if
  // any is the same as the one to be added using FastEqual.
  for (;
       new_prob->isCons();
       new_prob = OBJECT_CAST(Cons*, new_prob)->getTail())
    {
      Object* headProblem = OBJECT_CAST(Cons*, new_prob)->getHead();
      DEBUG_ASSERT(headProblem->isStructure());
      DEBUG_ASSERT(OBJECT_CAST(Structure*, headProblem)->getArity() == 2);
      DEBUG_ASSERT(OBJECT_CAST(Structure*, headProblem)->getFunctor() == AtomTable::comma);

      PrologValue t1(OBJECT_CAST(Structure*, headProblem)->getArgument(2));
      PrologValue t2(problem);

      if (heap.fastEqual(t1, t2) == true)
	{
	  // The problem exists already.
	  DEBUG_ASSERT(OBJECT_CAST(Structure*, headProblem)->getArgument(1)->isVariable());
	  Variable *dstatus 
	    = OBJECT_CAST(Variable*,
			  OBJECT_CAST(Structure*, headProblem)->getArgument(1));

	  if (dstatus->isThawed())
	    {
	      // Make the existing problem unsolved if has
	      // been solved already.
	      trailTag(dstatus);
	      dstatus->freeze();
	    }
	  return;
	}
    }

  // Add a new problem.
  Object *delay_prob = 
    heap.newDelay(problem,  OBJECT_CAST(Reference*, var)->getDelays());
  Object* mp = atoms->add("$retry_make_progress");
  Object* s = AtomTable::success;
  (void)psi_ip_set(mp,s); 


  updateAndTrailObject(reinterpret_cast<heapobject*>(var), delay_prob, 
		       Reference::DelaysOffset);
}

//
// Check if delayed problem is associated with variable.
//
bool
Thread::isDelayProblem(Object *problem, Object *var)
{
  DEBUG_ASSERT(var->isAnyVariable());
  Object *delays = OBJECT_CAST(Reference*, var)->getDelays();
  if (delays->isNil())
    {
      return false;
    }

  // Scan through the delayed problems of the variable checking to see if
  // the problem exists (using FastEqual).
  for ( ;
	delays->isCons(); 
	delays = OBJECT_CAST(Cons *, delays)->getTail())
    {
      Structure *delay = 
	OBJECT_CAST(Structure *, OBJECT_CAST(Cons *, delays)->getHead());

      DEBUG_ASSERT(delay->getArity() == 2);

      PrologValue t1(delay->getArgument(2));
      PrologValue t2(problem);

      if (heap.fastEqual(t1, t2) == true)
	{
	  // The problem exists already.
	  Variable *delay_status = OBJECT_CAST(Variable*, 
					       delay->getArgument(1));
	  if (delay_status->isThawed())
	    {
	      return false;
	    }

	  return true;
	}
    }

  return false;
}

//
// Given a delayed unification problem term1 = term2 to be delayed on variable,
// build the term term1 = term2 and delay this call on variable.
//
void
Thread::delayUnify(PrologValue& term1, PrologValue& term2,
		   Object *variable)
{
  DEBUG_ASSERT(variable->isAnyVariable());
  Structure *problem = heap.newStructure(2);
  problem->setFunctor(AtomTable::equal);
  problem->setArgument(1, heap.prologValueToObject(term1));
  problem->setArgument(2, heap.prologValueToObject(term2));

  //
  // Delay the problem.
  //
  delayProblem(problem, variable);
}

//
// Given a not_free_in problem to delay of the form x not_free_in s*t to be
// delayed on variable, build the term x not_free_in s*t and delay this call
// on variable.  Assume no free locals in s*t.
//
void
Thread::delayNFI(ObjectVariable *object_variable,
		 PrologValue& term,
		 Object *variable)
{
  DEBUG_ASSERT(variable->isAnyVariable());
  addExtraInfoToVars(term.getSubstitutionBlockList());
  Structure *problem = heap.newStructure(2);
  problem->setFunctor(AtomTable::nfi);
  problem->setArgument(1, object_variable);
  problem->setArgument(2, heap.prologValueToObject(term));
  
  //
  // Delay the problem.
  //
  delayProblem(problem, variable);
}

//
// Check if object_variable not_free_in variable problem exists.
// NO substitution!!
//
bool
Thread::isDelayNFI(Object * object_variable,
		   Object * variable)
{
  DEBUG_ASSERT(object_variable->isObjectVariable());
  DEBUG_ASSERT(variable->isAnyVariable());
  Structure *problem = heap.newStructure(2);

  problem->setFunctor(AtomTable::nfi);
  problem->setArgument(1, object_variable);
  problem->setArgument(2, variable);

  //
  // Check for delayed problem.
  //
  return isDelayProblem(problem, variable);
}

//
// Wake up any delayed problems associated with the given (object) reference.
// Assumes reference has been dereferenced.
//
void
Thread::wakeUpDelayedProblems(Object *ref)
{
  DEBUG_ASSERT(ref->isAnyVariable());
  DEBUG_ASSERT(ref == ref->variableDereference());

  DEBUG_ASSERT(! OBJECT_CAST(Reference*, ref)->getDelays()->isNil());

  //
  // Mark the variable that has woken delayed problems.
  // i.e. Switch the status to thaw.
  //
  for (Object *global_delays = 
	 ipTable.getImplicitPara(AtomTable::delays)->variableDereference();
       global_delays->isCons();
       global_delays = OBJECT_CAST(Cons *, global_delays)->getTail()->variableDereference())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference()->isStructure());

      Structure *delay
	= OBJECT_CAST(Structure*, OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference());

      DEBUG_ASSERT(delay->getArity() == 2);

      if (delay->getArgument(2)->variableDereference() == ref)
	{
	  // The variable is located - change the status
	  Reference *dstatus = OBJECT_CAST(Reference*, delay->getArgument(1));
	  trailTag(dstatus);
	  dstatus->thaw();
	  break;
	}
    }
    
  //
  // Signal that there are delayed problems woken up.
  //
  status.setFastRetry();
}

//
// Retry the delayed problems - 
// type = NOSIMPNFI then retry only NFI problems but don't simplify 
// type = NFI then retry NFI problems 
// type = BOTH then retry NFI and = problems
//
bool
Thread::retry_delays(delaytype type = NOSIMPNFI)
{
  bool both = (type == BOTH);
  // set the retry flag to fail
  Object* mp = atoms->add("$retry_make_progress");
  Object* s = AtomTable::failure;
  (void)psi_ip_set(mp,s); 

  
  while (true)
    {
      for (Object *global_delays = 
	     ipTable.getImplicitPara(AtomTable::delays)->variableDereference();
	   global_delays->isCons();
	   global_delays = OBJECT_CAST(Cons *, global_delays)->getTail()->variableDereference())
	{
	  DEBUG_ASSERT(OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference()->isStructure());
      
	  Structure *delay = OBJECT_CAST(Structure*, OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference());
      
	  DEBUG_ASSERT(delay->getArity() == 2);
	  Object* status = delay->getArgument(1)->variableDereference();
	  if (!status->isVariable()) 
	    {
	      continue;
	    }
	  // Get the variable with delays
	  Object* var_delays;
	  Object* var = delay->getArgument(2);
          (void)psi_delayed_problems_for_var(var, var_delays);
	  for ( ; var_delays->isCons();
		var_delays = OBJECT_CAST(Cons *, var_delays)->getTail())
	    {
	      Object* vd = 
		OBJECT_CAST(Cons*, var_delays)->getHead()->variableDereference();
	      DEBUG_ASSERT(vd->isStructure());
	      Structure* vdstruct = OBJECT_CAST(Structure *, vd);
	      DEBUG_ASSERT(vdstruct->getArity() == 2);
	      Object* vdstatus = 
		vdstruct->getArgument(1)->variableDereference();
	      DEBUG_ASSERT(vdstatus->isVariable());
	      if (!OBJECT_CAST(Variable*,vdstatus)->isFrozen())
		{
		  continue;
		}
	      Object* problem = 
		vdstruct->getArgument(2)->variableDereference();
	      DEBUG_ASSERT(problem->isStructure());
	      Structure* pstruct = OBJECT_CAST(Structure*, problem);
	      if (pstruct->getArity() != 2 ||
		  (!both && (pstruct->getFunctor() != AtomTable::nfi)) ||
                  (both && (pstruct->getFunctor() != AtomTable::nfi)
		   && (pstruct->getFunctor() != AtomTable::equal)))
		{
		  continue;
		}
	      if (both && (pstruct->getFunctor() == AtomTable::equal))
		{
		  PrologValue  
		    pval1(pstruct->getArgument(1)->variableDereference());
		  PrologValue  
		    pval2(pstruct->getArgument(2)->variableDereference());
		  heap.prologValueDereference(pval1);
		  heap.prologValueDereference(pval2);
		  trailTag(vdstatus);
		  OBJECT_CAST(Reference*, vdstatus)->thaw();
                  int counter = 0;
		  if (equalEqual(pval1, pval2, counter))
		    {
		      continue;
		    }
		  if (!unify(pstruct->getArgument(1), pstruct->getArgument(2)))
		    {
		      return false;
		    }
		  else
		    {
		      continue;
		    }
		}
	      // We have an unsolved nfi problem
	      Object* obvar = pstruct->getArgument(1)->variableDereference();
	      PrologValue pval(pstruct->getArgument(2));
              if (both || (type == NFI))
                {
		  trailTag(vdstatus);
		  OBJECT_CAST(Reference*, vdstatus)->thaw();
		  // Simplify first
		  if (notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), pval))
		    {
		      continue;
		    }
		  else
		    {
		      return false;
		    }
                }
	      heap.prologValueDereference(pval);
	      if (pval.getSubstitutionBlockList()->isCons())
		{
		  heap.dropSubFromTerm(*this, pval);
		}

	      if (pval.getSubstitutionBlockList()->isNil())
		{
		  trailTag(vdstatus);
		  OBJECT_CAST(Reference*, vdstatus)->thaw();
		  if (!notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), pval))
		    {
		      return false;
		    }
		}
	      else
		{
		  Object* sub = pval.getSubstitutionBlockList();
		  if (!OBJECT_CAST(Cons *, sub)->getTail()->isNil() 
		      || !pval.getTerm()->isAnyVariable())
		    {
		      continue;
		    }
		  // a single sub
		  // copy the sub
		  SubstitutionBlock* block =
		    heap.copySubstitutionBlock(OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons *, sub)->getHead()));
		  Cons* newsub = heap.newSubstitutionBlockList(block, AtomTable::nil);
		  DEBUG_ASSERT(newsub->isLegalSub());
		  PrologValue pvalcopy(newsub, pval.getTerm());
		  trailTag(vdstatus);
		  OBJECT_CAST(Reference*, vdstatus)->thaw();
		  if (!notFreeInVarSimp(OBJECT_CAST(ObjectVariable*, obvar), 
					pvalcopy))
		    {
		      return false;
		    }
		}
	    }
	}

      // Check to see if any progress has been made
      if (ipTable.getImplicitPara(mp)->variableDereference() == AtomTable::success)
	{
	// set the retry flag to fail
	  (void)psi_ip_set(mp,s); 
	}
      else
	{
	  break;
	}
    }
  return true;
}














