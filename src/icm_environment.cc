// icm_environment.cc -
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
// $Id: icm_environment.cc,v 1.16 2005/11/26 23:34:30 qp Exp $

#include "config.h"

#ifdef ICM_DEF
#include "icm.h"
#include "icmP.h"
#include "icm_handle.h"
#include "icm_environment.h"
#include "thread_qp.h"
#include "thread_table.h"
#include "atom_table.h"

bool
ICMEnvironment::Register(char *ps)
{
  assert(ps != NULL);

#ifdef DEBUG_ICM
  cerr << __FUNCTION__ << " " << ps << endl;
#endif

  assert(process_symbol == NULL);

  icmHandle tmp = icmParseHandle(ps);
  
#ifdef DEBUG_ICM      
  cerr << __FUNCTION__ << " Before icmRegisterAgent()" << endl;
#endif
  
  const icmStatus status = icmRegisterAgent(conn, tmp, NULL, &handle);
  
#ifdef DEBUG_ICM
  char buf[MAXSTRING];
  (void) icmHandleName(handle, buf, 512);
  cerr << __FUNCTION__ << "After icmRegisterAgent() " << buf << endl;
#endif
  switch (status)
    {
    case icmOk:
      (void) icmKeepHandle(handle);
      process_symbol = ps;
      return true;
      break;
    case icmFailed:
      return false;
      break;
    case icmError:
      return false;
      break;
    case icmEndFile:
      assert(false);
      return false;
      break;
    }
  
  assert(false);
  return false;
}

bool
ICMEnvironment::Unregister(void)
{
  assert(process_symbol != NULL);

#ifdef DEBUG_ICM
  char buf[MAXSTRING];
  (void) icmHandleName(handle, buf, 512);
#endif

#ifdef DEBUG_ICM
  cerr << __FUNCTION__ << " Before icmDeregisterAgent() " << buf << endl;
#endif
  const icmStatus status = icmDeregisterAgent(conn, handle);
  
#ifdef DEBUG_ICM
  cerr << __FUNCTION__ << " After icmDeregisterAgent() " << buf << endl;
#endif
  
  switch (status)
    {
    case icmOk:
      (void) icmReleaseHandle(handle);
      process_symbol = NULL;
      icmCloseComms(conn);
      return true;
      break;
    case icmFailed:
      return false;
      break;
    case icmError:
      return false;
      break;
    case icmEndFile:
      assert(false);
      return false;
      break;
    }
  
  assert(false);
  return false;
}


Object*
ICMMessage::constructSenderTerm(Thread& thread, AtomTable& atoms)
{
  Object* from_handle_cell;
  icm_handle_to_heap(thread.TheHeap(), atoms, 
		     sender, from_handle_cell);
  return from_handle_cell;
}

Object*
ICMMessage::constructReplyToTerm(Thread& thread, AtomTable& atoms)
{
  Object* replyto_handle_cell;
  icm_handle_to_heap(thread.TheHeap(), atoms, 
		     reply_to, replyto_handle_cell);
  return replyto_handle_cell;

}

Object*
ICMMessage::constructMessageTerm(Thread& thread, AtomTable& atoms,
				 bool remember_names)
{
  Object* message_cell = NULL;
  icmDataRec data;
  if (icmScanMsg(message, "%(%S%)", &data) == icmOk)
    {
      string buff(data.data, data.size);
      
      free(data.data);
      
      QPistringstream stream(buff);
      Object* object_variablenames;

      EncodeRead er(thread,
		    thread.TheHeap(),
		    stream,
		    message_cell,
		    atoms,
		    remember_names,
		    thread.getNames(),
		    object_variablenames);
      if (! er.Success())
	{
	  // XXX Should raise an exception
	  Fatal(__FUNCTION__, "Couldn't decode message!");
	}
      return message_cell;
    }
  // The message is not encoded
  icmStatus status = icmScanMsg(message, "%S", &data);
  if (status == icmOk)
    {
      // Nothing.
    }
  else if (status == icmFailed)
    {
      Fatal(__FUNCTION__, "Format of message doesn't match QP message format");
    }
  else if (status == icmError)
    {
      Fatal(__FUNCTION__, "icmScanMsg() returned icmError");
    }
  message_cell = AtomTable::nil;
  Heap& heap = thread.TheHeap();
  for (int i = data.size-1; i >= 0 ; i--)
    {
      Object* entry = heap.newNumber(data.data[i]);
      Cons* list = heap.newCons(entry, message_cell);
      message_cell = list;
    }

  // Free the data.
  free(data.data);

  return message_cell;
}

