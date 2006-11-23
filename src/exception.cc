// exception.cc - Define low level exception support routines.
//                The idea evolved from IC-Prolog and made compatible with
//                Quintus Prolog.
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
// $Id: exception.cc,v 1.4 2006/01/31 23:17:50 qp Exp $

#include "thread_qp.h"

//
// psi_get_catch(variable)
// Return the current value in the catch register.
// mode(out)
//
Thread::ReturnValue
Thread::psi_get_catch(Object *& object1)
{
  object1 = heap.newInteger(catchPoint);
  return(RV_SUCCESS);
}

//
// psi_set_catch(choice point)
// Set the catch register with the given value.
// mode(in)
//
Thread::ReturnValue
Thread::psi_set_catch(Object *& object1)
{
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isNumber());
  
  catchPoint = val1->getInteger();
  return(RV_SUCCESS);
}

//
// psi_failpt_to_catch
// Transfer the value from currentChoicePoint to catch.
// mode()
//
Thread::ReturnValue
Thread::psi_failpt_to_catch(void)
{
  catchPoint = currentChoicePoint;
  return(RV_SUCCESS);
}

//
// psi_catch_to_failpt
// Transfer the value from catch to currentChoicePoint.
// mode()
//
Thread::ReturnValue
Thread::psi_catch_to_failpt(void)
{
  currentChoicePoint = catchPoint;
  return(RV_SUCCESS);
}

//
// psi_psi_resume(state)
// Restore saved X regs and PC
// mode(in)
//
Thread::ReturnValue
Thread::psi_psi_resume(Object *& object1)
{
  //
  // !!! NOTE !!!
  //
  // In all the uses of psi_resume this pseudo-instruction
  // is immediately followed by a DEALLOCATE instruction.
  // BUT psi_resume resets the PC and so this DEALLOCATE is
  // never called. To compensate the DEALLOCATE code is
  // included below.
  //
  // !!! POSSIBLE PROBLEM !!!
  // 
  // If psi_resume is ever used in a predicate that does not
  //  ALLOCATE or DEALLOCATEs before the call then there will be
  //  trouble.
  
  EnvLoc PrevEnv = currentEnvironment;
  envStack.retrieve(PrevEnv, currentEnvironment,
		       continuationInstr);
  
  Object* state = heap.dereference(object1);

  assert(state->isStructure());
  assert(OBJECT_CAST(Structure*, state)->getArity() 
	       == NUMBER_X_REGISTERS+1);
  
  for (u_int i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      X[i] = OBJECT_CAST(Structure*, state)->getArgument(i+1);
    }
  Object* pc = 
    OBJECT_CAST(Structure*, state)->getArgument(NUMBER_X_REGISTERS+1);
  assert(pc->isNumber());
  programCounter = reinterpret_cast<CodeLoc>(pc->getInteger());
  return(RV_SUCCESS);
}



