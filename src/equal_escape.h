// equal_escape.h - an escape function to call FastEqual.
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
// $Id: equal_escape.h,v 1.3 2002/03/27 23:23:47 qp Exp $

#ifndef EQUAL_ESCAPE_H
#define EQUAL_ESCAPE_H

public:
//
// psi_fast_equal(term1,term2,status)
// returns true iff term1 and term2 have the same structure.
// mode(in,in,out)
//
ReturnValue psi_fast_equal(Object *& , Object *& , Object *& );

//
// psi_equal_equal(term1,term2)
// returns true iff term1 == term2 .
// mode(in,in)
//
ReturnValue psi_equal_equal(Object *& , Object *&);

//
// psi_simplify_term(term1,term2)
// mode(in,out)
//
ReturnValue psi_simplify_term(Object *&, Object *&);

//
// psi_simplify_term3(term1,term2, issimp)
// mode(in,out,out)
//
ReturnValue psi_simplify_term3(Object *&, Object *&, Object *&);

#endif	// EQUAL_ESCAPE_H










