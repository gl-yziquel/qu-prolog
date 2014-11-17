// object_variable.h - Routines for manipulating object variables.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: object_variable.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	OBJECT_VARIABLE_H
#define	OBJECT_VARIABLE_H

//
// psi_object_variable(term)
// Succeeds if term is an object variable.
// mode(in)
//
ReturnValue 	psi_object_variable(Object *&);

//
// psi_local_object_variable(term)
// Succeeds if term is a local object variable.
// mode(in)
//
ReturnValue	psi_local_object_variable(Object *&);

//
// psi_new_object_variable(variable)
// Return a new object variable.
// mode(out)
//
ReturnValue	psi_new_object_variable(Object *&);

//
// psi_is_distinct(object_variable1, object_variable2)
// Succeeds iff object_variable1 and object_variable2 are distinct object vars
// mode(in,in)
//
ReturnValue 	psi_is_distinct(Object *&, Object *&);

//
// psi_get_distinct(object_variable, variable)
// Retrieve the distinctness information under object_variable.
// mode(in,out)
//
ReturnValue	psi_get_distinct(Object *&, Object *&);

//
// psi_object_variable_name_to_prefix(atom, atom)
// Strip off an object variable suffix.
// mode(in,out)
//
ReturnValue	psi_object_variable_name_to_prefix(Object *&, Object *&);

//
// psi_valid_object_variable_prefix(atom)
// Returns true if the atom is a valid object_variable prefix.
// mode(in)
//
ReturnValue	psi_valid_object_variable_prefix(Object *&);

#endif	// OBJECT_VARIABLE_H
