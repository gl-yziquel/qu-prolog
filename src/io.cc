// io.cc -
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
// $Id: io.cc,v 1.7 2002/06/04 04:08:15 qp Exp $

#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
// #include <stropts.h>
#include <fcntl.h>

#include "global.h"
#include "io_qp.h"
#include "protos.h"
#include "thread_qp.h"
#include "icm_handle.h"
#include "scheduler.h"
#include "signals.h"
#include "thread_table.h"

extern Scheduler *scheduler;
extern CondList<ICMMessage *> *incoming_icm_message_queue;
extern Signals *signals;
extern ThreadTable *thread_table;
extern ThreadOptions *thread_options;

//-----------------------------------------------
//
// Sockets
//
//-----------------------------------------------
Socket::Socket(const int t, const int p, const int f)
  : FD(f, SOCKET),
    sstatus(SS_INIT),
    smode(SM_INIT),
    stype(t),
    sproto(p),
    istream(-1),
    ostream(-1)
{
  if (t == SOCK_STREAM)
    {
      setConnection();
    }
  else
    {
      setConnectionless();
    }

  //
  // When the socket is closed or the process dies, make sure that we
  // can reuse the address.
  //
  int opt_val = 1;

  SYSTEM_CALL_LESS_ZERO(setsockopt(getFD(), SOL_SOCKET, SO_REUSEADDR,
				   (char *) &opt_val, sizeof(opt_val)));
}

bool
Socket::isConnectAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET ||	sstatus == SS_BIND);
      break;
    }

  return result;
}

bool
Socket::isSendtoAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET || sstatus == SS_BIND ||
		sstatus == SS_CONNECTED);
      break;
    }

  return result;
}

bool
Socket::isRecvfromAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET || sstatus == SS_BIND ||
		sstatus == SS_CONNECTED);
      break;
    }

  return result;
}

bool
Socket::isBroadcast(void) const
{
  int val;
  unsigned int len = sizeof(val);

  if (getsockopt(getFD(),
		 SOL_SOCKET, SO_BROADCAST, (char *)&val, &len))
    {
      return false;
    }

  return val != 0;
}

bool
Socket::openSocket(const int type, const int proto)
{
  stype = type;
  sproto = proto;

  setFD(socket(AF_INET, type, proto));

  setIStream(-1);
  setOStream(-1);

  if (getFD() < 0)
    return false;

  setSocket();
  return true;
}

bool
Socket::closeSocket(void)
{
  if (close(getFD()) < 0)
    return false;
  
  setClose();
  
  return true;
}

void
Socket::setAccepted(Socket *sock, const int new_fd)
{
  sock->setFD(new_fd);
  sock->setConnection();
  sock->setConnected();
}

bool
Socket::isReady(void) const
{
  const int fd = getFD();
  return is_ready(fd, SOCKET);
}

bool
Socket::isEnded(void) const
{
  return sstatus == SS_CLOSED;
}

//-----------------------------------------------
//
// Streams
//
//-----------------------------------------------

bool
imstream::msg_ready(void)
{
#ifdef ICM_DEF
      for (;	 
	   *(iter) != thread->ICMQueue().end();   
	   (*(iter))++)  
	{   
	  if ( (**(iter))->Committed() )  
	    {               
	      continue;		
	    }                    
	  ICMMessage& icm_message = ***iter;
	  icmHandle from_handle = icm_message.Sender();
	  if (icmSameHandle(from_handle, sender_handle) == icmOk)
	    {                   
	      return true;            
	    }                  
	}                       
      (*iter)--;
      return false;
#else // ICM_DEF
      return false;
#endif // ICM_DEF
}

void
imstream::get_a_msg(void)
{
#ifdef ICM_DEF
  bool already_blocked = thread->getBlockStatus().testBlockICM();
  while (!msg_ready())
    {
        thread->getBlockStatus().setBlockICM(*(iter), 
                                             thread->ICMQueue().size(),0);
	scheduler->block_icm(thread);
	  scheduler->Sleep(*incoming_icm_message_queue, *thread_table, 
                           *signals, *thread_options);                 
    }

    ICMMessage& icm_message = ***iter;
#ifdef DEBUG
    icmHandle from_handle = icm_message.Sender();
#endif // DEBUG
    DEBUG_ASSERT(icmSameHandle(from_handle, sender_handle) == icmOk);
    icmDataRec data;
    icmStatus status = icmScanMsg(icm_message.Message(), "%S", &data);
    if (status == icmOk)
      {
	// Nothing.
      }
    else if (status == icmFailed)
      {
	Fatal(__FUNCTION__, 
	      "Format of message doesn't match QP message format");
      }
    else if (status == icmError)
      {
	Fatal(__FUNCTION__, "icmScanMsg() returned icmError");
      }	
    strstreambuf* sbtemp = new strstreambuf(128);
    istream* strintemp = new istream(sbtemp);
    ostream* strouttemp = new ostream(sbtemp);
    (*strin) >> strouttemp->rdbuf();
    delete sb;
    delete strin;
    delete strout;
    sb = sbtemp;
    strin = strintemp;
    strout = strouttemp; 
    strout->write(data.data, data.size);
    strin->clear();
    free(data.data);
    icm_message.Commit();
    if (already_blocked)
      {
        thread->getBlockStatus().setBlockICM(*(iter), 
                                             thread->ICMQueue().size(),0);
	scheduler->block_icm(thread);
      }
#endif // ICM_DEF
}

