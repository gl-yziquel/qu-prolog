// icm_message_handler.cc -
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
// $Id: icm_message_handler.cc,v 1.4 2000/12/17 21:02:17 qp Exp $

#include "config.h"

#ifdef ICM_DEF
#include "icm.h"
#include "icmP.h"
#include "icm_aux.h"
#include "icm_environment.h"
#include "icm_handle.h"
#include "icm_message_handler.h"
#include "thread_qp.h"
#include "thread_table.h"
#include "global.h"

#ifndef USE_ICM_DEREGISTER
//#warning Not using icmDeregisterAgent() call.
static bool qpDeregisterAgent(icmConn conn,
			      icmHandle handle,
			      icmHandle sender,
			      icmOption options,
			      icmMsg message);
#endif

void *
incoming_icm_message_handler(void *ie)
{
  if (ie == NULL)
    {
      Fatal(__FUNCTION__, "Bad ICM environment");
    }

  ICMEnvironment& icm_environment = *(ICMEnvironment *) ie;

  icmConn icm_conn = icm_environment.Conn();

#ifdef DEBUG_ICM
  cerr.form("%s Before message handling loop (%ld)\n", __FUNCTION__);
#endif

  icmHandle recipient;
  icmHandle sender;
  icmOption options;
  icmMsg message;
    
  long int message_no = -LONG_MAX;

  for (;;)
    {
      icmStatus status = icmGetMsg(icm_conn, 
				   &recipient, &sender, &options,
				   &message, &message_no);

      switch (status)
	{
	case icmOk:
	  {
#ifdef DEBUG_ICM
	    char recipient_buf[MAXSTRING], sender_buf[MAXSTRING];
	    (void) icmHandleName(sender, sender_buf, MAXSTRING);
	    (void) icmHandleName(recipient, recipient_buf, MAXSTRING);
	    cerr.form("%s Message received for %s from %s\n",
		      __FUNCTION__, recipient_buf, sender_buf);
#endif

#ifndef USE_ICM_DEREGISTER
	    if (qpDeregisterAgent(icm_conn, icm_environment.Handle(),
				  sender, options, message))
	      {
		return NULL;
	      }
#endif
	    icmDataRec data;
	    icmStatus status = icmScanMsg(message, "%S", &data);
            if(status == icmOk && 
	       data.size == 17 &&
	       strncmp(data.data, "control_C_message", data.size) == 0)
              {
                pthread_kill(*interrupt_handler_thread, SIGINT);
              }
            else
              {
		icmHandle replyto = sender;
	    
	        // If this call fails, replyto is unchanged
	        (void) icmIsOption(options, icmReplyto, &replyto);
	    
	        // Return the storage used by the options.
	        icmReleaseOptions(options);
	        ICMMessage *icm_message = new ICMMessage(recipient,
	    					         replyto,
						         sender,
						         message);
	        if (icm_message == NULL)
	          {
		    OutOfMemory(__FUNCTION__);
	          }
	    
	        ICMEnvironment& icm_environment = *(ICMEnvironment *) ie;
	        icm_environment.Queue().Lock();
	        icm_environment.Queue().push_back(icm_message);
	        icm_environment.Queue().Unlock();
	      }
	    if (status == icmOk)
	      {
		free(data.data);
	      }
          }
	  break;
	case icmFailed:
	  Warning(__FUNCTION__, "icmGetMsg() returned icmFailed");
	  DEBUG_ASSERT(false);
	  break;
	case icmError:
	  Warning(__FUNCTION__, "icmGetMsg() returned icmError");
	  break;
	case icmEndFile:
	  Warning(__FUNCTION__, "ICM Communicatons Server has closed connectoin");
	  break;
	}
    }
  
#ifdef DEBUG_ICM
  cerr.form("%s After message handling loop\n", __FUNCTION__);
#endif

  DEBUG_ASSERT(false);
  return NULL;
}

#ifndef USE_ICM_DEREGISTER
static bool
qpDeregisterAgent(icmConn conn,
		  icmHandle handle,
		  icmHandle sender,
		  icmOption options,
		  icmMsg message)
{
  char deregister_result[MAXSTRING];
  icmHandle deregister_handle;
  
  // TO DO: This code is a workaround for some problems with the
  // TO DO: ICM icmDeregisterAgent mechanism.
  // TO DO: It should go away when some issues have been resolved.
  if(sender==conn->server && 
     icmScanMsg(message,"%(icmDeregisterAgent%s%h%)",
		&deregister_result,
		&deregister_handle)==icmOk)
    {
      DEBUG_ASSERT(icmSameAgentHandle(deregister_handle, handle)==icmOk);

      icmReleaseMsg(message);	/* release this message */
      icmReleaseOptions(options);
      
      // No checking of deregister_result for error return values
      // in this version.
      
      // Return from message loop.
      return true;
    }
  else
    {
      return false;
    }
}
#endif
#endif //ICM_DEF
