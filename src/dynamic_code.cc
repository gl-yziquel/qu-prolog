// dynamic_code.cc - Storage for dynamic code.
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
// $Id: dynamic_code.cc,v 1.10 2002/02/27 21:27:59 qp Exp $  

#include "objects.h"
#include "thread_qp.h"
#include "dynamic_code.h"
#include "dynamic_hash_table.cc"

extern AtomTable* atoms;
//
// Construct a hash entry for indexing into dynamic code area.
// "Variables" have tag set to 0 - they may match any term. 
// The tag is set to 0 if:
// 1. The term is a variable
// 2. The term is an obvar with a substitution.
// 3. The term is a structure with a non-atom functor.
// 4. The term is a quantifier with a non-atom quant.
//
// Otherwise tag is the cell tag of the term.
// The value part in non-zero if it contains some useful discrimination.
//

//
// Get the next link in clause chain.
//
CodeLoc getNextBlock(CodeLoc code)
{
  CodeLoc pc = code + OFFSET_TO_LAST_ADDRESS;
  return (getCodeLoc(pc));
}

#if 0
void ChainEnds::printMe(void)
{
  cerr << "------------ Chain ------------" << endl;
  cerr << "firstPtr = " << (word32)(firstPtr) << endl;
  cerr << "lastPtr = " << (word32)(lastPtr) << endl << endl;

  CodeLoc ptr = firstPtr;
  while (ptr != NULL)
    {
  CodeLoc clloc = ptr + Code::SIZE_OF_INSTRUCTION
    + Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
  CodeLoc cl = getCodeLoc(clloc);
  cerr << "Block = " << (word32)ptr << " CodeBlock = " << (word32)cl << endl;
  ptr = getNextBlock(ptr);
   }
}
#endif // 0

// 
// Add the clause block to the start of the clause chain.
//
void 
ChainEnds::addToChainStart(CodeLoc block)
{
  if (firstPtr == NULL)
    {
      DEBUG_ASSERT(lastPtr == NULL);
      firstPtr = block;
      lastPtr = block;
    }
  else
    {
      DEBUG_ASSERT(lastPtr != NULL);
      CodeLoc pc = firstPtr;
      updateInstruction(pc, DB_RETRY);
      pc = block;
      updateInstruction(pc, DB_TRY);
      pc += OFFSET_TO_LAST_ADDRESS;
      updateCodeLoc(pc, firstPtr); 
     firstPtr = block;
    }	  
}
	  
// 
// Add the clause block to the end of the clause chain.
//
void ChainEnds::addToChainEnd(CodeLoc block)
{
  if (firstPtr == NULL)
    {
      DEBUG_ASSERT(lastPtr == NULL);
      firstPtr = block;
      lastPtr = block;
      return;
    }
 CodeLoc pc = lastPtr;
  if (firstPtr == lastPtr)
    {
      updateInstruction(pc, DB_TRY);
    }
  pc += OFFSET_TO_LAST_ADDRESS;
  updateCodeLoc(pc, block);
  pc = block;
  updateInstruction(pc, DB_RETRY); 
  lastPtr = block;
}

//
// Garbage collect the link blocks in the chain whose clause block
// has been retracted.
//
void ChainEnds::gcChain(void)
{
  if (firstPtr == NULL)
    {
      return;
    }

  // The start of the chain
  CodeLoc start = firstPtr;
  CodeLoc clloc = start + Code::SIZE_OF_INSTRUCTION
    + Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
  // The address of the clause code block
  CodeLoc cl = getCodeLoc(clloc);
  // Delete all the linking blocks of retracted clauses at the beginning of 
  // the chain.
  while (getInstruction(cl) == NULL_INSTR)
    {
      // The clause has been retracted so delete the link
      CodeLoc tmp = start;
      start = getNextBlock(start);
      delete [] tmp;
      if (start == NULL)
	{
	  break;
	}
      clloc = start + Code::SIZE_OF_INSTRUCTION
	+ Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
      cl = getCodeLoc(clloc);
    }
  if (start == NULL)
    {
      firstPtr = NULL;
      lastPtr = NULL;
      removed = true;
      return;
    }
  firstPtr = start;
  CodeLoc follower = start;
  // At this point the first linking block is for a non-retracted clause.
  // The rest of the chain is processed looking for retracted clauses.
  while (start != NULL)
    {
      clloc = start + Code::SIZE_OF_INSTRUCTION
	+ Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
      cl = getCodeLoc(clloc);
      while (getInstruction(cl) != NULL_INSTR)
	{
	  follower = start;
	  start = getNextBlock(start);
	  if (start == NULL)
	    {
	      break;
	    }
	  clloc = start + Code::SIZE_OF_INSTRUCTION
	    + Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
	  cl = getCodeLoc(clloc);
	}
      if (start == NULL)
	{
	  lastPtr = follower;
	  break;
	}
      // At this point the current linking block is for a retracted clause
      // Delete this and subseqent blocks for deleted clauses.
      clloc = start + Code::SIZE_OF_INSTRUCTION
	+ Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
      cl = getCodeLoc(clloc);
      while (getInstruction(cl) == NULL_INSTR)
	{
	  // Delete linking block.
	  CodeLoc tmp = start;
	  start = getNextBlock(start);
	  delete [] tmp;
	  if (start == NULL)
	    {
	      break;
	    }
	  clloc = start + Code::SIZE_OF_INSTRUCTION
	    + Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
	  cl = getCodeLoc(clloc);
	}
      // At this point we have a linking block of a non-retracted clause.
      // The next pointer of the previous non-retracted linking block
      // (in follower) must be reset to point at start - the next 
      // non-retracted block.
      clloc = follower + Code::SIZE_OF_INSTRUCTION
	+ Code::SIZE_OF_NUMBER + 2*Code::SIZE_OF_ADDRESS;
      updateCodeLoc(clloc, start);
      lastPtr = follower;
    }
  if (firstPtr == lastPtr)
    {
      updateInstruction(firstPtr, DB_JUMP);
    }
  else
    {
      updateInstruction(firstPtr, DB_TRY);
    }
}

