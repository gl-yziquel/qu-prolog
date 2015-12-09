// occurs_check.cc - 	Performing occurs check.
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: occurs_check.cc,v 1.9 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h" 
#include "truth3.h"

// 
// Do OC on sub and produce a simplified sub.
//
truth3
Thread::occursCheckSubAndSimplify(const CheckType type,
				  Object *sub_block_list,
				  Object*& simp_list, Object* var)
{
  assert(sub_block_list != NULL);
  assert(sub_block_list->isNil() ||
	       (sub_block_list->isCons() && 
		OBJECT_CAST(Cons *, 
			    sub_block_list)->isSubstitutionBlockList()));
  simp_list = heap.copySubSpine(sub_block_list, 
				AtomTable::nil, AtomTable::nil) ;
  Object* new_sub_block_list = simp_list;
  
  for (Object *list = sub_block_list;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail(),
	 new_sub_block_list = 
	 OBJECT_CAST(Cons *, new_sub_block_list)->getTail())
    {
      assert(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      
      SubstitutionBlock *sub_block = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      SubstitutionBlock *new_sub_block = 
	heap.newSubstitutionBlock(sub_block->getSize());
      if (sub_block->isInvertible())
	{
	  new_sub_block->makeInvertible();
	}
      for (size_t i = 1; i <= sub_block->getSize(); i++)
	{
	  PrologValue t(sub_block->getRange(i));
	  Object* newt;
	  if (occursCheckAndSimplify(type, t, newt, var) != false)
	    {
#ifdef QP_DEBUG
for (size_t j = i; j <= sub_block->getSize(); j++)
{
  new_sub_block->setDomain(i, sub_block->getDomain(i));
  new_sub_block->setRange(i, sub_block->getRange(i));
}
#endif // QP_DEBUG
	      return(truth3::UNSURE);
	    }
	  new_sub_block->setDomain(i, sub_block->getDomain(i));
	  new_sub_block->setRange(i, newt);
	}
      OBJECT_CAST(Cons*, new_sub_block_list)->setHead(new_sub_block);
    }
  return false;
}


//
// Do a simple OC on the substitution block.
//
bool
Thread::simpleOccursCheckSub(Object* subblock, Object* var) 
{
  assert(subblock->isSubstitutionBlock());
  SubstitutionBlock *sub = OBJECT_CAST(SubstitutionBlock*, subblock);
  for (size_t i = 1; i <= sub->getSize(); i++)
    {
      if (simpleOccursCheck(sub->getRange(i), var) != false)
	{
	  return true;
	}
    }
  return false;
}

//
// A simplified occurs check that looks for any occurrence of the supplied
// variable.
//
truth3
Thread::simpleOccursCheck(Object* term, Object* var)
{
  assert(var == var->variableDereference());
  assert(var->isVariable());

  Object* t = term->variableDereference();

  switch (t->tTag())
    {
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      return false;
      break;
    case Object::tVar:
      return (var == t);
      break;
    case Object::tObjVar:
      return false;
      break;
    case Object::tStruct:
      {
	Structure* s = OBJECT_CAST(Structure*, t);
	truth3 flag = false;
	for (size_t i = 0; i <= s->getArity(); i++)
	  {
	    truth3 f = simpleOccursCheck(s->getArgument(i), var);
	    if (f == true)
	      {
		return true;
	      }
            flag = flag || f;
	  }
	return flag;
      }
      break;
    case Object::tCons:
      {
	truth3 flag = false;
	for ( ; t->isCons(); 
	      t = OBJECT_CAST(Cons*, t)->getTail()->variableDereference())
	  {
	    truth3 f = simpleOccursCheck(OBJECT_CAST(Cons*, t)->getHead(), var);
	    if (f == true)
	      {
		return true;
	      }
	    flag = flag || f;
	  }
	return (simpleOccursCheck(t, var) || flag);
      }
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm*, t);
	return ( simpleOccursCheck(q->getBody(), var) ||
		 simpleOccursCheck(q->getBoundVars(), var) ||
		 simpleOccursCheck(q->getQuantifier(), var));
      }
      break;
    case Object::tSubst:
      {
	Substitution* s = OBJECT_CAST(Substitution*, t);
	truth3 flag = simpleOccursCheck(s->getTerm(), var);
	if (flag != false)
	  {
	    return flag;
	  }
	Object* sub = s->getSubstitutionBlockList();
	for ( ; sub->isCons(); sub = OBJECT_CAST(Cons*, sub)->getTail())
	  {
	    assert(sub == sub->variableDereference());
	    if (simpleOccursCheckSub(OBJECT_CAST(Cons*, sub)->getHead(), var)
		!= false)
	      {
		return truth3::UNSURE;
	      }
	  }
	assert(sub->isNil());
	return false;
      }
      break;
    default:
      assert(false);
      return false;
    }
}

