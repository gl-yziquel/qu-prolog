//
// tcp_escapes.cc - TCP interface for Qu-Prolog.
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
// Prolog Primitives to support TCP comunication
//

#include "config.h"
#include "global.h"                                                             
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/file.h>
#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif	// HAVE_SYS_FILIO_H
#include <sys/un.h>
#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif	// HAVE_SYS_SOCKIO_H
#include <sys/ioctl.h>
#include <net/if.h>
#include <fcntl.h>

#if defined(HAVE_POLL)
#if defined(LINUX)
#include <sys/poll.h>
#else
#include <poll.h>
#endif // defined(LINUX)
#endif // defined(HAVE_POLL)

#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <iostream.h>
#include <strstream.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "arpa_inet.h"
#include "atom_table.h"
#include "is_ready.h"
#include "netinet_in.h"
#include "thread_qp.h"

extern IOManager *iom;
extern SocketManager *sockm;

//
// decode_socket decodes the socket number supplied in the cell,
// and checks whether it corresponds to a currently allocated
// socket.
//
// On success, it sets the Socket ** argument to the address of the
// appropriate socket object, and returns a value of EV_NO_ERROR.
// On failure, it returns the appropriate error value.
//
static ErrorValue
decode_socket(Heap& heap,
	      Object * socket_cell,
	      Socket **socket)
{
  *socket = (Socket *) NULL;

  if (socket_cell->isVariable())
    {
      return EV_INST;
    }
  else if (socket_cell->isNumber())
    {
      const int socket_number = socket_cell->getNumber();
      if (socket_number < 0 || socket_number >= (int)NUM_OPEN_SOCKETS)
	{
	  return EV_TYPE;
	}
      *socket = sockm->GetSocket(socket_number);
      if (*socket == NULL)
	{
	  return EV_TYPE;
	}
      return EV_NO_ERROR;
    }
  else
    {
      return EV_TYPE;
    }
}

//
// DECODE_SOCKET_ARG is a wrapper for calls to decode_socket()
//
#define DECODE_SOCKET_ARG(heap, cell, arg_num, socket)			\
  do {									\
    const ErrorValue result = decode_socket(heap, cell, &socket);	\
    if (result != EV_NO_ERROR)						\
      {									\
	PSI_ERROR_RETURN(result, arg_num);				\
      }									\
  } while (0)
  
//
// decode_port() decodes a port number from the supplied cell.
// On success, the u_short& argument is set to the port number
// and EV_NO_ERROR is returned.
// On failure, an appropriate error value is returned.
// The returned port is in network byte order.
//
static ErrorValue
decode_port(Heap& heap,
	    Object * port_cell,
	    u_short& port)	// Network byte order.
{
  port = 0;

  if (port_cell->isVariable())
    {
      return EV_INST;
    }
  else if (port_cell->isNumber())
    {
      port = htons((u_short)(port_cell->getNumber()));
      return EV_NO_ERROR;
    }
  else
    {
      return EV_TYPE;
    }
}

//
// DECODE_PORT_ARG is a wrapper for decode_port() calls.
//
#define DECODE_PORT_ARG(heap, cell, arg_num, port)		\
  do {								\
    const ErrorValue result = decode_port(heap, cell, port);	\
    if (result != EV_NO_ERROR)					\
      {								\
        PSI_ERROR_RETURN(result, arg_num);			\
      }								\
  } while (0)

//
// machine_ip_address() decodes an IP address from a supplied cell.
// On success, the IP address is returned.
// (The returned value is in network byte order.)
// On failure, a value of 0 (which is an invalid address) is returned.
//
static u_long
machine_ip_address(Heap& heap,
		   AtomTable& atoms,
		   Object * addr)
{
  if (addr->isNumber())
    {
      return(htonl((u_long)(addr->getNumber())));
    }
  else if (addr->isAtom())
    {
      char hostname[1000];
      (void)strcpy(hostname, atoms.getAtomString(OBJECT_CAST(Atom*, addr)));
      if (strcmp(hostname, "localhost") == 0)
	{
	  if (gethostname(hostname, 1000) != 0)
	    {
	      return 0;
	    }
	}
      hostent *hp;
      if (hp != gethostbyname(hostname))
        {
          struct in_addr in;
          in.s_addr = inet_addr(hostname);
          hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
        }
      endhostent();
      if (hp)
        {
          return(*(int *)hp->h_addr_list[0]);
        }
      else
        {
          return 0;
        }
    }
  else
    {
      return 0;
    }
}

