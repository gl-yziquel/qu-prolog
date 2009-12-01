// pseudo_instr.cc -  pseudo-instructions
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: pseudo_instr.cc,v 1.6 2006/01/31 23:17:51 qp Exp $

#include "global.h"
#include "atom_table.h"
#include "pred_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern PredTab *predicates;

//
// The functions that define pseudo instructions have the following
// return values:
//   -1    fail
//    0    succeed
//   > 0   error number
//

//
// Create new variables for objectss associated with an arg with out mode
// The modes are bits with 1 meaning out mode.
//
void
Thread::psi1NewVars(int32 mode, Object *& object1)
{
  if (mode)
    {
      object1 = heap.newVariable();
    }
}

void
Thread::psi2NewVars(int32 mode, Object *& object1, Object *& object2)
{
  if (mode & 2)
    {
      object1 = heap.newVariable();
    }
  if (mode & 1)
    {
      object2 = heap.newVariable();
    }
}

void
Thread::psi3NewVars(int32 mode, 
		    Object *& object1, Object *& object2, Object *& object3)
{
  if (mode & 4)
    {
      object1 = heap.newVariable();
    }
  if (mode & 2)
    {
      object2 = heap.newVariable();
    }
  if (mode & 1)
    {
      object3 = heap.newVariable();
    }
}

void
Thread::psi4NewVars(int32 mode, 
		    Object *& object1, Object *& object2, 
		    Object *& object3, Object *& object4)
{
  if (mode & 8)
    {
      object1 = heap.newVariable();
    }
  if (mode & 4)
    {
      object2 = heap.newVariable();
    }
  if (mode & 2)
    {
      object3 = heap.newVariable();
    }
  if (mode & 1)
    {
      object4 = heap.newVariable();
    }
}

void
Thread::psi5NewVars(int32 mode, 
		    Object *& object1, Object *& object2, Object *& object3, 
		    Object *& object4, Object *& object5)
{
  if (mode & 16)
    {
      object1 = heap.newVariable();
    }
  if (mode & 8)
    {
      object2 = heap.newVariable();
    }
  if (mode & 4)
    {
      object3 = heap.newVariable();
    }
  if (mode & 2)
    {
      object4 = heap.newVariable();
    }
  if (mode & 1)
    {
      object5 = heap.newVariable();
    }
}

//
// Build a structure to hold the current X registers and PC.
//
Object*
Thread::psiSaveState(void)
{
  Object* pc = heap.newInteger(reinterpret_cast<wordptr>(programCounter));
  Structure* state = heap.newStructure(NUMBER_X_REGISTERS + 1);

  state->setFunctor(AtomTable::dollar);

  for (u_int i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      assert(X[i] != NULL);
      if (X[i] == NULL) 
	{
	  //X[i] = heap.newVariable();
          X[i] = AtomTable::nil;
	}
      state->setArgument(i+1, X[i]);
    }
  state->setArgument(NUMBER_X_REGISTERS + 1, pc);
  return(state);
}

//
// Build a call for a pseudo instruction for use in interrupt handling
// and fast retry
//
Object*
Thread::psi0BuildCall(word32 n)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(2);

  problem->setFunctor(AtomTable::psi0_resume);   // "$psi0_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);

  return(problem);
}

Object*
Thread::psi1BuildCall(word32 n, Object * object1)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(3);

  problem->setFunctor(AtomTable::psi1_resume);   // "$psi1_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
 
  return(problem);
}

Object*
Thread::psi2BuildCall(word32 n, Object * object1, Object * object2)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(4);

  problem->setFunctor(AtomTable::psi2_resume);   // "$psi2_resume"
  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);

  return(problem);
}

Object*
Thread::psi3BuildCall(word32 n, Object * object1, Object * object2, 
		      Object * object3)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(5);

  problem->setFunctor(AtomTable::psi3_resume);   // "$psi3_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);
  problem->setArgument(5, object3);

  return(problem);
}

Object*
Thread::psi4BuildCall(word32 n,
		      Object * object1, Object * object2, Object * object3,
		      Object * object4)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(6);

  problem->setFunctor(AtomTable::psi4_resume);   // "$psi4_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);
  problem->setArgument(5, object3);
  problem->setArgument(6, object4);

  return(problem);
}

Object*
Thread::psi5BuildCall(word32 n,
		      Object * object1, Object * object2, Object * object3,
		      Object * object4, Object * object5)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(7);

  problem->setFunctor(AtomTable::psi5_resume);   // "$psi5_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);
  problem->setArgument(5, object3);
  problem->setArgument(6, object4);
  problem->setArgument(7, object5);

  return(problem);
}

//
// Pseudo instruction error handlers
//
CodeLoc
Thread::psi0ErrorHandler(word32 n)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi0_error_handler,
			4, atoms, code)).getPredicate(code);
                                               // "$psi0_error_handler"
}

CodeLoc
Thread::psi1ErrorHandler(word32 n, Object * object1)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi1_error_handler,
			5, atoms, code)).getPredicate(code);
                                               // "$psi1_error_handler"
}

CodeLoc
Thread::psi2ErrorHandler(word32 n, Object * object1, Object * object2)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi2_error_handler,
			6, atoms, code)).getPredicate(code);
                                               // "$psi2_error_handler"
}

CodeLoc
Thread::psi3ErrorHandler(word32 n, Object * object1, Object * object2, 
			 Object * object3)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  X[6] = object3;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi3_error_handler,
			7, atoms, code)).getPredicate(code);
                                               // "$psi3_error_handler"
}

CodeLoc
Thread::psi4ErrorHandler(word32 n, Object * object1, Object * object2, 
			 Object * object3, Object * object4)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  X[6] = object3;
  X[7] = object4;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi4_error_handler,
			8, atoms, code)).getPredicate(code);
                                               // "$psi4_error_handler"
}

CodeLoc
Thread::psi5ErrorHandler(word32 n, Object * object1, Object * object2, 
			 Object * object3, Object * object4, 
			 Object * object5 )
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  X[6] = object3;
  X[7] = object4;
  X[8] = object5;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi5_error_handler,
			9, atoms, code)).getPredicate(code);
                                               // "$psi5_error_handler"
}














