// thread_status.h -
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
// $Id: thread_status.h,v 1.3 2002/03/08 00:29:34 qp Exp $

#ifndef	THREAD_STATUS_H
#define	THREAD_STATUS_H

#include "defs.h"
#include "status.h"

//
// Flags require restoring to old value on backtracking.
//
class	ThreadStatus : private Status <word8>
{
private:
  
  static const word8 FAST_RETRY		= 0x01;
  static const word8 OCCURS_CHECK	= 0x02;
  static const word8 HEAT_WAVE		= 0x04;
  static const word8 DOING_RETRY     	= 0x08;
  static const word8 DO_GC	     	= 0x10;
  static const word8 NECK_CUT_RETRY     = 0x20;
  static const word8 TIMESLICE          = 0x40;
  
public:
  
  //
  // Set the flags.
  //
  void	setFastRetry(void)		{ set(FAST_RETRY); }
  void	setOccursCheck(void)		{ set(OCCURS_CHECK); }
  void	setHeatWave(void)		{ set(HEAT_WAVE); }
  void  setDoingRetry(void)             { set(DOING_RETRY); }
  void  setDoGC(void) 		        { set(DO_GC); }
  void  setNeckCutRetry(void) 	        { set(NECK_CUT_RETRY); }
  void  setTimeslicing(void) 	        { set(TIMESLICE); }
  
  //
  // Reset the flags.
  //
  void	resetFastRetry(void)		{ reset(FAST_RETRY); }
  void	resetOccursCheck(void)		{ reset(OCCURS_CHECK); }
  void	resetHeatWave(void)		{ reset(HEAT_WAVE); }
  void  resetDoingRetry(void)           { reset(DOING_RETRY); }
  void  resetDoGC(void)           	{ reset(DO_GC); }
  void  resetNeckCutRetry(void)         { reset(NECK_CUT_RETRY); }
  void  resetTimeslicing(void)          { reset(TIMESLICE); }
  
  //
  // Test the flags.
  //
  bool	testFastRetry(void) const	{ return(test(FAST_RETRY)); }
  bool	testOccursCheck(void) const	{ return(test(OCCURS_CHECK)); }
  bool	testHeatWave(void) const	{ return(test(HEAT_WAVE)); }
  bool  testDoingRetry(void) const      { return(test(DOING_RETRY)); }
  bool  testDoGC(void) const      	{ return(test(DO_GC)); }
  bool  testNeckCutRetry(void) const    { return(test(NECK_CUT_RETRY)); }
  bool  testTimeslicing(void) const     { return(test(TIMESLICE)); }
  
  ThreadStatus(void)			
  { 
    setOccursCheck(); 
    setTimeslicing();
  }
};

#endif	// THREAD_STATUS_H
