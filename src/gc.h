// gc.h - Garbage collector for threads.
//
// ##Copyright##
// 
// Copyright 2000-2016 Peter Robinson  (pjr@itee.uq.edu.au)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.00 
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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



void gc_mark_pointer(Object*, Heap&, ObjectsStack&, GCBits&);

void gc_compact_heap(int32, Heap&);

void update_forward_pointers(Heap& heap, GCBits& gcbits);
void update_backward_pointers(Heap& heap, GCBits& gcbits);

#ifdef QP_DEBUG
bool check_term(Object* term);
#endif //QP_DEBUG
#endif	// GC_H
