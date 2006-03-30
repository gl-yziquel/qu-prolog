// thread_table.cc -
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
// $Id: thread_table.cc,v 1.8 2006/01/31 23:17:52 qp Exp $

#include <sys/types.h>
#include <sstream>

#include "config.h"

#include "thread_qp.h"
#include "thread_info.h"
#include "thread_table.h"

//
// Hash table for mapping from thread names to thread ids.
//
string&
ThreadTable::MakeName(const ThreadTableLoc loc)
{
  ostringstream strm;
  ThreadHashTableEntry entry;
  entry.setSymbol(&symbol);

  while (true)
    {
      strm.str("");
      strm << "thread" <<  next_id;
      symbol = strm.str();
      int index = hash_table.search(entry);
      next_id++;
      if (index == -1)
	{
          ThreadHashTableEntry* new_entry = new ThreadHashTableEntry;
	  new_entry->Assign(loc, symbol);
          hash_table.insert(*new_entry, index);
          return (symbol);
	}
    }
  assert(false);
  return (symbol);
}

bool
ThreadTable::AddName(const string& symbol,	// Name of the thread
		     const ThreadTableLoc loc)	// Thread id
{
  string sym(symbol);
  ThreadHashTableEntry entry;
  entry.setSymbol(&sym);

  int index = hash_table.search(entry);
  if (index == -1)
    {
      ThreadHashTableEntry* new_entry = new ThreadHashTableEntry;
      new_entry->Assign(loc, symbol);
      hash_table.insert(*new_entry, index);

      return true;
    }
  else
    {
      return false;
    }
}

ThreadTableLoc
ThreadTable::LookupName(const string& str) const
{
  string sym(str);
  ThreadHashTableEntry entry;
  entry.setSymbol(&sym);

  const int index = hash_table.search(entry);
  if (index == -1)
    {
      return (ThreadTableLoc) -1;
    }
  return hash_table.getEntry(index).Loc();
}

void
ThreadTable::RemoveName(const string& symbol)
{ 
  string sym(symbol);
  ThreadHashTableEntry entry;
  entry.setSymbol(&sym);

  const int index = hash_table.search(entry);
  if (index != -1)
    {
      hash_table.getEntry(index).makeRemoved();
    }
}

ThreadTableLoc
ThreadTable::AddID(Thread *thread)
{
  assert(thread != NULL);

  if (live < size)
    {
      ThreadTableLoc loc;

      for (loc = 0;
	   array[loc] != NULL;
	   loc++)
	;

      array[loc] = thread;

      return loc;
    }
  else
    {
      return (ThreadTableLoc) -1;
    }
}

Thread *
ThreadTable::LookupID(const ThreadTableLoc loc)
{
  assert(IsValid(loc));

  return array[loc];
}

const Thread *
ThreadTable::operator[](const ThreadTableLoc loc) const
{
  assert(IsValid(loc));

  return array[loc];
}

void
ThreadTable::RemoveID(const ThreadTableLoc loc)
{
  assert(IsValid(loc) && array[loc] != NULL);

  array[loc] = NULL;
}

ostream&
operator<<(ostream& ostrm, ThreadTable& thread_table)
{
  ostrm << "QPID\tSYMBOL\tGOAL" << endl;

  for (ThreadTableLoc loc = 0;
       loc < thread_table.Size();
       loc++)
    {
      if (thread_table[loc] != NULL)
	{
	  Thread& thread = *(thread_table.LookupID(loc));

	  ostrm << loc << "\t";
	  ostrm << thread << endl;
	}
    }

  return ostrm;
}

