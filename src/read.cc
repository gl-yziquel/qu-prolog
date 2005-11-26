// read.cc - Different specialised version of read for variables.
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
// $Id: read.cc,v 1.3 2005/11/26 23:34:30 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// psi_readR_var(variable, name)
// Return the variable associated with the name.  Otherwise, associate the
// given variable with the name.  No association is made for any name starting
// with '_'.
// mode(out,in)
//
Thread::ReturnValue
Thread::psi_readR_var(Object *& object1, Object *& object2)
{
  Object* val2 = heap.dereference(object2);

  assert(val2->isAtom());
  
  if (*(atoms->getAtomString(val2)) == '_')
    {
      //
      // Do not generate a name.
      //
      object1 =  heap.newVariable();
      return(RV_SUCCESS);
    }

  //
  // Obtain existing variable associates with the name.
  //
  Atom* a = OBJECT_CAST(Atom*, val2);
  Object* v = names.getVariable(a);
  if (v != NULL)
    {
      //
      // Use the existing variable.
      //
      object1 = v;
    }
  else
    {
      //
      // Associated the given variable with the name.
      //
      
      object1 = heap.newVariable(true);
      names.setNameNewVar(a, object1, *this);
    }
  return(RV_SUCCESS);
}

//
// psi_readR_object_variable(variable, name)
// Return the object variable associated with the name.  If none exists,
// create a new object variable and establish the association before returning
// the object variable.  No association is made for any name starting with '_'.
// mode(out,in)
//
Thread::ReturnValue
Thread::psi_readR_object_variable(Object *& object1, Object *& object2)
{
  Object* val2 = heap.dereference(object2);

  assert(val2->isAtom());
  
  //
  // Obtain existing variable associates with the name.
  //
  Object* object_variable = names.getVariable(OBJECT_CAST(Atom*, val2));
  
  if (object_variable == NULL)
    {
      object_variable = heap.newObjectVariable();
      if (*(atoms->getAtomString(val2)) != '_')
	{
	  names.setNameNewVar(OBJECT_CAST(Atom*, val2), 
			      object_variable, *this);
	}
    }
  
  //
  // Return the object variable.
  //
  object1 = object_variable;
  return(RV_SUCCESS);
}



