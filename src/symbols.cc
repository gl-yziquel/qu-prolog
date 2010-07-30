// symbols.cc - Contains a function which can be used to manage the access to
//		symbol tables.
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
// $Id: symbols.cc,v 1.5 2006/01/31 23:17:51 qp Exp $

#include "global.h"
#include "atom_table.h"
#include "pred_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern PredTab *predicates;

//
// psi_get_atom_from_atom_table(integer, atom, integer)
// Return the next atom in the atom table.
// mode(in,out,out)
//
Thread::ReturnValue
Thread::psi_get_atom_from_atom_table(Object *& object1, Object *& object2, 
				     Object *& object3)
{
  int32		i;
  Object* val1 = heap.dereference(object1);
  assert(val1->isNumber());

  i = val1->getInteger();

  while (++i < (signed) atoms->size())
    {
      if (! atoms->isEntryEmpty((AtomLoc)(i))) 
	{
	  object2 = atoms->getAtom((AtomLoc)(i));
	  object3 = heap.newInteger(i);
	  return(RV_SUCCESS);
	}
    }
  return(RV_FAIL);
}

//
// psi_get_pred_from_pred_table(integer, atom, integer, integer)
// Return the next predicate in the predicate table.
// mode(in,out,out,out)
//
Thread::ReturnValue
Thread::psi_get_pred_from_pred_table(Object *& object1, Object *& object2, 
				     Object *& object3, Object *& object4)
{
  int32		i;
  Object* val1 = heap.dereference(object1);
  assert(val1->isInteger());

  i = val1->getInteger();

  while (++i < (signed) predicates->size())
    {
      if (! predicates->isEmpty((PredLoc)(i))) 
	{
	  object2 = predicates->getPredName((PredLoc)(i), atoms);
	  object3 = heap.newInteger(predicates->getArity((PredLoc)(i)));
	  object4 = heap.newInteger(i);
	  return(RV_SUCCESS);
	}
    }
  return(RV_FAIL);
}

//
// symtype outputs into object3 :
//  (0)	If the predicate has no entry point defined.
//  (1) If the predicate is a dynamic predicate.
//  (2) If the predicate is a compiled predicate.
//  (3) If the predicate is an escape predicate.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_symtype(Object *& object1, Object *& object2, Object *& object3)
{
    Object* val1 = heap.dereference(object1);
    Object* val2 = heap.dereference(object2);

    assert(val1->isAtom());
    assert(val2->isShort());

    PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, val1), 
				     val2->getInteger(), atoms, code);
    if (loc == EMPTY_LOC) 
      {
	//
	// It does not have an entry point defined.
	//
	object3 = heap.newInteger(0);
      }
    else
      {
	PredCode pred = predicates->getCode(loc);
	switch (pred.type())
	  {
	  case PredCode::ESCAPE_PRED:
	    object3 = heap.newInteger(3);
	    break;
	  case PredCode::STATIC_PRED:
	    object3 = heap.newInteger(2);
	    break;
	  case PredCode::DYNAMIC_PRED:
	    object3 = heap.newInteger(1);
	    break;
	  }
      }
    return(RV_SUCCESS);
}








