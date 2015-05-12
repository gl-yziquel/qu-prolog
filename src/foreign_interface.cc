// foreign_interface.cc - A class for connectiong foreign functions to 
// thread methods.
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
// $Id: foreign_interface.cc,v 1.2 2006/02/14 02:40:09 qp Exp $

#include "thread_qp.h"
#include "pedro_env.h"

//class PedroMessage;

Object* 
ForeignInterface::getXReg(int i) 
{ return threadptr->XRegs()[i]->variableDereference(); }

Object* 
ForeignInterface::makeAtom(const char* s)
{return atoms->add(s); }

Object* 
ForeignInterface::makeInteger(const long i) 
{ return threadptr->TheHeap().newInteger(i); }

Object* 
ForeignInterface::makeString(const char * s) 
{ return threadptr->TheHeap().newStringObject(s); }

Object* 
ForeignInterface::makeDouble(const double d)
{ return threadptr->TheHeap().newDouble(d); }

Structure* 
ForeignInterface::makeStructure(const int n)
{ return  threadptr->TheHeap().newStructure(n); }

Object* 
ForeignInterface::makeCons(Object* h, Object* t)
{ return  threadptr->TheHeap().newCons(h, t); }

char*
ForeignInterface::getAtomString(Object* a)
{ return OBJECT_CAST(Atom*, a)->getName(); }

char*
ForeignInterface::getString(Object* a)
{ return OBJECT_CAST(StringObject*, a)->getChars(); }

bool 
ForeignInterface::unify(Object* o1, Object* o2)
{ return threadptr->unify(o1 , o2); }
      
bool 
ForeignInterface::push_message(const char * msg)
{  threadptr->MessageQueue().push_back(new PedroMessage(msg)); 
  return true;
}
      
