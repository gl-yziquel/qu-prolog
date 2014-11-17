// temperature.h - routines for handling freeze and thaw.
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
// $Id: temperature.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	TEMPERATURE_H
#define	TEMPERATURE_H

public:

void freeze_thaw_sub(Object*, Object*&,  bool, bool);

void freeze_thaw_term(Object*, Object*&, bool, bool);

//
// psi_freeze_term(term)
// Set the temperature tag of all variables in term  to freeze.
// mode(in)
//
ReturnValue psi_freeze_term(Object *&);

//
// psi_freeze_term(term,list)
// Set the temperature tag of all variables in term  to freeze.
// All variables that are frozen by this operation are returned in list.
// mode(in,out)
//
ReturnValue psi_freeze_term(Object *&, Object *&);


//
// psi_thaw_term(term)
// Set the temperature tag of all variables in term  to thaw.
// mode(in)
//
ReturnValue psi_thaw_term(Object *&);

//
// psi_thaw_term(term,list)
// Set the temperature tag of all variables in term  to thaw.
// All variables that are frozen by this operation are returned in list.
// mode(in,out)
//
ReturnValue psi_thaw_term(Object *&, Object *&);

//
// psi_freeze_var(term)
// Set the temperature tag of a (object) variable to freeze.
// mode(in)
//
ReturnValue psi_freeze_var(Object *&);

//
// psi_thaw_var(term)
// Set the temperature tag of a (object) variable to thaw.
// mode(in)
//
ReturnValue psi_thaw_var(Object *&);

//
// psi_frozen_var(term)
// Succeed if the (object) variable is frozen.
// mode(in)
//
ReturnValue psi_frozen_var(Object *&);

//
// psi_thawed_var(term)
// Succeed if the (object) variable is thawed.
// mode(in)
//
ReturnValue psi_thawed_var(Object *&);

#endif	// TEMPERATURE_H
