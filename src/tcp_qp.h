// tcp_qp.h -
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
// $Id: tcp_qp.h,v 1.2 2002/11/10 07:54:54 qp Exp $

#ifndef	TCP_QP_H
#define	TCP_QP_H

#include <sys/types.h>
#include <string>

//#include "string_qp.h"

//
// Opens and binds a socket and returns it, as well as the port that
// the socket was bound to. The port is chosen by the operating system.
// The returned value is in network byte order.
//
extern int open_socket_any_port(u_short&);

//
// Opens and binds a socket and returns it. The port is chosen by the
// operating system.
//
extern int open_socket_any_port(void);

//
// Same as above, except that the port is supplied by the caller.
// The argument is in network byte order.
//
extern int open_socket(const u_short);

//
// Close the socket.
//
extern void close_socket(const int);

//
// Given a machine's name, try to find its IP address.
// (The result is in network byte order.)
//
extern u_long LookupMachineIPAddress(const std::string&);
extern u_long LookupMachineIPAddress(const char *);

//
// Find the IP address of this machine. 
// (The result is in network byte order.)
//
extern u_long LookupMachineIPAddress(void);

//
// Do a connection to a socket
//
bool do_connection(int sockfd, int port, u_long ip_address);


void getIPfromifconfig(char* ip);

#endif	// TCP_QP_H
