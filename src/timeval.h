// timeval.h - Routines for handling time. Covers only the timeval structure.
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
// $Id: timeval.h,v 1.2 2002/11/03 08:37:35 qp Exp $

#ifndef	TIMEVAL_H
#define	TIMEVAL_H

#include <sys/time.h>
#include <unistd.h>
#include <iostream>

#include "errors.h"

class Timeval
{
private:
  timeval tv;

public:
  Timeval(const time_t sec, const time_t usec = 0)
    {
      DEBUG_ASSERT(sec != (time_t) -1 || usec == 0);// sec == -1 -> usec == 0
      DEBUG_ASSERT(usec < 1000000);		// 1 million

      tv.tv_sec = sec; tv.tv_usec = usec;
    }
  Timeval(void)
    {
      SYSTEM_CALL_LESS_ZERO(gettimeofday(&tv, NULL));
    }
  Timeval(const Timeval& t)
    {
      tv.tv_sec = t.tv.tv_sec;
      tv.tv_usec = t.tv.tv_usec;
    }

  time_t Sec(void) const { return tv.tv_sec; }
  time_t MicroSec(void) const { return tv.tv_usec; }

  bool IsForever(void) const { return Sec() == (time_t) -1; }

  void operator=(const Timeval& t)
    {
      tv.tv_sec = t.tv.tv_sec;
      tv.tv_usec = t.tv.tv_usec;
    }
  bool operator==(const Timeval& t) const
    {
      return timercmp(&tv, &t.tv, ==);
    }
  bool operator!=(const Timeval& t) const
    {
      return timercmp(&tv, &t.tv, !=);
    }
  bool operator<(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return t.Sec() != (time_t) -1;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return true;
	}
      else
	{
	  return timercmp(&tv, &t.tv, <);
	}
    }
  bool operator<=(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return t.Sec() == (time_t) -1;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return true;
	}
      else
	{
	  return timercmp(&tv, &t.tv, <=);
	}
    }
  bool operator>(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return t.Sec() != (time_t) -1;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return false;
	}
      else
	{
	  return timercmp(&tv, &t.tv, >);
	}
    }
  bool operator>=(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return t.Sec() == (time_t) -1;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return false;
	}
      else
	{
	  return timercmp(&tv, &t.tv, >=);
	}
    }
};

inline std::ostream& operator<<(std::ostream& ostrm, const Timeval& t)
{
  ostrm << "sec = " << t.Sec() << " usec = " << t.MicroSec();

  return ostrm;
}

#endif	// TIMEVAL_H
