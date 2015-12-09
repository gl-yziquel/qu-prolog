// symbols.h - Contains a function which can be used to manage the access to
//	       symbol tables.
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
// $Id: symbols.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef SYMBOLS_H
#define SYMBOLS_H

//
// psi_get_atom_from_atom_table(integer, atom, integer)
// Return the next atom in the atom table.
// mode(in,out,out)
//
ReturnValue psi_get_atom_from_atom_table(Object *& , Object *& , Object *& );

//
// psi_get_pred_from_pred_table(integer, atom, integer)
// Return the next predicate in the predicate table.
// mode(in,out,out,out)
//
ReturnValue  psi_get_pred_from_pred_table(Object *& , Object *& , 
					  Object *& , Object *& );

//
// symtype outputs into  :
//  (0) If the predicate has no entry point defined.
//  (1) If the predicate is a dynamic predicate.
//  (2) If the predicate is a compiled predicate.
//  (3) If the predicate is an escape predicate.
// mode(in,in,out)
//
ReturnValue	psi_symtype(Object *& , Object *& , Object *& );

#endif // SYMBOLS_H
