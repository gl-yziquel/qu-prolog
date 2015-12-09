// process.cc - Pseudo-instructions for handling the process attributes 
// associated with a QuProlog invocation.
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: process.cc,v 1.3 2005/03/08 00:35:12 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern char *process_symbol;

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#endif

// @doc
// @pred process_pid(ProcessID)
// @mode process_pid(-) is det
// @type process_pid(process_id)
// @description
// Return the process-id of the current process.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_process_pid(Object *& pid_arg)
{
#ifdef WIN32
  pid_arg = heap.newInteger(reinterpret_cast<long>(GetCurrentProcess()));
#else 
  pid_arg = heap.newInteger(getpid());
#endif
  return RV_SUCCESS;
}

// @doc
// @pred process_symbol(Name)
// @mode process_symbol(-) is det
// @type process_symbol(atom)
// @description
// Return the symbolic name of this process.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_process_symbol(Object *& name_cell)
{
  if (process_symbol == NULL)
    {
      return RV_FAIL;
    }
  else
    {
      name_cell = atoms->add(process_symbol);
      return RV_SUCCESS;
    }
}

