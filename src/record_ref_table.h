// record_ref_table.h - Record database class.
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
// $Id: record_ref_table.h,v 1.4 2005/03/08 00:35:13 qp Exp $

#ifndef RECORD_REF_TABLE_H
#define RECORD_REF_TABLE_H

#include <iostream>
#include <string.h>

#include "config.h"

#include "area_offsets.h"
#include "atom_table.h"
#include "defs.h"
#include "magic.h"
#include "page_table.h"
#include "qem_options.h"
#include "stack_qp.h"
#include "timestamp.h"

class RecordRefInfo
{
private:
  bool erased;	// True iff this recorded value has been erased
  StackLoc prev;	// Pointers to previous and
  StackLoc next;	// next elements in the chain

  word32 len;
#ifdef WIN32
  char s[1];
#else
  char s[1] __attribute__ ((aligned));
#endif

public:
  RecordRefInfo(void)
  { erased = false; prev = next = EMPTY_LOC; len = 0; }

  // Access functions
  bool getErased(void) const { return(erased); }
  StackLoc getPrev(void) const { return(prev); }
  StackLoc getNext(void) const { return(next); }
  word32 getLength(void) const { return(len); }
  const char *getString(void) const { return(s); }

  // Setting functions
  void	setErased(const bool e)	{ erased = e; }
  void	setPrev(const StackLoc p) { prev = p; }
  void	setNext(const StackLoc n) { next = n; }
  void	setString(const char *str, const word32 l)
  {
    len = l;
    memcpy(s, str, len);
  }
};

class RecordDB: public PrologStack<RecordRefInfo>,
		public Timestamp
{
private:
virtual const char* GetAreaName(void)	const
	{ return("record ref table"); }

public:
  RecordDB(word32 tableSize,
	   word32 boundary)
    : PrologStack<RecordRefInfo>(tableSize, boundary) { }

  // Access functions
  bool getErased(const StackLoc index) const
  {
    return(inspectEntry(index).getErased());
  }

  StackLoc getPrev(const StackLoc index) const
  { 
    return(inspectEntry(index).getPrev());
  }

  StackLoc getNext(const StackLoc index) const
  {
    return(inspectEntry(index).getNext());
  }

  word32 getLength(const StackLoc index) const
  {
    return(inspectEntry(index).getLength());
  }

  const char *getString(const StackLoc index) const
  {
    return(inspectEntry(index).getString());
  }

  // Setting functions
  void	setErased(const StackLoc index, const bool e)
  {
    Stamp();

    getEntry(index).setErased(e);
  }

  void	setPrev(const StackLoc index, const StackLoc p)
  { 
    Stamp();

    getEntry(index).setPrev(p);
  }

  void	setNext(const StackLoc index, const StackLoc n)
  {
    Stamp();

    getEntry(index).setNext(n);
  }

  void	setString(const StackLoc index, const char *s, word32 l)
  {
    Stamp();

    getEntry(index).setString(s, l);
  }

  // Adding a new entry
  StackLoc add(const StackLoc p, const StackLoc n, const char *s, word32 l)
  {
    Stamp();

    StackLoc loc = allocateBlock(sizeof(RecordRefInfo) + l - 1);	
    
    getEntry(loc).setErased(false);
    getEntry(loc).setPrev(p);
    getEntry(loc).setNext(n);
    getEntry(loc).setString(s, l);
    
    return(loc);
  }
  
  StackLoc	getTop(void)	const
  { return(getTopOfStack()); }

  //
  // Save and restore the table.
  //
  void	save(ostream& ostrm) const
  { saveStack(ostrm, RECORD_TABLE_MAGIC_NUMBER); }
  
  void	load(istream& istrm)
    {
      loadStack(istrm);
      Stamp();
    }

};
#endif // RECORD_REF_TABLE_H
