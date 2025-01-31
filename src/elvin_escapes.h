// elvin_escapes.h - Elvin escapes
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
// $Id: elvin_escapes.h,v 1.2 2006/01/31 23:17:50 qp Exp $

#ifndef	ELVIN_ESCAPES_H
#define	ELVIN_ESCAPES_H

public:

//
// psi_elvin_connect(server)
//
// Connect to the elvin server
//
// mode(in)
//
ReturnValue psi_elvin_connect(Object *&);

//
// psi_elvin_disconnect
// Disconnect from Elvin
//
ReturnValue psi_elvin_disconnect(void);

//
// psi_elvin_add_subscription(subscription)
//
// Add an Elvin subscription
//
// mode(in)
//
ReturnValue psi_elvin_add_subscription(Object *&);

//
// psi_elvin_add_notification(notification)
//
// Add an Elvin notification
//
// mode(in)
//
ReturnValue psi_elvin_add_notification(Object *&);

//
// psi_elvin_subscriptions(subscriptions)
//
// Get the current Elvin subscriptions for this thread.
//
// mode(out)
//
ReturnValue psi_elvin_subscriptions(Object *&);

//
// psi_elvin_delete_subscription(subscription)
//
// Delete an Elvin subscription
//
// mode(in)
//
ReturnValue psi_elvin_delete_subscription(Object *&);

#if 0
//
// psi_elvin_makeID(ID)
//
// Make a unique ID for use in Elvin notifications
//
// mode(out)
//
ReturnValue psi_elvin_makeID(Object *&);
#endif

#endif	// ELVIN_ESCAPES_H





