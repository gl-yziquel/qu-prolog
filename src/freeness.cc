// freeness.cc - has two components:
//               a.  freeness test returns no, unsure, yes.
//		 b.  applies not_free_in constraints to terms.
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
// $Id: freeness.cc,v 1.15 2002/07/26 00:39:57 qp Exp $

// #include "atom_table.h"
#include "global.h"
#include "heap_qp.h"
#include "thread_qp.h"

//
// Check whether object variable is not free in the structure.
//
bool
Thread::notFreeInStructure(ObjectVariable *object_variable,
			   PrologValue& term, bool gen_delays = true)
{
  DEBUG_ASSERT(term.getTerm()->isStructure());

  Object *sub_block_list = term.getSubstitutionBlockList();
  Structure *structure = OBJECT_CAST(Structure*, term.getTerm());

  //
  // Do 'not_free_in' test for the functor: 
  //	ObjectVariable 'not_free_in' term.sub * functor(term.term).
  //
  PrologValue functor(sub_block_list, structure->getFunctor());
  
  if (! notFreeIn(object_variable, functor, gen_delays))
    {
      return false;
    }

  //
  // Do 'not_free_in' test for the every argument. 
  //
  for (size_t i = 1; i <= structure->getArity(); i++)
    {
      PrologValue arg(sub_block_list, structure->getArgument(i));

      if (! notFreeIn(object_variable, arg, gen_delays))
	{
	  return false;
	}	
    }

  return true;
}

//
// Check whether object variable is not free in the list.
//
bool	
Thread::notFreeInList(ObjectVariable *object_variable,
		      PrologValue& list, bool gen_delays = true)
{
  DEBUG_ASSERT(list.getTerm()->isCons());

  Object *l = list.getTerm();
  for (;
       l->isCons();
       l = OBJECT_CAST(Cons *, l)->getTail()->variableDereference())
    {
      //
      // Do 'not_free_in' test for each element in the list. 
      //
      PrologValue elem(list.getSubstitutionBlockList(),
		       OBJECT_CAST(Cons *, l)->getHead());

      if (! notFreeIn(object_variable, elem, gen_delays))
	{
	  return false;
	}	
    }
  PrologValue last(list.getSubstitutionBlockList(), l);

  return notFreeIn(object_variable, last, gen_delays);
}

//
// Check whether variable is not free in the quantified term.
//
bool	
Thread::notFreeInQuantifier(ObjectVariable *object_variable,
			    PrologValue& term, bool gen_delays = true)
{
  DEBUG_ASSERT(term.getTerm()->isQuantifiedTerm());
  DEBUG_ASSERT(object_variable == object_variable->variableDereference());

  Object *sub_block_list = term.getSubstitutionBlockList();
  QuantifiedTerm *quantified_term = OBJECT_CAST(QuantifiedTerm*, 
						term.getTerm());

  size_t items = 0;  	// Count number of items pushed onto
			// the push down stack in this call.
  
  //
  // Do 'not_free_in' test for the quantifier: 
  //	ObjectVariable 'not_free_in' term.sub * quantifier(term.term).
  //
  PrologValue quantifier(sub_block_list,
			 quantified_term->getQuantifier());

  if (! notFreeIn(object_variable, quantifier, gen_delays))
    {
      pushDownStack.popNEntries(items);
      return false;
    }

  //
  // Do 'not_free_in' test for the bound variable list.
  //
  
  bool nfi_var_found = false;
  bool all_dom_disjoint = true;

  Object *bound_var_list =
    quantified_term->getBoundVars()->variableDereference();
  for (;
       bound_var_list->isCons();
       bound_var_list = 
	 OBJECT_CAST(Cons *, bound_var_list)->getTail()->variableDereference())
    {
      Object *head = OBJECT_CAST(Cons *, bound_var_list)->getHead()->variableDereference();

      if (head->isStructure())
	{
	  Structure *structure = OBJECT_CAST(Structure *, head);

	  DEBUG_ASSERT(structure->getFunctor() == AtomTable::colon &&
		       structure->getArity() == 2);

	  Object *colon_object_variable 
	    = structure->getArgument(1)->variableDereference();

	  DEBUG_ASSERT(colon_object_variable->isObjectVariable());

	  nfi_var_found = nfi_var_found || 
                          (colon_object_variable == object_variable);
          all_dom_disjoint = all_dom_disjoint &&
                       object_variable->distinctFrom(colon_object_variable);
	  //
	  // For every element of the type x:t do 'not_free_in'
	  // test:	
	  //	ObjectVariable 'not_free_in' term.sub * t.
	  //
	  PrologValue colon(sub_block_list, structure->getArgument(2));

	  if (! notFreeIn(object_variable, colon, gen_delays))
	    {
              pushDownStack.popNEntries(items);
	      return false;
	    }

	  //
	  // Push object variable onto the stack ob_var_stack.
	  //
	  pushDownStack.push(colon_object_variable);

	  items++;
	}
      else
	{
	  DEBUG_ASSERT(head->isObjectVariable());
	  nfi_var_found = nfi_var_found || 
                          (head == object_variable);
          all_dom_disjoint = all_dom_disjoint &&
                       object_variable->distinctFrom(head);

	  //
	  // Push object variable onto the stack ob_var_stack.
	  //
	  pushDownStack.push(head);

	  items++;
	}
    }

  if (bound_var_list->isNil())
    {
      if (sub_block_list->isNil())
        {
          if (nfi_var_found)
            {
              pushDownStack.popNEntries(items);
              return true;
            }
          if (all_dom_disjoint)
            {
              pushDownStack.popNEntries(items);
              PrologValue nfi(sub_block_list, quantified_term->getBody());
              return (notFreeIn(object_variable, nfi, gen_delays));
            }
        }
      //
      // Generate substitution sub = term.sub * [$/y1, $/y2, ... $/yn]
      // where y1, y2, ..., yn are object variables from bound object
      // variable list.
      //
     
      SubstitutionBlock *sub_block = heap.newSubstitutionBlock(items);
      for (size_t i = items; i > 0; i--)
	{
	  sub_block->setRange(i, AtomTable::dollar);
	  sub_block->setDomain(i, pushDownStack.pop()->variableDereference());
	}

      Object *nfi_sub_block_list = heap.newSubstitutionBlockList(sub_block,
							    sub_block_list);

      PrologValue nfi(nfi_sub_block_list, quantified_term->getBody());
      //
      // Do 'not_free_in' test for sub * Body. 
      // 
      return notFreeIn(object_variable, nfi, gen_delays);
    }
  else
    {
      DEBUG_ASSERT(bound_var_list->isVariable());
      //
      // Delay the object_variable not_free_in term problem.
      // Assign the problem to the open list variable BoundVarList.
      //
      pushDownStack.popNEntries(items);

      if (gen_delays)
	{
	  delayNFI(object_variable, term, bound_var_list);
	}
      else
	{
	  return false;
	}
    }

  return true;
}

