// unify.cc - The Qu-Prolog  unify instructions.
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
// $Id: unify.cc,v 1.11 2002/07/26 00:39:58 qp Exp $

// #include "atom_table.h"
#include "global.h"
#include "thread_qp.h"

//
// The following define is used to constract a big switch statement
// in unify for the possible types of the terms being unified.
// !!!WARNING!!! This idea requires that 8 > Object::uSubst 
// (the highest tag)
//
#define CrossTag(t1, t2)	8 * (t1) + (t2)

//
// Extend open bound variable list. Extend shorter to match longer one.
// 
BoundVarState
Thread::extendBoundVarListLoop(Object* varSub, Object* variable,
			     Object* listSub, Object* list,
			     Object*& delayedVar,
			     const bool swap, bool in_quant)
{
  DEBUG_ASSERT(variable->isVariable());
  
  list = list->variableDereference();
  if (list->isNil())
    {
      if (unify(variable, list, in_quant))
	{
	  return(MATCH);
	}
      else
	{
	  return(MISMATCH);
	}
    }
  else if (list->isVariable())
    {
      delayedVar = list;
      return(DELAY);
    }
  else
    {
      DEBUG_ASSERT(list->isCons());

      Variable* newTail = heap.newVariable();
      newTail->setOccursCheck();
      BoundVarState state =
	extendBoundVarListLoop(varSub, newTail, listSub,
			       OBJECT_CAST(Cons*, list)->getTail(),
			       delayedVar, swap, in_quant);
      
      Cons* newList = heap.newCons();
      newList->setTail(newTail);

      Object* head = 
	OBJECT_CAST(Cons*, list)->getHead()->variableDereference();
      if (head->isObjectVariable())
	{
	  // 
	  // The corresponding element in the list is an object
	  // variable. Create new list - [ObjectVariable | var1].
	  //
	  ObjectVariable* objectVariable = heap.newObjectVariable();
	  newList->setHead(objectVariable);
	  
	  if (!unify(variable, newList, in_quant))
	    {
	      return (MISMATCH);
	    }

	  if (swap)
	    {
	      pushDownStack.push(head);
	      pushDownStack.push(objectVariable);
	    }
	  else
	    {
	      pushDownStack.push(objectVariable);
	      pushDownStack.push(head);
	    }
	}
      else 
	{
	  DEBUG_ASSERT(head->isStructure());
	  Structure* str = OBJECT_CAST(Structure*, head);
	  DEBUG_ASSERT(str->getArity() == 2 && 
		       str->getFunctor() == AtomTable::colon);
	  
	  //
	  // The corresponding element in the list is a
	  // structure of the form: x : t.  Create structure -
	  // ObjectVariable : var1.
	  //
	  ObjectVariable* objectVariable = heap.newObjectVariable();
	  Variable* type = heap.newVariable();
	  type->setOccursCheck();
	  
	  Structure* term = heap.newStructure(2, AtomTable::colon, 
					 objectVariable, type); 
	  newList->setHead(term);
	  //
	  // Get object variables from head.
	  //
	  Object* headObjectVariable 
	    = str->getArgument(1)->variableDereference();
	  DEBUG_ASSERT(headObjectVariable->isObjectVariable());
	  Object* headType = str->getArgument(2);
	  
	  //
	  // Unify term parts
	  // 
          DEBUG_ASSERT(varSub->isLegalSub());
          DEBUG_ASSERT(listSub->isLegalSub());
	  PrologValue t1(varSub, type);
	  PrologValue t2(listSub, headType);
	  heap.prologValueDereference(t1);
	  heap.prologValueDereference(t2);
	  
	  if (!unifyPrologValues(t1, t2, in_quant))
	    {
	      return(MISMATCH);
	    }
	
	  if (!unify(variable, newList, in_quant))
	    {
	      return (MISMATCH);
	    }
	  
	  if (swap)
	    {
	      pushDownStack.push(headObjectVariable);
	      pushDownStack.push(objectVariable);
	    }
	  else
	    {
	      pushDownStack.push(objectVariable);
	      pushDownStack.push(headObjectVariable);
	    }
      	}
      return(state);
    }
}

//
// Pair up bound variable lists.
// quantifier1 = s1 q1 BoundVarList1 term1
// quantifier2 = s2 q2 BoundVarList2 term2
//
BoundVarState
Thread::pairUpBoundVarList(PrologValue& quantifier1, PrologValue& quantifier2,
			 Object*& delayedVar, bool in_quant)
{
  DEBUG_ASSERT(quantifier1.getTerm()->isQuantifiedTerm());
  DEBUG_ASSERT(quantifier1.getTerm()->isQuantifiedTerm());

  Object* boundvars1
    = OBJECT_CAST(QuantifiedTerm*, quantifier1.getTerm())->getBoundVars();
  Object* boundvars2
    = OBJECT_CAST(QuantifiedTerm*, quantifier2.getTerm())->getBoundVars();
  
  for (boundvars1 = boundvars1->variableDereference(),
	 boundvars2 = boundvars2->variableDereference();
       boundvars1->isCons() && boundvars2->isCons() ;
       boundvars1 
	 = OBJECT_CAST(Cons*, boundvars1)->getTail()->variableDereference(),
       boundvars2 
	 = OBJECT_CAST(Cons*, boundvars2)->getTail()->variableDereference())
    {
      Object* head1 
	= OBJECT_CAST(Cons*, boundvars1)->getHead()->variableDereference();
      Object* head2 
	= OBJECT_CAST(Cons*, boundvars2)->getHead()->variableDereference();

      if (head1->isObjectVariable() && head2->isObjectVariable())
	{
	  //
	  // Both, head1 and head2 are object variables.
	  //
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
	  //
	  // head1 is  x : t1,  head2 is  y : t2
	  //
	  
	  //
	  // Push object variables x and y 
	  //
	  pushDownStack.push(OBJECT_CAST(Structure*, head1)->getArgument(1)->variableDereference());
	  pushDownStack.push(OBJECT_CAST(Structure*, head2)->getArgument(1)->variableDereference());
	  
	  //
	  // Unify term parts
	  //
          DEBUG_ASSERT(quantifier1.getSubstitutionBlockList()->isLegalSub());
          DEBUG_ASSERT(quantifier2.getSubstitutionBlockList()->isLegalSub());
	  PrologValue q1(quantifier1.getSubstitutionBlockList(),
			 OBJECT_CAST(Structure*, head1)->getArgument(2));
	  PrologValue q2(quantifier2.getSubstitutionBlockList(),
			 OBJECT_CAST(Structure*, head2)->getArgument(2));
	  heap.prologValueDereference(q1);
	  heap.prologValueDereference(q2);
	  if (!unifyPrologValues(q1, q2, in_quant))
	    {
	      return(MISMATCH);
	    }
	}
      else
	{
	  return(MISMATCH);
	}
    }
  if (boundvars1->isNil() && boundvars2->isNil())
    {
      return(MATCH);
    }
  else if (boundvars1->isVariable() && boundvars2->isVariable())
    {
      delayedVar = boundvars1;
      return(DELAY);
    }
  else if (boundvars1->isVariable())
    {
      //
      // If one bound variable list -  'boundVars1' is open, 
      // in the other words, it is ended with a variable, and 
      // the another - 'boundVars2' is not at the same point,
      // then the open one should be extended.
      //
      return(extendBoundVarListLoop(quantifier1.getSubstitutionBlockList(), 
				    boundvars1, 
				    quantifier2.getSubstitutionBlockList(), 
				    boundvars2,
				    delayedVar, false, in_quant));
    }
  else if (boundvars2->isVariable())
    {
      //
      // Similar to the case before. Because the order of
      // pushing object variables onto the object variable 
      // pair stack is important, and the same function  
      // 'extendBoundVarListLoop' is called the boolean 
      // argument 'swap' is set to true.
      // 
      return(extendBoundVarListLoop(quantifier2.getSubstitutionBlockList(), 
				    boundvars2, 
				    quantifier1.getSubstitutionBlockList(), 
				    boundvars1,
				    delayedVar, true, in_quant));
    }
  else
    {
      return(MISMATCH);
    }
}