DynamicClauseHashEntry*  
DynamicPredicate::makeEntry(Thread &th, Object* term)
{
  Object* pterm = term->variableDereference();
  const Object::uTag argTag = pterm->utag();
  word32 t, v;
  
  switch (argTag)
    {
    case Object::uVar:
      {
        t = 0; v = 0;
      }
      break;
      
    case Object::uObjVar:
      {
	// cannot discriminate between obvars
	t = reinterpret_cast<word32>(argTag); 
	v = 0;  
      }
      break;
      
    case Object::uCons:
      {
        t = argTag; v = 0;  // no useful info to put in v
      }
      break;
      
    case Object::uStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, pterm);
	
	if (str->getFunctor()->isAtom())
          {
            t = argTag;
 	    v = reinterpret_cast<word32>(str->getFunctor());
          }
        else
          {
            t = 0; v = 0;
          }
      }
      break;
      
    case Object::uQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, pterm);
	
	if (quant->getQuantifier()->isAtom())
          {
            t = argTag;
 	    v = reinterpret_cast<word32>(quant->getQuantifier());
          }
        else
          {
            t = 0; v = 0;
          }
      }
      break;
      
    case Object::uConst:
      {
        t = argTag;
        if (pterm->isNumber())
          {
            v = pterm->getNumber();
          }
        else
          {
 	    v = reinterpret_cast<word32>(pterm);
          }
      }
      break;
      
    case Object::uSubst:
      {
        PrologValue spterm(pterm);
        th.TheHeap().prologValueDereference(spterm);
        const Object::uTag sargTag = spterm.getTerm()->utag();
	
	switch (sargTag)
	  {
	  case Object::uCons:
	    {
	      t = sargTag; v = 0;  // no useful info to put in v
	    }
	    break;
	    
	  case Object::uStruct:
	    {
	      Structure* str = OBJECT_CAST(Structure*, spterm.getTerm());
	      
	      if (str->getFunctor()->isAtom())
		{
		  t = sargTag;
		  v = reinterpret_cast<word32>(str->getFunctor());
		}
	      else
		{
		  t = 0; v = 0;
		}
	    }
	    break;
	    
	  case Object::uQuant:
	    {
	      QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, 
						  spterm.getTerm());
	      
	      if (quant->getQuantifier()->isAtom())
		{
		  t = sargTag;
		  v = reinterpret_cast<word32>(quant->getQuantifier());
		}
	      else
		{
		  t = 0; v = 0;
		}
	    }
	    break;
	    
	  case Object::uConst:
	    {
	      t = sargTag;
	      if (spterm.getTerm()->isNumber())
		{
		  v = spterm.getTerm()->getNumber();
		}
	      else
		{
		  v = reinterpret_cast<word32>(spterm.getTerm());
		}
	    }
	    break;
	    
	  default:
	    t = 0;v=0;
	  }
      }
      break;
      
    default:
      t = 0;v=0;
      DEBUG_ASSERT(false);
    }
  DynamicClauseHashEntry *entry = new DynamicClauseHashEntry(t, v); 
  return entry;
}


//
// Add clause to each hash entry - used to add clause with var in indexed arg.
// 
void
DynamicPredicate::addToHashedChains(const bool asserta, CodeLoc codeBlock)
{
  //
  // Set up hash table iterator
  //
  indexedClauses.iter_reset();
  int index = indexedClauses.iter_next();
  while(index != -1)
    {
      CodeLoc cb = makeDBCodeBlock(codeBlock);
      if (asserta)
	{
	  indexedClauses.getEntry(index).addToChainStart(cb);
	}
      else
	{
	  indexedClauses.getEntry(index).addToChainEnd(cb);
	}
      index = indexedClauses.iter_next();
    } 
}

