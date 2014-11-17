// write.h - Different specialised versions of write for atoms, integers, and
//	     variables.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: write.h,v 1.5 2005/03/27 22:07:43 qp Exp $

#ifndef WRITE_H
#define WRITE_H

private:
void writeVarName(Object* ref, NameGen,
		  word32& counter, QPStream *stream);

public:
//
// Different specialised versions of write for atoms.
//

//
// psi_write_atom(stream_index, atom)
// Default method for writing atoms.  The string is written without any
// processing.
// mode(in,in)
// 
ReturnValue psi_write_atom(Object *& , Object *& );

//
// psi_writeq_atom(stream_index, atom)
// The string is written with quotes whenever it is needed.
// mode(in,in)
// 
ReturnValue psi_writeq_atom(Object *& , Object *& );

//
// psi_write_integer(stream_index, integer)
// Write for integers.
// mode(in,in)
//
ReturnValue psi_write_integer(Object *& , Object *& );

//
// psi_write_float(stream_index, float)
// Write for floats.
// mode(in,in)
//
ReturnValue psi_write_float(Object *& , Object *& );

//
// psi_write_string(stream_index, string)
// Write for strings.
// mode(in,in)
//
ReturnValue psi_write_string(Object *& object1, Object *& object2);

//
// psi_writeq_string(stream_index, string)
// Write for strings - quotes added.
// mode(in,in)
//
ReturnValue psi_writeq_string(Object *& object1, Object *& object2);

//
// Different specialised versions of write for variables.
//

//
// psi_write_var(stream_index, variable)
// Default method for writing variables.  If the variable has a name, use the
// name.  Otherwise, the location of the variable is written as a base 16 
// number with '_' preceding it.
// mode(in,in)
//
ReturnValue psi_write_var(Object *& , Object *& );

//
// psi_writeR_var(stream_index, variable)
// Write the assigned name for the variable.
// mode(in,in)
//
ReturnValue psi_writeR_var(Object *& , Object *& );

//
// Different specialised versions of write for object variables.
//

//
// psi_write_object_variable(stream_index, object_variable)
// Default method for writing object variables.  If the variable has a name,
// use the name.  Otherwise, the location of the variable is written as a base
// 16 number with '_x' preceding it.
// mode(in,in)
//
ReturnValue psi_write_object_variable(Object *& , Object *& );

//
// psi_writeR_object_variable(stream_index, object_variable)
// Write the assigned name for the object variable.
// mode(in,in)
//
ReturnValue psi_writeR_object_variable(Object *& , Object *& );

//
// psi_writeq_object_variable(stream_index, object_variable)
// Write the assigned name for the object variable.
// Quote it if there's anything nasty inside.
//
ReturnValue psi_writeq_object_variable(Object *& , Object *& );

//
// A low-level dump of the term
//
ReturnValue psi_debug_write(Object *& );

#endif // WRITE_H
