// signals.cc -
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
// $Id: signal.cc,v 1.2 2002/11/03 08:37:32 qp Exp $

#include <iostream>

#include "config.h"

#include "signals.h"

Signals::Signals(void)
{
  signals[SIGINT].init("SIGINT");
#if 0
  signals[SIGHUP].init("SIGHUP");
  signals[SIGINT].init("SIGINT");
  signals[SIGQUIT].init("SIGQUIT");
  signals[SIGILL].init("SIGILL");
  signals[SIGTRAP].init("SIGTRAP");
  signals[SIGIOT].init("SIGIOT");
  signals[SIGABRT].init("SIGABRT");
#ifdef SIGEMT
  signals[SIGEMT].init("SIGEMT");
#endif	// SIGEMT
  signals[SIGBUS].init("SIGBUS");
  signals[SIGFPE].init("SIGFPE");
  signals[SIGKILL].init("SIGKILL");
  signals[SIGSEGV].init("SIGSEGV");
#ifdef SIGSYS
  signals[SIGSYS].init("SIGSYS");
#endif	// SIGSYS
  signals[SIGPIPE].init("SIGPIPE");
  signals[SIGALRM].init("SIGALRM");
  signals[SIGTERM].init("SIGTERM");
  signals[SIGSTKFLT].init("SIGSTKFLT");
  signals[SIGUSR1].init("SIGUSR1");
  signals[SIGUSR2].init("SIGUSR2");
  signals[SIGCLD].init("SIGCLD");
  signals[SIGCHLD].init("SIGCHLD");
  signals[SIGCONT].init("SIGCONT");
  signals[SIGSTOP].init("SIGSTOP");
  signals[SIGTSTP].init("SIGTSTP");
  signals[SIGPWR].init("SIGPWR");
  signals[SIGWINCH].init("SIGWINCH");
  signals[SIGURG].init("SIGURG");
  signals[SIGPOLL].init("SIGPOLL");
  signals[SIGIO].init("SIGIO");
  signals[SIGTTIN].init("SIGTTIN");
  signals[SIGTTOU].init("SIGTTOU");
  signals[SIGVTALRM].init("SIGVTALRM");
  signals[SIGPROF].init("SIGPROF");
  signals[SIGXCPU].init("SIGXCPU");
  signals[SIGXFSZ].init("SIGXFSZ");
#ifdef SIGWAITING
  signals[SIGWAITING].init("SIGWAITING");
#endif	// SIGWAITING
#ifdef SIGLWP
  signals[SIGLWP].init("SIGLWP");
#endif        // SIGLWP
#ifdef SIGFREEZE
  signals[SIGFREEZE].init("SIGFREEZE");
#endif        // SIGFREEZE
#ifdef SIGTHAW
  signals[SIGTHAW].init("SIGTHAW");
#endif        // SIGTHAW
#endif // 0

}




