// machine.cc - Escapes for dealing with machine addresses, etc.
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
// $Id: machine.cc,v 1.3 2000/12/13 23:10:02 qp Exp $

#include <sys/types.h>
#include <netinet/in.h>

#include "atom_table.h"
#include "icm.h"
#include "thread_qp.h"

extern AtomTable *atoms;

// @doc
// @pred machine_ip_address(IPAddress)
// @mode machine_ip_address(-) is det
// @type machine_ip_address(atom)
// @description
// Return the IP address of this machine in octet notation.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_machine_ip_address(Object *& ip_address_arg)
{
#ifdef ICM_DEF
  char *ip_address = icmMachineIP();

  ip_address_arg = atoms->add(ip_address);

  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

// @doc
// @pred machine_name(Name)
// @mode machine_name(-) is det
// @type machine_name(atom)
// @description 
// Return the name of this machine.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_machine_name(Object *& hostname_arg)
{
#ifdef ICM_DEF
  char *machine_name = icmMachineName();
  
  hostname_arg = atoms->add(machine_name);

  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

