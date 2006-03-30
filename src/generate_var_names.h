// generate_var_names.h -
//
// ##Copyright##
// 
// Copyright (C) 2000-2004
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
// Copyright 2000-2004 by The University of Queensland, 
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
// $Id: generate_var_names.h,v 1.4 2006/03/30 22:50:30 qp Exp $

#ifndef GENERATE_VAR_NAMES_H
#define GENERATE_VAR_NAMES_H

public:
typedef Atom* (*NameGen)(Thread*, word32&);

//
// Generate a new name for variables.  Find one that is either not in use or
// generate a new variable name.
// The name sequence is:
// A, .., Z, A1, .., Z1, A2, .., Z2, ...
//
static Atom* GenerateVarName(Thread* threadPtr, word32& counter);

//
// Generate a new name for object variables.  Find one that is either not in
// use or generate a new variable name.
//
static Atom* GenerateObjectVariableName(Thread* threadPtr, word32& counter);

//
// Generate a new remembered name for object variables.  
// Find one that is either not in
// use or generate a new variable name.
//
static Atom* GenerateRObjectVariableName(Thread* threadPtr, word32& counter);

#endif // GENERATE_VAR_NAMES_H






