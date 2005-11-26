// int.h - Handling of integers to reduce the problems of moving QuProlog
//	objects between machines of different ``endian-ness''.
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
// ##Copyright##
//
// $Id: int.h,v 1.12 2005/06/29 22:05:30 qp Exp $

#ifndef	INT_H
#define	INT_H

#include "int.h"
#ifdef GCC_VERSION_2
#include <istream.h>
#else
#include <istream>
#endif
#include <limits.h>
//#include <netinet/in.h>

#include "errors.h"
#ifdef WIN32
#define __PRETTY_FUNCTION__ __FUNCDNAME__
#endif

using namespace std;

template <class IntType>
class Int
{
protected:
  IntType value;
  int type;

public:
  virtual size_t SizeOf(void) const { return sizeof(IntType); }

  // v is the value
  // type is an optional type used in the assembler to distinguish
  // between atom ptrs and integers.
  Int(const IntType v, const int m = 0) : value(v), type(m) { }
  
  // Note: If you're passing an istrstream as the istream argument,
  // make sure you've used the istrstream(const char *, int)
  // constructur, otherwise you'll probably get a premature end of stream!
  Int(istream& istrm, const int m = 0) : type(m)
  {
    if (sizeof(IntType) == sizeof(double))
      {
        u_char w[sizeof(double)];
        for (size_t i = 0; i < sizeof(IntType); i++)
          {
            if (istrm.good())
              {
                w[i] = (u_char)istrm.get();
              }
            else
              {
                ReadFailure("integer", "i/o error");
              }
           }
         memcpy(&value, w, sizeof(double));
       }
     else
       {
         IntType v = 0;
    
         for (size_t i = 0; i < sizeof(IntType); i++)
           {
	     u_char c;
	
	     if (istrm.good())
	       {
	         c = (u_char)istrm.get();
	       }
	     else
	       {
	         ReadFailure("integer", "i/o error");
	       }

	     v = (v << 8) | c;
           }
         value = v;
       }
  }
  
  virtual IntType Value(void) const { return value; }
  virtual void Value(const IntType v) { value = v; }

  virtual int Type(void) const { return type; }

  virtual bool operator==(const Int<IntType>& i) const
  {
    return ((Value() == i.Value()) && (Type() == i.Type()));
  }

  virtual ostream& Save(ostream& ostrm) const
    {
      if (sizeof(IntType) == sizeof(double))
          {
            u_char w[sizeof(double)];
            memcpy(w, &value, sizeof(double));
            for (size_t i = 0; i < sizeof(IntType); i++)
              {
                ostrm << w[i];
              }
              return ostrm;
           }
         else
           {
              IntType v = Value();
      
              for (size_t i = sizeof(IntType); i > 0; i--)
	        {
	          const u_char c = (u_char) ((word32)v >> (8 * (i - 1))) & 0xff;
	          ostrm << c;
	        }
      
              return ostrm;
            }
    }
  virtual ~Int() {}
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
    default:
      return 0;
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








