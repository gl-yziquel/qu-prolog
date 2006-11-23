// heap_qp.h
//
// A representation of the heap (or global stack) for the Qu-Prolog
// Abstract Machine (QuAM).
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
// $Id: heap_qp.h,v 1.9 2006/02/05 22:14:55 qp Exp $

#ifndef HEAP_QP_H
#define HEAP_QP_H

#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>

#include <vector>
#include <list>

#include "area_offsets.h"
#include "atom_table.h"      
#include "compiler_support.h"      

#include "defs.h" // Qu-Prolog data type definitions &c.
#include "debug.h" // Qu-Prolog debugging facilities
#include "errors.h" // Qu-Prolog error handling
#include "foreign_interface.h"

#include "objects.h" // What's going to get created on the heap

#include "error_value.h"
#ifndef WIN32
#include "icm.h"
#endif
#include "io_qp.h"
#include "name_table.h"
#include "prolog_value.h"
#include "thread_status.h"
#include "truth3.h"

enum BoundVarState { MISMATCH, DELAY, MATCH };



//
// The maximum possible arity of a structure in the heap
// (NB. These are encoding-imposed limits, not arbitary ones, and are
// included merely for convenience and to avoid magic numbers)
//
static const u_long MaxArity = 0x008FFFFF; // 2**23 - 1
static const u_long MaxSubstBlock = 0x00008FFF; // 2**15 - 1

//////////////////////////////////////////////////////////////////////
// The Heap class specification

class Heap
{
private:
  heapobject *top;       // Where the top of the heap is
  heapobject *next;      // Where the next heapobject will go
  heapobject *highwater; // The high water mark of the heap
  heapobject *data;      // The heap proper (ie. an array of heapobjects)
  heapobject *savedTop;   // Saved top for backtracking
  heapobject *gcMark;    // The point at which to trigger garbage collection
  char *heapname;        // The name of the heap
  bool doGC;             // does garbage collection happen for this heap

public:
  //
  // Constructor and destructor
  //
  inline Heap(char *name, u_long size, bool GC = false);
  inline ~Heap(void);

private:
  // Allocate enough space for a given number of heap objects
  inline heapobject *allocateHeapSpace(size_t numHeapObjs);
  void outOfSpace(void);

  // Return the name of the area (for debugging purposes)
  inline char *getAreaName(void) const;

public:
  //
  // Is it time for garbage collection?
  //
  inline bool doGarbageCollection(void)
    { return (doGC && (next > gcMark)); }
  //
  // Is the pointer a heap pointer
  //
  inline bool isHeapPtr(heapobject* ptr) {return (ptr >= data && ptr < top); }

  inline bool isActive(heapobject* ptr)
    { return (!isHeapPtr(ptr) || ptr < next); }

  //
  // Allocated size
  //
  inline word32 allocatedSize(void) {return static_cast<word32>(top - data); }
  //
  // Max usage
  //
  inline word32 maxUsage(void) {return static_cast<word32>(highwater - data); }
  //
  // get the heap base for copy share term
  //
  inline heapobject* getBase(void);
  //
  // get the top of heap
  //
  inline heapobject* getTop(void);
  //
  // get the saved top
  //
  inline heapobject* getSavedTop(void);
  //
  // get the address of the saved top as a heapobject*
  //
  inline heapobject* getSavedTopAddr(void);
  //
  // update the top
  //
  inline void setTop(heapobject*);
  //
  // update the saved top
  //
  inline void setSavedTop(heapobject* t);
  //
  // Appropriate methods for creating new objects on the heap.  As
  // additional heap objects are created, companion methods here
  // need to be added.
  //
  inline Variable *newVariable(const bool has_extra_info = false);
  inline ObjectVariable *newObjectVariable(void);

  inline Structure *newStructure(const size_t arity);

  // Both constructors for the list type.
  inline Cons *newCons(void);
  inline Cons *newCons(Object *, Object *);
  Cons *newCons(char* ch);

  inline Cons *newSubstitutionBlockList(SubstitutionBlock *,
					Object *);

  inline Short *newShort(int32 val);
  inline Long *newLong(long val);
  inline Object *newInteger(long val);
  inline Double *newDouble(double d);
  inline StringObject *newStringObject(const char* s);
  inline QuantifiedTerm *newQuantifiedTerm(void);

  inline Substitution *newSubstitution(void);
  inline Substitution *newSubstitution(Object *sub_block_list,
				       Object *term);

