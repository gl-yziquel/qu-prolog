// objvar.cc - Object variable manipulations.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: object_variable.cc,v 1.5 2006/01/31 23:17:51 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// psi_object_variable(term)
// Succeeds if term is an object variable.
// mode(in)
//
Thread::ReturnValue
Thread::psi_object_variable(Object *& object)
{
  assert(object->hasLegalSub());
  PrologValue pval(object);

  heap.prologValueDereference(pval);

  return BOOL_TO_RV(pval.getTerm()->isObjectVariable());
}

//
// psi_local_object_variable(term)
// Succeeds if X0 is a local object variable.
// mode(in)
//
Thread::ReturnValue
Thread::psi_local_object_variable(Object *& object)
{
  assert(object->variableDereference()->hasLegalSub());
  Object* term = heap.dereference(object);

  return BOOL_TO_RV(term->isLocalObjectVariable());
}

//
// psi_new_ObjectVariable(variable)
// Return a new object variable.
// mode(out)
//
Thread::ReturnValue
Thread::psi_new_object_variable(Object *& object)
{
  object = heap.newObjectVariable();

  return RV_SUCCESS;
}

//
// psi_is_distinct(ObjectVariable1, ObjectVariable2)
// Succeeds iff ObjectVariable1 and ObjectVariable2 are distinct object vars
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_is_distinct(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  return BOOL_TO_RV(val1->isObjectVariable() &&
		    val2->isObjectVariable() &&
		    val1->distinctFrom(val2));
}

//
// psi_get_distinct(ObjectVariable, variable)
// Retrieve the distinctness information under ObjectVariable.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_distinct(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  if (! val1->isObjectVariable())
    {
      return RV_FAIL;
    }
  else
    {
      assert(val1->isObjectVariable());

      ObjectVariable *object_variable =
	OBJECT_CAST(ObjectVariable *, val1);

      object2 = object_variable->getDistinctness();

      return RV_SUCCESS;
    }
}

static inline bool
object_variable_suffix_char(char c)
{
  return ('0' <= c && c <= '9') || c == '_';
}

//
// psi_object_variable_name_to_prefix(atom, atom)
// Strip off an object variable suffix.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_object_variable_name_to_prefix(Object *& object1,
					   Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  assert(val1->isAtom());

  const char *s = OBJECT_CAST(Atom*, val1)->getName();

  int i;

  if (strlen(s) ==  0)    // The empty atom
    {
      return RV_FAIL;
    }

  // Search backwards for first non-suffix character
  for (i = static_cast<int>(strlen(s) - 1);
       i >= 0 && object_variable_suffix_char(s[i]);
       i--)
    ;

  if (i < 0) 
    {
      return RV_FAIL;
    } 
  else if (s[i] < 'a' || s[i] > 'z') 
    {
      return RV_FAIL;
    } 
  else 
    {
      if (s[0] == '_') 
	{
	  strncpy(atom_buf1, s+1, i);
	  atom_buf1[i] = '\0';
	} 
      else 
	{
	  strncpy(atom_buf1, s, i+1);
	  atom_buf1[i+1] = '\0';
	}
      
      object2 = atoms->add(atom_buf1);
      
      return RV_SUCCESS;
    }
}

//
// psi_valid_object_variable_prefix(atom)
// Returns true if the atom is a valid ObjectVariable prefix.
// mode(in)
//
Thread::ReturnValue
Thread::psi_valid_object_variable_prefix(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
 
  assert(val1->isAtom());
  
  const char *s = OBJECT_CAST(Atom*, val1)->getName();

  size_t i;

  for (i = strlen(s); i > 0 && 'a' <= s[i-1] && s[i-1] <= 'z'; i--)
    ;
  
  return BOOL_TO_RV(i == 0);
}


















