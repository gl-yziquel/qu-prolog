// check.cc -
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
// $Id: check.cc,v 1.10 2003/04/21 06:11:12 qp Exp $

// #include "atom_table.h"
//#include "dereference.h"
#include "error_value.h"
#include "heap_qp.h"
#include "icm.h"
#include "icm_handle.h"

extern AtomTable *atoms;

ErrorValue
Heap::decode_stream(IOManager& iom,
		    Object* stream_cell,
		    QPStream **stream_handle,
		    const IODirection dir)
{
  DEBUG_ASSERT(dir == INPUT || dir == OUTPUT);

  QPStream *strmptr = NULL;

  if (stream_cell->isNumber())
    {
      const int stream_number = stream_cell->getNumber();
      if (stream_number < 0 || stream_number >= (int)NUM_OPEN_STREAMS)
	{
	  return EV_TYPE;
	}
      strmptr = iom.GetStream(stream_number);
      if (strmptr == NULL)
	{
	  return EV_TYPE;
	}
    }
  else if (stream_cell->isAtom())
    {
          
      if (stream_cell == AtomTable::stream_stdin ||
	  stream_cell == AtomTable::stream_user ||
	  stream_cell == AtomTable::stream_user_input)
	{
	  if (dir == INPUT)
	    {
	      strmptr = iom.StdIn();
	    }
	  else
	    {
	      return EV_NOT_PERMITTED;
	    }
	}
      else if (stream_cell == AtomTable::stream_stdout ||
	       stream_cell == AtomTable::stream_user ||
	       stream_cell == AtomTable::stream_user_output)
	{
	  if (dir == OUTPUT)
	    {
	      strmptr = iom.StdOut();
	    }
	  else
	    {
	      return EV_NOT_PERMITTED;
	    }
	}
      else if (stream_cell == AtomTable::stream_stderr ||
	       stream_cell == AtomTable::stream_user_error)
	{
	  if (dir == OUTPUT)
	    {
	     strmptr = iom.StdErr();
	    }
	  else
	    {
	      return EV_NOT_PERMITTED;
	    }
	}
      else
	{
	  return EV_VALUE;
	}
    }
  else if (stream_cell->isVariable())
    {
      return EV_INST;
    }
  else
    {
      return EV_TYPE;
    }
  
  if (strmptr == NULL)
    {
      return EV_VALUE;
    }
  else if (strmptr->Type() == SOCKET)
    {
      return EV_TYPE;
    }

  *stream_handle = strmptr;
  
  return EV_NO_ERROR;
}

ErrorValue
Heap::decode_stream_output(IOManager& iom,
			   Object* stream_cell,
			   QPStream **stream_handle)
{
  const ErrorValue ev = decode_stream(iom, stream_cell, stream_handle, OUTPUT);
  if (ev == EV_NO_ERROR)
    {
      if ((*stream_handle)->getDirection() != INPUT)
	{
	  return EV_NO_ERROR;
	}
      else 
	{
	  return EV_NOT_PERMITTED;
	}
    }
  else
    {
      return ev;
    }
}

ErrorValue
Heap::decode_stream_input(IOManager& iom,
			  Object* stream_cell,
			  QPStream **stream_handle)
{
  const ErrorValue ev = decode_stream(iom, stream_cell, stream_handle, INPUT);
  if (ev == EV_NO_ERROR)
    {
      if ((*stream_handle)->getDirection() != OUTPUT)
	{
	  return EV_NO_ERROR;
	}
      else 
	{
	  return EV_NOT_PERMITTED;
	}
    }
  else
    {
      return ev;
    }
}

