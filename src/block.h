// block.h - Information carried by blocked threads.
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
// $Id: block.h,v 1.2 2000/12/13 23:10:00 qp Exp $

#ifndef	BLOCK_H
#define	BLOCK_H

#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

#include "cond_list.h"
#include "defs.h"
#include "config.h"
#include "debug.h"
#include "errors.h"
#include "icm_message.h"
#include "io_qp.h"
#include "status.h"

class BlockStatus : private Status <word8>
{
private:
  //
  // Status values.
  //
  static const word8 BLOCK_RETRY	= 0x01;	// Waiting to retry
  static const word8 RESTART_RETRY	= 0x02;	// Retry the operation

  static const word8 BLOCK_ICM		= 0x04;	// Waiting for IPC message
  static const word8 RESTART_ICM	= 0x08; // Restart IPC operation

  static const word8 BLOCK_IO		= 0x10;	// Waiting for IO
  static const word8 RESTART_IO		= 0x20;	// Restart IO operation

  static const word8 BLOCK_WAIT		= 0x40;	// Waiting for something
  static const word8 RESTART_WAIT	= 0x80; // Restart

  //
  // Timeouts
  //
  time_t timeout;		// 0 if no timeout
				// >0 if timeout (absolute time value)
  bool timed_out;		// true if timeout has passed

  //
  // Retry
  //
  time_t retry_time;		// Absolute time of retry

  //
  // IO
  //
  int fd;			// The fd to wait on
  IOType io_type;		// Type of io to be waited on

  // 
  // ICM
  //
  CondList<ICMMessage *>::iterator iter;
  size_t queue_size;

  //
  // Wait
  //
  word32 db_stamp;			// Stamp value when the wait started
  word32 record_db_stamp;		// Stamp value when the wait started

public:
  BlockStatus(void)
  {
    Clear();
  }

  ~BlockStatus(void) { }

  //
  // Timeout information.
  //
  bool IsTimeout(void) const { return timeout > 0; }
  time_t Timeout(void) const { return timeout; }
  void setTimeout(time_t t) { timeout = t; }
  
  bool IsTimedOut(void) const { return timed_out; }
  void SetTimedOut(void) { timed_out = true; }

  //
  // Test block/restart status.
  //
  bool IsBlocked(void) const { return (testBlockWait() ||
				       testBlockICM() ||
				       testBlockIO()); }
  bool IsRestarted(void) const { return (testRestartICM() ||
					 testRestartWait() ||
					 testRestartIO()); }

//  bool testBlockRetry(void) const { return test(BLOCK_RETRY); }
//  bool testRestartRetry(void) const { return test(RESTART_RETRY); }
  bool testBlockIO(void) const { return test(BLOCK_IO); }
  bool testRestartIO(void) const { return test(RESTART_IO); }
  bool testBlockICM(void) const { return test(BLOCK_ICM); }
  bool testRestartICM(void) const { return test(RESTART_ICM); }
  bool testBlockWait(void) const { return test(BLOCK_WAIT); }
  bool testRestartWait(void) const { return test(RESTART_WAIT); }

  //
  // Set/clear a block waiting on a retry.
  //
//  void setBlockRetry(const time_t);		// When to retry
//  void resetBlockRetry(void) { reset(BLOCK_RETRY); }

  //
  // Set/clear a restart on a retry
  //
//  void setRestartRetry(void) { set(RESTART_RETRY); }
//  void resetRestartRetry(void) { reset(RESTART_RETRY); }

  //
  // Set/clear a block waiting on some IO.
  //
  void setBlockIO(const int,
		  const IOType,
		  const time_t = 0);		// Optional timeout
  void resetBlockIO(void) { reset(BLOCK_IO); }

  //
  // Set/clear a restart for an IO operation.
  //
  void setRestartIO(void) { set(RESTART_IO); }
  void resetRestartIO(void) { reset(RESTART_IO); }

  // 
  // Set/clear a block waiting on an ICM message.
  //
  void setBlockICM(CondList<ICMMessage *>::iterator,
		   const size_t,
		   const time_t = 0);		// Optional timeout
  void resetBlockICM(void) { reset(BLOCK_ICM); }

  //
  // Set/clear a restart on an ICM operation.
  //
  void setRestartICM(void) { set(RESTART_ICM); }
  void resetRestartICM(void) { reset(RESTART_ICM); }

  //
  // Set/clear a block waiting on some sort of timeout.
  //
  void setBlockWait(const word32,		// Stamp value of db
		    const word32,		// Stamp value of record_db
		    const time_t);		// Compulsory timeout
  void resetBlockWait(void) { reset(BLOCK_WAIT); }

  //
  // Set/clear a restart
  //
  void setRestartWait(void) { set(RESTART_WAIT); }
  void resetRestartWait(void) { reset(RESTART_WAIT); }

  //
  // Clear status completely.
  //
  void Clear(void);

  //
  // When should this thread be retried?
  //
//  time_t RetryTime(void) const
//  {
//    DEBUG_ASSERT(testBlockRetry() || testRestartRetry());
//
//    return retry_time;
//  }

  //
  // Return the FD for the IO block (IO block only).
  //
  int getFD(void) const
  {
    DEBUG_ASSERT(testBlockIO() || testRestartIO());

    return fd;
  }

  //
  // Return the input/output type of the IO required (IO block only).
  //
  IOType getIOType(void) const
  {
    DEBUG_ASSERT(testBlockIO() || testRestartIO());

    return io_type;
  }

  CondList<ICMMessage *>::iterator getIter(void) 
    {
      DEBUG_ASSERT(testBlockICM());

      return iter;
    }

  size_t QueueSize(void) const
    { 
//      DEBUG_ASSERT(testBlockICM() || testBlockWait() || testRestartIO());

      return queue_size;
    }

  word32 DBStamp(void) const
    {
      DEBUG_ASSERT(testBlockWait());

      return db_stamp;
    }

  word32 RecordDBStamp(void) const
    {
      DEBUG_ASSERT(testBlockWait());

      return record_db_stamp;
    }
};

//
// This is a class for keeping track of IO descriptors that are blocked.
// It should work with SYSV and BSD systems, but I don't know about POSIX.
//
class BlockedIO
{
private:
  fd_set blocked_read;	// fds that someone is waiting on reading from
  fd_set blocked_write;	// fds that someone is waiting on writing to

  fd_set polled_read;	// fds that have recently been polled for reading
  fd_set polled_write;	// fds that have recenlty been polled for writing

  int max_blocked_fd;	// Top blocked fd

  //
  // Arrays for counting how many threads are blocked on each fd.
  //
  int *blocked_input_counts;
  int *blocked_output_counts;
public:
  BlockedIO(void);
  
  ~BlockedIO(void)
  {
    delete blocked_input_counts;
    delete blocked_output_counts;
  }

  void Add(const int, const IOType);

  void Remove(const int, const IOType);

  bool Poll(const int msec = 0);

  //  bool IsReady(const int fd, const IOType) const;
};

#endif	// BLOCK_H

