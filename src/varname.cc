// varname.cc - Get and set variable names.
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
// $Id: varname.cc,v 1.3 2000/12/13 23:10:03 qp Exp $

#include <iostream.h>
#include <strstream.h>

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// Name(get) unnamed vars in sub adding these vars to varlist.
// If do_name is true then unnamed vars are given names.
// If get_vars is true then unnamed vars are collected into varlist.
//

void
Thread::name_term_vars_sub(Object* sub, Object*& varlist, 
			   bool do_name, bool get_vars)
{
  DEBUG_ASSERT(sub->isNil() || (sub->isCons() && OBJECT_CAST(Cons*, sub)->isSubstitutionBlockList()));

  for (;sub->isCons();sub = OBJECT_CAST(Cons*, sub)->getTail() )
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, sub)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* subblock 
	= OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());
      
      for (size_t i = 1; i <= subblock->getSize(); i++)
        {
	  name_term_vars(subblock->getRange(i), varlist, 
			 do_name, get_vars);
          name_term_vars(subblock->getDomain(i), varlist,
			 do_name, get_vars);
	}
    }
  return;
}

//
// Name(get) unnamed vars in term adding these vars to varlist.
// If do_name is true then unnamed vars are given names.
// If get_vars is true then unnamed vars are collected into varlist.
//

void
Thread::name_term_vars(Object* term, Object*& varlist, 
		       bool do_name, bool get_vars)
{
  DEBUG_ASSERT(term->variableDereference()->hasLegalSub());
  term = heap.dereference(term);
  switch (term->utag())
    {
    case Object::uVar:
      if (OBJECT_CAST(Reference*, term)->getName() == NULL)
	{
	  if (get_vars)
            {
	      Cons* temp = heap.newCons(term, varlist);
	      varlist = temp;
	    }
	  if (do_name)
	    {
	      Atom* name = GenerateVarName(this, metaCounter, atom_buf1);
              term = addExtraInfo(OBJECT_CAST(Variable*, term));
	      names.setNameOldVar(name, term, *this);
	    }
	}
      break;

    case Object::uObjVar:
      if (!term->isLocalObjectVariable() &&
	  OBJECT_CAST(Reference*, term)->getName() == NULL)
	{
	  if (get_vars)
            {
	      Cons* temp = heap.newCons(term, varlist);
	      varlist = temp;
	    }
	  if (do_name)
	    {
	      Atom* name = GenerateRObjectVariableName(this, objectCounter, atom_buf1);
	      names.setNameOldVar(name, term, *this);
	    }
	}
      break;

    case Object::uCons:
      {
	Object* list = term;
	for (; list->isCons();
	     list = heap.dereference(OBJECT_CAST(Cons*, list)->getTail()))
	  {
	    name_term_vars(OBJECT_CAST(Cons*, list)->getHead(), 
			   varlist, do_name, get_vars);
	  }
	if (!list->isConstant())
	  {
	    name_term_vars(list, varlist, do_name, get_vars);
	  }
      }
      break;

    case Object::uStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	if (!str->getFunctor()->isConstant())
	  {
	    name_term_vars(str->getFunctor(), varlist, 
			   do_name, get_vars);
	  }

	for (size_t i = 1; i <= str->getArity(); i++)
	  {
	    name_term_vars(str->getArgument(i), varlist, 
			   do_name, get_vars);
	  }
      }
      break;

    case Object::uQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, term);
	if (!quant->getQuantifier()->isConstant())
	  {
	    name_term_vars(quant->getQuantifier(), varlist, 
			   do_name, get_vars);
	  }
	name_term_vars(quant->getBoundVars(), varlist, 
		       do_name, get_vars);
	name_term_vars(quant->getBody(), varlist, do_name, get_vars);
      }
      break;

    case Object::uConst:
      break;

    case Object::uSubst:
      name_term_vars_sub(OBJECT_CAST(Substitution*, 
				     term)->getSubstitutionBlockList(), 
			 varlist, do_name, get_vars);
      name_term_vars(OBJECT_CAST(Substitution*, term)->getTerm(), 
		     varlist, do_name, get_vars);
      break;
      
    default:
      DEBUG_ASSERT(false);
      break;
    }
}


//
// psi_get_var_name(variable, name)
// Return the name of the variable if there is one. Otherwise, fail.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_var_name(Object *& object1, Object *& object2)
{
  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  if (! val1->isAnyVariable())
    {
      return(RV_FAIL);
    }
  else
    {
      Reference* var = OBJECT_CAST(Reference*, val1);
      Object* name = var->getName();

      if (name == NULL)
	{
	  return(RV_FAIL);
	}
      else
	{
	  object2 = name;
	  return(RV_SUCCESS);
	}
    }
}

