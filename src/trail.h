// trail.h - The various trails used by QuProlog.
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
// $Id: trail.h,v 1.10 2003/11/12 02:39:39 qp Exp $

#ifndef	TRAIL_H
#define	TRAIL_H

#include <iostream>

#include "area_offsets.h"
#include "objects.h"
#include "defs.h"
#include "stack_qp.h"
#include "dynamic_code.h"

//
// A trail for variable bindings.
//
class BindingTrail : public PrologStack <heapobject*>
{

private:

  virtual  const char *getAreaName(void) const {return("binding trail"); }

public:
  BindingTrail(word32 size, word32 boundary)
    : PrologStack <heapobject*> (size, boundary) {}

  //
  // Get the current trail position.
  //
  TrailLoc	getTop(void)	const	{ return(getTopOfStack()); }

  //
  // Trail a binding - trail pointer to variable.
  //
  void trail(heapobject* v)
    {
      DEBUG_ASSERT(reinterpret_cast<Object*>(v)->isAnyVariable());
      pushElement(v);
    }

  //
  // Roll back the trail to a specified position.  While rolling back,
  // all conditional bindings are reset.
  //
  void backtrackTo(const TrailLoc loc)
  {
    TrailLoc	current;
    for (current = getTop(); current > loc;)
      {
	current--;
	//
	// get address of (ob)var
	//
	heapobject* ptr = inspectEntry(current);
	DEBUG_ASSERT(ptr != NULL);
	//     
	// Reset (ob)var to unbound
	//
	*(ptr+1) = reinterpret_cast<heapobject>(ptr);
      }
    setTopOfStack(loc);
  }

  //
  // Given a segment of trail between start and the top, re-determine
  // whether the entry is needed or not.
  //
  void tidyUpTrail(TrailLoc start, const heapobject* beforeChoice)
  {
    TrailLoc	top, next;
    
    top = getTop();
    while (start < top)
      {
	if (inspectEntry(start) < beforeChoice)
	  {
	    start++;
	  }
	else
	  {
	    break;
	  }
      }
    for (next = start+1; next < top; next++)
      {
	if (inspectEntry(next) < beforeChoice)
	  {
	    //
	    // Keep the current entry.
	    // Copy the address.
	    //
	    *fetchAddr(start) = inspectEntry(next);
	    start++;
	  }
      }
    setTopOfStack(start);
  }

#ifdef DEBUG
  void printMe(AtomTable& atoms)
    {
      cerr << endl << "---- Trail --- " << endl;
      for (u_int i = 0; i < getTop(); i++)
	{
	  heapobject* ptr = getEntry(i);
	  reinterpret_cast<Object*>(ptr)->printMe_dispatch(atoms);
	  cerr << endl;
	}
    }
#endif // DEBUG

};

//
// Class for elements of UpdatableObjectTrail
//
class UpdatableObject
{
private:
  heapobject* addr;
  Object*     old_value;
  u_int       offset;

public:
  UpdatableObject(void):addr(NULL),old_value(NULL), offset(0) {}

  UpdatableObject(heapobject* a, Object* o, u_int off)
    :addr(a),old_value(o), offset(off) {}

  heapobject* getAddress(void) const { return(addr); }

  void setAddress(heapobject* a) { addr = a; }

  heapobject* getAddressAddr(void) 
    {return(reinterpret_cast<heapobject*>(&addr)); }

  Object* getOldValue(void) const {return(old_value); }

  void setOldValue(Object* o) { old_value = o; }

  heapobject* getOldVAddr(void) 
    {return(reinterpret_cast<heapobject*>(&old_value)); }

  u_int getOffset(void) const {return(offset); }

  void operator=(const UpdatableObject& a)
    { addr = a.addr; old_value = a.old_value; offset = a.offset; }

};

