// elvin_escapes.cc - Elvin escapes.
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
// $Id: elvin_escapes.cc,v 1.2 2003/12/11 23:41:26 qp Exp $

#include "global.h"
#include "thread_qp.h"
#include "elvin_env.h"


#ifdef ELVIN_DEF
extern ElvinMessageChannel* elvin_channel;
#endif // ELVIN_DEF

// --------------------------------------------------------------------------
//
// PSEUDO INSTRUCTIONS
//
// --------------------------------------------------------------------------

Thread::ReturnValue
Thread::psi_elvin_connect(Object *& server_cell)
{
#ifdef ELVIN_DEF
  if (elvin_channel != NULL)
    {
      Warning(Program, "Already connected");
      return RV_FAIL;
    }
  Object* server = server_cell->variableDereference();
  elvin_channel = new ElvinMessageChannel(*thread_table);
  elvin_channel->elvinInit(server);
  scheduler->getChannels().push_back(elvin_channel);
  return RV_SUCCESS;
#else // ELVIN_DEF
  return RV_FAIL;
#endif // ELVIN_DEF
}


Thread::ReturnValue
Thread::psi_elvin_disconnect(void)
{
#ifdef ELVIN_DEF
  if (elvin_channel == NULL)
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  elvin_channel->elvinDisconnect();
  list <MessageChannel*>& channels = scheduler->getChannels();
  for (list <MessageChannel*>::iterator iter = channels.begin();
       iter != channels.end();
       iter++)
    {
      if (*iter == elvin_channel)
	{ 
	  channels.erase(iter);
	  break;
	}
    }
  delete elvin_channel;
  elvin_channel = NULL;
  return RV_SUCCESS;
#else // ELVIN_DEF
  return RV_FAIL;
#endif // ELVIN_DEF
}


Thread::ReturnValue
Thread::psi_elvin_add_subscription(Object *& subscription_cell)
{
#ifdef ELVIN_DEF
  if (elvin_channel == NULL)
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }

  Object* subscription = subscription_cell->variableDereference();

  return BOOL_TO_RV(elvin_channel->addSubscription(this->TInfo().ID(), 
						   OBJECT_CAST(Atom*,subscription)));

#else // ELVIN_DEF
  return RV_FAIL;
#endif // ELVIN_DEF
}

Thread::ReturnValue
Thread::psi_elvin_add_notification(Object *& notification_cell)
{
#ifdef ELVIN_DEF
  if (elvin_channel == NULL)
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }

  Object* notification = notification_cell->variableDereference();

  return BOOL_TO_RV(elvin_channel->addNotification(notification, *this));

#else // ELVIN_DEF
  return RV_FAIL;
#endif // ELVIN_DEF
}

Thread::ReturnValue
Thread::psi_elvin_subscriptions(Object *& subscriptions)
{
#ifdef ELVIN_DEF
  if (elvin_channel == NULL)
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  subscriptions = elvin_channel->subListToList(*this);
  return RV_SUCCESS;

#else // ELVIN_DEF
  return RV_FAIL;
#endif // ELVIN_DEF
}


Thread::ReturnValue
Thread::psi_elvin_delete_subscription(Object *& subscription_cell)
{
#ifdef ELVIN_DEF
  if (elvin_channel == NULL)
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  Object* subscription = subscription_cell->variableDereference();
  return BOOL_TO_RV(elvin_channel->deleteSubscription(this->TInfo().ID(), 
						      subscription));

#else // ELVIN_DEF
  return RV_FAIL;
#endif // ELVIN_DEF
}

Thread::ReturnValue
Thread::psi_elvin_makeID(Object *& id)
{
#ifdef ELVIN_DEF
  if (elvin_channel == NULL)
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  id = atoms->add(createUUID().c_str());
  return RV_SUCCESS;

#else // ELVIN_DEF
  return RV_FAIL;
#endif // ELVIN_DEF
}
