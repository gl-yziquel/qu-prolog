// env_var.h - Interface to environment variables. The name is env_var.h
// 		to avoid clashes with other environment files.
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
// $Id: env_var.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	ENV_VAR_H
#define	ENV_VAR_H

// @doc
// @pred env_getenv(Name, Value)
// @type env_getenv(string, string)
// @mode env_getenv(+, -) is semidet
//
// Looks up the Value associated with name, if any,
// in the process's environment. Succeeds if the name has
// a value in the environment, fails otherwise.
//
// @internaldoc
// Interfaces more or less directly with the getenv(3c) call.
// Implemented directly by pseudo-instruction.
// @end internaldoc
// @end doc
ReturnValue psi_env_getenv(Object *&, Object *&);

// @doc
// @pred env_putenv(Name, Value)
// @type env_putenv(string, string)
// @mode env_putenv(+, +) is det
//
// Sets the Value associated with Name in the process's environment.
// @internaldoc
// Interfaces more or less directly with the putenv(3c) call.
// Implemented directly by pseudo-instruction.
// @end internaldoc
// @end doc
ReturnValue psi_env_putenv(Object *&, Object *&);

#endif	// ENV_VAR_H
