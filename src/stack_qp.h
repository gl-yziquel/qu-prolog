// stack_qp.h - Fundamental stack arrangement.
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
// $Id: stack_qp.h,v 1.8 2003/09/28 07:53:36 qp Exp $

#ifndef	STACK_QP_H
#define	STACK_QP_H

#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "area_offsets.h"
#include "defs.h"
#include "errors.h"
#include "page_table.h"
#include "timestamp.h"

typedef	word32	StackWord;

extern const char *Program;

using namespace std;

//
// This is primary used for stack inspection by statistics.
//
class	FixedSizeStack
{
public:

	//
	// Return the size of the stack in use.  The size is defined as the
	// number of StoredType in the stack.
	//
virtual	word32		sizeOfStack(void) const		{ return(0); }

	//
	// Return the size allocated to the stack.  The size is defined as the
	// number of StoredType in the stack.
	//
virtual	word32		allocatedSize(void) const	{ return(0); }

	//
	// Return the maximum usage for this session.
	//
virtual	word32		maxUsage(void) const		{ return(0); }
};

//
// StoredType is the data type stored in the stack.
// Error messages that can be reported:
//	OutOfPage, BadReset, BadReference, EmptyStack.
//
template <class StoredType>
class	PrologStack : private PageTable <StoredType>,
		      public FixedSizeStack
{

private:

  StackLoc	top;			// Top of stack.
  StackLoc	overflow;		// Overflow boundary.
  StackLoc	highWaterMark;		// Maximum usage for a session.
  
  //
  // Return the name of the table.
  //
  virtual	const char	*getAreaName(void) const
    { return("prolog stack"); }
  
  //
  // Indicate the stack will overflow.
  //
  void		stackWillOverflow(void) const
    {
      ErrArea = getAreaName();
      FatalS(__FUNCTION__, "stack overflow ", ErrArea);
    }
  
  //
  // Raise an exception if the allocation crosses over the overflow
  // boundary.
  //
  void		overflowCheck(const StackLoc OldTop,
			      const StackLoc NewTop)
    {
      if (highWaterMark < NewTop)
	{
	  if (NewTop <= overflow)
	    {
	      highWaterMark = NewTop;
	    }
	  else if (OldTop <= overflow)
	    {
	      stackWillOverflow();
	    }
	}
    }
  
protected:
  
  const StoredType& inspectEntry(const StackLoc s) const
    {
      DEBUG_CODE(
		    if (s >= top)
		    {
		      BadReference(__FUNCTION__, getAreaName(), s);
		    }
		    );
      
      return(getItem(s));
    }

  //
  // Get the current top of stack location.
  //
  StackLoc	getTopOfStack(void) const	{ return(top); }
  
  //
  // Set the top of the stack.
  // BadReset is reported if the top of stack is reset to anywhere
  // above the current top of stack.
  //
  void		setTopOfStack(const StackLoc NewTop)
    {
/*
      DEBUG_CODE(if (NewTop > top)
		    {
		      BadReset(__FUNCTION__,
			       getAreaName(),
			       NewTop);
		    }
		    );
*/
      top = NewTop;
    }
  
  //
  // Reset the top of the stack to the beginning of the stack.
  //
  void		clearStack(void)		{ setTopOfStack(0); }
  
  const StoredType *inspectAddr(const StackLoc loc) const
    {
      DEBUG_CODE(if (loc >= top)
		    {
		      BadReference(__FUNCTION__,
				   getAreaName(),
				   loc);
		    }
		    );
      return(offsetToAddress(loc));
    }
  
  //
  // Push an element onto the stack.
  // OutOfPage is reported if the index table is run out; or
  //
  void	pushElement(const StoredType word)
    {
	allocateItems(top, 1);
	getItem(top) = word;
	top++;
	overflowCheck(top - 1, top);
    }
  
  //
  // Pop an element off the stack.
  // EmptyStack is reported if it tries to pop beyond the bottom of the
  // stack.
  //
  StoredType	popElement(void)
    {
      DEBUG_CODE(if (top == 0)
		    {
		      EmptyStack(__FUNCTION__,
				 getAreaName());
		    }
		    );
      //
      // Because the top points to next free entry, so
      // decrement the pointer and return the popped
      // value.
      //
      return(getItem(--top));
    }
  
  //
  // Allocate 'n' elements of StoredType in the stack.
  // OutOfPage is reported if the index table is run out; or
  //
  StackLoc allocateElements(const word32 n)
    {
	StackLoc	block = top;

	allocateItems(top, n);
	top += n;
	overflowCheck(block, top);
	return(block);
    }
  
  //
  // Round 'size' to the next multiple of 'basic' unit.
  //
  word32 roundBasicUnit(const word32 size, const word32 basic) const
    { return((size + basic - 1) / basic); }
  
  //
  // Push a record onto the stack and return a pointer to it.
  // 'size' is given in bytes.
  // OutOfPage is reported if the index table is run out; or
  //
  StackLoc	allocateBlock(const word32 size)
    {
        word32   	elements;
	StackLoc	block, OldTop = top;

	//
	// Round up to the nearest whole StoredType.
	//
        elements = roundBasicUnit(size, sizeof(StoredType));
	block = allocateSegment(top, elements);
	top = block + elements;
	overflowCheck(OldTop, top);
	return(block);
    }
  
  //
  // Return the size of the stack in use.  The size is defined as the
  // number of StoredType in the stack.
  //
  virtual word32 sizeOfStack(void) const	{ return(getTopOfStack()); }
  
  //
  // Return the maximum usage for this session.
  //
  virtual word32 maxUsage(void) const		{return(highWaterMark);}
  
  //
  // Write the stack to a stream.
  //
  void		saveStack(std::ostream& ostrm, const u_long magic) const;
  
  //
  // Load a file segment into the stack.
  //
  void		loadFileSegment(std::istream& istrm, const char *file,
				const word32 size)
    { readData(istrm, file, size, allocateElements(size)); }
  
  //
  // Load the stack from a stream.
  //
  void		loadStack(std::istream& istrm);
  
public:

  //
  // Given an index of a word in the stack, fetch the address.
  // BadReference is reported if reference is made above the current
  // top of stack.
  //
  StoredType *fetchAddr(const StackLoc loc)
    {
      DEBUG_CODE(if ((top > 0) && (loc >= top))
      {
	cerr << __FUNCTION__ << " " << loc << " " << top << endl;
	
	BadReference(__FUNCTION__, getAreaName(), loc);
      }
      );
      return(offsetToAddress(loc));
    }

  //
  // Return the size allocated to the stack.  The size is defined as the
  // number of StoredType in the stack.
  //
  virtual word32 allocatedSize(void) const	{ return(areaSize()); }

  //
  // Get an element.
  //
  StoredType&	getEntry(const StackLoc s)
    {
      DEBUG_CODE(
		    if (s >= top)
		    {
		      BadReference(__FUNCTION__, getAreaName(), s);
		    }
		    );
      
      return(getItem(s));
    }

  PrologStack(word32 size, word32 boundary = 0) :
  PageTable <StoredType> (size)
    {
      top = 0;
      highWaterMark = 0;
      overflow = areaSize() - boundary * K;
    }
  virtual	~PrologStack(void);
};


#endif	// STACK_QP_H
