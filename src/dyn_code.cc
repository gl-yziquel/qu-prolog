// dyn_code.cc - Dynamic code area management.
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
// $Id: dyn_code.cc,v 1.13 2006/01/31 23:17:50 qp Exp $

#include "config.h"
#include "global.h"
#include "code.h"
#include "thread_qp.h"
#include "dynamic_code.h"

extern Code *code;
extern PredTab *predicates;

//#include "dynamic_hash_table.cc"

CodeLoc getFirstUnretractedClause(CodeLoc code)
{
  CodeLoc current = code;
  while(current != NULL)
    {
      CodeLoc clloc = current + Code::SIZE_OF_INSTRUCTION 
	+ Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
      CodeLoc cl = getCodeLoc(clloc);
      if (getInstruction(cl) != FAIL)
	{
	  return current;
	}
      CodeLoc next = current + OFFSET_TO_LAST_ADDRESS;
      current = getCodeLoc(next);
    }
  return current;
}

//
// psi_code_top(variable)
// Return the top of the code area.
// mode(out)
//
Thread::ReturnValue
Thread::psi_code_top(Object*& object1)
{
  object1 = heap.newNumber(reinterpret_cast<word32>(code->getTop()));
  
  return(RV_SUCCESS);
}


//
// psi_get_opcode(opcode, buffer, offset)
// Get an opcode from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_opcode(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;

  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
  
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());
  
  object1 = heap.newNumber(getInstruction(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_const(constant, buffer, offset)
// Get a constant from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_const(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
  
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());
  
  object1 = getConstant(offset);
  
  return(RV_SUCCESS);
}

