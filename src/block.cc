// block.cc -
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
// $Id: block.cc,v 1.15 2006/02/14 02:40:08 qp Exp $

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


bool 
BlockingIOObject::unblock(Timeval& tout)
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
BlockingTimeoutObject::unblock(Timeval& tout)
{
  Timeval now;

  if (timeout.isForever())
    {
      return false;
    }
  else if (timeout <= now)
    {
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    { 
      Timeval delta(timeout, now);
      if (delta < tout) tout = delta;
      return false;
    }
}

BlockingMessageObject::BlockingMessageObject(Thread* const t, double to, 
					     list<Message *>::iterator *i)
  : BlockingObject(t), timeout(to), iter(i)
{
  size = static_cast<u_int>(t->MessageQueue().size());
}

void
BlockingMessageObject::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
}

bool 
BlockingMessageObject::unblock(Timeval& tout)
{
  Timeval now;

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
  else if (timeout.isForever())
    {
      return false; 
    }
  else if (timeout <= now)
    {
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    { 	 
      Timeval delta(timeout, now);
      if (delta < tout) tout = delta;
      return false;
    }
}

WaitPred:: WaitPred(Object* pn, int a, DynamicPredicate* pp, int s) : 
  predname(pn), arity(a), predptr(pp)
{
  stamp = s;
}

void WaitPred::updateStamp(void)
{
  stamp = predptr->GetStamp();
}

BlockingWaitObject::BlockingWaitObject(Thread* const t, Code* c, Object* preds,
				       Object* until, Object* every, 
				       PredTab* predicates) 
  :  BlockingObject(t), code(c)
{
  setIsWait();
  setWakeOnTimeout(false);
  stamp = c->GetStamp();
  for (Object* predlist = preds; predlist->isCons(); 
       predlist = OBJECT_CAST(Cons *, predlist)->getTail()->variableDereference())
    {
      Object* pred = OBJECT_CAST(Cons *, predlist)->getHead()->variableDereference();
      assert(pred->isStructure());
      Structure* predstr = OBJECT_CAST(Structure*, pred);
      int stamp = -1;
      if (predstr->getFunctor()->variableDereference() == AtomTable::minus)
        {
          stamp = predstr->getArgument(2)->variableDereference()->getInteger();
          predstr = OBJECT_CAST(Structure*, predstr->getArgument(1)->variableDereference());
        }
      Object* predname = predstr->getArgument(1)->variableDereference();
      assert(predname->isAtom());
      Object* arityobj = predstr->getArgument(2)->variableDereference();
      int arity =  arityobj->getInteger();
      PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, predname), arity,
				       atoms, code);
      DynamicPredicate* predptr = predicates->getCode(loc).getDynamicPred();
      if (stamp == -1) stamp = predptr->GetStamp();
      WaitPred* wp = new WaitPred(predname, arity, predptr, stamp);
      wait_preds.push_back(wp);  
    }
  double until_time;
  if (until->isInteger()) 
    {
      until_time = until->getInteger();
      timeout = Timeval(until_time);
    }
  else
    {
      assert(until->isDouble());
      until_time = until->getDouble();
      timeout = Timeval(until_time);
    }
  if (every->isInteger()) 
    {
      retry_timeout = every->getInteger();
      if (retry_timeout != -1)
	timeout = Timeval(retry_timeout);
    }
  else
    {
      assert(every->isDouble());
      retry_timeout = every->getDouble();
    }
}

BlockingWaitObject::~BlockingWaitObject(void)
{
  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      delete *iter;
    }
}

void
BlockingWaitObject::update(void)
{
  stamp = code->GetStamp();
  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      WaitPred* wp = *iter;
      wp->updateStamp();
    }
}

/*
Object*
BlockingWaitObject::extract_changed_preds(void)
{
  Object* result = AtomTable::nil;

  for (int i = wait_preds.size()-1; i >= 0; i--)
    {
      WaitPred* wp = wait_preds[i];
      if (wp->modified)
	{
	  Structure* predstruct = getThread()->TheHeap().newStructure(2);
	  predstruct->setFunctor(AtomTable::divide);
	  predstruct->setArgument(1, wp->predname);
	  predstruct->setArgument(2, getThread()->TheHeap().newInteger(wp->arity));
	  result = getThread()->TheHeap().newCons(predstruct, result);
	}
    }
  return result;
}
*/

bool BlockingWaitObject::is_unblocked(void)
{
  if (wait_preds.begin() == wait_preds.end())
    return stamp < code->GetStamp();

  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      WaitPred* wp = *iter;
      if (wp->stamp < wp->predptr->GetStamp())
	return true;
    }
  return false;
}

void BlockingWaitObject::dump(void)
{
  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      WaitPred* wp = *iter;
      cerr << OBJECT_CAST(Atom*, wp->predname)->getName() 
	   << "/" << wp->arity << " " << wp->stamp;
    }
}

bool 
BlockingWaitObject::unblock(Timeval& tout)
{
  Timeval now;

  if (is_unblocked())
    {
      getThread()->getBlockStatus().setRestartWait();
      if (retry_timeout != -1) 
	timeout = Timeval(retry_timeout);

      return true;
    }
  else if (timeout.isForever())
    {
      return false;
    }
  else if (timeout <= now)
    {
      if (retry_timeout != -1) 
	timeout = Timeval(retry_timeout);
      setWakeOnTimeout(retry_timeout == -1);
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    { 	 
      Timeval delta(timeout, now);
      if (delta < tout) tout = delta;
      return false;
    }
}