  inline SubstitutionBlock *newSubstitutionBlock(const size_t size);
  inline SubstitutionBlock *copySubstitutionBlock(SubstitutionBlock *);
  //
  // Add a substitution to the right of another one.
  //
  Object *appendSubstitutionBlockLists(Object *, Object *);

  Object* copyDistinctnessList(Object* dist_list, ObjectVariable* obvar);

  bool isBindingList(Object* o) const;

  Object* newDelay(Object *problem, Object *tail);

// Fast equals
bool fastEqualSubstitution(Object *, Object *);

bool fastEqualSubstitutionBlock(SubstitutionBlock *, SubstitutionBlock *);

truth3 fastEqualBoundVariables(Object *, Object *);
  
truth3 fastEqualQuant(Object *, Object *);

truth3 fastEqualStruct(Object *, Object *);

truth3 fastEqualCons(Object *, Object *);

truth3 fastEqualTerm(Object *, Object *);

truth3 fastEqual(PrologValue&, PrologValue&);

  //
  // dereference() follows the variable-reference trail from an object
  // -- iteratively, not recursively -- and returns either the ultimate
  // non-variable object being referred to or an unbound variable.
  // Substitutions are collected together and any substitution
  // evaluations are carried out.
  //
  inline Object* dereference(Object* o);
  
  //
  // Dereference a Prolog Value
  //
  inline void prologValueDereference(PrologValue& pval);

  void save(ostream& ostrm) const;

  void load(istream& istrm);


#include "check.h"
#include "copy_term.h"
#include "collect.h"
#include "dereference.h"
#include "display_term.h"
#include "regalloc.h"
#include "substitution.h"
#include "timeout.h"
#include "unravel.h"
#include "yield.h"
                                       
#ifdef QP_DEBUG
  void printMe(AtomTable&);
#endif
};

//////////////////////////////////////////////////////////////////////
// Inline function bodies for Heap

//
// Default constructor
//
inline Heap::Heap(char* name, u_long size, bool GC)
  : data( new heapobject[size * K] )
{
  //
  // Ensure that the heap is a sensible size
  //
  assert(size > 0);

  //
  // Validate the invariant on heapobject.  This seems about the
  // nicest place to do it at the moment.
  //
  assert(sizeof (heapobject) == sizeof (void *));

  top = data + size * K / sizeof (heapobject);
  gcMark = data + (9 * size * K) / (10 * sizeof (heapobject)); // 90% of heap
  next = data;
  highwater = data;
  doGC = GC;
  heapname = name;
  savedTop = data;
}

//
// Destructor
//
inline Heap::~Heap(void)
{
  if (data != NULL)
    {
      delete [] data;
    }
}

//
// Allocates enough space on the heap for `numHeapObjs' new objects.
// This will need to be modifided to account for contingencies,
// eg. when there isn't enough space on the heap to allocate all of
// the requested objects.
//
inline heapobject *
Heap::allocateHeapSpace(size_t numHeapObjs)
{
  //
  // Only really useful if size_t isn't unsigned
  //
  assert(numHeapObjs > 0);

  register heapobject *result = next;
  next += numHeapObjs;

  //
  // Overflow checks
  //
  if (next > top)
    {
      //
      // Die if no more space left on the heap
      //
      outOfSpace();
      exit(EXIT_FAILURE);
    }
  else if (next > highwater)
    {
      //
      // High water mark adjustment, if neccessary
      //
      highwater = next;
    }

#if DEBUG
  for (heapobject *pos = result; pos < result + numHeapObjs; pos++)
    {
      *pos = 0;
    }
#endif

  return result;
}

//
// Return the name of the code area, for inclusion in error messages.
//
inline char *Heap::getAreaName(void) const
{
  return heapname;
}

inline heapobject*
Heap::getSavedTop(void)
{
  return savedTop;
}

inline heapobject*
Heap::getSavedTopAddr(void)
{
  return(reinterpret_cast<heapobject*>(&savedTop));
}

inline void
Heap::setTop(heapobject* t)
{
  assert(t >= data);
  assert(t <= top);
  next = t;
}

inline void
Heap::setSavedTop(heapobject* t)
{
  assert(t >= data);
  assert(t <= top);
  savedTop = t;
}

inline heapobject* 
Heap::getBase(void)
{
  return data;
}

inline heapobject*
Heap::getTop(void)
{
  return next;
}