//
// psi_get_integer(constant, buffer, offset)
// Get an integer from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_integer(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());

  object1 = heap.newNumber(getInteger(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_double(constant, buffer, offset)
// Get a double from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_double(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());

  object1 = heap.newDouble(getDouble(offset));
  
  return(RV_SUCCESS);
}


//
// psi_get_number(number, buffer, offset)
// Get a number from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_number(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());
   
  object1 = heap.newNumber(getNumber(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_address(address, buffer, offset)
// Get an address from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_address(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());

  object1 = heap.newNumber(getAddress(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_offset(offset, buffer, offset)
// Get an offset from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_offset(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());

  object1 = heap.newNumber(getOffset(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_pred(predicate atom, buffer, offset)
// Get a predicate atom from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_pred(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getNumber() + val3->getNumber());

  object1 = getPredAtom(offset);
  
  return(RV_SUCCESS);
}

//
// psi_get_entry(offset, linkblock, predtype)
// Get the code for this block.
// mode(out,in, out)
//
Thread::ReturnValue
Thread::psi_get_entry(Object*& object1, Object*& object2, Object*& object3)
{
  Object* val2 = object2->variableDereference();
  assert(val2->isNumber());
  assert(val2->getNumber() != 0);
  CodeLoc code = reinterpret_cast<CodeLoc>((val2->getNumber()) +
    Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS); 
  
  object1 = heap.newNumber(reinterpret_cast<word32>(getCodeLoc(code)));
  object3 = heap.newNumber(0);
  return(RV_SUCCESS);
}

//
// psi_reset_entry(predicate, arity)
// Abolish the predicate definition. 
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_reset_entry(Object*& object1, Object*& object2)
{
  Object* val1 = object1->variableDereference();
  Object* val2 = object2->variableDereference();  
  
  assert(val1->isAtom());
  assert(val2->isNumber());
  
  predicates->resetEp(OBJECT_CAST(Atom*, val1), val2->getNumber(), atoms, code);
  
  return(RV_SUCCESS);
}

//
// psi_assert(Head, Assembled, FirstLast, Ref).
// mode(in,in,in,out).
//
Thread::ReturnValue
Thread::psi_assert(Object*& object1, Object*& object2, 
		   Object*& object3, Object*& object4)
{
  code->Stamp();
  Object *pred, *indexarg;
  int arity;
  PredLoc loc;
  
  Object* val1 = object1->variableDereference();
  Object* val3 = object3->variableDereference();
  
  if (val1->isAtom())
    {
      arity = 0;
      pred = val1;
      indexarg = val1;
      loc = predicates->lookUp(OBJECT_CAST(Atom*, val1), 0, atoms, code);
      if (loc == EMPTY_LOC)
	{
	  DynamicPredicate* dp = new DynamicPredicate(0);
	  loc = 
	    predicates->addDynamicPredicate(atoms, 
					    OBJECT_CAST(Atom*, val1),
					    0, dp, code);
	}
    }
  else 
    {
      assert(val1->isStructure());
      Structure* str = OBJECT_CAST(Structure*, val1);
      arity = static_cast<int>(str->getArity());
      pred = heap.dereference(str->getFunctor());
      assert(pred->isAtom());
      loc = predicates->lookUp(OBJECT_CAST(Atom*, pred), arity, atoms, code);
      if (loc == EMPTY_LOC)
	{
	  DynamicPredicate* dp = new DynamicPredicate(arity);
	  loc = predicates->addDynamicPredicate(atoms, 
						OBJECT_CAST(Atom*, pred), 
						arity, dp, code);
	}
    }
  assert(val3->isNumber());
  bool asserta = (val3->getNumber() == 0);
  DynamicPredicate* dp =  predicates->getCode(loc).getDynamicPred();
  dp->Stamp();
  if (arity != 0)
    {
         indexarg = 
	   OBJECT_CAST(Structure*, val1)->getArgument(1 + dp->getIndexedArg());
    }
#ifdef DYNAMIC_CODE_DEBUG
  cerr << "--------- BEFORE assertClause -----------" << endl << endl;
  dp->display_clauses();
#endif // DYNAMIC_CODE_DEBUG
  dp->assertClause(*this, indexarg, object2, asserta); 
#ifdef DYNAMIC_CODE_DEBUG
  dp->display_clauses();
#endif // DYNAMIC_CODE_DEBUG
  object4 = heap.newNumber(0);
  return(RV_SUCCESS);
}

//
// psi_retract(Ref).
// retract clause with reference Ref.
// mode(in).
//
Thread::ReturnValue
Thread::psi_retract(Object*& object1)
{
  code->Stamp();
  Object* val1 = object1->variableDereference();
  assert(val1->isNumber());
  CodeLoc code = reinterpret_cast<CodeLoc>((val1->getNumber()) 
    + Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER);
  DynamicPredicate* pred = 
    reinterpret_cast<DynamicPredicate*>(getAddress(code));
  pred->makeDirty();
  pred->Stamp();
  CodeLoc first = getCodeLoc(code);
  updateInstruction(first, FAIL);
  
  return(RV_SUCCESS);
}

// Get the timestamp for a predicate
// mode psi_predicate_stamp(in,in,out)
//
Thread::ReturnValue
Thread::psi_predicate_stamp(Object*& object1, Object*& object2,
                            Object*& object3)
{
  Object* pred = object1->variableDereference();
  Object* arityObject = object2->variableDereference();
  
  int arity = arityObject->getNumber();
  
  PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, pred), arity,
				   atoms, code);
  if (loc == EMPTY_LOC)
    {
      return(RV_FAIL);
    }
  else if ((predicates->getCode(loc)).type() == PredCode::DYNAMIC_PRED)
    {
      DynamicPredicate* dp =  predicates->getCode(loc).getDynamicPred();
      object3 = heap.newNumber(dp->GetStamp());
      return(RV_SUCCESS);
    }
  else
    {
      return(RV_FAIL);
    }

}

//
// psi_dynamic(pred, arity, indexArg, hashtablesize)
// Declare pred/arity as a dynamic predicate with indexArg (default = 1)
// and hashtablesize (default = 4)
// mode(in,in,in,in).
Thread::ReturnValue
Thread::psi_dynamic(Object*& object1, Object*& object2, 
		    Object*& object3, Object*& object4)
{
  Object* pred = object1->variableDereference();
  Object* arityObject = object2->variableDereference();
  Object* indexArgObject = object3->variableDereference();
  Object* tableSizeObject = object4->variableDereference();
  
  if (pred->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (!pred->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  //
  // pred is an atom
  //
  if (arityObject->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  else if (!arityObject->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  //
  // arity is a number
  //
  int arity = arityObject->getNumber();
  
  if (indexArgObject->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  else if (!indexArgObject->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }
  
  int indexArg = indexArgObject->getNumber();
  
  if ((arity > 0) && ((indexArg < 1) || (indexArg > arity)))
    {
      PSI_ERROR_RETURN(EV_RANGE, 3);
    }
  //
  // indexArg is a number in range
  //
  
  if (tableSizeObject->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 4);
    }
  else if (!tableSizeObject->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 4);
    }
  int tableSize = tableSizeObject->getNumber();
  if (tableSize < 1)
    { 
      PSI_ERROR_RETURN(EV_RANGE, 4);
    }
  //
  // tableSize is a positive int
  //
  
  PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, pred), arity,
				   atoms, code);
  if (loc == EMPTY_LOC)
    {
      DynamicPredicate* dp 
	= new DynamicPredicate(arity, indexArg-1, tableSize);
      loc = predicates->addDynamicPredicate(atoms, OBJECT_CAST(Atom*, pred), 
					    arity, dp, code);
      return(RV_SUCCESS);
    }
  else if ((predicates->getCode(loc)).type() == PredCode::DYNAMIC_PRED)
    {
      return(RV_SUCCESS);
    }
  else
    {
      return(RV_FAIL);
    }
}


//
// psi_get_dynamic_chain(predicate, chain)
// Get the entry point to a predicate.
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_get_dynamic_chain(Object*& object1, Object*& object2)
{
#if 0
  int   arity;
  Object* predObject;
  
  Object* val1 = object1->variableDereference();

  if (val1->isAtom())
    {
      predObject = val1;
      arity = 0;
    }
  else
    {
      assert(val1->isStructure());
      Structure* str = OBJECT_CAST(Structure*, val1);
      arity = str->getArity();
      predObject = str->getFunctor();
    }
  
  const PredLoc loc = 
    predicates->lookUp(OBJECT_CAST(Atom*, predObject), arity, atoms, code);
  if (loc == EMPTY_LOC)
    {
      return(RV_FAIL);
    }
  const PredCode pred = predicates->getCode(loc);
  
  if (pred.type() != PredCode::DYNAMIC_PRED)
    {
      return (RV_FAIL);
    }

  Object* argObject;
  
  const word8 arg = pred.getDynamicPred()->getIndexedArg();
  assert(arity == 0 || arg < arity);
  if (arity == 0)
    {
      argObject = AtomTable::nil; 
    }
  else
    {
      argObject = OBJECT_CAST(Structure*, val1)->getArgument(arg+1);
    }
  ChainEnds* chain 
    = pred.getDynamicPred()->lookUpClauseChain(*this, argObject);
  if (chain->first() == NULL)
    {
      return RV_FAIL;
    }
  CodeLinkingBlock* start = chain->first()->getNext()->nextUnretractedBlock();
  if (start == NULL)
    {
      return RV_FAIL;
    }
  start->aquire();
  RefObject r(start, NULL);
  refTrail.trail(r);
  object2 = heap.newNumber(reinterpret_cast<word32>(start));
#endif
  return RV_SUCCESS;
}

//
// psi_get_first_clause(pred, ref, more)
// Get the first linkblock ptr for the predicate
// more is true if there are subsequent clauses
//
Thread::ReturnValue
Thread::psi_get_first_clause(Object*& object1, Object*& object2,
			     Object*& object3)
{
  int   arity;
  Object* predObject;
  
  Object* val1 = object1->variableDereference();

  if (val1->isAtom())
    {
      predObject = val1;
      arity = 0;
    }
  else
    {
      assert(val1->isStructure());
      Structure* str = OBJECT_CAST(Structure*, val1);
      arity = static_cast<int>(str->getArity());
      predObject = str->getFunctor();
    }
  
  const PredLoc loc = 
    predicates->lookUp(OBJECT_CAST(Atom*, predObject), arity, atoms, code);
  if (loc == EMPTY_LOC)
    {
      return(RV_FAIL);
    }
  const PredCode pred = predicates->getCode(loc);
  
  if (pred.type() != PredCode::DYNAMIC_PRED)
    {
      return (RV_FAIL);
    }

  Object* argObject;
  
  const word8 arg = pred.getDynamicPred()->getIndexedArg();
  assert(arity == 0 || arg < arity);
  if (arity == 0)
    {
      argObject = AtomTable::nil; 
    }
  else
    {
      argObject = OBJECT_CAST(Structure*, val1)->getArgument(arg+1);
    }
  ChainEnds* chain 
    = pred.getDynamicPred()->lookUpClauseChain(*this, argObject);

  CodeLoc code = getFirstUnretractedClause(chain->first());
  if (code == NULL)
    {
      return RV_FAIL;
    }

  object2 = heap.newNumber(reinterpret_cast<word32>(code));
  CodeLoc cl = code + Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER;
  DynamicPredicate* thispred = reinterpret_cast<DynamicPredicate*>(getAddress(cl));
  RefObject r(REF_PRED, thispred);
  refTrail.trail(r);
  thispred->aquire();
  CodeLoc nextAddr = cl + Code::SIZE_OF_ADDRESS;
  code = getFirstUnretractedClause(getCodeLoc(nextAddr));
  if (code == NULL)
    {
      object3 = AtomTable::failure;
    }
  else
    {
      object3 = AtomTable::success;
    }
  return(RV_SUCCESS);
}


//
// psi_get_next_clause(ptr, next, more)
// Get the next linkblock ptr for ptr.
// mode(in, out, out)
//
Thread::ReturnValue
Thread::psi_get_next_clause(Object*& object1, Object*& object2,
			    Object*& object3)
{
  Object* val1 = object1->variableDereference();

  assert(val1->isNumber());
  assert(val1->getNumber() != 0);

  CodeLoc code = reinterpret_cast<CodeLoc>((val1->getNumber()) + OFFSET_TO_LAST_ADDRESS);

  CodeLoc next = getFirstUnretractedClause(getCodeLoc(code));

  if (next == NULL)
    {
      return RV_FAIL;
    }

  object2 = heap.newNumber(reinterpret_cast<word32>(next));
  code = next + OFFSET_TO_LAST_ADDRESS;
  next = getFirstUnretractedClause(getCodeLoc(code));
  if (next == NULL)
    {
      object3 = AtomTable::failure;
    }
  else
    {
      object3 = AtomTable::success;
    }
  return(RV_SUCCESS);
}