//
// Create two parallel substitutions where all ranges are new local
// object variables, and domains are bound object variables from the  
// push down stack. Bound object variables have been stored 
// in the push down stack before, from the bound variable lists of quantified 
// terms. Add the corresponding parallel substitution to the right 
// of term (quantifier) substitution.  
//
void
Thread::makeQuantSubs(Object*& sub1, Object*& sub2, 
		      Object* qsub1, Object* qsub2, int old_size) 
{
  DEBUG_ASSERT(qsub1->isNil() || (qsub1->isCons() &&
	       OBJECT_CAST(Cons*, qsub1)->isSubstitutionBlockList()));
  DEBUG_ASSERT(qsub2->isNil() || (qsub2->isCons() &&
	       OBJECT_CAST(Cons*, qsub2)->isSubstitutionBlockList()));

  bool both_empty = (qsub1->isNil() && qsub2->isNil());
  // 
  // The size of a substitution is the size of 'ob_var_stack'
  // stack divided by 2, because this stack contains object
  // variables for both substitutions.
  // 

  size_t n;

  if (both_empty)
    {
      // Find the length of the sub not counting matching vars
      n = 0;
      for (size_t i = old_size; i < pushDownStack.size(); i += 2)
	{
	  if (pushDownStack.getEntry(i)->variableDereference() !=
	      pushDownStack.getEntry(i+1)->variableDereference())
	    {
	      n++;
	    }
	}
      if (n == 0)
	{
          pushDownStack.popNEntries(pushDownStack.size() - old_size);
	  sub1 = qsub1;
	  sub2 = qsub2;
	  return;
	}
    }
  else
    {
      n = (pushDownStack.size() - old_size)/ 2;
    }

  SubstitutionBlock* block1 = heap.newSubstitutionBlock(n);
  SubstitutionBlock* block2 = heap.newSubstitutionBlock(n);

  block1->makeInvertible();
  block2->makeInvertible();
  //
  // Fill domains and ranges.
  //
  for (size_t i = 1; i <= n; )
    {
      Object* o1 = pushDownStack.pop()->variableDereference();
      Object* o2 = pushDownStack.pop()->variableDereference();
      if (both_empty && (o1 == o2))
	{
	  continue;
	}
      ObjectVariable* local = heap.newObjectVariable(); 
      local->makeLocalObjectVariable();
      block2->setDomain(i, OBJECT_CAST(ObjectVariable*, o1));
      block1->setDomain(i, OBJECT_CAST(ObjectVariable*, o2));
      block1->setRange(i, local);
      block2->setRange(i, local);
      i++;
    }
  sub1 = heap.newSubstitutionBlockList(block1, qsub1); 
  sub2 = heap.newSubstitutionBlockList(block2, qsub2);
}

//
// Bind variable to a skeletal structure
//
void
Thread::bindToSkelStruct(Object* variable, Object* structure)
{
  DEBUG_ASSERT(variable->isVariable());
  DEBUG_ASSERT(structure->isStructure());

  u_int arity = OBJECT_CAST(Structure*, structure)->getArity();

  Structure* newStruct = heap.newStructure(arity);

  Variable* funct = heap.newVariable();
  funct->setOccursCheck();

  newStruct->setFunctor(funct);

  for (u_int i = 1; i <= arity; i++)
    {
      //
      // Assign the i-th argument of 
      // the new created structure to 
      // a new variable.
      //
      Variable* arg = heap.newVariable();
      arg->setOccursCheck();
      newStruct->setArgument(i, arg);
    }
  bind(OBJECT_CAST(Variable*, variable), newStruct);
}

//
// Bind variable to a skeletal list
//
void
Thread::bindToSkelList(Object* variable)
{
  DEBUG_ASSERT(variable->isVariable());
  Variable* head = heap.newVariable();
  Variable* tail = heap.newVariable();
  head->setOccursCheck();
  tail->setOccursCheck();
  Cons* newList = heap.newCons(head, tail);

  //
  // Bind variable to the created list.
  //
  bind(OBJECT_CAST(Variable*, variable), newList);
}

//
// Bind variable to a skeletal quantified term
//
void
Thread::bindToSkelQuant(Object* variable)
{
  DEBUG_ASSERT(variable->isVariable());

  //
  // Create a new quantified term and 
  // assign its quantifier, bound 
  // variable and bound term to new  
  // variables.
  //
  QuantifiedTerm* newQuant = heap.newQuantifiedTerm();
  Variable* q = heap.newVariable();
  Variable* bv = heap.newVariable();
  Variable* b = heap.newVariable();
  q->setOccursCheck();
  bv->setOccursCheck();
  b->setOccursCheck();
  newQuant->setQuantifier(q);
  newQuant->setBoundVars(bv);
  newQuant->setBody(b);

  bind(OBJECT_CAST(Variable*, variable), newQuant);

  //
  // Impose the constraint for bound variables.
  //
  Structure* problem = heap.newStructure(1);
  problem->setFunctor(AtomTable::checkBinder);
  problem->setArgument(1,bv);

  delayProblem(problem, bv);
}

//
// Unify two quantified terms.
//
bool
Thread::unifyQuantifiers(PrologValue& quant1, PrologValue& quant2, 
			 bool in_quant)
{
  DEBUG_ASSERT(quant1.getTerm()->isQuantifiedTerm());
  DEBUG_ASSERT(quant2.getTerm()->isQuantifiedTerm()); 

  Object*	delayedVar;

  //
  // Initialise push down stack.
  //
  // pushDownStack.clear();
  int old_size = pushDownStack.size();
  
  //
  // Both, term and quantifier, are quantified terms.
  // term       = s1 * q1 BoundVarList1 body1
  // quantifier = s2 * q2 BoundVarList2 body2
  //
  
  //
  // Pair up bound variable lists.
  //
  switch (pairUpBoundVarList(quant1, quant2, delayedVar, in_quant))
    {
    case MISMATCH:
      pushDownStack.popNEntries(pushDownStack.size() - old_size);
      return(false);
      break;
      
    case DELAY:
      pushDownStack.popNEntries(pushDownStack.size() - old_size);
      if (!in_quant || balanceLocals(quant1, quant2))
	{
	  //
	  // Unify quantifiers
	  //
	  PrologValue q1(quant1.getSubstitutionBlockList(),
			 OBJECT_CAST(QuantifiedTerm*,quant1.getTerm())->getQuantifier());
	  PrologValue q2(quant2.getSubstitutionBlockList(),
			 OBJECT_CAST(QuantifiedTerm*,quant2.getTerm())->getQuantifier());
	  heap.prologValueDereference(q1);
	  heap.prologValueDereference(q2);

	  if (!unifyPrologValues(q1, q2, in_quant))
	    {
	      return(false);
	    }
	  
	  delayUnify(quant1, quant2, delayedVar);
	}
      else
	{
	  return(false);
	}
      break;
      
    case MATCH:
      //
      // Unify quantifiers
      //
      PrologValue q1(quant1.getSubstitutionBlockList(),
		     OBJECT_CAST(QuantifiedTerm*,quant1.getTerm())->getQuantifier());
      PrologValue q2(quant2.getSubstitutionBlockList(),
		     OBJECT_CAST(QuantifiedTerm*,quant2.getTerm())->getQuantifier());
      heap.prologValueDereference(q1);
      heap.prologValueDereference(q2);

      if (!unifyPrologValues(q1, q2, in_quant))
	{
          pushDownStack.popNEntries(pushDownStack.size() - old_size);
	  return(false);
	}
      //
      // Create substitutions: 
      //	sub1 = s1 * [v1/x1, ..., vn/xn] 
      //	sub2 = s2 * [v1/y1, ..., vn/yn]. 
      // where:
      //	v1, ..., vn are 
      //	new local object variables,
      //	x1, ..., xn are object variables 
      //	from the list BoundVarList1
      //	y1, ..., yn are object variables 
      //	from the list BoundVarList2
      //
      Object *s1, *s2;
      makeQuantSubs(s1, s2, quant1.getSubstitutionBlockList(), 
		    quant2.getSubstitutionBlockList(), old_size);

      //
      // Unify bodies
      // 
      PrologValue b1(s1, OBJECT_CAST(QuantifiedTerm*,quant1.getTerm())->getBody());
      PrologValue b2(s2, OBJECT_CAST(QuantifiedTerm*,quant2.getTerm())->getBody());
      heap.prologValueDereference(b1);
      heap.prologValueDereference(b2);
      if (!unifyPrologValues(b1, b2, true))
	{
	  return(false);
	}
    }
  return(true);
}	


//
// Unify two frozen object variables.
//
bool
Thread::unifyFrozenFrozenObjectVariables(PrologValue& frozenObjectVariable1, 
				      PrologValue& frozenObjectVariable2)
{
  if (frozenObjectVariable1.getSubstitutionBlockList()->isNil() &&
      frozenObjectVariable2.getSubstitutionBlockList()->isNil())
    {
      return(false);
    }
  else
    {
      if (balanceLocals(frozenObjectVariable1, frozenObjectVariable2))
	{
	  delayUnify(frozenObjectVariable1, frozenObjectVariable2,
		     frozenObjectVariable1.getTerm());
	}
      else
	{
	  return(false);
	}
    }
return(true);
}

