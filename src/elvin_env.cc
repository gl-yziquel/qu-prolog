
// elvin_env.cc - Elvin support.
//
// $Id: elvin_env.cc,v 1.2 2004/02/12 23:53:46 qp Exp $

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

#include "config.h"
#ifdef ELVIN_DEF

using namespace std;

#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <elvin/elvin.h>
#include <crypt.h>
#include <time.h>
#include <stdio.h>



#include "QuProlog.h"
#include "thread_table.h"
#include "scheduler.h"

#include "elvin_env.h"

// Required global variables from QP
extern AtomTable* atoms;
extern ThreadTable *thread_table;
extern Scheduler *scheduler;

// Global variables for Elvin interface.
static ElvinMessageChannel* elvin_channel_ptr = NULL;
static elvin_client_t client;

static bool timeout_before(struct timeval *first, struct timeval * second)
{
  return ((first->tv_sec <= second->tv_sec) ||
          ((first->tv_sec == second->tv_sec) && 
	  (first->tv_usec <= second->tv_usec)));
}

// Callback for notification traversal
static int traverse_cb(char *name,
		       elvin_basetypes_t type,
		       elvin_value_t value,
		       int *continue_traversal,
		       void *rock,
		       elvin_error_t error)
{
  Atom* fieldname = atoms->add(name);
  // emsg collects all the message parts
  ElvinMessage* emsg = (ElvinMessage*)rock;
  // Construct an ElvinMsgPart object of appropriate kind
  switch (type)
    {
    case ELVIN_STRING :
      {
	ElvinMsgPartString* part = 
	  new ElvinMsgPartString(fieldname, value.s);
	emsg->pushMsgPart(part);
	break;
      }
    case ELVIN_INT32:
      {
	ElvinMsgPartInt* part = 
	  new ElvinMsgPartInt(fieldname, value.i);
	emsg->pushMsgPart(part);
	break;
      }
    case ELVIN_INT64:
      {
	ElvinMsgPartInt64* part = 
	  new ElvinMsgPartInt64(fieldname, value.h);
	emsg->pushMsgPart(part);
	break;
      }
    case ELVIN_REAL64:
      {
	ElvinMsgPartReal64* part = 
	  new ElvinMsgPartReal64(fieldname, value.d);
	emsg->pushMsgPart(part);
	break;
      }
    case ELVIN_OPAQUE:
      {
	ElvinMsgPartOpaque* part = 
	  new ElvinMsgPartOpaque(fieldname, value.o);
	emsg->pushMsgPart(part);
	break;
      }
      
    default:
      break;
      
    }
  return 0;
}

/* This is called when we receive a notification */
static int notify_cb(elvin_handle_t handle,
              elvin_subscription_t sub,
              elvin_notification_t notification,
              int is_secure,
              void *rock,
              elvin_error_t err)
{
  SubscriptionData* sdata = (SubscriptionData*)rock;
  ThreadTableLoc thread_id = sdata->getThreadID();
  ElvinMessage* emsg = new ElvinMessage(thread_id);
  int continue_traversal = 1;
  if (!(elvin_notification_traverse(notification,
				   traverse_cb,
				   &continue_traversal,
				   emsg,
				   err) == 0)) 
    {
      elvin_error_fprintf(stderr, err);
      exit(1);
    }
  // Add the new message to the pending messages
  elvin_channel_ptr->pushPending(emsg);
  return 0;
}

static elvin_io_handler_t add_io_handler(int fd,
                                         uint32_t mask,
                                         elvin_io_handler_cb_t callback,
                                         void* rock,
                                         void* /* mainloop_rock */,
                                         elvin_error_t error)
{
  elvin_io_handler_t hand = 
    elvin_io_handler_alloc(client, callback, rock, fd, mask, error);
  
  bool read =
    (mask & (ELVIN_READ_MASK | ELVIN_ACCEPT_MASK | ELVIN_ERROR_MASK)) ? true : false;
  
  // Create a new elvin handler and add to message channel
  ElvinHandler* elvin_handler = new ElvinHandler(read, fd, hand);
  elvin_channel_ptr->addHandler(elvin_handler);
  return hand;
}

static int modify_io_handler(elvin_io_handler_t handler,
    uint32_t *mask,
    elvin_io_handler_cb_t callback,
    void **io_handler_rock,
    void *mainloop_rock,
    elvin_error_t error)
{
cerr << "modify " << endl;
return 1;
}

