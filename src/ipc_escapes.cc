// ipc_escapes.cc - Interprocess communication.
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
// $Id: ipc_escapes.cc,v 1.27 2005/11/26 23:34:30 qp Exp $

#include <algorithm>

#include <sys/types.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "config.h"

#include "atom_table.h"
#include "global.h"
#include "icm.h"
#include "icm_environment.h"
#include "icm_handle.h"
#include "is_ready.h"
#include "thread_qp.h"
#include "thread_table.h"
#include "timeval.h"
#include "tcp_qp.h"

extern AtomTable *atoms;
#ifdef ICM_DEF
extern ICMMessageChannel* icm_channel;
extern ICMEnvironment* icm_environment;
#endif
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
    reference = reinterpret_cast<list<Message *>::iterator *> (object->getNumber()); \
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
      QPostringstream stream;

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

      int size = stream.str().length();

      char *msgstr = new char[size+1];
      memcpy(msgstr, stream.str().data(), size);
      icmDataRec data = { size, msgstr };

      message = icmFormatMsg(NULL, "%(%S%)", &data);
      delete msgstr;
    }
  else
    {
      QPostringstream stream;

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


      int size = stream.str().length();
      char *msgstr = new char[size+1];
      memcpy(msgstr, stream.str().data(), size);
      icmDataRec data = { size, msgstr };
      message = icmFormatMsg(NULL, "%S", &data);
      delete msgstr;
    }

  icmHandle sender_handle = icm_thread_handle(*icm_environment,
					      *this);

  // If the message is destined for the same process then simply add
  // to the message queue otherwise send the message using the ICM.

  if (icmSameAgentHandle(sender_handle, recipient_handle) == icmOk)
    {

      ICMMessage *icm_message = new ICMMessage(sender_handle,
					       replyto_handle,
					       recipient_handle,
					       message);
      if (!icm_channel->msgToThread(icm_message))
	{
	  icm_channel->pushMessageToBuff(icm_message);
	}
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
      assert(false);
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
  list<Message *>::iterator *iter = new list<Message *>::iterator;

  Structure* iterstr = heap.newStructure(1);
  iterstr->setFunctor(AtomTable::dollar);
  iterstr->setArgument(1, heap.newNumber(reinterpret_cast<unsigned> (iter)));
  reference_cell = iterstr;

  return RV_SUCCESS;
}

//
// Get the first thing on the message queue for this thread.
//
Thread::ReturnValue
Thread::psi_ipc_first(Object *& reference0_cell,
		      Object *& timeout_cell,
                      Object *& reference1_cell)
{
  Object* reference0_str = heap.dereference(reference0_cell);
  Object* timeout_arg = heap.dereference(timeout_cell);

  assert(reference0_str->isStructure());
  Object* reference0_arg = 
     OBJECT_CAST(Structure*, reference0_str)->getArgument(1);

  list<Message *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference0_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  time_t timeout;
  DECODE_TIMEOUT_ARG(heap, timeout_arg, 2, timeout);

  *iter = message_queue.begin();

  IS_READY_MESSAGE(*atoms, message_queue, *iter, timeout);

  (**iter)->IncReferences();

  reference1_cell = reference0_str;
  
  return RV_SUCCESS;
}

// Get the next thing on the message queue for this thread.
Thread::ReturnValue
Thread::psi_ipc_next(Object *& reference0_cell,
		     Object *& reference1_cell,
		     Object *& timeout_cell)
{
  Object* reference0_str = heap.dereference(reference0_cell);
  Object* timeout_arg = heap.dereference(timeout_cell);
 
  assert(reference0_str->isStructure());
  Object* reference0_arg = 
     OBJECT_CAST(Structure*, reference0_str)->getArgument(1);
  if (reference0_arg == AtomTable::dollar) return RV_FAIL;

  list<Message *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference0_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  time_t timeout;
  DECODE_TIMEOUT_ARG(heap, timeout_arg, 2, timeout);

  // Save the current position
  Message& message = ***iter;

  // Advance to the next message
  (*iter)++;

  IS_READY_MESSAGE(heap, message_queue, *iter, timeout);

  message.DecReferences();
  
  (**iter)->IncReferences();
  
  reference1_cell =  reference0_str;
  
  return RV_SUCCESS;
}
		   
