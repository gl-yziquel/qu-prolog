// timer_escapes.cc - Timer procedures
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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

#include <errno.h>

//#include "config.h"

//#include "global.h"
#include "atom_table.h"

#include "thread_qp.h"

#include "timer.h"

extern TimerStack timerStack;

Thread::ReturnValue
Thread::psi_create_timer(Object *& goal_arg, Object *& time_arg, 
			 Object *& one_time_arg, Object *& timer_id)
{
  Object* ga = heap.dereference(goal_arg);
  Object* ta = heap.dereference(time_arg);
  Object* ota = heap.dereference(one_time_arg);
  if (!ta->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  if (!ota->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }
  bool one_time = (ota == AtomTable::success);
  Object* ga_copy = heap.copyTerm(ga, *(timerStack.getHeap()));
  double time;
  if (ta->isDouble()) time = ta->getDouble();
  else time = ta->getInteger();
  if (time < 0) PSI_ERROR_RETURN(EV_TYPE, 2);
  u_int id = timerStack.create_timer(this, ga_copy, time, one_time);
  if (id == (u_int)(-1))
    return RV_FAIL;
  timer_id = heap.newInteger(id);
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_delete_timer(Object *& id_arg)
{
  Object* idobj = heap.dereference(id_arg);
  assert(idobj->isInteger());
  u_int id = (u_int)(idobj->getInteger());
  if (timerStack.delete_timer(this, id))
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_timer_goals(Object *& goals)
{
  Object* g;
  if (timerStack.make_timer_goal(g, heap))
    {
      goals = timerStack.getHeap()->copyTerm(g, heap);
      return RV_SUCCESS;
    }
  return RV_FAIL;
}
