// elvin_env.h - Elvin support.
//
// $Id: elvin_env.h,v 1.7 2005/11/26 23:34:29 qp Exp $

/* This file is part of the Elvin interface to QuProlog.
 * Copyright (c) 2003 Peter Robinson <pjr@itee.uq.edu.au>
 * Copyright (c) 2002 DSTC Pty Ltd (ACN 052 372 577)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */
#ifndef	ELVIN_ENV_H
#define	ELVIN_ENV_H

#ifdef ELVIN_DEF

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <elvin/elvin.h>
#include "messages.h"

string createUUID();

/* static int notify_cb(elvin_handle_t handle, */
/*                      elvin_subscription_t sub, */
/*                      elvin_notification_t notification, */
/*                      int is_secure, void *rock, elvin_error_t err); */
//
// The base class for a component of an elvin message.
// This contains the field name of the message and
// the derived classes contain the values.
//
class ElvinMsgPart
{
private:
  Atom* name;                     // field name of message
public:
  explicit ElvinMsgPart(Atom* n)
    : name(n) {}

  virtual ~ElvinMsgPart() {}

  Atom*& getName(void) { return name; }
  // Build a QuProlog term from the message
  virtual Object* buildTerm(Thread&, AtomTable&) = 0;
};

//
// A derived class of ElvinMsgPart for Elvin strings.
//
class ElvinMsgPartString : public ElvinMsgPart
{
private:
  string value;
public:
  ElvinMsgPartString(Atom* n, char* v)
    : ElvinMsgPart(n), value(v) {}

  Object* buildTerm(Thread&, AtomTable&);
};

//
// A derived class of ElvinMsgPart for Elvin ints.
//
class ElvinMsgPartInt : public ElvinMsgPart
{
private:
  int value;
public:
  ElvinMsgPartInt(Atom* n, int v)
    : ElvinMsgPart(n), value(v) {}

  Object* buildTerm(Thread&, AtomTable&);
};

//
// A derived class of ElvinMsgPart for Elvin int64.
//
class ElvinMsgPartInt64 : public ElvinMsgPart
{
private:
   int64_t value;
public:
  ElvinMsgPartInt64(Atom* n, int64_t v)
    : ElvinMsgPart(n), value(v) {}

  Object* buildTerm(Thread&, AtomTable&);
};

//
// A derived class of ElvinMsgPart for Elvin real64.
//
class ElvinMsgPartReal64 : public ElvinMsgPart
{
private:
   double value;
public:
  ElvinMsgPartReal64(Atom* n, double v)
    : ElvinMsgPart(n), value(v) {}

  Object* buildTerm(Thread&, AtomTable&);
};

//
// A derived class of ElvinMsgPart for Elvin real64.
//
class ElvinMsgPartOpaque : public ElvinMsgPart
{
private:
   string value;
public:
  ElvinMsgPartOpaque(Atom* n, elvin_opaque_t v)
    : ElvinMsgPart(n), value((char*)(v.data), v.length) {}

  Object* buildTerm(Thread&, AtomTable&);
};

//
// The ElvinMessage class is derived from the QuProlog Message base
// class. This class must define how to build the sender and reply-to
// addresses (as QuProlog terms) and the message as a QuProlog term.
//
class ElvinMessage : public Message
{
private:
  ThreadTableLoc thread_id;     // The QP thread this message is for
  // The message is stored as a list of message parts (i.e. mappings
  // from filed names to values)
  list<ElvinMsgPart*> elvin_msg;  
public:
  explicit ElvinMessage(ThreadTableLoc tid) : Message(), thread_id(tid) {}
  
  ~ElvinMessage(void)
    {
      for (list<ElvinMsgPart*>::iterator iter = elvin_msg.begin();
	   iter != elvin_msg.end();
	   iter++)
	{
	  delete *iter;
	}
    }

  Object* constructSenderTerm(Thread&, AtomTable&);
  Object* constructReplyToTerm(Thread&, AtomTable&);
  Object* constructMessageTerm(Thread&, AtomTable&,
                               bool remember_names = false);
  
  ThreadTableLoc getThreadID(void) { return thread_id; }

  void pushMsgPart(ElvinMsgPart* part)
  {
    elvin_msg.push_back(part);
  }
};

//
// Wrapper for elvin IO handler - used to determine which handler to
// call for a given FD.
//
class ElvinHandler
{
private:
  bool read;                      // FD is for reading?
  bool trash;                     // Ready for deleting?
  int fd;                         // FD
  elvin_io_handler_t handler;     // Elvin IO handler for this FD

public:
  ElvinHandler(bool r, int f, elvin_io_handler_t h)
    : read(r), trash(false), fd(f), handler(h) {}

