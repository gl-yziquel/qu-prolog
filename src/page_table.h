// page_table.h - Basic operations for a page table with a singe page.
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
// $Id: page_table.h,v 1.3 2002/11/08 00:44:18 qp Exp $

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "errors.h"

template <class StoredType>
class	PageTable
{

private:

  StoredType	*index;			// Index table to the page.
  word32		allocatedSize;		// Allocated size.
  
  //
  // Allocate a new page to the index table if it is required.
  // OutOfPage is reported if the index table is run out; or
  //
  void		allocateEntries(const word32 EndLoc)
    {
      if (EndLoc > allocatedSize)
	{
	  OutOfPage(__FUNCTION__,
		    getAreaName(),
		    allocatedSize / K);
	}
    }
  
protected:
  
  //
  // Return the name of the table.
  //
  virtual	const char	*getAreaName(void) const = 0;
  
  //
  // Given an index of a word in the stack, get the address.
  //
  StoredType	*offsetToAddress(const PageLoc loc) const
    { return(index + loc); }
  
  //
  // Given an index of a word in the stack, return the item at that
  // location.
  //
  StoredType&	getItem(const PageLoc loc) const
    { return(index[loc]); }

  //
  // Allocate 'n' items of StoredType starting at the specified location.
  // OutOfPage is reported if the index table is run out; or
  //
  void		allocateItems(const PageLoc loc, const word32 n)
    {
      allocateEntries(loc + n);
    }
  
  //
  // Allocate a segment of 'n' items of StoredType within one page and
  // return a pointer to this space.  The segment may start at the given
  // location or the beginning of next page.
  // OutOfPage is reported if the index table is run out; or
  //
  PageLoc		allocateSegment(const PageLoc loc, const word32 n)
    {
      allocateEntries(loc + n);
      return(loc);
    }
  
  //
  // Return the size of the area allocated.
  //
  word32		areaSize(void) const
    { return(allocatedSize); }
  
  //
  // Write the area bounded by "begin" and "end" to a stream.
  //
  void		saveArea(std::ostream& ostrm, const u_long magic,
			 const PageLoc begin, const PageLoc end) const;
  
  //
  // Read the "ReadSize" entries of data from a stream into the memory
  // starting at "start".
  //
  void		readData(std::istream& istrm, const char *file,
			 const word32 ReadSize, const PageLoc start);
  
  //
  // Load the area from a stream.  "start" marks the start of the area
  // in memory.
  //
  void		loadArea(std::istream& istrm, const PageLoc start);
  
public:
  
  PageTable(word32 size);
  virtual	~PageTable(void);
};

#endif	// PAGE_TABLE_H
