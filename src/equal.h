
// equal.h
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
// $Id: equal.h,v 1.2 2001/09/20 03:22:06 qp Exp $

#ifndef	EQUAL_H
#define	EQUAL_H

public:
//
// Call $equal_var/2 which is defined in Prolog.
//
bool equalVariable(PrologValue& var1, PrologValue& var2);

//
// Call $equal_object_variable/2 which is defined in Prolog.
//
bool equalObjectVariable(PrologValue&, PrologValue&);


//
// C-level implementation of ==
//
bool equalEqual(PrologValue&, PrologValue&, int&);

//
// C-level version of simplify_term
//

//
// Top-level - returns true iff some simplification was done.
//
bool simplify_term(PrologValue&, Object*&);

bool simplify_sub_term(PrologValue&, Object*&, Object*);

bool gen_nfi_delays(ObjectVariable*, Object*);

void transform_with_tester(Object*, Object*&, Object*);

#endif	// EQUAL_H