//
// Unify object variable and non-object variable term.
//
bool
Thread::unifyObjectVariableTerm(PrologValue& objectVariable, PrologValue& term)
{
  if (objectVariable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, objectVariable);
    }
  switch(term.getTerm()->utag())
    {
    case Object::uCons:	 
      if (heap.yieldList(term.getTerm(), 
		    objectVariable.getSubstitutionBlockList(), status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;
      
    case Object::uStruct:	 
      if (heap.yieldStructure(term.getTerm(), 
			 objectVariable.getSubstitutionBlockList(), 
			 status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;
      
    case Object::uConst:	 
      if (heap.yieldConstant(term.getTerm(), 
			objectVariable.getSubstitutionBlockList(), 
			status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;
      
    case Object::uQuant:	 
      if (heap.yieldQuantifier(term.getTerm(), 
			  objectVariable.getSubstitutionBlockList(), 
			  status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;

    default:
      DEBUG_ASSERT(false);
    }
  return(true); 
}

//
// Unify object variable with another object variable.
// 'ObjectVariable1' has no substitution.
//
bool
Thread::unifyObjectVariableObjectVariable(Object* objectVariable1, 
					  PrologValue& objectVariable2)
{
  DEBUG_ASSERT(objectVariable1->isObjectVariable());
  DEBUG_ASSERT(objectVariable1 == objectVariable1->variableDereference());

  if (heap.yieldObjectVariable(OBJECT_CAST(ObjectVariable*, objectVariable1), 
			  objectVariable2.getSubstitutionBlockList(), 
			  status))
    {	
      PrologValue objectVariable(objectVariable1);
      if (balanceLocals(objectVariable, objectVariable2))
	{
	  delayUnify(objectVariable, objectVariable2, 
		     objectVariable2.getTerm());
	}
      else
	{
	  return(false);
	}
    }
  else if (objectVariable1->distinctFrom(objectVariable2.getTerm()))
    {
      return(false);
    }
  else
    {
      bindObjectVariables(OBJECT_CAST(ObjectVariable*, objectVariable1), 
			  OBJECT_CAST(ObjectVariable*, 
				      objectVariable2.getTerm()));
      objectVariable1 = objectVariable1->variableDereference();
      return(generateDistinction(OBJECT_CAST(ObjectVariable*, objectVariable1),
				 objectVariable2.getSubstitutionBlockList()));
    }
  return(true);
}

//
// Unify two object variables.
//
bool
Thread::unifyObjectVariables(PrologValue& objectVariable1, 
			     PrologValue& objectVariable2)
{
  DEBUG_ASSERT(objectVariable1.getTerm()->isObjectVariable());
  DEBUG_ASSERT(objectVariable2.getTerm()->isObjectVariable());

  if (objectVariable1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, objectVariable1);
    }
  if (objectVariable2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, objectVariable2);
    }
  if (objectVariable1.getTerm() == objectVariable2.getTerm())
    {
      if(objectVariable1.getSubstitutionBlockList() == 
         objectVariable2.getSubstitutionBlockList())
        {
          return true;
        }

      if (objectVariable1.getSubstitutionBlockList()->isNil() &&
	  ! heap.yieldObjectVariable(objectVariable1.getTerm(),
				objectVariable2.getSubstitutionBlockList(),
				status))
	{
	  return(generateDistinction(OBJECT_CAST(ObjectVariable*, objectVariable1.getTerm()),  objectVariable2.getSubstitutionBlockList()));
	}
      else if (objectVariable2.getSubstitutionBlockList()->isNil() &&
	       !heap.yieldObjectVariable(objectVariable2.getTerm(),
				    objectVariable1.getSubstitutionBlockList(),
				    status))
	{
	  return(generateDistinction(OBJECT_CAST(ObjectVariable*,objectVariable2.getTerm()), objectVariable1.getSubstitutionBlockList()));
	}
      else if (! balanceLocals(objectVariable1, objectVariable2))
	{
	  return(false);
	}
      else if (heap.fastEqual(objectVariable1, objectVariable2) != true)
	{
	  delayUnify(objectVariable1, objectVariable2,
		     objectVariable1.getTerm());
	}
    }
  else if (!status.testHeatWave() && 
	   OBJECT_CAST(Reference*, objectVariable1.getTerm())->isFrozen() && 
	   OBJECT_CAST(Reference*, objectVariable2.getTerm())->isFrozen())
    {
      return(unifyFrozenFrozenObjectVariables(objectVariable1,
					      objectVariable2));
    }
  else if (objectVariable1.getSubstitutionBlockList()->isNil() &&
	   objectVariable2.getSubstitutionBlockList()->isNil())
    {
      if (objectVariable1.getTerm()->distinctFrom(objectVariable2.getTerm()))
	{
	  return(false);
	}
      else
	{
	  bindObjectVariables(OBJECT_CAST(ObjectVariable*, objectVariable1.getTerm()), OBJECT_CAST(ObjectVariable*, objectVariable2.getTerm()));
	}
    } 
  else if (objectVariable1.getTerm()->isLocalObjectVariable())
    {
      Object *domElem, *newEnd;
      DEBUG_ASSERT(objectVariable1.getSubstitutionBlockList()->isNil());
      if (! objectVariable1.getTerm()->containLocalObjectVariable(objectVariable2.getSubstitutionBlockList(), domElem, newEnd))
	{
	  return(false);
	}
      else
	{
	  //
	  // Because the last occurrence of the local object 
	  // variable ObjectVariable1.term in the substitution 
	  // ObjectVariable2.sub is as a range element, 
	  // ObjectVariable1.term is replaced with the corresponding 
	  // domain and the ObjectVariable2.sub with the new 
	  // substitution copied from the right up to the one 
	  // where the local object variable is found. 
	  //
	  // ObjectVariable1.term = vk
	  // ObjectVariable2.sub  = s1 * ... * 
	  //	[v1/x1, ... , vk/xk, ... vm/xm] * sj * ... * sn
	  // is transformed to:
	  // ObjectVariable1.term = xk
	  // ObjectVariable2.sub  = sj * ... * sn
	  //
	  objectVariable1.setTerm(domElem);
	  objectVariable2.setSubstitutionBlockList(heap.splitSubstitution(objectVariable2.getSubstitutionBlockList(), newEnd));
	  heap.prologValueDereference(objectVariable1);
	  return(unifyObjectVariables(objectVariable1, objectVariable2));
	}
    }
  else if (objectVariable2.getTerm()->isLocalObjectVariable())
    {
      Object *domElem, *newEnd;
      DEBUG_ASSERT(objectVariable2.getSubstitutionBlockList()->isNil());
      if (! objectVariable2.getTerm()->containLocalObjectVariable(objectVariable1.getSubstitutionBlockList(), domElem, newEnd))
	{
	  return(false);
	}
      else
	{
	  //
	  // Because the last occurrence of the local object 
	  // variable ObjectVariable2.term in the substitution 
	  // ObjectVariable1.sub is as a range element, 
	  // ObjectVariable2.term is replaced with the corresponding 
	  // domain and the ObjectVariable1.sub with the new 
	  // substitution copied from the right up to the one 
	  // where the local object variable is found. 
	  //
	  // ObjectVariable2.term = vk
	  // ObjectVariable1.sub  = s1 * ... * 
	  //	[v1/x1, ... , vk/xk, ... vm/xm] * sj * ... * sn
	  // is transformed to:
	  // ObjectVariable2.term = xk
	  // ObjectVariable1.sub  = sj * ... * sn
	  //
	  objectVariable2.setTerm(domElem);
	  objectVariable1.setSubstitutionBlockList(heap.splitSubstitution(objectVariable1.getSubstitutionBlockList(), newEnd));
	  heap.prologValueDereference(objectVariable2);
	  return(unifyObjectVariables(objectVariable2, objectVariable1));
	}
    }
  else if (objectVariable1.getSubstitutionBlockList()->isNil())
    {
      return(unifyObjectVariableObjectVariable(objectVariable1.getTerm(), 
					       objectVariable2));
    }
  else if (objectVariable2.getSubstitutionBlockList()->isNil())
    {
      return(unifyObjectVariableObjectVariable(objectVariable2.getTerm(), 
					       objectVariable1));
    }
  else if (objectVariable1.getSubstitutionBlockList()->isNil() ||
	   OBJECT_CAST(Cons*, objectVariable1.getSubstitutionBlockList())->isInvertible())
    {
      if (heap.invert(*this, objectVariable1.getSubstitutionBlockList(),
		      objectVariable2))
	{
	  heap.prologValueDereference(objectVariable2);
	  return(unifyObjectVariableObjectVariable(objectVariable1.getTerm(), 
						   objectVariable2));
	}
      else
	{
	  return(false);
	}
    }
  else if (objectVariable2.getSubstitutionBlockList()->isNil() || OBJECT_CAST(Cons*, objectVariable2.getSubstitutionBlockList())->isInvertible())
    {
      if (heap.invert(*this, objectVariable2.getSubstitutionBlockList(), 
		 objectVariable1))
	{
	  heap.prologValueDereference(objectVariable1);
	  return(unifyObjectVariableObjectVariable(objectVariable2.getTerm(), 
						   objectVariable1));
	}
      else
	{
	  return(false);
	}
    }
  else if (balanceLocals(objectVariable1, objectVariable2))
    {
      delayUnify(objectVariable1, objectVariable2, 
		 objectVariable1.getTerm());
    }
  else
    {
      return(false);
    }
  return(true);
}

//
// Unify variables.               
// 
// NOTE: variable1.term must contain the younger variable.
//	 variable1 and variable2 are different.
//
bool
Thread::unifyVariableVariable1(PrologValue& variable1, PrologValue& variable2,
			       bool in_quant)
{
  DEBUG_ASSERT(variable1.getTerm()->isVariable());
  DEBUG_ASSERT(variable2.getTerm()->isVariable());
  DEBUG_ASSERT(variable1.getTerm() != variable2.getTerm());
  DEBUG_ASSERT(reinterpret_cast<void*>(variable1.getTerm()) 
	       >
	       reinterpret_cast<void*>(variable2.getTerm()));
  if (variable1.getSubstitutionBlockList()->isNil() ||
      OBJECT_CAST(Cons*, variable1.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable1.getSubstitutionBlockList(), variable2))
	{
	  return false;
	}
      variable1.setSubstitutionBlockList(AtomTable::nil);
      if (in_quant && !balanceLocals(variable1, variable2))
	{
	  return false;
	}

      Object* simpterm;
      Object* var = variable1.getTerm()->variableDereference();
      if (occursCheckPV(ALL_CHECK, var, variable2, simpterm) == false)
	{
	  if (OBJECT_CAST(Variable*, var)->isOccursChecked())
	    {
	      OBJECT_CAST(Variable*, variable2.getTerm())->setOccursCheck();
	    }
	  bind(OBJECT_CAST(Variable*, var), simpterm);
	  return true;
	}
      else
	{
	  delayUnify(variable1, variable2, var);
	  return true;
	}
    }
  else if (variable2.getSubstitutionBlockList()->isNil() ||
      OBJECT_CAST(Cons*, variable2.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable2.getSubstitutionBlockList(), variable1))
	{
	  return false;
	}
      variable2.setSubstitutionBlockList(AtomTable::nil);
      if (in_quant && !balanceLocals(variable2, variable1))
	{
	  return false;
	}

      Object* simpterm;
      Object* var = variable2.getTerm()->variableDereference();
      if (occursCheckPV(ALL_CHECK, var, variable1, simpterm) == false)
	{
	  if (OBJECT_CAST(Variable*, var)->isOccursChecked())
	    {
	      OBJECT_CAST(Variable*, variable1.getTerm())->setOccursCheck();
	    }
	  bind(OBJECT_CAST(Variable*, var), simpterm);
	  return true;
	}
      else
	{
	  delayUnify(variable2, variable1, var);
	  return true;
	}
    }
  else if (!in_quant || balanceLocals(variable1, variable2))
    {
      delayUnify(variable1, variable2, 
		 variable1.getTerm());
      return true;
    }
  else
    {
      return(false);
    }
  DEBUG_ASSERT(false);
  return true;
}

//
// Unify frozen variable with a variable.               
// Frozen variable behaves like a constant.
// 
bool
Thread::unifyFrozenVariable(PrologValue& frozenVariable, PrologValue& variable,
			    bool in_quant)
{
  DEBUG_ASSERT(frozenVariable.getTerm()->isFrozenVariable());

  if (variable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable);
    }
  if (frozenVariable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, frozenVariable);
    }

  if (!status.testHeatWave() && variable.getTerm()->isFrozenVariable())
    {
      if (frozenVariable.getTerm() != variable.getTerm())
	{
	  return(false);
	}
      else
	{
	  if (in_quant && ! balanceLocals(frozenVariable, variable))
	    {
	      return(false);
	    }
	  stripUnmatchedSubs(frozenVariable, variable);
	  if (heap.fastEqual(frozenVariable, variable) != true)
	    {
	      delayUnify(frozenVariable, variable, 
			 frozenVariable.getTerm());
	    }
	  return(true);
	}
    }
  else if (frozenVariable.getSubstitutionBlockList()->isNil() &&
	   variable.getSubstitutionBlockList()->isNil())
    {
      bindVariables(OBJECT_CAST(Variable*, frozenVariable.getTerm()), 
		    OBJECT_CAST(Variable*, variable.getTerm()));
      return true;
    }
  else if (variable.getSubstitutionBlockList()->isNil() ||
	   OBJECT_CAST(Cons*, variable.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable.getSubstitutionBlockList(), 
		      frozenVariable))
	{
	  return false;
	}
      variable.setSubstitutionBlockList(AtomTable::nil);
      if (in_quant && !balanceLocals(variable, frozenVariable))
	{
	  return false;
	}

      Object* simpterm;
      if (occursCheckPV(ALL_CHECK, variable.getTerm(), 
			frozenVariable, simpterm) == false)
	{
	  if (OBJECT_CAST(Variable*, variable.getTerm())->isOccursChecked())
	    {
	      OBJECT_CAST(Variable*, frozenVariable.getTerm())->setOccursCheck();
	    }
	  bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), simpterm);
	  return true;
	}
    }
  if (!in_quant || balanceLocals(variable, frozenVariable))
    {
      delayUnify(variable, frozenVariable, 
		 variable.getTerm());
      return true;
    }
  else
    {
      return(false);
    }
}

