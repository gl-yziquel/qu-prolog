// env.cc - Contains a set of functions which can be used for
//           assessing the overall tasks such as setting flags
//           call another functions and print out the statistics.
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
// $Id: env.cc,v 1.7 2002/11/03 08:37:26 qp Exp $

#include	<stdlib.h>
#include	<sstream>
#include	<signal.h>
#include	<stdarg.h>

#include "global.h"
#include "atom_table.h"
#include "objects.h"
#include "pred_table.h"
#include "signals.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern Object** lib_path;
extern PredTab *predicates;
extern Signals *signals;

Thread::ReturnValue
Thread::call_predicate(int32 noargs, ...)
{
  word32 arity;		// arity of the predicate.
  PredLoc PredCodeLoc;	// Location of predicate code.
  PredCode PredAddr;
  Object *callTerm, *functor;
  char *pred;

  va_list args;
  va_start(args, noargs);

  if (noargs == 0)
    {
      callTerm = va_arg(args, Object*);
    }
  else
    {
      callTerm = heap.newStructure(noargs);
      OBJECT_CAST(Structure*, callTerm)->setFunctor(va_arg(args, Object*));
      for (int i = 1; i <= noargs; i++)
	{
	  OBJECT_CAST(Structure*, 
		      callTerm)->setArgument(i,va_arg(args, Object*)); 
	}
    }

  callTerm = heap.dereference(callTerm);
  va_end(args);
  arity = 0;
  
  //
  // Get predicate name and arity.
  //
  if (callTerm->isAtom())
    {
      PredCodeLoc = predicates->lookUp(OBJECT_CAST(Atom*, callTerm), arity,
				       atoms, code);
    }
  else if (callTerm->isStructure())
    {
      functor = callTerm;
      do
	{
	  arity += OBJECT_CAST(Structure*, functor)->getArity();
	  functor = OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
	} while (functor->isStructure());
      
      if (! functor->isAtom())
	{
	  PredCodeLoc = predicates->lookUp(AtomTable::call_exception, 1,
					   atoms, code);
	                                        // "$call_exception"
	  arity = 0;
	}
      else
	{
	  //
	  // Get code location from predicates.
	  //
	  if (arity > NUMBER_X_REGISTERS - 1)
	    {
	      ostringstream ostrm;
	      ostrm << atoms->getAtomString(functor)
		    << "/" << arity << ends;
	      pred = (char*)(ostrm.str().data());
	      PredCodeLoc = 
		predicates->lookUp(atoms->getAtom(atoms->lookUp(pred)),
				   NUMBER_X_REGISTERS - 1, atoms, code);
	    }
	  else
	    {
	      PredCodeLoc = predicates->lookUp(OBJECT_CAST(Atom*, functor), 
					       arity, atoms, code);
	    }
	}
    }
  else if (callTerm->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  //
  // Set programCounter to interrupt code.
  //
  if (PredCodeLoc == EMPTY_LOC)
    {
      programCounter = UndefinedPred(callTerm);
      return(RV_SUCCESS);
    }
  
  //
  // Get parameters of the predicate.
  //
  functor = callTerm;
  if (arity > NUMBER_X_REGISTERS - 1)
    {
      int j = arity - NUMBER_X_REGISTERS + 2;
      Structure* shorten = heap.newStructure(j);
      shorten->setFunctor(AtomTable::qup_shorten);  // "$qup_shorten"
      
      int i = OBJECT_CAST(Structure*, functor)->getArity();
      while(j > 0)
	{
	  shorten->setArgument(j--, OBJECT_CAST(Structure*, 
						functor)->getArgument(i--));
	  
	  if (i == 0)
	    {
	      functor = OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
	      i = OBJECT_CAST(Structure*, functor)->getArity();
	    }
	}
      X[NUMBER_X_REGISTERS - 2] = shorten;
      arity = NUMBER_X_REGISTERS - 2;
      for (; i > 0; i--)
	{
	  arity--;
	  X[arity] = OBJECT_CAST(Structure*, functor)->getArgument(i);
	}
      functor = 
	OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
    }
  while (arity > 0)
    {
      for (int i = OBJECT_CAST(Structure*, functor)->getArity(); i > 0; i--)
	{
	  arity--;
	  X[arity] = OBJECT_CAST(Structure*, functor)->getArgument(i);
	}
      functor = 
	OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
    }
  //
  // Set programCounter to predicate code.
  //
  PredAddr = predicates->getCode(PredCodeLoc);
  if (PredAddr.type() == PredCode::ESCAPE_PRED)
    {
      return(PredAddr.getEscape()(*this) ? RV_SUCCESS : RV_FAIL);
    }
  else if (PredAddr.type() == PredCode::DYNAMIC_PRED)
    {
      DynamicPredicate* dp = PredAddr.getDynamicPred();
      const word8 arg = dp->getIndexedArg();
      ChainEnds* chain = dp->lookUpClauseChain(*this, X[arg]);
      CodeLoc block = chain->first();
      if (block == NULL)
        {
           return(RV_FAIL);
        }
      programCounter = block;
      return(RV_SUCCESS);
    }       
  else
    {
      programCounter = PredAddr.getPredicate(code);
      return(RV_SUCCESS);
    }
}

//
// psi_set_flag(integer, integer).
// Sets internal system flag.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_set_flag(Object *& object1, Object *& object2)
{
  Object* val1 = object1->variableDereference();
  Object* val2 = object2->variableDereference();

  DEBUG_ASSERT(val1->isShort());
  DEBUG_ASSERT(val2->isShort());
  DEBUG_ASSERT((val2->getNumber() == 1) || (val2->getNumber() == 0));

  switch (val1->getNumber())
    {
    case 0: 
      (val2->getNumber() == 1) ? status.setFastRetry() : status.resetFastRetry();
      break;
    case 1: 
      val2->getNumber() == 1 
	? status.setOccursCheck() 
	: status.resetOccursCheck();
      break;
    case 2: 
      (val2->getNumber() == 1) ? status.setHeatWave() : status.resetHeatWave();
      break;
    case 3: 
#if 0
      if (val2->getNumber() == 1)
	{
	  MachStatus.setEnableSignals();
	  for (u_int i = 1; i < NSIG + 1; i++)
	    {
	      if (signals->IsSet(i))
		{
		  MachStatus.setSignals();
		  break;
		}
	    }
	}
      else
	{
	  MachStatus.resetEnableSignals();
	}
#endif //0
      break;
    case 4: 
      val2->getNumber() == 1 
	? status.setDoingRetry() 
	: status.resetDoingRetry();
      break;
    case 5:
      if (val2->getNumber() == 1)
	{
	  if (!status.testTimeslicing())
	    {
	      status.setTimeslicing();
	      scheduler->Status().setEnableTimeslice();
	      TInfo().setForbidThread(false);
	    }
	}
      else
	{
	  if (status.testTimeslicing())
	    {
	      status.resetTimeslicing();
	      scheduler->Status().resetEnableTimeslice();
	      TInfo().setForbidThread(true);
	    }
	}
      break;
      
    default: 
      DEBUG_ASSERT(false);
    }
  return(RV_SUCCESS);
}

//
// psi_get_flag(integer, variable).
// Gets internal system flag.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_flag(Object *& object1, Object *& object2)
{
  int32	state = 0;
  Object* val1 = object1->variableDereference();

  DEBUG_ASSERT(val1->isShort());

  switch (val1->getNumber())
    {
    case 0: 
      state	= status.testFastRetry() ? 1 : 0;
      break;
    case 1: 
      state	= status.testOccursCheck() ? 1 : 0;
      break;
    case 2: 
      state	= status.testHeatWave() ? 1 : 0;
      break;
    case 3: 
      //      state	= MachStatus.testEnableSignals() ? 1 : 0;
      break;
    case 4: 
      state	= status.testDoingRetry() ? 1 : 0;
      break;
    case 5: 
      state	= status.testTimeslicing() ? 1 : 0;
      break;
    default: 
      DEBUG_ASSERT(false);
    }
  object2 = heap.newNumber(state);
  return(RV_SUCCESS);
}

//
// psi_call_predicate0(structure)
// This function executes the nonvariable term as the term
// itself in the program text.
// mode(in)
// 
Thread::ReturnValue
Thread::psi_call_predicate0(Object *& object1)
{
  return call_predicate(0, object1);
}

//
// psi_call_predicate1(structure,arg)
// This function executes the nonvariable term as the term
// itself in the program text with argument arg.
// mode(in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate1(Object *& object1, Object *& object2)
{
  return call_predicate(1, object1, object2);
}
//
// psi_call_predicate2(structure,arg1,arg2)
// This function executes the nonvariable term as the term
// itself in the program text with arguments arg1,arg2.
// mode(in,in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate2(Object *& object1, Object *& object2, Object *& object3)
{
  return call_predicate(2, object1, object2, object3);
}

//
// psi_call_predicate3(structure,arg1,arg2,arg3)
// This function executes the nonvariable term as the term
// itself in the program text with arguments arg1,arg2,arg3.
// mode(in,in,in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate3(Object *& object1,
			    Object *& object2, 
			    Object *& object3,
			    Object *& object4)
{
  return call_predicate(3, object1, object2, object3, object4);
}

