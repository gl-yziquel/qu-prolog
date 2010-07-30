// block.h - Information carried by blocked threads.
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
// $Id: block.h,v 1.13 2006/02/14 02:40:09 qp Exp $

#ifndef	BLOCK_H
#define	BLOCK_H

#include "defs.h"
#include "timeval.h"
#include <list>
#include <sys/types.h>
#ifndef WIN32
        #include <sys/time.h>
#endif

#ifdef WIN32
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <winsock2.h>
#endif

class Thread;
class Code;
class IOManager;
class Message;


class BlockStatus
{
 private:
  enum RunType {
    RUNNABLE,       
    RESTART_IO,
    RESTART_MSG,
    RESTART_TIME,
    RESTART_WAIT,
    BLOCKED
  };

  RunType status;
 public:
  BlockStatus() : status(RUNNABLE) {}

  ~BlockStatus() {}

  bool isBlocked(void) const { return status == BLOCKED; }
  bool isRunnable(void) const { return status == RUNNABLE; }
  bool isRestarted(void) const 
    { return (status != BLOCKED) && (status != RUNNABLE); }

  bool isRestartTime(void) const { return status == RESTART_TIME; }
  bool isRestartIO(void)   const { return status == RESTART_IO; }
  bool isRestartMsg(void)  const { return status == RESTART_MSG; }
  bool isRestartWait(void) const { return status == RESTART_WAIT; }

  void setBlocked(void)     { status = BLOCKED; }
  void setRunnable(void)    { status = RUNNABLE; }
  void setRestartIO(void)   { status = RESTART_IO; }
  void setRestartMsg(void)  { status = RESTART_MSG; }
  void setRestartTime(void) { status = RESTART_TIME; }
  void setRestartWait(void) { status = RESTART_WAIT; }

};


// The base class for blocking objects

class BlockingObject
{
private:
  Thread* thread;     // the blocked thread
public:
  explicit BlockingObject(Thread* const t) : thread(t) {}

  virtual ~BlockingObject() {}

  Thread* getThread(void) { return thread; }

  virtual bool unblock(Timeval& tout) = 0;

  virtual bool hasFD(void) = 0;

#ifdef WIN32
  virtual int getFD(void) = 0;
#endif

  virtual void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) = 0;
};

class BlockingIOObject : public BlockingObject
{
 private:
  Timeval retry_time;            // Absolute time of retry
  int fd;                       // The fd to wait on
  IOType io_type;               // Type of io to be waited on
  IOManager* iomp;
 public:
  BlockingIOObject(Thread* const t, int f, IOType iot, IOManager* mp)
    : BlockingObject(t), retry_time(-1, 0), fd(f), io_type(iot), iomp(mp) {}

  bool unblock(Timeval& tout);

  bool hasFD(void) { return true; }

  int getFD(void) { return fd; }

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd);
};

class BlockingTimeoutObject : public BlockingObject
{
 private:
  Timeval timeout;
 public:
  BlockingTimeoutObject(Thread* const t, double to) 
    : BlockingObject(t), timeout(to) {}

  bool unblock(Timeval& tout);

  bool hasFD(void) { return false; }

#ifdef WIN32
  int getFD(void) { return NULL; }
#endif

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) {}

};

class BlockingMessageObject : public BlockingObject
{
 private:
  Timeval timeout;
  std::list<Message *>::iterator *iter;
  u_int size;
 public:
  BlockingMessageObject(Thread* const t, double to, 
			std::list<Message *>::iterator *i);

  bool unblock(Timeval& tout);

  bool hasFD(void) { return true; }

#ifdef WIN32
  int getFD(void) { return NULL; }
#endif

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd);

};

class BlockingWaitObject : public BlockingObject
{
 private:
  Code* code; 
  Timeval timeout;
  u_int stamp;
 public:
  BlockingWaitObject(Thread* const t, Code* c, double to);

  bool unblock(Timeval& tout);

  bool hasFD(void) { return false; }

#ifdef WIN32
  int getFD(void) { return NULL; }
#endif

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) {}

};



#endif	// BLOCK_H

