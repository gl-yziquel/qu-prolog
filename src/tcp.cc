// tcp.cc -
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
// $Id: tcp.cc,v 1.3 2000/12/13 23:10:02 qp Exp $

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/utsname.h>

#include "netinet_in.h"
#include "tcp_qp.h"

extern const char *Program;

int
open_socket_any_port(u_short& port)	// Network byte order.
{
  // Open the socket
  const int s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0)
    {
      perror(__FUNCTION__);
      Fatal(__FUNCTION__, "socket() failed");
    }

  // Bind the socket
  sockaddr_in addr;
  
  memset(&addr, 0, sizeof(addr));
  
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = 0;			// System chooses port number
  
  SYSTEM_CALL_LESS_ZERO(bind(s, (sockaddr *)&addr, sizeof(addr)));
  
  // Ensure the port is reusable
  int opt_val = 1;
  SYSTEM_CALL_LESS_ZERO(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, 
				   (char *) &opt_val, sizeof(opt_val)));

  // Find out the port number we were given
  memset(&addr, 0, sizeof(addr));
  unsigned int addr_len = sizeof(addr);
  
  // Extract the port we were assigned from socket information
  SYSTEM_CALL_LESS_ZERO(getsockname(s, (sockaddr *)&addr, &addr_len));
  
  port = addr.sin_port;

  return s;
}

int
open_socket_any_port(void)
{
  u_short port;
  return open_socket_any_port(port);
}

int
open_socket(const u_short port)	// Network byte order.
{
  // Open the socket
  const int s = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket < 0)
    {
      perror(__FUNCTION__);
      Fatal(__FUNCTION__, "socket() failed");
    }

  // Bind the socket
  sockaddr_in addr;
  
  memset(&addr, 0, sizeof(addr));
  
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = port;
  
  SYSTEM_CALL_LESS_ZERO(bind(s, (sockaddr *)&addr, sizeof(addr)));

  // Ensure the port is reusable
  int opt_val = 1;
  SYSTEM_CALL_LESS_ZERO(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, 
				    (char *) &opt_val, sizeof(opt_val)));

  return s;
}

void
close_socket(const int s)
{
  SYSTEM_CALL_LESS_ZERO(close(s));
}

//
// Given a machine's name, try to find its internet address.
// (Result is in network byte order.)
//
u_long
LookupMachineIPAddress(const String& name)
{
  return LookupMachineIPAddress(name.Str());
}

u_long
LookupMachineIPAddress(const char *name)
{
  //
  // Code adapted from W. Richard Stevens ``Unix Network Programming''.
  //
  // First try to convert the host name as a dotted-decimal number.
  // Only if that fails do we call gethostbyname().
  //
  u_long inaddr;
  hostent host_info;
  sockaddr_in remote_addr;

  inaddr = inet_addr(name);

  if (inaddr != INADDR_NONE)
    {
      // it's dotted-decimal
      memcpy((char *) &remote_addr.sin_addr,
	     (char *) &inaddr,
	     sizeof(inaddr));
      host_info.h_name = NULL;

    }
  else
    {
      hostent *hp;
      
      if ( (hp = gethostbyname(name)) == NULL)
	{
	  Warning(__FUNCTION__, "host name error");
	  return false;
	}

      host_info = *hp;    // found it by name, structure copy

      memcpy((char *) &remote_addr.sin_addr,
	     (char *) hp->h_addr,
	     hp->h_length);
    }

  return remote_addr.sin_addr.s_addr;
}

//
// Try to find the IP address of this machine.
// (Result is in network byte order.)
//
u_long
LookupMachineIPAddress(void)
{
  struct utsname name;
  
  SYSTEM_CALL_LESS_ZERO(uname(&name));

  return LookupMachineIPAddress(name.nodename);
}









