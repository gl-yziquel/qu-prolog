// compare.h - Contains a function which compares the 2 terms
//             passed to it and returns the result of the 
//             comparison in X2.
//
// ##Copyright##
// 
// Copyright (C) 2000, 20001
// Software Verification Research Centre
// The University of Queensland
// Australia 4072
// 
// email: svrc@it.uq.edu.au
// 
// The Qu-Prolog 6.0 System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000,2001 by The University of Queensland, 
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
// 	written consent from the SVRC; and
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
// For information on commercial use of this software contact the SVRC.
// 
// ##Copyright##
//
// $Id: compare.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef COMPARE_H
#define COMPARE_H

public:
//
// psi_compare_var(var1, var2, res)
// Return -1 if var1 is senior than var2.
// mode(in,in,out)
//
ReturnValue psi_compare_var(Object *& , Object *& , Object *& );

//
// psi_compare_atom(atom1, atom2, res)
// Return -1 if atom1 is less than atom2 alphabetically.
// mode(in,in,out)
//
ReturnValue psi_compare_atom(Object *& , Object *& , Object *& );

//
//  psi_compare_pointers(term1, term2)
//  Return true iff the pointers are identical.
//  mode(in,in)
//
ReturnValue psi_compare_pointers(Object *& , Object *& );

#endif // COMPARE_H






