// thread_info.h - Thread identification, etc.
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: thread_info.h,v 1.7 2006/01/31 23:17:52 qp Exp $

#ifndef THREAD_INFO_H
#define THREAD_INFO_H

#include <iostream>

#include "config.h"

#include "heap_qp.h"
//#include "symbol_info.h"
#include "thread_table_loc.h"

class ThreadInfo
{
private:
  // Location in global thread table.
  bool thread_table_loc_set;
  bool is_forbid_thread;
  bool symbol_set;

  // Is this an initial thread?
  const bool initial;

  // Initial Prolog goal of this thread.
  Object* goal;

  ThreadTableLoc thread_table_loc;
  // Thread symbol
  string symbol;

public:
  explicit ThreadInfo(Thread *pt)
    : thread_table_loc_set(false),
    is_forbid_thread(false),
    symbol_set(false),
    initial(pt == NULL),
    goal(NULL)
  {
  }

  ~ThreadInfo(void)
    { }

  bool IDSet(void) const { return thread_table_loc_set; }
  ThreadTableLoc ID(void) const
  {
    assert(thread_table_loc_set);
    return thread_table_loc;
  }
  void SetID(const ThreadTableLoc ttl)
  {
    thread_table_loc = ttl;
    thread_table_loc_set = true;
  }

  bool Initial(void) const { return initial; }

  Object*& Goal(void) { return goal; }

  void setForbidThread(bool is_forbid) { is_forbid_thread = is_forbid; }

  bool isForbidThread(void) const { return is_forbid_thread; }

  bool SymbolSet(void) const { return symbol_set; }

  const string& Symbol(void) const
  {
    return symbol;
  }

  void SetSymbol(const string& s)
  {
    symbol_set = true;
    symbol = s;
  }

  ostream& Display(ostream& ostrm, AtomTable& atoms, Heap& heap);
};

#endif // THREAD_INFO_H
