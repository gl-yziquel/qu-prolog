// c_to_prolog.cc - Support functions for calling Qu-Prolog from C++.
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: c_to_prolog.cc,v 1.9 2006/01/31 23:17:49 qp Exp $

#include <stdarg.h>

#include "global.h"
#include "atom_table.h"
#include "code.h"
#include "pred_table.h"
#include "qem_options.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern PredTab *predicates;
extern QemOptions *qem_options;

//
// Save the current state into a choice point.  Then, set up the registers in
// a new thread to be ready for execution.  Return the new thread as an
// identifier.  If query/arity is undefined or unable to create a new thread,
// NULL is returned.
//
Thread&
Thread::initialise(Object* query, const word32 arity, va_list ap)
{
  static const CodeLoc success =
    predicates->getCode(predicates->lookUp(atoms->add("$succ_return_to_c"),
					   0, atoms, code)).getPredicate(code);
  static const CodeLoc failure =
    predicates->getCode(predicates->lookUp(atoms->add("$fail_return_to_c"),
					   0, atoms, code)).getPredicate(code);

  //
  // Look up the location for query.
  //
  assert(query->isAtom());
  const PredLoc loc =
    predicates->lookUp(OBJECT_CAST(Atom*, query), arity, atoms, code);
  if (loc == EMPTY_LOC)
    {
      Fatal(__FUNCTION__, "Unknown query");
    }

  //
  // Create a new thread to execute the query.
  //
  Thread *th = new Thread(this,
			  buffers,
			  scratchpad,
			  heap,
			  gcstack,
			  gcbits,
			  names,
			  ipTable,
			  bindingTrail,
			  otherTrail,
			  qem_options->EnvironmentStackSize(),
			  qem_options->ChoiceStackSize());


  // Create a choice point to hold the state and the alternative is set
  // to the predicate that handles failure from the query.
  //
  th->currentChoicePoint = pushChoicePoint(failure, 0);
  
  //
  // Set up registers.
  //
  th->programCounter = predicates->getCode(loc).getPredicate(code);
  th->continuationInstr = success;
  for (u_int i = 0; i < arity; i++)
    {
      th->X[i] = va_arg(ap, Object*);
    }
  
  //
  // Return the new thread as an identifier.
  //
  return(*th);
}

//
// Save the current state into a choice point.  Then, set up the registers in
// a new thread to be ready for execution.  Return the new thread as an
// identifier.  If query/arity is undefined or unable to create a new thread,
// NULL is returned.
//
Thread&
Thread::QuPSetUpQuery(Object* query, const word32 arity, ...)
{
  va_list ap;

  va_start(ap, arity);
  Thread& th = initialise(query, arity, ap);
  va_end(ap);
  return(th);
}

//
// Execute the query to obtain the next solution.
// Return:
//	Value	Meaning
//	0	fail
//	1	success
//
word32
Thread::QuPNextSolution(void)
{
  const word32 result = Execute() == 0 ? 1 : 0;

  return(result);
}

//
// Restore to the state before SetUpQuery.  Any data, except side effects,
// created after SetUpQuery is lost.
//
bool
Thread::QuPCutFailQuery(void)
{
  //
  // Backtrack to the state before QuPSetUpQuery.
  //
  choiceStack.failToBeginning(*this);
  
  return(true);
}

//
// Restore to the state before SetUpQuery.  Keep any data created after
// SetUpQuery.
//
bool
Thread::QuPCutQuery(void)
{
  //
  // Cut back to the state before QuPSetUpQuery.
  //
  tidyTrails(choiceStack.getHeapAndTrailsState(choiceStack.firstChoice()));

  return(true);
}

//
// Execute the query to obtain the first solution.
// Return:
//	Value	Meaning
//	0	fail
//	1	success
//
word32
Thread::QuPQueryCut(Object* query, const word32 arity ...)
{
  va_list		ap;
  
  //
  // Set up the query.
  //
  va_start(ap, arity);
  Thread& th = initialise(query, arity, ap);
  assert(&th != NULL);
  va_end(ap);
  
  //
  // Obtain the first solution.
  //
  const word32 result = th.QuPNextSolution();
  
  //
  // Clean up after the execution.
  //
  th.QuPCutQuery();

  //
  // Delete the thread.
  //
  delete &th;
  
  //
  // Return the result.
  //
  return(result);
}

//
// Execute the query.  Once the first solution is obtained, clean up the data
// areas and only leave the side effects behind.
// Return:
//	Value	Meaning
//	0	fail
//	1	success
//
word32
Thread::QuPQueryCutFail(Object* query, const word32 arity ...)
{
  va_list ap;
  
  //
  // Set up the query.
  //
  va_start(ap, arity);
  Thread& th = initialise(query, arity, ap);
  assert(&th != NULL);
  va_end(ap);
  
  //
  // Obtain the first solution.
  //
  const word32 result = th.QuPNextSolution();
  
  //
  // Clean up the result except side effects after the execution.
  //
  th.QuPCutFailQuery();
  
  //
  // Delete the thread.
  //
  delete &th;

  //
  // Return the result.
  //
  return(result);
}



