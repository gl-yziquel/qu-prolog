// foreign_interface.h - A class for connectiong foreign functions to 
// thread methods.
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: foreign_interface.h,v 1.2 2006/02/14 02:40:09 qp Exp $

#ifndef FOREIGN_INTERFACE_H
#define FOREIGN_INTERFACE_H

#include "atom_table.h"
//#include "thread_qp.h"

class Object;
class Structure;
class Thread;

extern AtomTable *atoms;

class ForeignInterfaceBase 
{
 public:
  virtual ~ForeignInterfaceBase() {}
  virtual Object* getXReg(int i) = 0;
  virtual Object* makeAtom(const char* s) = 0;
  virtual Object* makeInteger(const long i) = 0;
  virtual Object* makeDouble(const double d) = 0;
  virtual Structure* makeStructure(const int n) = 0;
  virtual Object* makeCons(Object* h, Object* t) = 0;
  virtual char* getAtomString(Object* a) = 0;
  virtual bool unify(Object* o1, Object* o2) = 0;
};

class ForeignInterface : public ForeignInterfaceBase
{
 public:
  explicit ForeignInterface(Thread* th) : threadptr(th) {}
    
    Object* getXReg(int i); 
    Object* makeAtom(const char* s); 
    Object* makeInteger(const long i); 
    Object* makeDouble(const double d);
    Structure* makeStructure(const int n);
    Object* makeCons(Object* h, Object* t);

    char* getAtomString(Object* a);
    bool unify(Object* o1, Object* o2);
      
    private:
      Thread* threadptr;
 };

#endif //FOREIGN_INTERFACE_H


