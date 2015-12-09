// timeval.h - Routines for handling time. Covers only the timeval structure.
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
// $Id: timeval.h,v 1.7 2006/03/30 22:50:31 qp Exp $

#ifndef	TIMEVAL_H
#define	TIMEVAL_H

#include <math.h>

#ifdef WIN32
#include <time.h>
#include <winsock2.h>
#include <io.h>
#include <windows.h>	
extern int gettimeofday(struct timeval* tp, void* tzp);
typedef u_int suseconds_t;
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <iostream>

#include "errors.h"

class Timeval
{
private:
  timeval tv;

public:
  Timeval(const time_t sec, const suseconds_t usec = 0)
    {
      assert(sec != (time_t) -1 || usec == 0);// sec == -1 -> usec == 0
      assert(usec < 1000000);		// 1 million

      tv.tv_sec = sec; 
      tv.tv_usec = usec;
    }
  Timeval(void)
    {
      SYSTEM_CALL_LESS_ZERO(gettimeofday(&tv, NULL));
    }

  // t1 - t2
  Timeval(const Timeval& t1, const Timeval& t2)
    {
      if (t1.isForever())
        {
          tv.tv_sec = (time_t) -1;
          tv.tv_usec = 0;
        }
      else if (t1.MicroSec() < t2.MicroSec())
        {
          tv.tv_usec = 1000000 + t1.MicroSec() - t2.MicroSec();
          tv.tv_sec = t1.Sec() - t2.Sec() - 1;
        }
      else
        {
          tv.tv_usec = t1.MicroSec() - t2.MicroSec();
          tv.tv_sec = t1.Sec() - t2.Sec();
        }
    }
      
  Timeval(const double d)
    {
      if (d < 0) 
        { 
           tv.tv_sec = (time_t) -1;  
           tv.tv_usec = 0; 
        } 
      else
        {
          gettimeofday(&tv, NULL);
          long s = (long)floor(d);
          long m = (long)floor((d-s)*1000000);
          long ms = tv.tv_usec + m;
          long secs = tv.tv_sec + s + ms / 1000000;
          long usecs = ms % 1000000;
          tv.tv_sec = (time_t)secs;
          tv.tv_usec = (suseconds_t)usecs;
        }
    }

  time_t Sec(void) const { return tv.tv_sec; }
  suseconds_t MicroSec(void) const { return tv.tv_usec; }

  bool isForever(void) const { return Sec() == (time_t) -1; }

  void setTime(time_t s, suseconds_t ms)
  {
    tv.tv_sec = s;
    tv.tv_usec = ms;
  }

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
	  return false;
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
/*
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
*/
};

inline std::ostream& operator<<(std::ostream& ostrm, const Timeval& t)
{
  ostrm << "sec = " << t.Sec() << " usec = " 
        << t.MicroSec();

  return ostrm;
}

#endif	// TIMEVAL_H
