// heap_buffer.h - Qu-Prolog buffer management.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: heap_buffer.h,v 1.5 2006/01/31 23:17:50 qp Exp $

#ifndef	HEAP_BUFFER_H
#define	HEAP_BUFFER_H

//
// Buffers are used in conjunction with the scratchpad for findall 
// and simplifying substitutions.
//

#include "defs.h"
#include "objects.h"

class HeapBuffer
{
private:
  u_int count;       // how many list elements are in the buffer
  heapobject* buffer_start;     // address of the start of the buffer
  Object** tail_address; // the address of the list tail for the next element
  heapobject* initial_heap_top; // the top of heap when buffer allocated

public:
  
  //
  // Access methods.
  //
  u_int 	 getCount(void)	      const { return(count); }
  heapobject*	 getStart(void )      const { return(buffer_start); }
  Object**       getTailAddress(void) const { return(tail_address); }
  heapobject*    getInitialTop(void)  const { return(initial_heap_top); }
  
  void incCount(void)                { count++; }
  void setTailAddress(Object** addr) { tail_address = addr; }

  void init(heapobject* heapTop, heapobject* scratchTop)
    {
      count = 0;
      buffer_start = scratchTop;
      tail_address = NULL;
      initial_heap_top = heapTop;
    }

  HeapBuffer(void)			       
    {
      count = 0;
      buffer_start = NULL;
      tail_address = NULL;
      initial_heap_top = NULL;
    }
      
};

class	HeapBufferManager
{
private:

  HeapBuffer		*buffers;
  word32		size;		// Size of buffers array.
  word32		top;		// Points to the next free entry.
  
public:
  //
  // Check if no buffers have been allocated.
  //
  bool isEmpty(void) { return (top == 0); }

  //
  // Allocate a buffer, return the buffer index.
  //
  word32 allocate(heapobject* heapTop, heapobject* scratchTop);
  
  //
  // Pop the buffer from the scratchpad and release the buffer object.
  //
  void deallocate(word32 bindex);

  //
  // Get the start address of the buffer
  //
  heapobject* getStart(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getStart());
    }

  //
  // Get the initial heap address stored in the buffer
  //
  heapobject* getInitialTop(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getInitialTop());
    }

  //
  // Get the count i.e. number of elements in list of the buffer.
  //
  u_int getCount(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getCount());
    }

  //
  // Increment the count in list of the buffer.
  //
  void incCount(word32 bindex)
    {
      assert(bindex == (top - 1));
      buffers[bindex].incCount();
    }
  
  //
  // Get the address of the list tail of the buffer.
  //
  Object** getTailAddress(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getTailAddress());
    }

  //
  // Set the address of the list tail of the buffer.
  //
  void setTailAddress(word32 bindex, Object** addr)
    {
      assert(bindex == (top - 1));
      buffers[bindex].setTailAddress(addr);
    }


  //
  // Get the list of the buffer.
  //
  Object* getTerm(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(reinterpret_cast<Object*>(buffers[bindex].getStart()));
    }
    

  //
  // Allocate space and initialize.
  //
  explicit HeapBufferManager(word32 NumberOfBuffers)
    {
      buffers = new HeapBuffer [NumberOfBuffers];
      size = NumberOfBuffers; 
      top = 0;
    }
  ~HeapBufferManager(void)
    {
      if (buffers != NULL)
	{
	  delete [] buffers;
	}
      top = 0;
    }
};

#endif  // HEAP_BUFFER_H




