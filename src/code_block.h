// code_block.h -
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
// $Id: code_block.h,v 1.5 2006/01/31 23:17:49 qp Exp $

#ifndef	CODE_BLOCK_H
#define	CODE_BLOCK_H

//#include <stream>

#include "int.h"
#include "code.h"

typedef u_long CodeBlockLoc;

const u_long INIT_CODE_SIZE = 1000;

enum CodeBlockType { QUERY_BLOCK, PREDICATE_BLOCK };

class CodeBlock
{
private:
  CodeBlockType type;		// Type of code block

  u_long atom;		// Name and arity of code block (predicates only)
  u_long arity;

  char *code;		// Code area, dynamically expanded

  u_long size;		// Current storage allocated for code area
  u_long current;	// Current fullness of code area

  void Expand(void)
    {
      u_long new_size = size * 2;
      char *tmp = new char[new_size];
      
      memcpy(tmp, code, size);
      
      delete [] code;
      
      code = tmp;
      size = new_size;
    }

public:
  CodeBlock(const CodeBlockType t,
	    const u_long at,
	    const u_long ar)
    : type(t),
      atom(at),
      arity(ar),
      code(new char[INIT_CODE_SIZE]),
      size(INIT_CODE_SIZE),
      current(0)
  {

  }

  ~CodeBlock(void)
    {
      delete [] code;
    }

  char operator[](const CodeBlockLoc loc) const
  {
    assert(loc <= current);
    return code[loc];
  }

  CodeBlockType Type(void) const { return type; }
  u_long Atom(void) const { return atom; }
  u_long Arity(void) const { return arity; }

  u_long Current(void) const { return current; }
  u_long Size(void) const { return size; }

  void Advance(u_long n)
    {
      while (current + n > size)
	{
	  Expand();
	}

      current += n;
    }

  // Version of put that sticks chars on the end, expanding the code
  // block when needed.
  // This will be the normal case.
  void Put(char c)
    {
      if (current == size)
	{
	  Expand();
	}

      code[current] = c;
      current++;
    }

  // Version of Put that explicitly supplies a position.
  // This is the case when we are patching the jumps to a label that
  // we've just encountered.
  // Since this use only makes sense when the p <= current,
  // we abort if p > current.
  void Put(u_long p, char c)
    {
      assert(p <= current);

      code[p] = c;
    }

  bool operator==(const CodeBlock& cb) const
  {
    return this == &cb;
  }

  ostream& Save(ostream& ostrm) const;
};

inline ostream& operator<<(ostream& ostrm, const CodeBlock&)
{
  return ostrm << "Code Block";
}


#endif	// CODE_BLOCK_H
