// trace_escapes.cc - Set the level of the QuAM trace.
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
// $Id: trace_escapes.cc,v 1.3 2000/12/13 23:10:02 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
#include "trace_qp.h"

//
// A wrapper for decode_trace_flag() calls.
//
#define DECODE_TRACE_FLAG_ARG(arg, arg_num, flag)	\
do {							\
  const ErrorValue ev = decode_trace_flag(arg, flag);	\
  if (ev != EV_NO_ERROR)				\
    {							\
      PSI_ERROR_RETURN(ev, arg_num);			\
    }							\
} while (0)
		
static ErrorValue
decode_trace_flag(Object *& flag_cell,
		  word32& flag)
{
  if (flag_cell->isVariable())
    {
      return EV_INST;
    }
  else if (flag_cell->isAtom())
    {
      if (flag_cell == AtomTable::trace_instr)
	{
	  flag = Trace::TRACE_INSTR;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_backtrack)
	{
	  flag = Trace::TRACE_BACKTRACK;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_env)
	{
	  flag = Trace::TRACE_ENV;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_choice)
	{
	  flag = Trace::TRACE_CHOICE;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_cut)
	{
	  flag = Trace::TRACE_CUT;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_heap)
	{
	  flag = Trace::TRACE_HEAP;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_regs)
	{
	  flag = Trace::TRACE_REGS;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_all)
	{
	  flag = Trace::TRACE_ALL;
	  return EV_NO_ERROR;
	}
      else
	{
	  return EV_VALUE;
	}
    }
  else
    {
      return EV_TYPE;
    }
}

Thread::ReturnValue
Thread::psi_set_trace_level(Object *& object1)
{
  Object* val1 = heap.dereference(object1);
  
  DEBUG_ASSERT(val1->isNumber());
	
  trace.TraceLevel() = (word32)(val1->getNumber());
  
  return(RV_SUCCESS);
}

Thread::ReturnValue
Thread::psi_set_trace_flag(Object *& flag_arg)
{
  Object* argF = heap.dereference(flag_arg);

  word32 flag;
  DECODE_TRACE_FLAG_ARG(argF, 1, flag);

  trace.SetTraceFlag(flag);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_clear_trace_flag(Object *& flag_arg)
{
  Object* argF = heap.dereference(flag_arg);

  word32 flag;
  DECODE_TRACE_FLAG_ARG(argF, 1, flag);

  trace.ClearTraceFlag(flag);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_test_trace_flag(Object *& flag_arg)
{
  Object* argF = heap.dereference(flag_arg);

  word32 flag;
  DECODE_TRACE_FLAG_ARG(argF, 1, flag);

  return BOOL_TO_RV(trace.TestTraceFlag(flag));
}






