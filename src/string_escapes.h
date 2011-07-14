// string_escapes.h - Get string from a string stream.
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
// $Id: string_escapes.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef STRING_ESCAPES_H
#define STRING_ESCAPES_H

public:
//
// psi_stream_to_chars(stream_index, variable)
// Get the list of characters from a string stream.
// mode(in,out)
//
ReturnValue psi_stream_to_chars(Object *& , Object *& );

//
// psi_stream_to_atom(stream_index, variable)
// Get an atom from a string stream.
// mode(in,out)
//
ReturnValue psi_stream_to_atom(Object *& , Object *& );

//
// psi_stream_to_string(stream_index, variable)
// Get a string from a string stream.
//
ReturnValue psi_stream_to_string(Object *& stream_arg, Object *& string_arg);

//
// psi_list_to_string(list, variable)
// Convert a list into a string
//
ReturnValue psi_list_to_string(Object *& list_arg, Object *& string_arg);

//
// psi_string_to_atom(string, variable)
// Convert a string into an atom
//
ReturnValue psi_string_to_atom(Object *& string_arg, Object *& atom_arg);

//
// psi_atom_to_string(atom, variable)
// Convert an atom into a string
//
ReturnValue psi_atom_to_string(Object *& atom_arg, Object *& string_arg);

//
// psi_string_length(string, variable)
// Get the length of a string
//
ReturnValue psi_string_length(Object *& string_arg, Object *& length_arg);

//
// psi_string_concat(string, string, variable)
// Concatentate 2 strings
//
ReturnValue psi_string_concat(Object *& string1_arg, Object *& string2_arg, 
			      Object *& concat_arg);

//
// psi_split_string(string, integer, variable, variable)
// Split a string at the given position
//
ReturnValue psi_split_string(Object *& string_arg, Object *& pos_arg, 
			     Object *& split1_arg, Object *& split2_arg);



#endif // STRING_ESCAPES_H