//
// psi_call_predicate4(structure,arg1,arg2,arg3,arg4)
// This function executes the nonvariable term as the term
// itself in the program text with arguments arg1,arg2,arg3,arg4
// mode(in,in,in,in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate4(Object *& object1,
			    Object *& object2, 
			    Object *& object3,
			    Object *& object4,
			    Object *& object5)
{
  return call_predicate(4, object1, object2, object3, object4, object5);
}

#if 0
// 
// psi_call_clause(address, term)
// Execute a clause from address and use the term as query.  This is used for
// decompiling a dynamic clause.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_call_clause(Object *& object1, Object *& object2)
{
  Cell            query;
  word32          arity, i;
  PrologValue     pval1, pval2;
  
  pval1.term = object1;
  pval2.term = object2;
  heap.Dereference(pval1);
  heap.Dereference(pval2);
  query = pval2.term;

  DEBUG_ASSERT(pval1.getTerm()->isNumber());

  arity = ((query.isAtom()) ? (0) : (heap.StructArity(query)));
  for (i = 0; i < arity; i++)
    {
      X[i] = heap.StructNthArgument(query, i + 1);
    }

  programCounter = (CodeLoc)heap.NumValue(pval1.term);
  return(RV_SUCCESS);
}
#endif // 0

//
// psi_get_qplibpath(variable).
// This functionn returns the path for 
// files to the variable.
// mode(out)
//
Thread::ReturnValue
Thread::psi_get_qplibpath(Object *& object1)
{
  object1 = *lib_path;
  return(RV_SUCCESS);
}

