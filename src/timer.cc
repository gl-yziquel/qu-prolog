// timer.cc - Managment of timers
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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

#include "timer.h"
#include "copy_term.h"
#include "thread_qp.h"

u_int
TimerStack::create_timer(Thread* th, Object* goal, double time, 
			 bool one_time)
{
  Object* copy = th->TheHeap().copyTerm(goal, *current_heap);
  heapobject* toh = current_heap->getTop();
  Timer* t = new Timer(th, copy, toh, time, next_id, one_time);
  if (insert_timer(t))
    {
      return next_id++;
    }
  else
    {
      Fatal(__FUNCTION__, "Out of timer space");
      return (u_int)(-1);
    }

}

bool
TimerStack::insert_timer(Timer* it)
{
  int i = tos-1;
  
  for (; i >= 0; i--) 
    {
      Timer* t = timers[i];
      if ((t == NULL) || (it->time < t->time))
	{
	  timers[i+1] = t;
	}
      else
	{
	  break;
	}
    }
  timers[i+1] = it;
  tos++;
  return (tos < TIMER_NUM-1);
}

bool
TimerStack::delete_timer(Thread* th, u_int id)
{
  bool found = false;
  for (int i = 0; i < tos; i++)
    {
      if (found)
	{
	  timers[i] = timers[i+1];
	}
      else
	{
	  Timer* t = timers[i];
	  if ((t != NULL) && (t->thread == th) && (t->id == id))
	    {
	      found = true;
	      delete t;
	      timers[i] = NULL;
	    }
	}
    }
  if (found) tos--;

  return found;
}

void
TimerStack::delete_all_timers(Thread* th)
{
  int count = 0;
  for (int i = 0; i < tos; i++)
    {
      Timer* t = timers[i];
      if ((t != NULL) && (t->thread == th))
	{
	  count++;
	  delete t;
	  timers[i] = NULL;
	}
    }
  // compress
  int next = 0;
  for (int i = 0; i < tos; i++)
    {
      Timer* t = timers[i];
      timers[next] = t;
      if (t != NULL)
	{
	  next++;
	}
    }
  tos -= count;

}

bool
TimerStack::make_timer_goal(Object*& goal, Heap& dest)
{
  Timeval now = Timeval();
  int i = tos-1;
  Timer* t = NULL;
  bool found = false;
  for (; i >= 0; i--)
    {
      t = timers[i];
      if (t->time <= now)
	{
	  found = true;
	  break;
	}
    }
  if (!found) return false;

  int ind = i+1;
  goal = AtomTable::nil;
  for (; i >= 0; i--)
    {
      t = timers[i];
      Cons* lst = dest.newCons(t->goal, goal);
      goal = OBJECT_CAST(Object*, lst);
      if (!t->one_time)
	{
	  t->resetTimer();
	  insert_timer(t);
	  timers[i] = NULL;
	}
      else
	{
	  delete t;
	  timers[i] = NULL;
	}
    }
  // compress
  int next = 0;
  for (int i = ind; i < tos; i++)
    {
      Timer* t = timers[i];
      timers[next] = t;
      if (t != NULL)
	{
	  next++;
	}
    }
  tos = next;
  copy_compress_heap();
  return true;
}

void 
TimerStack::copy_compress_heap(void)
{
  other_heap->setTop( other_heap->getBase());
  for (int i = 0; i < tos; i++)
    {
      Timer* t = timers[i];
      Object* copy = current_heap->copyTerm(t->goal, *other_heap);
      t->goal = copy;
    }
  Heap* tmp = current_heap;
  current_heap = other_heap;
  other_heap = tmp;
}

bool 
TimerStack::timer_ready(void)
{
  Timeval now;
  return ((tos > 0) && (timers[0]->time <= now));
}

void  
TimerStack::update_timeout(Timeval& tout)
{
  if (tos > 0)
    {
      Timeval now;
      Timeval delta(timers[0]->time, now);
      if (delta < tout) tout = delta;
    }
}
