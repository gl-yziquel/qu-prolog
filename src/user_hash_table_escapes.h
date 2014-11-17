// user_hash_table_escapes.h - Interface to user hash table.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: user_hash_table_escapes.h,v 1.1 2006/01/31 23:19:10 qp Exp $

#ifndef USER_HT_ESCAPES_H
#define USER_HT_ESCAPES_H

public:

//
// psi_user_ht_insert(Fst, Snd, Data)
// Insert Data into the user hash table indexed by Fst and Snd
//
// mode(in,in,in)

ReturnValue psi_user_ht_insert(Object *&, Object *&, Object *&);


//
// psi_user_ht_lookup(Fst, Snd, Data)
// Lookup Data in the user hash table indexed by Fst and Snd
//
// mode(in,in,out)

ReturnValue psi_user_ht_lookup(Object *&, Object *&, Object *&);

//
// psi_user_ht_remove(Fst, Snd)
// Remove entry in the user hash table indexed by Fst and Snd
//
// mode(in,in)

ReturnValue psi_user_ht_remove(Object *&, Object *&);

//
// psi_user_ht_search(Fst, Snd, Data)
// Collect together all entries in the hash table that match
// Fst and Snd. Data is a list of elements of the form '$'(F,S,T)
//
// mode(in,in,out)

ReturnValue psi_user_ht_search(Object *&, Object *&, Object *&);


#endif  // USER_HT_ESCAPES_H
