// gc_escapes.h - Garbage collector for threads.
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
// $Id: gc_escapes.h,v 1.5 2005/03/08 00:35:06 qp Exp $

#ifndef	GC_ESCAPES_H
#define	GC_ESCAPES_H

public: 

#ifdef QP_DEBUG
bool check_env(EnvLoc env);

bool check_choice(ChoiceLoc choiceloc);

bool check_trail();

bool check_ips();

bool check_name();

bool check_heap2(Heap& heap);

//
// Check heap for correct pointers
//
bool check_heap(Heap&, AtomTable*, GCBits&);
#endif // DEBUG

// Mark the registers

void gc_mark_registers(word32);

// Mark the environmants
void gc_mark_environments(EnvLoc);

// Mark the choicepoints
void gc_mark_choicepoints(ChoiceLoc);

// Mark the trail
void gc_mark_trail();

// Mark the implicit parameters
void gc_mark_ips();

// Mark the variable names
void gc_mark_names();

// Mark the heap

void gc_marking_phase(word32);

void gc_sweep_registers(word32);

void gc_sweep_trail(void);

void gc_sweep_names(void);

void gc_sweep_ips(void);

void gc_sweep_environments(EnvLoc);

void gc_sweep_choicepoints(ChoiceLoc);

void gc_compaction_phase(word32);


// Do garbage collection

bool gc(word32);

// Trigger garbage collection

ReturnValue psi_gc(void);

ReturnValue psi_suspend_gc(void);
ReturnValue psi_unsuspend_gc(void);

#ifdef QP_DEBUG
void dump_choices(ChoiceLoc);

void dump_areas(word32);

#endif // QP_DEBUG

#endif	// GC_ESCAPES_H
