// pred_table.h - The predicate table is a hash table providing the link
//		  between the predicate name and its code.  Each entry is
//		  hashed on the predicate name and its arity.  Rather using
//		  the string of the predicate name, the atom is used.
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
// $Id: pred_table.cc,v 1.4 2002/12/05 03:39:32 qp Exp $

#include "area_offsets.h"
#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "global.h"
#include "hash_table.h"
#include "pred_table.h"

//
// Constructor:
//	Initialise the table with escape functions.
//
PredTab::PredTab(AtomTable* atoms, word32 TableSize) :
  HashTable <PredEntry, PredEntry> (TableSize)
{
#define DefEscape(escape, arity, fn)	\
	insertEscape((escape), (arity), atoms)
#include "escapes.h"
#undef DefEscape
}

//
// Add a new entry to the predicate table.
//
PredLoc
PredTab::add(AtomTable* atoms,
	     Atom* PredName, const word32 arity, const PredCode code,
	     Code* codePtr)
{
  PredEntry	input;
  input.assign(PredName, arity, code, atoms);
  const PredLoc	index = search(input);
  PredEntry& entry = getEntry(index);
  if (! entry.isEmpty())
    {
      //
      // Redefined the predicate.
      //
      ostringstream os;
      os << "new definition for " << PredName->getName() 
	 << "/" << arity << " is ignored";
      Warning(__FUNCTION__, os.str().c_str()); 
      return(index);
    }
  
  //
  // Add/overwrite with the new entry.
  //
  entry.assign(PredName, arity, code, atoms);
  
  //
  // Return the location of string in the atom table.
  // 
  return(index);
}

//
// Reset the code location (Entry point) to NULL.
// This is used by the buffer code and is a spin-off from sbprolog.
//
void
PredTab::resetEp(Atom* PredName, const word32 arity, AtomTable* atoms, 
		 Code* code)
{
  PredCode        pred;
  pred.makePredicate(PredCode::STATIC_PRED, NULL, code);
  
  PredEntry       input;
  input.assign(PredName, arity, pred, atoms);
  
  const PredLoc index = search(input);
  PredEntry& entry = getEntry(index);
  
  //
  // Overwrite with NULL 
  //
  entry.assign(NULL, 0, pred, atoms);
}

//
// Link an escape function with its name.
//
void
PredTab::linkEscape(AtomTable* atoms, 
		    const char *name, const word32 arity, const EscFn f)
{
  PredCode        escape;
  PredLoc		index;
  
  escape.makeEscape(f);
  index = lookUp(atoms->getAtom(atoms->lookUp(name)), arity, atoms, code);
  if (index == EMPTY_LOC)
    {
      ostringstream os;
      os << "escape function " << name << 
	"/" << arity << " is not installed";
      Warning(__FUNCTION__, os.str().c_str());
    }
  else
    {
      getCode(index) = escape;
    }
}