//
// Check whether ObjectVariable is not free in the s*X.
// (X may be a variable or object variable)
//
bool
Thread::notFreeInVar(ObjectVariable *object_variable,
		     PrologValue& var, bool gen_delays = true)
{
  DEBUG_ASSERT(var.getTerm()->isAnyVariable());
  DEBUG_ASSERT(object_variable == object_variable->variableDereference());

  Object *sub_block_list = var.getSubstitutionBlockList();

  Object *ref = var.getTerm();

  if (sub_block_list->isNil())
    {
      if (ref->isVariable())
	{
	  if (gen_delays)
	    {
	      delayNFI(object_variable, var, ref);
	    }
	  else
	    {
	      return false;
	    }
	}
      else if (ref == object_variable)
	{
	  return false;
	}
      else if (!object_variable->distinctFrom(ref))
	{
	  if (gen_delays)
	    {
	      Object* mp = atoms->add("$retry_make_progress");
	      Object* s = AtomTable::success;
	      (void)psi_ip_set(mp,s); 
	      setDistinct(object_variable, OBJECT_CAST(ObjectVariable*, ref));
	    }
	  else
	    {
	      return false;
	    }
	}
    }
  else
    {
      if (gen_delays)
	{
	  // Simplify the substitution
	  Object* simpterm;
	  (void)simplify_sub_term(var, simpterm, object_variable);
	  PrologValue pterm(simpterm);
	  heap.prologValueDereference(pterm);
	  if (!pterm.getTerm()->isAnyVariable() ||  
	      pterm.getSubstitutionBlockList() ->isNil())
	    {
	      return notFreeIn(object_variable, pterm);
	    }
	  return (notFreeInVarSimp(object_variable, pterm));
	}
      else
	{
	  return false;
	}
    }
  
  return true;
}

//
// Constrain object variable to be not free in the term.  Fails if free in.
// Succeeds if not free in.  Delays otherwise.
// Delayed not_free_in problems are generated where necessary.
// Returns false iff object variable is free in term.
//
// NOTE: Object variable cannot be a local object variable.
//       Also assumes ObjectVariable has no substitution and
//       term has no free locals.
//
bool	
Thread::notFreeIn(ObjectVariable *object_variable, PrologValue& term,
		  bool gen_delays = true)
{
  object_variable = OBJECT_CAST(ObjectVariable*, object_variable->variableDereference());
  heap.prologValueDereference(term);
  if (term.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term);
    }

  switch (term.getTerm()->utag())
    {
    case Object::uVar:
    case Object::uObjVar:
      return notFreeInVar(object_variable, term, gen_delays);
      break;

    case Object::uCons:
      return notFreeInList(object_variable, term, gen_delays);
      break;

    case Object::uStruct:
      return notFreeInStructure(object_variable, term, gen_delays);
      break;

    case Object::uQuant:
      return notFreeInQuantifier(object_variable, term, gen_delays);
      break;

    case Object::uConst:
      return true;
      break;

    default:
      DEBUG_ASSERT(false);
      return true;
      break;
    }
}

 
//
// Not free in calls generated internally by the system can be of the form
// ObjectVariable not_free_in term with ObjectVariable of the form s*x and 
// term having possible free locals.
//
// Before notFreeIn is called, s is inverted (without generating further
// not_free_in calls) and the free locals in the new term are replaced by $'s.
//
// Assume term is already dereferenced.
//
// NOTE: it is important that the object variable is not fully dereferenced
// otherwise the substitution might be lost
//
bool
Thread::internalNotFreeIn(PrologValue object_variable,
			  PrologValue term)
{
  DEBUG_ASSERT(object_variable.getTerm()->isObjectVariable());

  Object *sub_block_list = object_variable.getSubstitutionBlockList();
  ObjectVariable *ov = 
    OBJECT_CAST(ObjectVariable *, 
		object_variable.getTerm()->variableDereference());

  DEBUG_ASSERT(! ov->isLocalObjectVariable());

  if (! sub_block_list->isNil())
    {
      heap.invertWithoutNFI(sub_block_list, term);
      heap.prologValueDereference(term);
    }

  //
  // Now the problem is: x not_free_in term (x is not a local).
  // 
  if (term.getTerm()->isLocalObjectVariable())
    {
      //
      // The case: x not_free_in v.
      // 
      return true;
    }
  
  //
  // The case: x not_free_in s1 * ... * sn * t.
  // Replace free locals with $'s
  // 
  Object **modified_list = term.getSubstitutionBlockListAddress();
  
  for (Object *s1 = term.getSubstitutionBlockList();
       s1->isCons();
       s1 = OBJECT_CAST(Cons *, s1)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, s1)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub1_block =
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s1)->getHead());
      
      DEBUG_ASSERT(sub1_block->getSize() > 0);
      
      Object *range = sub1_block->getRange(1);
      
      if (range->isLocalObjectVariable())
	{
	  bool found = false;
	  //
	  // Assume substitutions of the form:
	  //	[vm/xm, ..., v1/x1]
	  // For such a substitution si look for  
	  // sj < si of the form:
	  //	[ym/vm, ..., y1/v1].
	  //
	  for (Object *s2 = OBJECT_CAST(Cons *,s1)-> getTail();
	       s2->isCons();
	       s2 = OBJECT_CAST(Cons *, s2)->getTail())
	    {
              DEBUG_ASSERT(OBJECT_CAST(Cons*, s2)->getHead()->isSubstitutionBlock());
	      SubstitutionBlock *sub2_block = 
		OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s2)->getHead());
	      
	      DEBUG_ASSERT(sub2_block->getSize() > 0);
	      
	      //
	      // According to the way local object variables
	      // are generated, it is enough to check
	      // whether first range and domain are equal.
	      //
	      if (range == sub2_block->getDomain(1))
		{
		  found = true;
		  break;
		}
	    }
	  
	  if (! found)
	    {
	      //
	      // If there is no corresponding substitution
	      // replace each range by $.
	      //
	      // NOTE: sub table is copied to avoid problems
	      // with sharing.
	      //
              DEBUG_ASSERT(OBJECT_CAST(Cons*, s1)->getHead()->isSubstitutionBlock());
              size_t size =
	        OBJECT_CAST(SubstitutionBlock *, 
                            OBJECT_CAST(Cons *, s1)->getHead())->getSize();
	      Object *new_sub = heap.copySubstitutionBlockWithDollars(s1,size);
	      *modified_list = heap.copySubSpine(*modified_list, s1, new_sub); 
	      while (*modified_list != new_sub)
		{
		  modified_list =
		    OBJECT_CAST(Cons*,
				*modified_list)->getTailAddress();
		}
	    }
	}
    }
  //
  // After removing locals pass the problem on
  //
  return notFreeIn(ov, term);
}


