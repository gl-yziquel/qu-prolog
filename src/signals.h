// signals.h -
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
// $Id: signals.h,v 1.4 2006/01/31 23:17:51 qp Exp $

#ifndef	SIGNALS_H
#define	SIGNALS_H


#include <signal.h>
#include <string.h>

#include "debug.h"
#include "defs.h"
#include "status.h"

class SignalStatus : public Status <word8>
{
private:
  static const word8 ENABLE_SIGNALS	= 0x01;
  static const word8 SIGNALS		= 0x02;
public:
  //
  // Set the flags.
  //
  void setEnableSignals(void)	{ set(ENABLE_SIGNALS); }
  void setSignals(void)		{ set(SIGNALS); }
  //
  // Reset the flags.
  //
  void resetEnableSignals(void)		{ reset(ENABLE_SIGNALS); }
  void resetSignals(void)		{ reset(SIGNALS); }
  //
  // Test the flags.
  //
  bool testEnableSignals(void) const	{ return test(ENABLE_SIGNALS);}
  bool testSignals(void) const		{ return test(SIGNALS); }
  
  SignalStatus(void)			{ }
};

class Signals
{
private:
  class Signal
  {
  private:
    int signal;
    char *name;
  public:
    //
    // Set and clear the signal.
    //
    void Increment(void) { signal++; }
    void Decrement(void) { signal--; }
    
    void Clear(void) { signal = 0; }

    bool IsSet(void)
      {
	bool is_set;
	is_set = signal != 0;
	return is_set;
      }
    
    //
    // Get the cell representation of the signal.
    //
    const char *Name(void) const { return name; }
    
    //
    // Initialise the entry.
    //
    void init(const char *n) {
      int len = strlen(n);
      name = new char[len+1];
      strcpy(name, n);
    }

  public:    
    Signal(void) : signal(0), name(NULL) { }
    ~Signal(void) { }
  };

  Signal signals[NSIG + 1];

  SignalStatus signal_status;

public:
  void Increment(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      signals[sig].Increment();
    }
  void Decrement(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      signals[sig].Decrement();
    }
  bool IsSet(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      return signals[sig].IsSet();
    }
  void Clear(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      signals[sig].Clear();
    }
  const char *Name(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      return signals[sig].Name();
    }

  SignalStatus& Status(void) { return signal_status; }

  Signals(void);
};

#endif	// SIGNALS_H
