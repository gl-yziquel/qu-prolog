// dyn_code_block.h - Storage for dynamic code.
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
// $Id: dyn_code_block.h,v 1.6 2006/01/31 23:17:50 qp Exp $  

#ifndef DYN_CODE_BLOCK_H
#define DYN_CODE_BLOCK_H

#include <list>
//#include "atom_table.h"
//#include "code.h"
#include "dynamic_code.h"
#include "instructions.h"

// Forward declarations
class CodeLinkingBlock;

class DynCodeBlock
{
private:
  int refcount;
  list<CodeLinkingBlock*> codeblocks;
  CodeLoc code;
public:
  // When a new code block is created (by assert) refcount is set to 1
  // because asserting produces a reference.
  explicit DynCodeBlock(CodeLoc c):refcount(1)
  {
    code = c;
  }

  // Called when something references the clause.
  void aquire(void)
  {
    refcount++;
  }

  // Called when something is finished with the clause.
  // If the reference count becomes zero this object is deleted.
  void release(void)
  {
    refcount--;
    if (refcount == 0)
      {
	delete this;
      }
  }

  int getRefcount(void) { return refcount; }

  // Update the list of linking blocks.
  void addLinkBlock(CodeLinkingBlock* b)
  {
    codeblocks.push_back(b);
  }

  // When the clause is retracted the first instruction in the block
  // is set to fail and the jump address in the linking blocks are set to 0
  //
  void setFail(void)
  {
    updateInstruction(code, FAIL);
    for (list<CodeLinkingBlock*>::iterator iter = codeblocks.begin();
	 iter != codeblocks.end();
	 iter++)
      {
	(*iter)->setJumpAddr(0);
      }
  }
  
  ~DynCodeBlock(void) 
  {
    // delete the linking blocks
    for (list<CodeLinkingBlock*>::iterator iter = codeblocks.begin();
	 iter != codeblocks.end();
	 iter++)
      {
	(*iter)->release();
      }
    // delete the list
    codeblocks.clear();
    // delete the code
    delete [] code;
  }

  CodeLoc getStartOfCode(void)
  {
    return code;
  }

#ifdef QP_DEBUG
  void printMe(void)
  {
    cerr << "----DynCodeBlock-----" << endl;
    cerr << "refc = " << refcount << endl;
    cerr << "Code = " << (word32)code << endl;
  }

  bool list_member(CodeLinkingBlock* link)
  {
    for (list<CodeLinkingBlock*>::iterator iter = codeblocks.begin();
	 iter != codeblocks.end();
	 iter++)
      {
	if (*iter == link)
	  {
	    return true;
	  }
      }
    return false;
  }
#endif // DEBUG
	
};


#endif  // DYN_CODE_BLOCK_H