//
// A trail for updatable objects - var names, delays, distinctness. 
// Also used for IP's.
//
class UpdatableObjectTrail : public PrologStack <UpdatableObject>
{

private:
  char* areaName;
  virtual  const char *getAreaName(void) const 
    {return(areaName); }

public:
  UpdatableObjectTrail(word32 size, word32 boundary, char* name)
    : PrologStack <UpdatableObject> (size, boundary) {areaName = name;}

  //
  // Get the current trail position.
  //
  TrailLoc	getTop(void)	const	{ return(getTopOfStack()); }

  //
  // Trail an object assignment.
  //
  void trail(UpdatableObject& v)
    {
      pushElement(v);
    }

#ifdef DEBUG
  void printMe(AtomTable& atoms)
    {
      cerr << endl << "---- Trail --- " << endl;
      for (u_int i = 0; i < getTop(); i++)
	{
	  UpdatableObject* ptr = fetchAddr(i);
	  cerr << hex << "Address: " << (word32)(ptr->getAddress()) 
	       << dec << "Offset: " << ptr->getOffset() << endl;
	  cerr << "OldValue: ";
	  ptr->getOldValue()->printMe_dispatch(atoms);
	  cerr << endl;
	}
    }
#endif // DEBUG
	  
  //
  // Roll back the trail to a specified position.  While rolling back,
  // all conditional assignments are reset.
  //
  void backtrackTo(const TrailLoc loc)
  {
    TrailLoc	current;
    
    for (current = getTop(); current >loc; )
      {
	current--;
	//
	// get updatable object pointer
	//
	UpdatableObject* ptr = fetchAddr(current);
	DEBUG_ASSERT(ptr != NULL);
	if (ptr->getAddress() != NULL)
	  {
	    //     
	    // Reset object
	    //
	    *(ptr->getAddress() + ptr->getOffset()) 
	      = reinterpret_cast<heapobject>(ptr->getOldValue());
	  }
      }
    setTopOfStack(loc);
  }

  //
  // Given a segment of trail between start and the top, re-determine
  // whether the entry is needed or not.
  //
  void tidyUpTrail(TrailLoc start, Heap& heap)
  {
    TrailLoc	top, next;
    top = getTop();

    while (start < top)
      {
        UpdatableObject entry_obj = inspectEntry(start);
	heapobject* entry = entry_obj.getAddress();
	if ((entry == NULL) || entry < heap.getSavedTop() || entry >= heap.getTop())
	  {
            for (TrailLoc i = start+1; i < top; i++)
              {

		UpdatableObject i_entry_obj = inspectEntry(i);
                if ((entry == i_entry_obj.getAddress())
		    && (entry_obj.getOffset() == i_entry_obj.getOffset()))
                  {
                     fetchAddr(i)->setAddress(NULL);
                  }
              }
	    start++;
	  }
	else
	  {
	    break;
	  }
      }
    for (next = start+1; next < top; next++)
      {
        UpdatableObject entry_obj = inspectEntry(next);
	heapobject* entry = entry_obj.getAddress();
	if ((entry == NULL) || entry < heap.getSavedTop() || entry >= heap.getTop())
	  {
            for (TrailLoc i = next+1; i < top; i++)
              {
		UpdatableObject i_entry_obj = inspectEntry(i);
                if ((entry == i_entry_obj.getAddress())
		    && (entry_obj.getOffset() == i_entry_obj.getOffset()))
                  {
                     fetchAddr(i)->setAddress(NULL);
                  }
              }
	    //
	    // Keep the current entry.
	    // Copy the entry.
	    //
	    *fetchAddr(start) = inspectEntry(next);
	    start++;
	  }
      }
    setTopOfStack(start);
  }

};

//
// Class for elements of UpdatableTagTrail
//
class UpdatableTag
{
private:
  heapobject* addr;
  heapobject     old_value;

public:
  UpdatableTag(void):addr(NULL),old_value(0) {}

  UpdatableTag(heapobject* a, heapobject t):addr(a),old_value(t) {}

  heapobject* getAddress(void) const { return(addr); }

  void setAddress(heapobject* a) { addr = a; }

