// int.h - Handling of integers to reduce the problems of moving QuProlog
//	objects between machines of different ``endian-ness''.
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
// $Id: int.h,v 1.4 2001/11/21 00:21:14 qp Exp $

#ifndef	INT_H
#define	INT_H

#include <iostream.h>
#include <limits.h>
//#include <netinet/in.h>

#include "errors.h"

template <class IntType>
class Int
{
protected:
  IntType value;
  IntType type;

public:
  virtual size_t SizeOf(void) const { return sizeof(IntType); }

  // v is the value
  // type is an optional type used in the assembler to distinguish
  // between atom ptrs and integers.
  Int(const IntType v, const IntType m = 0) : value(v), type(m) { }
  
  // Note: If you're passing an istrstream as the istream argument,
  // make sure you've used the istrstream(const char *, int)
  // constructur, otherwise you'll probably get a premature end of stream!
  Int(istream& istrm, const IntType m = 0) : type(m)
  {
    IntType v = 0;
    
    for (size_t i = 0; i < sizeof(IntType); i++)
      {
	u_char c;
	
	if (istrm.good())
	  {
	    istrm.get(c);
	  }
	else
	  {
	    ReadFailure("integer", "i/o error");
	  }

	v = (v << 8) | c;
      }
    value = v;
    
#if 0
    switch (sizeof(IntType))
      {
      case 1:
	value = v;
	break;
      case 2:
	value = ntohs(v);
	break;
      case 4:
	value = ntohl(v);
	break;
      }
#endif
  }
  
  virtual IntType Value(void) const { return value; }
  virtual void Value(const IntType v) { value = v; }

  virtual IntType Type(void) const { return type; }

  virtual bool operator==(const Int<IntType>& i) const
  {
    return ((Value() == i.Value()) && (Type() == i.Type()));
  }

  virtual ostream& Save(ostream& ostrm) const
    {
      IntType v = Value();
      
#if 0
      switch (sizeof(IntType))
	{
	case 1:
	  v = masked_value;
	  break;
	case 2:
	  v = htons(masked_value);
	  break;
	case 4:
	  v = htonl(masked_value);
	  break;
	}
#endif
      for (size_t i = sizeof(IntType); i > 0; i--)
	{
	  const u_char c = (u_char) (v >> (8 * (i - 1))) & 0xff;
	  ostrm << c;
	}
      
      return ostrm;
    }
};

// Print ot an Int in a form that can be read by a person.
template <class IntType>
ostream& 
operator<<(ostream& ostrm, const Int<IntType>& i)
{
  return ostrm << i.Value();
}

template <class IntType>
void
IntSave(ostream& ostrm, const IntType value)
{
  if (! ostrm.good())
    {
      SaveFailure(__PRETTY_FUNCTION__, "precondition");
    }

  Int<IntType> i(value);
  i.Save(ostrm);
      
  if (ostrm.fail())
    {
      SaveFailure(__PRETTY_FUNCTION__, "postcondition");
    }
}

template <class IntType>
IntType
IntLoad(istream& istrm)
{
  if (! istrm.good())
    {
      ReadFailure(__PRETTY_FUNCTION__, "precondition");
    }

  Int<IntType> i(istrm);

  if (istrm.fail())
    {
      ReadFailure(__PRETTY_FUNCTION__, "postcondition");
    }

  return i.Value();
}

template <class IntType>
IntType
UnsignedMax(const IntType)
{
  switch (sizeof(IntType))
    {
    case 1:
      return UCHAR_MAX;
      break;
    case 2:
      return USHRT_MAX;
      break;
    case 4:
      return (IntType)UINT_MAX;
      break;
    }
}

template <class IntType>
IntType
SignedMax(const IntType)
{
  switch (sizeof(IntType))
    {
    case 1:
      return CHAR_MAX;
      break;
    case 2:
      return SHRT_MAX;
      break;
    case 4:
      return INT_MAX;
      break;
    }
}

template <class IntType>
IntType
SignedMin(const IntType)
{
  switch (sizeof(IntType))
    {
    case 1:
      return CHAR_MIN;
      break;
    case 2:
      return SHRT_MIN;
      break;
    case 4:
      return INT_MIN;
      break;
    }
}


#endif	// INT_H








