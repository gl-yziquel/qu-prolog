// bind.h - Qu-Prolog bindings. 
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
// $Id: bind.h,v 1.2 2002/03/24 05:58:30 qp Exp $

//#include "thread.h"
//#include "trail.h"

#ifndef BIND_H
#define BIND_H

public:

//
// Bind two variables based on age.
//
void bindVariables(Variable *, Variable *);

//
// Bind two object variables based on age.
//
void bindObjectVariables(ObjectVariable *, ObjectVariable *);

//
// Some thread methods involving trailing.
//

inline void bindAndTrail(Object* var, Object* value)
{
  DEBUG_ASSERT(var != NULL);
  DEBUG_ASSERT(value != NULL);
  DEBUG_ASSERT(var->isAnyVariable());
  //
  // Trail only if var is before saved top
  //

  if (reinterpret_cast<heapobject*>(var) < heap.getSavedTop() &&
      reinterpret_cast<heapobject*>(var) >= heap.getBase())
    {
      bindingTrail.trail(reinterpret_cast<heapobject*>(var));
    }
  *(var->storage()) = 
    reinterpret_cast<heapobject>(value); 
}

inline void updateAndTrailObject(heapobject* ptr, Object* value, u_int offset)
{
  DEBUG_ASSERT(ptr != NULL);
  DEBUG_ASSERT(value != NULL);
  //
  // Don't trail only if ptr is after saved top on the heap
  //
  if (ptr < heap.getSavedTop() || ptr >= heap.getTop())
    {
      UpdatableObject t(ptr, reinterpret_cast<Object*>(*(ptr+offset)), offset);
      objectTrail.trail(t);
    }
  *(ptr+offset) = reinterpret_cast<heapobject>(value); 
}

//
// Update and trail an implicit parameter entry
//
inline void Thread::updateAndTrailIP(heapobject* ptr, Object* value,
                                     u_int offset = 0)
{
  DEBUG_ASSERT(ptr != NULL);
  DEBUG_ASSERT(value != NULL);
  //
  // Don't trail only if ptr is after saved top on the heap
  //
  if (ptr < heap.getSavedTop() || ptr >= heap.getTop())
    {
      UpdatableObject t(ptr, reinterpret_cast<Object*>(*(ptr+offset)), offset);
      ipTrail.trail(t);
    }
  *(ptr+offset) = reinterpret_cast<heapobject>(value); 
}

inline void trailTag(Object* o)
{
  DEBUG_ASSERT(o != NULL);
  //
  // Don't trail only if o is after saved top on the heap
  //
  if (reinterpret_cast<heapobject*>(o) < heap.getSavedTop() ||
      reinterpret_cast<heapobject*>(o) >= heap.getTop())
    {
      UpdatableTag t(reinterpret_cast<heapobject*>(o), 
		     *(reinterpret_cast<heapobject*>(o)));
      tagTrail.trail(t);
    }
}

//
// var is an unbound variable. Bind var to object.
// Assumes var is dereferenced.
//
inline void bind(Variable *var , Object *object)
{
  DEBUG_ASSERT(var == var->variableDereference());
  
  //
  // Wake up any delayed problems associated with cell1.
  //
  
  if (var->getDelays()->isCons())
    {
      wakeUpDelayedProblems(var);
    }
  bindAndTrail(var, object);
}

//
// If the variable does not have extra info then
// create a new variable (with extra info) that has
// the same tags as the given variable and bind the given
// var to the new var.
//
inline Variable* addExtraInfo(Variable* oldvar)
{
  DEBUG_ASSERT(oldvar == oldvar->variableDereference());
  if (!oldvar->hasExtraInfo())
    {
      Variable* newvar = heap.newVariable(true);
      newvar->copyTag(oldvar);
      bind(oldvar, newvar);
      return newvar;
    }
  else
    {
      return oldvar;
    }
}

#endif  // BIND_H







