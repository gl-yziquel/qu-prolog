// thread_condition.h -
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
// $Id: thread_condition.h,v 1.2 2002/11/03 08:37:34 qp Exp $

#ifndef	THREAD_CONDITION_H
#define	THREAD_CONDITION_H

#include <iostream>

// Information about the status of the thread.
class ThreadCondition
{
public:
  enum ThreadConditionValue {
    NEW,	// The thread has been created, but not assigned a goal
    RUNNABLE,	// The thread is now runnable
    SUSPENDED,	// The thread is now suspended
    EXITED	// The thread has exited
  };
private:
  ThreadConditionValue condition;
  bool stopped;

public:
  ThreadCondition(void) : condition(NEW), stopped(false) { }

  ThreadConditionValue Condition(void) const { return condition; }
  void Condition(const ThreadConditionValue tcv) { condition = tcv; }

  bool IsStopped(void) const { return stopped; }
  void SetStopped(void) { stopped = true; }
  void ClearStopped(void) { stopped = false; }
};

using namespace std;
// Print out a ThreadCondition in a form that can be read by a person.
extern ostream& operator<<(ostream&, const ThreadCondition&);

#endif	// THREAD_CONDITION_H
