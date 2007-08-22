// get_args.cc - Put the list of atoms onto the heap in WAM format.
//		 argv is the list of atoms on the mainline call.
//
//
// Also manages initial goal passed in with -g switch
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
// $Id: get_args.cc,v 1.2 2000/12/13 23:10:01 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern QemOptions *qem_options;
extern char *initial_goal;

//
// Put the list of atoms onto the heap in WAM format. 
// argv is the array of atoms on the mainline call.
// mode(out)
//
Thread::ReturnValue
Thread::psi_get_args(Object *& object1)
{
  Object* tail = AtomTable::nil;
  for (word32 i = qem_options->PrologArgc(); i > 0; i--)
    {
      Object* head = atoms->add(qem_options->PrologArgv()[i - 1]);
      Cons* temp = heap.newCons(head,tail);
      tail = temp;
    }
  
  object1 = tail;
  return(RV_SUCCESS);
}


//
// Extract the initial goal as a string - fails if no initial goal
//
Thread::ReturnValue 
Thread::psi_initial_goal(Object *& object1)
{
  if (initial_goal == NULL) {
    return(RV_FAIL);
  }
  object1 = heap.newStringObject(initial_goal);
  return(RV_SUCCESS);
}