static int remove_io_handler(elvin_io_handler_t hand,
                             void* /* mainloop_rock */,
                             elvin_error_t error)
{
  elvin_channel_ptr->removeHandler(hand);
  return elvin_io_handler_free(hand, error);
}

static elvin_timeout_t add_timeout(uint32_t ms_delay,
                                   elvin_timeout_cb_t callback,
                                   void* rock,
                                   void* /* mainloop_rock */,
                                   elvin_error_t error)
{
  elvin_timeout_t timeout =
    elvin_timeout_alloc(client, ms_delay, callback, rock, error);
  elvin_channel_ptr->addTimeout(timeout);
  return timeout;
}

static int modify_timeout(elvin_timeout_t timeout,
    uint32_t *ms_delay,
    elvin_timeout_cb_t callback,
    void **timeout_rock,
    void *mainloop_rock,
    elvin_error_t error)
{
cerr << "modify timeout" << endl;
return 1;
}

static int remove_timeout(elvin_timeout_t timeout,
                          void* /* mainloop_rock */,
                          elvin_error_t error)
{
  if (elvin_channel_ptr->removeTimeout(timeout))
    {
      return elvin_timeout_free(timeout, error);
    }
  else
    {
      return 0;
    }
}

// Subscription callback
static int subscribe_cb(elvin_handle_t /*handle*/, int /*result*/,
                         elvin_subscription_t subscription, void *rock,
                         elvin_error_t error)
{

  ((SubscriptionData*)rock)->setSubscription(subscription); 
  elvin_channel_ptr->pushSubData((SubscriptionData*)rock);
  return 1;
}

static int unsubscribe_cb(elvin_handle_t /*handle*/, int /*result*/,
                         elvin_subscription_t subscription, void *rock,
                         elvin_error_t error)
{
  return 1;
}

static int status_cb(elvin_handle_t handle, elvin_status_event_t event,
                     void *rock, elvin_error_t error)
{
  //cerr << "Status event " << event->description << endl;
  return 1;
}

static int connect_cb(elvin_handle_t handle, int /* result */,
                       void* rock, elvin_error_t error)
{
  elvin_channel_ptr->setConnected();
  return 1;
}

static int disconnect_cb(elvin_handle_t handle, int /* result */,
                       void* rock, elvin_error_t error)
{
  elvin_channel_ptr->setDisconnected();
  return 1;
}

//
// Convert a C-string into a QP ASCII list/
//
static Object* charsToList(Heap& heap, char* s)
{
  char* c = s;
  if (*c == '\0')
    {
      return AtomTable::nil;
    }
  Cons* list = heap.newCons();
  Object* result = list;
  while (true)
    {
      list->setHead(heap.newNumber((int)(*c)));
      c++;
      if (*c == '\0')
	{
	  list->setTail(AtomTable::nil);
	  break;
	}
      Cons* list_tmp = heap.newCons();
      list->setTail(list_tmp);
      list = list_tmp;
    }
  return result;
}

//
// Convert a string object into a QP  ASCII list/
// NOTE: string may contain 0's
//
static Object* stringToList(Heap& heap, string& s)
{
  Object* val = AtomTable::nil;

  for (int i = s.length()-1; i >= 0; i--)
    {
       Cons* list = heap.newCons();
       list->setHead(heap.newNumber((int)(s[i])));
       list->setTail(val);
       val = list;
    }
  return val;
}

//
// Convert a QP ASCII list into a string via an ostringstream
//
static void listToString(Object* arg, ostringstream& str)
{
  while (arg->isCons())
    {
      Cons* list = OBJECT_CAST(Cons*, arg);
      str << (char)(list->getHead()->variableDereference()->getNumber());
      arg = list->getTail()->variableDereference();
    }
}

//
// Use the atom '$elvin' as the sender and reply to addresses.
// THis can be used at the Prolog level to determine that the message
// comes from Elvin rather than ICM.
//
Object*
ElvinMessage::constructSenderTerm(Thread& thread, AtomTable& atoms)
{
  return atoms.add("$elvin");
}

Object*
ElvinMessage::constructReplyToTerm(Thread& thread, AtomTable& atoms)
{  
  return atoms.add("$elvin");
}

////////////////////////////////////////////////////////////////
// Construct Prolog terms for each kind of ElvinMsgPart objects
//

//
// Elvin-strings are converted to QP ASCII lists
//
Object*
ElvinMsgPartString::buildTerm(Thread& thread, AtomTable& atoms)
{
  Heap& heap = thread.TheHeap();
  return charsToList(heap, const_cast<char*>(value.c_str()));
}

