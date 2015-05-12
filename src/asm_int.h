// asm_int.h - Integer storage for the assembler.
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: asm_int.h,v 1.7 2005/08/31 03:20:19 qp Exp $

#ifndef	ASM_INT_H
#define	ASM_INT_H

#ifdef WIN32
#include <list>
#endif


#include "code_block.h"
#include "int.h"
#include "config.h"

template <class IntType>
class ASMInt: public Int<IntType>
{
public:
  ASMInt(const IntType v,
	 const int m = 0) : Int<IntType>(v, m) { }

  void Put(CodeBlock& code_block) const
  {
    const IntType v = this->value;
    switch (sizeof(IntType))
      {
      case 1:
	code_block.Put(static_cast<char>((word32)v & 0xff));
	break;
      case 2:
	{
	  code_block.Put(static_cast<char>(((word32)v >> 8) & 0xff));
	  code_block.Put(static_cast<char>((word32)v & 0xff));
	}
	break;
      case 4:
	{
	  code_block.Put(static_cast<char>(((word32)v >> 24) & 0xff));
	  code_block.Put(static_cast<char>(((word32)v >> 16) & 0xff));
	  code_block.Put(static_cast<char>(((word32)v >> 8) & 0xff));
	  code_block.Put(static_cast<char>((word32)v & 0xff));
	}
	break;
#if BITS_PER_WORD == 64
      case 8:
	{
	  code_block.Put(static_cast<char>(((wordptr)v >> 56) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 48) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 40) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 32) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 24) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 16) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 8) & 0xff));
	  code_block.Put(static_cast<char>((wordptr)v & 0xff));
	}
	break;
#endif
      }
  }
  
  void Put(CodeBlockLoc loc, CodeBlock& code_block) const
  {
    const IntType v = this->value;
    
    switch (sizeof(IntType))
      {
      case 1:
	code_block.Put(loc, v & 0xff);
	break;
      case 2:
	{
	  code_block.Put(loc++, (v >> 8) & 0xff);
	  code_block.Put(loc++, v & 0xff);
	}
	break;
      case 4:
	{
	  code_block.Put(loc++, (v >> 24) & 0xff);
	  code_block.Put(loc++, (v >> 16) & 0xff);
	  code_block.Put(loc++, (v >> 8) & 0xff);
	  code_block.Put(loc++, v & 0xff);
	}
	break;
#if BITS_PER_WORD == 64
      case 8:
	{
	  code_block.Put(loc++, (((wordptr)v) >> 56) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 48) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 40) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 32) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 24) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 16) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 8) & 0xff);
	  code_block.Put(loc++, ((wordptr)v) & 0xff);
	}
	break;
#endif
      }
  }
};

// Separate type because double is the same size as wordptr
// on 64-bit systems.
template <class IntType>
class ASMDouble: public Int<IntType>
{
public:
  ASMDouble(const IntType v,
	    const int m = 0) : Int<IntType>(v, m) { }

  void Put(CodeBlock& code_block) const
  {
    const IntType v = this->value;
    
    char w[sizeof(double)];
    memcpy(w, &v, sizeof(double));
    for (u_int i = 0; i < sizeof(double); i++)
      code_block.Put(w[i]);
  }
  
  void Put(CodeBlockLoc loc, CodeBlock& code_block) const
  {
    const IntType v = this->value;
    
    char w[sizeof(double)];
    memcpy(w, &v, sizeof(double));
    for (u_int i = 0; i < sizeof(double); i++)
    {
      code_block.Put(loc++, w[i]);
    }
  }
};

#endif	// ASM_INT_H






