// compare.cc - Contains a function which compares the 2 terms
//              passed to it and returns the result of the
//              comparison in X2.
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
// $Id: compare.cc,v 1.4 2006/01/31 23:17:49 qp Exp $

#include <string.h>

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// Thread::psi_compare_var(var1, var2, res)
// Return -1 if var1 is more senior than var2.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_compare_var(Object *& object1, Object *& object2, Object *& object3)
{
  int32		res = 1;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  assert(val1->isAnyVariable());
  assert(val2->isAnyVariable());
  assert(val1->tTag() == val2->tTag());
  
  if (reinterpret_cast<void*>(val1) < reinterpret_cast<void*>(val2))
    {
      res = -1;
    }
  object3 = heap.newShort(res);
  return(RV_SUCCESS);
}

//
// psi_compare_atom(atom1, atom2, res)
// Return -1 if atom1 is less than atom2 alphabetically.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_compare_atom(Object *& object1, Object *& object2, Object *& object3)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  assert(val1->isAtom());
  assert(val2->isAtom());

  char* str1 = OBJECT_CAST(Atom*, val1)->getName();
  char* str2 = OBJECT_CAST(Atom*, val2)->getName();
  object3 = 
    heap.newShort(strcmp(str1, str2));
  return(RV_SUCCESS);
}

//
//  psi_compare_pointers(term1, term2)
//  Return true iff the pointers are identical.
//  mode(in,in)
//
Thread::ReturnValue
Thread::psi_compare_pointers(Object *& object1, Object *& object2)
{
  return(BOOL_TO_RV(object1->variableDereference() == 
		    object2->variableDereference()));
}