//
// Simplify the substitution associated with var and apply not free in.
// Assumes the term is an (obj)var and has a single parallel sub.
// WARNING - this function destructively updates the sub.
//
bool
Thread::notFreeInVarSimp(ObjectVariable *object_variable,
			 PrologValue& term)
{
  DEBUG_ASSERT(term.getTerm()->isAnyVariable());
  DEBUG_ASSERT(object_variable == object_variable->variableDereference());

  addExtraInfoToVars(term.getSubstitutionBlockList());
  addExtraInfoToVars(term.getTerm());
  heap.prologValueDereference(term);

  if (!term.getTerm()->isAnyVariable())
    {
       return notFreeIn(object_variable, term);
    }
  DEBUG_ASSERT(term.getTerm()->isAnyVariable());

  Object *sub_block_list = term.getSubstitutionBlockList();

  //
  // The dereference may have removed the substitution
  //
  if (sub_block_list->isNil())
    {
      if (term.getTerm()->isObjectVariable())
	{
	  ObjectVariable* term_obj_var = OBJECT_CAST(ObjectVariable*, 
						     term.getTerm());
	  if (term_obj_var == object_variable)
	    {
	      return false;
	    }
	  else
	    {
	      if (! object_variable->distinctFrom(term_obj_var))
		{
		  Object* mp = atoms->add("$retry_make_progress");
		  Object* s = AtomTable::success;
		  (void)psi_ip_set(mp,s); 
		  
		  setDistinct(object_variable, term_obj_var);
		}
	      return true;
	    }
	}
      else 
	{
	  delayNFI(object_variable, term, term.getTerm());
	  return true;
	}
    }

  DEBUG_ASSERT(!sub_block_list->isNil());
  DEBUG_ASSERT(OBJECT_CAST(Cons* , sub_block_list)->getTail()->isNil());
  
  DEBUG_ASSERT(OBJECT_CAST(Cons*, sub_block_list)->getHead()->isSubstitutionBlock());
  SubstitutionBlock *sub_block = 
    OBJECT_CAST(SubstitutionBlock *,
		OBJECT_CAST(Cons* , sub_block_list)->getHead());
  
  DEBUG_ASSERT(sub_block->getSize() > 0);
  
  Object *var = term.getTerm();

  int size = sub_block->getSize();
  bool all_dollars = true;
  bool obvar_in_domain = false;
  bool term_in_domain = false;
  Object* rans[size];
  ObjectVariable* doms[size];
  int total = size;
  
  //
  // Initialise rans and doms and test:
  // * if all range elements are $.
  // * if the obvar is in the domain of the sub
  // * if the term is in the domain of the sub
  //
  for (int i = 1; i <= size; i++)
    {
      DEBUG_ASSERT(sub_block->getDomain(i)->variableDereference()->isObjectVariable());
      doms[i-1] = OBJECT_CAST(ObjectVariable*, sub_block->getDomain(i)->variableDereference());
      rans[i-1] = sub_block->getRange(i)->variableDereference();
      if (rans[i-1] != AtomTable::dollar)
	{
	  all_dollars = false;
	}
      if (object_variable == doms[i-1])
	{
	  obvar_in_domain = true;
	}
      if (var == doms[i-1])
	{
	  term_in_domain = true;
	}
    }

  if (all_dollars)
    {
      if (obvar_in_domain ||
	  (var->isObjectVariable() &&
	   (object_variable->distinctFrom(var) || term_in_domain)
	   ) ||
	  (var->isVariable() &&
	   isDelayNFI(object_variable, var))
	  )
	{
	  return true;
	}
      else if (size == 1 && object_variable == var)
	{
	  DEBUG_ASSERT(doms[0] == doms[0]->variableDereference());
	  if ((! status.testHeatWave()) &&
	      object_variable->isFrozen() &&
	      doms[0]->isFrozen())
	    {
              DEBUG_ASSERT(var->isAnyVariable());
	      delayNFI(object_variable, term, var);
	      return true;
	    }

	  bindObjectVariables(object_variable, doms[0]);
	  Object* mp = atoms->add("$retry_make_progress");
	  Object* s = AtomTable::success;
	  (void)psi_ip_set(mp,s); 

	  return true;
	}
    }

  // 
  // Compress substitution.
  //
  // sub = [tn/xn,...,t1/x1] - if ti = $ and xi distinct from object_variable 
  // then ti/xi can be safely removed provided xi distinct from xn,..,x(i+1).
  //
  for (int i = size-1; i >= 0; i--)
    {
      DEBUG_ASSERT(doms[i] != NULL);
      DEBUG_ASSERT(doms[i] == doms[i]->variableDereference());
      if (rans[i] == AtomTable::dollar &&
	  doms[i]->distinctFrom(object_variable))
	{
	  bool is_distinct = true;
	  for (int j = size-1; j > i; j--) 
	    {
	      DEBUG_ASSERT((doms[j] == NULL) ||
			   (doms[j] == doms[j]->variableDereference()));
	      if ((doms[j] != NULL) && (! doms[i]->distinctFrom(doms[j])))
		{
		  is_distinct = false;
		  break;
		}
	    }
	  if (is_distinct) 	
	    {
	      doms[i] = NULL;
	      total--;
	    }
	}
    }
  if (total == 0)
    {
      term.setSubstitutionBlockList(AtomTable::nil);
      sub_block_list = AtomTable::nil;
      return notFreeIn(object_variable, term);
    }
  
  DEBUG_CODE({
    Object *remember = term.getTerm();
    heap.prologValueDereference(term);
    DEBUG_ASSERT(remember == term.getTerm());
  }
	     );
  
  if (sub_block_list->isNil() &&
      term.getTerm()->isObjectVariable())
    {
      ObjectVariable* term_obj_var = OBJECT_CAST(ObjectVariable*, 
						 term.getTerm());
      if (term_obj_var == object_variable)
	{
	  return false;
	}
      else
	{
	  DEBUG_ASSERT(object_variable == 
		       object_variable->variableDereference());
	  if (! object_variable->distinctFrom(term_obj_var))
	    {
	      Object* mp = atoms->add("$retry_make_progress");
	      Object* s = AtomTable::success;
	      (void)psi_ip_set(mp,s); 

	      setDistinct(object_variable, term_obj_var);
	    }

	  return true;
	}
    }
  
  if (total == 1 && object_variable == term.getTerm())
    {
      int pos;
      for (pos = 0; pos < size; pos++)
	{
	  if (doms[pos] != NULL)
	    {
	      break;
	    }
	}
      DEBUG_ASSERT(doms[pos] != NULL);
      DEBUG_ASSERT(doms[pos] == doms[pos]->variableDereference());
      if ((! status.testHeatWave()) &&
	  object_variable->isFrozen() &&
	  doms[pos]->isFrozen())
	{
          DEBUG_ASSERT(term.getTerm()->isAnyVariable());

	  SubstitutionBlock* sub = heap.newSubstitutionBlock(1);
	  sub->setDomain(1, doms[pos]);
	  sub->setRange(1, rans[pos]);
	  term.setSubstitutionBlockList(heap.newSubstitutionBlockList(sub, AtomTable::nil));
	  delayNFI(object_variable, term,  term.getTerm());
	  return true;
	}
      Object* mp = atoms->add("$retry_make_progress");
      Object* s = AtomTable::success;
      (void)psi_ip_set(mp,s); 

      bindObjectVariables(object_variable, doms[pos]);

      object_variable =
	OBJECT_CAST(ObjectVariable*, object_variable->variableDereference());

      if (rans[pos] == AtomTable::dollar)
	{
	  return true;
	}
      else
	{
	  PrologValue range(rans[pos]);
	  return notFreeIn(object_variable, range);
	}
    }

  //
  // If there is a ti/xi such that ti = object_variable then xi not_free_in
  // [$/x(i-1),...,$/x1]*term.term  and object_variable not_free_in 
  // [tn/xn,...,t(i+1)/x(i+1), t(i-1)/x(i-1), ...t1/x1]*term.term;
  // otherwise delay the problem.
  //
  int pos = 0;
  for (int i = 0; i < size; i++)
    {
      if (doms[i] == NULL)
	{
	  continue;
	}
      pos++;
      PrologValue range(rans[i]);
      DEBUG_ASSERT(doms[i] == doms[i]->variableDereference());
      ObjectVariable* domain_object_variable = doms[i];
      if (range.getTerm() == object_variable && 
          range.getSubstitutionBlockList()->isNil()) 
	{
	  if (pos == 1)
	    {
	      PrologValue new_term(term.getTerm());
	      if (total == 1)
		{
		  return notFreeInVar(domain_object_variable, new_term) && 
		    notFreeIn(object_variable, new_term);
		}
	      else
		{
		  doms[i] = NULL;
		  total--;
		  SubstitutionBlock* sub = heap.newSubstitutionBlock(total);
		  int offset = 1;
		  for (int j = 0; j < size; j++)
		    {
		      if (doms[j] != NULL)
			{
			  sub->setDomain(offset, doms[j]);
			  sub->setRange(offset, rans[j]);
			  offset++;
			}
		    }
		  DEBUG_ASSERT(offset == total+1);
		  PrologValue term1(heap.newSubstitutionBlockList(sub, AtomTable::nil), term.getTerm());
		  return notFreeInVar(domain_object_variable, new_term) && 
		    notFreeIn(object_variable, term1);
		}
	    }
	  else
	    {
	      SubstitutionBlock *sub = 
		heap.newSubstitutionBlock(pos - 1);

	      int offset = pos-1;
	      for (int j = i - 1; j >= 0; j--)
		{
		  if (doms[j] != NULL)
		    {
		      sub->setDomain(offset, doms[j]);
		      sub->setRange(offset, AtomTable::dollar);
		      offset--;
		    }
		}
	      DEBUG_ASSERT(offset == 0);

	      Cons* new_sub = 
		heap.newSubstitutionBlockList(sub, AtomTable::nil);
	      PrologValue new_term(new_sub, term.getTerm());

	      ObjectVariable* domain_object_variable = doms[i];
	      DEBUG_ASSERT(domain_object_variable 
			   == domain_object_variable->variableDereference());
	      doms[i] = NULL;
	      total--;
	      DEBUG_CODE(
	      {
		Object *remember = new_term.getTerm();
		heap.prologValueDereference(new_term);
		DEBUG_ASSERT(remember == new_term.getTerm());
	      });
	      heap.prologValueDereference(new_term);
	      
	      DEBUG_ASSERT(new_term.getTerm()->isAnyVariable());

	      sub = heap.newSubstitutionBlock(total);

	      offset = total;
	      for (int j = size - 1; j >= 0; j--)
		{
		  if (doms[j] != NULL)
		    {
		      sub->setDomain(offset, doms[j]);
		      sub->setRange(offset, rans[j]);
		      offset--;
		    }
		}
	      DEBUG_ASSERT(offset == 0);
		  PrologValue term1(heap.newSubstitutionBlockList(sub, AtomTable::nil), term.getTerm());

              if (new_term.getSubstitutionBlockList()->isNil())
                {
	          return notFreeInVar(domain_object_variable, new_term) && 
		    notFreeIn(object_variable, term1);
                }
              else
                {
	          return notFreeInVarSimp(domain_object_variable,new_term) && 
		         notFreeIn(object_variable, term1);
                 }
	    }
	}
    }
  
  DEBUG_ASSERT(term.getTerm()->isAnyVariable());
  
  if (total == 0)
    {
      term.setSubstitutionBlockList(AtomTable::nil);
      return notFreeIn(object_variable, term, term.getTerm());
    }
  if (total == size)
    {
      delayNFI(object_variable, term, term.getTerm());
    }
  else
    {
      SubstitutionBlock *sub = heap.newSubstitutionBlock(total);
  
      int offset = total;
      for (int j = size - 1; j >= 0; j--)
	{
	  if (doms[j] != NULL)
	    {
	      sub->setDomain(offset, doms[j]);
	      sub->setRange(offset, rans[j]);
	      offset--;
	    }
	}
      DEBUG_ASSERT(offset == 0);
      PrologValue term1(heap.newSubstitutionBlockList(sub, AtomTable::nil), term.getTerm());
      delayNFI(object_variable, term1, term.getTerm());
    }
  return true;
}