//
// psi_uncurry(term1, term2).
// Flattens (uncurries) term1 to term2.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_uncurry(Object *& object1, Object *& object2)
{
        int32           i;
        word32          arity;          // arity of the term.

        PrologValue     pval1(object1);

        heap.prologValueDereference(pval1);
        arity = 0;

        //
        // Get predicate name and arity.
        //
        if (!pval1.getTerm()->isStructure())
        {
            object2 = object1;
            return(RV_SUCCESS);
        }
        //
        // pval1 is a structure
        //
	PrologValue 
	  functor(pval1.getSubstitutionBlockList(), 
		  OBJECT_CAST(Structure*, pval1.getTerm())->getFunctor());
        heap.prologValueDereference(functor);
        if (!functor.getTerm()->isStructure())
        {
            object2 = object1;
            return(RV_SUCCESS);
        }
        //
        // pval1 is higher order
        //
	PrologValue hi_func(pval1.getSubstitutionBlockList(), pval1.getTerm());

	DEBUG_ASSERT(hi_func.getTerm()->isStructure());
        do
        {
	  arity += OBJECT_CAST(Structure*, hi_func.getTerm())->getArity();
	  hi_func.setTerm(OBJECT_CAST(Structure*,
				       hi_func.getTerm())->getFunctor());
	  heap.prologValueDereference(hi_func);
        } while (hi_func.getTerm()->isStructure());

	Structure* str = heap.newStructure(arity);
	str->setFunctor(heap.prologValueToObject(hi_func));

	PrologValue term(pval1.getSubstitutionBlockList(), pval1.getTerm());
        while (arity > 0)
        {
                heap.prologValueDereference(term);
                for (i = OBJECT_CAST(Structure*, term.getTerm())->getArity() 
		       ; i > 0; i--)
                {
		  PrologValue arg(term.getSubstitutionBlockList(),
				  OBJECT_CAST(Structure*, 
					      term.getTerm())->getArgument(i));
		  str->setArgument(arity, heap.prologValueToObject(arg));
		  arity--;

                }
		term.setTerm(OBJECT_CAST(Structure*, 
					 term.getTerm())->getFunctor());
        }
	object2 = str;
        return(RV_SUCCESS);
} 






