// ipc_escapes.cc - Interprocess communication.
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
// $Id: ipc_escapes.cc,v 1.14 2002/05/03 01:32:28 qp Exp $

#include <algorithm>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "config.h"

#include "atom_table.h"
#include "global.h"
#include "icm.h"
#include "icm_environment.h"
#include "icm_handle.h"
#include "is_ready.h"
#include "thread_qp.h"
#include "timeval.h"
#include "tcp_qp.h"

extern AtomTable *atoms;
extern ICMEnvironment *icm_environment;
extern const char *Program;
extern char *process_symbol;

#define DECODE_REFERENCE_ARG(heap, object, arg_num, reference)		  \
  do {									  \
    if (object->isVariable())						  \
      {									  \
	PSI_ERROR_RETURN(EV_INST, arg_num);				  \
      }									  \
    if (!object->isNumber())						  \
      {									  \
	PSI_ERROR_RETURN(EV_TYPE, arg_num);				  \
      }									  \
    reference = reinterpret_cast<list<ICMMessage *>::iterator *> (object->getNumber()); \
  } while (0)

#define DECODE_NONNEG_INT_ARG(heap, object, arg_num, val)	\
  do {							\
    if (object->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (!object->isNumber())			\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    else if (object->getNumber() < 0)			\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    val = object->getNumber();  			\
  } while (0)

// --------------------------------------------------------------------------
//
// PSEUDO INSTRUCTIONS
//
// --------------------------------------------------------------------------

Thread::ReturnValue
Thread::psi_ipc_send(Object *& message_cell,
		     Object *& recipient_handle_cell,
		     Object *& replyto_handle_cell,
		     Object *& options_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  Object* message_arg = heap.dereference(message_cell);
  Object* recipient_handle_arg = heap.dereference(recipient_handle_cell);
  Object* replyto_handle_arg = heap.dereference(replyto_handle_cell);
  Object* options_arg = heap.dereference(options_cell);


  icmHandle recipient_handle;
  DECODE_ICM_HANDLE_ARG(heap, *atoms, recipient_handle_arg, 2,
			recipient_handle);
  
  icmHandle replyto_handle;
  DECODE_ICM_HANDLE_ARG(heap, *atoms, replyto_handle_arg, 3,
			replyto_handle);

  bool remember_names;
  bool encoded;
  DECODE_SEND_OPTIONS_ARG(heap, options_arg, 4,
			  remember_names, encoded);

  icmMsg message;

  if (encoded)
    {
      // XXX Deleted on destruction of Stream stream
      ostrstream *ostrm = new ostrstream();
      if (ostrm == NULL)
        {
          OutOfMemory(__FUNCTION__);
        }

      if (ostrm->bad())
	{
	  PSI_ERROR_RETURN(EV_SYSTEM, 0);
	}

      Stream stream(ostrm);

      EncodeWrite ew(*this,
                     heap,
                     stream,
                     message_arg,
                     *atoms,
                     remember_names,
                     names);
      if (!ew.Success())
        {
          PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 0);
        }

      icmDataRec data = { ostrm->pcount(), ostrm->str() };
      
      message = icmFormatMsg(NULL, "%(%S%)", &data);
      free(data.data);
    }
  else
    {
      // Raw format (not encoded).
      // XXX Deleted on destruction of Stream stream
      ostrstream *ostrm = new ostrstream();
      if (ostrm == NULL)
        {
          OutOfMemory(__FUNCTION__);
        }

      if (ostrm->bad())
        {
          PSI_ERROR_RETURN(EV_SYSTEM, 0);
        }

      Stream stream(ostrm);


      while (message_arg->isCons())
        {
           Cons* list = OBJECT_CAST(Cons*, message_arg);
	   Object* head = list->getHead()->variableDereference();
           if (!head->isNumber())
             {
               PSI_ERROR_RETURN(EV_TYPE, 1);
             }
           int c = head->getNumber();
	   if ((c < 0) || (c > 255))
             {
               PSI_ERROR_RETURN(EV_TYPE, 1);
             }
           stream << (char)c;
           message_arg = list->getTail()->variableDereference();
        }
      if (!message_arg->isNil())
        {
          PSI_ERROR_RETURN(EV_TYPE, 1);
        }


      icmDataRec data = { ostrm->pcount(), ostrm->str() };
      
      message = icmFormatMsg(NULL, "%S", &data);
      free(data.data);
    }

  // Did anything go wrong the formatting of the message?
  //if (status == icmFailed)
  //  {
  //    PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 0);
  //  }

  icmHandle sender_handle = icm_thread_handle(*icm_environment,
					      *this);
  if (sender_handle == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  // If the message is destined for the same process then simply add
  // to the message queue otherwise send the message using the ICM.

  if (icmSameAgentHandle(sender_handle, recipient_handle) == icmOk)
    {
      ICMMessage *icm_message = new ICMMessage(recipient_handle,
					       replyto_handle,
					       sender_handle, message);
      if (icm_message == NULL)
	{
	  OutOfMemory(__FUNCTION__);
	}
      icm_environment->Queue().Lock();
      icm_environment->Queue().push_back(icm_message);
      icm_environment->Queue().Unlock();
      return RV_SUCCESS;
    }
      
  // Set the replyto handle in the options
  icmOption options = icmNewOpt(NULL, icmReplyto, replyto_handle);

  // Away it goes!
  icmStatus status = icmSendMsg(icm_environment->Conn(),
		                recipient_handle,
		                sender_handle,
		                options,
		                message);

  icmReleaseOptions(options);
  
  icmReleaseMsg(message);
  
  if (status == icmOk)
    {
      return RV_SUCCESS;
    }
  else if (status == icmFailed)
    {
      // TO DO: Could block instead.
      return RV_FAIL;
    }
  else 
    {
      DEBUG_ASSERT(false);
      return RV_FAIL;
    }
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

//
// ipc_make_iterator(reference_out)
//
// Create an iterator for use with ipc_first and ipc_next
//
// mode(out)
//
//
Thread::ReturnValue 
Thread::psi_make_iterator(Object *& reference_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  list<ICMMessage *>::iterator *iter = new list<ICMMessage *>::iterator;

  reference_cell = heap.newNumber(reinterpret_cast<unsigned> (iter));

  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

//
// Get the first thing on the ICM queue for this thread.
//
Thread::ReturnValue
Thread::psi_ipc_first(Object *& reference0_cell,
		      Object *& timeout_cell,
                      Object *& reference1_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  Object* reference0_arg = heap.dereference(reference0_cell);
  Object* timeout_arg = heap.dereference(timeout_cell);

  list<ICMMessage *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference0_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  time_t timeout;
  DECODE_TIMEOUT_ARG(heap, timeout_arg, 2, timeout);

  *iter = icm_queue.begin();

  IS_READY_ICM(*atoms, icm_queue, *iter, timeout);

  (**iter)->IncReferences();

  reference1_cell = heap.newNumber(reinterpret_cast<unsigned> (iter));
  
  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

// Get the next thing on the IPC queue for this thread.
Thread::ReturnValue
Thread::psi_ipc_next(Object *& reference0_cell,
		     Object *& reference1_cell,
		     Object *& timeout_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  Object* reference0_arg = heap.dereference(reference0_cell);
  Object* timeout_arg = heap.dereference(timeout_cell);
 
  list<ICMMessage *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference0_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  time_t timeout;
  DECODE_TIMEOUT_ARG(heap, timeout_arg, 2, timeout);

  // Save the current position
  ICMMessage& icm_message = ***iter;

  // Advance to the next message
  (*iter)++;

  IS_READY_ICM(heap, icm_queue, *iter, timeout);

  icm_message.DecReferences();
  
  (**iter)->IncReferences();
  
  reference1_cell =  heap.newNumber(reinterpret_cast<unsigned> (iter));
  
  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}
		   
Thread::ReturnValue
Thread::psi_ipc_get_message(Object *& message_cell,
			    Object *& reference_cell,
			    Object *& from_handle_cell,
			    Object *& replyto_handle_cell,
			    Object *& remember_names_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  Object* reference_arg = heap.dereference(reference_cell);
  Object* remember_names_arg = heap.dereference(remember_names_cell);

  list<ICMMessage *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference_arg, 2, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  bool remember_names;
  DECODE_BOOLEAN_ARG(*atoms, remember_names_arg, 5, remember_names);
  
  ICMMessage& icm_message = ***iter;

  icmHandle from_handle = icm_message.Sender();
  icm_handle_to_heap(heap, *atoms, from_handle, from_handle_cell);

  icmHandle replyto_handle = icm_message.ReplyTo();
  icmHandle dummy_handle = icmDummyHandle();
  if (icmSameHandle(replyto_handle, dummy_handle) == icmOk)
    {
      replyto_handle_cell = from_handle_cell;
    }
  else
    {
      icm_handle_to_heap(heap, *atoms, replyto_handle, replyto_handle_cell);
    }

  icmDataRec data;
  if (icmScanMsg(icm_message.Message(), "%(%S%)", &data) == icmOk)
    {
	// XXX Deleted on destruction of stream.
	istrstream *istrm = new istrstream(data.data, data.size);
	if (istrm == NULL)
	  {
	    OutOfMemory(__FUNCTION__);
	  }
	if (istrm->bad())
	  {
	    // Free the data.
	    free(data.data);

	    PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 0);
	  }
	
	Stream stream(istrm);
	Object* object_variablenames;
	
	EncodeRead er(*this,
		      heap,
		      stream,
		      message_cell,
		      *atoms,
		      remember_names,
		      names,
		      object_variablenames);
        free(data.data);
	if (! er.Success())
	  {
	    // XXX Should raise an exception
	    Fatal(__FUNCTION__, "Couldn't decode message!");
	  }
      return RV_SUCCESS;
    }
  // The message is not encoded
  icmStatus status = icmScanMsg(icm_message.Message(), "%S", &data);
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

  /*
  The old way was to turn the message into an atom
  char buf[data.size+1];
  strncpy(buf, data.data, data.size);
  buf[data.size] = '\0';
  message_cell = atoms->add(buf);
  The new way is to make a list of ASCII values
  */

  message_cell = AtomTable::nil;
  for (int i = data.size-1; i >= 0 ; i--)
    {
      Object* entry = heap.newNumber(data.data[i]);
      Cons* list = heap.newCons(entry, message_cell);
      message_cell = list;
    }
  
  // Free the data.
  free(data.data);

  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_ipc_commit(Object *& reference_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  Object* reference_arg = heap.dereference(reference_cell);

  list<ICMMessage *>::iterator *iter;
  DECODE_REFERENCE_ARG(heap, reference_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  ICMMessage *icm_message = **iter;

  icm_message->Commit();
  icm_message->DecReferences();

  if (icm_message->References() == 0)
    {
      delete icm_message;
      (void)icm_queue.erase(*iter);
    }
  delete iter;

  // Remove any remaining timeouts (that must have been generated by
  // an ipc_first or ipc_next call).

  scheduler->deleteTimeout(this);

  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

Thread::ReturnValue
Thread::psi_ipc_open(Object *& level_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  icm_level++;
  level_cell = heap.newNumber(icm_level);

  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}

#ifdef ICM_DEF
static bool commit_delete(ICMMessage *msg)
{
  if (msg->Committed())
    {
      delete msg;
      return true;
    }
  else
    {
      return false;
    }
}
#endif // ICM_DEF

Thread::ReturnValue
Thread::psi_ipc_close(Object *& level_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  Object* level_arg = heap.dereference(level_cell);

  size_t level;
  DECODE_NONNEG_INT_ARG(heap, level_arg, 1, level);

  if (level != icm_level)
    {
      PSI_ERROR_RETURN(EV_VALUE, 1);
    }

  icm_level--;

  // Can we garbage collect the ICM queue?
  if (icm_level == 0)
    {
      list<ICMMessage *>::iterator iter =
	remove_if(icm_queue.begin(), icm_queue.end(), commit_delete);
      icm_queue.erase(iter, icm_queue.end());
    }

  return RV_SUCCESS;
#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF
}




