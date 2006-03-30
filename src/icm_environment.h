// icm_environment.h -
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
// $Id: icm_environment.h,v 1.12 2006/02/14 02:40:09 qp Exp $

#ifdef ICM_DEF
#ifndef	ICM_ENVIRONMENT_H
#define	ICM_ENVIRONMENT_H

#include <list>
#include "icm.h"
#include "icm_message.h"
#include "messages.h"
#include "signals.h"

class IOManager;

class ICMEnvironment
{
 private:
  icmConn conn;
  icmHandle handle;
  long int message_no;
  char *process_symbol;
  int comm_fd;
  
 public:  
  explicit ICMEnvironment(icmConn ic)
    : conn(ic),
    handle(NULL),
    message_no(-LONG_MAX),
    process_symbol(NULL)
    { comm_fd = icmCommSocket(conn); }

  icmConn Conn(void) { return conn; }
  icmHandle Handle(void) { return handle; }
  long int & messageNo(void) { return message_no; }
  long int * messageNoRef(void) { return &message_no; }
  int getCommFD(void) { return comm_fd; }

  // Register the process symbol with the ICM comms server.
  bool Register(char *ps);

  // Unregister the process symbol with the ICM comms server.
  bool Unregister(void);
};

// The ICMMessage class - derived from the Message class
class ICMMessage : public Message
{
private:
  icmHandle sender;
  icmHandle reply_to;
  icmHandle recipient;
  icmMsg message;

public:
  ICMMessage(icmHandle s, icmHandle rt, icmHandle r, icmMsg m)
    : Message(), sender(s), reply_to(rt), recipient(r), message(m) {}

  ~ICMMessage() { icmReleaseMsg(message); }

  icmHandle getSender(void) { return sender; }
  icmHandle getRecipient(void) { return recipient; }
  icmMsg getMessage(void) { return message; }

  Object* constructSenderTerm(Thread&, AtomTable&);
  Object* constructReplyToTerm(Thread&, AtomTable&);
  Object* constructMessageTerm(Thread&, AtomTable&,
			       bool remember_names = false);
};


class ICMMessageChannel : public MessageChannel
{
 private:
  ICMEnvironment& icm_env;
  list<ICMMessage*> msg_buff;
  IOManager& iom;
  Signals& signals;

public:
  ICMMessageChannel(ICMEnvironment& e, ThreadTable& t, 
		    IOManager& i, Signals& s) 
    : MessageChannel(t), icm_env(e), iom(i), signals(s) {}

  bool msgToThread(ICMMessage*);

  bool  ShuffleMessages(void);

  void pushMessageToBuff(ICMMessage* m) { msg_buff.push_back(m); }

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd);

  void processTimeouts(Timeval& t) {}
};


#endif	// ICM_ENVIRONMENT_H

#endif // ICM_DEF

