// stream_escapes.cc - I/O stream manipulations.
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
// $Id: stream_escapes.cc,v 1.14 2005/11/26 23:34:31 qp Exp $

#include <errno.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "atom_table.h"
#include "io_qp.h"
#include "system_support.h"
#include "thread_qp.h"
#include "unify.h"

#ifdef ICM_DEF
#include "icm_handle.h"
extern ICMEnvironment *icm_environment;
#endif

extern AtomTable *atoms;
extern IOManager *iom;

//
// psi_get_open_streams(StreamList)
// Make a list of all the open stream nums.
// mode psi_get_open_streams(out)
//
Thread::ReturnValue
Thread::psi_get_open_streams(Object *& result)
{
  result = AtomTable::nil;
  for (u_int i = 0; i < NUM_OPEN_STREAMS; i++)
    {
      if (iom->GetStream(i) != NULL)
	{
	  Cons* list = heap.newCons(heap.newNumber(i), result);
	  result = list;
	}
    }
  return RV_SUCCESS;
}

//
// psi_open(file, iomode, var)
// Open the file for the specified mode.
//
Thread::ReturnValue
Thread::psi_open(Object *& filename_arg,
		 Object *& access_mode_arg,
		 Object *& stream_arg)
{
  Object* argF = heap.dereference(filename_arg);
  Object* argAM = heap.dereference(access_mode_arg);
  
  if (argF->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argF->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  if (argAM->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argAM->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const word32 mode = argAM->getNumber();
  
  if (!(mode <= AM_APPEND))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  //
  // Open the file.
  //
//PORT
//#ifdef WIN32
  // See comments in io.cc
//  string tempstr = wordexp(atoms->getAtomString(OBJECT_CAST(Atom*, argF)));
//  const char *file = tempstr.c_str();
//#else
//  const char *file = wordexp(atoms->getAtomString(OBJECT_CAST(Atom*, argF))).c_str();
//#endif
  string filename = atoms->getAtomString(OBJECT_CAST(Atom*, argF));
  wordexp(filename);
  char file[1024];
  strcpy(file, filename.c_str());


  switch (mode)
    {
    case AM_READ:
      {
	QPistream *stream = new QPistream(file);

	if (stream->bad())
	  {
	    delete stream;
	    PSI_ERROR_RETURN(EV_VALUE, 0);
	  }

	//
	// Return index of the stream.
	//
	stream_arg = heap.newNumber(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
      break;
    case AM_WRITE:
      {
	QPostream *stream = new QPostream(file, ios::out|ios::trunc);

	if (stream->bad())
	  {
	    delete stream;
	    PSI_ERROR_RETURN(EV_VALUE, 0);
	  }

	//
	// Return index of the stream.
	//
	stream_arg = heap.newNumber(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
      break;
    case AM_APPEND:
      {
	QPostream *stream = new QPostream(file, ios::out|ios::app);

	if (stream->bad())
	  {
	    delete stream;
	    PSI_ERROR_RETURN(EV_VALUE, 0);
	  }

	//
	// Return index of the stream.
	//
	stream_arg = heap.newNumber(iom->OpenStream(stream));
	return RV_SUCCESS;
	break;
      }
    }

  return RV_FAIL;
}

//
// psi_open_string(string, iomode, type, variable)
// Open a string stream.
//
Thread::ReturnValue
Thread::psi_open_string(Object *& string_arg,
			Object *& access_mode_arg,
			Object *& type_arg,
			Object *& stream_arg)
{
  Object* argS = heap.dereference(string_arg);
  Object* argAM = heap.dereference(access_mode_arg);
  Object* argT = heap.dereference(type_arg);

  if (argAM->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argAM->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  word32 mode = argAM->getNumber();
  
  if (!(mode <= AM_APPEND))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  switch (mode)
    {
    case AM_READ:
      {
	//
	// Check the string type and the string.
	//
	
	if (argS->isVariable())
	  {
	    PSI_ERROR_RETURN(EV_INST, 1);
	  }
	if (!argS->isAtom() && !argS->isCons())
	  {
	    PSI_ERROR_RETURN(EV_TYPE, 1);
	  }
	
	if (argT->isVariable())
	  {
	    PSI_ERROR_RETURN(EV_INST, 3);
	  }
	if (!argT->isShort())
	  {
	    PSI_ERROR_RETURN(EV_TYPE, 3);
	  }
	
	if (argT->getNumber() == 0)
	  {
	    QPistringstream *stream = new QPistringstream(atoms->getAtomString(OBJECT_CAST(Atom*, argS)));
	    
	    //
	    // Return the index of the stream.
	    //
	    stream_arg = heap.newNumber(iom->OpenStream(stream));
	    return RV_SUCCESS;
	  }
	else if (argT->getNumber() == 1)
	  {
	    //
	    // Open strstream for converting a list of characters
	    // to an array, and then for reading.
	    //
	    ostringstream *strstr = new ostringstream;

	    //
	    // Converting a list of characters to an array.
	    //
	    while (argS->isCons())
	      {
		Cons* list = OBJECT_CAST(Cons*, argS);
		Object* head = heap.dereference(list->getHead());
		
		if (!head->isShort())
		  {
		    PSI_ERROR_RETURN(EV_VALUE, 1);
		  }
		
		if (strstr->good() &&
		    strstr->put(head->getNumber()).fail())
		  {
		    delete strstr;
		    return RV_FAIL;
		  }
		argS = heap.dereference(list->getTail());
	      }
	    
	    assert(argS->isNil());
	    
	    QPistringstream *stream = new QPistringstream(strstr->str());
	    delete strstr;
	    //
	    // Return the index of the stream.
	    //
	    stream_arg = heap.newNumber(iom->OpenStream(stream));
	    return RV_SUCCESS;
	  }
	else
	  {
	    PSI_ERROR_RETURN(EV_VALUE, 3);
	  }
      }
    break;
    case AM_WRITE:
      {
	QPostringstream *stream = new QPostringstream;
	//
	// Return the index of the stream.
	//
	stream_arg = heap.newNumber(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
    break;
    }
  
  return RV_FAIL;
}

//
// psi_close(stream_index, force)
// Close the specified stream.
//
Thread::ReturnValue
Thread::psi_close(Object *& stream_arg,
		  Object *& force_arg)
{
  Object* strm = heap.dereference(stream_arg);
  Object* force = heap.dereference(force_arg);
  //
  // Check arguments.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, strm, 1, stream, dir);

  if (force->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!force->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  const word32 force_val = force->getNumber();     // PJR used??
  if (!(force_val <= 1))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  //stream->close();
  return BOOL_TO_RV(iom->CloseStream(strm->getNumber()));
}

//
// psi_current_input(variable)
// Return the current input stream index.
//
Thread::ReturnValue
Thread::psi_current_input(Object *& stream_arg)
{
  stream_arg = heap.newNumber(iom->CurrentInput());
  return RV_SUCCESS;
}

//
// psi_current_output(variable)
// Return the current output stream index.
//
Thread::ReturnValue
Thread::psi_current_output(Object *& stream_arg)
{
  stream_arg = heap.newNumber((word32) iom->CurrentOutput());
  return RV_SUCCESS;
}

//
// psi_set_input(stream_index)
// Switch current input stream to the new index.
//
Thread::ReturnValue
Thread::psi_set_input(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Change stream.
  //
  iom->SetCurrentInput(stream_object->getNumber());
  
  return RV_SUCCESS;
}

//
// psi_set_output(stream_index)
// Switch current output stream to the new index.
//
Thread::ReturnValue
Thread::psi_set_output(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Change stream.
  //
  iom->SetCurrentOutput(stream_object->getNumber());
  
  return RV_SUCCESS;
}

//
// psi_flush_output(stream_index)
// Flush the output stream.
//
Thread::ReturnValue
Thread::psi_flush_output(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Flush the output stream.
  //
  stream->flush();

  
  return RV_SUCCESS;
}

//
// psi_set_autoflush(stream)
// Set the output stream to be unbuffered - i.e. flushes at each output.
//
Thread::ReturnValue
Thread::psi_set_autoflush(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Set auto flush - fails if not an QPofdstream or an QPomstream
  //
  return BOOL_TO_RV(stream->set_autoflush());
}

//
// psi_at_end_of_stream(stream_index)
// Succeed if the input stream reaches the end of the stream.
//
Thread::ReturnValue
Thread::psi_at_end_of_stream(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);
  
  //
  // Check the input stream.
  //
  errno = 0;

  if (stream->isOutput())
    {
      return RV_FAIL;
    }
  else if (! stream->isReady())
    {
      return RV_FAIL;
    }
  else if (stream->eof() && errno == 0)
    {
      stream->clear(ios::failbit);
      return RV_SUCCESS;
    }

  if (errno == 4)
   {
     stream->clear();
   }
  return RV_FAIL;
}

//
// psi_past_end_of_stream(stream_index)
// Succeed if the input stream passes the end of the stream.
//
Thread::ReturnValue
Thread::psi_past_end_of_stream(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);
  
  //
  // Check the input stream.
  //
  if (stream->isOutput())
    {
      return RV_FAIL;
    }
  else
    {
      return BOOL_TO_RV(stream->fail());
    }
}

//
// psi_reset_stream(stream_index)
// Reset the input stream.
//
Thread::ReturnValue
Thread::psi_reset_stream(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, stream_object, 1, stream);

  //
  // Reset the input stream.
  //
  stream->clear();

  return RV_SUCCESS;
}

//
// psi_stream_position(stream_index, variable)
// Get the stream position.
//
Thread::ReturnValue
Thread::psi_stream_position(Object *& stream_arg, Object *& pos_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);

  //
  // Get position.
  //
  int32 pos = 0;

  pos = stream->tell();
  
  //
  // Return the position.
  //
  pos_arg = heap.newNumber(pos);
  return RV_SUCCESS;
}

//
// psi_set_stream_position(stream_index, position)
// Set the stream to the specified absolute position.
//
Thread::ReturnValue
Thread::psi_set_stream_position(Object *& stream_arg, Object *& pos_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  Object* pos_object = heap.dereference(pos_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);

  CHECK_NUMBER_ARG(pos_object, 2);

  int32 pos = pos_object->getNumber();
  if (pos < 0)
    {
      PSI_ERROR_RETURN(EV_RANGE, 2);
    }
  
  //
  // Change position.
  //
  if (stream->isInput())
    {
      stream->seekg(pos);
    }
  else
    {
      stream->seekp(pos);
    }
  
  return RV_SUCCESS;
}

//
// psi_line_number(stream_index, variable)
// Get the line number.
//
Thread::ReturnValue
Thread::psi_line_number(Object *& stream_arg, Object *& line_num_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);

  //
  // Get position and return the position.
  //
  line_num_arg = heap.newNumber(stream->lineNumber());
  return RV_SUCCESS;
}


//
// psi_stdin(stream)
// Gets the stream associated with standard input.
//
Thread::ReturnValue 
Thread::psi_stdin(Object *& stream_object)
{
  stream_object = heap.newNumber(reinterpret_cast<word32>(iom->StdIn()));

  return RV_SUCCESS;
}

//
// psi_stdout(stream)
// Gets the stream associated with standard output.
//
Thread::ReturnValue 
Thread::psi_stdout(Object *& stream_object)
{
  stream_object = heap.newNumber(reinterpret_cast<word32>(iom->StdOut()));

  return RV_SUCCESS;
}

//
// psi_stderr(stream)
// Gets the stream associated with standard error.
//
Thread::ReturnValue 
Thread::psi_stderr(Object *& stream_object)
{
  stream_object = heap.newNumber(reinterpret_cast<word32>(iom->StdErr()));

  return RV_SUCCESS;
}


//
// psi_open_msgstream(address, iomode, variable)
// Open a message stream.
//
Thread::ReturnValue
Thread::psi_open_msgstream(Object *& address,
			   Object *& access_mode_arg,
			   Object *& stream_arg)
{
#ifdef ICM_DEF
  Object* argS = heap.dereference(address);
  Object* argAM = heap.dereference(access_mode_arg);

  icmHandle handle;
  DECODE_ICM_HANDLE_ARG(heap, *atoms, argS, 1, handle);

  if (argAM->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argAM->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  word32 mode = argAM->getNumber();
  
  if (!(mode < AM_APPEND))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  switch (mode)
    {
    case AM_READ:
      {
	QPimstream *stream = new QPimstream(handle);
	//
	// Return the index of the stream.
	//
	int iom_fd = iom->OpenStream(stream);
	stream->setFD(iom_fd);
	stream_arg = heap.newNumber(iom_fd);
	return RV_SUCCESS;
      }
    break;
    case AM_WRITE:
      {
	QPomstream *stream = new QPomstream(handle, this, icm_environment);
	//
	// Return the index of the stream.
	//
	stream_arg = heap.newNumber(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
    break;
    }
  
#endif // ICM_DEF
  return RV_FAIL;
}

//
// psi_set_stream_properties(stream, properties)
// Set the stream properties.
// mode (in,in)
//
Thread::ReturnValue 
Thread::psi_set_stream_properties(Object *& stream_num, Object *& prop)
{
  Object* strnum = heap.dereference(stream_num);
  int dir;
  QPStream* stream;
  DECODE_STREAM_ARG(heap, *iom, strnum, 1, stream, dir);
  Object* props = heap.dereference(prop);

  assert(props->isStructure() && 
	       OBJECT_CAST(Structure*, props)->getArity() == 7);
#ifndef NDEBUG
    for (u_int i = 1; i <= 7; i++)
      {
	assert(OBJECT_CAST(Structure*, props)->getArgument(i)->variableDereference()->isConstant());
      }
#endif
  stream->setProperties(props);
  return RV_SUCCESS;
}

//
// psi_get_stream_properties(stream, properties)
// Get the stream properties.
// mode (in,out)
//
Thread::ReturnValue 
Thread::psi_get_stream_properties(Object *& stream_num, Object *& prop)
{
  Object* strnum = heap.dereference(stream_num);

  assert(strnum->isNumber());

  u_int snum = strnum->getNumber();

  if (snum >= NUM_OPEN_STREAMS || iom->GetStream(snum) == NULL)
    {
      return RV_FAIL;
    }

  prop = iom->GetStream(snum)->getProperties();
  return RV_SUCCESS;
}

//
// set_std_stream(stdstream, newstream)
// replace the stream with number stdstream (0,1,2) with newstream.
// mode (in,in)
//
Thread::ReturnValue
Thread::psi_set_std_stream(Object *& std_stream_num, Object *& new_stream_num)
{
  Object* std_num = heap.dereference(std_stream_num);
  Object* new_num = heap.dereference(new_stream_num);
  
  if (std_num->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (new_num->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!std_num->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!new_num->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  if (iom->set_std_stream(std_num->getNumber(), new_num->getNumber()))
    {
      return RV_SUCCESS;
    }
   PSI_ERROR_RETURN(EV_VALUE, 1);
}


//
// reset_std_stream(stdstream)
// reset the stream with number stdstream (0,1,2).
// mode (in,in)
//
Thread::ReturnValue
Thread::psi_reset_std_stream(Object *& std_stream_num)
{
  Object* std_num = heap.dereference(std_stream_num);
  
  if (std_num->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!std_num->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (iom->reset_std_stream(std_num->getNumber()))
    {
      return RV_SUCCESS;
    }
   PSI_ERROR_RETURN(EV_VALUE, 1);
}

//
// psi_get_msgstream_handle(StreamID, Handle)
// retrieve the handle of the imstream
// mode (in,out)
//
Thread::ReturnValue
Thread::psi_get_msgstream_handle(Object *& stream_num, Object *& handle_object)
{
#ifdef ICM_DEF
  Object* snum = heap.dereference(stream_num);
  
  if (snum->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!snum->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  u_int num = snum->getNumber();
  if (num >= NUM_OPEN_STREAMS)
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  QPStream *s = iom->GetStream(num);
  if (s == NULL || s->Type() != IMSTREAM)   
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  icm_handle_to_heap(heap, *atoms, s->getSenderHandle(), handle_object);
  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}