//
// Unify two thawed variables.               
// 
bool
Thread::unifyVariableVariable(PrologValue& variable1, PrologValue& variable2,
			      bool in_quant)
{
  if (variable1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable1);
    }
  if (variable2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable2);
    }
  if (variable1.getTerm() == variable2.getTerm()) 
    {
      if (in_quant && ! balanceLocals(variable1, variable2))
	{
	  return(false);
	}
      stripUnmatchedSubs(variable1, variable2);
      if (heap.fastEqual(variable1, variable2) != true)
	{
	  delayUnify(variable1, variable2, variable1.getTerm());
	}
    }
  else if (variable1.getSubstitutionBlockList()->isNil() &&
	   variable2.getSubstitutionBlockList()->isNil())
    {
      bindVariables(OBJECT_CAST(Variable*, variable1.getTerm()), 
		    OBJECT_CAST(Variable*, variable2.getTerm()));
    }
  else if (reinterpret_cast<void*>(variable1.getTerm())
	   < 
	   reinterpret_cast<void*>(variable2.getTerm()))
    {
      return(unifyVariableVariable1(variable2, variable1, in_quant));
    }
  else
    {
      return(unifyVariableVariable1(variable1, variable2, in_quant));
    }
  
  return(true);
}

//
// Unify variable and non-variable term.
//
bool
Thread::unifyVariableTerm(PrologValue& variable, PrologValue& term,
			  bool in_quant)
{
  truth3		flag;
  
  if (!status.testHeatWave() && 
      OBJECT_CAST(Variable*, variable.getTerm())->isFrozen())
    {
      if (term.getTerm()->isObjectVariable())
        {
	  if (term.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, term);
	    }
          DEBUG_ASSERT(term.getTerm()->isObjectVariable());
          if (heap.yieldVariable(variable.getTerm(), 
				 term.getSubstitutionBlockList(),
				 status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
	        {
		  delayUnify(variable, term, variable.getTerm());
                  return(true);
	        }
	      else
	        {
	          return(false);
	        }
            }
          else
            {
              return (false);
            }
        }
      else
        {
          return(false);
        }
    }
  //
  // If we are inside a quant unify and the term is a local object variable
  // then the only possible solution is for the variable to be an object 
  // variable and so we bind the variable to a new object variable and
  // attempt the unification again.
  //
  if (in_quant && term.getTerm()->isLocalObjectVariable())
    {
      Object* newobj = heap.newObjectVariable();
      bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), newobj);
      heap.prologValueDereference(variable);
      return unifyPrologValues(variable, term, in_quant);
    }

  if (variable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable);
    }
  if (variable.getSubstitutionBlockList()->isNil() ||
      OBJECT_CAST(Cons*, variable.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable.getSubstitutionBlockList(), term))
	{ 
	  return false;
	}
      heap.prologValueDereference(term);
      variable.setSubstitutionBlockList(AtomTable::nil);

      Object* simpterm;
      flag = occursCheckPV(ALL_CHECK, variable.getTerm(), term, simpterm);
      if (flag == true)
	{
	  return(false);
	}
      else if (flag == truth3::UNSURE)
	{
	  if (!in_quant || balanceLocals(variable, term))
	    {
	      delayUnify(variable, term, 
			 variable.getTerm());
	      return(true);
	    }
	  else
	    {
	      return false;
	    }
	}
      else
	{
	  if (in_quant && !balanceLocals(variable, term))
	    {
	      return false;
	    }
	  bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), simpterm);
	  return(true);
	}
    }
  else
    {
      Object* dummy;
      switch(term.getTerm()->utag())
	{
	case Object::uCons:	 
	  if (heap.yieldList(term.getTerm(), 
			     variable.getSubstitutionBlockList(),
			     status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else if (occursCheckPV(DIRECT, variable.getTerm(), term, dummy) 
		   == true)
	    {
	      return(false);
	    }
	  else
	    {
	      bindToSkelList(variable.getTerm());
	      heap.prologValueDereference(variable);
	      return(unifyPrologValues(variable, term, in_quant));
	    }
	  break;
	  
	case Object::uStruct:	 
	  if (heap.yieldStructure(term.getTerm(), 
				  variable.getSubstitutionBlockList(),
				  status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else if (occursCheckPV(DIRECT, variable.getTerm(), term, dummy) 
		   == true)
	    {
	      return(false);
	    }
	  else
	    {
	      bindToSkelStruct(variable.getTerm(), term.getTerm());
	      heap.prologValueDereference(variable);
	      return(unifyPrologValues(variable, term, in_quant));
	    }
	  break;
	  
	case Object::uConst:	 
	  if (heap.yieldConstant(term.getTerm(), 
				 variable.getSubstitutionBlockList(),
				 status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else
	    {
	      bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), 
		   term.getTerm());
	    }
	  break;
	  
	case Object::uObjVar:	 
	  if (term.getTerm()->isLocalObjectVariable())
	    {
	      Object *domElem, *newEnd;
	      if (! term.getTerm()->containLocalObjectVariable(variable.getSubstitutionBlockList(), domElem, newEnd)) 
		{
		  return(false);
		}
	      else
		{
		  //
		  // Because the last occurrence of the 
		  // local object variable term.term
		  // in the substitution variable.sub
		  // is as a range element, term.term
		  // is replaced with the corresponding 
		  // domain and the variable.sub with the 
		  // new substitution copied from the 
		  // right up to the one where the local 
		  // object variable is found. 
		  //
		  // term.term = vk
		  // variable.sub  = s1 * ... * 
		  //	[v1/x1, ... , vk/xk, ... vm/xm]
		  //		* sj * ... * sn
		  // is transformed to:
		  // term.term = xk
		  // variable.sub  = sj * ... * sn
		  //
		  term.setTerm(domElem);
		  variable.setSubstitutionBlockList(
                   heap.splitSubstitution(variable.getSubstitutionBlockList(),
					 newEnd));
		  heap.prologValueDereference(term);
		  heap.prologValueDereference(variable);
		  return(unifyPrologValues(variable, term, in_quant));
		}
	    }
	  else if (term.getSubstitutionBlockList()->isNil())
	    {
	      DEBUG_ASSERT(variable.getTerm() == variable.getTerm()->variableDereference());
	      bind(OBJECT_CAST(Variable*, variable.getTerm()),
		   heap.newObjectVariable());
	      heap.prologValueDereference(variable);
	      return(unifyObjectVariableObjectVariable(term.getTerm(), 
						       variable));
	    }
	  else if (!in_quant || balanceLocals(variable, term))
	    {
	      delayUnify(variable, term, variable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	  break;
	  
	case Object::uQuant:	 
	  if (heap.yieldQuantifier(term.getTerm(), 
				   variable.getSubstitutionBlockList(),
				   status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else if (occursCheckPV(DIRECT, variable.getTerm(), term, dummy) 
		   == true)
	    {
	      return(false);
	    }
	  else
	    {
	      bindToSkelQuant(variable.getTerm());
	      heap.prologValueDereference(variable);
	      return(unifyQuantifiers(variable, term, in_quant));
	    }
	  break;
	  
	default:
	  DEBUG_ASSERT(false);
	}
    }
  
  return(true); 
}

//
// Unify two variables.
//
bool
Thread::unifyVarVar(PrologValue& variable1, PrologValue& variable2, 
		    bool in_quant)
{
  DEBUG_ASSERT(variable1.getTerm()->isVariable());
  DEBUG_ASSERT(variable2.getTerm()->isVariable());

  if (!status.testHeatWave() && 
      OBJECT_CAST(Variable*, variable1.getTerm())->isFrozen())
    {
      return(unifyFrozenVariable(variable1, variable2, in_quant));
    }
  else if (!status.testHeatWave() && 
      OBJECT_CAST(Variable*, variable2.getTerm())->isFrozen())
    {
      return(unifyFrozenVariable(variable2, variable1, in_quant));
    }
  else
    {
      return(unifyVariableVariable(variable1, variable2, in_quant));
    }
}

//
// Unification of two Prolog Values.
// Assumes PrologValue dereference has been done to both terms.
//
bool
Thread::unifyPrologValues(PrologValue& term1, PrologValue& term2, 
			  bool in_quant = false)
{
  if (term1.getTerm() == term2.getTerm() &&
      term1.getSubstitutionBlockList() == term2.getSubstitutionBlockList())
    {
      return(true);
    }

  DEBUG_ASSERT(term1.getTerm()->utag() < 8);
  DEBUG_ASSERT(term2.getTerm()->utag() < 8);
  switch (CrossTag(term1.getTerm()->utag(), term2.getTerm()->utag()))
    {
      //
      // term1 is a variable
      //
    case CrossTag(Object::uVar, Object::uVar):
      return(unifyVarVar(term1, term2, in_quant));
      break;

    case CrossTag(Object::uVar, Object::uObjVar):
    case CrossTag(Object::uVar, Object::uCons):
    case CrossTag(Object::uVar, Object::uStruct):
    case CrossTag(Object::uVar, Object::uQuant):
    case CrossTag(Object::uVar, Object::uConst):
      return(unifyVariableTerm(term1, term2, in_quant));
      break;

      //
      // term1 is an object variable
      //      
    case CrossTag(Object::uObjVar, Object::uVar):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;

    case CrossTag(Object::uObjVar, Object::uObjVar):
      return(unifyObjectVariables(term1, term2));
      break;

    case CrossTag(Object::uObjVar, Object::uCons):
    case CrossTag(Object::uObjVar, Object::uStruct):
    case CrossTag(Object::uObjVar, Object::uQuant):
    case CrossTag(Object::uObjVar, Object::uConst):
      return(unifyObjectVariableTerm(term1, term2));
      break;

      //
      // term1 is a list
      //

    case CrossTag(Object::uCons, Object::uVar):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;

    case CrossTag(Object::uCons, Object::uObjVar):
      return(unifyObjectVariableTerm(term2, term1));
      break;

    case CrossTag(Object::uCons, Object::uCons):
      {
	Cons* list1 = OBJECT_CAST(Cons*, term1.getTerm());
	Cons* list2 = OBJECT_CAST(Cons*, term2.getTerm());
	PrologValue head1(term1.getSubstitutionBlockList(), list1->getHead());
	PrologValue head2(term2.getSubstitutionBlockList(), list2->getHead());
	heap.prologValueDereference(head1);
	heap.prologValueDereference(head2);
	if (!unifyPrologValues(head1, head2, in_quant))
	  {
	    return(false);
	  }
	PrologValue tail1(term1.getSubstitutionBlockList(), list1->getTail());
	PrologValue tail2(term2.getSubstitutionBlockList(), list2->getTail());
	heap.prologValueDereference(tail1);
	heap.prologValueDereference(tail2);
	return (unifyPrologValues(tail1, tail2, in_quant));
	break;
      }

    case CrossTag(Object::uCons, Object::uStruct):
    case CrossTag(Object::uCons, Object::uQuant):
    case CrossTag(Object::uCons, Object::uConst):
      return(false);
      break;

      //
      // term1 is a structure
      //

    case CrossTag(Object::uStruct, Object::uVar):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;

    case CrossTag(Object::uStruct, Object::uObjVar):
      return(unifyObjectVariableTerm(term2, term1));
      break;

    case CrossTag(Object::uStruct, Object::uCons):
      return(false);
      break;

    case CrossTag(Object::uStruct, Object::uStruct):
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1.getTerm());
	Structure* struct2 = OBJECT_CAST(Structure*, term2.getTerm());
	u_int arity = struct1->getArity();
	if (arity != struct2->getArity())
	  {
	    return(false);
	  }
	PrologValue funct1(term1.getSubstitutionBlockList(), 
			   struct1->getFunctor());
	PrologValue funct2(term2.getSubstitutionBlockList(), 
			   struct2->getFunctor());
	heap.prologValueDereference(funct1);
	heap.prologValueDereference(funct2);
	if (!unifyPrologValues(funct1, funct2, in_quant))
	  {
	    return(false);
	  }
      
	for (u_int i = 1; i <= arity; i++)
	  {
	    PrologValue arg1(term1.getSubstitutionBlockList(), 
			     struct1->getArgument(i));
	    PrologValue arg2(term2.getSubstitutionBlockList(), 
			     struct2->getArgument(i));

	    heap.prologValueDereference(arg1);
	    heap.prologValueDereference(arg2);
	    if (!unifyPrologValues(arg1, arg2, in_quant))
	      {
		return(false);
	      }
	  }
	break;
      }

    case CrossTag(Object::uStruct, Object::uQuant):
    case CrossTag(Object::uStruct, Object::uConst):
      return(false);
      break;

      //
      // term1 is a quantified term
      //
    case CrossTag(Object::uQuant, Object::uVar):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;

    case CrossTag(Object::uQuant, Object::uObjVar):
      return(unifyObjectVariableTerm(term2, term1));
      break;

    case CrossTag(Object::uQuant, Object::uCons):
    case CrossTag(Object::uQuant, Object::uStruct):
      return(false);
      break;

    case CrossTag(Object::uQuant, Object::uQuant):
      return(unifyQuantifiers(term1, term2, in_quant));
      break;

    case CrossTag(Object::uQuant, Object::uConst):
      return(false);
      break;
  
      //
      // term1 is a constant
      //
    case CrossTag(Object::uConst, Object::uVar):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;

    case CrossTag(Object::uConst, Object::uObjVar):
      return(unifyObjectVariableTerm(term2, term1));
      break;

    case CrossTag(Object::uConst, Object::uCons):
    case CrossTag(Object::uConst, Object::uStruct):
    case CrossTag(Object::uConst, Object::uQuant):
      return (false);
      break;

    case CrossTag(Object::uConst, Object::uConst):
      return (term1.getTerm()->equalConstants(term2.getTerm()));
      break;

    default:
      DEBUG_ASSERT(false);
      return(false);
    }
  return(true);
}


//
// General unify algorithm. 
//
bool
Thread::unify(Object* term1, Object* term2, bool in_quant = false)
{
  //
  // Do the full dereference.
  //
DEBUG_ASSERT(term1->variableDereference()->hasLegalSub());
DEBUG_ASSERT(term2->variableDereference()->hasLegalSub());
  term1 = heap.dereference(term1);
  term2 = heap.dereference(term2);
  if (term1 == term2)
    {
      return(true);
    }
  //
  // At this point the terms are different.
  //
  DEBUG_ASSERT(term1->utag() < 8);
  DEBUG_ASSERT(term2->utag() < 8);
  switch (CrossTag(term1->utag(), term2->utag()))
    {
      //
      // term1 is a variable
      //
    case CrossTag(Object::uVar, Object::uVar):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1);
	Variable* var2 = OBJECT_CAST(Variable*, term2);
	if (var1->isFrozen() && var2->isFrozen() 
	    && !status.testHeatWave())
	  {
	    return(false);
	  }
	bindVariables(var1, var2);
	return(true);
	break;
      }
	
      case CrossTag(Object::uVar, Object::uObjVar):
	{	
	  Variable* var1 = OBJECT_CAST(Variable*, term1);
	  if (var1->isFrozen() && !status.testHeatWave())
	    {
	      return(false);
	    }
	  bind(var1, term2);
	  return(true);
	  break;
	}

    case CrossTag(Object::uVar, Object::uCons):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1);
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var1, term2, simpterm);
	if (flag == false)
	  {
	    bind(var1, simpterm);
	  }
	else if (flag == true)
	  {
	    return(false);
	  } 
	else
	  {
	    bindToSkelList(var1);
	    return(unify(var1, term2, in_quant));
	  }
	return(true);
	break;
      }

    case CrossTag(Object::uVar, Object::uStruct):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1);
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var1, term2, simpterm);
	if (flag == false)
	  {
	    bind(var1, simpterm);
	  }
	else if (flag == true)
	  {
	    return(false);
	  } 
	else
	  {
	    bindToSkelStruct(var1, term2);
	    return(unify(var1, term2, in_quant));
	  }
	return(true);
	break;
      }

    case CrossTag(Object::uVar, Object::uQuant):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1);
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var1, term2, simpterm);
	if (flag == false)
	  {
	    bind(var1, simpterm);
	  }
	else if (flag == true)
	  {
	    return(false);
	  } 
	else
	  {
	    bindToSkelQuant(var1);
	    return(unify(var1, term2, in_quant));
	  }
	return(true);
	break;
      }

    case CrossTag(Object::uVar, Object::uConst):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1);
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	bind(var1, term2);
	return(true);
	break;
      }

    case CrossTag(Object::uVar, Object::uSubst):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	Variable* var1 = OBJECT_CAST(Variable*, term1);
	Object* simpterm;
	if( (var1->isThawed() || status.testHeatWave())
	    && occursCheck(ALL_CHECK, var1, term2, simpterm) == false)
	  {
	    bind(var1, simpterm);
	    return true;
	  }
	else
	  {
	    PrologValue pterm1(term1);
	    PrologValue pterm2(term2);
	    heap.prologValueDereference(pterm1);
	    heap.prologValueDereference(pterm2);
	    return(unifyPrologValues(pterm1, pterm2));
	  }
	break;
      }

      //
      // term1 is an object variable
      //      
    case CrossTag(Object::uObjVar, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2);
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	bind(var2, term1);
	return(true);
	break;
      }

    case CrossTag(Object::uObjVar, Object::uObjVar):
      {
	ObjectVariable* obvar1 = OBJECT_CAST(ObjectVariable*, term1);
	ObjectVariable* obvar2 = OBJECT_CAST(ObjectVariable*, term2);
	if ((obvar1->isFrozen() && obvar2->isFrozen() 
	    && !status.testHeatWave()) 
	    ||
	    obvar1->distinctFrom(obvar2))
	  {
	    return(false);
	  }
	bindObjectVariables(obvar1,obvar2);
	return(true);
	break;
      }

    case CrossTag(Object::uObjVar, Object::uCons):
    case CrossTag(Object::uObjVar, Object::uStruct):
    case CrossTag(Object::uObjVar, Object::uQuant):
    case CrossTag(Object::uObjVar, Object::uConst):
      return(false);
      break;

    case CrossTag(Object::uObjVar, Object::uSubst):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	PrologValue pterm1(term1);
	PrologValue pterm2(term2);
	heap.prologValueDereference(pterm1);
	heap.prologValueDereference(pterm2);
	return(unifyPrologValues(pterm1, pterm2));
	break;
      } 
      
      //
      // term1 is a list
      //

    case CrossTag(Object::uCons, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2);
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	Object* simpterm;
       	truth3 flag = occursCheck(ALL_CHECK, var2, term1, simpterm);
	if (flag == false)
	  {
	    bind(var2, simpterm);
	  }
	else if (flag == true)
	  {
	    return(false);
	  } 
	else
	  {
	    bindToSkelList(var2);
	    return(unify(var2, term1, in_quant));
	  }
	return(true);
	break;
      }

    case CrossTag(Object::uCons, Object::uObjVar):
      return(false);
      break;

    case CrossTag(Object::uCons, Object::uCons):
      {
	Cons* list1 = OBJECT_CAST(Cons*, term1);
	Cons* list2 = OBJECT_CAST(Cons*, term2);
	return (unify(list1->getHead(), list2->getHead(), in_quant) &&
		unify(list1->getTail(), list2->getTail(), in_quant));
	break;
      }

    case CrossTag(Object::uCons, Object::uStruct):
    case CrossTag(Object::uCons, Object::uQuant):
    case CrossTag(Object::uCons, Object::uConst):
      return(false);
      break;

    case CrossTag(Object::uCons, Object::uSubst):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	PrologValue pterm1(term1);
	PrologValue pterm2(term2);
	heap.prologValueDereference(pterm1);
	heap.prologValueDereference(pterm2);
	return(unifyPrologValues(pterm1, pterm2));
	break;
      }


      //
      // term1 is a structure
      //

    case CrossTag(Object::uStruct, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2);
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var2, term1, simpterm);
	if (flag == false)
	  {
	    bind(var2, simpterm);
	  }
	else if (flag == true)
	  {
	    return(false);
	  } 
	else
	  {
	    bindToSkelStruct(var2, term1);
	    return(unify(var2, term1, in_quant));
	  }
	return(true);
	break;
      }
	
    case CrossTag(Object::uStruct, Object::uObjVar):
    case CrossTag(Object::uStruct, Object::uCons):
      return(false);
      break;

    case CrossTag(Object::uStruct, Object::uStruct):
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1);
	Structure* struct2 = OBJECT_CAST(Structure*, term2);
	
	u_int arity = struct1->getArity();
	if (arity != struct2->getArity())
	  {
	    return(false);
	  }
	if (!unify(struct1->getFunctor(), struct2->getFunctor(), in_quant))
	  {
	    return(false);
	  }
	for (u_int i = 1; i <= arity; i++)
	  {
	    if (!unify(struct1->getArgument(i), 
		       struct2->getArgument(i), in_quant))
	      {
		return(false);
	      }
	  }
	return(true);
	break;
      }

    case CrossTag(Object::uStruct, Object::uQuant):
    case CrossTag(Object::uStruct, Object::uConst):
      return(false);
      break;

    case CrossTag(Object::uStruct, Object::uSubst):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	PrologValue pterm1(term1);
	PrologValue pterm2(term2);
	heap.prologValueDereference(pterm1);
	heap.prologValueDereference(pterm2);
	return(unifyPrologValues(pterm1, pterm2));
	break;
      }

      //
      // term1 is a quantified term
      //
    case CrossTag(Object::uQuant, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2);
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var2, term1, simpterm);
	if (flag == false)
	  {
	    bind(var2, simpterm);
	  }
	else if (flag == true)
	  {
	    return(false);
	  } 
	else
	  {
	    bindToSkelQuant(var2);
	    return(unify(var2, term1, in_quant));
	  }
	return(true);
	break;
      }

    case CrossTag(Object::uQuant, Object::uObjVar):
    case CrossTag(Object::uQuant, Object::uCons):
    case CrossTag(Object::uQuant, Object::uStruct):
      return(false);
      break;
  
    case CrossTag(Object::uQuant, Object::uQuant):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	PrologValue pterm1(term1);
	PrologValue pterm2(term2);
	return(unifyQuantifiers(pterm1, pterm2, false));
	break;
      }
      
    case CrossTag(Object::uQuant, Object::uConst):
      return(false);
      break;

    case CrossTag(Object::uQuant, Object::uSubst):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	PrologValue pterm1(term1);
	PrologValue pterm2(term2);
	heap.prologValueDereference(pterm1);
	heap.prologValueDereference(pterm2);
	return(unifyPrologValues(pterm1, pterm2));
	break;
      }

      //
      // term1 is a constant.
      //

    case CrossTag(Object::uConst, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2);
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	bind(var2, term1);
	return(true);
	break;
      }

    case CrossTag(Object::uConst, Object::uObjVar):
    case CrossTag(Object::uConst, Object::uCons):
    case CrossTag(Object::uConst, Object::uStruct):
    case CrossTag(Object::uConst, Object::uQuant):
      return(false);
      break;

    case CrossTag(Object::uConst, Object::uConst):
      return (term1->equalConstants(term2));
      break;

    case CrossTag(Object::uConst, Object::uSubst):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	PrologValue pterm1(term1);
	PrologValue pterm2(term2);
	
	heap.prologValueDereference(pterm2);
	return(unifyPrologValues(pterm1, pterm2));
	break;
      }

      //
      // term1 is a substitution.
      //

    case CrossTag(Object::uSubst, Object::uVar):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	Variable* var2 = OBJECT_CAST(Variable*, term2);
	Object* simpterm;
	if( (var2->isThawed() || status.testHeatWave())
	    && occursCheck(ALL_CHECK, var2, term1, simpterm) == false)
	  {
	    bind(var2, simpterm);
	    return true;
	  }
	else
	  {
	    PrologValue pterm1(term1);
	    PrologValue pterm2(term2);
	    heap.prologValueDereference(pterm1);
	    heap.prologValueDereference(pterm2);
	    return(unifyPrologValues(pterm1, pterm2));
	  }
	break;
      }

    case CrossTag(Object::uSubst, Object::uObjVar):
    case CrossTag(Object::uSubst, Object::uCons):
    case CrossTag(Object::uSubst, Object::uStruct):   
    case CrossTag(Object::uSubst, Object::uQuant):
    case CrossTag(Object::uSubst, Object::uConst):
    case CrossTag(Object::uSubst, Object::uSubst):
      {
        DEBUG_ASSERT(term1->hasLegalSub());
        DEBUG_ASSERT(term2->hasLegalSub());
	PrologValue pterm1(term1);
	PrologValue pterm2(term2);
	heap.prologValueDereference(pterm1);
	heap.prologValueDereference(pterm2);
	return(unifyPrologValues(pterm1, pterm2));
	break;
      }

    default:
      DEBUG_CODE(cerr << "Unmatched case in unify" << endl;
                 term1->printMe_dispatch(*atoms);
		 term2->printMe_dispatch(*atoms););
      DEBUG_ASSERT(false);
      return(false);
    }
  DEBUG_ASSERT(false);
  return(false);
}

