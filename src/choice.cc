// choice.cc - Definition of a choice point.
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
// $Id: choice.cc,v 1.6 2002/11/03 08:37:24 qp Exp $

#include "area_offsets.h"
#include "choice.h"
#include "code.h"
#include "defs.h"
#include "environment.h"
#include "indent.h"
#include "thread_qp.h"



//
// Restore the heap and name table back to the previous state
// recorded in a choice point.
//
inline void Choice::restoreHeapNameTable(Thread& th) const
  {
    th.backtrackTo(heapAndTrailsState);
  }                                                                             
//
// Restore the thread back to the previous state recorded in a
// choice point.
//
void Choice::restore(Thread& th) const
{
  word32 i;

  th.getStatus() = status;
  th.ContinuationInstr() = continuationInstr;
  restoreHeapNameTable(th);
  th.CurrentEnvironment() = currentEnvironment;
  
  th.EnvStack().setTop(envStackTop);
  
  th.MetaCounter() = metaCounter;
  th.ObjectCounter() = objectCounter;
  
  for (i = 0; i < NumArgs; i++)
    {
      th.XRegs()[i] = X[i];
    }
}

//
// Push a new choice point onto the stack.  The current state of the
// thread is saved in the choice point and the location of the
// alternative is recorded.  The pointer to the newly created choice
// point is then returned.
// If ChoiceLoc or StackLoc changes representation, then a bug may
// occur if this is not changed.
//
//  ChoiceLoc ChoiceStack::push(Thread& th,
//  			    const CodeLoc alternative,
//  			    const word32 NumXRegs)
//  {
//    ChoiceLoc	index;
//    EnvLoc	TopEnv;
  
//    index = pushRecord(size(NumXRegs));
  
//    if (isEnvProtected(th.CurrentChoicePoint(), th.CurrentEnvironment()))
//      {
//        TopEnv = getEnvTop(th.CurrentChoicePoint());
//      }
//    else
//      {
//        TopEnv = th.CurrentEnvironment() +
//  	th.EnvStack().envSize(th.CurrentEnvironment());
//      }
    
//    fetchChoice(index)->assign(th, NumXRegs, TopEnv);
//    nextClause(index) = alternative;
  
//    return(index);
//  }

//
// Pop the current choice point and return a pointer to previous
// choice point.
//
//  ChoiceLoc       ChoiceStack::pop(const ChoiceLoc loc)
//    {
//      ChoiceLoc	previous;
    
//      previous = fetchChoice(loc)->getPreviousChoice();
//      popRecord();
    
//      return(previous);
//    }

//
// Upon failure, set the registers up for the execution of the next
// alternative from a given choice point.
//
//void ChoiceStack::getNextAlternative(Thread& th, const ChoiceLoc index)
//{ 
//  th.ProgramCounter() = nextClause(index);
//  th.CutPoint() = fetchChoice(index)->getCutPoint();
//}

//
// Display meaningful fields for debugging
ostream&
ChoiceStack::Display(ostream& ostrm, ChoiceLoc index, const size_t depth) const
{
  const Choice *c = inspectChoice(index);
  
  Indent(ostrm, depth);
  ostrm << "nextClause=" << hex << c->inspectNextClause() << dec << endl;

  Indent(ostrm, depth);
  ostrm << "currentEnvironment=" << hex <<  c->currentEnv() << dec << endl;

  Indent(ostrm, depth);
  ostrm << "envStackTop=" << hex << c->getEnvTop() << dec << endl;

  Indent(ostrm, depth);
  ostrm << "previousChoicePoint=" << hex << c->getPreviousChoice() << dec << endl;
  Indent(ostrm, depth);
  ostrm << "cutPoint=" << hex << c->getCutPoint() << dec << endl;
 
  Indent(ostrm, depth);
  ostrm << "numArgs=" << hex << c->getNumArgs() << dec << endl;

  return ostrm;
}










