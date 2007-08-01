//
// tcp_escapes.h - escape functions for supporting TCP communication
// within QP.
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

#ifndef TCP_ESCAPES_H
#define TCP_ESCAPES_H

public:
//
// @internaldoc
// @pred '$open_socket_stream'(Socket, IOMode, Stream)
// @mode '$tcp_connect1'(+, +, -)
// @type '$tcp_connect1'(Integer, Integer, StreamID)
// @description
// Open a stream for either reading or writing on the socket.
// @end pred
// @end internaldoc

ReturnValue psi_open_socket_stream(Object *&, Object *&, Object *&);

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
// @end pred
// @end doc
ReturnValue psi_tcp_socket(Object *&, Object *&, Object *&);

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
//  'so_broadcast'	= permit sending of broadcast msgs (not supported)
//  'so_oobinline'	= leave received OOB data in line
//  'so_sndbuf'		= size of send buffer
//  'so_rcvbuf'		= size of receive buffer
//  'so_sndtimeo'	= send timeout
//  'so_rcvtimeo'	= receive timeout
//
// For now we only support the SOL_SOCKET level
// @end pred
// @end doc
ReturnValue psi_tcp_setsockopt(Object *&, Object *&, Object *&);

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
ReturnValue psi_tcp_getsockopt(Object *&, Object *&, Object *&);

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
ReturnValue psi_tcp_bind(Object *&, Object *&, Object *&);

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
ReturnValue psi_tcp_listen(Object *&);

// @internaldoc
// @pred '$tcp_accept'(Socket, NewSocket, Port, IPAddress)
// @mode '$tcp_accept'(+, -, -, -) is semidet
// @type '$tcp_accept'(Integer, Integer, Port, IPAddress)
// @desciption
// Accept a connection from the new socket.
// @end pred
// @end internaldoc
ReturnValue psi_tcp_accept(Object *&, Object *&, Object *&, Object *&);

// @internaldoc
// @pred '$tcp_connect1'(Socket, Port, IPAddress)
// @mode '$tcp_connect1'(+, +, +)
// @type '$tcp_connect1'(Integer, Integer, IPAddress)
// @description
// Start off the connect() call. What will generally happen is that well
// get an all clear or EINPROGRESS return, both of which are (potentially)
// good news.
// @end pred
// @end internaldoc
ReturnValue psi_tcp_connect1(Object *&, Object *&, Object *&);

// @internaldoc
// @pred '$tcp_connect2'(Socket)
// @mode '$tcp_connect2'(+)
// @type '$tcp_connect2'(Integer)
// @description
// Polls the socket to see if the earlier connect() has finally gone through.
// @end pred
// @end internaldoc
ReturnValue psi_tcp_connect2(Object *&);

// @doc
// @pred tcp_checkconn(Socket)
// @mode tcp_checkconn(+) is semidet
// @type tcp_checkconn(Integer)
// @description
// Succeeds if the socket is in a state that allows connection; fails otherwise.
// @end pred
// @end doc
ReturnValue psi_tcp_checkconn(Object *&);

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
ReturnValue psi_tcp_close(Object *&);

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
ReturnValue psi_tcp_getsockname(Object *&, Object *&, Object *&);

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
ReturnValue psi_tcp_getpeername(Object *&, Object *&, Object *&);


// @doc
// @pred tcp_local_host(Name, IPAddress)
// @mode tcp_local_host(-, -) is det
// @type tcp_local_host(Atom, Integer)
// @description
// Corresponds to: nslookup(1M)
//
// Return the name and IP address of the local host.
// @end pred
// @end doc
ReturnValue psi_tcp_local_host(void);

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
ReturnValue psi_tcp_host_to_ip_address(Object *&, Object *&);

// @doc
// @pred tcp_host_from_ip_address(Name, IPAddress)
// @mode tcp_host_from_ip_address(-, +) is det
// @type tcp_host_from_ip_address(Atom, Integer)
// @description
// Corresponds to: nslookup(1N)
//
// Looks up the host name for the machine with the supplied IP address.
// @end pred
// @end doc
ReturnValue psi_tcp_host_from_ip_address(Object *&, Object *&);

// @internaldoc
// @pred '$tcp_service_to_proto_port'(Service, Protocol, Port)
// @mode '$tcp_service_to_proto_port'(+, -, -) is det
// @type '$tcp_service_to_proto_port'(Atom, Atom, Integer)
// @end pred
// @end internaldoc
ReturnValue psi_tcp_service_to_proto_port(Object *&,Object *&,Object *&);

// @internaldoc
// @pred '$tcp_service_proto_to_port'(Service, Protocol, Port)
// @mode '$tcp_service_proto_to_port'(+, +, -) is det
// @type '$tcp_service_proto_to_port'(Atom, Atom, Integer)
// @end pred
// @end internaldoc
ReturnValue psi_tcp_service_proto_to_port(Object *&,Object *&,Object *&);

// @internaldoc
// @pred '$tcp_service_from_proto port'(Service, Proto, Port)
// @mode '$tcp_service_from_proto_port'(-, -, +) is det
// @type '$tcp_service_from_proto_port'(Atom, Integer, Integer)
// @end pred
// @end internaldoc
ReturnValue psi_tcp_service_from_proto_port(Object *&,Object *&,Object *&);

// @internaldoc
// @pred '$tcp_service_from_proto_port'(Service, Proto, Port)
// @mode '$tcp_service_from_proto_port'(-, +, +) is det
// @type '$tcp_service_from_proto_port'(Atom, Integer, Integer)
// @end pred
// @end internaldoc
ReturnValue psi_tcp_service_proto_from_port(Object *&,Object *&,Object *&);


// @doc
// @pred tcp_is_socket(Socket)
// @mode tcp_is_socket(+) is semidet
// @type tcp_is_socket(Integer)
// @description
// Succeeds if its argument is a valid socket descriptor; fails otherwise.
// @end pred
// @end doc
ReturnValue psi_tcp_is_socket(Object *&);


ReturnValue psi_select(Object *&, Object *&);


ReturnValue psi_socket_fd(Object *&, Object *&);

#endif	// TCP_ESCAPES_H
