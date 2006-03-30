// icm_handle.h -
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
// $Id: icm_handle.h,v 1.8 2006/01/31 23:17:50 qp Exp $
#ifdef ICM_DEF //don't use this file if icm isn't in use

#ifndef	ICM_HANDLE_H
#define	ICM_HANDLE_H

#include <sstream>
#include <ctype.h>

#include "atom_table.h"
#include "errors.h"
#include "heap_qp.h"
#include "icm_environment.h"
#include "int.h"
#include "thread_qp.h"
#include "thread_table_loc.h"

class ICMOutgoingTarget
{
private:
  string target;
public:
  // Thread number
  explicit ICMOutgoingTarget(const ThreadTableLoc id)
    {
      ostringstream buff;
      buff << (u_int)id;
      target = buff.str();
    }

  // Thread symbol
  ICMOutgoingTarget(const string& symbol)
    {
      target = symbol;
    }
  
  ~ICMOutgoingTarget(void)
    {
    }

  string& Target(void) { return target; }
};

class ICMIncomingTarget
{
private:
  enum { TARGET_ID, TARGET_SYMBOL } type;

  union {
    ThreadTableLoc id;
    char *symbol;
  } desc;
public:
  explicit ICMIncomingTarget(char *t)
    {
      assert(t != NULL);
      bool is_num = true;
      for (char* c = t; *c != '\0'; c++)
	{
	  if (!isdigit((int)(*c)))
	    {
	      is_num = false;
	      break;
	    }
	}
      if (is_num)
	{
	  type = TARGET_ID;
	  istringstream target_stream(t);
	  target_stream >> desc.id;
	}
      else
	{
	  type = TARGET_SYMBOL;
	  const size_t length = strlen(t) + 1;
	  desc.symbol = new char[length];
	  // Copy the target - carefully null terminating the stream
	  strcpy(desc.symbol, t);
	}
    }

  ~ICMIncomingTarget(void)
    {
      if (type == TARGET_SYMBOL)
	{
	  delete [] desc.symbol;
	}
    }

  bool IsID(void) const { return type == TARGET_ID; }
  ThreadTableLoc ID(void) const
    {
      assert(type == TARGET_ID);
      return desc.id;
    }
  
  bool IsSymbol(void) const { return type == TARGET_SYMBOL; }
  char *Symbol(void)
    {
      assert(type == TARGET_SYMBOL);
      return desc.symbol;
    }
};

// Create a handle for the current process.
// Warning: Don't icmReleaseHandle the handle.
extern icmHandle icm_process_handle(ICMEnvironment&);

// Create a handle for the supplied thread.
// Warning: Don't icmReleaseHandle the handle.
extern icmHandle icm_thread_handle(ICMEnvironment&, Thread&);

// For getting icmHandles to the prolog heap.
// Use heap.decode_icm_handle() to go from heap to icmHandle.
extern void icm_handle_to_heap(Heap&, AtomTable&, icmHandle, Object*&);

#endif	// ICM_HANDLE_H



#endif //ICM_DEF - don't use this file if icm isn't in use
