// timer.h - Managment of timers
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

#ifndef	TIMER_H
#define	TIMER_H

#include "heap_qp.h"
#include "objects.h"
#include "timeval.h"

#define TIMER_HEAP_SIZE 5000
#define TIMER_NUM 100

class Timer
{
 public:
  Thread* thread;
  Object* goal;
  heapobject* next;
  Timeval time;
  u_int id;
  double delta;
  bool one_time;
  
 Timer(Thread* th, Object* g, heapobject* n, double t, u_int i, bool ot) 
   : thread(th), goal(g), next(n), time(t), id(i), delta(t), one_time(ot) 
  {}
  
  void resetTimer(void)
  {
    time = Timeval(delta);
  }

};

class TimerStack
{
 private:
  Timer* timers[TIMER_NUM];
  u_int next_id;
  Heap* current_heap;
  Heap* other_heap;
  int tos;

 public:
  TimerStack(void)
    {
      next_id = 0;
      tos = 0;
      current_heap = new Heap("Timer Heap", TIMER_HEAP_SIZE, false);
      other_heap = new Heap("Timer Heap", TIMER_HEAP_SIZE, false);
    }

  ~TimerStack(void)
    {
      for (int i = 0; i < tos; i++) delete timers[i];
      delete current_heap;
      delete other_heap;
    }
       
  Heap* getHeap(void) { return current_heap; }

  u_int create_timer(Thread* th, Object* goal, double time, 
		     bool one_time);

  bool insert_timer(Timer* t);

  bool delete_timer(Thread* th, u_int id);
  
  void delete_all_timers(Thread* th);

  bool make_timer_goal(Object*&, Heap&);

  void copy_compress_heap(void);

  bool timer_ready(void);
  
  void update_timeout(Timeval& timeout);
};
  
#endif	// TIMER_H
