// unravel.h -
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
// $Id: unravel.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	UNRAVEL_H
#define	UNRAVEL_H

#include "compiler_support.h"

public: 

void setyregs(WordArray&, int);

Object* yreg(int);

Object* xreg(int);

word32 callpred(Object*, int);

word32 getput(Object*, Object*, bool, WordArray&);

word32 unifyset(Object*, bool, WordArray&);

word32 getputlist(Object*, bool, WordArray&);

word32 getputstruct(Object*, int, Object*, bool, WordArray&);

word32 getstructframe(Object*, int, WordArray&);

word32 putquant(Object*, WordArray&);

word32 putsub(Object*, int, WordArray&);

word32 putemptysub(Object*, WordArray&);


word32 putsubterm(Object*, Object*, WordArray&);


void xputget(Object*, Object*, WordArray&, WordArray&);

void varunify(Object*, Object*, WordArray&, WordArray&);

void goalSubSpread(Object*, Object*, WordArray&, WordArray&);

void goalStructSpread(Object*, Object*, WordArray&, WordArray&);

void goalArgSpread(Object*, Object*, WordArray&, WordArray&);

void headStructSpread(Object*, Object*, WordArray&, bool, WordArray&);

void headArgSpread(Object*, Object*, WordArray&, WordArray&);

void unravelHead(Object*, WordArray&, WordArray&);

void goalSpread(Object*, WordArray&, WordArray&);

void unravelBody(Object*, WordArray&, WordArray&);

void unravel(Object*,  WordArray&, WordArray&, int&);

#endif	// UNRAVEL_H



