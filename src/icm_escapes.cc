// icm_escapes.cc -
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
// $Id: icm_escapes.cc,v 1.4 2001/02/23 01:11:44 qp Exp $

#include "atom_table.h"
#include "icm_environment.h"
#include "icm_handle.h"
#include "qem_options.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern ICMEnvironment *icm_environment;
extern QemOptions *qem_options;
extern char *process_symbol;
extern char *icm_address;
extern int icm_port;

Thread::ReturnValue
Thread::psi_icm_process_handle(Object *& handle_object)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }
  else
    {
      icmHandle handle = icm_process_handle(*icm_environment);

      icm_handle_to_heap(heap, *atoms, handle, handle_object);

#if 0
      icmReleaseHandle(handle);
#endif

      return RV_SUCCESS;
    }
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_icm_thread_handle(Object *& handle_object)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }
  else
    {
      icmHandle handle = icm_thread_handle(*icm_environment, *this);

      icm_handle_to_heap(heap, *atoms, handle, handle_object);

      icmReleaseHandle(handle);

      return RV_SUCCESS;
    }
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_icm_handles_equal(Object *& handle1_object,
			      Object *& handle2_object)
{
#ifdef ICM_DEF
  Object* handle1_arg = heap.dereference(handle1_object);
  Object* handle2_arg = heap.dereference(handle2_object);

  icmHandle handle1;
  DECODE_ICM_HANDLE_ARG(heap, *atoms, handle1_arg, 1, handle1);

  icmHandle handle2;
  DECODE_ICM_HANDLE_ARG(heap, *atoms, handle2_arg, 2, handle2);
  
  ReturnValue rv = BOOL_TO_RV(icmSameAgentHandle(handle1, handle2) == icmOk);

#if 0  
  icmReleaseHandle(handle1);
  icmReleaseHandle(handle2);
#endif

  return rv;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_icm_handles_qp_equal(Object *& handle1_object,
				 Object *& handle2_object)
{
#ifdef ICM_DEF
  Object* handle1_arg = heap.dereference(handle1_object);
  Object* handle2_arg = heap.dereference(handle2_object); 

  icmHandle handle1;
  DECODE_ICM_HANDLE_ARG(heap, *atoms, handle1_arg, 1, handle1);

  icmHandle handle2;
  DECODE_ICM_HANDLE_ARG(heap, *atoms, handle2_arg, 2, handle2);

  ReturnValue rv = BOOL_TO_RV(icmSameHandle(handle1, handle2) == icmOk);

#if 0
  icmReleaseHandle(handle1);
  icmReleaseHandle(handle2);
#endif

  return rv;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_icm_handle_from_components(Object *& target_object,
				       Object *& name_object,
				       Object *& host_object,
				       Object *& locations_object,
				       Object *& handle_object)
{
#ifdef ICM_DEF
  Object* argT = heap.dereference(target_object);
  Object* argN = heap.dereference(name_object);
  Object* argH = heap.dereference(host_object);
  Object* argL = heap.dereference(locations_object);

  CHECK_ATOMIC_ARG(argT, 1);
  CHECK_ATOM_ARG(argN, 2);
  CHECK_ATOM_ARG(argH, 3);
  CHECK_ATOM_LIST_ARG(heap, argL, 4);

  Structure* handle_structure = heap.newStructure(4);
  handle_structure->setFunctor(AtomTable::icm_handle);
  handle_structure->setArgument(1, argT);
  handle_structure->setArgument(2, argN);
  handle_structure->setArgument(3, argH);
  handle_structure->setArgument(4, argL);
  
  handle_object = handle_structure;
  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_icm_handle_to_components(Object *& target_object,
				     Object *& name_object,
				     Object *& home_object,
				     Object *& locations_object,
				     Object *& handle_object)
{
#ifdef ICM_DEF
  Object* argH = heap.dereference(handle_object);

  if (argH->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 5);
    }
  if (! argH->isStructure())
    {
      PSI_ERROR_RETURN(EV_TYPE, 5);
    }
  else
    {
      Structure* str = OBJECT_CAST(Structure*, argH);
      if (str->getFunctor() != AtomTable::icm_handle
	  || str->getArity() != 4)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 5);
	}
      else
	{
	  Object* target = heap.dereference(str->getArgument(1));
	  Object* name = heap.dereference(str->getArgument(2));
	  Object* home = heap.dereference(str->getArgument(3));
	  Object* locations = heap.dereference(str->getArgument(4));

	  CHECK_ATOMIC_ARG(target, 5);
	  CHECK_ATOM_ARG(name, 5);
	  CHECK_ATOM_ARG(home, 5);
	  CHECK_ATOM_LIST_ARG(heap, locations, 5);

	  target_object = target;
	  name_object = name;
	  home_object = home;
	  locations_object = locations;
	}
    }
  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}



// @doc
// @pred icm_address(Name)
// @mode icm_address(-) is det
// @type icm_address(atom)
// @description
// Return the symbolic name of this process.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_icm_address(Object *& name_cell)
{
  if (process_symbol == NULL)
    {
      return RV_FAIL;
    }
  else if (icm_address == NULL)
    {
      name_cell = atoms->add("");
      return RV_SUCCESS;
    }
  else
    {
      name_cell = atoms->add(icm_address);
      return RV_SUCCESS;
    }
}

// @doc
// @pred icm_port(Name)
// @mode icm_port(-) is det
// @type icm_port(integer)
// @description
// Return the symbolic name of this process.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_icm_port(Object *& name_cell)
{
  if (process_symbol == NULL)
    {
      return RV_FAIL;
    }
  else
    {
      name_cell = heap.newNumber(icm_port);
      return RV_SUCCESS;
    }
}