bool
ICMMessageChannel::msgToThread(ICMMessage* message)
{
  char *icm_target;
  
  (void) icmAnalyseHandle(message->getRecipient(), &icm_target, 
			  NULL, NULL, NULL, NULL);
  
  if (*icm_target == '\0')
    {
      // Empty target - search for QPimstream for the sender
      iom.updateStreamMessages(message->getSender(), message->getMessage());
      delete message;
      return true;
    }
  
  ICMIncomingTarget target(icm_target);
  
  ThreadTable& thread_table = getThreadTable();

  ThreadTableLoc id = (ThreadTableLoc) -1;
  if (target.IsID())
    {
      id = target.ID();
    }
  else if (target.IsSymbol())
    {
      id = thread_table.LookupName(target.Symbol());
      if (id == (ThreadTableLoc) -1)
	{
	  return false;
	}
    }
  
  if (!thread_table.IsValid(id))
    {
      return false;
    }
  else
    {
      Thread* thread = thread_table.LookupID(id);
      if (thread == NULL)
	{
	  return false;
	}

      thread->MessageQueue().push_back(message);
      return true;
    }

}

bool
ICMMessageChannel::ShuffleMessages(void)
{
  icmHandle recipient;
  icmHandle sender;
  icmOption options;
  icmMsg message;
  bool newMsg = false;

  for (list<ICMMessage*>::iterator iter = msg_buff.begin();
       iter != msg_buff.end();
       )
    {
      if (msgToThread(*iter))
	{
	  newMsg = true;
	  iter = msg_buff.erase(iter);
	}
      else
	{
	  iter++;
	}
    }

  while (icmMsgAvail(icm_env.Conn(), icm_env.messageNo()) == icmOk)
    {
      icmStatus status = icmGetMsg(icm_env.Conn(),
                                   &recipient, &sender, &options,
                                   &message, icm_env.messageNoRef());
      
      switch (status)
        {
        case icmOk:
          {
#ifdef DEBUG_ICM
            char recipient_buf[MAXSTRING], sender_buf[MAXSTRING];
            (void) icmHandleName(sender, sender_buf, MAXSTRING);
            (void) icmHandleName(recipient, recipient_buf, MAXSTRING);
	    cerr << __FUNCTION__
		 << " Message received for "
		 << recipient_buf << " from " << sender_buf << endl;
#endif
	    
            icmDataRec data;
            icmStatus status = icmScanMsg(message, "%S", &data);
            if(status == icmOk &&
               data.size == 17 &&
               strncmp(data.data, "control_C_message", data.size) == 0)
	      
              {
		free(data.data);
		signals.Increment(SIGINT);
		signals.Status().setSignals();
		return newMsg;
              }
            else
              {
		if (status == icmOk)
		  {
		    free(data.data);
		  }
		newMsg = true;
                icmHandle replyto = sender;
		
                // If this call fails, replyto is unchanged
                (void) icmIsOption(options, icmReplyto, &replyto);
		
                // Return the storage used by the options.
                icmReleaseOptions(options);

		ICMMessage *icm_message = 
		  new ICMMessage(sender, replyto, recipient, message);

		if (msgToThread(icm_message))
		  {
		    newMsg = true;
		  }
		else
		  {
		    msg_buff.push_back(icm_message);
		  }
	      }

          }
          break;
        case icmFailed:
          Warning(__FUNCTION__, "icmGetMsg() returned icmFailed");
          assert(false);
          break;
        case icmError:
          Warning(__FUNCTION__, "icmGetMsg() returned icmError");
          break;
        case icmEndFile:
          Warning(__FUNCTION__, "ICM Communicatons Server has closed connection");
          break;
        }
    }
  return newMsg;
}

void
ICMMessageChannel::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
  int fd = icm_env.getCommFD();
  if (fd > max_fd) max_fd = fd;
  FD_SET(fd, rfds);
}

#endif // ICM_DEF