//
// decode_ip_address() decodes an IP address supplied in the Object *& 
// argument.
// On success, the Object *& argument is set to the IP address, and a value
// of EV_NO_ERROR is returned.
// On failure, an appropriate error value is returned.
// (The ip address is returned in network byte order.)
//
static ErrorValue
decode_ip_address(Heap& heap, AtomTable& atoms,
		  Object * ip_address_cell,
		  u_long& ip_address)
{
  ip_address = INADDR_NONE;

  if (ip_address_cell->isVariable())
    {
      return EV_INST;
    }

  if (ip_address_cell->isNumber() || ip_address_cell->isAtom())
    {
      ip_address = machine_ip_address(heap, atoms, ip_address_cell);
      if (ip_address)
        {
          return EV_NO_ERROR;
        }
      else if (ip_address_cell == AtomTable::inaddr_any)
        {
          ip_address = INADDR_ANY;
          return EV_NO_ERROR;
        }
      else
        {
          return EV_VALUE;
        }
    }
  else
    {
      return EV_TYPE;
    }
}

//
// DECODE_IP_ADDRESS_ARG is a wrapper for decode_ip_address() calls.
//
#define DECODE_IP_ADDRESS_ARG(heap, atoms, cell, arg_num, ip_address)	 \
  do {									 \
    const ErrorValue result = decode_ip_address(heap, atoms, cell, ip_address); \
    if (result != EV_NO_ERROR)						 \
      {									 \
        PSI_ERROR_RETURN(result, arg_num);				 \
      }									 \
  } while (0)


//
// @internaldoc
// @pred '$open_socket_stream'(Socket, IOMode, Stream)
// @mode '$tcp_connect1'(+, +, -)
// @type '$tcp_connect1'(Integer, Integer, StreamID)
// @description
// Open a stream for either reading or writing on the socket.
// @end pred
// @end internaldoc

Thread::ReturnValue
Thread::psi_open_socket_stream(Object *& socket_arg, Object *& mode_arg, 
			       Object *& stream_arg)
{
  DEBUG_ASSERT(mode_arg->variableDereference()->isNumber());
  int mode = mode_arg->variableDereference()->getNumber();

  Object* argS = socket_arg->variableDereference();

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  switch (mode)
    {
    case AM_READ:
      {
//	ifstream *istrm = new ifstream(socket->getFD(), NULL, 0);
	ifstream *istrm = new ifstream(socket->getFD());
        if (istrm == NULL)
          {
            OutOfMemory(__FUNCTION__);
          }
	
        if (istrm->bad())
          {
            delete istrm;
            PSI_ERROR_RETURN(EV_VALUE, 0);
          }
	
        Stream *stream = new Stream(istrm);
        if (stream == NULL)
          {
            OutOfMemory(__FUNCTION__);
          }
	
        //
        // Return index of the stream.
        //
	int streamno = iom->OpenStream(stream);
	socket->setIStream(streamno);
        stream_arg = heap.newNumber(streamno);
        return RV_SUCCESS;
      }
      break;
    case AM_WRITE:
      {
        ofstream *ostrm = new ofstream(socket->getFD());
        if (ostrm == NULL)
          {
            OutOfMemory(__FUNCTION__);
          }
	
        if (ostrm->bad())
          {
            delete ostrm;
            PSI_ERROR_RETURN(EV_VALUE, 0);
          }
	
        Stream *stream = new Stream(ostrm);
        if (stream == NULL)
          {
            OutOfMemory(__FUNCTION__);
          }
	
        //
        // Return index of the stream.
        //
	int streamno = iom->OpenStream(stream);
	socket->setOStream(streamno);
        stream_arg = heap.newNumber(streamno);
        return RV_SUCCESS;
      }
      break;
    case AM_APPEND:
      DEBUG_ASSERT(false);
      break;
    }
  return RV_FAIL;
}

