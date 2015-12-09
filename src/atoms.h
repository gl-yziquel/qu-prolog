// atoms.h - Predicates for maniuplating atoms.
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
// $Id: atoms.h,v 1.2 2001/06/04 01:22:54 qp Exp $

#ifndef	ATOMS_H
#define	ATOMS_H

public:
//
// psi_atom_length(atom, variable)
// Work out the string length of an atom.
// mode(in,out)
//
ReturnValue psi_atom_length(Object *& , Object *& );

//
// psi_atom_concat2(atomic, atomic, atomic)
// Join the first 2 atomics to get the third.
// mode(in,in,out)
//
ReturnValue psi_atom_concat2(Object *& object1, Object *& object2, 
			     Object *& object3);
//
// psi_concat_atom(list of atomic, variable)
// Join a list of atomic together to form a new atom.
// mode(in,out)
//
ReturnValue psi_concat_atom(Object *& , Object *& );

//
// psi_concat_atom3(list of atomic, separator, ariable)
// Join a list of atomic together to form a new atom separating
// each atom with separator
// mode(in,in,out)
//
ReturnValue psi_concat_atom3(Object *& , Object *& , Object *& );

//
// psi_atom_search(atom1, start, atom2, variable)
// Return the location with atom1 where atom2 is located.
// mode(in,in,in,out)
//
ReturnValue psi_atom_search(Object *& , Object *& , Object *& , Object *& );

//
// psi_sub_atom(atom, start, length, variable)
// Return a new atom formed from the supplied atom.
// mode(in,in,in,out)
//
ReturnValue psi_sub_atom(Object *& , Object *& , Object *& , Object *& );

#endif	// ATOMS_H







