// name.cc - Functions which build up a string which corresponds to a 
//           given list, or build up a list whose elements correspond 
//           to a given name.
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
// $Id: name.cc,v 1.2 2000/12/13 23:10:02 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// psi_atom_codes(atom, var)
// Convert an atom to a list of character codes.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_atom_codes(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  DEBUG_ASSERT(val1->isAtom());
 
  Object* tail = AtomTable::nil;
  const char *string = atoms->getAtomString(val1);

  for (int i = strlen(string) - 1; i >= 0; i--)
    {
      Object* head = heap.newNumber(string[i]);
      Cons* temp = heap.newCons(head, tail);
      tail = temp;
    }
  
  object2 = tail;
  return(RV_SUCCESS);
}

//
// psi_codes_atom(list integer, var)
// Convert from a list of character codes to an atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_codes_atom(Object *& object1, Object *& object2)
{
  char		*s;
  Object* list = object1->variableDereference();

  for (s = atom_buf1; list->isCons(); s++)
    {
      Cons* clist = OBJECT_CAST(Cons*, list);
      Object* head = clist->getHead()->variableDereference();
      list = clist->getTail()->variableDereference();
      DEBUG_ASSERT(head->isShort());
      *s = head->getNumber();
    }
  *s = '\0';
  object2 = atoms->add(atom_buf1);
  return(RV_SUCCESS);
}

//
// psi_char_code(char, var)
// Convert a character to its character code.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_char_code(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  DEBUG_ASSERT(val1->isAtom());
  
  const char *string = atoms->getAtomString(val1);
  if (string[1] != '\0')
    {
      return(RV_FAIL);
    }
  else
    {
      object2 = heap.newShort(string[0]);
      return(RV_SUCCESS);
    }
}

//
// psi_code_char(integer, var)
// Convert a character code to its character.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_code_char(Object *& object1, Object *& object2)
{
  char string[2];
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  DEBUG_ASSERT(val1->isShort());
  
  string[0] = val1->getNumber();
  string[1] = '\0';
  object2 = atoms->add(string);
  return(RV_SUCCESS);
}




