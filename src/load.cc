// load.cc - Load and link a .qo file.
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
// $Id: load.cc,v 1.6 2004/03/19 04:54:17 qp Exp $

#include <unistd.h>

#include "atom_table.h"
#include "system_support.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern Code *code;
extern PredTab *predicates;
extern QemOptions *qem_options;

// psi_load(filename, queryname)
// Load and link a .qo file.  If the operation is successful, 0 is returned in
// X1.
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_load(Object *& object1, Object*& object2)
{
  Object* val1 = heap.dereference(object1);

  DEBUG_ASSERT(val1->isAtom());

  const char *file = wordexp(atoms->getAtomString(val1)).c_str(); 

  if (access(file, F_OK) == 0)
    {
      ObjectIndex index(*code, *atoms, *predicates);
      StringMap string_map(qem_options->StringMapSize(), 0);
      word32 NumQuery = 0;

      //
      // Read the file.
      //
      if (index.loadObjectFile(file, NumQuery, string_map, *predicates))
	{
	  //
	  // Link the program.
	  //
	  index.resolveObject(string_map, *predicates, false, object2);
	  
	  return(RV_SUCCESS);
	}
    }

  return(RV_FAIL);
}





