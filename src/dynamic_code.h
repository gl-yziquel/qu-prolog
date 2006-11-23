// dynamic_code.h - Storage for dynamic code.
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
// $Id: dynamic_code.h,v 1.11 2006/01/31 23:17:50 qp Exp $  

#ifndef DYNAMIC_CODE_H
#define DYNAMIC_CODE_H

// Each dynamic predicate contains a chain of all clauses, a chain
// of clauses that have a variable in the indexed argument and
// a hash table, hashed on the indexed argument, that contains
// a clause chain for clauses that match the indexed argument.
//

#include <list>
#include "atom_table.h"
#include "code.h"
#include "dynamic_hash_table.h"
#include "pred_table.h"

static const size_t SIZE_OF_DB_BLOCK =  Code::SIZE_OF_INSTRUCTION 
  + Code::SIZE_OF_NUMBER 
  + 3*Code::SIZE_OF_ADDRESS;

static const size_t OFFSET_TO_LAST_ADDRESS =  Code::SIZE_OF_INSTRUCTION 
  + Code::SIZE_OF_NUMBER 
  + 2*Code::SIZE_OF_ADDRESS;


class DynamicPredicate;

class CodeBlock
{
 private:
  word32 create_timestamp;
  word32 delete_timestamp;
  CodeLoc codePtr;
  DynamicPredicate* thispred;

 public:
  CodeBlock(word32 ct, CodeLoc cp, DynamicPredicate* tp) : 
    create_timestamp(ct), delete_timestamp(WORD32_MAX), codePtr(cp),
    thispred(tp)
    { }

    ~CodeBlock() { delete [] codePtr; }
    
    void setDelete(word32 ts) { delete_timestamp = ts; }
    
    bool isAlive(word32 ts) const 
    { return (create_timestamp <= ts) && (ts < delete_timestamp); }
    
    bool toDelete(word32 ts) const { return ts >= delete_timestamp; }
    CodeLoc getCode() const { return codePtr; }
    DynamicPredicate* getThisPred() const { return thispred; }
    word32 getCTS() const { return create_timestamp; }
    word32 getDTS() const { return delete_timestamp; }
    
};

class LinkedClause
{
 private:
  CodeBlock* blockPtr;
  LinkedClause* next;
 public:
  LinkedClause(CodeBlock* bp, LinkedClause* np) : 
    blockPtr(bp), next(np) 
    { }
    
    ~LinkedClause() { }
    
    bool isAlive(word32 ts) const 
    { return blockPtr->isAlive(ts); }

    LinkedClause* nextAlive(word32 ts)
      {
	LinkedClause* ptr = this;
	while ((ptr != NULL) && !ptr->isAlive(ts))
	  ptr = ptr->getNext();
	return ptr;
      }
    LinkedClause* nextNextAlive(word32 ts)
      {
	LinkedClause* ptr = next;
	while ((ptr != NULL) && !ptr->isAlive(ts))
	  ptr = ptr->getNext();
	return ptr;
      }

    bool toDelete(word32 ts) const { return blockPtr->toDelete(ts); }
    CodeBlock* getCodeBlock() const { return blockPtr; }

    LinkedClause* getNext() const { return next; }
    void setNext(LinkedClause* n) { next = n; }
    
};

//
// Wrapper for start and end pointers of  code blocks that
// link the clauses of the chain.
//
class ChainEnds
{
 private:
  LinkedClause* firstPtr;
  LinkedClause* lastPtr;

 public:
  
  static const word8 NULL_INSTR = (word8)256;
  
  ChainEnds(void) : firstPtr(NULL), lastPtr(NULL) {} 

    ~ChainEnds(void) {}

    void setFirst(LinkedClause* f) { firstPtr = f; }
    void setLast(LinkedClause* l) { lastPtr = l; }
  
    LinkedClause* first(void) { return firstPtr; }
    LinkedClause* last(void) { return lastPtr; }

    void addToChainStart(CodeBlock* block)
    {
      LinkedClause* newlink = new LinkedClause(block, firstPtr);
      firstPtr = newlink;
      if (lastPtr == NULL) lastPtr = newlink;
    }

    void addToChainEnd(CodeBlock* block)
    {
      LinkedClause* newlink = new LinkedClause(block, NULL);
      if (lastPtr == NULL)
	{
	  assert(firstPtr == NULL);
	  firstPtr = newlink;
	}
      else
	lastPtr->setNext(newlink);
      lastPtr = newlink;
    }

    void operator=(const ChainEnds c)
      {
	firstPtr = c.firstPtr;
	lastPtr = c.lastPtr;
      }

    void gcChain(word32 time, bool deleteBlock);

#ifdef QP_DEBUG
    void printMe(void);
#endif //DEBUG
  
};


//
// This class defines the entries in the hash table.
//
class DynamicClauseHashEntry
{
 private:
  // tag is the Cell tag for the hashed arg and value is the associated
  // value. clauseChain is a chain of clauses for this entry.
  word32 	tag, value;
  ChainEnds*    clauseChain;
  bool removed;

 public:
  
  void clearEntry(void)
  {
    if (clauseChain != NULL)
      {
	assert(clauseChain->first() == NULL);
        assert(clauseChain->last() == NULL);
	delete clauseChain;
        clauseChain = NULL;
      }
  }

  ChainEnds* getChainEnds(void)
    {  return clauseChain; }