//
// Elvin int32's are converted to QP integers
//
Object*
ElvinMsgPartInt::buildTerm(Thread& thread, AtomTable& atoms)
{
  Heap& heap = thread.TheHeap();
  return heap.newNumber(value);
}

//
// Elvin int64's are converted to atoms and wrapped in a 'int64' structure
// i.e. 999999999999 is converted to the term int64('999999999999')
//
Object*
ElvinMsgPartInt64::buildTerm(Thread& thread, AtomTable& atoms)
{
  Heap& heap = thread.TheHeap();
  ostringstream str;
  str << value << ends;
  Object* a =  atoms.add(const_cast<char*>(str.str().c_str()));
  Structure* val = heap.newStructure(1);
  val->setFunctor(atoms.add("int64"));
  val->setArgument(1, a);
  return val;
}
//
// Elvin real64's are converted to atoms and wrapped in a 'real64' structure
// i.e. 999999.999999 is converted to the term real64('999999.999999')
//
Object*
ElvinMsgPartReal64::buildTerm(Thread& thread, AtomTable& atoms)
{
  Heap& heap = thread.TheHeap();
  ostringstream str;
  str << value << ends;
  Object* a =  atoms.add(const_cast<char*>(str.str().c_str()));
  Structure* val = heap.newStructure(1);
  val->setFunctor(atoms.add("real64"));
  val->setArgument(1, a);
  return val;
}

//
// Elvin opaques are dealt with in 2 different ways.
// If the opaque starts with  "$qpterm$" then the value 
// (after removing the "$qpterm$") is treated as
// and encoded QP term and so is decoded to that term.
// Otherwise it is converted to a term of the form opaque(QPList)
// where QPList is the corresponding  QP ASCII list.
//
static const char* qpterm_str = "$qpterm$";
static const int qpterm_str_len = 8;

Object*
ElvinMsgPartOpaque::buildTerm(Thread& thread, AtomTable& atoms)
{
  Heap& heap = thread.TheHeap();
  if (value.find(qpterm_str) == 0)
    {
      Object* object_variablenames;
      Object* oval;
      string encoded = value.substr(qpterm_str_len);
      QPistringstream stream(encoded);
      EncodeRead er(thread,
                    heap,
                    stream,
                    oval,
                    atoms,
                    false,
                    thread.getNames(),
                    object_variablenames);
      Structure* val = heap.newStructure(1);
      val->setFunctor(atoms.add("qpterm"));
      val->setArgument(1, oval);
      return val;
    }
  else
    {
      Object* oval = stringToList(heap, value);
      Structure* val = heap.newStructure(1);
      val->setFunctor(atoms.add("opaque"));
      val->setArgument(1, oval);
      return val;
    }
}

//
// Turn a list of ElvinMsgPart terms into a QP list whose elements are
// of the form fieldname = value-term
//
Object*
ElvinMessage::constructMessageTerm(Thread& thread, AtomTable& atoms, bool rn)
{
  Heap& heap = thread.TheHeap();
  Object* result = AtomTable::nil;

  for (list<ElvinMsgPart*>::reverse_iterator riter = elvin_msg.rbegin();
       riter != elvin_msg.rend();
       riter++)
    {
      Structure* str = heap.newStructure(2);
      str->setFunctor(AtomTable::equal);
      str->setArgument(1, (*riter)->getName());
      str->setArgument(2, (*riter)->buildTerm(thread, atoms));
      Cons* list = heap.newCons(str, result);
      result = list;
    }
  return result;
}

void
ElvinHandler::callHandler(elvin_error_t error)
{
  uint32_t active_mask;

  
  int would_block = 0;
  if (! elvin_io_handler_get_mask(handler,
				  &active_mask,
				  error)) {
    elvin_error_fprintf(stderr, error);
    exit(1);
  }

  if (! elvin_io_handler_dispatch(handler,
				  active_mask,
				  &would_block,
				  error)) {
    elvin_error_fprintf(stderr, error);
    exit(1);
  }

}

