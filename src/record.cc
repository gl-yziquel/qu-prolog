// record.cc - A record style database.
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
// $Id: record.cc,v 1.2 2000/12/13 23:10:02 qp Exp $

#include <strstream.h>

#include "atom_table.h"
#include "record_ref_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern RecordDB *record_db;

//
// psi_record_get_first_ref(atom, ref)
//
// Finds the first reference associated with the atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_record_get_first_ref(Object *& object1, Object *& object2)
{
  StackLoc	loc;
  
  Object* val1 = heap.dereference(object1);
  
  DEBUG_ASSERT(val1->isAtom());
  
  loc = OBJECT_CAST(Atom*, val1)->getFirstRef();
  
  while (loc != EMPTY_LOC && record_db->getErased(loc)) 
    {
      loc = record_db->getNext(loc);
    }
  
  if (loc == EMPTY_LOC || record_db->getErased(loc)) 
    {
      return RV_FAIL;
    } 
  else 
    {
      object2 = heap.newNumber(loc);
      return RV_SUCCESS;
    }
}

//
// psi_record_get_next_ref(ref, next)
//
// Looks up the next reference in the atom's association chain.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_record_get_next_ref(Object *& object1, Object *& object2)
{
  StackLoc	loc;
  
  Object* val1 = heap.dereference(object1);
  DEBUG_ASSERT(val1->isNumber());
  
  loc = val1->getNumber();
  
  if (loc == EMPTY_LOC || loc > record_db->getTop()) 
    {
      return RV_FAIL;
    }

  // Find the next ref
  loc = record_db->getNext(loc);
  
  while (loc != EMPTY_LOC && record_db->getErased(loc)) 
    {
      loc = record_db->getNext(loc);
    }
  
  if (loc == EMPTY_LOC || record_db->getErased(loc)) 
    {
      return RV_FAIL;
    } 
  else 
    {
      object2 = heap.newNumber(loc);
      return RV_SUCCESS;
    }
}

//
// psi_record_get_last_ref(atom, ref)
//
// Finds the last reference associated with the atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_record_get_last_ref(Object *& object1, Object *& object2)
{
  StackLoc	loc;

  Object* val1 = heap.dereference(object1);

  DEBUG_ASSERT(val1->isAtom());
  
  loc = OBJECT_CAST(Atom*, val1)->getLastRef();
  
  while (loc != EMPTY_LOC && record_db->getErased(loc)) 
    {
      loc = record_db->getPrev(loc);
    }
  
  if (loc == EMPTY_LOC || record_db->getErased(loc)) 
    {
      return(RV_FAIL);
    } 
  else 
    {
      object2 = heap.newNumber(loc);
      return(RV_SUCCESS);
    }
}

//
// psi_record_get_term(ref, string)
//
// Return the atom pointed to by the reference.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_record_get_term(Object *& object1, Object *& object2)
{
  StackLoc	loc;

  Object* val1 = heap.dereference(object1);
  
  DEBUG_ASSERT(val1->isNumber());
  
  loc = val1->getNumber();
  
  if (loc > record_db->getTop() || record_db->getErased(loc)) 
    {
      return(RV_FAIL);
    } 
  else 
    {
      Object* object_variablenames;

      istrstream *istrm = 
	new istrstream(record_db->getString(loc), record_db->getLength(loc));
      if (istrm == NULL)
	{
	  OutOfMemory(__FUNCTION__);
	}
      Stream stream(istrm);

      EncodeRead er(*this,
		    heap,
		    stream,
		    object2,
		    *atoms,
		    false,
		    names,
		    object_variablenames);
      
      return BOOL_TO_RV(er.Success());
    }
}

//
// psi_record_record_first(atom, term, ref)
//
// Records the term in the first place associated with the atom.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_record_record_first(Object *& object1,
				Object *& object2,
				Object *& object3)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  DEBUG_ASSERT(val1->isAtom());

  // XXX Deleted on destruction of stream
  ostrstream *ostrm = new ostrstream(atom_buf1, ATOM_LENGTH, 0);
  if (ostrm == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  if (ostrm->bad())
    {
      delete ostrm;
      PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 0);
    }

  Stream stream(ostrm);

  EncodeWrite ew(*this, heap, stream, val2, *atoms, false, names);
  if (ew.Success())
    {
      const StackLoc first = OBJECT_CAST(Atom*, val1)->getFirstRef();

      const StackLoc loc = record_db->add(EMPTY_LOC, first,
					 ostrm->str(), ostrm->pcount());
      
      OBJECT_CAST(Atom*, val1) ->setFirstRef(loc);
      if (first == EMPTY_LOC) 
	{
	 OBJECT_CAST(Atom*, val1) ->setLastRef(loc);
	} 
      else 
	{
	  record_db->setPrev(first, loc);
	}
      
      // Return the stack reference
      object3 = heap.newNumber(loc);

      ostrm->freeze(0);

      return(RV_SUCCESS);
    } 
  else 
    {
      ostrm->freeze(0);

      return(RV_FAIL);
    }
}

//
// psi_record_record_last(atom, term, ref)
//
// Records the term in the last place associated with the atom.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_record_record_last(Object *& object1, Object *& object2, Object *& object3)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  DEBUG_ASSERT(val1->isAtom());
  
  // XXX Deleted on destruction of stream
  ostrstream *ostrm = new ostrstream(atom_buf1, ATOM_LENGTH, 0);
  if (ostrm == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  if (ostrm->bad())
    {
      delete ostrm;
      PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 0);
    }

  Stream stream(ostrm);

  EncodeWrite ew(*this, heap, stream, val2, *atoms, false, names);
  if (ew.Success())
    {
      const StackLoc last = OBJECT_CAST(Atom*, val1)->getLastRef();
      const StackLoc loc = record_db->add(last, EMPTY_LOC,
				   ostrm->str(), ostrm->pcount());
      
      OBJECT_CAST(Atom*, val1)->setLastRef(loc);
      if (last == EMPTY_LOC) 
	{
	   OBJECT_CAST(Atom*, val1)->setFirstRef(loc);
	} 
      else 
	{
	  record_db->setNext(last, loc);
	}
      
      // Return the reference
      object3 = heap.newNumber(loc);

      ostrm->freeze(0);

      return(RV_SUCCESS);
    } 
  else 
    {
      ostrm->freeze(0);

      return(RV_FAIL);
    }
}

//
// psi_erase(ref)
//
// Erase the reference pointed to by ref.
// mode(in)
//
Thread::ReturnValue
Thread::psi_erase(Object *& object1)
{
  Object* val1 = heap.dereference(object1);
  
  DEBUG_ASSERT(val1->isNumber());
  
  const StackLoc loc = val1->getNumber();
  
  if (loc > record_db->getTop() || record_db->getErased(loc)) 
    {
      return(RV_FAIL);
    } 
  else 
    {
      record_db->setErased(loc, true);
      return(RV_SUCCESS);
    }
}