//
// Copy the var clause chain to hash entry.
// Used to copy the var clauses when adding the first clause with
// a given hash value.
//
void
DynamicPredicate::copyVarClauses(ChainEnds& chain)
{
  CodeLoc iter = varChain.first();
  for (;
       iter != NULL;
       iter = getNextBlock(iter))
    {
      CodeLoc clloc = iter + Code::SIZE_OF_INSTRUCTION
        + Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
      CodeLoc cl = getCodeLoc(clloc);
      chain.addToChainEnd(makeDBCodeBlock(cl));
    }
}

//
// Garbage collect the predicate
//
void DynamicPredicate::gcPredicate(void)
{
  CodeLoc clauseGarbage = NULL;

  CodeLoc clauseLink = allChain.first();
  DEBUG_ASSERT(clauseLink != NULL);

  // First go through the allChain chain looking for retracted clauses.
  // Reset the first instruction to NULL_INSTR and follow this with the address
  // of the previous retracted clause so that they can all be deleted 
  // after the linking blocks have been processed.
  // clauseGarbage contains a pointer to the chain of these retracted blocks.
  //
  while (clauseLink != NULL)
    {
      CodeLoc clauseAddr = clauseLink + Code::SIZE_OF_INSTRUCTION 
	+ Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
      CodeLoc clause = getCodeLoc(clauseAddr);
      CodeLoc pc = clause;
      if (getInstruction(pc) == FAIL)
	{
	  updateInstruction(clause, ChainEnds::NULL_INSTR);
	  updateCodeLoc(pc, clauseGarbage);
          clauseGarbage = clause;
	}
      clauseLink = getNextBlock(clauseLink);
    }
  DEBUG_ASSERT(clauseGarbage != NULL);
  // Delete the required linking blocks of allChain,varChain and all the
  // indexed chains.
  allChain.gcChain();
  varChain.gcChain();
  indexedClauses.iter_reset();
  int index = indexedClauses.iter_next();
  while(index != -1)
    {
      indexedClauses.getEntry(index).getChainEnds()->gcChain();
      index = indexedClauses.iter_next();
    }

  // Now that the linking blocks have been processed, delete the
  // code blocks collected in clauseChain.
  //
  while (clauseGarbage != NULL)
    {
      CodeLoc pc = clauseGarbage + Code::SIZE_OF_INSTRUCTION;
      CodeLoc next = getCodeLoc(pc);
      delete [] clauseGarbage;
      clauseGarbage = next;
    }

  dirty = false;
}

// 
// Asserting a new clause.
// indexarg - the term in the index position.
// instrs - a Prolog list representing the instructions for the clause.
// blockPtr - the location of the new clause.
// asserta - front or back?
//
void  
DynamicPredicate::assertClause(Thread &th, Object* indexarg, 
			       Object* instrs,  
			       const bool asserta)
{
  instrs = instrs->variableDereference();
  
  CodeLoc code = (CodeLoc)(instrs->getNumber());

  if (clauseArity == 0)
    {
      //
      // No args to index on so use the all clause chain.
      //
      if (asserta)
	{
	  addToStartClauseChain(allChain, code);
	}
      else
	{
	  addToEndClauseChain(allChain, code);
	}
      return;
    }
  //
  // clauseArity > 0
  //
  
  DynamicClauseHashEntry* entry = makeEntry(th, indexarg); 
  
  //
  // add to all clause chain.
  //
  if (asserta)
    {
      addToStartClauseChain(allChain, code);
    }
  else
    {
      addToEndClauseChain(allChain, code);
    }
  if (entry->isEmpty())
    {
      //
      // index arg is var so add to var chain.
      //
      if (asserta)
	{
	  addToStartClauseChain(varChain, code);
	}
      else
	{
	  addToEndClauseChain(varChain, code);
	}
      //
      // Update existing hash entries.
      //
      addToHashedChains(asserta, code);
      delete entry;
    }
  else 
    {
      //
      // Something to add to hash table
      //
      int index = indexedClauses.search(*entry);
      if (index == -1)
	{
	  // Not found - then add
	  indexedClauses.insert(*entry, index);
	}
      delete entry;
      ChainEnds* chainPtr = indexedClauses.getEntry(index).getChainEnds();
      DEBUG_ASSERT(chainPtr != NULL);
      if (chainPtr->first() == NULL)
	{
	  DEBUG_ASSERT(chainPtr->last() == NULL);
	  //
	  // New entry so copy var clauses into this chain.
	  //
	  copyVarClauses(*chainPtr);
	}
      if (asserta)
	{
	  addToStartClauseChain(*chainPtr, code);
	}
      else
	{
	  addToEndClauseChain(*chainPtr, code);
	}

#if 0
      cerr << endl << "hash chains" << endl;
      indexedClauses.iter_reset();
      int ind = indexedClauses.iter_next();
      while(ind != -1)
      {
        cerr << "INDEX = " << ind << endl;
        indexedClauses.getEntry(ind).getChainEnds()->printMe();
        ind = indexedClauses.iter_next();
      }
#endif // 0

    }
}


