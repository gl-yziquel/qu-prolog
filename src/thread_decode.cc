// thread_decode.cc - support for decoding thread info.
//
// ##Copyright##
// 
// Copyright (C) 2000, 20001
// Software Verification Research Centre
// The University of Queensland
// Australia 4072
// 
// email: svrc@it.uq.edu.au
// 
// The Qu-Prolog 6.0 System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000,2001 by The University of Queensland, 
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
// 	written consent from the SVRC; and
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
// For information on commercial use of this software contact the SVRC.
// 
// ##Copyright##
//
// $Id: thread_decode.cc,v 1.3 2001/11/21 00:21:17 qp Exp $

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
      const ThreadTableLoc loc = (ThreadTableLoc) (thread_cell->getNumber());

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
      const char *symbol = atoms->getAtomString(OBJECT_CAST(Atom*, thread_cell));
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

ErrorValue
decode_thread_conditions(Heap& heap, AtomTable& atoms,
			 Object * arg,
			 bool& db,
			 bool& record_db,
			 time_t& wait_time)
{
  if (heap.check_functor(arg, AtomTable::thread_wait_conditions, 3))
    {
      Structure* str = OBJECT_CAST(Structure*, arg);
      Object* db_cell 
	= str->getArgument(1)->variableDereference();
      Object* record_db_cell 
	= str->getArgument(2)->variableDereference();
      Object* wait_time_cell 
	= str->getArgument(3)->variableDereference();

      if (db_cell->isVariable() ||
	  record_db_cell->isVariable() ||
	  wait_time_cell->isVariable())
	{
	  return EV_INST;
	}

      if (db_cell->isAtom() &&
	  record_db_cell->isAtom() &&
	  heap.IsTimeout(wait_time_cell))
	{
	  db = atoms.atomToBool(db_cell);
	  record_db = atoms.atomToBool(record_db_cell);
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

bool
decode_defaults(Heap& heap, Object * sizes,
		Object *& heap_size,
		Object *& scratchpad_size,
		Object *& binding_trail_size,
		Object *& object_trail_size,
		Object *& ip_trail_size,
		Object *& tag_trail_size,
		Object *& ref_trail_size,
		Object *& env_size,
		Object *& choice_size,
		Object *& name_table_size,
		Object *& ip_table_size)
{
  if (heap.check_functor(sizes, AtomTable::thread_defaults, 11))
    {
      Structure* str = OBJECT_CAST(Structure*, sizes);
      heap_size = str->getArgument(1)->variableDereference();
      scratchpad_size = str->getArgument(2)->variableDereference();
      binding_trail_size = str->getArgument(3)->variableDereference();
      object_trail_size = str->getArgument(4)->variableDereference();
      ip_trail_size = str->getArgument(5)->variableDereference();
      tag_trail_size = str->getArgument(6)->variableDereference();
      ref_trail_size = str->getArgument(7)->variableDereference();
      env_size = str->getArgument(8)->variableDereference(); 
      choice_size = str->getArgument(9)->variableDereference();
      name_table_size = str->getArgument(10)->variableDereference();
      ip_table_size = str->getArgument(11)->variableDereference();

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
		int& object_trail_size,
		int& ip_trail_size,
		int& tag_trail_size,
		int& ref_trail_size,
		int& env_size,
		int& choice_size,
		int& name_table_size,
		int& ip_table_size)
{
  Object* heap_size_cell;
  Object* scratchpad_size_cell;
  Object* binding_trail_size_cell;
  Object* object_trail_size_cell;
  Object* ip_trail_size_cell;
  Object* tag_trail_size_cell;
  Object* ref_trail_size_cell;
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
			   object_trail_size_cell,
			   ip_trail_size_cell,
			   tag_trail_size_cell,
			   ref_trail_size_cell,
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
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, object_trail_size_cell,
				       object_trail_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, ip_trail_size_cell,
				       ip_trail_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, tag_trail_size_cell,
				       tag_trail_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, ref_trail_size_cell,
				       ref_trail_size, error);
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