  ~ElvinHandler() {}

  bool isRead(void) const { return read; }
  bool isTrash(void) const {return trash; }
  void makeTrash(void) {trash = true; }
  int getFD(void) const { return fd; }
  bool sameHandler(elvin_io_handler_t h) { return h == handler; }
  void callHandler(elvin_error_t error);
};


//
// A wrapper for an Elvin subscription.
// Used for listing and removing subscriptions.
//
class SubscriptionData
{
 private:
  ThreadTableLoc threadID;   // The QP thread associated with the subscription
  Atom* formula;             // The formula of the subscription
  elvin_subscription_t sub;  // The subscription
 public:
  SubscriptionData(ThreadTableLoc tn, Atom* f) 
    : threadID(tn), formula(f) {}

  ThreadTableLoc getThreadID(void) { return threadID; }
  Atom* getFormula(void) { return formula; }
  void setSubscription(elvin_subscription_t s) { sub = s; }
  elvin_subscription_t getSubscription(void) { return sub; }
  bool operator==(const SubscriptionData& t) const
    {
      return ((threadID == t.threadID) && (formula == t.formula));
    }
};

//
// The ElvinMessageChannel is derived from the QP base class MessageChannel.
// This must define the methods:
// ShuffleMessages - for putting Elvin messages into the message buffers
//                   of the appropriate QP threads.
// updateFDSETS - for updating the FD sets of Elvin sockets to be used
//                by QP to determine if IO events have occurred using select.
// This class is used as the main point that provides the interface between
// QP and Elvin.
//
class ElvinMessageChannel : public MessageChannel
{
 private:
  // All the current Elvin handlers
  list<ElvinHandler*> elvin_handlers;
  // Notifications that have arrived but have not been processed.
  list<ElvinMessage*> pending_messages;
  // All the current subscriptions
  list<SubscriptionData*> subscription_data;
  // Are we connect to Elvin?
  bool connected;
  // Elvin error
  elvin_error_t error;
  // Has the subscription been done?
  bool subscribed;
  // Elvin handle
  elvin_handle_t handle;
  // Registered timeouts
  list<elvin_timeout_t> reg_timeouts;
  // Make callbacks to all handlers in these FD sets
  void processFDs(fd_set* rfds, fd_set* wfds);
  // Move all the pending messages to the appropriate QP threads' message
  // buffers 
  bool processPending(void);
  // Move the given message to the appropriate QP thread's message buffer
  bool msgToThread(ElvinMessage* msg);
 public:
  explicit ElvinMessageChannel(ThreadTable& t): MessageChannel(t), connected(false) {}
  
  ~ElvinMessageChannel();
  // Initialize connection to Elvin
  void elvinInit(Object*);
  // Disconnect from Elvin
  void elvinDisconnect(void);
  
  elvin_handle_t getHandle(void) { return handle; }
  elvin_error_t getError(void) { return error; }
  
  void setSubscribed(bool b) { subscribed = b; }
  
  void readElvin(void);

  // Add an Elvin handler to the current handlers
  void addHandler(ElvinHandler* h)
    {
      elvin_handlers.push_front(h);
    }
  // Add a timeout to the registered timeouts
  void addTimeout(elvin_timeout_t timeout);

  // Remove a timeout from the registered timeouts
  int removeTimeout(elvin_timeout_t timeout);

  // add a new notification to the pending messages
  void pushPending(ElvinMessage* em)
    {
      pending_messages.push_back(em);
    }
  // Add a new subscription info object
  void pushSubData(SubscriptionData* sdata)
    {
      subscription_data.push_back(sdata);
    }
  // Add a new Elvin subscription
  bool addSubscription(ThreadTableLoc, Atom*);
  // delete the subscription
  bool deleteSubscription(ThreadTableLoc, Object*);
  // Add an Elvin notification
  bool addNotification(Object*, Thread&);
  // Turn the list of current substitutions into a QP list
  Object* subListToList(Thread&);

  void setConnected(void) { connected = true; }
  void setDisconnected(void) { connected = false; }

  bool isConnected(void)const { return connected; }

  void removeHandler(elvin_io_handler_t h);

  bool  ShuffleMessages(void);

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd);

  void processTimeouts(struct timeval& next);

};

#endif // ELVIN_DEF
#endif	// ELVIN_ENV_H
