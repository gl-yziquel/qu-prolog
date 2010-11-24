// env_var.cc - Interface to environment variables.
//		The name is env_var.cc to avoid clashes with other
//		files that are related to environments.
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
// $Id: env_var.cc,v 1.3 2002/11/08 00:44:15 qp Exp $

#include <stdlib.h>

#include "config.h"

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

Thread::ReturnValue
Thread::psi_env_getenv(Object *& name_arg, Object *& value_arg)
{
  Object* name = heap.dereference(name_arg);

  if (name->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!name->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  const char *env_value = getenv(OBJECT_CAST(Atom*, name)->getName());
  if (env_value == NULL)
    {
      return RV_FAIL;
    }

  value_arg = atoms->add(env_value);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_env_putenv(
	       Object *& name_arg,
	       Object *& value_arg)
{
  Object* name = heap.dereference(name_arg);
  Object* value = heap.dereference(value_arg);

  if (name->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!name->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  if (value->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!value->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *name_string = OBJECT_CAST(Atom*, name)->getName();
  const char *value_string = OBJECT_CAST(Atom*, value)->getName();

  const size_t name_string_len = strlen(name_string);
  const size_t value_string_len = strlen(value_string);

  // The string containing the environment entry has to look like
  // name=value, so we need two extra bytes, one for the '=' and one
  // for the terminating null.
  const size_t total_len = name_string_len + value_string_len + 2;

  char *env_entry_string = new char[total_len];

  (void) strcpy(env_entry_string, name_string);
  (void) strcat(env_entry_string, "=");
  (void) strcat(env_entry_string, value_string);
	 
  const int result = putenv(env_entry_string);

  return result == 0 ? RV_SUCCESS : RV_FAIL;
}








