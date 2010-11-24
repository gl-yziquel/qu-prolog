// thread_table.h -
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
// $Id: thread_table.h,v 1.11 2006/01/31 23:17:52 qp Exp $

#ifndef	THREAD_TABLE_H
#define	THREAD_TABLE_H

#include <sys/types.h>
#include <string>

#include "defs.h"
#include "hash_qp.h"
#include "dynamic_hash_table.h"
//#include "string_qp.h"
#include "thread_table_loc.h"

class Thread;

class ThreadHashTableEntry
{
 private:
  bool removed;		// Has the entry been removed?
  ThreadTableLoc loc;	// Location of thread.
  string *symbol;		// The symbol.
 public:
  ThreadHashTableEntry(void) : removed(false), loc(0), symbol(NULL) { }
  
  ThreadHashTableEntry(string* s) : removed(false), loc(0), symbol(s) { }
  
  
  bool isEmpty(void) const { return (symbol == NULL); }
  
  bool isRemoved(void) const { return removed; }

  void makeRemoved(void) { removed = true; }  

  ThreadTableLoc Loc(void) const
    {
      assert(! removed);
      return loc;
    }
  string& Symbol(void)
    {
      assert(! removed);
      assert(symbol != NULL);
      return *symbol;
    }
  const string& InspectSymbol(void) const
    {
      assert(! removed);
      assert(symbol != NULL);
      return *symbol;
    }
  
  void clearEntry(void)
    {
      removed = false;
      delete symbol;
      symbol = NULL;
    }
  
  void setSymbol(string* s)
    {
      symbol = s;
    }
  
  void Assign(const ThreadTableLoc l,
	      const string& s)
    {
      removed = false;
      loc = l;
      symbol = new string(s);
    }
  
  bool operator==(const ThreadHashTableEntry& tte) const
    {
      if (symbol == tte.symbol) return true;
      if ((symbol == NULL) || (tte.symbol == NULL)) return false;
      return (*symbol == (*tte.symbol));
    }
  
  int hashFn(void) const
    {
      assert(symbol != NULL);
      return Hash(symbol->c_str(), symbol->length());
    }
};

/*
  class HashTableKey
    {
    private:
      const string symbol;
    public:
      HashTableKey(const string& s) : symbol(s) { }
      
      const string& InspectSymbol(void) const
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
	return Hash(symbol.c_str(), symbol.length());
      }
    };
*/

class ThreadTableHashTable : public DynamicHashTable<ThreadHashTableEntry>
{
 public:
  explicit ThreadTableHashTable(const word32 size) :
    DynamicHashTable<ThreadHashTableEntry>(size) 
    { }
  
  const char *getAreaName(void) const { return "Thread Table"; }
  
  int hashFunction(const ThreadHashTableEntry key) const
    {
      return key.hashFn();
    }
};

class ThreadTable
{
  //
  // Hash table for associating thread names with thread id's.
  //


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

  // String to hold thread name
  string symbol;

 public:
  typedef Thread* ThreadPtr;
  explicit ThreadTable(const word32 TableSize = THREAD_TABLE_SIZE)
    : hash_table(TableSize),
      live(0),
      next_id(0),
      size(TableSize)
    {
      array = new ThreadPtr[size];
      
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
  string& MakeName(const ThreadTableLoc loc);
  string& MakeName(const ThreadTableLoc loc, const char * rootname);

  // Add a thread's name.
  bool AddName(const string&,	        	// Name of thread
	       const ThreadTableLoc);	// Thread id

  // Lookup a thread given its name. Returns (ThreadTableLoc) -1 when
  // the name can't be found.
  ThreadTableLoc LookupName(const string&) const;

  // Remove a thread's name.
  void RemoveName(const string&);

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







