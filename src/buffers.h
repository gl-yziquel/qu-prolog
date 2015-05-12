// buffers.h - Qu-Prolog buffer management.
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: buffers.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	BUFFERS_H
#define	BUFFERS_H

public:	
//
// psi_alloc_buffer(buffer)
// Return the allocated buffer.
// mode(out)
//
ReturnValue psi_alloc_buffer(Object *&);


//
// psi_dealloc_buffer(buffer)
// Trim scratchpad and deallocate the buffer.
// mode(in,in)
//
ReturnValue psi_dealloc_buffer(Object *&);

//
// psi_copy_term_from_buffer(buffer, term)
// Copy the term from the start of the buffer to the heap and return
// the copied term.
// mode(in, out)
//
ReturnValue 
psi_copy_term_from_buffer(Object *&, Object *&);

//
// psi_copy_to_buffer_tail(buffer, term, share)
// Copy the term to the buffer and add to the end of the buffer list.
// The term will be shared if share is true.
// mode(in, in, in)
//
ReturnValue
psi_copy_to_buffer_tail(Object *&, Object *&, Object *&);

//
// psi_copy_obvar_to_buffer_tail(buffer, obvar)
// Copy the obvar to the buffer and add to the end of the buffer list.
// The obvar is not dereferenced.
// mode(in, in)
//
ReturnValue
psi_copy_obvar_to_buffer_tail(Object *& , Object *&);

//
// psi_make_sub_from_buffer(buffer, term, substitution)
// The buffer contains a list representing a substitution block.
// A substitution block is built on the heap from shared copies of the domain
// and range elements in the buffer. The substitution block is turned into
// a substitution block list and applied to term to produce substitution.
//
// mode(in, in, out)
//
ReturnValue
psi_make_sub_from_buffer(Object *&, Object *&, Object *&);

//
// psi_buffer_set_domains_apart(buffer, obvar)
// Make all the domain elements in the sub in the buffer different from obvar.
//
// mode(in, in)
//
ReturnValue
psi_buffer_set_domains_apart(Object *& object1, Object *& object2);

//
// Copy a term directly in the heap.
//
// mode(in, out)
//
ReturnValue
psi_copy_term(Object *&, Object *&);

#endif  // BUFFERS_H









