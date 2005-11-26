// gc.h - Garbage collector for threads.
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
// $Id: gc.h,v 1.5 2005/03/08 00:35:06 qp Exp $

#ifndef	GC_H
#define	GC_H

#include "heap_qp.h"
#include "objects.h"

#ifdef QP_DEBUG
bool check_heap2(Heap&);
#endif // QP_DEBUG
//
// In the "upward" phase of compression an entry in the heap
// with the F bit set can be found. This happens when the object
// starting at this point has previously entered a relocation chain.
// At this point we want to relocate the chain so that we are pointing
// at the final destination. However, in order to do this we need to know the
// size of the object stored at the current location. To do this we need the
// tag for the object - which is found at the end of the relocation chain.
// This function is used to find the end of the relocation chain.
//
inline heapobject* unfold_chain(heapobject* ptr)
{
  while ((*ptr & Object::GC_F) == Object::GC_F)
    {
      ptr = reinterpret_cast<heapobject*>(*ptr & ~Object::GC_Mask);
    }
  return ptr;
}

inline void update_relocation_chain(heapobject* current, heapobject* dest)
{
  heapobject* j;
  while ((*current & Object::GC_F) == Object::GC_F)
    {
      j = reinterpret_cast<heapobject*>(*current & ~Object::GC_Mask);
      *current = (*j & ~Object::GC_M) | (*current & Object::GC_M);
      *j = reinterpret_cast<heapobject>(dest) | (*j & Object::GC_M);
    }
}

inline void into_relocation_chain(heapobject* j, heapobject* current)
{
  *current = (*j & ~Object::GC_M) | (*current & Object::GC_M);
  *j = reinterpret_cast<heapobject>(current) | 
       (*j & Object::GC_M) | Object::GC_F; 
}

void gc_mark_pointer(Object*, int32&, Heap&);

void gc_compact_heap(int32, Heap&);

#ifdef QP_DEBUG
bool check_term(Object* term);
#endif //QP_DEBUG
#endif	// GC_H
