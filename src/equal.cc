// equal.cc - 
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
// $Id: equal.cc,v 1.7 2002/07/26 00:39:57 qp Exp $

// #include "atom_table.h"
#include "heap_qp.h"
#include "thread_qp.h"
#include "truth3.h"
extern AtomTable *atoms;
//
// Call $equal_var/2 which is defined in Prolog.
//
bool
Thread::equalVariable(PrologValue& var1, PrologValue& var2)
{
  return false;
}

//
// Call $equal_object_variable/2 which is defined in Prolog.
//
bool
Thread::equalObjectVariable(PrologValue& object_variable1,
			    PrologValue& object_variable2)
{
  return false;
}


//
// C-level implementation of ==
// Assumes terms have been dereferenced
//
bool 
Thread::equalEqual(PrologValue& term1, PrologValue& term2, int& counter)
{
  if (term1.getTerm()->utag() != term2.getTerm()->utag())
    {
      // different types
      return false;
    }

  if (term1.getTerm() == term2.getTerm() &&
      term1.getSubstitutionBlockList() == term2.getSubstitutionBlockList())
    {
      // identical pointers
      return true;
    }

  DEBUG_ASSERT(term1.getTerm()->utag() == term2.getTerm()->utag());
  switch (term1.getTerm()->utag())
    {
    case Object::uConst:
      return (term1.getTerm()->equalConstants(term2.getTerm()));
      break;
    case Object::uCons:
      {
	Cons* list1 = OBJECT_CAST(Cons*, term1.getTerm());
	Cons* list2 = OBJECT_CAST(Cons*, term2.getTerm());
	PrologValue head1(term1.getSubstitutionBlockList(), list1->getHead());
	PrologValue head2(term2.getSubstitutionBlockList(), list2->getHead());
	heap.prologValueDereference(head1);
	heap.prologValueDereference(head2);
	if (!equalEqual(head1, head2, counter))
	  {
	    return false;
	  }
	PrologValue tail1(term1.getSubstitutionBlockList(), list1->getTail());
	PrologValue tail2(term2.getSubstitutionBlockList(), list2->getTail());
	heap.prologValueDereference(tail1);
	heap.prologValueDereference(tail2);
	return (equalEqual(tail1, tail2, counter));
	break;
      }
    case Object::uStruct:
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1.getTerm());
	Structure* struct2 = OBJECT_CAST(Structure*, term2.getTerm());
	if (struct1->getArity() != struct2->getArity())
	  {
	    return false;
	  }
	for (u_int i = 0; i <= struct1->getArity(); i++)
	  {
	    PrologValue arg1(term1.getSubstitutionBlockList(), 
			     struct1->getArgument(i));
	    PrologValue arg2(term2.getSubstitutionBlockList(), 
			     struct2->getArgument(i));
	   
	    heap.prologValueDereference(arg1);
	    heap.prologValueDereference(arg2);
	    if (!equalEqual(arg1, arg2, counter))
	      {
		return false;
	      }
	  }
	return true;
	break;
      }
    case Object::uQuant:
      {
	QuantifiedTerm* quant1 = OBJECT_CAST(QuantifiedTerm*, term1.getTerm());
	QuantifiedTerm* quant2 = OBJECT_CAST(QuantifiedTerm*, term2.getTerm());
	PrologValue q1(term1.getSubstitutionBlockList(), 
		       quant1->getQuantifier());
	PrologValue q2(term2.getSubstitutionBlockList(), 
		       quant2->getQuantifier());
	heap.prologValueDereference(q1);
	heap.prologValueDereference(q2);
	if (!equalEqual(q1, q2, counter))
	  {
	    return false;
	  }
	int old_size = pushDownStack.size();

	Object* boundvars1 = quant1->getBoundVars();
	Object* boundvars2 = quant2->getBoundVars();
	for (boundvars1 = boundvars1->variableDereference(),
	       boundvars2 = boundvars2->variableDereference();
	     boundvars1->isCons() && boundvars2->isCons() ;
	     boundvars1 = OBJECT_CAST(Cons*, boundvars1)->getTail()->variableDereference(),
	       boundvars2 = OBJECT_CAST(Cons*, boundvars2)->getTail()->variableDereference())
	  {
	    Object* head1 = OBJECT_CAST(Cons*, boundvars1)->getHead()->variableDereference();
	    Object* head2 = OBJECT_CAST(Cons*, boundvars2)->getHead()->variableDereference();
	    
	    if (head1->isObjectVariable() && head2->isObjectVariable())
	      {
		pushDownStack.push(head1);
		pushDownStack.push(head2);
	      }    
	    else if (head1->isStructure() && head2->isStructure())
	      {
		DEBUG_ASSERT(OBJECT_CAST(Structure*, head1)->getFunctor()
			     == AtomTable::colon);
		DEBUG_ASSERT(OBJECT_CAST(Structure*, head1)->getArity() == 2);
		DEBUG_ASSERT(OBJECT_CAST(Structure*, head2)->getFunctor()
			     == AtomTable::colon);
		DEBUG_ASSERT(OBJECT_CAST(Structure*, head1)->getArity() == 2);
		
		pushDownStack.push(OBJECT_CAST(Structure*, head1)->getArgument(1)->variableDereference());
		pushDownStack.push(OBJECT_CAST(Structure*, head2)->getArgument(1)->variableDereference());
		PrologValue t1(term1.getSubstitutionBlockList(),
				OBJECT_CAST(Structure*, head1)->getArgument(2));
		PrologValue t2(term2.getSubstitutionBlockList(),
			       OBJECT_CAST(Structure*, head2)->getArgument(2));
		heap.prologValueDereference(t1);
		heap.prologValueDereference(t2);
		if (!equalEqual(t1, t2, counter))
		  {
		    pushDownStack.popNEntries(pushDownStack.size() - old_size);
		    return false;
		  }
	      }
	    else
	      {
		pushDownStack.popNEntries(pushDownStack.size() - old_size);
		return false;
	      }
	  }
	if (boundvars1 != boundvars2)
	  {
	    pushDownStack.popNEntries(pushDownStack.size() - old_size);
	    return false;
	  }
	size_t n = (pushDownStack.size() - old_size)/2;
	if (n == 0)
	  {
	    PrologValue body1(term1.getSubstitutionBlockList(), 
			      quant1->getBody());
	    PrologValue body2(term2.getSubstitutionBlockList(), 
			      quant2->getBody());
	    heap.prologValueDereference(body1);
	    heap.prologValueDereference(body2);
	    return (equalEqual(body1, body2, counter));
	  }
	// Non-empty binding list
	SubstitutionBlock* block1 = heap.newSubstitutionBlock(n);
	SubstitutionBlock* block2 = heap.newSubstitutionBlock(n);
	for (size_t i = 1; i <= n; )
	  {
	    Object* o2 = pushDownStack.pop()->variableDereference();
	    Object* o1 = pushDownStack.pop()->variableDereference();
	    Structure* ranstruct = heap.newStructure(1);
	    ranstruct->setFunctor(atoms->add("$$quant"));
	    ranstruct->setArgument(1, heap.newNumber(counter++));
	    DEBUG_ASSERT(o1->isObjectVariable());
	    DEBUG_ASSERT(o2->isObjectVariable());
	    block2->setDomain(i, OBJECT_CAST(ObjectVariable*, o2));
	    block1->setDomain(i, OBJECT_CAST(ObjectVariable*, o1));
	    block1->setRange(i, ranstruct);
	    block2->setRange(i, ranstruct);
	    i++;     
	  }
	Object* subs1 = heap.newSubstitutionBlockList(block1, term1.getSubstitutionBlockList());
	Object* subs2 = heap.newSubstitutionBlockList(block2, term2.getSubstitutionBlockList());
	PrologValue body1(subs1, quant1->getBody());
	PrologValue body2(subs2, quant2->getBody());
	heap.prologValueDereference(body1);
	heap.prologValueDereference(body2);
	return (equalEqual(body1, body2, counter));
	break;
      }
    case Object::uVar:
      {
	if (term1.getTerm() != term2.getTerm())
	  {
	    return false;
	  }
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	if (term1.getSubstitutionBlockList() 
	    == term2.getSubstitutionBlockList())
	  {
	    return true;
	  }
	// At this point we save the state for backtracking - at the end of 
	// test we reset the state.
	heapobject* savesavedtop = heap.getSavedTop();
	heapobject* savedHT = heap.getTop();
        TrailLoc savedBindingTrailTop = bindingTrail.getTop();
	TrailLoc savedObjectTrailTop = objectTrail.getTop();
	TrailLoc savedIPTrailTop = ipTrail.getTop();
	TrailLoc savedTagTrailTop = tagTrail.getTop();
	TrailLoc savedRefTrailTop = refTrail.getTop();
	heap.setSavedTop(savedHT);

	bool result;
	Object* obvar = heap.newObjectVariable();
	bindAndTrail(term1.getTerm(), obvar);
	(void)retry_delays();
	PrologValue pt1(term1.getSubstitutionBlockList(), term1.getTerm());
	PrologValue pt2(term2.getSubstitutionBlockList(), term2.getTerm());
	heap.prologValueDereference(pt1);
	heap.prologValueDereference(pt2);
	result = equalEqual(pt1, pt2, counter);

	// Restore state
	bindingTrail.backtrackTo(savedBindingTrailTop);
	objectTrail.backtrackTo(savedObjectTrailTop);
	ipTrail.backtrackTo(savedIPTrailTop);
	tagTrail.backtrackTo(savedTagTrailTop);
	refTrail.backtrackTo(savedRefTrailTop);
	heap.setTop(savedHT);
	heap.setSavedTop(savesavedtop);
	return result;
	break;
      }
    case Object::uObjVar:
      {
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	if (term1.getSubstitutionBlockList()->isNil() 
	    && term2.getSubstitutionBlockList()->isNil())
	  {
	    return (term1.getTerm() == term2.getTerm());
	  }
	Object* domain = NULL;
	Object* term;
	if (!term1.getSubstitutionBlockList()->isNil())
	  {
	    Cons *sub_block_list = 
	      OBJECT_CAST(Cons *, term1.getSubstitutionBlockList());
	    SubstitutionBlock *sub_block =
	      OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());
	    DEBUG_ASSERT(sub_block->getSize() > 0);
	    term = term1.getTerm();
	    size_t size = sub_block->getSize();
	    for (size_t i = 1; i <= size; i++)
	      {
		domain = sub_block->getDomain(i)->variableDereference();
		if(!OBJECT_CAST(ObjectVariable*, domain)->distinctFrom(OBJECT_CAST(ObjectVariable*, term)))
		  {
		    break;
		  }
	      }
	  }
	else
	  {
	    DEBUG_ASSERT(!term2.getSubstitutionBlockList()->isNil());
	    Cons *sub_block_list = 
	      OBJECT_CAST(Cons *, term2.getSubstitutionBlockList());
	    SubstitutionBlock *sub_block =
	      OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());
	    DEBUG_ASSERT(sub_block->getSize() > 0);
	    term = term2.getTerm();
	    size_t size = sub_block->getSize();
	    for (size_t i = 1; i <= size; i++)
	      {
		domain = sub_block->getDomain(i)->variableDereference();
		if(!OBJECT_CAST(ObjectVariable*, domain)->distinctFrom(OBJECT_CAST(ObjectVariable*, term)))
		  {
		    break;
		  }
	      }
	  }
	// At this point we save the state for backtracking - at the end of 
	// test we reset the state.
	heapobject* savesavedtop = heap.getSavedTop();
	heapobject* savedHT = heap.getTop();
        TrailLoc savedBindingTrailTop = bindingTrail.getTop();
	TrailLoc savedObjectTrailTop = objectTrail.getTop();
	TrailLoc savedIPTrailTop = ipTrail.getTop();
	TrailLoc savedTagTrailTop = tagTrail.getTop();
	TrailLoc savedRefTrailTop = refTrail.getTop();
	heap.setSavedTop(savedHT);

	bool result;
	bindAndTrail(term, domain);
	if (!retry_delays())
	  {
	    result = true;
	  }
	else
	  {
	    PrologValue pt1(term1.getSubstitutionBlockList(), term1.getTerm());
	    PrologValue pt2(term2.getSubstitutionBlockList(), term2.getTerm());
	    heap.prologValueDereference(pt1);
	    heap.prologValueDereference(pt2);
	    result = equalEqual(pt1, pt2, counter);
	  }

	// Restore state
	bindingTrail.backtrackTo(savedBindingTrailTop);
	objectTrail.backtrackTo(savedObjectTrailTop);
	ipTrail.backtrackTo(savedIPTrailTop);
	tagTrail.backtrackTo(savedTagTrailTop);
	refTrail.backtrackTo(savedRefTrailTop);
	heap.setTop(savedHT);
	
	if (!result)
	  {
	    heap.setSavedTop(savesavedtop);
	    return false;
	  }
	DEBUG_ASSERT(domain->isObjectVariable());
	DEBUG_ASSERT(term->isObjectVariable());
	DEBUG_ASSERT(domain == domain->variableDereference());
	DEBUG_ASSERT(!OBJECT_CAST(ObjectVariable*, domain)->distinctFrom(OBJECT_CAST(ObjectVariable*, term)));
	setDistinct(OBJECT_CAST(ObjectVariable*, domain),
		    OBJECT_CAST(ObjectVariable*, term));
	if (!retry_delays())
	  {
	    result = true;
	  }
	else
	  {
	    PrologValue pt1(term1.getSubstitutionBlockList(), term1.getTerm());
	    PrologValue pt2(term2.getSubstitutionBlockList(), term2.getTerm());
	    heap.prologValueDereference(pt1);
	    heap.prologValueDereference(pt2);
	    result = equalEqual(pt1, pt2, counter);
	  }
	// Restore state
	bindingTrail.backtrackTo(savedBindingTrailTop);
	objectTrail.backtrackTo(savedObjectTrailTop);
	ipTrail.backtrackTo(savedIPTrailTop);
	tagTrail.backtrackTo(savedTagTrailTop);
	refTrail.backtrackTo(savedRefTrailTop);
	heap.setTop(savedHT);
	heap.setSavedTop(savesavedtop);

	return result;
	break;
      }
    default:
      DEBUG_ASSERT(false);
      return(false);   
    }
}

