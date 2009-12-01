// bios.h - Basic I/O.
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: bios.h,v 1.2 2002/06/04 04:08:14 qp Exp $

#ifndef BIOS_H
#define BIOS_H

public:
//
// psi_get_char(stream_index, variable)
// Get the next character from the input stream.
// mode(in,out)
//
ReturnValue psi_get_char(Object *&, Object *&);

//
// psi_put_char(stream_index, character)
// Put the character into the output stream.
// mode(in,in)
//
ReturnValue psi_put_char(Object *&, Object *&);

//
// psi_get_code(stream_index, variable)
// Get the next character from the input stream.
// mode(in,out)
//
ReturnValue psi_get_code(Object *&, Object *&);

//
// psi_put_code(stream_index, byte)
// Put the byte into the output stream.
// mode(in,in)
//
ReturnValue psi_put_code(Object *&, Object *&);

//
// psi_get_line(stream_index, variable)
// Get the next line from the input stream.
// The newline character is consumed but not added to the return
// value.
// mode(in,out)
//

ReturnValue psi_get_line(Object *& stream_arg, Object *& code_list);  

//
// psi_put_line(stream_index, list)
// Put the ASCII list to the stream - add a newline character.
//
// mode(in, in)

ReturnValue psi_put_line(Object *& stream_arg, Object *& code_list);

#endif // BIOS_H























