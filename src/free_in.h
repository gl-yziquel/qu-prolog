// free_in.h -	"free_in" escape test functions.
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
// $Id: free_in.h,v 1.2 2001/09/20 03:22:06 qp Exp $

#ifndef	FREE_IN_H
#define	FREE_IN_H

public:
//
// psi_not_free_in(object_variable, term)
// Execute the not free in constraint.  The problem can succeed, fail or delay.
// mode(in,in)
//
ReturnValue	psi_not_free_in(Object *& , Object *& );

//
// psi_not_free_in_var_simplify(object_variable, var)
// Simplify the substitution associated with var and apply not free in.
//
ReturnValue	psi_not_free_in_var_simplify(Object *& , Object *& );

ReturnValue psi_addExtraInfoToVars(Object*&);

//
// Call notFreeInNFISimp
// mode(in,in)
//
ReturnValue psi_not_free_in_nfi_simp(Object*&, Object*&);  

//
// is_not_free_in
// mode(in,in)
//
ReturnValue psi_is_not_free_in(Object*&, Object*&);

//
// is_free_in
// mode(in,in)
//
ReturnValue psi_is_free_in(Object*&, Object*&);
      
#endif	// FREE_IN_H
