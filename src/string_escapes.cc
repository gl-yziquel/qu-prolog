// string_escapes.cc - Get string from a string stream.
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
// $Id: string_escapes.cc,v 1.7 2005/03/08 00:35:14 qp Exp $

#include <sstream>

#include "atom_table.h"
#include "io_qp.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern IOManager *iom;

//
// psi_stream_to_chars(stream_index, variable)
// Get the list of characters from a string stream.
//
Thread::ReturnValue
Thread::psi_stream_to_chars(Object *& stream_arg,
			    Object *& char_list_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);

  //
  // Converting the string to a list of characters.
  //
  Object* tail = AtomTable::nil;
  int size = static_cast<int>(stream->str().length());
  if (size > 0)
    {
      string data = stream->str();
      for (int i = size; i > 0; i--)
	{
	  Cons* temp = heap.newCons();
	  temp->setTail(tail);
	  temp->setHead(heap.newNumber(data[i - 1]));
	  tail = temp;
	}
    }
  
  //
  // Return the list of characters.
  //
  char_list_arg = tail;

  return RV_SUCCESS;
}

//
// psi_stream_to_atom(stream_index, variable)
// Get an atom from a string stream.
//
Thread::ReturnValue
Thread::psi_stream_to_atom(Object *& stream_arg, Object *& atom_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);

  //
  // Return the atom.
  //
  int size = static_cast<int>(stream->str().length());
  if (size == 0)
    {
      atom_arg = atoms->add("");
    }
  else
    {
      string data = stream->str();
      char* buff = new char[size+1];
      for (int i = 0; i < size; i++)
	{
	  buff[i] = data[i];
	}
      buff[size] = '\0';
      atom_arg = atoms->add(buff);
      delete buff;
    }

  return RV_SUCCESS;
}






