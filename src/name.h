// name.h - Functions which build up a string which corresponds to a 
//          given list, or build up a list whose elements correspond 
//          to a given name.
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
// $Id: name.h,v 1.2 2006/02/01 04:26:02 qp Exp $

#ifndef	NAME_H
#define	NAME_H

public:

//void addEscapes(string& str, char quote);

//void removeEscapes(string& str, char quote);

//
// psi_atom_codes(atom, var)
// Convert an atom to a list of character codes.
// mode(in,out)
//
ReturnValue	psi_atom_codes(Object *& , Object *& );

//
// psi_codes_atom(list integer, var)
// Convert from a list of character codes to an atom.
// mode(in,out)
//
ReturnValue	psi_codes_atom(Object *& , Object *& );

//
// psi_char_code(char, var)
// Convert a character to its character code.
// mode(in,out)
//
ReturnValue	psi_char_code(Object *& , Object *& );
//
// psi_code_char(integer, var)
// Convert a character code to its character.
// mode(in,out)
//
ReturnValue	psi_code_char(Object *& , Object *& );

//
// psi_number_codes(number, list)
// Convert number to ASCII representation
// mode(in,out)
//
ReturnValue     psi_number_codes(Object *& , Object *& );

//
// psi_codes_number(number, list)
// Convert a list (an ASCII representation of a number) iinto that number
// mode(in,out)
//
ReturnValue     psi_codes_number(Object *& , Object *& );

#endif // NAME_H
