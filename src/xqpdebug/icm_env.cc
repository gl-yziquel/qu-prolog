/***************************************************************************
                          icm_env.cpp  -  ICM management
                             -------------------
    begin                : Sat Dec 14 2002
    copyright            : (C) 2002 by Peter Robinson
    email                : pjr@itee.uq.edu.au
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


// $Id: icm_env.cc,v 1.2 2004/05/25 02:14:30 qp Exp $

#include <iostream>
#include <qstring.h>

#include "icm.h"
#include "icm_env.h"

using namespace std;

//
// Create an ICM environment
// name - the name of this process
// port - the port number for the ICM server
// icm_server - the machine address for the ICM server
//
// This initilizes communication and registers name with the ICM server.
// comm_fd is set to the socket used for communication
//
ICMEnvironment::ICMEnvironment(char* name, int port, 
			       char* icm_server)
    : seqNo(-LONG_MAX)
{
  strcpy(process_symbol, name);
  // Start up communications
  initICMIo();
  const icmStatus icm_status = icmInitComms(port, icm_server, &conn);

  if (icm_status == icmFailed)
    {
      cerr << " Couldn't contact ICM communications server" << endl;
      exit(1);
    }
  else if (icm_status == icmError)
    {
      cerr << " ICM communications refused connection" << endl;
      exit(1);
    }

   icmHandle tmp = icmParseHandle(process_symbol);
   const icmStatus status = icmRegisterAgent(conn, tmp, NULL, &handle);

   switch (status)
    {
    case icmOk:
      (void) icmKeepHandle(handle);
      break;
    case icmFailed:
      cerr << "Couldn't register agent name " << process_symbol << endl;
      exit(1);
      break;
    case icmError:
      cerr << "ICM comms server unavailable" << endl;
      exit(1);
      break;
    case icmEndFile:
      exit(1);
      break;
    }
    comm_fd =  icmCommSocket(conn);
    ourHandle = icmParseHandle(process_symbol);
}

//
// Deregister with ICM and close communications.
//
ICMEnvironment::~ICMEnvironment(void)
{
  const icmStatus status = icmDeregisterAgent(conn, handle);
  switch (status)
    {
    case icmOk:
      (void) icmReleaseHandle(handle);
      icmCloseComms(conn);
      break;
    case icmFailed:
      cerr << "Couldn't deregister agent name " << process_symbol << endl;
      break;
    case icmError:
      cerr << "ICM comms server unavailable" << endl;
      break;
    case icmEndFile:
      break;
    }

}

//
// Test to see if a message is availabe to read
//
bool
ICMEnvironment::msgAvail(void)
{
  return (icmMsgAvail(conn, seqNo) == icmOk);
}

//
// Read a message
//
void
ICMEnvironment::getMsg(bool& compressed, string& msgstr,
		       string& sender_name, string& replyto_name)
{
    icmHandle recip;
    icmHandle sender;
    char sender_handle_name[HANDLE_NAME_SIZE];
    char replyto_handle_name[HANDLE_NAME_SIZE];

    icmMsg msg;
    icmOption opts;
    icmStatus status = icmGetMsg(conn, &recip, &sender, &opts, &msg, &seqNo);
    switch (status)
      {
      case icmOk:
        {
          icmDataRec data;
	  if (icmScanMsg(msg, "%(%S%)", &data) == icmOk)
	    {
	      //
	      // The message is a compressed QP term
	      //
	      string buff(data.data, data.size);
	      
	      icmHandle replyto = sender;
              // If this call fails, replyto is unchanged
              (void) icmIsOption(opts, icmReplyto, &replyto);

              icmHandleName(sender, sender_handle_name,HANDLE_NAME_SIZE);
              icmHandleName(replyto, replyto_handle_name,HANDLE_NAME_SIZE);
              sender_name =  sender_handle_name;
              replyto_name =  replyto_handle_name;

	      msgstr = string(buff);
	      compressed = true;
	      free(data.data);
              icmReleaseMsg(msg);
              icmReleaseOptions(opts);

	    }
          else if (icmScanMsg(msg, (char*)"%S", &data) == icmOk)
            {
	      // 
	      // The message is a normal string message
	      // 
              icmHandle replyto = sender;
              // If this call fails, replyto is unchanged
              (void) icmIsOption(opts, icmReplyto, &replyto);

              icmHandleName(sender, sender_handle_name,HANDLE_NAME_SIZE);
              icmHandleName(replyto, replyto_handle_name,HANDLE_NAME_SIZE);
              sender_name =  sender_handle_name;
              replyto_name =  replyto_handle_name;
	      string buff(data.data, data.size);
              msgstr = string(buff);
	      compressed = false;

              free(data.data);
              icmReleaseMsg(msg);
              icmReleaseOptions(opts);
            }
          else
            {
              icmReleaseMsg(msg);
              icmReleaseOptions(opts);
              exit(0);
            }
          break;
        }
      case icmFailed:
        cerr << "icmGetMsg() returned icmFailed" << endl;;
        exit(0);
        break;
      case icmError:
        cerr << "icmGetMsg() returned icmError" << endl;
        exit(0);
        break;
      case icmEndFile:
        cerr << "ICM Communicatons Server has closed connection" << endl;
        exit(0);
        break;
      }
}

//
// Send a message
// If compressed is true, the message is sent as an encoded QP message.
// NOTE - in this case msg should be an encoded string.
// Othewise, if compressed is false, then the message is sent as a 
// normal string (and msg should be a normal string).
//
void
ICMEnvironment::sendMsg(bool compressed, string msg, 
			string to, string replyto)
{
    icmHandle tgt;
    icmHandle reply;
    icmDataRec data;
    icmOption opts;

    tgt = icmParseHandle(const_cast<char*>(to.c_str()));
    data.size = msg.length();
    data.data = const_cast<char*>(msg.c_str());
    reply = icmParseHandle(const_cast<char*>(replyto.c_str()));

    opts = icmNewOpt(NULL, icmReplyto, reply);
    if (compressed && (icmFmtSendMsg(conn, tgt, reply, 
				     opts, (char*)"%(%S%)", &data) == icmOk))
      {
	icmReleaseOptions(opts);
      }
    else if (!compressed && (icmFmtSendMsg(conn, tgt, reply, opts, 
					   (char*)"%S", &data) == icmOk))
      {
        icmReleaseOptions(opts);
      }
    else
      {
        icmReleaseOptions(opts);
	cerr << "Unable to send message" << endl;
        exit(1);
      }
}