//
// C-level version of simplify_term
//

//
// Top-level - returns true iff some simplification was done.
//
bool
Thread::simplify_term(PrologValue& term, Object*& simpterm)
{
  heap.prologValueDereference(term);
  switch (term.getTerm()->utag())
    {
    case Object::uConst:
      {
	simpterm = term.getTerm();
	return false;
	break;
      }
    case Object::uCons:
      {
	PrologValue head(term.getSubstitutionBlockList(), OBJECT_CAST(Cons*, term.getTerm())->getHead());
	PrologValue tail(term.getSubstitutionBlockList(), OBJECT_CAST(Cons*, term.getTerm())->getTail());
	Object *simphead, *simptail;
	bool headsimplified = simplify_term(head, simphead);
	bool tailsimplified = simplify_term(tail, simptail);
	if (!term.getSubstitutionBlockList()->isNil()
	    || headsimplified || tailsimplified)
	  {
	    simpterm = heap.newCons(simphead, simptail);
	    return true;
	  }
	else
	  {
	    simpterm = term.getTerm();
	    return false;
	  }
	break;
      }
    case Object::uStruct:
      {
	Structure* termstruct = OBJECT_CAST(Structure*, term.getTerm());
	u_int arity = termstruct->getArity();
	Object* allargs[arity+1];
	bool is_simplified = !term.getSubstitutionBlockList()->isNil();
	for (u_int i = 0; i <= arity; i++)
	  {
	    PrologValue arg(term.getSubstitutionBlockList(), 
			    termstruct->getArgument(i));
	    is_simplified = simplify_term(arg, allargs[i]) || is_simplified;
	  }
	if (is_simplified)
	  {
	    Structure* newstruct = heap.newStructure(arity);
	    for (u_int i = 0; i <= arity; i++)
	      {
		newstruct->setArgument(i, allargs[i]);
	      }
	    simpterm = newstruct;
	    return true;
	  }
	else
	  {
	    simpterm = term.getTerm();
	    return false;
	  }
	break;
      }
    case Object::uQuant:
      {
	QuantifiedTerm* quant = 
	  OBJECT_CAST(QuantifiedTerm*, term.getTerm());
	bool is_simplified;
	Object *simpq, *simpbound, *simpbody, *simpquant;
	PrologValue q(quant->getQuantifier());
	PrologValue bv(quant->getBoundVars());
	PrologValue body(quant->getBody());
	is_simplified = simplify_term(q, simpq);
	is_simplified =  simplify_term(bv, simpbound) || is_simplified;
	is_simplified =  simplify_term(body, simpbody) || is_simplified;
	if (is_simplified)
	  {
	    QuantifiedTerm* newq = heap.newQuantifiedTerm();
	    newq->setQuantifier(simpq);
	    newq->setBoundVars(simpbound);
	    newq->setBody(simpbody);
	    simpquant = newq;
	  }
	else
	  {
	    simpquant = term.getTerm();
	  }
	if (term.getSubstitutionBlockList()->isNil())
	  {
	    simpterm = simpquant;
	    return is_simplified;
	  }
	else
	  {
	    PrologValue st(term.getSubstitutionBlockList(), simpquant);
	    return (simplify_sub_term(st, simpterm, AtomTable::success) 
		    || is_simplified);
	  }
	break;
      }
    case Object::uVar:
      {
	Object* savedsub = term.getSubstitutionBlockList();
	if (savedsub->isCons())
	  {
	    heap.dropSubFromTerm(*this, term);
	  }
	bool is_simplified = (savedsub != 
			      term.getSubstitutionBlockList());
	if (term.getSubstitutionBlockList()->isNil())
	  {
	    simpterm = term.getTerm();
	    return is_simplified;
	  }
	// Var has a sub so simplify the sub
	return (simplify_sub_term(term, simpterm, AtomTable::success) 
		|| is_simplified);
	break;
      }
    case Object::uObjVar:
      {
	Object* savedsub = term.getSubstitutionBlockList();
	if (savedsub->isCons())
	  {
	    heap.dropSubFromTerm(*this, term);
	  }
	bool is_simplified = (savedsub != 
			      term.getSubstitutionBlockList());
	if (term.getSubstitutionBlockList()->isNil())
	  {
	    simpterm = term.getTerm();
	    return is_simplified;
	  }
	heap.prologValueDereference(term);
	is_simplified = (savedsub != 
			 term.getSubstitutionBlockList());
	if (term.getTerm()->utag() != Object::uObjVar)
	  {
	    (void)simplify_term(term, simpterm);
	    return true;
	  }
	// ObjVar has a sub so simplify the sub
	return (simplify_sub_term(term, simpterm, AtomTable::success) 
		|| is_simplified);
	break;
      }
    default:
      DEBUG_ASSERT(false);
      return false;
    }
  return true;
}