//
// Time to unconnect from Elvin - delete ElvinMessageChannel object
//
ElvinMessageChannel::~ElvinMessageChannel()
{
  // delete handlers
  for (list<ElvinHandler*>::iterator iter = elvin_handlers.begin();
       iter != elvin_handlers.end();
       iter++)
    {
      delete *iter;
    }
  // delete pending messages
  for (list<ElvinMessage*>::iterator iter = pending_messages.begin();
       iter != pending_messages.end();
       iter++)
    {
      delete *iter;
    }
  // free Elvin handles
  if (elvin_handle_free(handle, error) == 0)
      {
        cerr <<  "*** elvin_handle_free(): failed" << endl;
        elvin_error_fprintf(stderr, error);
        exit(1);
      }
  // free client
  if (elvin_client_free(client, error) == 0)
    {
      cerr <<  "*** elvin_client_free(): failed" << endl;
      elvin_error_fprintf(stderr, error);
      exit(1);
    }

  // free Elvin error
  if (elvin_error_free(error, NULL) == 0)
      {
        cerr <<  "*** elvin_error_free(): failed" << endl;
        exit(1);
      }
}

//
// Remove a given handler
//
void
ElvinMessageChannel::removeHandler(elvin_io_handler_t h)
{
  for (list<ElvinHandler*>::iterator iter = elvin_handlers.begin();
       iter != elvin_handlers.end();
       iter++)
    {
      if ((*iter)->sameHandler(h))
	{
	  (*iter)->makeTrash();  // set for later deletion
	  return;
	}
    }
}

// Add a timeout to the registered timeouts
void
ElvinMessageChannel:: addTimeout(elvin_timeout_t timeout)
{
  struct timeval expiry_time;
  if (!elvin_timeout_expiry_time(timeout, &expiry_time, error))
    {
      cerr << "Error in addTimeout" << endl;       
      elvin_error_fprintf(stderr, error);
      exit(1);
    }
  
  for (list<elvin_timeout_t>::iterator iter = reg_timeouts.begin();
       iter != reg_timeouts.end();
       iter++)
    {
      struct timeval item_expiry_time;
      if (!elvin_timeout_expiry_time((*iter), &item_expiry_time, error))
	{
	  cerr << "Error in addTimeout" << endl;       
	  elvin_error_fprintf(stderr, error);
	  exit(1);
	}
      if (timeout_before(&expiry_time, &item_expiry_time))
	{
	  reg_timeouts.insert(iter, timeout);
	  return;
	}
    }
  reg_timeouts.push_front(timeout);
}

// Remove a timeout from the registered timeouts
int 
ElvinMessageChannel::removeTimeout(elvin_timeout_t timeout)
{
    for (list<elvin_timeout_t>::iterator iter = reg_timeouts.begin();
       iter != reg_timeouts.end();
       iter++)
    {
      if ((*iter) == timeout)
	{
	  reg_timeouts.erase(iter);
	  return 1;
	}
    }
    return 0;
}

// Process expired timeouts
void 
ElvinMessageChannel::processTimeouts(struct timeval& next)
{
  struct timeval now;
  if( gettimeofday(&now, NULL) != 0) cerr << "gettimeofday failed" << endl;

  for (list<elvin_timeout_t>::iterator iter = reg_timeouts.begin();
       iter != reg_timeouts.end();
       )
    {
      struct timeval item_expiry_time;
      if (!elvin_timeout_expiry_time((*iter), &item_expiry_time, error))
	{
	  cerr << "Error in processTimeouts" << endl;       
	  elvin_error_fprintf(stderr, error);
	  exit(1);
	}

      if (timeout_before(&item_expiry_time, &now))
	{
	  if (!elvin_timeout_dispatch((*iter), error)) 
	    {
	      elvin_error_fprintf(stderr, error);
	      exit(1);
	    }
	  elvin_timeout_free((*iter), NULL);
	  iter = reg_timeouts.erase(iter);
	}
      else
	{
	  struct timeval n1;
          if (now.tv_usec > item_expiry_time.tv_usec)
	    { 
	      n1.tv_usec = 1000000 + item_expiry_time.tv_usec - now.tv_usec;
	      n1.tv_sec = item_expiry_time.tv_sec - now.tv_sec - 1;
	    }
	  else
	    {
	      n1.tv_usec = item_expiry_time.tv_usec - now.tv_usec;
	      n1.tv_sec = item_expiry_time.tv_sec - now.tv_sec;
	    }
	  if (((next.tv_sec == 0) && (next.tv_usec == 0)) 
	      || timeout_before(&n1, &next)) 
	    {
	      next.tv_sec = n1.tv_sec;
	      next.tv_usec = n1.tv_usec;
	    }
	  return;
	}
    }
}


