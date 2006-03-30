// dynamic_hash_table.h - A hash table template.
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
// $Id: dynamic_hash_table.h,v 1.6 2006/01/31 23:17:50 qp Exp $    
//

#ifndef DYNAMIC_HASH_TABLE_H
#define DYNAMIC_HASH_TABLE_H

#include <stdlib.h>

//
// HashType is the data type stored in the hash table.
// The size of the table must be a power of 2.
//
template <class HashType>
class	DynamicHashTable 
{

private:

	int		tableSize;	// Size of the hash table.
	int		tableSizeMask;	// Size of the hash table - 1.
	int             used;           // Number of used entries.
	HashType	*table;		// The table itself.
        int 		iter_pos;       // iterator position


	//
	// Round up to (the next power of 2)*2.
	//
	int		next_2power(int n) const
			{
				int power = 2;
				n--;
				while (n > 0)
				{
					n >>= 1;
					power <<= 1;
				}
				return(power);
			}

protected:

	//
	// The initial hashing calculation.
	// 
virtual	int		hashFunction(const HashType entry) const = 0;

public:
	//
	// Search through the hash table.  
	// If the entry is found then the position is returned else -1.
	// It requires overloaded operator == for HashType for comparison.
	//
	int		search(const HashType item) const;

	//
	// Insert entry in table.  
	// The table is resized if it becomes more than half full.
	// Returns true if entry exists. Also returns in hashValue the
        // index.
	//
	bool		insert(const HashType item, int& hashValue);

	//
	// Remove entry from table.  
	// Returns 1 if found otherwise 0.
	//
	int		remove(const int position);


	//
	// Resize the table
	//
	void		resize(const int newsize);

        //
        // Given a location, return the entry in the table.
        //
        HashType&       getEntry(const int loc) const
                        { 
			   if ((loc < 0) || (loc >= tableSize))
			   {
			     // cerr << "Out of bounds " << loc << endl;
			     abort();
			   }
			   return(table[loc]); 
			}

	//
	// Return the amount of table in use.
	//
	int		sizeOfTable(void)	const   { return(used); }

	//
	// Return the size of the table.
	//
	int		allocatedSize(void)	const	{ return(tableSize); }

	//
	// Reset iterator
	//
        void 		iter_reset(void)		{ iter_pos = 0; }

	//
	// Position of next entry for iterator
	//
	int		iter_next(void);      



	DynamicHashTable(int TabSize);
virtual	~DynamicHashTable(void);
};


//
// Constructor:
//	Allocate the hash table.
//
template <class HashType>
DynamicHashTable<HashType>::DynamicHashTable(int TabSize)
{
  tableSize = next_2power(TabSize);
  table = new HashType[tableSize];
  tableSizeMask = tableSize-1;
  used = 0;
}

//
// Destructor:
//	Clean up the table.
//
template <class HashType>
DynamicHashTable<HashType>::~DynamicHashTable(void)
{
  delete [] table;
}

//
// Search through the hash table.  
// If the entry is found then the position is returned else -1.
//
template <class HashType>
int
DynamicHashTable<HashType>::search(const HashType item) const
{
  int	hashValue, increment;
  HashType* entry;
  
  for (hashValue = hashFunction(item) & tableSizeMask, 
	 increment = 1, entry = &table[hashValue];
       ! entry->isEmpty(); )
    {
      if (!entry->isRemoved() && (item == *entry))
	{
	  return(hashValue);
	}
      else if (increment  == tableSize)
	{
	  return(-1);
	}
      hashValue = (hashValue + increment++) & tableSizeMask;
      entry = &table[hashValue];
    }
  //
  // No matching entry is found.  
  //
  return(-1);
}

//
// Insert entry in table.  
// The table is resized if it becomes more than half full.
// Returns 1 if already there otherwise 0.
//
template <class HashType>
bool
DynamicHashTable<HashType>::insert(const HashType item, int &hashValue)
{
  int	increment;
  HashType* entry;
  
  for (hashValue = hashFunction(item) & tableSizeMask, 
	 increment = 1, entry = &table[hashValue];
       ! (entry->isEmpty() || entry->isRemoved()); )
    {
      if (item == *entry)
	{
	  return(true);
	}
      else if (increment  == tableSize)
	{
	  // cerr << "Table cycled through" << endl;
	  abort();
	}
      hashValue = (hashValue + increment++) & tableSizeMask;
      entry = &table[hashValue];
    }
  //
  // Empty or removed slot found.   
  //
  if ((used << 1) > tableSize)
    {
      // Check if there is a removed slot
      bool is_removed = false;
      for (int i = 0; i < tableSize; i++)
	{
	  if (!table[i].isEmpty() && table[i].isRemoved())
	    {
	      is_removed = true;
	      break;
	    }
	}
      int newTableSize;
      if (is_removed)
	{
	  newTableSize = tableSize;
	}
      else
	{
	  newTableSize = next_2power(tableSize);
	}
      resize(newTableSize);
      insert(item, hashValue);
    }
  else
    {
      used++;
      table[hashValue] = item;
    }
  assert(hashValue == search(item));
  return(false);
}

//
// Remove entry from table.  
// Returns 1 if found -1 if out of range otherwise 0.
//
template <class HashType>
int
DynamicHashTable<HashType>::remove(const int position) 
{
  if ((position < 0) || (position >= tableSize))
    {
      return(-1);
    }
  if (table[position].isEmpty() || table[position].isRemoved())
    {
      return(0);
    }
  used--;
  table[position].makeRemoved();
  return(1);
}

//
// Resize the table
//
template <class HashType>
void
DynamicHashTable<HashType>::resize(const int newsize) 
{
  HashType *oldtable = table;
  int oldtableSize = tableSize;
  
  tableSize = newsize;
  table = new HashType[tableSize]; 
  tableSizeMask = tableSize-1;
  used = 0;
  
  for (int j = 0; j < oldtableSize; j++)
    {
      if (!oldtable[j].isEmpty())
	{
	  if(oldtable[j].isRemoved())
	    {
	      oldtable[j].clearEntry();
	    }
	  else
	    {
	      int dummy;
	      insert(oldtable[j], dummy);
	    }
	}
    }  
  delete [] oldtable;
}

//
// Position of next entry for iterator
// Return -1 if none left.
//
template <class HashType>
int		
DynamicHashTable<HashType>::iter_next(void)      
{
  while (iter_pos < tableSize)
    {
      if (!table[iter_pos].isEmpty() 
	  && !table[iter_pos].isRemoved())
	{
	  return(iter_pos++);
	}
      iter_pos++;
    }
  return(-1);
}







#endif	// DYNAMIC_HASH_TABLE_H