bool
Thread::simplify_sub_term(PrologValue& term, Object*& simpterm, Object* tester)
{
  // allocate buffer
  Object* index = 
    heap.newNumber(buffers.allocate(heap.getTop(), scratchpad.getTop()));
 
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
	  if (!retry_delays())
	    {
	      bindingTrail.backtrackTo(savedBindingTrailTop);
	      objectTrail.backtrackTo(savedObjectTrailTop);
	      ipTrail.backtrackTo(savedIPTrailTop);
	      tagTrail.backtrackTo(savedTagTrailTop);
	      refTrail.backtrackTo(savedRefTrailTop);
	      heap.setTop(savedHT);
	      continue;
	    }
	  if (term.getTerm()->isObjectVariable())
	    {
	      dom = OBJECT_CAST(ObjectVariable*, dom->variableDereference());
	      if (!dom->distinctFrom(OBJECT_CAST(ObjectVariable*, 
						 term.getTerm()->variableDereference())))
		{
		  bindObjectVariables(dom, OBJECT_CAST(ObjectVariable*, 
						       term.getTerm()->variableDereference()));
		  if (retry_delays())
		    {
		      Object* simpterm;
		      PrologValue newterm(term.getSubstitutionBlockList(), 
					  dom);
		      
		      (void)simplify_term(newterm, simpterm);
		      Object* result;
		      transform_with_tester(simpterm, result, tester);
		      Object* copydom = dom;
		      Object* succ = AtomTable::success;
		      (void)psi_copy_obvar_to_buffer_tail(index, copydom);
		      (void)psi_copy_to_buffer_tail(index, result, succ);
		    }
		}
	    }
	  else if (term.getTerm()->isVariable())
	    {
	      if (gen_nfi_delays(dom, term.getTerm()) && retry_delays())
		{
		  Object* simpterm;
		  PrologValue newterm(term.getSubstitutionBlockList(), dom);
		  (void)simplify_term(newterm, simpterm);
		  Object* result;
		  transform_with_tester(simpterm, result, tester);
		  Object* copydom = dom->variableDereference();
		  Object* succ = AtomTable::success;
		  (void)psi_copy_obvar_to_buffer_tail(index, copydom);
		  (void)psi_copy_to_buffer_tail(index, result, succ);
		}
	    }
	  else
	    {
	      DEBUG_ASSERT(term.getTerm()->isQuantifiedTerm());
	      DEBUG_ASSERT(!tester->isObjectVariable());
	      PrologValue qterm(term.getTerm());
	      DEBUG_ASSERT(dom == dom->variableDereference());
	      if (freeness_test(dom, qterm) != false)
		{
		  Object* simpterm;
		  PrologValue newterm(term.getSubstitutionBlockList(), dom);
		  (void)simplify_term(newterm, simpterm);
		  Object* copydom = dom;
		  Object* succ = AtomTable::success;
		  (void)psi_copy_obvar_to_buffer_tail(index, copydom);
		  (void)psi_copy_to_buffer_tail(index, simpterm, succ);
		} 
	    }
	  // Restore state
	  bindingTrail.backtrackTo(savedBindingTrailTop);
	  objectTrail.backtrackTo(savedObjectTrailTop);
	  ipTrail.backtrackTo(savedIPTrailTop);
	  tagTrail.backtrackTo(savedTagTrailTop);
	  refTrail.backtrackTo(savedRefTrailTop);
	  heap.setTop(savedHT);
	}	   
    }
  pushDownStack.popNEntries(pushDownStack.size() - old_size);
  heap.setSavedTop(savesavedtop);
  // Collect result
  Object* termterm = term.getTerm();
  (void)psi_make_sub_from_buffer(index, termterm, simpterm);
  (void)psi_dealloc_buffer(index);
  PrologValue psimp(simpterm);
  return (heap.fastEqual(term, psimp) != true);
}

