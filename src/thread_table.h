// thread_table.h -
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
// $Id: thread_table.h,v 1.3 2001/02/22 21:47:00 qp Exp $

#ifndef	THREAD_TABLE_H
#define	THREAD_TABLE_H

#include <sys/types.h>

#include "cond_list.h"
#include "defs.h"
#include "hash_qp.h"
#include "hash_table.h"
#include "string_qp.h"
#include "thread_table_loc.h"

class Thread;

class ThreadTable
{
  //
  // Hash table for associating thread names with thread id's.
  //

  class HashTableEntry
    {
    private:
      bool empty;		// Is the entry empty?
      ThreadTableLoc loc;	// Location of thread.
      String *symbol;		// The symbol.
    public:
      HashTableEntry(void) : empty(true) { }
      
      bool isEmpty(void) const { return empty; }
      
      ThreadTableLoc Loc(void) const
      {
	DEBUG_ASSERT(! empty);
	return loc;
      }
      String& Symbol(void)
      {
	DEBUG_ASSERT(! empty);
	return *symbol;
      }
      const String& InspectSymbol(void) const
      {
	DEBUG_ASSERT(! empty);
	return *symbol;
      }

      void Clear(void)
      {
	empty = true;
	delete symbol;
	symbol = NULL;
      }
      
      void Assign(const ThreadTableLoc l,
		  const String& s)
      {
	empty = false;
	loc = l;
	symbol = new String(s);
	if (symbol == NULL)
	  {
	    OutOfMemory(__FUNCTION__);
	  }
      }

      bool operator==(const HashTableEntry& tte) const
	{
	  return Loc() == tte.Loc() &&
	    InspectSymbol() == tte.InspectSymbol();
	}
    };

  class HashTableKey
    {
    private:
      const String symbol;
    public:
      HashTableKey(const String& s) : symbol(s) { }
      
      const String& InspectSymbol(void) const
	{
	  return symbol;
	}

      bool operator==(const HashTableEntry& t) const
      {
	if (t.isEmpty())
	{
	  return false;
	}
	else
	{
	  return InspectSymbol() == t.InspectSymbol();
	}
      }

      word32 hashFn(void) const
      {
	return Hash(symbol.Str(), symbol.Length());
      }
    };

  class ThreadTableHashTable : public HashTable<HashTableEntry, HashTableKey>
  {
  public:
    ThreadTableHashTable(const word32 size) :
      HashTable<HashTableEntry, HashTableKey>(size) 
      { }
    
    ThreadTableLoc Search(const HashTableKey key) const
      {
	return search(key);
      }

    HashTableEntry& GetEntry(const ThreadTableLoc loc)
      {
	return getEntry(loc);
      }

    const HashTableEntry& InspectEntry(const ThreadTableLoc loc) const
      {
	return inspectEntry(loc);
      }

    const char *getAreaName(void) const { return "Thread Table"; }

    word32 hashFunction(const HashTableKey key) const
      {
	return key.hashFn();
      }
  };

private:
  // Hash table from name to thread id.
  ThreadTableHashTable hash_table;
  
  // Array from thread id to thread.
  Thread **array;
  
  // Number of live threads.
  word32 live;
  
  // Next thread id.
  word32 next_id;

  // Size of the hash table and the array.
  const word32 size;

  // Buffer for constructing names of threads
  char name_buff[ATOM_LENGTH];
  
public:
  ThreadTable(const word32 TableSize = THREAD_TABLE_SIZE)
    : hash_table(TableSize),
      live(0),
      next_id(0),
      size(TableSize)
    {
      array = new (Thread *)[size];
      if (array == NULL)
	{
	  OutOfMemory(__FUNCTION__);
	}
      
      for (size_t i = 0; i < size; i++)
	{
	  array[i] = NULL;
	}
    }

  //
  // Operations on the thread name->thread id hash table.
  // A thread must have a slot in the thread array before these
  // operations can have meaning.
  //

  // Create a name of the form threadN for the given thread
  char* MakeName(const ThreadTableLoc loc);

  // Add a thread's name.
  bool AddName(const String&,		// Name of thread
	       const ThreadTableLoc);	// Thread id

  // Lookup a thread given its name. Returns (ThreadTableLoc) -1 when
  // the name can't be found.
  ThreadTableLoc LookupName(const String&) const;

  // Remove a thread's name.
  void RemoveName(const String&);

  //
  // Operations on the thread id array.
  //
  
  bool IsValid(const ThreadTableLoc loc) const
    {
      return loc < size;
    }
  
  // Return the size of the hash table.
  word32 Size(void) const { return size; }

  // Reserve a slot in the thread id array for the thread.
  ThreadTableLoc AddID(Thread *);

  // Look up the thread.
  Thread *LookupID(const ThreadTableLoc);

  const Thread *operator[](const ThreadTableLoc) const;

  // Remove the thread.
  void RemoveID(const ThreadTableLoc);

  size_t Live(void) const { return live; }
  void IncLive(void) { live++; }
  void DecLive(void) { live--; }
};

// Print out some information about a thread table in
// a form that can be read by a person.
extern ostream& operator<<(ostream& ostrm, ThreadTable&);

#endif	// THREAD_TABLE_H







