// hash_table.cc - Fundamental hash table arrangement.  Open addressing is
//		   used.  It requires overloaded operator == for comparison.
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
// $Id: hash_table.cc,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#include <iostream.h>
#include <time.h>

#include "hash_table.h"
#include "int.h"

//
// Constructor:
//	Allocate the hash table.
//
template <class HashType, class HashKey>
HashTable<HashType, HashKey>::HashTable(word32 TabSize)
{
  tableSize = next_2power(TabSize);
  table = new HashType[tableSize];
  if (table == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }
  else
    {
      tableSizeMask = tableSize-1;
    }
}

//
// Destructor:
//	Clean up the table.
//
template <class HashType, class HashKey>
HashTable<HashType, HashKey>::~HashTable(void)
{
  if (table != NULL)
    {
      delete [] table;
    }
}

//
// Hash into the table by the string.
//
template <class HashType, class HashKey>
HashLoc
HashTable<HashType, HashKey>::hashString(const char *string) const
{
  word32	value = 0;
  
  while (*string != '\0')
    {
      value = (value << 5) + value + *string++;
    }
  return(value);
}

//
// Search through the hash table.  Either it locates the matching entry or an
// empty location is found.  When one of these situations becomes true, the
// location of the entry is returned.
//
template <class HashType, class HashKey>
HashLoc
HashTable<HashType, HashKey>::search(const HashKey key) const
{
  HashLoc loc = hashFunction(key) & tableSizeMask;

  for (word32 increment = 1;
       ! inspectEntry(loc).isEmpty();
       loc = (loc + increment) & tableSizeMask, increment++)
    {
      if (key == inspectEntry(loc))
	{
	  return(loc);
	}
      else if (increment  == tableSize)
	{
	  //
	  // The table has been cycled through.
	  //
	  OutOfHashTable(__FUNCTION__, getAreaName(), tableSize);
	}
    }
  //
  // No matching entry is found.  Return this empty entry for possible
  // insertion.
  //
  return(loc);
}

//
// Return the size of the table in use.
//
template <class HashType, class HashKey>
word32
HashTable<HashType, HashKey>::sizeOfTable(void) const
{
  word32 size = 0, i;
  
  for (i = 0; i < allocatedSize(); i++)
    {
      if (! inspectEntry(i).isEmpty())
	{
	  size++;
	}
    }
  return(size);
}

//
// Write the table to a stream.
//
template <class HashType, class HashKey>
void
HashTable<HashType, HashKey>::saveTable(ostream& ostrm, const u_long magic) const
{
  IntSave<word32>(ostrm, magic);
  IntSave<word32>(ostrm, tableSize);

  // XXX Endian problem
  if (ostrm.good() &&
      ostrm.write(table, tableSize * sizeof(HashType)).fail())
    {
      SaveFailure(__FUNCTION__, "data", getAreaName());
    }
}

//
// Load the table from a stream.
//
template <class HashType, class HashKey>
void
HashTable<HashType, HashKey>::loadTable(istream& istrm)
{
  const word32	ReadSize = IntLoad<word32>(istrm);
  if (ReadSize != tableSize)
    {
      Fatal(__FUNCTION__, "wrong size for %s", (int32)(getAreaName()));
    }

  //
  // Read in the table.
  //
  // XXX Endian problem
  if (istrm.good() &&
      istrm.read(table, tableSize * sizeof(HashType)).fail())
    {
      ReadFailure(__FUNCTION__,
		  "data",
		  getAreaName());
    }
}
