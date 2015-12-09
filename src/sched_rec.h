// sched_rec.h - Scheduler records.
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: sched_rec.h,v 1.2 2000/12/12 03:36:21 qp Exp $

#ifndef	SCHED_REC_H
#define	SCHED_REC_H

#include <time.h>

#include "defs.h"

class Thread;

class SchedRec
{
private:
  Thread& thread;
  time_t timeout;
  bool blocked;
  bool removed;
public:
  SchedRec(Thread& t, const word32 p = 0)
    : thread(t), timeout(p), blocked(false), removed(false) { }
  
  Thread& Thr(void) { return thread; }
  time_t Timeout(void) const { return timeout; }
  
  void Block(void) { blocked = true; }
  void Unblock(void) { blocked = false; }
  bool Blocked(void) const { return blocked; }

  void Remove(void) { removed = true; }
  bool Removed(void) const { return removed; }

  bool operator==(const SchedRec& sr) { return &thread == &sr.thread; }
};

#endif	// SCHED_REC_H
