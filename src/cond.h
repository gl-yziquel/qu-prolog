// cond.h - Condition variable class.
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
// $Id: cond.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	COND_H
#define	COND_H

#include <pthread.h>

#include "mutex.h"
#include "timeval.h"

class Cond : public Mutex
{
protected:
  pthread_cond_t cond;

public:
  Cond(void)
  {
    SYSTEM_CALL_NON_ZERO(pthread_cond_init(&cond, NULL));
  }
  ~Cond(void)
  {
    SYSTEM_CALL_NON_ZERO(pthread_cond_destroy(&cond));
  }

  void Wait(void)
  {
    SYSTEM_CALL_NON_ZERO(pthread_cond_wait(&cond, &mutex));
  }

  // Waits until time t, or until Signal()ed.
  // Returns true if the condition variable is Signal()ed,
  // false if there's a timeout and raises an error if anything else
  /// happens.
  bool TimedWait(const time_t t)
  {
    if (t == (time_t) -1)
      {
	Wait();
	return true;
      }
    else
      {
	const timespec ts = { t, 0 };
	SYSTEM_CALL_NON_ZERO_RETURN_BOOL(pthread_cond_timedwait(&cond, &mutex, &ts),
					 ETIMEDOUT);
      }
  }
  bool TimedWait(const Timeval& tv)
  {
    if (tv.IsForever())
      {
	Wait();
	return true;
      }
    else
      {
	const timespec ts = { tv.Sec(), tv.MicroSec() * 1000 };
	SYSTEM_CALL_NON_ZERO_RETURN_BOOL(pthread_cond_timedwait(&cond, &mutex, &ts),
					 ETIMEDOUT);
      }
  }
  void Signal(void)
  {
    SYSTEM_CALL_NON_ZERO(pthread_cond_signal(&cond));
  }
  void Broadcast(void)
  {
    SYSTEM_CALL_NON_ZERO(pthread_cond_broadcast(&cond));
  }
};

#endif	// COND_H
