// arithmetic.cc -  definitions for pseudo-instructions for arithmetic
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
// $Id: arithmetic.cc,v 1.3 2003/09/28 07:53:35 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// arithEvaluate is an auxilary function used by arithmetical pseudo
//instructions to carry out the evaluation of expressions.
//
int32
Thread::arithEvaluate(PrologValue& val)
{
  if (val.getTerm()->isNumber())
    {
      return (val.getTerm()->getNumber());
    }
  else if (val.getTerm()->isStructure())
    {
      long res1, res2 = 0;

      Structure *structure = OBJECT_CAST(Structure *, val.getTerm());

      size_t arity = structure->getArity();

      //
      // calcualte the values of the arguments
      //
      if (arity == 1)
	{
	  PrologValue val1(val.getSubstitutionBlockList(),
			   structure->getArgument(1));	  
	  heap.prologValueDereference(val1);
	  res1 = arithEvaluate(val1);

	  if (error_value != EV_NO_ERROR)
	    {
	      return 0;
	    }
	}
      else if (arity == 2)
	{
	  PrologValue val1(val.getSubstitutionBlockList(),
			   structure->getArgument(1));	  
	  heap.prologValueDereference(val1);
	  res1 = arithEvaluate(val1);
	  PrologValue val2(val.getSubstitutionBlockList(),
			   structure->getArgument(2));	  
	  heap.prologValueDereference(val2);
	  res2 = arithEvaluate(val2);

	  if (error_value != EV_NO_ERROR)
	    {
	      return 0;
	    }
	}
      else // illegal number of arguments
	{
	  error_value = EV_TYPE;
	  return 0;
	}
      
      //
      // evaluate the expression according to the operator
      //
      PrologValue funpv(val.getSubstitutionBlockList(),
			structure->getFunctor());	  
      heap.prologValueDereference(funpv);
      Object* fun = funpv.getTerm();
   
      DEBUG_ASSERT(fun->isAtom());

      Atom *op = OBJECT_CAST(Atom *, fun);

      if (op == AtomTable::plus)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }

	  return res1 + res2;
	}
      else if (op == AtomTable::minus)
	{
	  if (arity == 1)
	    {
	      return -res1;
	    }
	  else if (arity == 2)
	    {
	      return res1 - res2;
	    }
	  else
	    {
	      error_value = EV_TYPE;
	    }
	}
      else if (op == AtomTable::multiply)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  return res1 * res2;
	}
      else if (op == AtomTable::divide)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  if (res2 == 0)
	    {
	      error_value = EV_ZERO_DIVIDE;
	      return 0;
	    }
	  
	  return res1 / res2;
	}
      else if (op == AtomTable::intdivide)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  if (res2 == 0)
	    {
	      error_value = EV_ZERO_DIVIDE;
	      return 0;
	    }
	  
	  return res1 / res2;
	}
      else if (op == AtomTable::mod)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }	      
	  if (res2 == 0)
	    {
	      error_value = EV_ZERO_DIVIDE;
	      return 0;
	    }

	  return res1 % res2;
	}
      else if (op == AtomTable::power)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  {
	    long tmp = 1;
	    
	    while (res2-- > 0)
	      {
		tmp *= res1;
	      }
	    return tmp;
	  }
	}
      else if (op == AtomTable::bitwiseand)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }

	  return res1 & res2;
	}
      else if (op == AtomTable::bitwiseor)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  return res1 | res2;
	}
      else if (op == AtomTable::shiftl)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  return res1 << res2;
	}
      else if (op == AtomTable::shiftr)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  return res1 >> res2;
	}
      else if (op == AtomTable::bitneg)
	{
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return 0;
	    }
	  return ~res1;
	}
      else 
	{
	  error_value = EV_TYPE;
	  return 0;
	}
    }
  else if (val.getTerm()->isVariable())
    {
      error_value = EV_INST;
      return 0;
    }
  else
    {
      error_value = EV_TYPE;
      return 0;
    }

  return 0;
}

//
// psi_is(Out, Exp)
// mode(out,in)
//
Thread::ReturnValue
Thread::psi_is(Object *& object1, Object *& object2)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;
  
  PrologValue val(object2);
  heap.prologValueDereference(val);
  const long result = arithEvaluate(val);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }
  else
    {
      object1 = heap.newNumber(result);

      return RV_SUCCESS;
    }
}

//
// psi_less(A, B)
// mode(in,in)
// true iff A < B
//
Thread::ReturnValue
Thread::psi_less(Object *& object1, Object *& object2)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  const long res1 = arithEvaluate(pval1);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  const long res2 = arithEvaluate(pval2);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }
  
  //
  // The two args evaluate correctly so test them
  //
  return BOOL_TO_RV(res1 < res2);
}

//
// psi_lesseq(A, B)
// mode(in,in)
// true iff A <= B
//
Thread::ReturnValue
Thread::psi_lesseq(Object *& object1, Object *& object2)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  const long res1 = arithEvaluate(pval1);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  const long res2 = arithEvaluate(pval2);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }
  
  //
  // The two args evaluate correctly so test them
  //
  return BOOL_TO_RV(res1 <= res2);

}


//
// psi_add(A,B,Sum)
// mode(in,in,out)
// Sum = A + B
//
Thread::ReturnValue
Thread::psi_add(Object *& object1, Object *& object2, Object *& object3)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  const long res1 = arithEvaluate(pval1);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  const long res2 = arithEvaluate(pval2);
 
  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }

  //
  // The two args evaluate correctly so add them
  //
  object3 = heap.newNumber(res1+res2);

  return RV_SUCCESS;
}

//
// psi_subtract(A,B,Diff)
// mode(in,in,out)
// Diff = A - B
//
Thread::ReturnValue
Thread::psi_subtract(Object *& object1, Object *& object2, Object *& object3)
{
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  const long res1 = arithEvaluate(pval1);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  const long res2 = arithEvaluate(pval2);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }

  //
  // The two args evaluate correctly so subtract them
  //
  object3 = heap.newNumber(res1 - res2);

  return RV_SUCCESS;
}


//
// psi_increment(A,B)
// mode(in,out)
// B = A + 1
//
Thread::ReturnValue
Thread::psi_increment(Object *& object1, Object *& object2)
{
  error_value = EV_NO_ERROR;
  
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  const long res1 = arithEvaluate(pval1);
     
    if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  //
  // The arg evaluate correctly so increment it
  //
  object2 = heap.newNumber(res1 + 1);

  return RV_SUCCESS;
}

//
// psi_decrement(A,B)
// mode(in,out)
// B = A - 1
//
Thread::ReturnValue
Thread::psi_decrement(Object *& object1, Object *& object2)
{
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  const long res1 = arithEvaluate(pval1);
   
  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  //
  // The arg evaluate correctly so decrement it
  //
  object2 = heap.newNumber(res1 - 1);

  return RV_SUCCESS;
}


