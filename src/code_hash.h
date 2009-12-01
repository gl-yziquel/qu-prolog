// code_hash.h - Compiled hash tables for SWITCH_ON instructions.
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
// $Id: code_hash.h,v 1.4 2006/01/31 23:17:49 qp Exp $

#ifndef	CODE_HASH_H
#define	CODE_HASH_H

#include "area_offsets.h"
#include "code.h"
#include "defs.h"


//
// Generic compiled hash table.
// The size of the table must be a power of 2 in order to obtain the best
// performance.
//
template <class HashEntry>
class	CodeHashTable
{
  
private:
  
  Code& code;		// Code area.
  CodeLoc base;		// Base of the table.
  word32 tableSize;	// Size of the table.
  word32 tableSizeMask;	// Size of the table - 1.
  
  //
  // Convert a hash index to an address.
  //
  CodeLoc		offsetToAddr(const word32 index) const
    { return(base + index * HashEntry::SIZE); }
  
protected:
  
  //
  // Initial hashing calculation.
  //
  virtual	wordptr		hashFunction(const HashEntry entry) const = 0;
  
  //
  // Search for the entry in the hash table.
  //
  word32		search(const HashEntry entry) const;
  
public:
  
  //
  // Size of the hash table.
  //
  word32  	size(void) const	{ return(tableSize); }
  
  //
  // Add a new entry into the table.
  // 
  void		add(HashEntry entry)
    { entry.store(code, offsetToAddr(search(entry))); }
  
  //
  // Look up for an existing entry and return the offset (the label
  // where to jump to).
  //
  word32		lookUp(const HashEntry existing) const
    {
      CodeLoc		OffsetLoc;
      
      OffsetLoc = offsetToAddr(search(existing)) + HashEntry::OFFSET_LOCATION;
      return(getOffset(OffsetLoc));
    }
  
  CodeHashTable(Code& area, const CodeLoc start, const word32 TabSize)
    : code(area),
      base(start),
      tableSize(TabSize),
      tableSizeMask(tableSize - 1)
    { }

    virtual ~CodeHashTable() {}
};


//
// Search for the entry in the hash table.
//
template <class HashEntry>
word32
CodeHashTable<HashEntry>::search(const HashEntry entry) const
{
  word32		hash, increment;
  HashEntry	current;
  CodeLoc		cptr;
  
  hash = hashFunction(entry) & tableSizeMask;
  increment = 1;
  while (true)
    {
      cptr = offsetToAddr(hash);
      current.load(code, cptr);
      if (current.isEmpty() || current == entry)
	{
	  return(hash);
	}
      else if (increment ==  tableSize)
	{
	  //
	  // The table has been cycled through.
	  //
	  OutOfHashTable(__FUNCTION__,
			 "code hash table", tableSize);
	}
      else
	{
	  hash = (hash + increment) & tableSizeMask;
	  increment ++;
	}
    }
}

#endif	// CODE_HASH_H
