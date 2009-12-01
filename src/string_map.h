// string_map.h - Used for relocation of atoms and numbers during loading.
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
// $Id: string_map.h,v 1.3 2002/11/03 08:37:33 qp Exp $

#ifndef	STRING_MAP_H
#define	STRING_MAP_H

#include <iostream>

#include "area_offsets.h"
#include "atom_table.h"
#include "defs.h"
//#include "heap.h"
#include "stack_qp.h"

//
// Mapping the string offset given in qo files to the location in the atom
// table.  The string offsets in qo files refer the string number in the
// string table in the qo files.  i.e.  Offset 1 refers the first string,
// offset 2 refers to the second string, and so on.  There is no offset 0.
//
class	StringMap : public PrologStack <Atom*>
{

private:

virtual	const char *getAreaName(void) const { return("string map"); }

public:
  StringMap(word32 size, word32 boundary)
    : PrologStack <Atom*> (size, boundary) {}

  //
  // Return the current top of stack.
  //
  StringMapLoc	getTop(void) const	{ return(getTopOfStack()); }
  
  //
  // Read in the strings.
  // Return whether it is successful or not.
  //
  bool loadStrings(istream& istrm, const char *file, AtomTable& atoms);
  
  //
  // Convert an old offset to the new one.
  //
  Atom* convert(const StringMapLoc base, const  word32 old) const
  {
    return *inspectAddr(base + old);
  }
};

//
// The map for numbers.
//
class NumberMap : public PrologStack <Object*>
{

private:

  virtual const char *getAreaName(void) const { return("number map"); }

public:
NumberMap(word32 size, word32 boundary)
    : PrologStack <Object*> (size, boundary) {}

  //
  // Return the current top of stack.
  //
  NumberMapLoc	getTop(void) const	{ return(getTopOfStack()); }
  
  //
  // Read in the numbers.
  // Return whether it is successful or not.
  //
  bool loadNumbers(istream& istrm, Heap& number_heap);
  
  //
  // Convert an old offset to the new one.
  //
  Object* convert(const NumberMapLoc base, const  word32 old) const
  {
    return *inspectAddr(base + old);
  }
};

#endif	// STRING_MAP_H




