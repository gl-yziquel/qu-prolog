// area_offsets.h - Contains all the 'typedef' for offset into different data
//		    areas.  If any of the area is changed, the following
//		    'typedef' may change.
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
// $Id: area_offsets.h,v 1.2 2000/12/13 23:10:00 qp Exp $

#ifndef	AREA_OFFSETS_H
#define	AREA_OFFSETS_H

#include "defs.h"

//
// Offsets for generic data areas.
//
typedef word32		PageLoc;	// See page.h
typedef PageLoc		StackLoc;	// See stack_qp.h
typedef word32	HashLoc;	// See hash_table.h

//
// Offsets for global data areas.
//
typedef StackLoc	StringLoc;	// See string_table.h
typedef HashLoc		AtomLoc;	// See atom_table.h
typedef HashLoc		PredLoc;	// See pred_table.h

//
// Offsets for data areas local to each thread.
//
typedef HashLoc		NameLoc;	// See name_table.h
typedef HashLoc         IPLoc;        // See name_table.h 
// typede	HeapLoc;	// See heap.h
typedef StackLoc	EnvLoc;		// See environment.h
typedef StackLoc	ChoiceLoc;	// See choice.h
typedef wordptr*	TrailLoc;	// See trail.h

//
// Offsets for data area for linking.
//
typedef	StackLoc	StringMapLoc;	// See string_map.h
typedef	StackLoc	NumberMapLoc;	// See string_map.h

#endif	// AREA_OFFSETS_H
