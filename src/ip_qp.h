// ip_qp.h - Routines for manipulating implicit parameters, which must be an atom.
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: ip_qp.h,v 1.2 2001/09/24 00:38:33 qp Exp $

#ifndef	IP_QP_H
#define	IP_QP_H

public:
//
// psi_ip_set(key, value)
// Assign a value for an implicit parameter.
// mode(in,in)
//
ReturnValue psi_ip_set(Object *& , Object *& );

// psi_ip_setA(key, hashVal, value)
// Assign a value for an array implicit parameter.
// mode(in,in,in)
//
ReturnValue psi_ip_setA(Object *& , Object *& , Object *& );

//
// psi_ip_lookup(key, value)
// Look up the value of an implicit parameter.
// mode(in,out)
//
ReturnValue	psi_ip_lookup(Object *& , Object *& );

// psi_ip_lookupA(key, hashVal, value)
// Lookup a value for an array implicit parameter.
// mode(in,in,out)
//
ReturnValue psi_ip_lookupA(Object *& , Object *& , Object *& );

// psi_ip_get_array_keys(name, values)
// return all the keys for the IP array name
// mode(in, out)
//
ReturnValue psi_ip_get_array_entries(Object *&, Object *&);

// psi_ip_array_clear(key)
// Clear (initilize) an IP array.
// mode(in)
//
ReturnValue psi_ip_array_clear(Object *& );

// psi_ip_array_init(key, size)
// Initilize an IP array to size.
// mode(in, in)
//
ReturnValue psi_ip_array_init(Object *& , Object *&);


//
// psi_ip_lookup_default(key, value,default)
// Look up the value of an implicit parameter.
// mode(in,out,in)
//
ReturnValue psi_ip_lookup_default(Object *&, Object *&, Object *&);

// psi_ip_lookupA_default(key, hash_val, value, default)
// Lookup a value for an array implicit parameter.
// mode(in,in,out, in)
//
ReturnValue psi_ip_lookupA_default(Object *&, Object *&,  Object *&, Object *&);
#endif	// IP_QP_H

