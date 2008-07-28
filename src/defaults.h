// defaults.h - Global default size constants for
//		all the C++ components of the QP
//		suite. #include this file whenever
//		global default values are needed.
//		This should only be necessary when
//		command line arguments are being
//		processed.
//		Otherwise, extract the correct value
//		from the *_options object.
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
// $Id: defaults.h,v 1.5 2001/12/17 04:27:32 qp Exp $

#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <sys/types.h>

#include "defs.h"
#include "tcp_qp.h"

//
// Default size in K for different global areas.
//
const word32 CODE_SIZE = 400;
const word32 STRING_TABLE_SIZE = 64;

//
// Default size in entries for different global hash tables.
//
const word32 PREDICATE_TABLE_SIZE  = 10009;
const word32 ATOM_TABLE_SIZE  = 10009;

//
// Default size for different areas local to each thread.
//
const word32 NAME_TABLE_SIZE  = 10000;
const word32 HEAP_SIZE  = 400;			// K
const word32 ENVIRONMENT_STACK_SIZE = 64;	// K
const word32 CHOICE_STACK_SIZE  = 64;		// K
const word32 BINDING_TRAIL_SIZE  = 32;	       	// K
const word32 OTHER_TRAIL_SIZE = 32;		// K
const word32 SCRATCHPAD_SIZE = 100;             // K
const word32 IP_TABLE_SIZE = 10000;                 

//
// Default size in K for area used in linking.
//
const word32 STRING_MAP_SIZE  = 64;
//
// Default size in K entries for the record database reference table.
//
const word32 RECORD_DB_SIZE  = 64;

//
// Default qx file.
//
char *QX_FILE = NULL;

//
// Default stand alone setting. If true, qem won't try to register itself
// with the nameserver. Otherwise, it will.
//
const bool STAND_ALONE = false;


//
// Default nameserver port.
//
const u_short PEDRO_PORT = 4550;

//
// Default process symbol.
//
char *PROCESS_SYMBOL = NULL;


//
// Default initial goal
//
char* INITIAL_GOAL = NULL;

//
// Default debugging value.
//
const bool DEBUGGING = false;

#endif // DEFAULTS_H

