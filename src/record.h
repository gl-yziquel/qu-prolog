// record.h - A record style database.
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
// $Id: record.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	RECORD_H
#define	RECORD_H

public:
//
// psi_record_get_first_ref(atom, ref)
//
// Finds the first reference associated with the atom.
// mode(in,out)
//
ReturnValue psi_record_get_first_ref(Object *& , Object *& );

//
// psi_record_get_next_ref(ref, next)
//
// Looks up the next reference in the atom's association chain.
// mode(in,out)
//
ReturnValue psi_record_get_next_ref(Object *& , Object *& );

//
// psi_record_get_last_ref(atom, ref)
//
// Finds the last reference associated with the atom.
// mode(in,out)
//
ReturnValue psi_record_get_last_ref(Object *& , Object *& );

//
// psi_record_get_term(ref, string)
//
// Return the atom pointed to by the reference.
// mode(in,out)
//
ReturnValue psi_record_get_term(Object *& , Object *& );

//
// psi_record_record_first(atom, term, ref)
//
// Records the term in the first place associated with the atom.
// mode(in,in,out)
//
ReturnValue psi_record_record_first(Object *& , Object *& , Object *& );

//
// psi_record_record_last(atom, term, ref)
//
// Records the term in hte last place associated with the atom.
// mode(in,in,out)
//
ReturnValue psi_record_record_last(Object *& , Object *& , Object *& );

//
// psi_erase(ref)
//
// Erase the reference pointed to by ref.
// mode(in)
//
ReturnValue psi_erase(Object *& );

#endif	// RECORD_H