void
omstream::send_msg(void)
{
#ifdef ICM_DEF
  icmStatus status;
//  (*ostrm) << ends;
  icmDataRec data = { ostrm->pcount(), ostrm->str() };
  icmMsg message = icmFormatMsg(NULL, "%S", &data);
//  DEBUG_ASSERT(status == icmOk);
  status = icmSendMsg(icm_environment->Conn(),
		      to_handle,
		      icm_thread_handle(*icm_environment, *sender_thread),
		      NULL,
		      message);
  DEBUG_ASSERT(status == icmOk);
  ostrm->freeze(0);
  delete ostrm;
  ostrm = new ostrstream();
#endif // ICM_DEF
}

bool
Stream::isEnded(void) const
{
  switch (type)
    {
    case ISTREAM:
      return (desc.i_stream == NULL) || (desc.i_stream->eof());
      break;
    case OSTREAM:
      return (desc.o_stream == NULL);
      break;
    case ISTRSTREAM:
      return (desc.i_strstream == NULL) || (desc.i_strstream->eof());
      break;
    case OSTRSTREAM:
      return (desc.o_strstream == NULL);
      break;
    default:
      DEBUG_ASSERT(false);
      return false;
      break;
    }
}

//
// Change the line counter.
//
void
Stream::newline(void)
{
  lineCounter++;
}

void
Stream::unnewline(void)
{
  lineCounter--;
}

bool
Stream::isReady(void) const
{
  switch (type)
    {
    case ISTREAM:
    case OSTREAM:
      {
	const int fd = getFD();
	return is_ready(fd, type);
      }
      break;
    default:
      return true;
      break;
    }
}

void 
Stream::setProperties(Object* prop)
{
  DEBUG_ASSERT(prop->isStructure());
  // copy the tag
  properties[0] = *(reinterpret_cast<heapobject*>(prop));
  Object* propobject = reinterpret_cast<Object*>(properties);
  DEBUG_ASSERT(propobject->isStructure());
  // copy functor and args
  for (u_int i = 0; i <= OBJECT_CAST(Structure*, propobject)->getArity(); i++)
    {
        OBJECT_CAST(Structure*, propobject)->setArgument(i, OBJECT_CAST(Structure*, prop)->getArgument(i)->variableDereference());
    }
}

void
Stream::setRSProperties(void)
{
  // !! WARNING !! Do the following a different way
  // This sets up the structure tag and arity directly.
  properties[0] = (7 << 8) | 0x0000000CUL;
  DEBUG_ASSERT(reinterpret_cast<Object*>(properties)->isStructure());
  Structure* propstr = reinterpret_cast<Structure*>(properties);
  propstr->setFunctor(atoms->add("$prop"));
  propstr->setArgument(1, atoms->add("read"));
  propstr->setArgument(2, atoms->add("input"));
  propstr->setArgument(3, atoms->add("string"));
  propstr->setArgument(4, atoms->add("none"));
  propstr->setArgument(5, atoms->add("error"));
  propstr->setArgument(6, atoms->add("false"));
  propstr->setArgument(7, atoms->add("test"));
}

bool
is_ready(const int fd, const IOType type)
{
  fd_set fds;

  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  // Set up the time value to indicate a poll
  timeval tv = { 0, 0 };

  int result = 0;

  switch (type)
    {
    case ISTREAM:
      result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      break;
    case OSTREAM:
      result = select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, &tv);
      break;
    case SOCKET:
      result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      break;
    default:
      DEBUG_ASSERT(false);
      result = 0;
      break;
    }

#ifdef DEBUG_IO
  cerr.form("%s result = %ld FD_ISSET(%ld, ...) = %ld\n",
	    __FUNCTION__, result, fd, FD_ISSET(fd, &fds));
#endif
  return result && FD_ISSET(fd, &fds);
}


