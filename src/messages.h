// messages.h - message processing.
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: messages.h,v 1.8 2006/02/14 02:40:09 qp Exp $

#ifndef	MESSAGES_H
#define	MESSAGES_H

#include "thread_table.h"
#include "timeval.h"

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#include <winsock2.h>
#endif

class Thread;

//
// The base class for individual messages
//
class Message
{
private:
  int references;    // reference count for deleting messages
  bool committed;   // has message been consummed?

public:
  Message():references(0),committed(false) {}

  virtual ~Message() {}

  void IncReferences(void) { references++; }
  void DecReferences(void) { references--; }

  size_t References(void) const { return references; }

  void Commit(void) { committed = true; }
  bool Committed(void) const { return committed; }

  bool canDelete(void) const { return(committed && (references == 0)); }

  // virtual methods vor derived classes

  virtual void constructMessage(Object*& sender, Object*& msg,
				Thread&, AtomTable&,
				bool remember_names = false) = 0;
};

//
// The base class for message channels
//

class MessageChannel
{
private:
  ThreadTable& thread_table;
public:
  explicit MessageChannel(ThreadTable& t) : thread_table(t) {}

  virtual ~MessageChannel() {}

  ThreadTable& getThreadTable(void) { return thread_table; }

  // Put messages on appropriate threads' message buffer
  virtual bool ShuffleMessages(void) = 0;

  // Update FD_SET's for testing with select
  virtual void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) = 0;

  // Process timeouts related to message channel
  virtual void processTimeouts(Timeval& timeout) = 0;
};


#endif // MESSAGES_H