//
// Add extra info to all variables appearing in the term.
// This is needed so that when simplifying terms new variables with extra
// info are not produced because, otherwise it will cause problems
// with term copying.
//
void
Thread::addExtraInfoToVars(Object *term)
{
  DEBUG_ASSERT(term->variableDereference()->hasLegalSub());
  term = heap.dereference(term);

  switch (term->utag())
    {
    case Object::uConst:
    case Object::uObjVar:
      break;
    case Object::uVar:
      (void)addExtraInfo(OBJECT_CAST(Variable*, term));
      break;
    case Object::uCons:
      addExtraInfoToVars(OBJECT_CAST(Cons*, term)->getHead());
      addExtraInfoToVars(OBJECT_CAST(Cons*, term)->getTail());
      break;
    case Object::uStruct:
      {
	Structure* structure = OBJECT_CAST(Structure*, term);
	addExtraInfoToVars(structure->getFunctor());
	for (u_int i = 1; i <= structure->getArity(); i++)
	  {
	    addExtraInfoToVars(structure->getArgument(i));
	  }
      }
      break;
    case Object::uQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, term);
	addExtraInfoToVars(quant->getQuantifier());
	addExtraInfoToVars(quant->getBody());
      }
      break;
    case Object::uSubst:
      {
	Substitution* sterm = OBJECT_CAST(Substitution*, term);
	addExtraInfoToVars(sterm->getSubstitutionBlockList());
	addExtraInfoToVars(sterm->getTerm());
      }
      break;
    case Object::uSubsBlock:
      {
        DEBUG_ASSERT(term->isSubstitutionBlock());
	SubstitutionBlock* sub_block = OBJECT_CAST(SubstitutionBlock*, term);
	for (u_int i = 1; i <= sub_block->getSize(); i++)
	  {
	    addExtraInfoToVars(sub_block->getRange(i));
	  }
      }
      break;
    default:
      DEBUG_ASSERT(false);
      break;
    }
}




