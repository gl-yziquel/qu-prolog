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
// $Id: icm_escapes.cc,v 1.10 2003/12/11 23:41:26 qp Exp $

#include "atom_table.h"
#include "icm_environment.h"
#include "icm_handle.h"
#include "qem_options.h"
#include "thread_qp.h"
#include "scheduler.h"

#include <netdb.h>

extern AtomTable *atoms;
extern ICMEnvironment *icm_environment;
extern QemOptions *qem_options;
extern char *process_symbol;
extern char *icm_address;
extern int icm_port;
extern ICMMessageChannel* icm_channel;
extern ThreadTable *thread_table;
extern IOManager *iom;
extern Signals *signals;
extern Scheduler *scheduler;

Thread::ReturnValue
Thread::psi_icm_register(Object *& name_arg, Object *& port_arg, 
			 Object *& server_arg)
{
#ifdef ICM_DEF
  if (icm_environment != NULL)
    {
      Warning(Program, "Already registered");
      return RV_FAIL;
    }
  DEBUG_ASSERT(name_arg->variableDereference()->isAtom());
  DEBUG_ASSERT(port_arg->variableDereference()->isNumber());
  DEBUG_ASSERT(server_arg->variableDereference()->isAtom());
  Atom* name = OBJECT_CAST(Atom*, name_arg->variableDereference());
  int port = port_arg->variableDereference()->getNumber();
  Atom* server = OBJECT_CAST(Atom*, server_arg->variableDereference());

  process_symbol = atoms->getAtomString(name);
  char* icm_server = (server == atoms->add("") 
		      ? NULL : atoms->getAtomString(server));

  icmConn icm_conn;
  // Start up communications
  const icmStatus icm_status = icmInitComms(port, icm_server, &icm_conn); 

  if (icm_status == icmFailed)
    {
      Warning(Program, " Couldn't contact ICM communications server");
      return RV_FAIL;
    }
  else if (icm_status == icmError)
    {
      Warning(Program, " ICM communications refused connection");
      return RV_FAIL;
    }
  // Set up icm and register
  icm_environment = new ICMEnvironment(icm_conn);
  if (!icm_environment->Register(process_symbol))
    {
      Fatal(Program, " Cannot register process with ICM");
    }


  // Create a channel for ICM messages
  icm_channel = 
    new ICMMessageChannel(*icm_environment, *thread_table, *iom, *signals);
  // Add ICM channel to scheduler channels
  scheduler->getChannels().push_back(icm_channel);
  return RV_SUCCESS;

#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_icm_deregister(void)
{
#ifdef ICM_DEF
  if (icm_environment == NULL)
    {
      Warning(Program, "Not registered");
      return RV_FAIL;
    }
  list <MessageChannel*>& channels = scheduler->getChannels();
  for (list <MessageChannel*>::iterator iter = channels.begin();
       iter != channels.end();
       iter++)
    {
      if (*iter == icm_channel)
        {
          channels.erase(iter);
          break;
        }
    }

  delete icm_channel;
  icm_environment->Unregister();
  delete icm_environment;
  icm_environment = NULL;
  process_symbol = NULL;
  return RV_SUCCESS;

#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}


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

bool machine_name_to_full_name(Object*& name, Object*& fullname)
{
  Object* mname = name->variableDereference();
  if (!mname->isAtom())
    {
      return false;
    }
  Atom* name_atom = OBJECT_CAST(Atom*, mname);
  char* name_string = atoms->getAtomString(name_atom);
  if(strchr(name_string,'.') != NULL) // A dotted name
    {
       fullname = mname;
      return true;
    }
  hostent *hp = gethostbyname(name_string);
  endhostent();
  if (!hp)
    {
      return false;
    }
  
  fullname =  atoms->add(hp->h_name);
  return true;
}

Thread::ReturnValue 
Thread::psi_icm_symbolic_address_to_icm_handle(Object *& add_obj, 
					       Object *& handle_obj)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }
  
  Object* address_term = heap.dereference(add_obj);

  if (address_term->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }

  Object* my_handle;
  icmHandle handle = icm_thread_handle(*icm_environment, *this);
  
  icm_handle_to_heap(heap, *atoms, handle, my_handle);
  Structure* my_hand_str = OBJECT_CAST(Structure*,my_handle);
  
  icmReleaseHandle(handle);

  if (address_term->isAtom())
    {
      if (address_term == atoms->add("self"))
	{
	  handle_obj = my_handle;
          return RV_SUCCESS;
        }
      else
	{
          my_hand_str->setArgument(1, address_term);
	  handle_obj = my_handle;
          return RV_SUCCESS;
        }
    }
  else if (address_term->isStructure())
    {
      Object* thread_name = NULL;
      Object* process_name = NULL;
      Object* machine_name = NULL;
      Object* locations = NULL;
      Structure* hand_str = OBJECT_CAST(Structure*, address_term);
      Object* func = hand_str->getFunctor()->variableDereference();
      if (func->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 1);
	}
      if (func == AtomTable::divide) // has locations
	{
	  Object* l = hand_str->getArgument(2)->variableDereference();
	  if (l->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	  locations = l;
	  Object* tmp = hand_str->getArgument(1)->variableDereference();
	  if (tmp->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	  if (!tmp->isStructure())
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 1);
	    }
	  hand_str = OBJECT_CAST(Structure*, tmp);
	  func = hand_str->getFunctor()->variableDereference();
	  if (func->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	}
      if (func == atoms->add("@"))
	{
	  Object* l = hand_str->getArgument(2)->variableDereference();
	  if (l->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	  machine_name = l;
	  Object* tmp = hand_str->getArgument(1)->variableDereference();
	  if (tmp->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	  if (!tmp->isStructure())
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 1);
	    }
	  hand_str = OBJECT_CAST(Structure*, tmp);
	  func = hand_str->getFunctor()->variableDereference();
	  if (func->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	}
      if (func == atoms->add(":"))
	{
	  Object* l = hand_str->getArgument(2)->variableDereference();
	  if (l->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	  process_name = l;
	  thread_name = hand_str->getArgument(1)->variableDereference();
	  if (thread_name->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 1);
	    }
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
  
      if (machine_name == atoms->add("localhost") 
	  || machine_name == atoms->add("LOCALHOST"))
	{
	  machine_name = NULL;
	}
      if (machine_name != NULL) 
	{
	  Object* fullname;
	  if (!machine_name_to_full_name(machine_name, fullname))
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 1);
	    }
	  machine_name = fullname;
	}
      if (locations == NULL)
	{
	  if (machine_name != NULL)
	    {
	      Cons* loc = heap.newCons();
	      loc->setHead(machine_name);
	      loc->setTail(AtomTable::nil);
	      my_hand_str->setArgument(4, loc);
	    }
	}
      else
	{
	  if (locations->isNil())
	    {
	      my_hand_str->setArgument(4, locations);
	    }
	  else
	    {
	      Cons* fullloc;
	      Cons* next = heap.newCons();
	      fullloc = next;
	      while (!locations->isNil())
		{
		  if (!locations->isCons())
		    {
		      PSI_ERROR_RETURN(EV_TYPE, 1);
		    }
		  Object* head = OBJECT_CAST(Cons*, locations)->getHead()->variableDereference();
		  locations = OBJECT_CAST(Cons*, locations)->getTail()->variableDereference();
		  Object* fullname;
		  if (!machine_name_to_full_name(head, fullname))
		    {
		      PSI_ERROR_RETURN(EV_TYPE, 1);
		    }
		  next->setHead(fullname);
                  if (locations->isNil())
		    {
		      next->setTail(AtomTable::nil);
		      break;
		    }
		  Cons* tmp = heap.newCons();
		  next->setTail(tmp);
		  next = tmp;
		}
	      my_hand_str->setArgument(4, fullloc);
	    }
	}
      if (machine_name != NULL) 
	{
	  my_hand_str->setArgument(3, machine_name);
	}
      if (process_name != NULL)
	{
	  my_hand_str->setArgument(2, process_name);
	}
      if (thread_name != NULL)
	{
	  my_hand_str->setArgument(1, thread_name);
	}
      handle_obj = my_handle;
      return RV_SUCCESS;
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}


