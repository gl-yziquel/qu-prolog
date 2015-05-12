// page_table.cc - Basic operations for a page table with a single page.
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: page_table.cc,v 1.9 2006/01/31 23:17:51 qp Exp $

#ifndef PAGE_TABLE_CC
#define PAGE_TABLE_CC

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "int.h"
#include "magic.h"
#include "page_table.h"

//
// Constructor:
//	Allocate the index table and initialise it NULL.  There is no need to
//	allocate the first page because it is handled by pushElement.
//
template <class StoredType>
PageTable<StoredType>::PageTable(word32 size)
{
  word32	FullSize;
  
  FullSize = size * K;
  index = new StoredType [FullSize];
  //
  // Initialise the page table.
  //
  allocatedSize = FullSize;
}

//
// Destructor:
//	Clean up the index table.
//
template <class StoredType>
PageTable<StoredType>::~PageTable(void)
{
  if (index != NULL)
    {
      delete [] index;		// Delete the index table.
    }
  
  allocatedSize = 0;
}

//
// Write the area bounded by "begin" and "end" to a stream.
//
template <class StoredType>
void
PageTable<StoredType>::saveArea(ostream& ostrm, const u_long magic,
				const PageLoc begin, const PageLoc end) const
{
  assert(end >= begin);

  const size_t size = end - begin;

  //
  // Write out the magic number.
  //
  IntSave<word32>(ostrm, magic);

  //
  // Write out the size (i.e. the number of entries of "StoredType").
  //
  IntSave<word32>(ostrm, static_cast<word32>(size));

  //
  // Write out the page.
  //
  ostrm.write((char*)(offsetToAddress(begin)), static_cast<std::streamsize>(size * sizeof(StoredType)));
  if (ostrm.fail())
    {
      SaveFailure(__FUNCTION__, "data segment", getAreaName());
    }
}

//
// Read the "ReadSize" entries of data from a stream into the memory starting
// at "start".
//
template <class StoredType>
void
PageTable<StoredType>::readData(istream& istrm, const char *AreaName,
				const word32 ReadSize, const PageLoc start)
{
  //
  // Read in a segment into the page.
  //
  allocateEntries(start + ReadSize);
#if defined(MACOSX)
    istrm.read((char*)offsetToAddress(start), ReadSize * sizeof(StoredType));
#else
  if (istrm.good() &&
      istrm.read((char*)offsetToAddress(start), ReadSize * sizeof(StoredType)).fail())
    {
      ReadFailure(__FUNCTION__, "data segment", AreaName);
    }
#endif //defined(MACOSX)
}

//
// Load the area from a stream.  "start" marks the start of the area in memory.
//
template <class StoredType>
void
PageTable<StoredType>::loadArea(istream& istrm, const PageLoc start)
{
  const word32 ReadSize = IntLoad<word32>(istrm);
  if (ReadSize > allocatedSize)
    {
      //
      // Wrong size.
      //
      FatalS(__FUNCTION__, "wrong size for ", getAreaName());
    }

  readData(istrm, getAreaName(), ReadSize, start);
}

#endif	// PAGE_TABLE_CC
