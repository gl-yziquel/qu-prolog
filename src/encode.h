// encode.h - Term encoding and decoding.
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
// $Id: encode.h,v 1.8 2002/12/15 08:23:49 qp Exp $

#ifndef ENCODE_H
#define ENCODE_H

#include "atom_table.h"
#include "objects.h"
#include "defs.h"
// #include "io_qp.h"
#include <vector>

class Heap;
class NameTable;
class Thread;

//
// Map the (meta and object) variables and atoms into unique entries.
//
class	EncodeMap
{
private:
  //
  // The array index cannot be larger than 1 byte because the encoder
  // sends 1 byte.
  // Therefore we consider a vector of tables with the max length of the
  // vector being 256.

  static const int TABLE_MAX	= 256;
  
  vector<Object**>	vector_of_tables;
  int top_table_entry;
  int top_vector_entry;
  
public:
  
  static const int32 NOT_FOUND	=             -1;
  static const word8 ENCODE_REFERENCE =        0;
  static const word8 ENCODE_VARIABLE =         1; 
  static const word8 ENCODE_OB_REFERENCE =     2;
  static const word8 ENCODE_OB_VARIABLE =      3;
  static const word8 ENCODE_LIST =             4;
  static const word8 ENCODE_STRUCTURE =        5; 
  static const word8 ENCODE_QUANTIFIER =       6;
  static const word8 ENCODE_ATOM_REF =         7;
  static const word8 ENCODE_ATOM =             8;
  static const word8 ENCODE_INTEGER =          9;
  static const word8 ENCODE_SUBSTITUTION =     10;
  static const word8 ENCODE_SUBSTITUTION_END = 11;
  static const word8 ENCODE_NAME =             12;
  static const word8 ENCODE_REF_OFFSET =       13;

  //
  // Add.
  //
  void add(Object* c)
  {
    if (top_table_entry < TABLE_MAX)
      {
        vector_of_tables[top_vector_entry-1][top_table_entry++] = c;
      }
    else
      {
	if (top_vector_entry == TABLE_MAX)
	  {
	    cerr << "Not enough space to encode term" << endl;
            exit(1);
          }
	vector_of_tables.push_back(new Object* [TABLE_MAX]);
        top_table_entry = 0;
	vector_of_tables[top_vector_entry++][top_table_entry++] = c;
      }
  }
  
  //
  // Look-up.
  //
  Object* lookUp(word8 i, word8 j) { return(vector_of_tables[i][j]); }

  int32	lookUp(Object* c)
  {
    int i;
    int j;
    
    for (i = 0; i < top_table_entry; i++)
      {
	if (vector_of_tables[top_vector_entry-1][i] == c)
	  {
	    return(TABLE_MAX*(top_vector_entry-1) + i);
	  }
      }
    for (j = 0; j < top_vector_entry-1; j++)
      {
	for (i = 0; i < TABLE_MAX; i++)
	  {
	    if (vector_of_tables[j][i] == c)
	      {
		return(TABLE_MAX*j + i);
	      }
	  }
      }
    return(NOT_FOUND);
  }
  
  Object* getObjectVariableNames(Heap&);
  
  EncodeMap(void)
    {
      vector_of_tables.push_back(new Object* [TABLE_MAX]);
      top_table_entry = 0;
      top_vector_entry = 1;
    }
  ~EncodeMap(void)
    {
      for (int i = 0; i < top_vector_entry; i++)
	{
	  delete [] vector_of_tables[i];
	}
      top_table_entry = 0;
    }
};

//
// Auxiliary class bundles up some useful things.
//
class EncodeBase
{
protected:
  bool success;
  EncodeMap *map;

public:
  EncodeBase(void)
    : map(new EncodeMap())
    {
    }
  ~EncodeBase(void)
    {
      delete map;
    }
  bool Success(void) const { return success; }
};

class EncodeWrite : public EncodeBase {
private:
  //
  // Write a character.
  //
  bool	writeEncodeChar(QPStream&, const word8);
  
  //
  // Encode write a number
  //
  bool writeEncodeNumber(QPStream&, const int32);
    
  //
  // Encode the string and write the result to the stream.
  //
  bool	encodeWriteString(QPStream&, Atom*, AtomTable& atoms);
  
  //
  // Encode the variable name and sent it over.
  //
  bool	encodeWriteVarName(Heap&, QPStream&, Object*, AtomTable&);
  
  //
  // Encode the substitution and write the result to the stream.
  //
  bool encodeWriteSub(Thread&, Heap&, QPStream&, Object*, 
		      AtomTable&, const bool, NameTable&);

  bool encodeWriteTerm(Thread&, Heap&, QPStream&, Object*,
		       AtomTable&, const bool, NameTable&);
public:
  EncodeWrite(Thread& th, Heap& heap, QPStream& stream, Object* term,
	      AtomTable& atoms, const bool remember, NameTable& names)
    {
      success = encodeWriteTerm(th, heap, stream, term,
				atoms, remember, names);
    }
};

class EncodeRead : public EncodeBase {
private:
  char *string;

  //
  // Read a character.
  //
  bool encodeReadChar(QPStream&, word8&);
  
  //
  // Read from a stream and decode back to a string.
  //
  bool encodeReadString(QPStream&, Atom*&, AtomTable&);

  //
  // Read a number.
  //
  bool encodeReadNumber(QPStream&, int32&);

  //
  // Read from a stream and decode back to the substitution.
  //
  bool encodeReadSub(Thread&, Heap&, QPStream&, Object*&,
		     AtomTable&, const bool, NameTable&);

  bool encodeReadTerm(Thread&, Heap&, QPStream&, Object*&,
		      AtomTable&, const bool, NameTable&);
    
public:
  //
  // Read from a stream and decode back to the term.
  //
  EncodeRead(Thread& th,
	     Heap& heap, QPStream& stream,
	     Object*& term,
	     AtomTable& atoms,
	     const bool remember,
	     NameTable& names,
	     Object*& name_list)
    : string(new char[ATOM_LENGTH])
  {
    success = encodeReadTerm(th, heap, stream, term, atoms, remember, names);

    if (success)
      {
	name_list = map->getObjectVariableNames(heap);
      }
  }

  ~EncodeRead(void)
    {
      delete [] string;
    }
};

#endif	// ENCODE_H
