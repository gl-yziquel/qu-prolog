// check.h - Useful argument checking macros. Used in pseudo-instructions.
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
// $Id: check.h,v 1.5 2005/03/08 00:35:00 qp Exp $

#ifndef	CHECK_H
#define	CHECK_H

// #include "atom_table.h"


#define DECODE_STREAM_ARG(heap, iom, cell, arg_num, stream, dir)	\
  do {									\
    const ErrorValue ev_input =						\
      (heap).decode_stream_input(iom, cell, &stream);			\
    if (ev_input == EV_NO_ERROR)					\
      {									\
	dir = INPUT;							\
      }									\
    else if (ev_input == EV_NOT_PERMITTED)				\
      {									\
	const ErrorValue ev_output =					\
          (heap).decode_stream_output(iom, cell, &stream);		\
	if (ev_output == EV_NO_ERROR)					\
	  {								\
	    dir = OUTPUT;						\
	  }								\
	else								\
	  {								\
	    PSI_ERROR_RETURN(ev_output, arg_num);			\
	  }								\
      }									\
    else								\
      {									\
	PSI_ERROR_RETURN(ev_input, arg_num);				\
      }									\
  } while (0)

#define DECODE_STREAM_OUTPUT_ARG(heap, iom, cell, arg_num, stream)	   \
  do {									   \
    const ErrorValue ev = (heap).decode_stream_output(iom, cell, &stream); \
    if (ev != EV_NO_ERROR)						   \
      {									   \
	PSI_ERROR_RETURN(ev, arg_num);					   \
      }									   \
  } while (0)

#define DECODE_STREAM_INPUT_ARG(heap, iom, cell, arg_num, stream)	  \
  do {									  \
    const ErrorValue ev = (heap).decode_stream_input(iom, cell, &stream); \
    if (ev != EV_NO_ERROR)						  \
      {									  \
	PSI_ERROR_RETURN(ev, arg_num);					  \
      }									  \
  } while (0)

#define CHECK_NUMBER_ARG(cell, arg_num)		\
  do {						\
    if ((cell)->isVariable())			\
      {						\
	PSI_ERROR_RETURN(EV_INST,		\
			 arg_num);		\
      }						\
    if (!(cell)->isNumber())			\
      {						\
	PSI_ERROR_RETURN(EV_TYPE,		\
			 arg_num);		\
      }						\
  } while (0)

#define CHECK_ATOM_ARG(cell, arg_num)		\
  do {						\
    if ((cell)->isVariable())			\
      {						\
	PSI_ERROR_RETURN(EV_INST, arg_num);	\
      }						\
    else if (!(cell)->isAtom())			\
      {						\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);	\
      }						\
  } while (0)

#define CHECK_ATOMIC_ARG(cell, arg_num)			\
  do {							\
    if ((cell)->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (!(cell)->isAtom() && !(cell)->isNumber())	\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
  } while (0)

#define CHECK_VARIABLE_ARG(heap, prolog_value, arg_num, var)	\
do {								\
  PrologValue prolog_value(var);				\
  (heap).prologValueDereference(prolog_value);				\
  if (!(prolog_value).getTerm()->isVariable())			\
    {								\
      PSI_ERROR_RETURN(EV_INST, arg_num);			\
    }								\
} while (0)

#define DECODE_SEND_OPTIONS_ARG(heap, cell, arg_num,		\
				remember_names, encode)		\
  do {								\
    const bool result =					\
      (heap).decode_send_options(cell,				\
				 remember_names, encode);	\
    if (!result)					\
      {								\
        PSI_ERROR_RETURN(EV_TYPE, arg_num);			\
      }								\
  } while (0)

#define DECODE_RECV_OPTIONS_ARG(heap, cell, arg_num,			\
			       remember_names, peek, encode)		\
  do {									\
    const ErrorValue result =						\
      (heap).decode_recv_options(cell, remember_names, peek, encode);	\
    if (result != EV_NO_ERROR)						\
      {									\
        PSI_ERROR_RETURN(result, arg_num);				\
      }									\
  } while (0)

#define CHECK_ATOM_LIST_ARG(heap, cell, arg_num)	\
  do {							\
    size_t length = 0;					\
    if ((cell)->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (! (heap).check_atom_list(cell, length))	\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
  } while (0)

#define DECODE_BOOLEAN_ARG(atoms, cell, arg_num, b)	\
  do {							\
    if ((cell)->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (! (cell)->isAtom())				\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    b = (atoms).atomToBool(cell);			\
  } while (0)

public:
ErrorValue decode_stream(IOManager&, Object*, QPStream **,
			 const IODirection);

bool check_functor(Object*, Atom*, const word32);

ErrorValue decode_stream_output(IOManager&, Object*, QPStream **);
ErrorValue decode_stream_input(IOManager&, Object*, QPStream **);

ErrorValue decode_nonneg_int(Object*, int&);

//
// Check the options associated with outgoing 
// TCP and IPC communication.
//
bool decode_send_options(Object*, bool&, bool&);

//
// Decode the options associated with incoming
// TCP and IPC/ICM communication.
//
bool decode_recv_options(Object*, Object*&, Object*&, Object*&);

//
// Decode the options associated with incoming
// TCP and IPC/ICM communications.
//
ErrorValue decode_recv_options(Object*, bool&, bool&, bool&);


bool check_atom_list(Object*, size_t&);

#endif	// CHECK_H
