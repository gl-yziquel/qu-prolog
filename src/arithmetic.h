// arithmetic.h -  definitions for pseudo-instructions for arithmetic
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
// $Id: arithmetic.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

private:
//
// arithEvaluate is an auxilary function used by arithmetical pseudo
//instructions to carry out the evaluation of expressions.
//
int32 arithEvaluate(PrologValue& pval);

public:
//
// psi_is(Out, Exp)
// mode(out,in)
//
ReturnValue psi_is(Object *& , Object *& );

//
// psi_less(A, B)
// mode(in,in)
// true iff A < B
//
ReturnValue psi_less(Object *& , Object *& );

//
// psi_lesseq(A, B)
// mode(in,in)
// true iff A <= B
//
ReturnValue psi_lesseq(Object *& , Object *& );

//
// psi_add(A,B,Sum)
// mode(in,in,out)
// Sum = A + B
//
ReturnValue psi_add(Object *& , Object *& , Object *& );

//
// psi_subtract(A,B,Diff)
// mode(in,in,out)
// Diff = A - B
//
ReturnValue psi_subtract(Object *& , Object *& , Object *& );

//
// psi_increment(A,B)
// mode(in,out)
// B = A + 1
//
ReturnValue psi_increment(Object *& , Object *& );

//
// psi_decrement(A,B)
// mode(in,out)
// B = A - 1
//
ReturnValue psi_decrement(Object *& , Object *& );

#endif // ARITHMETIC_H

