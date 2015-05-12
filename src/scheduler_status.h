// scheduler_status.h -
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
// $Id: scheduler_status.h,v 1.2 2001/12/17 04:27:33 qp Exp $

#ifndef	SCHEDULER_STATUS_H
#define	SCHEDULER_STATUS_H

#include "defs.h"
#include "status.h"

class SchedulerStatus : private Status <word8>
{
private:
  static const word8 ENABLE_TIMESLICE = 0x01;
  static const word8 TIMESLICE = 0x02;
  static const word8 RESTART = 0x04;		// Restart from front of queue

public:
  //
  // Set flags.
  //
  void setEnableTimeslice(void)	{ set(ENABLE_TIMESLICE); }
  void setTimeslice(void)	{ set(TIMESLICE); }
  void setRestart(void)		{ set(RESTART); }
  //
  // Clear flags.
  //
  void resetEnableTimeslice(void)	{ reset(ENABLE_TIMESLICE); }
  void resetTimeslice(void)		{ reset(TIMESLICE); }
  void resetRestart(void)		{ reset(RESTART); }
  //
  // Test flags.
  //
  bool testEnableTimeslice(void) const	{ return test(ENABLE_TIMESLICE); }
  bool testTimeslice(void) const	{ return test(TIMESLICE); }
  bool testRestart(void) const		{ return test(RESTART); }

};
#endif	// SCHEDULER_STATUS_H

