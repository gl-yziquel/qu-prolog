// dynamic_code.h - Storage for dynamic code.
//
// ##Copyright##
// 
// Copyright (C) 2000, 20001
// Software Verification Research Centre
// The University of Queensland
// Australia 4072
// 
// email: svrc@it.uq.edu.au
// 
// The Qu-Prolog 6.0 System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000,2001 by The University of Queensland, 
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
// 	written consent from the SVRC; and
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
// For information on commercial use of this software contact the SVRC.
// 
// ##Copyright##
//
// $Id: dynamic_code.h,v 1.6 2002/02/05 04:00:44 qp Exp $  

#ifndef DYNAMIC_CODE_H
#define DYNAMIC_CODE_H

// Each dynamic predicate contains a chain of all clauses, a chain
// of clauses that have a variable in the indexed argument and
// a hash table, hashed on the indexed argument, that contains
// a clause chain for clauses that match the indexed argument.
//

#include <list.h>
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

//
// Wrapper for start and end pointers of  code blocks that
// link the clauses of the chain.
//
class ChainEnds
{
private:
  bool removed;
  CodeLoc firstPtr;
  CodeLoc lastPtr;

public:
  
  static const word8 NULL_INSTR = (word8)256;
  
  ChainEnds(void) : removed(false), firstPtr(NULL), lastPtr(NULL) {} 

  ~ChainEnds(void) {}

  void setFirst(CodeLoc f) { firstPtr = f; }
  void setLast(CodeLoc l) { lastPtr = l; }
  
  CodeLoc first(void) { return firstPtr; }
  CodeLoc last(void) { return lastPtr; }

  void addToChainStart(CodeLoc block);
  void addToChainEnd(CodeLoc block);

  void makeRemoved(void) { removed = true; }

  void unmakeRemoved(void) { removed = false; }

  bool isRemoved(void) {return removed; }

  void operator=(const ChainEnds c)
  {
    firstPtr = c.firstPtr;
    lastPtr = c.lastPtr;
    removed = c.removed;
  }

  void gcChain(void);

#ifdef DEBUG
  void printMe(void);
#endif //DEBUG
  
};

//
// The clause chains are made up of code blocks
//
// These blocks contain code for either linking blocks or clause code blocks
//
// The possible code for a link block
//
// The first clause of a chain is
// DB_TRY
// arity
// address of predicate
// address of this clause
// address of next clause
//
// Subsequent clauses of a clain
// DB_RETRY
// arity
// address of predicate
// address of this clause
// address of next clause
//
// A singleton clause
// DB_JUMP
// arity
// address of predicate
// address of code block
// NULL address


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

public:
  
  void clearEntry(void)
  {
    if (clauseChain != NULL)
      {
	DEBUG_ASSERT(clauseChain->first() == NULL);
        DEBUG_ASSERT(clauseChain->last() == NULL);
	delete clauseChain;
        clauseChain = NULL;
      }
  }

  ChainEnds* getChainEnds(void)
  {  return clauseChain; }

  CodeLoc getStartCodeChain(void)
  {  return clauseChain->first(); }

  CodeLoc getEndCodeChain(void) 
  {  return clauseChain->last(); }

  bool isEmpty(void) const
  {  return (tag == 0); }

  bool isRemoved(void)
  {  return (clauseChain->isRemoved()); }

  void addToChainStart(CodeLoc block)
  {  clauseChain->addToChainStart(block); }

  void addToChainEnd(CodeLoc block)
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
	    DEBUG_ASSERT(clauseChain->isRemoved());
	    DEBUG_ASSERT(clauseChain->first() == NULL);
	    DEBUG_ASSERT(clauseChain->last() == NULL);
	    clauseChain->unmakeRemoved();
	  }
      }
    else
      {
        clauseChain = entry.clauseChain;
      }
  }

  DynamicClauseHashEntry(word32 t = 0, word32 v = 0) 
    : tag(t), value(v), clauseChain(NULL)
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

  CodeLoc getStartCodeChain(const int index)
  { return(getEntry(index).getStartCodeChain()); }

  CodeLoc getEndCodeChain(const int index)
  { return(getEntry(index).getEndCodeChain()); }
  
  DynamicClauseHash(word32 TableSize) 
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

public:

  word8 getIndexedArg(void) const 
  { return indexedArg; }

  void gcPredicate(void);

  void aquire(void)
  { 
    refcount++; 
  }

  void release(void)
  {
    DEBUG_ASSERT(refcount > 0);
    refcount--;
    if (refcount == 0 && dirty)
      {
	gcPredicate();
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
    DEBUG_ASSERT(clauseArity != 0);
    
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

  CodeLoc makeDBCodeBlock(CodeLoc clauseCode)
  {
    CodeLoc block = new word8[SIZE_OF_DB_BLOCK];
    CodeLoc pc = block;
    updateInstruction(pc, DB_JUMP);
    pc += Code::SIZE_OF_INSTRUCTION;
    updateNumber(pc, clauseArity);
    pc += Code::SIZE_OF_NUMBER;
    updateAddress(pc, (word32)this);
    pc += Code::SIZE_OF_ADDRESS;
    updateCodeLoc(pc, clauseCode);
    pc += Code::SIZE_OF_ADDRESS;
    updateAddress(pc, 0);
    return (block);

  }

  void  addToStartClauseChain(ChainEnds& chain, CodeLoc codeBlock)
  {
    chain.addToChainStart(makeDBCodeBlock(codeBlock));
  }

  void  addToEndClauseChain(ChainEnds& chain, CodeLoc codeBlock)
  {
    chain.addToChainEnd(makeDBCodeBlock(codeBlock));
  }


  void addToHashedChains(const bool asserta, CodeLoc codeBlock);
   
  void copyVarClauses(ChainEnds& chain);

  void  assertClause(Thread &th, Object* indexarg,
                     Object* instrs, const bool asserta);

  DynamicClauseHashEntry* makeEntry(Thread &th, Object* term);


  DynamicPredicate(const word8 arity, const word8 indexarg = 0, 
                   const int tablesize = 4)
    : clauseArity(arity),indexedArg(indexarg), 
    dirty(false), refcount(0),
    indexedClauses(tablesize) {}

  
};

#endif  // DYNAMIC_CODE_H










