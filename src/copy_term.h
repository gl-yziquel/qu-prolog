// copy_term.h - Copy a term from one heap to another.
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
// $Id: copy_term.h,v 1.3 2002/11/13 04:04:14 qp Exp $

#ifndef	COPY_TERM_H
#define	COPY_TERM_H


private:
class VarRec
{
private:
  heapobject* source_loc;
  heapobject* target_loc;
public:
  VarRec(heapobject* sl, heapobject* tl) : source_loc(sl), target_loc(tl)
    { }

  heapobject* sourceLoc(void) const { return source_loc; }
  heapobject* targetLoc(void) const { return target_loc; }

  bool operator==(const VarRec& v) const
  {
    return sourceLoc() == v.sourceLoc();
  }

  void operator=(const VarRec& v)
    {
      source_loc = v.sourceLoc();
      target_loc = v.targetLoc();
    }
};


Object* copy_var(Object*, Heap&, list<VarRec *>&);

Object* copy_object_variable(Object* source_object_variable, 
			     Heap& target_heap,
			     list<VarRec *>& object_variable_rec_list);


Object* copy_subblock(Object* source_substitution,
		      Heap& target_heap,
		      list<VarRec *>& var_rec_list,
		      list<VarRec *>& object_variable_rec_list);

Object* copy_share_subblock(Object* source_substitution,
			    Heap& target_heap,
			    const heapobject* low, const heapobject* high);

Object* copy_term(Object* source_term, Heap& target_heap,
		  list<VarRec *>& var_rec_list,
		  list<VarRec *>& object_variable_rec_list);

Object* copy_share_term(Object* source_term, Heap& target_heap,
			const heapobject* low, const heapobject* high);

public:
Object* copyTerm(Object* source_term, Heap& target_heap);

Object* copyShareTerm(Object* source_term, Heap& target_heap, 
		      const heapobject* low, const heapobject* high);

#endif	// COPY_TERM_H