//
// Used in simplifying substitutions.
// Do trivial simplifications without resorting to simplify_term.
// "Complicated" constraints are ignored
//
bool
Thread::notFreeInNFISimp(ObjectVariable *object_variable,
			 PrologValue& term)
{
  heap.prologValueDereference(term);
  if (term.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term);
    }

  Object* t = term.getTerm();
  if (t->isConstant() || 
      (t->isAnyVariable() && term.getSubstitutionBlockList()->isNil()))
    {
      return notFreeIn(object_variable, term);
    }
  Object *sub_block_list = term.getSubstitutionBlockList();
  if (!t->isAnyVariable() || sub_block_list->isNil() || 
      !OBJECT_CAST(Cons* , sub_block_list)->getTail()->isNil())
    {
      return true;
    }
  
  DEBUG_ASSERT(OBJECT_CAST(Cons*, sub_block_list)->getHead()->isSubstitutionBlock());
  SubstitutionBlock *sub_block = 
    OBJECT_CAST(SubstitutionBlock *,
		OBJECT_CAST(Cons* , sub_block_list)->getHead());

  SubstitutionBlock *new_sub_block = 
    heap.newSubstitutionBlock(sub_block->getSize());

  for (size_t i = 1; i <= sub_block->getSize(); i++)
    {
      new_sub_block->setDomain(i, sub_block->getDomain(i));
      PrologValue ran(sub_block->getRange(i));
      
      heap.prologValueDereference(ran);
      if (ran.getSubstitutionBlockList()->isCons())
	{
	  heap.dropSubFromTerm(*this, ran);
	}

      DEBUG_ASSERT(object_variable == object_variable->variableDereference());
      if (ran.getTerm()->isConstant() ||
	  ran.getTerm()->isObjectVariable() &&
	  ran.getSubstitutionBlockList()->isNil() &&
	  object_variable->distinctFrom(ran.getTerm()))
	{
	  new_sub_block->setRange(i, AtomTable::dollar);
	}
      else
	{
	  new_sub_block->setRange(i, sub_block->getRange(i));
	}
    }
  Cons* new_sub = 
    heap.newSubstitutionBlockList(new_sub_block, AtomTable::nil);
  PrologValue new_term(new_sub, t);


  Object *remember = new_term.getTerm();
  heap.prologValueDereference(new_term);
  if (remember == new_term.getTerm() && !new_term.getSubstitutionBlockList()->isNil() )
    {
      DEBUG_ASSERT(new_term.getTerm()->isAnyVariable());
      return notFreeInVarSimp(object_variable, new_term);
    }
  else
    {
      return notFreeInNFISimp(object_variable, new_term);
    }
}


//
// A C-level implementation of freeness_test.
// returns true if obvar is free in term
//         false if obvar is not free in term
//         unsure otherwise
// 
truth3 
Thread::freeness_test(ObjectVariable* obvar, PrologValue& term)
{
  DEBUG_ASSERT(obvar == obvar->variableDereference());
  heap.prologValueDereference(term);
  switch (term.getTerm()->utag())
    {
    case Object::uConst:
      {
	return false;
	break;
      }
    case Object::uCons:
      {
	PrologValue head(term.getSubstitutionBlockList(), 
			 OBJECT_CAST(Cons*, term.getTerm())->getHead());
	PrologValue tail(term.getSubstitutionBlockList(), 
			 OBJECT_CAST(Cons*, term.getTerm())->getTail());
	DEBUG_ASSERT(obvar == obvar->variableDereference());
	truth3 headtest = freeness_test(obvar, head);
	if (headtest == true)
	  {
	    return true;
	  }
	else
	  {
	    DEBUG_ASSERT(obvar == obvar->variableDereference());
	    return (freeness_test(obvar, tail) || headtest);
	  }
	break;
      }
    case Object::uStruct:
      {
	Structure* termstruct = OBJECT_CAST(Structure*, term.getTerm());
	u_int arity = termstruct->getArity();
	truth3 result = false;
	for (u_int i = 0; i <= arity; i++)
	  {	   
	    PrologValue arg(term.getSubstitutionBlockList(), 
			    termstruct->getArgument(i));
	    DEBUG_ASSERT(obvar == obvar->variableDereference());
	    truth3 argtest = freeness_test(obvar, arg);
	    if (argtest == true)
	      {
		return true;
	      }
	    else
	      {
		result = (result || argtest);
	      }
	  }
	return result;
	break;
      }
    case Object::uQuant:
      {
	DEBUG_ASSERT(obvar == obvar->variableDereference());
	return freeness_test_quant(obvar, term);
	break;
      }
    case Object::uVar:
      {
	DEBUG_ASSERT(obvar == obvar->variableDereference());
	return freeness_test_var(obvar, term);
	break;
      }
    case Object::uObjVar:
      {
	DEBUG_ASSERT(obvar == obvar->variableDereference());
	return freeness_test_obvar(obvar, term);
	break;
      }
    default:
      {
	DEBUG_ASSERT(false);
	return false;
      }
    }
  return false;
}


