// prolog_value.h - Define the class for holding substitution and term as
//		    a pair.
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
// $Id: prolog_value.h,v 1.4 2006/03/30 22:50:31 qp Exp $

#ifndef	PROLOG_VALUE_H
#define	PROLOG_VALUE_H

#include "defs.h"
#include "debug.h"
#include "objects.h"

class PrologValue
{
 private:
  Object *sub;		// List of substitutions
  Object *term;		// The term

 public:
  PrologValue(void) : sub(AtomTable::nil), term(NULL) { }
    PrologValue(Object *t)
      {
	if (t->isSubstitution())
	  {
	    Substitution *s = OBJECT_CAST(Substitution*, t);
	    sub = s->getSubstitutionBlockList();
	    term = s->getTerm();
	    assert(sub->isLegalSub());
	  }
	else
	  {
	    sub = AtomTable::nil;
	    term = t;
	  }
      }
    PrologValue(Object *s, Object *t)
      : sub(s), term(t)
      {
	assert(s->isLegalSub());
      }
  
      Object *getSubstitutionBlockList(void) { return sub; }
      Object *getTerm(void) { return term; }
      void setTerm(Object *t)
      {
	term = t;
      }

      Object **getSubstitutionBlockListAddress(void) 
	{ 
	  return &sub;
	}

      void setSubstitutionBlockList(Object *list)
      {
	assert(list->isLegalSub());

	sub = list;
      }

  
};

#endif	// PROLOG_VALUE_H











