// thread_table.cc -
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
// $Id: thread_table.cc,v 1.3 2001/02/22 21:47:00 qp Exp $

#include <sys/types.h>
#include <strstream.h>

#include "config.h"

#include "thread_qp.h"
#include "thread_info.h"
#include "thread_table.h"

//
// Hash table for mapping from thread names to thread ids.
//
char*
ThreadTable::MakeName(const ThreadTableLoc loc)
{
  ostrstream strm(name_buff, ATOM_LENGTH);

  while (true)
    {
      strm.seekp(0);
      if (strm.good() && strm.form("thread%d", next_id).fail())
	{
	  Fatal(__FUNCTION__, "problem generating thread ID");
	}
      strm << ends;
      String symbol(name_buff);
      HashTableKey key(symbol);

      const ThreadTableLoc index = hash_table.Search(key);
      HashTableEntry& entry = hash_table.GetEntry(index);
      next_id++;
      if (entry.isEmpty())
	{
	  entry.Assign(loc, symbol);
	  return (name_buff);
	}
    }
  DEBUG_ASSERT(false);
  return (NULL);
}

bool
ThreadTable::AddName(const String& symbol,	// Name of the thread
		     const ThreadTableLoc loc)	// Thread id
{
  HashTableKey key(symbol);

  const ThreadTableLoc index = hash_table.Search(key);
  HashTableEntry& entry = hash_table.GetEntry(index);

  if (entry.isEmpty())
    {
      entry.Assign(loc, symbol);

      return true;
    }
  else
    {
      return false;
    }
}

ThreadTableLoc
ThreadTable::LookupName(const String& str) const
{
  HashTableKey key(str);

  const ThreadTableLoc index = hash_table.Search(key);
  const HashTableEntry& entry = hash_table.InspectEntry(index);
  if (entry.isEmpty())
    {
      return (ThreadTableLoc) -1;
    }

  return entry.Loc();
}

void
ThreadTable::RemoveName(const String& symbol)
{
  HashTableKey key(symbol);

  const ThreadTableLoc index = hash_table.Search(key);
  HashTableEntry& entry = hash_table.GetEntry(index);

  if (!entry.isEmpty())
    {
      entry.Clear();
    }
}

ThreadTableLoc
ThreadTable::AddID(Thread *thread)
{
  DEBUG_ASSERT(thread != NULL);

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
  DEBUG_ASSERT(IsValid(loc));

  return array[loc];
}

const Thread *
ThreadTable::operator[](const ThreadTableLoc loc) const
{
  DEBUG_ASSERT(IsValid(loc));

  return array[loc];
}

void
ThreadTable::RemoveID(const ThreadTableLoc loc)
{
  DEBUG_ASSERT(IsValid(loc) && array[loc] != NULL);

  array[loc] = NULL;
}

ostream&
operator<<(ostream& ostrm, ThreadTable& thread_table)
{
  ostrm.form("%6s %-9s %-20s %-40s\n",
	     "QPID", "STATUS", "SYMBOL", "GOAL");

  for (ThreadTableLoc loc = 0;
       loc < thread_table.Size();
       loc++)
    {
      if (thread_table[loc] != NULL)
	{
	  Thread& thread = *(thread_table.LookupID(loc));

	  ostrm.form("%6ld ", loc);
	  ostrm << thread << endl;
	}
    }

  return ostrm;
}

