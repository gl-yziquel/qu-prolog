// name_table.h - Definitions of the name table for storing variable names
// and the implicit parameter table for storing implicit parameters.
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: name_table.cc,v 1.4 2006/01/31 23:17:51 qp Exp $

#include "area_offsets.h"
#include "atom_table.h"
#include "objects.h"
//#include "heap.h"
#include "name_table.h"
#include "thread_qp.h"
#include "trail.h"

//
// Add a new entry or update an entry in the name table.
//
void
NameTable::set(NameEntry key, Thread& th)
{
  NameEntry&	entry = getEntry(search(key));
  Atom*&     	name = entry.getName();
  heapobject*   valuePtr = entry.getValueAddr();

  assert(entry.isEmpty());
      //
      // Add a new entry.
      //
  assert(! key.getValue()->isSubstitutionBlock());
  th.updateAndTrailObject(valuePtr, key.getValue(), 0);
  name = key.getName();
}

void
NameTable::setNameNewVar(Atom* index, Object* var, Thread& th)
{
  assert(var->isAnyVariable());
  setVariableName(index, var, th);
  OBJECT_CAST(Reference*, var)->setName(index);
}

void
NameTable::setNameOldVar(Atom* index, Object* var, Thread& th)
{
  assert(var->isAnyVariable());
  assert(OBJECT_CAST(Reference*, var)->hasExtraInfo());
  setVariableName(index, var, th);
  th.updateAndTrailObject(reinterpret_cast<heapobject*>(var), index, 
			  Reference::NameOffset);
}
  

//
// Add a new entry or update an entry in the IP table.
//
void
IPTable::set(IPEntry key, Thread& th)
{
  IPEntry&	entry = getEntry(search(key));
  
  assert(!key.getValue()->isSubstitutionBlock());
  if (entry.isEmpty())
    {
      //
      // Add a new entry.
      //
      th.updateAndTrailIP(entry.getNameAddress(), key.getName());
      th.updateAndTrailIP(entry.getValueAddr(), key.getValue());
    }
  else
    {
      //
      // Overwrite the value of an existing entry.
      //
      th.updateAndTrailIP(entry.getValueAddr(), key.getValue());
    }
}








