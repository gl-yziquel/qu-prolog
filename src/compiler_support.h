// compiler_support.h -
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
// $Id: compiler_support.h,v 1.9 2005/11/26 23:34:29 qp Exp $

#ifndef	COMPILER_SUPPORT_H
#define	COMPILER_SUPPORT_H

#include "defs.h"
#include "errors.h"
// #include "io_qp.h"

#define WARRAYSIZE 8000
#define REGISTERSIZE 800

extern const char *Program;

class QPStream;

//
// This class is used for storing the results of phases of the compiler.
// The entries are pointers to heap objects representing "instructions".
//
class WordArray
{
private:
  word32    *base;
  int       size;
  int       last;

public:
  explicit WordArray(int s)
    { 
      base = new word32[s];
      size = s; 
      last = 0;
    }

  virtual ~WordArray(void)
    { 
      if (base != NULL)
	{
	  delete [] base;
	}
    }

  inline void addEntry(word32 entry)
    {
      if (last + 1 >= size)
	{
	  Fatal(__FUNCTION__, "Out of compiler array memory");
	}
      base[last++] = entry;
    }

  inline word32 *Entries(void) { return base; }

  inline int lastEntry(void) { return last; }

  inline void resetLast(int l)
    {
      assert(l >= 0);
      assert(l < size);
      last = l;
    }

};

//
// This class is used to keep track of the lifetimes of X registers.
//
class xreglife
{
private:
  class llist
  {
  private:
    int start;
    int end;
    llist* next;

  public:
    llist(void) { start = 0; end = 0; next = NULL; }
    ~llist(void) {}

    int& getStart(void) { return start; }
    int& getEnd(void) { return end; }
    llist*& getNext(void) { return next; }
  };

  llist** reginfo;
  int size;

public:
  typedef llist* llistptr;
  explicit xreglife(int s) 
    {      
      reginfo = new llistptr[s];

      for (int i = 0; i < s; i++)
	{
	  reginfo[i] = NULL;
	}
      size = s; 
    }
  ~xreglife(void)
    {
      for (int i = 0; i < size; i++)
	{
	  llist* list = reginfo[i];
	  while (list != NULL)
	    {
	      llist* next = list->getNext();
	      delete list;
	      list = next;
	    }
	}
      delete [] reginfo;
    }

void add(int i, int s)
    {
      if (i > size)
	{
	  Fatal(__FUNCTION__, "Out of bounds in xreglife");
	}
      if (reginfo[i] == NULL)
	{
	  reginfo[i] = new llist;
	  reginfo[i]->getStart() = s;
	}
      else
	{
	  llist* next = reginfo[i];
	  while (next->getEnd() != 0 && next->getNext() != NULL)
	    {
	      next = next->getNext();
	    }
	  if (next->getEnd() == 0)
	    {
	      next->getEnd() = s;
	    }
	  else
	    {
	      llist* n = new llist;
	      n->getStart() = s;
	      next->getNext() = n;
	    }
	}
    }


  bool addRange(int i, int s, int e);
    
#if 0
  void display(void)
    {
      for (int i = 0; i < size; i++)
	{
	  if (reginfo[i] != NULL)
	    {
	      cerr << "xreg[" << i << "]: ";

	      for (llist* next = reginfo[i]; 
		   next != NULL; next = next->getNext())
		{
		  cerr << " [" << next->getStart() << ", " << next->getEnd()
		       << "]";
		}
	      cerr << endl;
	    }
	}
    }
#endif // 0
};

#if 0
class range
{
private:
  int start;
  int end;
public:
  range(int s, int e) { start = s; end = e; }
  ~range(void) { }
public:
  int& getStart(void) { return start; }
  int& getEnd(void) { return end; }
};
#endif // 0

void build_lifetime(WordArray&, xreglife&, WordArray&); 

void updateLife(WordArray&, Object*);

bool is_xreg(Object*, int&);

bool is_yreg(Object*);

int yreg_num(Object*);

bool equal_regs(Object*, Object*);

void prefer_registers_aux(WordArray&, xreglife&, WordArray&, int, int, int);

void prefer_registers(WordArray&, xreglife&, WordArray&, int);

void init_live(Object**);
void make_live(Object*, Object*, Object**);
void make_dead(Object*, Object**);
bool is_live(Object*, Object*, Object**);

bool any_assoc_putset(Object*, int, WordArray&);

bool alloc_needed(Object*);

int psi_reg(Object*);

void writeCAtom(char*, QPStream*);

void writeInstructions(WordArray&, QPStream*);

word8* dumpInstructions(WordArray&);



#endif	// COMPILER_SUPPORT_H








