// string_table.h - The table holds the atoms in C++ string format.  That is,
//		    a sequence of characters terminated by '\0'.  The strings
//		    are stored in the table consecutively.
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
// $Id: string_table.h,v 1.3 2002/11/03 08:37:33 qp Exp $

#ifndef	STRING_TABLE_H
#define	STRING_TABLE_H

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "magic.h"
#include "qem_options.h"
#include "stack_qp.h"

//
// The stack holds '\0' terminating strings.
//	String Table 
//
//	|        |
//	+--------+
//	|   h    | 
//	+--------+
//	|   e    |
//	+--------+
//	|   l    |
//	+--------+
//	|   l    |
//	+--------+
//	|   o    |
//	+--------+
//	|   \0   |
//	+--------+
//	|        |
//


class	StringTab : public PrologStack <char>
{

private:
  
  //
  // Return the name of the area.
  //
  virtual	const char	*getAreaName(void) const
    { return("string table"); }
  
public:
  
  //
  // Allocate space for the table and install default strings.
  //
  StringTab(word32 size, word32 boundary) :
  PrologStack <char> (size, boundary)
    {}
  
  //
  // Retrieve the string from the table.
  // If StringLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  char *getString(const StringLoc loc)
    { return(fetchAddr(loc)); }

  const char *inspectString(const StringLoc loc) const
    { return(inspectAddr(loc)); }

  //
  // Add a new string to the table.
  //
  StringLoc	add(const char *string);
  
  //
  // Size of the string table.
  //
  word32	size(void) const	{ return(allocatedSize()); }
  
  //
  // Save the data.
  //
  void save(std::ostream& ostrm) const
    { saveStack(ostrm, STRING_TABLE_MAGIC_NUMBER); }

  //
  // Restore the data.
  //
  void load(std::istream& istrm)
    { loadStack(istrm); }

};

#endif	// STRING_TABLE_H
