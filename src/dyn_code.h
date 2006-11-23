// dyn_code.h - Dynamic code area management.
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
// $Id: dyn_code.h,v 1.4 2005/11/06 22:59:16 qp Exp $

#ifndef	DYN_CODE_H
#define	DYN_CODE_H

//
// psi_code_top(variable)
// Return the top of the code area.
// mode(out)
//
ReturnValue psi_code_top(Object*& object1);

//
// psi_get_opcode(opcode, buffer, offset)
// Get an opcode from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_opcode(Object*& object1, Object*& object2, 
			   Object*& object3);

//
// psi_get_const(constant, buffer, offset)
// Get a constant from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_const(Object*& object1, Object*& object2, 
			  Object*& object3);

//
// psi_get_integer(constant, buffer, offset)
// Get an integer from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_integer(Object*& object1, Object*& object2, 
			    Object*& object3);

//
// psi_get_double(constant, buffer, offset)
// Get a double from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_double(Object*& object1, Object*& object2, 
                           Object*& object3);


//
// psi_get_number(number, buffer, offset)
// Get a number from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_number(Object*& object1, Object*& object2, 
			   Object*& object3);

//
// psi_get_address(address, buffer, offset)
// Get an address from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_address(Object*& object1, Object*& object2, 
			    Object*& object3);

//
// psi_get_offset(offset, buffer, offset)
// Get an offset from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_offset(Object*& object1, Object*& object2, 
			   Object*& object3);

//
// psi_get_pred(predicate atom, buffer, offset)
// Get a predicate atom from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_pred(Object*& object1, Object*& object2, Object*& object3);

//
// psi_get_entry(offset, predicate, predtype)
// Get the entry point to a predicate.
// mode(out,in, out)
//
ReturnValue psi_get_entry(Object*& object1, Object*& object2, 
			  Object*& object3);

//
// psi_reset_entry(predicate, arity)
// Abolish the predicate definition. 
// mode(in,in)
//
ReturnValue psi_reset_entry(Object*& object1, Object*& object2);

// psi_assert(Head, Assembled, FirstLast, Ref).
// mode(in,in,in,out).
//
ReturnValue psi_assert(Object*& object1, Object*& object2, 
		       Object*& object3, Object*& object4);

// psi_retract(Ref).
// retract clause with reference Ref.
// mode(in,in).
//
ReturnValue psi_retract(Object*& object1);

// Get the timestamp for a predicate
// mode psi_predicate_stamp(in,in,out)
//
ReturnValue psi_predicate_stamp(Object*& object1, Object*& object2,
                            Object*& object3);
//
// psi_dynamic(pred, arity, indexArg, hashtablesize)
// Declare pred/arity as a dynamic predicate with indexArg (default = 1)
// and hashtablesize (default = 2)
// mode(in,in,in,in).
ReturnValue psi_dynamic(Object*& object1, Object*& object2, 
			Object*& object3, Object*& object4);

//
// psi_get_dynamic_chain(predicate, chain)
// Get the entry point to a predicate.
// mode(in, out)
//
ReturnValue psi_get_dynamic_chain(Object*& object1, Object*& object2);

//
// psi_get_first_clause(chain, time, ref, more)
// Get the first linkblock ptr for the chain
// more is true if there are subsequent clauses
//
ReturnValue psi_get_first_clause(Object*& object1, Object*& object2,
				 Object*& object3, Object*& object4);
//
// psi_get_next_clause(ptr, time, next, more)
// Get the next linkblock ptr for ptr.
// mode(in, out, out)
//
ReturnValue psi_get_next_clause(Object*& object1, Object*& object2,
				Object*& object3, Object*& object4);


//
// psi_get_next_clause(link, nextlink)
// get the next link in the clause linking chain
// mode(in,out)
//
//ReturnValue psi_get_next_clause(Object*& object1, Object*& object2);

#endif	// DYN_CODE_H



