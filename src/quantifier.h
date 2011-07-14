// quantifier.h - routines for manipulating quantified term.
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: quantifier.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	QUANTIFIER_H
#define	QUANTIFIER_H

public:
//
// psi_quant(term)
// Succeeds if term is a quantified term.
// mode(in)
//
ReturnValue psi_quant(Object *&);

//
// psi_quantifier(term, quantifier)
// Return the quantifier of a quantified term.
// mode(in,out)
//
ReturnValue	psi_quantifier(Object *&, Object *&);

//
// psi_bound_var(term, variables)
// Return the bound variables of a quantified term.
// mode(in,out)
//
ReturnValue	psi_bound_var(Object *&, Object *&);

//
// psi_body(term, body)
// Return the body of a quantified term.
// mode(in,out)
//
ReturnValue	psi_body(Object *&, Object *&);

//
// psi_quantify(term, quantifier, variables, body)
// term is the quantified term made up from quantifier, variables and body.
// mode(in,in,in,in)
//
ReturnValue	psi_quantify(Object *&, Object *&, Object *&, Object *&);

//
// psi_check_binder(bound_list, object variables list)
// Ensure the object variables in the bound list mutually distinct and the 
// object variables in object variables list are distinct from those in bound
// list.
// mode(in,in)
//
ReturnValue	psi_check_binder(Object *&, Object *&);

#endif	// QUANTIFIER_H