//
// Update the FD sets for use in select
//
void
ElvinMessageChannel::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
  // Consider all the handlers
  for (list<ElvinHandler*>::iterator iter = elvin_handlers.begin();
       iter != elvin_handlers.end();
       )
    {
      if ((*iter)->isTrash())
	{
	  // Marked for deletion - so delete
	  delete (*iter);
	  iter = elvin_handlers.erase(iter);
	}
      else
	{
	  // Update appropriate FD set and max FD
	  int fd = (*iter)->getFD();
	  if (fd > max_fd) max_fd = fd;
	  if ((*iter)->isRead())
	    {
	      FD_SET(fd, rfds);
	    }
	  else
	    {
	      FD_SET(fd, wfds);
	    }
	  iter++;
	}
    }
}

//
// Shuffle all notifications to appropriate QP threads
//
bool
ElvinMessageChannel::ShuffleMessages(void)
{
  fd_set rfds,wfds;

  // Continue processing until no more events on Elvin sockets.
  while(true)
    {
      int max_fd = 0;
      
      FD_ZERO(&rfds);
      FD_ZERO(&wfds);
      // Set up the time value to indicate a poll
      timeval tv = { 0, 0 };

      updateFDSETS(&rfds, &wfds, max_fd);
      
      // Poll on Elvin sockets
      int fdresult = select(max_fd + 1, &rfds, &wfds, (fd_set *) NULL, &tv);

      if(fdresult > 0)
	{
	  // Move notifications into pending list
	  processFDs(&rfds, &wfds);
	}
      else
	{
	  break;
	}
    }
  // Move pending notifications into QP threads message buffers.
  return processPending();
}

//
// Call the handlers for Elvin sockets.
//
void
ElvinMessageChannel::processFDs(fd_set* rfds, fd_set* wfds)
{
  for (list<ElvinHandler*>::iterator iter = elvin_handlers.begin();
       iter != elvin_handlers.end();
       iter++)
    {
      if ((*iter)->isTrash())
	{
	  continue;
	}
      int fd = (*iter)->getFD();
      if (((*iter)->isRead() && FD_ISSET(fd, rfds)) ||
	  (!(*iter)->isRead() && FD_ISSET(fd, wfds)))
	{
	  // Activity on socket - so call handler
	  (*iter)->callHandler(error);
	}
    }
}


//
// Determine which thread should get the Elvin message.
//
bool
ElvinMessageChannel::msgToThread(ElvinMessage* msg)
{
  ThreadTable& thread_table = getThreadTable();
 
  ThreadTableLoc id = msg->getThreadID();
  
  if ((id == (ThreadTableLoc) -1) || !thread_table.IsValid(id))
    {
      return false;
    }
  
  Thread* thread = thread_table.LookupID(id);
  if (thread == NULL)
    {
      return false;
    }
  // Thread found so update message queue
  thread->MessageQueue().push_back(msg);
  return true;
}

//
// Process all pending messages.
//
bool
ElvinMessageChannel::processPending(void)
{
  bool did_something = false;

  while (!pending_messages.empty())
    {
      ElvinMessage* msg = pending_messages.front();
      pending_messages.pop_front();

      if (msgToThread(msg))
	{
	  did_something = true;
	}
      else
	{
	  delete msg;
	}
    }
  return did_something;
}

