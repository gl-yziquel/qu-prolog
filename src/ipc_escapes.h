// ipc_escapes.h - Interprocess communication.
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
// $Id: ipc_escapes.h,v 1.3 2003/10/05 04:50:46 qp Exp $

#ifndef	IPC_ESCAPES_H
#define	IPC_ESCAPES_H

public:


//
// ipc_make_iterator(reference_out)
//
// Create an iterator for use with ipc_first and ipc_next
//
// mode(out)
//
//
ReturnValue psi_make_iterator(Object *&);

// ipc_first(reference_in, timeout, reference_out)
//
// Get the reference to the first message on the thread's ipc queue.
//
// mode(in, in, out)
//
ReturnValue psi_ipc_first(Object *&, Object *&, Object *&);

//
// ipc_next(timeout, reference-in, reference-out)
//
// Get the reference to the next message off the thread's ipc queue.
//
// mode(in, in, out)
//
ReturnValue psi_ipc_next(Object *&, Object *&, Object *&);

//
// ipc_get_message(message, reference, from-address, remember-names)
//
// Lookup and decode the fields of a message given a reference.
//
// mode(out, in, out, in)
//
ReturnValue psi_ipc_get_message(Object *&, Object *&, Object *&, Object *&);

//
// ipc_commit(reference)
//
// Commit to receiving a message.
//
// mode(in)
//
ReturnValue psi_ipc_commit(Object *&);


//
// Broadcast message to all current local threads
// mode(in)
//
ReturnValue psi_broadcast(Object *&);

#endif	// IPC_ESCAPES_H