Thread::ReturnValue
Thread::psi_ipc_get_message(Object *& message_cell,
			    Object *& reference_cell,
			    Object *& from_handle_cell,
			    Object *& replyto_handle_cell,
			    Object *& remember_names_cell)
{
  Object* reference_str = heap.dereference(reference_cell);
  Object* remember_names_arg = heap.dereference(remember_names_cell);

  assert(reference_str->isStructure());
  Object* reference_arg = 
     OBJECT_CAST(Structure*, reference_str)->getArgument(1);

  list<Message *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference_arg, 2, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  bool remember_names;
  DECODE_BOOLEAN_ARG(*atoms, remember_names_arg, 5, remember_names);
  
  Message& message = ***iter;

  from_handle_cell = message.constructSenderTerm(*this, *atoms);
  replyto_handle_cell = message.constructReplyToTerm(*this, *atoms);
  message_cell = message.constructMessageTerm(*this, *atoms, remember_names);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_ipc_commit(Object *& reference_cell)
{
  Object* reference_str = heap.dereference(reference_cell);
  assert(reference_str->isStructure());
  Object* reference_arg = 
    OBJECT_CAST(Structure*, reference_str)->getArgument(1);


  OBJECT_CAST(Structure*, reference_str)->setArgument(1, AtomTable::dollar);

  list<Message *>::iterator *iter;
  DECODE_REFERENCE_ARG(heap, reference_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  Message *message = **iter;

  message->Commit();
  message->DecReferences();

  if (message->References() == 0)
    {
      delete message;
      (void)message_queue.erase(*iter);
    }
  delete iter;

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_ipc_open(Object *& level_cell)
{
#ifdef ICM_DEF_XXX
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  icm_level++;
  level_cell = heap.newNumber(icm_level);

  return RV_SUCCESS;
#else // ICM_DEF_XXX
  return RV_FAIL;
#endif // ICM_DEF_XXX
}

#ifdef ICM_DEF_XXX
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
#endif // ICM_DEF_XXX

Thread::ReturnValue
Thread::psi_ipc_close(Object *& level_cell)
{
#ifdef ICM_DEF_XXX
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
#else // ICM_DEF_XXX
  return RV_FAIL;
#endif // ICM_DEF_XXX
}

//
// Broadcast message to all current local threads
// mode(in)
//
Thread::ReturnValue
Thread::psi_broadcast(Object *& message_cell)
{
#ifdef ICM_DEF
  if (process_symbol == NULL)
    {
      Warning(__FUNCTION__, "ICM functionality is not available in unregistered qem processes");
      return RV_FAIL;
    }

  Object* message_arg = heap.dereference(message_cell);
  icmMsg message;

  QPostringstream stream;

  EncodeWrite ew(*this,
		 heap,
		 stream,
		 message_arg,
		 *atoms,
		 true,
		 names);
  if (!ew.Success())
    {
      PSI_ERROR_RETURN(EV_ALLOCATION_FAILURE, 0);
    }

  icmHandle sender_handle = icm_thread_handle(*icm_environment,
					      *this);


  for (ThreadTableLoc loc = 0; loc < thread_table->Size(); loc++)
    {
      if ((*thread_table)[loc] != NULL)
	{
	  int size = stream.str().length();
	  
	  icmDataRec data = { size, const_cast<char*>(stream.str().data()) };
	  
	  message = icmFormatMsg(NULL, "%(%S%)", &data);

	  ICMMessage *icm_message = new ICMMessage(sender_handle,
						   sender_handle,
						   sender_handle,
						   message);

	  Thread& thread = *(thread_table->LookupID(loc));
	  thread.MessageQueue().push_back(icm_message);
	}
    }
  return RV_SUCCESS;

#else // ICM_DEF
  return RV_FAIL;
#endif // ICM_DEF

}


