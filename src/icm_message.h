// icm_message.h -
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
// $Id: icm_message.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	ICM_MESSAGE_H
#define	ICM_MESSAGE_H

#include "objects.h"
#include "icm.h"
#include "mutex.h"

class ICMMessage: public Mutex
{
private:
  icmHandle recipient;
  icmHandle reply_to;
  icmHandle sender;
  icmMsg message;

  // Number of thread message iterators pointer at this message 
  // (if it's in a thread's message queue)
  size_t references;

  // Has the message been committed or not?
  bool committed;

public:
  // This constructor is used when retrieving the message from the 
  // communications server.
  ICMMessage(icmHandle r,
	     icmHandle rt,
	     icmHandle s,
	     icmMsg m)
    : recipient(r),
      reply_to(rt),
      sender(s),
      message(m),
      references(0),
      committed(false)
    {
    };
  ~ICMMessage(void)
    {
      icmReleaseMsg(message);
    }

  icmHandle Recipient(void) { return recipient; }
  icmHandle ReplyTo(void) { return reply_to; }
  icmHandle Sender(void) { return sender; }
  icmMsg Message(void) { return message; }

  void IncReferences(void) { references++; }
  void DecReferences(void) { references--; }

  size_t References(void) const { return references; }

  void Commit(void) { committed = true; }
  bool Committed(void) const { return committed; }
};

#endif	// ICM_MESSAGE_H
