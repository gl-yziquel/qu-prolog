// defs.h - a collection of useful declarations.
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
// $Id: defs.h,v 1.3 2001/11/21 00:21:12 qp Exp $

#ifndef	DEFS_H
#define	DEFS_H

#include <limits.h>
#include <sys/types.h>
#include <string.h>

// Automatically generated stuff.
#include "config.h"

#include "debug.h"

typedef char			int8;
typedef u_char			word8;
typedef SHORT_TYPE		int16;
typedef unsigned SHORT_TYPE	word16;
typedef INT_TYPE		int32;
typedef unsigned INT_TYPE	word32;
typedef word32                  heapobject;
typedef word8 	*CodeLoc;

//
// Define a K.
//
const	word32	K			= 1024;


const	word32	NUMBER_X_REGISTERS	= 20;

const	word32	PILE_SIZE		= 10;

const word32 WORD32_MAX	= (word32) -1;

const word32 NULL_LOC	= 0;
const word32 EMPTY_LOC	= WORD32_MAX;

//
// Default maximum number of threads.
//
const word32 THREAD_TABLE_SIZE = 100;

const word32 ATOM_LENGTH = 256;
const word32 IO_BUF_LENGTH = 2048;
const word32 NUMBER_OF_BUFFERS = 200;

const word32 ARITY_MAX = 255;

const word32 THREAD_MAX = 100;

const word32 NUM_OPEN_STREAMS = 100;

const word32 NUM_OPEN_SOCKETS = 20;

typedef void (*void_fn_ptr)(void);

// Maximum length of a TCP message.
const word32 TCP_BUF_LEN = 2048;

//
// Maximum arity of a pseudo-instruction.
//
const word32 PSI_ARITY_MAX = 5;

//
// Number representing ``no port''.
//
const u_short PORT_NONE = 0;

//
// String equality.
//
inline bool streq(const char *x, const char *y)
{
  DEBUG_ASSERT(x != NULL && y != NULL);
  return strcmp(x, y) == 0;
}

inline bool streqn(const char *x, const char *y, const size_t len)
{
  DEBUG_ASSERT(x != NULL && y != NULL);
  return strncmp(x, y, len) == 0;
}


#endif	// DEFS_H



