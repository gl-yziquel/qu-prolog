// atoms.cc - Predicates maniuplate atoms.
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
// $Id: atoms.cc,v 1.4 2002/11/03 08:37:23 qp Exp $

#include <string.h>
#include <sstream>

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// psi_atom_length(atom, variable)
// Work out the string length of an atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_atom_length(Object *& object1, Object *& object2)
{
  Object * val1 = object1;
  
  val1 = heap.dereference(val1);
  
  if (val1->isAtom())
    {
      object2 = heap.newShort(strlen(atoms->getAtomString(val1)));
      return(RV_SUCCESS);
    }
  else if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
// psi_atom_concat2(atomic, atomic, atomic)
// Join the first 2 atomics to get the third.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_atom_concat2(Object *& object1, Object *& object2, 
			 Object *& object3)
{
  ostringstream	strm;

  Object* a1 = heap.dereference(object1);
  Object* a2 = heap.dereference(object2);

  if (a1->isAtom())
    {
      strm << atoms->getAtomString(a1);
    }
  else if (a1->isNumber())
    {
      strm << a1->getNumber();
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (a2->isAtom())
    {
      strm << atoms->getAtomString(a2);
    }
  else if (a2->isNumber())
    {
      strm << a2->getNumber();
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  strm << ends;
    
  object3 = atoms->add(strm.str().data());
  return(RV_SUCCESS);
}

//
// psi_concat_atom(list of atomic, variable)
// Join a list of atomic together to form a new atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_concat_atom(Object *& object1, Object *& object2)
{
  ostringstream	strm;
 
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  while (pval1.getTerm()->isCons() && strm.good())
    {
      Cons* clist = OBJECT_CAST(Cons*, pval1.getTerm());
      Object* head = heap.dereference(clist->getHead());

      if (head->isAtom())
	{
	  strm << atoms->getAtomString(head);
	}
      else if (head->isNumber())
	{
	  strm << head->getNumber();
	}
      else if (head->isSubstitution())
	{
	  PrologValue pvhead(pval1.getSubstitutionBlockList(), head);
	  heap.prologValueDereference(pvhead);
	  head = pvhead.getTerm();
	  if (head->isAtom())
	    {
	      strm << atoms->getAtomString(head);
	    }
	  else if (head->isNumber())
	    {
	      strm << head->getNumber();
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 1);
	    }
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      pval1.setTerm(clist->getTail());
      heap.prologValueDereference(pval1);
    }
  
  if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }

  if (! pval1.getTerm()->isNil())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  strm << ends;
  
  object2 = atoms->add(strm.str().data());
  return(RV_SUCCESS);
}

//
// psi_concat_atom3(list of atomic, separator, ariable)
// Join a list of atomic together to form a new atom separating
// each atom with separator
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_concat_atom3(Object *& object1, Object *& object2,
			 Object *& object3)
{
  ostringstream	strm;
  ostringstream	strm1;
  bool		firstatom = true;
  Object* val2 = heap.dereference(object2);
  
  if (val2->isAtom())
    {
      strm1 << atoms->getAtomString(val2);
    }
  else if (val2->isNumber())
    {
      strm1 << val2->getNumber();
    }
  else if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  while (pval1.getTerm()->isCons() && strm.good())
    {
      if (firstatom)
	{
	  firstatom = false;
	}
      else
	{
	  strm << strm1.str();
	}

      Cons* clist = OBJECT_CAST(Cons*, pval1.getTerm());
      Object* head = heap.dereference(clist->getHead());

      if (head->isAtom())
	{
	  strm << atoms->getAtomString(head);
	}
      else if (head->isNumber())
	{
	  strm << head->getNumber();
	}
      else if (head->isSubstitution())
	{
	  PrologValue pvhead(pval1.getSubstitutionBlockList(), head);
	  heap.prologValueDereference(pvhead);
	  head = pvhead.getTerm();
	  if (head->isAtom())
	    {
	      strm << atoms->getAtomString(head);
	    }
	  else if (head->isNumber())
	    {
	      strm << head->getNumber();
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 1);
	    }
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      pval1.setTerm(clist->getTail());
      heap.prologValueDereference(pval1);
     }

  if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if(! pval1.getTerm()->isNil())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  strm << ends;

  object3 = atoms->add(strm.str().data());

  return(RV_SUCCESS);
}

//
// psi_atom_search(atom1, start, atom2, variable)
// Return the location with atom1 where atom2 is located.
// mode(in,in,in,out)
//
Thread::ReturnValue
Thread::psi_atom_search(Object *& object1, Object *& object2, 
			Object *& object3, Object *& object4)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);
  
  if (val1->isAtom() && val2->isShort() && val3->isAtom())
    {
      const char *string1 = atoms->getAtomString(val1);
      const char *substring = strstr(string1 + val2->getNumber() - 1,
				     atoms->getAtomString(val3));
      if (substring == NULL)
	{
	  return(RV_FAIL);
	}
      else
	{
	  object4 = heap.newNumber(strlen(string1) - strlen(substring)+1);
	  return(RV_SUCCESS);
	}
    }
  else if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  else if (val3->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  else if (!val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  else if (!val2->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }
}

//
// psi_sub_atom(atom, start, length, variable)
// Return a new atom formed from the supplied atom.
// mode(in,in,in,out)
//
Thread::ReturnValue
Thread::psi_sub_atom(Object *& object1, Object *& object2, 
		     Object *& object3, Object *& object4)
{
  int32		length;

  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);  
  
  DEBUG_ASSERT(val1->isAtom());
  DEBUG_ASSERT(val2->isShort());
  DEBUG_ASSERT(val3->isShort());
  
  length = val3->getNumber();
  strncpy(atom_buf1,
	  atoms->getAtomString(val1) + val2->getNumber() - 1, 
	  length);
  atom_buf1[length] = '\0';
  object4 = atoms->add(atom_buf1);
  return(RV_SUCCESS);
}