//
// freeness_test_quant does the freeness test on a quantified term
//
truth3 
Thread::freeness_test_quant(ObjectVariable* obvar, PrologValue& term)
{
  QuantifiedTerm* quant = 
    OBJECT_CAST(QuantifiedTerm*, term.getTerm());

  // Test the quantifier
  PrologValue q(term.getSubstitutionBlockList(), quant->getQuantifier());
  DEBUG_ASSERT(obvar == obvar->variableDereference());
  truth3 qtest = freeness_test(obvar, q);
  if (qtest == true)
    {
      return true;
    }
  
  // Test the "types" in the bound variable list and push the
  // binding object variables onto the push down stack in preparation
  // for testing the body.
  size_t old_size = pushDownStack.size();
  truth3 result = false;
  Object *bound_var_list =
    quant->getBoundVars()->variableDereference();
  for (;
       bound_var_list->isCons();
       bound_var_list = 
	 OBJECT_CAST(Cons *, bound_var_list)->getTail()->variableDereference())
    {
      Object *head = OBJECT_CAST(Cons *, bound_var_list)->getHead()->variableDereference();
      if (head->isStructure())
	{
	  // A "typed" binder
	  Structure *structure = OBJECT_CAST(Structure *, head);

	  DEBUG_ASSERT(structure->getFunctor() == AtomTable::colon &&
		       structure->getArity() == 2);

	  Object *colon_object_variable 
	    = structure->getArgument(1)->variableDereference();

	  DEBUG_ASSERT(colon_object_variable->isObjectVariable());
	  PrologValue colon(term.getSubstitutionBlockList(), 
			    structure->getArgument(2));
	  DEBUG_ASSERT(obvar == obvar->variableDereference());
	  truth3 colontest = freeness_test(obvar, colon);
	  if (colontest == true)
	    {
	      pushDownStack.popNEntries(pushDownStack.size() - old_size);
	      return true;
	    }
	  result = (result || colontest);
	  pushDownStack.push(colon_object_variable);
	}
      else
	{
	  pushDownStack.push(head);
	}
    }
  if (bound_var_list->isVariable())
    {
      // An open binding list
      pushDownStack.popNEntries(pushDownStack.size() - old_size);
      return truth3::UNSURE;
    }
  // Test the body - build up a substitution that replaces the bound vars
  // with a $ and add this substitution to the outer substitution
  DEBUG_ASSERT(bound_var_list->isNil());
  size_t items = pushDownStack.size() - old_size;
  if (items == 0)
    {
      PrologValue body(term.getSubstitutionBlockList(), quant->getBody());
      DEBUG_ASSERT(obvar == obvar->variableDereference());
      return (freeness_test(obvar, body) || result);
    }
  SubstitutionBlock *sub_block = heap.newSubstitutionBlock(items);
  for (size_t i = items; i > 0; i--)
    {
      sub_block->setRange(i, AtomTable::dollar);
      sub_block->setDomain(i, pushDownStack.pop()->variableDereference());
    }
  DEBUG_ASSERT(old_size == pushDownStack.size());
  Object *nfi_sub_block_list = 
    heap.newSubstitutionBlockList(sub_block, term.getSubstitutionBlockList());
  
  PrologValue body(nfi_sub_block_list, quant->getBody());
  DEBUG_ASSERT(obvar == obvar->variableDereference());
  return (freeness_test(obvar, body) || result);
}

//
// freeness_test_var does the freeness test on a var term.
// This is done in a similar way to simplify_term - each domain element
// of each substitution replaces the variable and retry_delays determines if
// this domain element needs to be considered. If it does the corresponding
// range element is checked with the appropriate extra constraints added.
// Finally obvar is used as the "final domain" element.
// If none of the range elements contain a free occurrence of obvar then
// neither does the term.
// If all the range elements contain a free occurrence then so does the term.
// Otherwise - UNSURE.
//
truth3 
Thread::freeness_test_var(ObjectVariable* obvar, PrologValue& term)
{
  if (term.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term);
    }
  truth3 result = false;

  // Save state
  heapobject* savesavedtop = heap.getSavedTop();
  heapobject* savedHT = heap.getTop();
  TrailLoc savedBindingTrailTop = bindingTrail.getTop();
  TrailLoc savedObjectTrailTop = objectTrail.getTop();
  TrailLoc savedIPTrailTop = ipTrail.getTop();
  TrailLoc savedTagTrailTop = tagTrail.getTop();
  TrailLoc savedRefTrailTop = refTrail.getTop();
  heap.setSavedTop(savedHT);

  // save old top of push down stack
  int old_size = pushDownStack.size();
  
  // process each substitution block
  for (Object* sub = term.getSubstitutionBlockList();
       sub->isCons();
       sub = OBJECT_CAST(Cons*, sub)->getTail())
    {
      SubstitutionBlock* sub_block = 
	OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());
      // process each substitution block
      size_t size = sub_block->getSize();
      for (size_t i = 1; i <= size; i++)
	{
	  DEBUG_ASSERT(sub_block->getDomain(i)->variableDereference()->isObjectVariable());

	  ObjectVariable* dom = 
	    OBJECT_CAST(ObjectVariable*, sub_block->getDomain(i)->variableDereference());
	  if (dom->isLocalObjectVariable())
	    {
	      continue;
	    }
	  bool found = false;
	  for (int j = pushDownStack.size(); j > old_size; )
	    {
	      j--;
	      Object* before = pushDownStack.getEntry(j);
	      if (before == dom)
		{
		  found = true;
		  break;
		}
	    }
	  if (found)
	    {
	      // domain element already processed so ignore
	      continue;
	    }
	  // Make dom different from all previous tested domain elements
	  for (int j = pushDownStack.size(); j > old_size; )
	    {
	      j--;
	      DEBUG_ASSERT(pushDownStack.getEntry(j)->isObjectVariable());
	      ObjectVariable* before = 
		OBJECT_CAST(ObjectVariable*, pushDownStack.getEntry(j));
	      DEBUG_ASSERT(dom == dom->variableDereference());
	      if (!dom->distinctFrom(before))
		{
		  setDistinct(dom, before);
		}
	    }
	  pushDownStack.push(dom);
	  if (gen_nfi_delays(dom, term.getTerm()) && retry_delays())
	    {
	      PrologValue newterm(term.getSubstitutionBlockList(), dom);
	      obvar = OBJECT_CAST(ObjectVariable*,
				  obvar->variableDereference());
	      result = (result || freeness_test(obvar, newterm));
	    }
	  // Restore state
	  bindingTrail.backtrackTo(savedBindingTrailTop);
	  objectTrail.backtrackTo(savedObjectTrailTop);
	  ipTrail.backtrackTo(savedIPTrailTop);
	  tagTrail.backtrackTo(savedTagTrailTop);
	  refTrail.backtrackTo(savedRefTrailTop);
	  heap.setTop(savedHT);
	  if (result != false)
	    {
	      break;
	    }
	}
      if (result != false)
	{
	  break;
	}
    }
  if (result != false)
    {
      pushDownStack.popNEntries(pushDownStack.size() - old_size);
      return truth3::UNSURE;
    }
  // add extra test for obvar
  ObjectVariable* dom = 
	    OBJECT_CAST(ObjectVariable*, obvar);
  bool found = false;
  for (int j = pushDownStack.size(); j > old_size; )
    {
      j--;
      Object* before = pushDownStack.getEntry(j);
      if (before == dom)
	{
	  found = true;
	  break;
	}
    }
  if (!found)
    {
      for (int j = pushDownStack.size(); j > old_size; )
	{
	  j--;
	  DEBUG_ASSERT(pushDownStack.getEntry(j)->isObjectVariable());
	  ObjectVariable* before = 
	    OBJECT_CAST(ObjectVariable*, pushDownStack.getEntry(j));
	  DEBUG_ASSERT(dom == dom->variableDereference());
	  if (!dom->distinctFrom(before))
	    {
	      setDistinct(dom, before);
	    }
	}
      if (gen_nfi_delays(dom, term.getTerm()) && retry_delays())
	{
	  PrologValue newterm(term.getSubstitutionBlockList(), dom);
	  obvar = OBJECT_CAST(ObjectVariable*, obvar->variableDereference());
	  result = (result || freeness_test(obvar, newterm));
	}
    }
  // Restore state
  bindingTrail.backtrackTo(savedBindingTrailTop);
  objectTrail.backtrackTo(savedObjectTrailTop);
  ipTrail.backtrackTo(savedIPTrailTop);
  tagTrail.backtrackTo(savedTagTrailTop);
  refTrail.backtrackTo(savedRefTrailTop);
  heap.setTop(savedHT);
  pushDownStack.popNEntries(pushDownStack.size() - old_size);
  heap.setSavedTop(savesavedtop);
  if (result == false)
    {
      return false;
    }
  else
    {
      return truth3::UNSURE;
    }
}

