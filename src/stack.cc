// stack.cc - Fundamental stack arrangement.
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: stack.cc,v 1.6 2005/03/08 00:35:14 qp Exp $

#ifndef STACK_CC
#define STACK_CC

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "errors.h"
#include "int.h"
#include "stack_qp.h"

template <class StoredType>
PrologStack<StoredType>::~PrologStack(void)
{
        top = 0;
}

//
// Write the stack to a stream.
//
template <class StoredType>
void
PrologStack<StoredType>::saveStack(ostream& ostrm, const u_long magic) const
{
  this->saveArea(ostrm, magic, 0, top);
  //
  // Write the top of stack.
  //
  IntSave<StackLoc>(ostrm, top);
}

//
// Load the stack from a stream.
//
template <class StoredType>
void
PrologStack<StoredType>::loadStack(istream& istrm)
{
  this->loadArea(istrm, 0);
  //
  // Read the top of stack.
  //
  top = IntLoad<StackLoc>(istrm);
}

#endif	// STACK_CC
