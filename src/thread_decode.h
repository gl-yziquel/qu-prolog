// thread_decode.h - support for decoding thread information.
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
// $Id: thread_decode.h,v 1.6 2006/02/14 02:40:09 qp Exp $

#ifndef	THREAD_DECODE_H
#define	THREAD_DECODE_H

#include "global.h"
#include "thread_qp.h"
#include "thread_table.h"
#include "timeval.h"

#define DECODE_THREAD_DEFAULT_NONNEG_INT(heap, cell, integer, error)	\
  do {									\
    const ErrorValue ev = (heap).decode_nonneg_int(cell, integer);	\
    if (ev != EV_NO_ERROR)						\
      {									\
        return ev;							\
      }									\
  } while (0)

ErrorValue
decode_thread(Heap& heap,
	      Object * thread_cell,
	      ThreadTable& thread_table,
	      Thread **thread);

#define DECODE_THREAD_ARG(heap, cell, thread_table, arg_num, thread)	\
do {									\
  const ErrorValue result = decode_thread(heap, cell, thread_table, &thread);	\
  if (result == EV_INST)                                            \
    {                                                                   \
      PSI_ERROR_RETURN(EV_INST, 1);                                     \
    }                                                                   \
  if (result != EV_NO_ERROR)                                        \
    {                                                                   \
      return RV_FAIL;                                                   \
    }                                                                   \
} while (0)								\

ErrorValue
decode_thread_conditions(Heap& heap, AtomTable& atoms,
			 Object * arg,
			 bool& db,
			 double& wait_time);

#define DECODE_THREAD_CONDITIONS_ARG(heap, atoms, arg, arg_num,		\
				     db, wait_time)			\
do {									\
  const ErrorValue ev = decode_thread_conditions(heap, atoms, arg,	\
						 db, 			\
						 wait_time);		\
  if (ev != EV_NO_ERROR)						\
    {									\
      PSI_ERROR_RETURN(ev, arg_num);					\
    }									\
} while (0)

bool
decode_defaults(Heap& heap, Object * sizes,
		Object *& heap_size,
		Object *& scratchpad_size,
		Object *& binding_trail_size,
		Object *& other_trail_size,
		Object *& env_size,
		Object *& choice_size,
		Object *& name_table_size,
		Object *& ip_table_size);

ErrorValue
decode_defaults(Heap& heap,
		Object * sizes,
		int& heap_size,
		int& scratchpad_size,
		int& binding_trail_size,
		int& other_trail_size,
		int& env_size,
		int& choice_size,
		int& name_table_size,
		int& ip_table_size);

#define DECODE_DEFAULTS_ARG(heap, cell, arg_num,	\
			    heap_size,			\
			    scratchpad_size,		\
			    binding_trail_size,	       	\
			    other_trail_size,	       	\
			    env_size,			\
			    choice_size,		\
			    name_table_size,		\
			    ip_table_size)		\
do {							\
  const ErrorValue result =				\
    decode_defaults(heap, cell,				\
		    heap_size,				\
		    scratchpad_size,				\
		    binding_trail_size,				\
		    other_trail_size,				\
		    env_size,				\
		    choice_size,			\
		    name_table_size,			\
		    ip_table_size);			\
  if (result != EV_NO_ERROR)				\
    {							\
      PSI_ERROR_RETURN(result, arg_num);		\
    }							\
} while (0)

#endif	//THREAD_DECODE_H