//
// freeness_test_obvar does the freeness test on an obvar term.
// Virtually the same as freeness_test_var except that the domain element
// and the term are unified.
//
truth3 
Thread::freeness_test_obvar(ObjectVariable* obvar, PrologValue& term)
{
  if (term.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term);
    }
  DEBUG_ASSERT(obvar == obvar->variableDereference());
  if (term.getSubstitutionBlockList()->isNil())
    {
      if (obvar == term.getTerm())
	{
	  return true;
	}
      else if (obvar->distinctFrom(OBJECT_CAST(ObjectVariable*, term.getTerm())))
	{
	  return false;
	}
      else
	{
	  return truth3::UNSURE;
	}
    }
  truth3 result = false;
  bool free_in_all = true;

  // Save state
  heapobject* savesavedtop = heap.getSavedTop();
  heapobject* savedHT = heap.getTop();
  TrailLoc savedBindingTrailTop = bindingTrail.getTop();
  TrailLoc savedObjectTrailTop = objectTrail.getTop();
  TrailLoc savedIPTrailTop = ipTrail.getTop();
  TrailLoc savedTagTrailTop = tagTrail.getTop();
  TrailLoc savedRefTrailTop = refTrail.getTop();
  heap.setSavedTop(savedHT);

  // save old top of push down stack
  int old_size = pushDownStack.size();
  
  // process each substitution block
  for (Object* sub = term.getSubstitutionBlockList();
       sub->isCons();
       sub = OBJECT_CAST(Cons*, sub)->getTail())
    {
      SubstitutionBlock* sub_block = 
	OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());
      // process each substitution block
      size_t size = sub_block->getSize();
      for (size_t i = 1; i <= size; i++)
	{
	  DEBUG_ASSERT(sub_block->getDomain(i)->variableDereference()->isObjectVariable());

	  ObjectVariable* dom = 
	    OBJECT_CAST(ObjectVariable*, sub_block->getDomain(i)->variableDereference());
	  if (dom->isLocalObjectVariable())
	    {
	      continue;
	    }
	  bool found = false;
	  for (int j = pushDownStack.size(); j > old_size; )
	    {
	      j--;
	      Object* before = pushDownStack.getEntry(j);
	      if (before == dom)
		{
		  found = true;
		  break;
		}
	    }
	  if (found)
	    {
	      continue;
	    }
	  for (int j = pushDownStack.size(); j > old_size; )
	    {
	      j--;
	      DEBUG_ASSERT(pushDownStack.getEntry(j)->isObjectVariable());
	      ObjectVariable* before = 
		OBJECT_CAST(ObjectVariable*, pushDownStack.getEntry(j));
	      DEBUG_ASSERT(dom == dom->variableDereference());
	      if (!dom->distinctFrom(before))
		{
		  setDistinct(dom, before);
		}
	    }
	  pushDownStack.push(dom);
	  DEBUG_ASSERT(dom == dom->variableDereference());
	  if (retry_delays() &&
	      !dom->distinctFrom(OBJECT_CAST(ObjectVariable*, term.getTerm())))
	    {
	      dom = OBJECT_CAST(ObjectVariable*,
				      dom->variableDereference());
	      bindObjectVariables(dom, OBJECT_CAST(ObjectVariable*, term.getTerm()->variableDereference()));
	      if (retry_delays())
		{
		  PrologValue newterm(term.getSubstitutionBlockList(), dom);
		  ObjectVariable* deref_obvar = OBJECT_CAST(ObjectVariable*,
							    obvar->variableDereference());
		  truth3 testnew = freeness_test(deref_obvar, newterm);
		  result = (result || testnew);
		  free_in_all = (free_in_all && (testnew == true));
		}
	    }
	  // Restore state
	  bindingTrail.backtrackTo(savedBindingTrailTop);
	  objectTrail.backtrackTo(savedObjectTrailTop);
	  ipTrail.backtrackTo(savedIPTrailTop);
	  tagTrail.backtrackTo(savedTagTrailTop);
	  refTrail.backtrackTo(savedRefTrailTop);
	  heap.setTop(savedHT);
	  if ((result != false) && (free_in_all != true))
	    {
	      break;
	    }
	}
      if ((result != false) && (free_in_all != true))
	{
	  break;
	}
    }
  if ((result != false) && (free_in_all != true))
    {
      pushDownStack.popNEntries(pushDownStack.size() - old_size);
      return truth3::UNSURE;
    }
  // add extra test for obvar
  ObjectVariable* dom = 
	    OBJECT_CAST(ObjectVariable*, obvar);
  bool found = false;
  for (int j = pushDownStack.size(); j > old_size; )
    {
      j--;
      Object* before = pushDownStack.getEntry(j);
      if (before == dom)
	{
	  found = true;
	  break;
	}
    }
  if (!found)
    {
      for (int j = pushDownStack.size(); j > old_size; )
	{
	  j--;
	  DEBUG_ASSERT(pushDownStack.getEntry(j)->isObjectVariable());
	  ObjectVariable* before = 
	    OBJECT_CAST(ObjectVariable*, pushDownStack.getEntry(j));
	  DEBUG_ASSERT(dom == dom->variableDereference());
	  if (!dom->distinctFrom(before))
	    {
	      setDistinct(dom, before);
	    }
	}
      DEBUG_ASSERT(dom == dom->variableDereference());
      if (retry_delays() &&
	  !dom->distinctFrom(OBJECT_CAST(ObjectVariable*, term.getTerm())))
	{
	  dom = OBJECT_CAST(ObjectVariable*,
			    dom->variableDereference());
	  bindObjectVariables(dom, OBJECT_CAST(ObjectVariable*, term.getTerm()->variableDereference()));
	  if (retry_delays())
	    {
	      PrologValue newterm(term.getSubstitutionBlockList(), dom);
	      ObjectVariable* deref_obvar = OBJECT_CAST(ObjectVariable*,
							obvar->variableDereference());
	      truth3 testnew = freeness_test(deref_obvar, newterm);
	      result = (result || testnew);
	      free_in_all = (free_in_all && (testnew == true));
	    }
	}
    }
  // Restore state
  bindingTrail.backtrackTo(savedBindingTrailTop);
  objectTrail.backtrackTo(savedObjectTrailTop);
  ipTrail.backtrackTo(savedIPTrailTop);
  tagTrail.backtrackTo(savedTagTrailTop);
  refTrail.backtrackTo(savedRefTrailTop);
  heap.setTop(savedHT);
  pushDownStack.popNEntries(pushDownStack.size() - old_size);
  heap.setSavedTop(savesavedtop);
  if (result == false)
    {
      return false;
    }
  else if (free_in_all == true)
    {
      return true;
    }
  else
    {
      return truth3::UNSURE;
    }
}