//
// Create a new (unbound) Variable on the heap
//
inline Variable *
Heap::newVariable(const bool has_extra_info)
{
  heapobject *x = allocateHeapSpace(Variable::size(has_extra_info));

  x[0] = Object::VarTag;
  x[1] = reinterpret_cast<heapobject>(x);

  if (has_extra_info)
    {
      x[0] = Object::VarOtherTag;
      reinterpret_cast<Reference*>(x)->setExtraInfo();
      x[2] = 
	reinterpret_cast<heapobject>((Object*)NULL);           // name
      x[3] = 
	reinterpret_cast<heapobject>(AtomTable::nil);   // delayed problems
    }

  return reinterpret_cast<Variable *>(x);
}

//
// Create a new (unbound) ObjectVariable on the heap
//
inline ObjectVariable *
Heap::newObjectVariable(void)
{
  heapobject *x = allocateHeapSpace(ObjectVariable::size(true));

  x[0] = Object::ObjVarTag;
  x[1] = reinterpret_cast<heapobject>(x);

  reinterpret_cast<Reference*>(x)->setExtraInfo();
  x[2] = 
    reinterpret_cast<heapobject>((Object*)NULL);             // name
  x[3] = 
    reinterpret_cast<heapobject>(AtomTable::nil);	// delayed problems
  x[4] = 
    reinterpret_cast<heapobject>(AtomTable::nil);	// distinctness information
  
  return reinterpret_cast<ObjectVariable *>(x);
}

//
// Create a new Structure on the heap with arity `arity'
//
inline Structure *
Heap::newStructure(const size_t arity)
{
  //
  // Ensure arity is in range
  //
  assert(0 <= arity && arity <= MaxArity);

  heapobject *x = allocateHeapSpace(Structure::size(arity));
  x[0] = static_cast<heapobject>((arity << 8) | Object::StructTag);

  return reinterpret_cast<Structure *>(x);
}

//
// Create a new List (cons) cell on the heap
//
inline Cons *
Heap::newCons(void)
{
  heapobject *x = allocateHeapSpace(Cons::size());

  x[0] = Object::ConsTag;

  return reinterpret_cast<Cons *>(x);
}

inline Cons *
Heap::newCons(Object* head, Object* tail)
{
  Cons *cons = newCons();

  cons->setHead(head);
  cons->setTail(tail);

  return cons;
}

#if 0
inline Cons *
Heap::newObjectVariableList(ObjectVariable *head,
			    Object *tail)
{
  assert(tail->isVariable() || 
	       tail->isNil() ||
	       tail->isObjectVariableList());

  Cons *cons = newCons(head, tail);

  cons->makeObjectVariableList();

  return cons;
}
#endif // 0

inline Cons *
Heap::newSubstitutionBlockList(SubstitutionBlock *head,
			       Object *tail)
{
  assert(tail->isNil() ||
	       (tail->isCons() &&
	       OBJECT_CAST(Cons*, tail)->isSubstitutionBlockList())
	       );

  Cons *cons = newCons(head, tail);

  cons->makeSubstitutionBlockList();
  
  if (head->isInvertible() &&   
      (tail->isNil() || OBJECT_CAST(Cons*, tail)->isInvertible()))
    {
      cons->makeInvertible();
    }
  
  return cons;
}

//
// Create a new Short on the heap with value `val'
//
inline Short *
Heap::newShort(int32 val)
{
  //
  // Value out of range?  Try Long.
  //
  assert(-0x400000 <= val && val < 0x400000);

  heapobject *x = allocateHeapSpace(Short::size());
  x[0] = (val << 8) | Object::ShortTag;

  return reinterpret_cast<Short *>(x);
}

//
// Create a reference to a new Long on the heap with value `val' and
// create a new long in the heap.
//
inline Long *
Heap::newLong(long val)
{
  assert(sizeof(long) == sizeof(heapobject));

  //
  // Value out of range?  Try using smaller numbers
  //
  assert(LONG_MIN <= val && val <= LONG_MAX);

  heapobject *x = allocateHeapSpace(Long::size());
  x[0] = Object::LongTag; 
  x[1] = val;

  return reinterpret_cast<Long *>(x);
}