//
// Open an Elvin connection and initialise ElvinMessageChannel object
//
void
ElvinMessageChannel::elvinInit(Object* where) 
{
  elvin_channel_ptr = this;
  // Allocate an error context
  if (! (error = elvin_error_alloc(NULL, NULL))) 
    {
      cerr << "Unable to allocate an error" << endl;
      exit(1);
    }
  // Allocates an empty Elvin client context on the heap.
  client = elvin_client_alloc(error);
  if (client == NULL) 
    {
      cerr << "*** elvin_client_alloc(): failed" << endl;
      exit(1);
    }
  // Set up handlers
  if (!elvin_mainloop_add_rock(client, NULL, error) ||
      !elvin_mainloop_add_add_io_handler_func(client,
					      add_io_handler, error) ||
      !elvin_mainloop_add_modify_io_handler_func(client,
					      modify_io_handler, error) ||
      !elvin_mainloop_add_remove_io_handler_func(client,
						 remove_io_handler, error) ||
      !elvin_mainloop_add_add_timeout_func(client, add_timeout, error) ||
      !elvin_mainloop_add_modify_timeout_func(client, modify_timeout, error) ||
      !elvin_mainloop_add_remove_timeout_func(client,
					      remove_timeout, error)) 
    {
        exit(1);
    }

    // Create an error context for use in the callbacks
    if (elvin_error_alloc(client, error) == NULL) 
      {
        exit(1);
      }

    // Init generic mainloop
    if (!elvin_mainloop_init(client, error)) 
      {
        exit(1);
      }
    // Init network-related parts of the library
    if (!elvin_connection_init(client, error)) 
      {
        exit(1);
      }
    
    // Create a new elvin connection handle
    handle = elvin_handle_alloc(client, error);
    if (handle == NULL)
      {
        cerr << "*** elvin_handle_alloc(): failed" << endl;
        exit(1);
      }
    elvin_handle_set_status_cb(handle, status_cb, client, error);
    if (where == atoms->add("default"))
      {
        if (elvin_handle_set_discovery_scope(handle, NULL, error) == 0) 
	  {
            cerr << "Unable to set scope" << endl;
            exit(1);
	  }
        if ((elvin_handle_set_failover(handle, 1, error) == 0) ||
            (elvin_handle_set_connection_attempts(handle, 10, error) == 0)) 
	  {
            cerr << "Unable to set failover attempts" << endl;
            exit(1);
	  }

      }
    else
      {
	Structure* wherestruct = OBJECT_CAST(Structure*, where);
	// where is a QP term that is used to determine how to connect
	// If where is of the form connect(URLatom) then URLatom is
	// used to determine the connection.
	// If where is of the form discover(URLatom) then URLatom is used
	// as a scope for discovery.
	if (wherestruct->getFunctor()->variableDereference()
	    == atoms->add("connect"))
	  {
	    Atom* url = OBJECT_CAST(Atom*, wherestruct->getArgument(1)->variableDereference());
	    if (elvin_handle_append_url(handle, atoms->getAtomString(url), error) == 0)
	      {
		cerr << "Bad URL" << endl;
		exit(1);
	      }
	  }
	else 
	  {
	    Atom* url = OBJECT_CAST(Atom*, wherestruct->getArgument(1)->variableDereference());
	    if (elvin_handle_set_discovery_scope(handle, atoms->getAtomString(url), error) == 0) 
	      {
		cerr << "Unable to set scope" << endl;
		exit(1);
	      }
	    if ((elvin_handle_set_failover(handle, 1, error) == 0) ||
		(elvin_handle_set_connection_attempts(handle, 10, error) == 0)) 
	      {
		cerr << "Unable to set failover attempts" << endl;
		exit(1);
	      }
	    
	  }
      }
    // Make a connection
    if (elvin_async_connect(handle, connect_cb, &client, error) == 0)
      {
        cerr <<  "*** elvin_connect(): failed" << endl;
        elvin_error_fprintf(stderr, error);
        exit(1);
      }

    fd_set rfds,wfds;

    // Keep processing Elvin sockets until connected.
    while (!connected)
      {
	int max_fd = 0;
	
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	
	updateFDSETS(&rfds, &wfds, max_fd);
	struct timeval tout = { 0 , 0 };
	processTimeouts(tout);
	timeval* wait_val;
	if (tout.tv_sec == 0 && tout.tv_usec == 0) 
	  {
	    wait_val = NULL; 
	  }
	else 
	  {
	    wait_val = &tout;
	  }
	if (select(max_fd + 1, &rfds, &wfds, (fd_set *) NULL, wait_val) > 0)
	  {
	    processFDs(&rfds, &wfds);
	  }
      }
}

//
// Disconnect from Elvin
//
void
ElvinMessageChannel::elvinDisconnect(void) 
{
  for (list<SubscriptionData*>::iterator iter = subscription_data.begin();
       iter != subscription_data.end();
       iter++)
    {
#if 0
      // Don't need to delete subscriptions ????
      elvin_subscription_t sub = (*iter)->getSubscription();
      if (elvin_async_delete_subscription(handle, 
					 sub,
					 unsubscribe_cb, NULL,
					 error) == 0)
	{
	  elvin_error_fprintf(stderr, error);
	  exit(1);
	}
#endif
      delete *iter;
    }
  if (elvin_async_disconnect(handle, disconnect_cb, NULL, error) == 0)
    {
      cerr <<  "*** elvin_disconnect(): failed" << endl;
      elvin_error_fprintf(stderr, error);
      exit(1);
    }
  fd_set rfds,wfds;
  // Process Elvin socket events until disconnected
  while (connected)
    {
      int max_fd = 0;
      
      FD_ZERO(&rfds);
      FD_ZERO(&wfds);
      
      updateFDSETS(&rfds, &wfds, max_fd);
      struct timeval tout = { 0 , 0 };
      processTimeouts(tout);
      timeval* wait_val;
      if (tout.tv_sec == 0 && tout.tv_usec == 0) 
	{
	  wait_val = NULL; 
	}
      else 
	{
	  wait_val = &tout;
	}
      if (select(max_fd + 1, &rfds, &wfds, (fd_set *) NULL, wait_val) > 0)
	{
	  processFDs(&rfds, &wfds);
	}
      
      (void)select(max_fd + 1, &rfds, &wfds, (fd_set *) NULL, NULL);
      processFDs(&rfds, &wfds);
      
    }
  
  for (list<elvin_timeout_t>::iterator iter = reg_timeouts.begin();
       iter != reg_timeouts.end();
       )
    {
      elvin_timeout_free((*iter), error);
      iter = reg_timeouts.erase(iter);
     }

  elvin_channel_ptr = NULL;
}