//
// Carry out a quick test to see if an object var is NFI a term.
// USed by dropSub to remove subs where possible.
//

bool
Thread::fastNFITerm(ObjectVariable* obvar, Object* term)
{
  DEBUG_ASSERT(obvar == obvar->variableDereference());
  DEBUG_ASSERT(term == term->variableDereference());
  switch (term->utag())
    {
    case Object::uConst:
      {
	return true;
	break;
      }
    case Object::uCons:
      {
	return(fastNFITerm(obvar, OBJECT_CAST(Cons*, term)->getHead()->variableDereference())
	       &&
	       fastNFITerm(obvar, OBJECT_CAST(Cons*, term)->getTail()->variableDereference())
	       );
	break;
      }
    case Object::uStruct:
      {
	Structure* termstruct = OBJECT_CAST(Structure*, term);
	u_int arity = termstruct->getArity();
	for (u_int i = 0; i <= arity; i++)
	  {	 
	    if (!fastNFITerm(obvar, termstruct->getArgument(i)->variableDereference()))
	      {
		return false;
	      }
	  }
	return true;
	break;
      }
    case Object::uQuant:
      {
	QuantifiedTerm* qterm = OBJECT_CAST(QuantifiedTerm*, term);
	if (!fastNFITerm(obvar, qterm->getQuantifier()->variableDereference()))
	  {
	    return false;
	  }
	Object *bound_var_list =
	  qterm->getBoundVars()->variableDereference();

	bool found = false;
	for (;
	     bound_var_list->isCons();
	     bound_var_list = OBJECT_CAST(Cons *, bound_var_list)->getTail()->variableDereference())
	  {
	    Object *head = OBJECT_CAST(Cons *, bound_var_list)->getHead()->variableDereference();
	    if (head->isStructure())
	      {
		// A "typed" binder
		Structure *structure = OBJECT_CAST(Structure *, head);
		
		DEBUG_ASSERT(structure->getFunctor() == AtomTable::colon &&
			     structure->getArity() == 2);
		
		if (!fastNFITerm(obvar, structure->getArgument(2)->variableDereference()))
		  {
		    return false;
		  }
		if (structure->getArgument(1)->variableDereference() == obvar)
		  {
		    found = true;
		  }
	      }
	    else
	      {
		if (head == obvar)
		  {
		    found = true;
		  }
	      }
	  }
	if (bound_var_list->isVariable())
	  {
	    return false;
	  }
	if (found)
	  {
	    return true;
	  }
	return (fastNFITerm(obvar, qterm->getBody()->variableDereference()));
	break;
      }
    case Object::uVar:
      {
	return (isDelayNFI(obvar, term));
	break;
      }
    case Object::uObjVar:
      {
	return OBJECT_CAST(ObjectVariable*, obvar)->distinctFrom(term);
	break;
      }
    case Object::uSubst:
      {
	Substitution* sterm = OBJECT_CAST(Substitution*, term);
	bool found = false;
	for (Object* sub = sterm->getSubstitutionBlockList();
	     sub->isCons();
	     sub = OBJECT_CAST(Cons*, sub)->getTail())
	  {
	    SubstitutionBlock* sub_block = 
	      OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());
	    // process each substitution block
	    size_t size = sub_block->getSize();
	    for (size_t i = 1; i <= size; i++)
	      {
		if (!fastNFITerm(obvar, sub_block->getRange(i)->variableDereference()))
		  {
		    return false;
		  }
		if ( sub_block->getDomain(i)->variableDereference() == obvar)
		  {
		    found = true;
		  }
	      }
	  }
	if (found)
	  {
	    return true;
	  }
	return (fastNFITerm(obvar, sterm->getTerm()->variableDereference()));
	break; 

      }
    default:
      {
	DEBUG_ASSERT(false);
	return false;
      }
    }
}
