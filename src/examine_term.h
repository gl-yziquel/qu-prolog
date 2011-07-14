// examine_term.h - The QU-Prolog functions which have to do with examining
//                  or testing a term.
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: examine_term.h,v 1.4 2006/02/06 00:51:38 qp Exp $

#ifndef EXAMINE_TERM_H
#define EXAMINE_TERM_H

//
// psi_collect_vars(term, list)
// Collect all the variables (and object_variables) in term into list
// mode(in,out)
//
ReturnValue	psi_collect_vars(Object *& , Object *& );

//
// psi_var(term)
// True if term is a variable, false otherwise
// mode(in)
//
ReturnValue	 psi_var(Object *& );

//
// psi_atom(term)
// True if term X0 is an atom, false otherwise
// mode(in)
//
ReturnValue 	psi_atom(Object *& );

//
// psi_integer(term)
// True if term is an integer, false otherwise
// mode(in)
//
ReturnValue psi_integer(Object *& );

//
// psi_float(term)
// True if term is a float, false otherwise
// mode(in)
//
ReturnValue psi_float(Object *& );

//
// psi_atomic(term)
// True if term is atomic, false otherwise
// mode(in)
//
ReturnValue psi_atomic(Object *& );

//
// psi_any_variable(term)
// True if term is a variable or object variable, false otherwise
// mode(in)
//
ReturnValue psi_any_variable(Object *& );

//
// psi_simple(term)
// True if term is any variable or atomic, false otherwise
// mode(in)
//
ReturnValue psi_simple(Object *& );

//
// psi_nonvar(term)
// True if term is not a variable, false otherwise
// mode(in)
//
ReturnValue psi_nonvar(Object *& );

//
// psi_std_var(term)
// True if term is a variable with no subs, false otherwise
// mode(in)
//
ReturnValue psi_std_var(Object *& );

//
// psi_std_compound(term)
// True if term is compound with an atom functor, false otherwise
// mode(in)
//
ReturnValue psi_std_compound(Object *& );

//
// psi_std_nonvar(term)
// True if term is atomic or std_compound, false otherwise
// mode(in)
//
ReturnValue psi_std_nonvar(Object *& );

//
// psi_list(term)
// True if term is a list, false otherwise
// mode(in)
//
ReturnValue psi_list(Object *& );

// psi_string(term)
// True if term is a string, false otherwise
// mode(in)
//
ReturnValue psi_string(Object *& object1);

//
// psi_fast_simplify(term, simpterm)
// do a simple term simplification
// mode(in, out)
//
ReturnValue psi_fast_simplify(Object *& , Object *& );

ReturnValue psi_hash_variable(Object *& , Object *& );

#endif // EXAMINE_TERM_H