//
// Add a subscription - each subscription is associated with a thread
//
bool
ElvinMessageChannel::addSubscription(ThreadTableLoc threadid, Atom* form)
{
  SubscriptionData* sub_data = new SubscriptionData(threadid, form);
  if (elvin_async_add_subscription(handle, 
				   atoms->getAtomString(form),
				   NULL, 1, notify_cb, sub_data,
				   subscribe_cb, sub_data,
				   error) == 0)
    {
      elvin_error_fprintf(stderr, error);
      return false;
    }
  return true;
} 

// 
// Delete a subscription based on a term of the form
// subsciption(ThreadName, Formula)
//
bool
ElvinMessageChannel::deleteSubscription(ThreadTableLoc threadID, Object* subterm)
{
  Object* form = subterm->variableDereference();

  for( list<SubscriptionData*>::iterator iter = subscription_data.begin();
       iter != subscription_data.end();
       iter++)
    {
      SubscriptionData* sdata = *iter;
      if (threadID != sdata->getThreadID() ||
	  form != sdata->getFormula())
	{
	  continue;
	}
      // Subscription is found
      elvin_subscription_t sub = sdata->getSubscription();
      if (elvin_async_delete_subscription(handle, 
					  sub,
					  unsubscribe_cb, NULL,
					  error) == 0)
	{
	  elvin_error_fprintf(stderr, error);
	  return false;
	}
      delete *iter;
      subscription_data.erase(iter);
      return true;
    }
  return false;
}

//
// Turn the information about subscriptions into a QP list whose
// elements are of the form subsciption(ThreadName, Formula)
//
Object*
ElvinMessageChannel::subListToList(Thread& th)
{
  Heap& heap = th.TheHeap();
  if (subscription_data.empty())
    {
      return AtomTable::nil;
    }
  ThreadTableLoc thread_id = th.TInfo().ID();
  Object* result = AtomTable::nil;
  for( list<SubscriptionData*>::reverse_iterator riter 
	 = subscription_data.rbegin();
       riter != subscription_data.rend();
       riter++ )
    {
      SubscriptionData* sdata = *riter;
      if (sdata->getThreadID() == thread_id)
	{
	  Cons* tmplist = heap.newCons(sdata->getFormula(), result);
	  result = tmplist;
	}
    }
  return result;
}

