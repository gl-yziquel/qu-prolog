// write.cc - Different specialised versions of write for atoms, integers, and
//	      variables.
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
// $Id: write.cc,v 1.9 2004/04/28 00:49:30 qp Exp $

#include <iostream>
#include <sstream>
#include <string.h>

#include "config.h"

#include "atom_table.h"
#include "is_ready.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern IOManager *iom;

//
// Different specialised versions of write for atoms.
//

//
// psi_write_atom(stream, atom)
// Default method for writing atoms->  The string is written without any
// processing.
// mode(in,in)
// 
Thread::ReturnValue
Thread::psi_write_atom(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  DEBUG_ASSERT(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if(!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  // IS_READY_STREAM(stream, -1);
 
  *stream << atoms->getAtomString(val2);

  return(RV_SUCCESS);
}

/*
  The string is safe if the string is one of the followings:
  1.  []
  2.  {}
  3.  ;
  4.  !
  5.  abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 .
  6.  #$&*+-./:<=>?@^~\
*/
static bool
SafeAtom(const char *s)
{
  if (*s == '\0' ||
      streq(s, ".") ||
      streq(s, "|"))
    {
      //
      // Null atom ('') or a single full stop ('.') or a single '|' is unsafe.
      //
      return(false);
    }
  else if (streq(s, "[]") ||
	   streq(s, "{}") ||
	   streq(s, ";") ||
	   streq(s, "!"))
    {
      return(true);
    }
  else if (strchr("abcdefghijklmnopqrstuvwxyz", *s) != NULL)
    {
      s++;
      while(*s != '\0')
	{
	  if (strchr("abcdefghijklmnopqrstuvwxyz"
		     "ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789",
		     *s) !=
	      NULL)
	    {
	      //
	      // index finds the given character in the 'safe'
	      // range.  So check the next character.
	      // 
	      s++;
	    }
	  else
	    {
	      //
	      // index cannot find the character in the 'safe'
	      // range.  So it is unsafe.
	      //
	      return(false);
	    }
	}
      return(true);
    }
  else
    {
      while(*s != '\0')
	{
	  if (strchr("#$&*+-./:<=>?@^~\\|", *s) != NULL)
	    {
	      //
	      // index finds the given character in the 'safe'
	      // range.  So check the next character.
	      // 
	      s++;
	    }
	  else
	    {
	      //
	      // index cannot find the character in the 'safe'
	      // range.  So it is unsafe.
	      //
	      return(false);
	    }
	}
      return(true);
    }
}

void
writeqAtom(const char *s, QPStream *stream)
{
  if (SafeAtom(s))
    {
      *stream << s;
    }
  else
    {
      //
      // The atom is not safe.  Quotes are needed.
      //
      *stream << '\'';
      while (*s != '\0')
	{
	  //
	  // For some characters, an extra copy of
	  // the same character is needed.
	  //
	  switch (*s)
	    {
	    case '\\':
	    case '\'':
	      *stream << *s;
	      break;
	    }
	  //
	  // Write the character out.
	  //
	  *stream << *s;
	  s++;
	}
      *stream << '\'';
    }
  return;
}

//
// psi_writeq_atom(stream, atom)
// The string is written with quotes whenever it is needed.  The condition for
// the quotes is when the string consists of characters other than
//	$abcdefghijklmnopqrstuvwxyz_0123456789 .
// mode(in,in)
// 
Thread::ReturnValue
Thread::psi_writeq_atom(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  DEBUG_ASSERT(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if(!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *s = atoms->getAtomString(val2);

  writeqAtom(s, stream);

  return(RV_SUCCESS);
}

//
// psi_write_integer(stream_index, integer)
// Write for integers.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_integer(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  // IS_READY_STREAM(stream, -1);

  *(stream) << val2->getNumber();

  return(RV_SUCCESS);
}

//
// Different specialised versions of write for variables.
//

//
// psi_write_var(stream_index, variable)
// Default method for writing variables.  If the variable has a name, use the
// name.  Otherwise, the location of the variable is written as a base 16
// number with '_' preceding it.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_var(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  DEBUG_ASSERT(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  
  if (!pval2.getTerm()->isVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  DEBUG_ASSERT(pval2.getTerm()->isVariable());
  Variable* var = OBJECT_CAST(Variable*, pval2.getTerm());

  if (var->hasExtraInfo() && var->getName() != NULL)
    {
      //
      // Use the existing name.
      //
      *(stream) << atoms->getAtomString(var->getName());
    }
  else
    {
      //
      // No name.
      //
     *(stream) << "_";
     *(stream) << (int)(reinterpret_cast<heapobject*>(var) - heap.getBase());
    }
  return(RV_SUCCESS);
}

//
// Write out the variable name of a variable.  The system generates one and
// records the association if none exists.
//
void
Thread::writeVarName(Object* ref, NameGen gen,
		     word32& counter, QPStream *stream)
{
  DEBUG_ASSERT(ref->isAnyVariable());

  Reference* var = OBJECT_CAST(Reference*, ref);

  DEBUG_ASSERT(var->hasExtraInfo());
  
  Atom* varName = var->getName();
  if (varName == NULL)
    {
      //
      // There is no name for the variable.  Generate one.
      //
      varName = (*gen)(this, counter, atom_buf1);
      //
      // Link the name and the variable up together.
      //
      names.setNameOldVar(varName, ref, *this);
    }
  *stream << atoms->getAtomString(varName);
}

//
// psi_writeR_var(stream_index, variable)
// Write the assigned name, which is stored in the name table, for the
// variable.
//
// The name is assigned either by the user via readR/1 or generated by
// writeR_var if it does not have one.
//
// This function is used by writeR/1 and portray/1.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_writeR_var(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  DEBUG_ASSERT(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  
  if (!pval2.getTerm()->isVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  DEBUG_ASSERT(pval2.getTerm()->isVariable());
  Variable* var = OBJECT_CAST(Variable*, pval2.getTerm());

  var = addExtraInfo(var);
  writeVarName(var, 
	       &Thread::GenerateVarName,
	       metaCounter,
	       stream);
  return(RV_SUCCESS);
}

//
// Different specialised versions of write for object variables.
//

//
// psi_write_object_variable(stream_index, object_variable)
// Default method for writing object variables.  If the variable has a name,
// use the name.  Otherwise, output a name of the form _x1, _x2, ...
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_object_variable(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  DEBUG_ASSERT(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isObjectVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  

  if (!pval2.getTerm()->isObjectVariable() || 
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  ObjectVariable* obvar = OBJECT_CAST(ObjectVariable*, pval2.getTerm());

  DEBUG_ASSERT(obvar->hasExtraInfo());

  if (obvar->getName() != NULL)
    {
      *stream << atoms->getAtomString(obvar->getName());
    }
  else
    {
      writeVarName(obvar, 
		   &Thread::GenerateObjectVariableName,
		   objectCounter, stream);
    }
  return(RV_SUCCESS);
}

//
// psi_writeR_ObjectVariable(stream_index, ObjectVariable)
// Write the assigned name, which is stored in the name table, for the
// object variable.
//
// The name is assigned either by the user via readR/1 or generated by
// writeR_ObjectVariable if it does not have one.
//
// This function is used by writeR/1 and portray/1.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_writeR_object_variable(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  DEBUG_ASSERT(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);


  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isObjectVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  

  if (!pval2.getTerm()->isObjectVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  //
  // Get the stream.
  //

  ObjectVariable* obvar = OBJECT_CAST(ObjectVariable*, pval2.getTerm());

  if (obvar->getName() != NULL)
    {
      *stream << atoms->getAtomString(obvar->getName());
    }
  else
    {
      writeVarName(obvar, 
		   &Thread::GenerateRObjectVariableName,
		   objectCounter, stream);
    }
  return(RV_SUCCESS);
}

//
// psi_writeq_ObjectVariable(stream_index, ObjectVariable)
//
// Write the assigned name, which is stored in the name table, for the
// object variable.
//
// The name is assigned either by the user via readR/1 or generated by
// writeR_ObjectVariable if it does not have one.
//
// This function is used by writeq/1 and portray/1.
//
// Funny names are quoted.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_writeq_object_variable(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  DEBUG_ASSERT(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isObjectVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  

  if (!pval2.getTerm()->isObjectVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  //
  // Get the stream.
  //

  ObjectVariable* obvar = OBJECT_CAST(ObjectVariable*, pval2.getTerm());

  if (obvar->getName() != NULL)
    {
      const char *s = atoms->getAtomString(obvar->getName());
      writeqAtom(s, stream);
    }
  else
    {
      writeVarName(obvar,
		   &Thread::GenerateRObjectVariableName,
		   objectCounter, stream);
    }
  
  return(RV_SUCCESS);
}

//
// A low-level dump of the term
//
Thread::ReturnValue
Thread::psi_debug_write(Object *& object1)
{
  #ifdef DEBUG
  object1->printMe_dispatch(*atoms,false);
  #endif
  return(RV_SUCCESS);
}


