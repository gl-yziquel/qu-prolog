// block.cc -
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
// $Id: block.cc,v 1.3 2002/06/04 04:08:14 qp Exp $

#include "config.h"

#include <unistd.h>

#include "block.h"

static time_t
AbsoluteTimeout(const time_t timeout)
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
 
//
// Set/clear a block waiting on a retry
//
//void
//BlockStatus::setBlockRetry(const time_t r)
//{
//  Clear();
//  set(BLOCK_RETRY);
//  
//  retry_time = r;
//}

// 
// Set up a block waiting on an ICM message.
//
void 
BlockStatus::setBlockICM(CondList<ICMMessage *>::iterator i,
			 const size_t qs,
			 const time_t to = 0)		// Optional timeout
{
  Clear();
  set(BLOCK_ICM);

  iter = i;
  queue_size = qs;
  timeout = AbsoluteTimeout(to);

#if defined(DEBUG_BLOCK) && defined(DEBUG_ICM)
  cerr.form("%s queue_size = %ld timeout = %ld\n",
	    __FUNCTION__, queue_size, timeout);
#endif
}

//
// Set up a block waiting on some IO.
//
void 
BlockStatus::setBlockIO(const int f,
			const IOType type,
			const time_t to = 0)		// Optional timeout
{
#if defined(DEBUG_BLOCK) && defined(DEBUG_IO)
  cerr.form("%s fd = %ld io_direction = %ld timeout %ld\n",
	    __FUNCTION__, f, type, to);
#endif

  Clear();
  set(BLOCK_IO);

  fd = f;
  io_type = type;
  
  timeout = AbsoluteTimeout(to);
}

void
BlockStatus::setBlockWait(const word32 dbs,
			  const word32 rdbs,
			  const time_t to)
{
#if defined(DEBUG_BLOCK) && defined(DEBUG_TIMEOUT)
  cerr.form("%s db_stamp = %ld record_db_stamp = %ld timeout = %ld\n",
            __FUNCTION__, dbs, rdbs, to);
#endif

  Clear();
  set(BLOCK_WAIT);

  db_stamp = dbs;
  record_db_stamp = rdbs;
  timeout = AbsoluteTimeout(to);
}

void
BlockStatus::Clear(void)
{
  clear();
  timeout = 0;
  timed_out = false;
}

BlockedIO::BlockedIO(void)
{
  // Start off with a blank slate
  FD_ZERO(&blocked_read);
  FD_ZERO(&blocked_write);
  
  FD_ZERO(&polled_read);
  FD_ZERO(&polled_write);
  
  // No fds yet
  max_blocked_fd = -1;

  //
  // Allocate and initialise the array of counts of blocked threads.
  //
  int max_fds = sysconf(_SC_OPEN_MAX);
  blocked_input_counts = new int[max_fds];
  if (blocked_input_counts == NULL)
    {
      Fatal("%s: Couldn't create array of blocked input counts\n",
	    __FUNCTION__);
    }
  blocked_output_counts = new int[max_fds];
  if (blocked_output_counts == NULL)
    {
      Fatal("%s: Couldn't create array of blocked output counts\n",
	    __FUNCTION__);
    }

  for (int i = 0; i < max_fds; i++)
    {
      blocked_input_counts[i] = 0;
      blocked_output_counts[i] = 0;
    }
}

void
BlockedIO::Add(const int fd, const IOType type)
{
#if defined(DEBUG_BLOCK) && defined(DEBUG_IO)
  cerr.form("%s fd = %ld type = %ld\n", __FUNCTION__, fd, type);
#endif

  switch (type)
    {
    case ISTREAM:
    case ISTRSTREAM:
      FD_SET(fd, &blocked_read);
      blocked_input_counts[fd]++;
      break;
    case OSTREAM:
    case OSTRSTREAM:
      FD_SET(fd, &blocked_write);
      blocked_output_counts[fd]++;
      break;
    case SOCKET:
      FD_SET(fd, &blocked_read);
      blocked_input_counts[fd]++;
      break;
    default:
      // This should never happen.
      DEBUG_ASSERT(false);
      break;
    }

  // Keep track of how many fds we need to select on in BlockedIO::Poll()
  if (fd > max_blocked_fd)
    {
      max_blocked_fd = fd;
    }
}

void
BlockedIO::Remove(const int fd, const IOType type)
{
#if defined(DEBUG_BLOCK) && defined(DEBUG_IO)
  cerr.form("%s fd = %ld type = %ld\n", __FUNCTION__, fd, type);
#endif 

  switch (type)
    {
    case ISTREAM:
    case ISTRSTREAM:
    case SOCKET:
      blocked_input_counts[fd]--;
      if (blocked_input_counts[fd] == 0)
	{
	  FD_CLR(fd, &blocked_read);
	}
      break;
    case OSTREAM:
    case OSTRSTREAM:
      blocked_output_counts[fd]--;
      if (blocked_output_counts[fd] == 0)
	{
	  FD_CLR(fd, &blocked_write);
	}
      break;
    default:
      // This should never happen.
      DEBUG_ASSERT(false);
      break;
    }

  // Keep track of how many fds we need to select on in BlockedIO::Poll()
  if (fd == max_blocked_fd)
    {
      max_blocked_fd = -1;
      for (int i = fd - 1; i >= 0; i--)
	{
	  if (blocked_input_counts[i] > 0 ||
	      blocked_output_counts[i] > 0)
	    {
	      max_blocked_fd = i;
	      break;
	    }
	}
    }
}

static void
copy_fd_set(fd_set *copy, fd_set *original, const int max_fd)
{
  for (int i = 0; i <= max_fd; i++)
    {
      if (FD_ISSET(i, original))
	{
	  FD_SET(i, copy);
	}
      else
	{
	  FD_CLR(i, copy);
	}
    }
}

bool
BlockedIO::Poll(const int msec = 0)		// Maximum time to wait
{
  copy_fd_set(&polled_read, &blocked_read, max_blocked_fd);
  copy_fd_set(&polled_write, &blocked_write, max_blocked_fd);
  
  timeval timeout = { 0, msec };

  const int result = select(max_blocked_fd + 1,
			    &polled_read, &polled_write, NULL, &timeout) > 0;
  
#if defined(DEBUG_BLOCK) && defined(DEBUG_IO)
  cerr.form("%s max_blocked_fd = %ld result = %ld\n",
	    __FUNCTION__, max_blocked_fd, result);
#endif
  
  return result > 0;
}