ErrorValue
Heap::decode_nonneg_int(Object* integer_cell, int& integer)
{
  if (integer_cell->isVariable())
    {
      return EV_INST;
    }
  else if (integer_cell->isNumber())
    {
      integer = integer_cell->getNumber();
      if (integer < 0)
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

bool
Heap::check_functor(Object* structure,
		    Atom* name, const word32 arity)
{
  if (structure->isStructure() &&
      arity == OBJECT_CAST(Structure*, structure)->getArity())
    {
      return name == OBJECT_CAST(Structure*, structure)->getFunctor();
    }
  else
    {
      return false;
    }
}

bool
Heap::decode_send_options(Object* options,
			  bool& remember_names,
			  bool& encode)
{
  if (options->isVariable())
    {
      return false;
    }
  remember_names = true;
  encode = true;
  if (options == AtomTable::nil)
    {
      return true;
    }
  while(options->isCons())
    {
      Cons* l = OBJECT_CAST(Cons*, options);
      Object* head = l->getHead()->variableDereference();
      options = l->getTail()->variableDereference();
      if (!head->isStructure())
	{
	  return false;
	}
      Structure* st = OBJECT_CAST(Structure*, head);
      Object* func = st->getFunctor()->variableDereference();
      if (func == atoms->add("remember_names"))
	{
	  remember_names = (st->getArgument(1)->variableDereference() 
			    == AtomTable::success);
	}
      else if (func == atoms->add("encode"))
	{
	  encode = (st->getArgument(1)->variableDereference() 
			    == AtomTable::success);
	}
      else
	{
	  return false;
	}
    }

  if (options == AtomTable::nil)
    {
      return true;
    }
  else
    {
      return false;
    }
}

bool
Heap::decode_recv_options(Object* options,
			  Object*& remember_names,
			  Object*& peek,
			  Object*& encode)
{
  if (check_functor(options, AtomTable::tcp_recv_options, 3))
    {
      Structure* str = OBJECT_CAST(Structure*, options);
      
      remember_names = str->getArgument(1)->variableDereference();
      peek = str->getArgument(2)->variableDereference();
      encode = str->getArgument(3)->variableDereference();

      return true;
    }
  else
    {
      return false;
    }
}

ErrorValue
Heap::decode_recv_options(Object* options_object,
			  bool& remember_names,
			  bool& peek,
			  bool& encode)
{
  Object* remember_names_object;
  Object* peek_object;
  Object* encode_object;

  if (options_object->isVariable())
    {
      return EV_INST;
    }
  else if (decode_recv_options(options_object,
			       remember_names_object,
			       peek_object,
			       encode_object))
    {
      if (remember_names_object->isVariable())
	{
	  return EV_INST;
	}
      else if (remember_names_object->isAtom())
	{
	  remember_names = atoms->atomToBool(remember_names_object);
	}
      else
	{
	  return EV_TYPE;
	}

      if (peek_object->isVariable())
	{
	  return EV_INST;
	}
      else if (peek_object->isAtom())
	{
	  peek = atoms->atomToBool(peek_object);
	}
      else
	{
	  return EV_TYPE;
	}

      if (encode_object->isVariable())
	{
	  return EV_INST;
	}
      else if (encode_object->isAtom())
	{
	  encode = atoms->atomToBool(peek_object);
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
Heap::decode_icm_handle(AtomTable& atoms,
			Object*& handle_object,
			icmHandle& handle)
{
#ifdef ICM_DEF
  if (!handle_object->isStructure())
    {
      return false;
    }

  Structure* str = OBJECT_CAST(Structure*, handle_object);

  if (str->getArity() != 4 || str->getFunctor() != atoms.add("$icm_handle"))
    {
      return false;
    } 
  Object* target_object = str->getArgument(1)->variableDereference();
  Object* name_object = str->getArgument(2)->variableDereference();
  Object* home_object = str->getArgument(3)->variableDereference();
  Object* locations_object = str->getArgument(4)->variableDereference();

  size_t length = 0;

  if (! (target_object->isAtom() || target_object->isNumber()) ||
      ! name_object->isAtom() ||
      ! home_object->isAtom() ||
      ! check_atom_list(locations_object, length)) 
    {
      return false;
    }

  string target;
  if (target_object->isAtom())
    {
      ICMOutgoingTarget icm_outgoing_target(atoms.getAtomString(OBJECT_CAST(Atom*, target_object)));
      target = icm_outgoing_target.Target();
    }
  else
    {
      ICMOutgoingTarget icm_outgoing_target(target_object->getNumber());
      target = icm_outgoing_target.Target();
    }

  const char *name = atoms.getAtomString(OBJECT_CAST(Atom*, name_object));
  const char *home = atoms.getAtomString(OBJECT_CAST(Atom*, home_object));

  char **locations = new (char *)[length + 1];
  
  for (size_t i = 0;
       i < length;
       i++,
	 locations_object = OBJECT_CAST(Cons*, locations_object)->getTail()->variableDereference())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, locations_object)->getHead()->variableDereference()->isAtom());
      locations[i] = 
	atoms.getAtomString(OBJECT_CAST(Cons*, 
					locations_object)->getHead()->variableDereference());
    }
  
  locations[length] = NULL;
  
  handle = icmMakeHandle(const_cast<char *>(target.c_str()), 
			 const_cast<char *>(name),
			 const_cast<char *>(home),
			 length, locations);
  
  delete [] locations;
#if 0
  icmKeepHandle(handle);
#endif

  return true;
#else // ICM_DEF
  return false;
#endif // ICM_DEF
}

bool
Heap::check_atom_list(Object* atom_list_object,
		      size_t& length)
{
  length = 0;

  atom_list_object = atom_list_object->variableDereference();
  for (;atom_list_object->isNil() || atom_list_object->isCons();)
    {
      if (atom_list_object->isNil())
	{
	  return true;
	}
      else if (atom_list_object->isCons())
	{
	  if (! OBJECT_CAST(Cons*, atom_list_object)->getHead()->variableDereference()->isAtom())
	    {
	      return false;
	    }
	  length++;
	  atom_list_object = OBJECT_CAST(Cons*, atom_list_object)->getTail()->variableDereference();
	}
    }

  return false;
}