//
// psi_set_var_name(var, name)
// Set the name for the given variable using the supplied name as the
// prefix.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_set_var_name(Object *& object1, Object *& object2)
{
  ostrstream strm(atom_buf1, ATOM_LENGTH);
  streampos StrmLoc;
  int32 counter = 0;

  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  DEBUG_ASSERT(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (!val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  Variable* var = OBJECT_CAST(Variable*, val1);
  if (var->getName() != NULL)
    {
      return(RV_FAIL);
    }
  //
  // else no name
  //
  var = addExtraInfo(var);
   
  //
  // Generate the variable name for the variable.
  //

  //
  // Set the prefix.
  //
  if (strm.good() &&
      strm.form("%s_", atoms->getAtomString(val2)).fail())
    {
      Fatal(__FUNCTION__,
	    "problem in putting prefix for set_var_name/2");
    }
  StrmLoc = strm.tellp();
  //
  // first char of name should be in A..Z
  //
  if (atom_buf1[0] < 'A' || atom_buf1[0] > 'Z')
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  //
  // Find a suitable suffix.
  //
  AtomLoc name_loc;
  do
    {
      strm.seekp(StrmLoc);
      if (strm.good() && strm.form("%d", counter).fail())
	{
	  Fatal(__FUNCTION__,
		"problem in putting suffix for set_var_name/2");
	}
      strm << ends;
      counter++;
      name_loc = atoms->lookUp(atom_buf1);
    } while (name_loc != EMPTY_LOC && 
	     names.getVariable(atoms->getAtom(name_loc)) != NULL);

  //
  // Add to the tables.
  //
  Atom* name = atoms->add(atom_buf1);
  names.setNameOldVar(name, var, *this);

  return(RV_SUCCESS);
}

//
// psi_set_ObjectVariable_name(objvar, name)
// Set the name for the given object variable using the supplied name as the
// prefix.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_set_object_variable_name(Object *& object1, Object *& object2)
{
  ostrstream strm(atom_buf1, ATOM_LENGTH);
  streampos StrmLoc;

  DEBUG_ASSERT(object1->variableDereference()->hasLegalSub());
  DEBUG_ASSERT(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!val1->isObjectVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  ObjectVariable* var = OBJECT_CAST(ObjectVariable*, val1);
  if (var->getName() != NULL)
    {
      return(RV_FAIL);
    }
  //
  // else no name
  //
 ObjectVariable* newvar = heap.newObjectVariable();
 
  //
  // Generate the variable name for the object variable.
  //

  //
  // Set the prefix.
  //
  if (strm.good() &&
      strm.form("%s_", atoms->getAtomString(OBJECT_CAST(Atom*, val2))).fail())
    {
      Fatal(__FUNCTION__, "problem in putting prefix for set_ObjectVariable_name/2");
    }
  StrmLoc = strm.tellp();

  //
  // Find a suitable suffix.
  //
  AtomLoc name_loc;
  do
    {
      strm.seekp(StrmLoc);
      if (strm.good() && strm.form("%d", objectCounter).fail())
	{
	  Fatal(__FUNCTION__,
		"problem in putting suffix for set_ObjectVariable_name/2");
	}
      strm << ends;
      objectCounter++;
      name_loc = atoms->lookUp(atom_buf1);
    } while (name_loc != EMPTY_LOC && 
	     names.getVariable(atoms->getAtom(name_loc)) != NULL);

  //
  // Add to the tables.
  //
  Atom* name = atoms->add(atom_buf1);

  names.setNameOldVar(name, newvar, *this);
  bindObjectVariables(var, newvar);

  return(RV_SUCCESS);
}

//
// psi_get_unnamed_vars(term,varlist)
// Get all unnamed (ob)vars in term - return them in varlist.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_unnamed_vars(Object *& object1, Object *& object2)
{
  Object* varlist = AtomTable::nil;

  name_term_vars(object1, varlist, false, true);

  object2 = varlist;

  return(RV_SUCCESS);
}
//
//
// psi_name_vars(term,varlist)
// Name all unnamed (ob)vars in term - return them in varlist.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_name_vars(Object *& object1, Object *& object2)
{
  Object* varlist = AtomTable::nil;

  name_term_vars(object1, varlist, true, true);

  object2 = varlist;

  return(RV_SUCCESS);
}
//
// psi_name_vars(term)
// Name all unnamed (ob)vars in term.
// mode(in)
//
Thread::ReturnValue
Thread::psi_name_vars(Object *& object1)
{
  Object* varlist = AtomTable::nil;

  name_term_vars(object1, varlist, true, false);

  return(RV_SUCCESS);
}





