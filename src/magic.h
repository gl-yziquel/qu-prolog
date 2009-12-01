// magic.h - Magic numbers for files.
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: magic.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	MAGIC_H
#define	MAGIC_H

#include "defs.h"

//
// Size of a magic number.
//
const	word32	MAGIC_SIZE			= sizeof(word32);

//
// Convert an ASCII string of length 4 to a magic number.
//
//
#define Magic(s) ((u_long)((s[0]<<24)|(s[1]<<16)|(s[2]<<8)|(s[3])))

//
// Magic strings for different areas.
//
#define  QU_PROLOG_VERSION		Magic("Q402")
#define  CODE_MAGIC_NUMBER		Magic("QCA0")
#define  PRED_TABLE_MAGIC_NUMBER	Magic("QPT0")
#define  STRING_TABLE_MAGIC_NUMBER	Magic("QST0")
#define  ATOM_TABLE_MAGIC_NUMBER	Magic("QAT0")
#define  NAME_TRAIL_MAGIC_NUMBER	Magic("QNT0")
#define  NAME_TABLE_MAGIC_NUMBER	Magic("QNA0")
#define  CHOICE_MAGIC_NUMBER		Magic("QCS0")
#define  ENVIRONMENT_MAGIC_NUMBER	Magic("QES0")
#define  HEAP_TRAIL_MAGIC_NUMBER	Magic("QHT0")
#define  HEAP_MAGIC_NUMBER		Magic("QHP0")
#define  RECORD_TABLE_MAGIC_NUMBER	Magic("QRT0")

#endif	// MAGIC_H