// @doc 
// @pred tcp_socket(Socket, Type, Protocol)
// @mode tcp_socket(-, +, +) is semidet
// @type tcp_socket(Integer, Atom, Atom)
// @description
// Corresponds to: socket(3N)
//
// Type is the atoms:
//  'sock_stream'
//
// Protocol is the atoms:
//  'ipproto_ip'
//
// We have commited ourselves to AF_INET family.
//
// Fails if the no socket can be allocated.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_socket(
	       Object *& socket_arg,
	       Object *& type_arg,
	       Object *& protocol_arg)
{
  Object* argT = heap.dereference(type_arg);
  Object* argP = heap.dereference(protocol_arg);

  if (argT->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (argP->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }

  int type;
  
  if (argT->isAtom())
    {

      if (argT == AtomTable::sock_stream)
	{
	  type = SOCK_STREAM;
	}
      else
	{
	  PSI_ERROR_RETURN(EV_VALUE, 2);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  int protocol;

  if (argP->isAtom())
    {
      if (argP == AtomTable::ipproto_ip)
	{
	  protocol = IPPROTO_IP;
	}
      else 
	{
	  PSI_ERROR_RETURN(EV_VALUE, 3);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }

  const int fd = socket(AF_INET, type, protocol);
  if (fd < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  Socket *socket = new Socket(type, protocol, fd);
  if (socket == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  socket->setSocket();


  socket_arg = heap.newNumber(sockm->OpenSocket(socket));

  return RV_SUCCESS;
}

// @doc
// @pred tcp_setsockopt(Socket, Optname, Value)
// @mode tcp_setsockopt(+, +, +) is det
// @type tcp_setsockopt(Integer, Atom, Integer)
// @description
// Corresponds to: setsockopt(3N)
//
// Optname is one of following atoms:
//  'so_debug'		= turn on debugging info recording
//  'so_reuseaddr'	= allow local IPAddress reuse
//  'so_keepalive'	= keep connections alive
//  'so_dontroute'	= just use interface IPAddresses
//  'so_broadcast'	= permit sending of broadcast msgs
//  'so_oobinline'	= leave received OOB data in line
//  'so_sndbuf'		= size of send buffer
//  'so_rcvbuf'		= size of receive buffer
//  'so_sndtimeo'	= send timeout
//  'so_rcvtimeo'	= receive timeout
//
// For now we only support the SOL_SOCKET level
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_setsockopt(Object *& socket_arg, Object *& option_arg,
			   Object *& value_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argO = heap.dereference(option_arg);
  Object* argV = heap.dereference(value_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (argO->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (argV->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }

  int opt;
  
  if (argO->isAtom())
    {
      if (argO == AtomTable::so_debug)
	{
	  opt = SO_DEBUG;
	}
      else if (argO == AtomTable::so_reuseaddr)
	{
	  opt = SO_REUSEADDR;
	}
      else if (argO == AtomTable::so_keepalive)
	{
	  opt = SO_KEEPALIVE;
	}
      else if (argO == AtomTable::so_dontroute)
	{
	  opt = SO_DONTROUTE;
	}
      else if (argO == AtomTable::so_broadcast)
	{
	  //opt = SO_BROADCAST;
	  return RV_FAIL;
	}
      else if (argO == AtomTable::so_oobinline)
	{
	  opt = SO_OOBINLINE;
	}
      else if (argO == AtomTable::so_sndbuf)
	{
	  opt = SO_SNDBUF;
	}
      else if (argO == AtomTable::so_rcvbuf)
	{
	  opt = SO_RCVBUF;
	}
#ifdef SO_SNDTIMEO
      else if (argO == AtomTable::so_sndtimeo)
	{
	  opt = SO_SNDTIMEO;
	}
#endif	// SO_SNDTIMEO
#ifdef SO_RCVTIMEO
      else if (argO == AtomTable::so_rcvtimeo)
	{
	  opt = SO_RCVTIMEO;
	}
#endif	// SO_RCVTIMEO
      else 
	{
	  PSI_ERROR_RETURN(EV_VALUE, 2);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  int val;

  if (argV->isNumber())
    {
      val = argV->getNumber();
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }

  const int ret = setsockopt(socket->getFD(),
			     SOL_SOCKET, opt, (char *)&val, sizeof(val));
  if (ret < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }
    
  return RV_SUCCESS;
}

// @doc 
// @pred tcp_getsockopt(Socket, Optname, Value)
// @mode tcp_getsockopt(+, +, -) is det
// @type tcp_getsockopt(Integer, Atom, Integer)
// @description
// Corresponds to: getsockopt(3N)
//
// Optname is one of following atoms:
//  'so_debug'		= turn on debugging info recording
//  'so_reuseaddr'	= allow local IPAddress reuse
//  'so_keepalive'	= keep connections alive
//  'so_dontroute'	= just use interface IPAddresses
//  'so_broadcast'	= permit sending of broadcast msgs
//  'so_oobinline'	= leave received OOB data in line
//  'so_sndbuf'		= size of send buffer
//  'so_rcvbuf'		= size of receive buffer
//  'so_sndtimeo'	= send timeout
//  'so_rcvtimeo'	= receive timeout
//  'so_error'		= get error status and clear
//  'so_type'		= get socket type
//
// For now we only support the SOL_SOCKET level
// @end doc
Thread::ReturnValue
Thread::psi_tcp_getsockopt(
		   Object *& socket_arg,
		   Object *& option_arg,
		   Object *& value_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argO = heap.dereference(option_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (argO->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  int opt = 0;

  if (argO->isAtom())
    {
      if (argO == AtomTable::so_debug)
	{
	  opt = SO_DEBUG;
	}
      else if (argO == AtomTable::so_reuseaddr)
	{
	  opt = SO_REUSEADDR;
	}
      else if (argO == AtomTable::so_keepalive)
	{
	  opt = SO_KEEPALIVE;
	}
      else if (argO == AtomTable::so_dontroute)
	{
	  opt = SO_DONTROUTE;
	}
      else if (argO == AtomTable::so_broadcast)
	{
	  opt = SO_BROADCAST;
	}
      else if (argO == AtomTable::so_oobinline)
	{
	  opt = SO_OOBINLINE;
	}
      else if (argO == AtomTable::so_sndbuf)
	{
	  opt = SO_SNDBUF;
	}
      else if (argO == AtomTable::so_rcvbuf)
	{
	  opt = SO_RCVBUF;
	}
#ifdef SO_SNDTIMEO
      else if (argO == AtomTable::so_sndtimeo)
	{
	  opt = SO_SNDTIMEO;
	}
#endif	// SO_SNDTIMEO
#ifdef SO_RCVTIMEO
      else if (argO == AtomTable::so_rcvtimeo)
	{
	  opt = SO_RCVTIMEO;
	}
#endif	// SO_RCVTIMEO
      else if (argO == AtomTable::so_error)
	{
	  opt = SO_ERROR;
	}
      else if (argO == AtomTable::so_type)
	{
	  opt = SO_TYPE;
	}
      else
	{
	  PSI_ERROR_RETURN(EV_VALUE, 2);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  int val;
  unsigned int len = sizeof(val);

  if (getsockopt(socket->getFD(), SOL_SOCKET, opt,
		 (char *)&val, &len))
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  value_arg = heap.newNumber(val);

  return RV_SUCCESS;
}

// @doc 
// @pred tcp_bind(Socket, Port, IPAddress)
// @mode tcp_bind(+, +, +) is det
// @type tcp_bind(Integer, Integer, IPAddress)
// @description
// Corresponds to: bind(3N)
//
// Bind the socket to the specified port and address.
//
// An IPAddress is either an integer or the atom 'inaddr_any'.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_bind(Object *& socket_arg,
		     Object *& port_arg,
		     Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argP = heap.dereference(port_arg);
  Object* argA = heap.dereference(ip_address_arg);

  Socket *socket = NULL;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  u_short port = 0;
  DECODE_PORT_ARG(heap, argP, 2, port);

  u_long ip_address = 0;
  DECODE_IP_ADDRESS_ARG(heap, *atoms, argA, 3, ip_address);

  if (!socket->isBindAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
  
  struct sockaddr_in server;
  
  server.sin_family = AF_INET;
  //server.sin_addr.s_addr = htonl((u_long)ip_address);
  //server.sin_port = htons((u_short)port);
  server.sin_addr.s_addr = ((u_long)ip_address);
  server.sin_port = ((u_short)port);

  const int ret = ::bind(socket->getFD(),
			 (struct sockaddr *) &server, sizeof(server));
  if (ret < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0); 
    }

  socket->setBind();

  return RV_SUCCESS;
}

// @doc
// @pred tcp_listen(Socket)
// @mode tcp_listen(+) is det
// @type tcp_listen(Integer)
// @description
// Corresponds to: listen(3N)
//
// Set the length of the sockets queue for incoming requests to 5.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_listen(Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);
  
  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (!socket->isListenAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }

  const int ret = listen(socket->getFD(), 5);
  if (ret < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  socket->setListen();

  return RV_SUCCESS;
}

//  @user
//  @pred tcp_accept(Socket, NewSocket, Port, IPAddress)
//  @type tcp_accept(Integer, Integer, Integer, IPAddress)
//  @mode tcp_accept(+, -, -, -, +) is semidet
//  @description
//  Corresponds to: accept(3N)
//  
//  An IPAddress is an integer or the atom 'inaddr_any'.
//  
//  Accept a connection to the given socket.
//  @internal
//  Implemented directly by pseudo-instruction.
//  @end internal
//  @end pred
//  @end user
Thread::ReturnValue
Thread::psi_tcp_accept(Object *& socket_arg,
		       Object *& new_socket_arg,
		       Object *& port_arg,
		       Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (!socket->isAcceptAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
  IS_READY_IO(socket, -1);
  struct sockaddr_in add;
  unsigned int length = sizeof(struct sockaddr_in);
  
  const int newsockfd = accept(socket->getFD(),
			       (struct sockaddr *) &add,
			       &length);
  if (newsockfd < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }
  
  Socket *newsocket = new Socket(0, 0, newsockfd);
  if (newsocket == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }
  
  socket->setAccepted(newsocket, newsockfd);
  new_socket_arg = heap.newNumber(sockm->OpenSocket(newsocket));
  port_arg = heap.newNumber(ntohs(add.sin_port));
  ip_address_arg = heap.newNumber(ntohl(add.sin_addr.s_addr));

  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_connect1'(Socket, Port, IPAddress)
// @mode '$tcp_connect1'(+, +, +)
// @type '$tcp_connect1'(Integer, Integer, IPAddress)
// @description
// Start off the connect() call. What will generally happen is that we'll
// get an all clear or EINPROGRESS return, both of which are (potentially)
// good news.
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_connect1(
		 Object *& socket_arg,
		 Object *& port_arg,
		 Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argP = heap.dereference(port_arg);
  Object* argA = heap.dereference(ip_address_arg);

  Socket *socket = NULL;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  u_short port = 0;
  DECODE_PORT_ARG(heap, argP, 2, port);

  u_long ip_address = 0;
  DECODE_IP_ADDRESS_ARG(heap, *atoms, argA, 3, ip_address);

  if (!socket->isConnectAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
  
  struct sockaddr_in add;
  
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = ip_address;
  add.sin_port = port;

  const int ret = connect(socket->getFD(),
			  (struct sockaddr *)&add, sizeof(add));

  if (ret == 0)
    {
      return RV_SUCCESS;
    }
  else if (errno == EINPROGRESS)
    {
      return RV_SUCCESS;
    }
  else
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }
}

// @internaldoc
// @pred '$tcp_connect2'(Socket)
// @mode '$tcp_connect2'(+, +)
// @type '$tcp_connect2'(Integer)
// @description
// Polls the socket to see if the earlier connect() has finally gone through.
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_connect2(Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  int fd = socket->getFD();
  
  fd_set fds;

  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  int result = select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);

  DEBUG_ASSERT(result && FD_ISSET(fd, &fds));
		

  socket->setConnected();

  return RV_SUCCESS;
}

// @doc
// @pred tcp_checkconn(Socket)
// @mode tcp_checkconn(+) is semidet
// @type tcp_checkconn(Integer)
// @description
// Succeeds if the socket is in a state that allows connection; fails otherwise.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_checkconn(Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  socket->setConnected();

  return RV_SUCCESS;
}

// @doc
// @pred tcp_close(Socket)
// @mode tcp_close(+) is det
// @type tcp_close(Integer)
// @description
// Corresponds to: close(2)
//
// Close the socket.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_close(
	      Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (socket->getIStream() != -1)
    {
      Stream* stream = iom->GetStream(socket->getIStream());
      stream->close();
      iom->CloseStream(socket->getIStream());
      socket->setIStream(-1);
    }
  if (socket->getOStream() != -1)
    {
      Stream* stream = iom->GetStream(socket->getOStream());
      stream->close();
      iom->CloseStream(socket->getOStream());
      socket->setOStream(-1);
    }

  socket->closeSocket();
  sockm->CloseSocket(argS->getNumber());

  delete socket;

  return RV_SUCCESS;
}

// @doc
// @pred tcp_getsockname(Socket, Port, IPAddress)
// @mode tcp_getsockname(+, -, -) is det
// @type tcp_getsockname(Integer, Integer, Integer)
// @description
// Corresponds to: getsockname(3N)
//
// Return the local port and IP address associated with the socket.
// @end pred
// @end doc 
Thread::ReturnValue
Thread::psi_tcp_getsockname(
		    Object *& socket_arg,
		    Object *& port_arg,
		    Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  sockaddr_in addr;
  unsigned int length = sizeof(struct sockaddr_in);

  if (getsockname(socket->getFD(),(struct sockaddr *)&addr,&length) < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  if (gethostname(io_buf, IO_BUF_LENGTH) < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  hostent *hp = gethostbyname(io_buf);
  if (hp == NULL)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  port_arg = heap.newNumber(ntohs(addr.sin_port));
  ip_address_arg = heap.newNumber(ntohl(*(int *)hp->h_addr_list[0]));

  return RV_SUCCESS;
}

// @doc
// @pred tcp_getpeername(Socket, Port, IPAddress)
// @mode tcp_getpeername(+, -, -) is det
// @type tcp_getpeername(Integer, Integer, Integer) 
// @description
// Corresponds to: getpeername(3N)
//
// Return the remote port and IP address associated with the socket.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_getpeername(
		    Object *& socket_arg,
		    Object *& port_arg,
		    Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  struct sockaddr_in addr;
  unsigned int length = sizeof(struct sockaddr_in);

  if (getpeername(socket->getFD(),(struct sockaddr *)&addr,&length) < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  port_arg = heap.newNumber(ntohs(addr.sin_port));

  ip_address_arg = heap.newNumber(ntohl(addr.sin_addr.s_addr));

  return RV_SUCCESS;
}

// @doc
// @pred tcp_host_to_ip_address(Name, IPAddress)
// @mode tcp_host_to_ip_address(+, -) is det
// @type tcp_host_to_ip_address(Atom, Integer)
// @description
// Corresponds to: nslookup(1N)
//
// Looks up the IP address of the given host.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_host_to_ip_address(Object *& host_arg,
				      Object *& ip_address_arg)
{
  Object* argH = heap.dereference(host_arg);

  if (argH->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argH->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  char hostname[1000];
  (void)strcpy(hostname, atoms->getAtomString(OBJECT_CAST(Atom*, argH)));
  if (strcmp(hostname, "localhost") == 0)
    {
      if (gethostname(hostname, 1000) != 0)
	{
	  PSI_ERROR_RETURN(EV_SYSTEM, 0);
	}
    }

  hostent *hp = gethostbyname(hostname);
  if (!hp)
    {
      struct in_addr in;
      in.s_addr = inet_addr(hostname);
      hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
    }
  endhostent();
  if (!hp)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

 ip_address_arg =  heap.newNumber(ntohl(*(int *)hp->h_addr_list[0]));

  return RV_SUCCESS;
}

// @doc
// @pred tcp_host_from_ip_address(Name, IPAddress)
// @mode tcp_host_from_ip_address(-, +) is det
// @type tcp_host_from_ip_address(Atom, Integer)
// @description
// Corresponds to: nslookup(1N)
//
// Looks up the host name for the machine with the supplied IP address.
// (Input ip address is in host byte order.)
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_host_from_ip_address(Object *& host_arg,
				     Object *& ip_address_arg)
{
  Object* argA = heap.dereference(ip_address_arg);

  u_long ip_address;
  DECODE_IP_ADDRESS_ARG(heap, *atoms, argA, 2, ip_address);
    
  struct hostent *hp =
    gethostbyaddr((char *)&ip_address, sizeof(ip_address), AF_INET);
  endhostent();
  if (!hp)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  host_arg = atoms->add(hp->h_name);

  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_service_to_proto_port'(Service, Protocol, Port)
// @mode '$tcp_service_to_proto_port'(+, -, -) is det
// @type '$tcp_service_to_proto_port'(Atom, Atom, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_to_proto_port(
			      Object *& service_arg,
			      Object *& proto_arg,
			      Object *& port_arg)
{
  Object* argS = heap.dereference(service_arg);

  if (argS->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argS->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  char * proto = NULL;

  servent *sp =
    getservbyname(atoms->getAtomString(OBJECT_CAST(Atom*, argS)), proto);
  (void) endservent();
  if (!sp)
    {
      return RV_FAIL;
    }
  
  port_arg = heap.newNumber(ntohs(sp->s_port));
  proto_arg = atoms->add(sp->s_proto);
  
  return RV_SUCCESS;
}
  
// @internaldoc
// @pred '$tcp_service_proto_to_port'(Service, Protocol, Port)
// @mode '$tcp_service_proto_to_port'(+, +, -) is det
// @type '$tcp_service_proto_to_port'(Atom, Atom, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_proto_to_port(
			       Object *& service_arg,
			       Object *& proto_arg,
			       Object *& port_arg)
{
  Object* argS = heap.dereference(service_arg);
  Object* argPr = heap.dereference(proto_arg);

  if (argS->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argS->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  if (argPr->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argPr->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *proto = atoms->getAtomString(argPr);

  servent *sp = getservbyname(atoms->getAtomString(argS), proto);
  (void) endservent();

  if (!sp)
    {
      return RV_FAIL;
    }
  
  //port_arg = heap.newNumber(sp->s_port);
  port_arg = heap.newNumber(ntohs(sp->s_port));

  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_service_from_proto port'(Service, Proto, Port)
// @mode '$tcp_service_from_proto_port'(-, -, +) is det
// @type '$tcp_service_from_proto_port'(Atom, Integer, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_from_proto_port(
				 Object *& service_arg,
				 Object *& proto_arg,
				 Object *& port_arg)
{
  Object* argPr = heap.dereference(proto_arg);
  Object* argPo = heap.dereference(port_arg);
  
  u_short port;
  DECODE_PORT_ARG(heap, argPo, 3, port);
  if (argPr->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argPr->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *proto = atoms->getAtomString(OBJECT_CAST(Atom*, argPr));
  
  servent *sp = getservbyport(port, proto);
  (void) endservent();
  if (!sp)
    {
      return RV_FAIL;
    }

  service_arg = atoms->add(sp->s_name);

  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_service_from_proto_port'(Service, Proto, Port)
// @mode '$tcp_service_from_proto_port'(-, -, +) is det
// @type '$tcp_service_from_proto_port'(Atom, Integer, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_proto_from_port(
				 Object *& service_arg,
				 Object *& proto_arg,
				 Object *& port_arg)
{
  Object* argPo = heap.dereference(port_arg);

  u_short port;
  DECODE_PORT_ARG(heap, argPo, 3, port);
//  if (argPo->isVariable())
//    {
//      PSI_ERROR_RETURN(EV_INST, 2);
//    }
//  if (!argPo->isNumber())
//    {
//      PSI_ERROR_RETURN(EV_TYPE, 2);
//    }

  const char *proto = NULL;

//  const u_short port = (u_short)argPo->getNumber();
  servent *sp = getservbyport(port, proto);
  (void) endservent();
  if (!sp)
    {
      return RV_FAIL;
    }

  service_arg = atoms->add(sp->s_name);
  proto_arg = atoms->add(sp->s_proto);
  
  return RV_SUCCESS;
}


// @doc
// @pred tcp_is_socket(Socket)
// @mode tcp_is_socket(+) is semidet
// @type tcp_is_socket(Integer)
// @description
// Succeeds if its argument is a valid socket descriptor; fails otherwise.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_is_socket(Object *& socket_arg)
{
  Socket *socket;
  const ErrorValue ev = decode_socket(heap, socket_arg->variableDereference(),
				      &socket);

  return ev == EV_NO_ERROR ? RV_SUCCESS : RV_FAIL;
}

