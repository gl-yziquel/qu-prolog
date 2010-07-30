// manager.h - For managing finite collections of things.
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
// $Id: manager.h,v 1.5 2006/01/31 23:17:51 qp Exp $

#ifndef	MANAGER_H
#define	MANAGER_H

#include <stdlib.h>
#include "defs.h"
#include "errors.h"

template <class Type>
class Manager
{
protected:
  word32 MAX;
  Type **elems;

public:
  explicit Manager(const word32 size)
    {
      assert(size > 0);

      MAX = size;

      typedef Type *TypePtr;	// For the benefit of ANSI C++
      elems = new TypePtr[MAX];
     
      assert(elems != NULL);

      for (word32 index = 0; index < MAX; index++)
	{
	  elems[index] = NULL;
	}
    }

  ~Manager(void)
    {
      delete [] elems;
    }

  bool isLegalIndex(const word32 index) const	
    { return index < MAX; }

  bool isElem(const word32 index) const
    { return isLegalIndex(index) && elems[index] != NULL; }
  
  Type &operator[](const word32 index) const
    {
      if (isElem(index))
	{
	  return *elems[index];
	}
      else
	{
	  Fatal(__FUNCTION__, "Bad index argument");
	}
    }

  int nextFree(const word32 start) const
    {
      word32 index;

      for (index = start; index < MAX && elems[index] != NULL; index++)
	;
      
      return (index == MAX) ? -1 : (int) index;
    }

  int nextFree(void) const { return nextFree(0); }
  
  //
  // Grab any slot.
  //
  int grab(Type *e)
    {
      int i = nextFree(0);
      
      if (isLegalIndex(i))
	{
	  elems[i] = e;
	}
      
      return i;
    }

  //
  // Grab a particular slot.
  //
  int grab(const word32 index, Type *e)
    {
      if (isLegalIndex(index))
	{
	  if (isElem(index))
	    {
	      Fatal(__FUNCTION__, "Attempt to overwrite item");
	    }
	  else
	    {
	      elems[index] = e;

	      return index;
	    }
	}
      else
	{
	  Fatal(__FUNCTION__, "Bad index argument ");
	}
    }

  //
  // Grab any slot after the one specified.
  //
  int grabAfter(const word32 start, Type *e)
    {
      int i = nextFree(start);
      
      if (isLegalIndex(i))
	{
	  elems[i] = e;
	}

      return i;
    }

  void release(const word32 index)
    {
      if (isLegalIndex(index))
	{
	  elems[index] = NULL;
	}
    }
};

#endif	// MANAGER_H
