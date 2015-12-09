// error_value.h -
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
// $Id: error_value.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	ERROR_VALUE_H
#define	ERROR_VALUE_H

// Ensure that this list stays up to date with respect to 
// library/psi_errors.ql.

enum ErrorValue {
  EV_NO_ERROR			= 0,	/* No error. */
  EV_INST			= 1,	/* Instantiation error. */
  EV_TYPE			= 2,	/* Type error. */
  EV_RANGE			= 3,	/* Out of range value. */
  EV_VALUE			= 4,	/* Bad value. */
  EV_ZERO_DIVIDE		= 5,	/* Division by zero. */
  EV_NOT_PERMITTED		= 6,	/* Not able to perform some operation. */
  EV_ALLOCATION_FAILURE		= 7,	/* Resource allocation failure. */
  EV_SYSTEM			= 8,	/* Operationg system call failure. */
  EV_UNIMPLEMENTED		= 9,	/* The operation requested isn't implemented yet. */
  EV_UNSUPPORTED		= 10	/* The operation requested is no longer supported */
};

#endif	// ERROR_VALUE_H