bool
Thread::structuralUnifySubs(Object* sub1, Object* sub2)
{
  for ( ;
	sub1->isCons() && sub2->isCons();
	sub1 = OBJECT_CAST(Cons *, sub1)->getTail(),
	  sub2 = OBJECT_CAST(Cons *, sub2)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons *, sub1)->getHead()->isSubstitutionBlock());
      DEBUG_ASSERT(OBJECT_CAST(Cons *, sub2)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* b1 = 
	OBJECT_CAST(SubstitutionBlock*,
		    OBJECT_CAST(Cons *, sub1)->getHead());
      SubstitutionBlock* b2 = 
	OBJECT_CAST(SubstitutionBlock*,
		    OBJECT_CAST(Cons *, sub2)->getHead());
      if (b1->getSize() != b2->getSize())
	{
	  return false;
	}
      for (size_t i = 1; i <= b1->getSize(); i++)
	{
	  PrologValue dom1(b1->getDomain(i));
	  PrologValue dom2(b2->getDomain(i));
	  PrologValue ran1(b1->getRange(i));
	  PrologValue ran2(b2->getRange(i));
	  if (!structuralUnify(dom1,dom2)
	      || !structuralUnify(ran1,ran2))
	    {
	      return false;
	    }
	}
    }
  return (sub1->isNil() && sub2->isNil());
}