bool
Thread::gen_nfi_delays(ObjectVariable* dom, Object* term)
{
  DEBUG_ASSERT(term->isVariable());
  Object* var_delays = OBJECT_CAST(Reference*, term)->getDelays();
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
	  pstruct->getFunctor() != AtomTable::nfi)
	{
	  continue;
	}
      // We have an unsolved nfi problem
      Object* obvar = pstruct->getArgument(1)->variableDereference();
      PrologValue pval(pstruct->getArgument(2));
      heap.prologValueDereference(pval);
      DEBUG_ASSERT(pval.getTerm() == term);
      pval.setTerm(dom);
      DEBUG_ASSERT(obvar->isObjectVariable());
      if (!notFreeInNFISimp(OBJECT_CAST(ObjectVariable*, obvar), pval))
	{
	  return false;
	}
    } 
  return true;
}

//
// When tester is an object variable this is used
// to check if tester is free in simpterm
// If it is then result = tester
// If not then result = '$'
// else if UNSURE result = simpterm
// If tester is not an object variable then result = simpterm
//
void
Thread::transform_with_tester(Object* simpterm, Object*& result, 
			      Object* tester)
{
  if (!tester->isObjectVariable())
    {
      result = simpterm;
      return;
    }
  PrologValue term(simpterm);
  tester = tester->variableDereference();
  truth3 free = freeness_test(OBJECT_CAST(ObjectVariable*, tester), term);
  if (free == true)
    {
      result = tester;
    }
  else if (free == false)
    {
      result = AtomTable::dollar;
    }
  else
    {
      result = simpterm;
    }
}