//
// Add a notification - input is a QP list whose elements are of the form
// fieldname = ElvinTerm where ElvinTerm is of one of the following:
// QP ASCII list - converted to Elvin string
// integer               - converted to Elvin int32
// int64(atom)           - converted to Elvin int64 - atom holds number
// real64(atom)          - converted to Elvin real64
// opaque(list)          - converted to Elvin opaque
// qpterm(term)          - encoded and converted to Elvin opaque
//                         prefixed by "$qpterm$"
// 
bool
ElvinMessageChannel::addNotification(Object* object0, Thread& thread)
{
  elvin_notification_t n;

  if (! (n = elvin_notification_alloc(client, error)))
    {
      elvin_error_fprintf(stderr, error);
      return false;
    }

  while(!object0->isNil())
    {
      Cons* list = OBJECT_CAST(Cons*, object0);
      Object* head = list->getHead()->variableDereference();
      Structure* term = OBJECT_CAST(Structure*, head);
      Atom* arg1 = OBJECT_CAST(Atom*, term->getArgument(1)->variableDereference());
      Object* arg2 = term->getArgument(2)->variableDereference();
	
      if (arg2->isCons())
	{
	  ostringstream str;
	  listToString(arg2, str);
	  str << ends;
	  if (elvin_notification_add_string(n, atoms->getAtomString(arg1),
					    const_cast<char*>(str.str().c_str()),
					    error) == 0) 
	    {
	      cerr << "elvin_notification_add_string(): failed" << endl;
	      elvin_notification_free(n, error);
	      return false;
	    }
	}
      else if (arg2->isNumber())
	{
	  if (elvin_notification_add_int32(n, atoms->getAtomString(arg1),
					   arg2->getNumber(), 
					   error) == 0) 
	    {
	      cerr << "elvin_notification_add_int32(): failed" << endl;
	      elvin_notification_free(n, error);
	      return false;
	    }
	}

      else if (arg2->isStructure())
	{
	  Structure* arg2str = OBJECT_CAST(Structure*, arg2);
	  
	  Atom* func = 
	    OBJECT_CAST(Atom*, arg2str->getFunctor()->variableDereference());
	  Atom* arg = 
	    OBJECT_CAST(Atom*, arg2str->getArgument(1)->variableDereference());

	  if (func == atoms->add("int64"))
	    {
	      istringstream str(atoms->getAtomString(arg));
	      int64_t v;
	      str >> v;
	      if (elvin_notification_add_int64(n, atoms->getAtomString(arg1),
					       v, error) == 0) 
		{
		  cerr << "elvin_notification_add_int64(): failed" << endl;
		  elvin_notification_free(n, error);
		  return false;
		}
	    }
	  else if (func == atoms->add("real64"))
	    {
	      istringstream str(atoms->getAtomString(arg));
	      double v;
	      str >> v;
	      if (elvin_notification_add_real64(n, atoms->getAtomString(arg1),
						v, error) == 0) 
		{
		  cerr << "elvin_notification_add_real64(): failed" << endl;
		  elvin_notification_free(n, error);
		  return false;
		}
	    }
	  else if (func == atoms->add("opaque"))
	    {
	      ostringstream str;
	      listToString(arg, str);
	      if (elvin_notification_add_opaque(n, atoms->getAtomString(arg1), const_cast<char*>(str.str().data()),str.str().length(), error) == 0) 
		{
		  cerr << "elvin_notification_add_opaque(): failed" 
		       << endl;
		  elvin_notification_free(n, error);
		  return false;
		}
	    }
	  else
	    {
	      // Use QP term encoding
	      Heap& heap = thread.TheHeap();
	      QPostringstream str;
	      str << qpterm_str;
	      EncodeWrite ew(thread, heap, str, arg, *atoms, 
			     false, thread.getNames());
	      if (elvin_notification_add_opaque(n, atoms->getAtomString(arg1), const_cast<char*>(str.str().data()),str.str().length(), error) == 0) 
		{
		  cerr << "elvin_notification_add_opaque(): failed" 
		       << endl;
		  elvin_notification_free(n, error);
		  return false;
		}
	    }
	}

      object0 = list->getTail()->variableDereference();
    }
  
  elvin_async_notify(handle, n, 1, NULL, error);
  elvin_notification_free(n, error);
  return true;
}

///////////////////////////////////////////
// Code for constructing message ID's.
// Taken directly from ktickertape
// written by Phil Cook

static char crypt_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

static char* crypt_id(time_t now)
{
    char hostid[9];
    char salt[3];

    // Construct a salt out of the current time
    salt[0] = crypt_chars[now & 0x3f];
    salt[1] = crypt_chars[(now >> 6) & 0x3f];
    salt[2] = '\0';

    // Print the hostid into a buffer
    sprintf(hostid, "%08lx", (long)gethostid());

    // Return the encrypted result
    return crypt(hostid, salt);
}

static int uuid_count = 0;

string createUUID()
{
    string retval;
    char* cryptid;
    char* buffer;
    time_t now;
    struct tm* tm_gmt;

    // Get the time
    if (time(&now) == (time_t) -1) {
        fprintf(stderr, "unable to determine current time");
        exit(1);
    }

    // Look up what that means in GMT
    tm_gmt = gmtime(&now);

    // Construct an encrypted hostid using the time as the salt
    cryptid = crypt_id(now);
    // Construct the UUID
    buffer = new char[sizeof("YYYYMMDDHHMMSS--1234-12") + strlen(cryptid)];

    sprintf(buffer, "%04x%02x%02x%02x%02x%02x-%s-%04x-%02x",
            tm_gmt->tm_year + 1900, tm_gmt->tm_mon + 1, tm_gmt->tm_mday,
            tm_gmt->tm_hour, tm_gmt->tm_min, tm_gmt->tm_sec,
            cryptid, (int)getpid(), uuid_count);

    retval = buffer;
    delete [] buffer;

    uuid_count = (uuid_count + 1) % 256;
    return retval;
}

#endif // ELVIN_DEF