  heapobject* getAddressAddr(void) 
    { return(reinterpret_cast<heapobject*>(&addr)); }

  heapobject getOldValue(void) const {return(old_value); }

  void operator=(const UpdatableTag& a)
    { addr = a.addr; old_value = a.old_value; }

};

//
// A trail for tags.
//
class UpdatableTagTrail : public PrologStack <UpdatableTag>
{

private:

  virtual  const char *getAreaName(void) const 
    {return("updatable tag trail"); }

public:
  UpdatableTagTrail(word32 size, word32 boundary)
    : PrologStack <UpdatableTag> (size, boundary) {}

  //
  // Get the current trail position.
  //
  TrailLoc	getTop(void)	const	{ return(getTopOfStack()); }

  //
  // Trail a tag.
  //
  void trail(UpdatableTag& v)
    {
      pushElement(v);
    }

  //
  // Roll back the trail to a specified position.  While rolling back,
  // all tags are reset.
  //
  void backtrackTo(const TrailLoc loc)
  {
    TrailLoc	current;
    
    for (current = getTop(); current > loc; )
      {
	current--;
	//
	// get updatable tag pointer
	//
	UpdatableTag* ptr = fetchAddr(current);
	DEBUG_ASSERT(ptr != NULL);
	if (ptr->getAddress() != NULL)
	  {
	    //     
	    // Reset tag
	    //
	    *(ptr->getAddress()) = ptr->getOldValue();
	  }
      }
    setTopOfStack(loc);
  }

  //
  // Given a segment of trail between start and the top, re-determine
  // whether the entry is needed or not.
  //
  void tidyUpTrail(TrailLoc start, Heap& heap)
  {
    TrailLoc	top, next;
    
    top = getTop();
    while (start < top)
      {
	heapobject* entry = inspectEntry(start).getAddress();
	if (entry < heap.getSavedTop() || entry >= heap.getTop())
	  {
	    start++;
	  }
	else
	  {
	    break;
	  }
      }
    for (next = start+1; next < top; next++)
      {
	heapobject* entry = inspectEntry(next).getAddress();
	if (entry < heap.getSavedTop() || entry >= heap.getTop())
	  {
	    //
	    // Keep the current entry.
	    // Copy the entry.
	    //
	    *fetchAddr(start) = inspectEntry(next);
	    start++;
	  }
      }
    setTopOfStack(start);
  }


#ifdef DEBUG
  void printMe(AtomTable& atoms)
    {
      cerr << endl << "---- Trail --- " << endl;
      for (u_int i = 0; i < getTop(); i++)
	{
	  UpdatableTag t = getEntry(i);
	  cerr << "old tag = " << t.getOldValue();
	  if (t.getAddress() == NULL)
	    {
	      cerr << endl;
	    }
	  else
	    {
	      cerr <<  " new value = " << *(t.getAddress()) << endl;
	    }  
	  reinterpret_cast<Object*>(t.getAddress())->printMe_dispatch(atoms);
	  cerr << endl;
	}
    }
#endif // DEBUG
};

// A trail for reference counts

class DynamicPredicate;

enum TypeOfEntry {REF_EMPTY, REF_CLAUSE, REF_PRED, REF_ENDCL};
class RefObject
{
private:
  TypeOfEntry entryType; 
  word32 pred;

public:

  RefObject(void):entryType(REF_CLAUSE),pred(0) {}

  RefObject(TypeOfEntry a, DynamicPredicate* p) 
    : entryType(a),pred((word32)p) {}

  RefObject(TypeOfEntry a, TrailLoc p) 
    : entryType(a),pred((word32)p) {}

  bool isAlt(void) { return (entryType == REF_PRED); }

  bool isEndLink(void) { return (entryType == REF_ENDCL); }

  bool isClause(void) { return (entryType == REF_CLAUSE); }

  bool isEmpty(void) { return (entryType == REF_EMPTY); }

  void makeEmpty(void) { entryType = REF_EMPTY; }