  LinkedClause* getStartCodeChain(void)
  {  return clauseChain->first(); }

  LinkedClause* getEndCodeChain(void) 
  {  return clauseChain->last(); }

  bool isEmpty(void) const
  {  return (tag == 0); }

  bool isRemoved(void)
  {  return removed; }

  void addToChainStart(CodeBlock* block)
  {  clauseChain->addToChainStart(block); }

  void addToChainEnd(CodeBlock* block)
  {  clauseChain->addToChainEnd(block); }

  int hashFn(void) const
  { return (value); }

  bool operator==(const DynamicClauseHashEntry entry) const
  { return ((tag == entry.tag) && (value == entry.value)); }

  void operator=(const DynamicClauseHashEntry entry)
    { 
      tag = entry.tag; 
      value = entry.value;
      if (entry.clauseChain == NULL)
	{
	  if (clauseChain == NULL)
	    {
	      clauseChain = new ChainEnds;
	    }
	  else
	    {
	      assert(removed);
	      assert(clauseChain->first() == NULL);
	      assert(clauseChain->last() == NULL);
	    }
	}
      else
	{
	  clauseChain = entry.clauseChain;
	}
      removed = false;
    }

  DynamicClauseHashEntry(word32 t = 0, word32 v = 0) 
    : tag(t), value(v), clauseChain(NULL), removed(false)
    {};

};

//
// The hash table for a dynamic predicate based on the DynamicHashTable
// template class.
//
class DynamicClauseHash : public DynamicHashTable <DynamicClauseHashEntry>
{
 private:
  int	hashFunction(const DynamicClauseHashEntry entry) const
  { return (entry.hashFn()); }
  
 public:
  ChainEnds* getChainEnds(const int index)
    { return(getEntry(index).getChainEnds()); }

  LinkedClause* getStartCodeChain(const int index)
  { return(getEntry(index).getStartCodeChain()); }

  LinkedClause* getEndCodeChain(const int index)
  { return(getEntry(index).getEndCodeChain()); }
  
  explicit DynamicClauseHash(word32 TableSize) 
    : DynamicHashTable <DynamicClauseHashEntry> (TableSize)
    {};

};


//
// The definition of a dynamic predicate.
// clauseArity - the arity of the predicate.
// indexedArg - the argument to hash on (counting from 0 - to match X regs).
// allChain - the all clauses chain.
// varChain - the clause chain with variables in the index arg.
// indexedClauses - the hash table for indexing.
//
class DynamicPredicate 
{
 private:
  word8	             clauseArity;
  word8	             indexedArg;
  bool               dirty;  // a flag to determine if some clause is retracted
  int                refcount; // The number of references to the predicate
  ChainEnds          allChain;
  ChainEnds          varChain;
  DynamicClauseHash  indexedClauses;
  Timestamp	     stamp;

 public:

  const word32 GetStamp(void) { return stamp.GetStamp(); }
  void Stamp(void) { stamp.Stamp(); }

  word8 getIndexedArg(void) const 
  { return indexedArg; }

  void gcPredicate(word32);

  void aquire(void)
  { 
    refcount++; 
  }

  void release(void)
  {
    assert(refcount > 0);
    refcount--;
    if (refcount == 0 && dirty)
      {
	gcPredicate(GetStamp());
      }
  }

  void makeDirty(void)
  {
    dirty = true;
  }

  //
  // Look up the hash table for the term in the index arg
  // Return -2 if indexarg is a variable
  // Return -1 if not in table
  // Else return index into table
  //
  int  lookUp(Thread &th, Object* indexarg)
  {
    assert(clauseArity != 0);
    
    DynamicClauseHashEntry* entry = makeEntry(th, indexarg); 

    if (entry->isEmpty())
      {
	//
	// "Variable" indexarg - any match - return all the clauses.
	//
	delete entry;
	return -2;
      }
    else
      {
	//
	// look up the hash table
	//
	const int index = indexedClauses.search(*entry);
	delete entry;
	return index;
      }
  }


  ChainEnds* lookUpClauseChain(Thread &th, Object* indexarg) 
    {
      if (clauseArity == 0)
	{
	  //
	  // No args - in this case indexarg is just a dummy.
	  // Nothing to index on so get all the clauses.
	  //
	  return &allChain;
	}
      int index = lookUp(th, indexarg);
      if (index == -2)
	{
	  //
	  // Variable so use allChain
	  //
	  return &allChain;
	}
      else if (index == -1)
	{
	  //
	  // No existing clauses that match indexarg - so get the var clauses.
	  //
	  return &varChain;
	}
      else
	{
	  //
	  // Match found so get the matching clauses.
	  //
	  return indexedClauses.getChainEnds(index);
	}
    }


  void addToHashedChains(const bool asserta, CodeBlock* codeBlock);
   
  void copyVarClauses(ChainEnds& chain);

  void  assertClause(Thread &th, Object* indexarg,
                     Object* instrs, const bool asserta);

  DynamicClauseHashEntry* makeEntry(Thread &th, Object* term);


  DynamicPredicate(const word8 arity, const word8 indexarg = 0, 
                   const int tablesize = 4)
    : clauseArity(arity),indexedArg(indexarg), 
    dirty(false), refcount(0),
    indexedClauses(tablesize) {}

#ifdef QP_DEBUG
    void display();
#endif
  
};

#endif  // DYNAMIC_CODE_H










