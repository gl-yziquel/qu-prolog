// state.h - Save and restore state predicates.
//          - Manage global state variables
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
// $Id: state.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef STATE_H
#define STATE_H

public:
//
// psi_save(filename)
// Save the state of the execution into the "filename".
// mode(in)
//
ReturnValue psi_save(Object *&);

//
// psi_restore(filename)
// Restore the state of the execution from the "filename".
// mode(in)
//
ReturnValue psi_restore(Object *&);

// psi_global_state_set(key, value)
// Assign a value for a global state entry.
// mode(in,in)
//
ReturnValue psi_global_state_set(Object *&, Object *&);

// psi_global_state_lookup(key, value)
// Lookup a value for a global state entry.
// mode(in,out)
//
ReturnValue psi_global_state_lookup(Object *&, Object *&);

// psi_global_state_increment(key, value)
// Increment the value for a global state entry and return the new value.
// mode(in,out)
//
ReturnValue psi_global_state_increment(Object *&, Object *&);

// psi_global_state_decrement(key, value)
// Decrement the value for a global state entry and return the new value.
// mode(in,out)
//
ReturnValue psi_global_state_decrement(Object *&, Object *&);

#endif // STATE_H