  DynamicPredicate* getPred(void) 
  {
    DEBUG_ASSERT(entryType != REF_EMPTY);
    DEBUG_ASSERT(entryType != REF_ENDCL);
    return reinterpret_cast<DynamicPredicate*>(pred); 
  }

  TrailLoc getLink(void)
  {
    DEBUG_ASSERT(entryType == REF_ENDCL);
    return (TrailLoc)pred;
  }

  void operator=(const RefObject& a)
  {
    entryType = a.entryType;
    pred = a.pred;
  }

};

class RefTrail : public PrologStack <RefObject>
{
private:
  virtual  const char *getAreaName(void) const 
    {return("reference count trail"); }

public:
  RefTrail(word32 size, word32 boundary)
    : PrologStack <RefObject> (size, boundary) {}

  TrailLoc	getTop(void)	const	{ return(getTopOfStack()); }
  
  void trail(RefObject& r)
    {
      pushElement(r);
    }
  
  void backtrackTo(const TrailLoc loc)
  {
    TrailLoc	current;
    
    for (current = getTop(); current > loc; )
      {
	current--;
	RefObject* ptr = fetchAddr(current);
	DEBUG_ASSERT(ptr != NULL);
	if (ptr->isEndLink())
	  {
	    continue;
	  }
	DynamicPredicate* pred = ptr->getPred();
	DEBUG_ASSERT(pred != NULL);
	pred->release();
      }
    setTopOfStack(loc);
  }

  void tidyUpTrail(const TrailLoc loc, const ChoiceLoc currCP)
  {
    #if 0
    cerr << "tidyUpTrail loc = " << (word32)loc <<  " Choice = " << (word32)currCP << endl;
  for (TrailLoc i = 0; i < getTop(); i++)
    {
      cerr << (word32)i << " : ";
      RefObject* ptr = fetchAddr(i);
      if (ptr->isEmpty())
	{
	  cerr << "Empty" << endl;
	}
      else if (ptr->isAlt())
	{
	  cerr << "Alt - pred = " << (word32)(ptr->getPred()) << endl;
	}
      else if (ptr->isClause())
	{
	  cerr << "Cla - pred = " << (word32)(ptr->getPred()) << endl;
	}
      else
	{
	  cerr << "Link - ent = " << (word32)(ptr->getLink()) << endl;
	}
    }
  #endif

    if (loc == getTop())
      {
	return;
      }
    TrailLoc top = getTop();
    RefObject* ptr;
    while (top > loc)
      {
	top--;
	ptr = fetchAddr(top);
	DEBUG_ASSERT(ptr != NULL);
	if (ptr->isEmpty())
	  {
	    continue;
	  }
	if (ptr->isAlt())
	  {
	    DynamicPredicate* pred = ptr->getPred();
	    DEBUG_ASSERT(pred != NULL);
	    pred->release();
	  }
	else if (ptr->isClause())
	  {
	    break;
	  }
	else
	  {
	    TrailLoc l = ptr->getLink();
	    if (l < loc)
	      {
		top++;
		break;
	      }
	    RefObject* lptr = fetchAddr(l);
	    DynamicPredicate* pred = lptr->getPred();
	    DEBUG_ASSERT(pred != NULL);
	    pred->release();
	    lptr->makeEmpty();
	  }
      }

    if (ptr->isClause())
      {
	if (top == loc)
	  {
	    top++;
	  }
	else
	  {
	    if(top > 0)
	      {
		RefObject* aptr = fetchAddr(top-1);
		DEBUG_ASSERT(aptr != NULL);
		if (aptr->isAlt())
		  {
		    DynamicPredicate* apred = aptr->getPred();
		    apred->release();
		    *fetchAddr(top-1) = inspectEntry(top);
		  }
		else
		  {
		    top++;
		  }
	      }
	    else
	      {
		top++;
	      }
	  }
      }
    setTopOfStack(top);
  }
	    
  void tryDecRef(const TrailLoc loc);
  
};



#endif // TRAIL_H








