// thread_decode.cc - support for decoding thread info.
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
// $Id: thread_decode.cc,v 1.8 2006/02/14 02:40:09 qp Exp $

#include "thread_decode.h"


ErrorValue
decode_thread(Heap& heap,
	      Object * thread_cell,
	      ThreadTable& thread_table,
	      Thread **thread)
{
  if (thread_cell->isVariable())
    {
      return EV_INST;
    }
  else if (thread_cell->isNumber())
    {
      const ThreadTableLoc loc = (ThreadTableLoc) (thread_cell->getInteger());

      if (thread_table.IsValid(loc))
	{
	  *thread = thread_table.LookupID(loc);
	  if (*thread == NULL)
	    {
	      return EV_VALUE;
	    }
	  else
	    {
	      return EV_NO_ERROR;
	    }
	}
      else
	{
	  return EV_VALUE;
	}
    }
  else if (thread_cell->isAtom())
    {
      const char *symbol = OBJECT_CAST(Atom*, thread_cell)->getName();
      ThreadTableLoc id = thread_table.LookupName(symbol);
      if (id == (ThreadTableLoc) -1)
        {
          return EV_VALUE;
        }
      *thread = thread_table.LookupID(id);
      if (*thread == NULL)
        {
          return EV_VALUE;
        }
      else
        {
          return EV_NO_ERROR;
        }
    }
  else
    {
      return EV_TYPE;
    }
}

/*
ErrorValue
decode_thread_conditions(Heap& heap, AtomTable& atoms,
			 Object * arg,
			 bool& db,
			 double& wait_time)
{
  if (heap.check_functor(arg, AtomTable::thread_wait_conditions, 2))
    {
      Structure* str = OBJECT_CAST(Structure*, arg);
      Object* db_cell 
	= str->getArgument(1)->variableDereference();
      Object* wait_time_cell 
	= str->getArgument(2)->variableDereference();

      if (db_cell->isVariable() ||
	  wait_time_cell->isVariable())
	{
	  return EV_INST;
	}

      if (db_cell->isAtom() &&
	  heap.IsTimeout(wait_time_cell))
	{
	  db = atoms.atomToBool(db_cell);
	  wait_time = heap.DecodeTimeout(wait_time_cell);

	  return EV_NO_ERROR;
	}
      else
	{
	  return EV_TYPE;
	}
    }
  else
    {
      return EV_TYPE;
    }
}

*/

bool
decode_defaults(Heap& heap, Object * sizes,
		Object *& heap_size,
		Object *& scratchpad_size,
		Object *& binding_trail_size,
		Object *& other_trail_size,
		Object *& env_size,
		Object *& choice_size,
		Object *& name_table_size,
		Object *& ip_table_size)
{
  if (heap.check_functor(sizes, AtomTable::thread_defaults, 8))
    {
      Structure* str = OBJECT_CAST(Structure*, sizes);
      heap_size = str->getArgument(1)->variableDereference();
      scratchpad_size = str->getArgument(2)->variableDereference();
      binding_trail_size = str->getArgument(3)->variableDereference();
      other_trail_size = str->getArgument(4)->variableDereference();
      env_size = str->getArgument(5)->variableDereference(); 
      choice_size = str->getArgument(6)->variableDereference();
      name_table_size = str->getArgument(7)->variableDereference();
      ip_table_size = str->getArgument(8)->variableDereference();

      return true;
    }
  else
    {
      return false;
    }
}

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
		int& ip_table_size)
{
  Object* heap_size_cell;
  Object* scratchpad_size_cell;
  Object* binding_trail_size_cell;
  Object* other_trail_size_cell;
  Object* env_size_cell;
  Object* choice_size_cell;
  Object* name_table_size_cell;
  Object* ip_table_size_cell;
  
  if (sizes->isVariable())
    {
      return EV_INST;
    }
  else if (decode_defaults(heap, sizes,
			   heap_size_cell,
			   scratchpad_size_cell,
			   binding_trail_size_cell,
			   other_trail_size_cell,
			   env_size_cell,
			   choice_size_cell,
			   name_table_size_cell,
			   ip_table_size_cell))
    {
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, heap_size_cell,
				       heap_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, scratchpad_size_cell,
				       scratchpad_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, binding_trail_size_cell,
				       binding_trail_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, other_trail_size_cell,
				       other_trail_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, env_size_cell,
				       env_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, choice_size_cell,
				       choice_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, name_table_size_cell,
				       name_table_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, ip_table_size_cell,
				       ip_table_size, error);
		    
      return EV_NO_ERROR;
    }
  else
    {
      return EV_TYPE;
    }
}

