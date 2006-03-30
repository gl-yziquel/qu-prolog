// icm_handle.cc -
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
// $Id: icm_handle.cc,v 1.9 2006/01/31 23:17:50 qp Exp $

#include "config.h"

#ifdef ICM_DEF
#include "objects.h"
#include "heap_qp.h"
#include "icm_handle.h"

// Decodes an icmHandle onto the QuProlog heap.
void
icm_handle_to_heap(Heap& heap,
		   AtomTable& atoms,
		   icmHandle handle,
		   Object*& handle_cell)
{
  char *target;
  char *name;
  char *home;
  char **locations;
  int len;

  const icmStatus status = 
    icmAnalyseHandle(handle, &target, &name, &home, &locations, &len);
  if (status == icmError)
    {
      Fatal(__FUNCTION__, "Bad icmHandle");
    }
  
  Structure* handle_struct = heap.newStructure(4);
  handle_struct->setFunctor(AtomTable::icm_handle);
  
  assert(target != NULL);

  if (strcmp(target, "") != 0)
    {
      ICMIncomingTarget icm_incoming_target(target);

      if (icm_incoming_target.IsID())
	{
	  handle_struct->setArgument(1, 
				     heap.newNumber(icm_incoming_target.ID()));
	}
      else
	{
	  handle_struct->setArgument(1, 
				     atoms.add(icm_incoming_target.Symbol()));
	}
    }
  else
    {
      handle_struct->setArgument(1, atoms.add(target));
    }

  handle_struct->setArgument(2, atoms.add(name));
  handle_struct->setArgument(3, atoms.add(home));

  Object* atom_list = AtomTable::nil;

  for (size_t i = len; i > 0; i--)
    {
      Cons* temp_list = heap.newCons(atoms.add(locations[i - 1]), atom_list);
      atom_list = temp_list;
    }
  handle_struct->setArgument(4, atom_list);
  handle_cell = handle_struct;
}

icmHandle
icm_process_handle(ICMEnvironment& icm_environment)
{
  return icm_environment.Handle();
}

icmHandle
icm_thread_handle(ICMEnvironment& icm_environment,
		  Thread& thread)
{
  icmHandle handle = icm_environment.Handle();

  char *target;
  char *name;
  char *home;
  char **locations;
  int len;

  const icmStatus analyse_status = 
    icmAnalyseHandle(handle, &target, &name, &home, &locations, &len);
  if (analyse_status == icmError)
    {
      Fatal(__FUNCTION__, "Bad icmHandle");
    }
  
  string thread_target;
  if (thread.TInfo().SymbolSet())
    {
      ICMOutgoingTarget icm_outgoing_target(thread.TInfo().Symbol());
      thread_target = icm_outgoing_target.Target();
    }
  else
    {
      ICMOutgoingTarget icm_outgoing_target(thread.TInfo().ID());
      thread_target = icm_outgoing_target.Target();
    }

  assert(thread_target != "");

  icmHandle thread_handle = 
    icmMakeHandle(const_cast<char *>(thread_target.c_str()),
		  name, home, len, locations);

  if (thread_handle == NULL)
    {
      Fatal(__FUNCTION__, "icmMakeHandle()");
    }

  return thread_handle;
}

#endif // ICM_DEF