//
// Structural unify. This unifies two terms as "structures" - i.e.
// Quantified terms and terms with substitutions are considered
// as ordinary structures. 
//
bool
Thread::structuralUnify(PrologValue& term1, PrologValue& term2)
{
  //
  // Do the full dereference.
  //
  heap.prologValueDereference(term1);
  heap.prologValueDereference(term2);
  if ((term1.getTerm() == term2.getTerm()) &&
      (term1.getSubstitutionBlockList() == term2.getSubstitutionBlockList()))
    {
      return(true);
    }
  //
  // At this point the terms are different.
  //
  DEBUG_ASSERT(term1.getTerm()->utag() < 8);
  DEBUG_ASSERT(term2.getTerm()->utag() < 8);
  switch (CrossTag(term1.getTerm()->utag(), term2.getTerm()->utag()))
    {
      //
      // term1 is a variable
      //
    case CrossTag(Object::uVar, Object::uVar):
      {
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	
	Object* sub1 = term1.getSubstitutionBlockList();
	Object* sub2 = term2.getSubstitutionBlockList();
	Object* t1 = term1.getTerm();
	Object* t2 = term2.getTerm();
	
	Variable* var1 = OBJECT_CAST(Variable*, t1);
	Variable* var2 = OBJECT_CAST(Variable*, t2);
	
	// Walk through the subs
	for ( ;
	      sub1->isCons() && sub2->isCons();
	      sub1 = OBJECT_CAST(Cons *, sub1)->getTail(),
		sub2 = OBJECT_CAST(Cons *, sub2)->getTail())
	  {}
	
	// sub2 is longer than sub1
	if (sub1->isNil() && !sub2->isNil())
	  {
	    if (var1->isFrozen() 
		&& !status.testHeatWave())
	      {
		return(false);
	      }
	    Object* newsub = 
	      heap.copySubSpine(term2.getSubstitutionBlockList(),
				OBJECT_CAST(Cons *, sub2)->getTail(), 
                                AtomTable::nil);
            DEBUG_ASSERT(newsub->isCons());
	    Object* newterm = heap.newSubstitution(newsub,t2);
	    
	    Object* simpterm;
	    truth3 flag = occursCheck(ALL_CHECK, var1, newterm, simpterm);
	    if (flag == false)
	      {
		bind(var1, simpterm);
	      }
	    else
	      {
		return(false);
	      } 
	    heap.prologValueDereference(term1);
	  }
	// sub1 is longer than sub2
	else if (sub2->isNil() && !sub1->isNil())
	  {
	    if (var2->isFrozen() 
		&& !status.testHeatWave())
	      {
		return(false);
	      }
	    Object* newsub = 
	      heap.copySubSpine(term1.getSubstitutionBlockList(),
				OBJECT_CAST(Cons *, sub1)->getTail(), 
                                AtomTable::nil);
            DEBUG_ASSERT(newsub->isCons());
	    Object* newterm = heap.newSubstitution(newsub,t1);
	    
	    Object* simpterm;
	    truth3 flag = occursCheck(ALL_CHECK, var2, newterm, simpterm);
	    if (flag == false)
	      {
		bind(var2, simpterm);
	      }
	    else
	      {
		return(false);
	      } 
	    heap.prologValueDereference(term2);
	  }
	else
	  {
	    DEBUG_ASSERT(sub1->isNil() && sub2->isNil());
	    if (term1.getTerm() != term2.getTerm())
	      {
		if (var1->isFrozen() && var2->isFrozen() 
		    && !status.testHeatWave())
		  {
		    return(false);
		  }
		bindVariables(var1, var2);
		heap.prologValueDereference(term1);
		heap.prologValueDereference(term2);
	      }
	  }
	
	DEBUG_ASSERT(term1.getTerm() == term2.getTerm());
	sub1 = term1.getSubstitutionBlockList();
	sub2 = term2.getSubstitutionBlockList();
	
	return structuralUnifySubs(sub1, sub2);
	
	break;
      }
      
    case CrossTag(Object::uVar, Object::uObjVar):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1.getTerm());
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	
	Object* sub1 = term1.getSubstitutionBlockList();
	Object* sub2 = term2.getSubstitutionBlockList();
	Object* t2 = term2.getTerm();
	
	// Walk through the subs
	for ( ;
	      sub1->isCons() && sub2->isCons();
	      sub1 = OBJECT_CAST(Cons *, sub1)->getTail(),
		sub2 = OBJECT_CAST(Cons *, sub2)->getTail())
	  {}
	
	// sub2 is longer than sub1
	if (sub1->isNil() && !sub2->isNil())
	  {
	    Object* newsub = 
	      heap.copySubSpine(term2.getSubstitutionBlockList(),
				OBJECT_CAST(Cons *, sub2)->getTail(), 
                                AtomTable::nil);
            DEBUG_ASSERT(newsub->isCons());
	    Object* newterm = heap.newSubstitution(newsub,t2);
	    
	    Object* simpterm;
	    truth3 flag = occursCheck(ALL_CHECK, var1, newterm, simpterm);
	    if (flag == false)
	      {
		bind(var1, simpterm);
	      }
	    else
	      {
		return(false);
	      } 
	    heap.prologValueDereference(term1);
	  }
	else if (sub1->isNil() && sub2->isNil())
	  {
	    bind(var1, t2);
	    heap.prologValueDereference(term1);
	  }
	else
	  {
	    return false;
	  }
	
	DEBUG_ASSERT(term1.getTerm() == term2.getTerm());
	sub1 = term1.getSubstitutionBlockList();
	sub2 = term2.getSubstitutionBlockList();
	
	return structuralUnifySubs(sub1, sub2);
	
	break;
      }
      
    case CrossTag(Object::uVar, Object::uCons):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1.getTerm());
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }

	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var1,  
				  heap.prologValueToObject(term2), simpterm);
	if (flag == false)
	  {
	    if (term1.getSubstitutionBlockList()->isCons())
	      {
		bindToSkelList(var1);
		return structuralUnify(term1, term2);
	      }
	    else
	      {
		bind(var1, simpterm);
		return(true);
	      }
	  }
	else 
	  {
	    return(false);
	  } 
	break;
      }
      
    case CrossTag(Object::uVar, Object::uStruct):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1.getTerm());
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }

	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var1, 
				  heap.prologValueToObject(term2), simpterm);
	if (flag == false)
	  {
	    if (term1.getSubstitutionBlockList()->isCons())
	      {
		bindToSkelStruct(var1, term2.getTerm());
		return structuralUnify(term1, term2);
	      }
	    else
	      {
		bind(var1, simpterm);
		return(true);
	      }
	  }
	else
	  {
	    return(false);
	  } 
	break;
      }

    case CrossTag(Object::uVar, Object::uQuant):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1.getTerm());
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var1, 
				  heap.prologValueToObject(term2), simpterm);
	if (flag == false)
	  {
	    if (term1.getSubstitutionBlockList()->isCons())
	      {
		bindToSkelQuant(var1);
		return structuralUnify(term1, term2);
	      }
	    else
	      {
		bind(var1, simpterm);
		return(true);
	      }
	  }
	else
	  {
	    return(false);
	  } 
	break;
      }

    case CrossTag(Object::uVar, Object::uConst):
      {
	Variable* var1 = OBJECT_CAST(Variable*, term1.getTerm());
	if (var1->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	bind(var1, term2.getTerm());
	return(true);
	break;
      }

      //
      // term1 is an object variable
      //      
    case CrossTag(Object::uObjVar, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2.getTerm());
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	
	Object* sub1 = term1.getSubstitutionBlockList();
	Object* sub2 = term2.getSubstitutionBlockList();
	Object* t1 = term1.getTerm();
	
	// Walk through the subs
	for ( ;
	      sub1->isCons() && sub2->isCons();
	      sub1 = OBJECT_CAST(Cons *, sub1)->getTail(),
		sub2 = OBJECT_CAST(Cons *, sub2)->getTail())
	  {}
	
	// sub1 is longer than sub2
	if (sub2->isNil() && !sub1->isNil())
	  {
	    Object* newsub = 
	      heap.copySubSpine(term1.getSubstitutionBlockList(),
				OBJECT_CAST(Cons *, sub1)->getTail(), 
                                AtomTable::nil);
            DEBUG_ASSERT(newsub->isCons());
	    Object* newterm = heap.newSubstitution(newsub,t1);
	    
	    Object* simpterm;
	    truth3 flag = occursCheck(ALL_CHECK, var2, newterm, simpterm);
	    if (flag == false)
	      {
		bind(var2, simpterm);
	      }
	    else
	      {
		return(false);
	      } 
	    heap.prologValueDereference(term2);
	  }
	else if (sub1->isNil() && sub2->isNil())
	  {
	    bind(var2, t1);
	    heap.prologValueDereference(term2);
	  }
	else
	  {
	    return false;
	  }
	
	DEBUG_ASSERT(term1.getTerm() == term2.getTerm());
	sub1 = term1.getSubstitutionBlockList();
	sub2 = term2.getSubstitutionBlockList();
	
	return structuralUnifySubs(sub1, sub2);
	
	break;
      }

    case CrossTag(Object::uObjVar, Object::uObjVar):
      {
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	
	Object* sub1 = term1.getSubstitutionBlockList();
	Object* sub2 = term2.getSubstitutionBlockList();
	Object* t1 = term1.getTerm();
	Object* t2 = term2.getTerm();

	ObjectVariable* obvar1 = OBJECT_CAST(ObjectVariable*, t1);
	ObjectVariable* obvar2 = OBJECT_CAST(ObjectVariable*, t2);
	if (obvar1 != obvar2)
	  {
	    if ((obvar1->isFrozen() && obvar2->isFrozen() 
		 && !status.testHeatWave()) 
		||
		obvar1->distinctFrom(obvar2))
	      {
		return(false);
	      }
	    bindObjectVariables(obvar1,obvar2);
	  }
	return structuralUnifySubs(sub1, sub2);

	break;
      }

    case CrossTag(Object::uObjVar, Object::uCons):
    case CrossTag(Object::uObjVar, Object::uStruct):
    case CrossTag(Object::uObjVar, Object::uQuant):
    case CrossTag(Object::uObjVar, Object::uConst):
      return(false);
      break;

      //
      // term1 is a list
      //

    case CrossTag(Object::uCons, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2.getTerm());
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }

	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var2, 
				  heap.prologValueToObject(term1), simpterm);
	if (flag == false)
	  {
	    if (term2.getSubstitutionBlockList()->isCons())
	      {
		bindToSkelList(var2);
		return structuralUnify(term1, term2);
	      }
	    else
	      {
		bind(var2, simpterm);
		return(true);
	      }
	  }
	else 
	  {
	    return(false);
	  } 
	break;
      }

    case CrossTag(Object::uCons, Object::uObjVar):
      return(false);
      break;

    case CrossTag(Object::uCons, Object::uCons):
      {
	Cons* list1 = OBJECT_CAST(Cons*, term1.getTerm());
	Cons* list2 = OBJECT_CAST(Cons*, term2.getTerm());
	PrologValue head1(term1.getSubstitutionBlockList(), list1->getHead());
	PrologValue head2(term2.getSubstitutionBlockList(), list2->getHead());
	PrologValue tail1(term1.getSubstitutionBlockList(),list1->getTail() );
	PrologValue tail2(term2.getSubstitutionBlockList(), list2->getTail());
	
	return (structuralUnify(head1, head2) &&
		structuralUnify(tail1, tail2));
	break;
      }
      
    case CrossTag(Object::uCons, Object::uStruct):
    case CrossTag(Object::uCons, Object::uQuant):
    case CrossTag(Object::uCons, Object::uConst):
      return(false);
      break;

      //
      // term1 is a structure
      //

    case CrossTag(Object::uStruct, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2.getTerm());
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }

	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var2, 
				  heap.prologValueToObject(term1), simpterm);
	if (flag == false)
	  {
	    if (term2.getSubstitutionBlockList()->isCons())
	      {
		bindToSkelStruct(var2, term1.getTerm());
		return structuralUnify(term1, term2);
	      }
	    else
	      {
		bind(var2, simpterm);
		return(true);
	      }
	  }
	else
	  {
	    return(false);
	  } 
	break;
      }
	
    case CrossTag(Object::uStruct, Object::uObjVar):
    case CrossTag(Object::uStruct, Object::uCons):
      return(false);
      break;

    case CrossTag(Object::uStruct, Object::uStruct):
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1.getTerm());
	Structure* struct2 = OBJECT_CAST(Structure*, term2.getTerm());
	
	u_int arity = struct1->getArity();
	if (arity != struct2->getArity())
	  {
	    return(false);
	  }

	for (u_int i = 0; i <= arity; i++)
	  {
	    PrologValue arg1(term1.getSubstitutionBlockList(), 
			     struct1->getArgument(i));
	    PrologValue arg2(term2.getSubstitutionBlockList(), 
			     struct2->getArgument(i));

	    if (!structuralUnify(arg1, arg2))
	      {
		return(false);
	      }
	  }
	return(true);
	break;
      }

    case CrossTag(Object::uStruct, Object::uQuant):
    case CrossTag(Object::uStruct, Object::uConst):
      return(false);
      break;

      //
      // term1 is a quantified term
      //
    case CrossTag(Object::uQuant, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2.getTerm());
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }

	Object* simpterm;
	truth3 flag = occursCheck(ALL_CHECK, var2, 
				  heap.prologValueToObject(term1), simpterm);
	if (flag == false)
	  {
	    if (term2.getSubstitutionBlockList()->isCons())
	      {
		bindToSkelQuant(var2);
		return structuralUnify(term1, term2);
	      }
	    else
	      {
		bind(var2, simpterm);
		return(true);
	      }
	  }
	else
	  {
	    return(false);
	  } 
	break;
      }

    case CrossTag(Object::uQuant, Object::uObjVar):
    case CrossTag(Object::uQuant, Object::uCons):
    case CrossTag(Object::uQuant, Object::uStruct):
      return(false);
      break;
  
    case CrossTag(Object::uQuant, Object::uQuant):
      {
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	if (!structuralUnifySubs(term1.getSubstitutionBlockList(),
				 term2.getSubstitutionBlockList()))
	  {
	    return false;
	  }

	QuantifiedTerm* q1 = OBJECT_CAST(QuantifiedTerm*, term1.getTerm());
	QuantifiedTerm* q2 = OBJECT_CAST(QuantifiedTerm*, term2.getTerm());
	PrologValue qu1(q1->getQuantifier());
	PrologValue qu2(q2->getQuantifier());
	PrologValue bv1(q1->getBoundVars());
	PrologValue bv2(q2->getBoundVars());
	PrologValue body1(q1->getBody());
	PrologValue body2(q2->getBody());
	return (structuralUnify(qu1, qu2)
		&& structuralUnify(bv1, bv2)
		&& structuralUnify(body1, body2));
	break;
      }
      
    case CrossTag(Object::uQuant, Object::uConst):
      return(false);
      break;

      //
      // term1 is a constant.
      //

    case CrossTag(Object::uConst, Object::uVar):
      {
	Variable* var2 = OBJECT_CAST(Variable*, term2.getTerm());
	if (var2->isFrozen() && !status.testHeatWave())
	  {
	    return(false);
	  }
	bind(var2, term1.getTerm());
	return(true);
	break;
      }

    case CrossTag(Object::uConst, Object::uObjVar):
    case CrossTag(Object::uConst, Object::uCons):
    case CrossTag(Object::uConst, Object::uStruct):
    case CrossTag(Object::uConst, Object::uQuant):
      return(false);
      break;

    case CrossTag(Object::uConst, Object::uConst):
      return (term1.getTerm()->equalConstants(term2.getTerm()));
      break;

    default:
      DEBUG_CODE(cerr << "Unmatched case in structuralUnify" << endl;
                 heap.prologValueToObject(term1)->printMe_dispatch(*atoms);
		 heap.prologValueToObject(term2)->printMe_dispatch(*atoms););
      DEBUG_ASSERT(false);
      return(false);
    }
  DEBUG_ASSERT(false);
  return(false);
}











