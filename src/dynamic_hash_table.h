// dynamic_hash_table.h - A hash table template.
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
// $Id: dynamic_hash_table.h,v 1.2 2001/11/21 00:21:13 qp Exp $    
//

#ifndef DYNAMIC_HASH_TABLE_H
#define DYNAMIC_HASH_TABLE_H


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
			       cerr << "Out of bounds " << loc << endl;
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

#endif	// DYNAMIC_HASH_TABLE_H

