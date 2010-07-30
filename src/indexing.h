// indexing.h - Compiled indexing tables for predicates.
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
// $Id: indexing.h,v 1.7 2006/01/31 23:17:50 qp Exp $

#ifndef INDEXING_H
#define INDEXING_H

#include "area_offsets.h"
#include "atom_table.h"
#include "objects.h"
#include "code.h"
#include "code_hash.h"
#include "defs.h"
#include "string_map.h"

//
// The value stored in atomic when the entry is empty.
//
const wordptr EMPTY_ENTRY = WORDPTR_MAX;


//
// A record for constant table.
//
class ConstEntry
{

private:

  wordptr atomic;
  word8 type;
  word16 offset;

public:
  ConstEntry(void) { }

  ConstEntry(const wordptr constant, const word16 t) 
    : atomic(constant), type(static_cast<word8>(t)) { }

  //
  // Location of the offset and the size of each entry in the hash
  // table in the code area.
  //
  static const word32 OFFSET_LOCATION = 
        Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER;
  static const word32 SIZE = OFFSET_LOCATION + Code::SIZE_OF_OFFSET;
  static const word16 EMPTY = 0;
  static const word16 INTEGER_TYPE = 1;
  static const word16 ATOM_TYPE = 2;
  
  //
  // Check whether the entry is empty or not.
  //
  bool isEmpty(void) const { return(type == EMPTY); }

  bool isAtom(void) const { return(type == ATOM_TYPE); }
  
  //
  // Compare two entries.
  //
  bool operator==(const ConstEntry& entry) const
    {
      return ((type == entry.type) && (atomic == entry.atomic));
    }
  
  //
  // Hash on the constant.
  //
  wordptr hashFn(void) const 
    { 
      return atomic;
    }
  
  //
  // Store the data in the hash table in the code area.
  //
  void store(Code& code, const CodeLoc loc) const
    {
      updateAddress(loc, atomic);
      updateNumber(loc + Code::SIZE_OF_CONSTANT, type);
      updateOffset(loc + Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER, offset);
    }
  
  //
  // Load the data from the hash table in the code area.
  //
  void load(Code& code, CodeLoc& loc)
    {
      atomic = getAddress(loc);
      type = getNumber(loc);
      offset = getOffset(loc);
    }

  //
  // change constant pointer to tagged offset
  //
  void pointerToOffset(AtomTable& atoms)
    {
      assert(type == ATOM_TYPE);
      AtomLoc loc = atoms.getOffset(reinterpret_cast<Atom*>(atomic));
      atomic = static_cast<wordptr>(loc);
    }

  //
  // change tagged offset to constant pointer
  //
  void offsetToPointer(AtomTable& atoms)
    {
      assert(type == ATOM_TYPE);
      atomic = reinterpret_cast<wordptr>(atoms.getAddress(atomic));
    }


  
  //
  // Convert to new offset if it is a constant.
  //
  void relocate(const StringMap& string_map, const StringMapLoc string_base)
    {
      if (type == ATOM_TYPE)
	{
	  atomic = reinterpret_cast<wordptr>(string_map.convert(string_base, 
                                                                atomic));
	}
    }
  
  //
  // Initialise the record.
  //
  void assign(const wordptr constant, const word16 t) 
    { 
      atomic = constant; 
      type = static_cast<word8>(t);
    }
};

//
// Constant table for SWITCH_ON_CONSTANT.
//
class ConstantTable : public CodeHashTable <ConstEntry>
{
  
private:
  
  wordptr hashFunction(const ConstEntry entry) const
    { return(entry.hashFn()); }

public:
  
  ConstantTable(Code& area, const CodeLoc start, const word32 TabSize) : 
    CodeHashTable <ConstEntry> (area, start, TabSize)
    {}

    virtual ~ConstantTable() {}
};



//
// A record for structure table.
//
class StructEntry
{
  
private:
  
  wordptr atomic;
  word32 arity;
  word32 offset;
  
public:
  StructEntry(void) { }
  StructEntry(const wordptr structure, const word32 a) :
    atomic(structure), arity(a)
    { }
  
  //
  // Location of the offset and the size of each entry in the hash
  // table in the code area.
  //
  static const word32 OFFSET_LOCATION = Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER;
  static const word32 SIZE = OFFSET_LOCATION + Code::SIZE_OF_OFFSET;
  
  //
  // Check whether the entry is empty or not.
  //
  bool isEmpty(void) const { return(atomic == EMPTY_ENTRY); }
  
  //
  // Compare two entries.
  //
  bool operator==(const StructEntry& entry) const
    {
      return ((arity == entry.arity) && (atomic == entry.atomic));
    }
  
  
  //
  // Hash on the constant.
  //
  wordptr hashFn(void) const
    {
      return((atomic) ^ arity); 
    }
  
  //
  // Store the data in the hash table in the code area.
  //
  void store(Code& code, const CodeLoc loc) const
    {
      updateAddress(loc, atomic);
      updateNumber(loc + Code::SIZE_OF_CONSTANT,
		   (word8) arity);
      updateOffset(loc + Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER,
		   (word16) offset);
    }

  //
  // Load the data from the hash table in the code area.
  //
  void load(Code& code, CodeLoc& loc)
  {
    atomic = getAddress(loc);
    arity = getNumber(loc);
    offset = getOffset(loc);
  }
 
  //
  // Convert to new offset if it is a constant.
  //
  void relocate(const StringMap& string_map, const StringMapLoc string_base)
  {
    atomic = reinterpret_cast<wordptr>(string_map.convert(string_base, atomic));
  }

  //
  // Initialise the record.
  //
  void assign(const wordptr constant, const word32 n)
  {
    atomic = constant;
    arity = n;
  }
  //
  // change constant pointer to tagged offset
  //
  void pointerToOffset(AtomTable& atoms)
    {
      assert(reinterpret_cast<Object*>(atomic)->isAtom());
      AtomLoc loc = atoms.getOffset(reinterpret_cast<Atom*>(atomic));
      atomic = static_cast<word32>(loc);
    }

  //
  // change tagged offset to constant pointer
  //
  void offsetToPointer(AtomTable& atoms)
    {
      atomic = reinterpret_cast<wordptr>(atoms.getAddress(atomic));
    }
};

//
// Structure table for SWITCH_ON_STRUCTURE, and SWITCH_ON_QUANTIFIER.
//
class StructureTable : public CodeHashTable <StructEntry>
{

private:

  wordptr hashFunction(const StructEntry entry) const
  { return(entry.hashFn()); }

public:

  StructureTable(Code& area, const CodeLoc start, const word32 TabSize) : 
    CodeHashTable <StructEntry> (area, start, TabSize)
  {}
};

#endif // INDEXING_H














