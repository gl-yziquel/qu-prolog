// gc_escapes.h - Garbage collector for threads.
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
// $Id: gc_escapes.h,v 1.4 2004/02/25 21:25:32 qp Exp $

#ifndef	GC_ESCAPES_H
#define	GC_ESCAPES_H

public: 

#ifdef DEBUG
bool check_env(EnvLoc env);

bool check_choice(ChoiceLoc choiceloc);

bool check_ip_trail();

bool check_ips();

bool check_name();

bool check_obj_trail();

bool check_heap2(Heap& heap);

//
// Check heap for correct pointers
//
bool check_heap(Heap&, AtomTable*);
#endif // DEBUG

// Mark the registers

void gc_mark_registers(word32, int32&);

// Mark the environmants
void gc_mark_environments(EnvLoc, int32&);

// Mark the choicepoints
void gc_mark_choicepoints(ChoiceLoc, int32&);

// Mark the implicit parameter trail
void gc_mark_ip_trail(int32&);

// Mark the implicit parameters
void gc_mark_ips(int32&);

// Mark the variable names
void gc_mark_names(int32&);

// Mark the required old values in object trail 
void gc_mark_object_trail(int32&);

// Mark the heap

void gc_marking_phase(word32, int32&);

void gc_sweep_registers(word32);

void gc_sweep_binding_trail(void);

void gc_sweep_tag_trail(void);

void gc_sweep_object_trail(void);

void gc_sweep_ip_trail(void);

void gc_sweep_names(void);

void gc_sweep_ips(void);

void gc_sweep_environments(EnvLoc);

void gc_sweep_choicepoints(ChoiceLoc, int32&);

void gc_compaction_phase(word32, int32&);


// Do garbage collection

void gc(word32);

// Trigger garbage collection

ReturnValue psi_gc(void);

#ifdef DEBUG
void dump_choices(ChoiceLoc);

void dump_areas(word32);

#endif // DEBUG

#endif	// GC_ESCAPES_H
