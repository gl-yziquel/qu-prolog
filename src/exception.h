// exception.h - Define low level exception support routines.
//               The idea is evolved from IC-Prolog and made compatible with
//               Quintus Prolog.
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
// $Id: exception.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	EXCEPTION_H
#define	EXCEPTION_H

public:
//
// psi_get_catch(variable)
// Return the current value in the catch register.
// mode(in)
//
ReturnValue psi_get_catch(Object *& );

//
// psi_set_catch(choice point)
// Set the catch register with the given value.
// mode(in)
//
ReturnValue psi_set_catch(Object *& );

//
// psi_failpt_to_catch
// Transfer the value from currentChoicePoint to catch.
//
ReturnValue psi_failpt_to_catch(void);

//
// psi_catch_to_failpt
// Transfer the value from catch to currentChoicePoint.
// mode()
//
ReturnValue psi_catch_to_failpt(void);

//
// psi_psi_resume(state)
// Restore saved X regs and PC
// mode(in)
//
ReturnValue psi_psi_resume(Object *& );

#endif	// EXCEPTION_H

