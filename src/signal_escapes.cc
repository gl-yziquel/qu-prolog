// signal.cc - Support predicates for signal.
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
// $Id: signal_escapes.cc,v 1.3 2001/06/17 21:54:48 qp Exp $

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "scheduler.h"
#include "signals.h"

extern "C" int kill(pid_t, int);


#include "thread_qp.h"

extern Signals *signals;

//
// psi_clear_signal(signal number)
// Remove any waiting signal for a given signal number.
// mode(in)
//
Thread::ReturnValue
Thread::psi_clear_signal(Object *& object1)
{
  Object* val1 = heap.dereference(object1);

  DEBUG_ASSERT(val1->isShort());

  signals->Clear(val1->getNumber());

  return(RV_SUCCESS);
}

//
// psi_clear_all_signals
// Remove all waiting signals.
// mode()
//
Thread::ReturnValue
Thread::psi_clear_all_signals(void)
{
  for (int i = 1; i < NSIG + 1; i++)
    {
      signals->Clear(i);
    }

  return(RV_SUCCESS);
}

//
// psi_default_signal_handler(signal number)
// Call the default signal handler.
// mode(in)
//
Thread::ReturnValue
Thread::psi_default_signal_handler(Object *& object1)
{
  Object* val1 = heap.dereference(object1);

  DEBUG_ASSERT(val1->isShort());

  int sig = val1->getNumber();

  kill(getpid(), sig);

  return(RV_SUCCESS);
}









