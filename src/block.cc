// block.cc -
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
// $Id: block.cc,v 1.14 2005/03/08 00:34:59 qp Exp $

#include "config.h"

#ifdef WIN32
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <io.h>
#else
        #include <unistd.h>
#endif

//#include "block.h"
#include "io_qp.h"
#include "thread_qp.h"

time_t absoluteTimeout(const time_t timeout)
{
  if (timeout == static_cast<time_t>(-1))
    {
      return timeout;
    }
  else
    {
      return timeout + time(NULL);
    }
}
 
bool 
BlockingIOObject::unblock(int& tout)
{
  if (io_type == IMSTREAM)
    {
      if ((iomp->GetStream(fd) == NULL) ||
	  (iomp->GetStream(fd)->msgReady()))
	{
	  getThread()->getBlockStatus().setRestartIO();
	  return true;
	}
      else
	{
	  return false;
	}
    }
  else
    {
      if (is_ready(fd, io_type))
	{
	  getThread()->getBlockStatus().setRestartIO();
	  return true;
	}
      else
	{
	  return false;
	}
    }
}

void
BlockingIOObject::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
  if (io_type != IMSTREAM)
    {
      if (fd > max_fd) max_fd = fd;
      FD_SET(fd, rfds);
    }
}

bool 
BlockingTimeoutObject::unblock(int& tout)
{
  const time_t now = time(NULL);
  if (timeout > 0 && timeout <= now)
    {
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    {
      if (timeout > 0)
	{
	  int delta = static_cast<int>(timeout - now);
	  if ((tout == 0) || tout > delta) tout = delta;
	}
      return false;
    }
}

BlockingMessageObject::BlockingMessageObject(Thread* const t, time_t to, 
					     list<Message *>::iterator *i)
  : BlockingObject(t), iter(i)
{
  timeout = absoluteTimeout(to);
  size = static_cast<u_int>(t->MessageQueue().size());
}

void
BlockingMessageObject::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
}

bool 
BlockingMessageObject::unblock(int& tout)
{
  const time_t now = time(NULL);

  if (size != getThread()->MessageQueue().size())
    {
       *iter = getThread()->MessageQueue().begin();
      for (u_int i = 1; i < size; i++)
	{
	  (*iter)++;
	}
      getThread()->getBlockStatus().setRestartMsg();
      return true;
    }
  else if (timeout > 0 && timeout <= now)
    {
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    {      
      if (timeout > 0)
	{
	  int delta = static_cast<int>(timeout - now);
	  if ((tout == 0) || tout > delta) tout = delta;
	}
      return false;
    }
}

BlockingWaitObject::BlockingWaitObject(Thread* const t, Code* c, time_t to) 
  :  BlockingObject(t), code(c)
{
  timeout = absoluteTimeout(to);
  stamp = c->GetStamp();
}


bool 
BlockingWaitObject::unblock(int& tout)
{
  const time_t now = time(NULL);

  if (stamp < code->GetStamp())
    {
      getThread()->getBlockStatus().setRestartWait();
      return true;
    }
  else if (timeout > 0 && timeout <= now)
    {
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    {
      if (timeout > 0)
	{
	  int delta = static_cast<int>(timeout - now);
	  if ((tout == 0) || tout > delta) tout = delta;
	}
      return false;
    }
}