inline StringObject*
Heap::newStringObject(const char* s)
{
  int size = strlen(s);
  assert(size > 0);
  int word_size = (size + sizeof(heapobject))/sizeof(heapobject);
  heapobject *x = allocateHeapSpace(1 + word_size);
  x[0] = static_cast<heapobject>((word_size << 8) | Object::StringTag);
  x[word_size] = 0;
  strcpy((char*)(x+1), s);
   return reinterpret_cast<StringObject *>(x);
}

inline Object *
Heap::newInteger(long val)
{
  if (-0x400000 <= val && val < 0x400000)
    {
      return newShort(val);
    }
  else
    {
      return newLong(val);
    }
}
  
inline Double *
Heap::newDouble(double val)
{
  heapobject *x = allocateHeapSpace(Double::size());

  x[0] = Object::DoubleTag;
  *((double*)(x+1)) = val; 

  return reinterpret_cast<Double *>(x);
}

//
// Create a new new QuantifiedTerm on the heap
//
inline QuantifiedTerm *
Heap::newQuantifiedTerm(void)
{
  heapobject *x = allocateHeapSpace(QuantifiedTerm::size());

  x[0] = Object::QuantTag;

  return reinterpret_cast<QuantifiedTerm *>(x);
}

//
// Create a new Substitution on the heap
//
inline Substitution *
Heap::newSubstitution(void)
{
  heapobject *x = allocateHeapSpace(Substitution::size());

  x[0] = Object::SubstTag;

  return reinterpret_cast<Substitution *>(x);
}

inline Substitution *
Heap::newSubstitution(Object *sub_block_list, Object *term)
{
  Substitution *substitution = newSubstitution();

  substitution->setSubstitutionBlockList(sub_block_list);
  substitution->setTerm(term);

  return substitution;
}

//
// Create a new SubstitutionBlock on the heap with `size' parallel
// substiutions
//
inline SubstitutionBlock *
Heap::newSubstitutionBlock(size_t sub_size)
{
  //
  // Too large?  Try splitting up your substitutions, 
  // or removing redundancies
  //
  assert(0 < sub_size);
  assert(sub_size <= MaxSubstBlock);

  heapobject *x = allocateHeapSpace(SubstitutionBlock::size(sub_size));

  x[0] = static_cast<heapobject>(sub_size << 12 | Object::SubBlockTag);

  return reinterpret_cast<SubstitutionBlock *>(x);
}

//
// Create a new SubstitutionBlock on the heap, copying the supplied
// substitution block.
//
inline SubstitutionBlock *
Heap::copySubstitutionBlock(SubstitutionBlock *sub_block)
{
  SubstitutionBlock *new_sub_block = 
    newSubstitutionBlock(sub_block->getSize());
  if (sub_block->isInvertible())
    {
      new_sub_block->makeInvertible();
    }

  for (size_t i = 1; i <= new_sub_block->getSize(); i++)
    {
      new_sub_block->setDomain(i, sub_block->getDomain(i));
      new_sub_block->setRange(i, sub_block->getRange(i));
    }

  return new_sub_block;
}


//
// dereference() follows the variable-reference trail from an object
// -- iteratively, not recursively -- and returns either the ultimate
// non-variable object being referred to or an unbound variable.
// Substitutions are collected together and any substitution
// evaluations are carried out.
//
inline Object* 
Heap::dereference(Object* o)
{
  //
  // Ensure we're not about to dereference a NULL pointer
  //
  assert(o != NULL);
  
  while ( (o->getTag() & Object::DerefMask) == 0 ) 
    {
      //
      // While still a (ob)variable, hence referring to something else,
      // move to what it's referring to
      //
      Object* n = OBJECT_CAST(Reference *, o)->getReference();
      assert(n != NULL);
      if ( n == o ) 
	{
	  return o; // An unbound (ob)variable
	}
      o = n;
    }

  if (o->isSubstitution())
    {
      return (subDereference(o));
    }
  // else
  return o;
}

//
// Dereference a Prolog Value
//
inline void 
Heap::prologValueDereference(PrologValue& pval)
{
  pval.setTerm(pval.getTerm()->variableDereference());
  if (pval.getSubstitutionBlockList()->isNil() 
      && !pval.getTerm()->isSubstitution())
    {
      return;
    }
  else
    {
      Object* term = pval.getTerm();
      Object* sub = pval.getSubstitutionBlockList();
      assert(term->hasLegalSub());
      assert(sub->isLegalSub());
      substitutionDereference(sub, term);
      pval.setTerm(term);
      pval.setSubstitutionBlockList(sub);
      return;
    }
}

#endif // HEAP_QP_H







