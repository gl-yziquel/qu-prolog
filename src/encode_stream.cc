// encode_stream.cc - Term encoding and decoding.
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
// $Id: encode_stream.cc,v 1.5 2002/11/13 04:04:15 qp Exp $

#include <iostream>
#include <string.h>

#include "config.h"

#include "atom_table.h"
#include "is_ready.h"
#include "thread_qp.h"
#include "scheduler.h"

extern AtomTable *atoms;
extern IOManager *iom;
extern Scheduler *scheduler;

//
// psi_encoded_write(stream, term, atom)
// Encode the term and write the result to the stream.
//
Thread::ReturnValue
Thread::psi_encoded_write(Object *& stream_arg,
			  Object *& term_arg,
			  Object *& remember_names_arg)
{
  Object* argS = heap.dereference(stream_arg);
  Object* argT = term_arg;
  Object* argRN = heap.dereference(remember_names_arg);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, argS, 1, stream);

  if (argRN->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  if (!argRN->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }

  // IS_READY_STREAM(stream, -1);
  
  EncodeWrite ew(*this,
		 heap,
		 *stream,
		 argT,
		 *atoms,
		 atoms->atomToBool(argRN),
		 names);

  return BOOL_TO_RV(ew.Success());
}

//
// psi_encoded_read(stream, variable, variable, atom)
// Encode the term and write the result to the stream.
//
Thread::ReturnValue
Thread::psi_encoded_read(Object *& stream_arg, Object *& term_arg,
			 Object *& object_variable_names_arg, 
			 Object *& remember_names_arg)
{
  Object* argS = heap.dereference(stream_arg);
  Object* argRN = heap.dereference(remember_names_arg);
 
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, argS, 1, stream);

  if (argRN->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  if (!argRN->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }

  IS_READY_STREAM(stream);

  EncodeRead er(*this,
		heap,
		*stream,
		term_arg,
		*atoms,
		atoms->atomToBool(argRN),
		names,
		object_variable_names_arg);
  return BOOL_TO_RV(er.Success());
}