//
// A "full" occurs check with the term simplified (if check succeeds).
//
truth3
Thread::occursCheckAndSimplify(const CheckType type, 
			       PrologValue& term, Object*& simpterm, 
			       Object* var)
{
  PrologValue tmpterm(term.getSubstitutionBlockList(), term.getTerm());
  heap.prologValueDereference(tmpterm);
  switch (tmpterm.getTerm()->tTag())
    {
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      simpterm = tmpterm.getTerm();
      return false;
      break;
    case Object::tStruct:
      {
	Structure* s = OBJECT_CAST(Structure*, tmpterm.getTerm());
	assert(s->getArity() <= MaxArity);
	Structure* news = heap.newStructure(s->getArity());
	truth3 flag = false;
	for (size_t i = 0; i <= s->getArity(); i++)
	  {
	    PrologValue t(tmpterm.getSubstitutionBlockList(), s->getArgument(i));
	    Object* arg;
	    truth3 f = occursCheckAndSimplify(type, t, arg, var);
	    if (f == true)
	      {
		return true;
	      }
	    flag = flag || f;
	    news->setArgument(i, arg);
	  }
	simpterm = news;
	return flag;
      }
      break;
    case Object::tCons:
      {
	Cons* c = OBJECT_CAST(Cons*, tmpterm.getTerm());
	Object* head;
	Object* tail;
	PrologValue h(tmpterm.getSubstitutionBlockList(), c->getHead());
	PrologValue t(tmpterm.getSubstitutionBlockList(), c->getTail());
	truth3 flag = 
	  occursCheckAndSimplify(type, h, head, var) ||
	  occursCheckAndSimplify(type, t, tail, var);
	simpterm = heap.newCons(head, tail);
	return flag;
      }
      break;
    case Object::tVar:
      if (var == tmpterm.getTerm())
	{
	  return true;
	}
      else if (type == DIRECT)
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  simpterm = heap.prologValueToObject(tmpterm);
	  return false;
	}
      else
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  if (tmpterm.getSubstitutionBlockList()->isNil())
	    {
	      simpterm = tmpterm.getTerm();
	      return false;
	    }
	  Object* simpsub;
	  truth3 flag = 
	    occursCheckSubAndSimplify(type, 
				      tmpterm.getSubstitutionBlockList(),
				      simpsub, var);
          assert(simpsub->isCons());
	  simpterm = heap.newSubstitution(simpsub, tmpterm.getTerm());
	  return flag;
	}
      break;
    case Object::tObjVar:
      if (type == DIRECT) 
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  simpterm = heap.prologValueToObject(tmpterm);
	  return false;
	}
      else
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  if (tmpterm.getSubstitutionBlockList()->isNil())
	    {
	      simpterm = tmpterm.getTerm();
	      return false;
	    }
	  Object* simpsub;
	  truth3 flag = 
	    occursCheckSubAndSimplify(type, 
				      tmpterm.getSubstitutionBlockList(),
				      simpsub, var);
          assert(simpsub->isCons());
	  simpterm = heap.newSubstitution(simpsub, tmpterm.getTerm());
	  return flag;
	}
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm*, tmpterm.getTerm());
	PrologValue pvq(q->getQuantifier());
	PrologValue pvv(q->getBoundVars());
	PrologValue pvb(q->getBody());
	Object* newquant;
	Object* newbv;
	Object* newbody;
	
	truth3 flag = 
	  occursCheckAndSimplify(type, pvq, newquant, var) ||
	  occursCheckAndSimplify(type, pvv, newbv, var) ||
	  occursCheckAndSimplify(type, pvb, newbody, var);
	QuantifiedTerm* newt = heap.newQuantifiedTerm();
	newt->setQuantifier(newquant);
	newt->setBoundVars(newbv);
	newt->setBody(newbody);
	
	if (flag == false)
	  {
	    if (tmpterm.getSubstitutionBlockList()->isCons())
	      {
		heap.dropSubFromTerm(*this, tmpterm);
	      }
	    if (tmpterm.getSubstitutionBlockList()->isNil())
	      {
		simpterm = tmpterm.getTerm();
		return false;
	      }
	    Object* simpsub;
	    flag = 
	      occursCheckSubAndSimplify(type, 
					tmpterm.getSubstitutionBlockList(),
					simpsub, var);
            assert(simpsub->isCons());
	    simpterm = heap.newSubstitution(simpsub, newt);
	  }
	return flag; 
      }
    default:
      assert(false);
      return true;
    }
}




