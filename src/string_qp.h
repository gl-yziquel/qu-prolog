// string_qp.h -
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
// $Id: string_qp.h,v 1.1 2000/12/13 23:10:02 qp Exp $

#ifndef	STRING_QP_H
#define	STRING_QP_H

#include <string.h>

#include <iostream.h>

#include "defs.h"
#include "errors.h"

class String {
private:
  size_t length;
  char *string;

public:
  //
  // Copies the supplied string.
  //
  String(const char *str)
    : length(strlen(str)),
      string(new char[length + 1])
  {
    if (string == NULL)
      {
	OutOfMemory(__FUNCTION__);
      }
    strcpy(string, str);
    string[length] = '\0';
  }

  String(const char *str,
	 const size_t len)
    : length(len),
      string(new char[length + 1])
  {
    if (string == NULL)
      {
	OutOfMemory(__FUNCTION__);
      }
    strncpy(string, str, length);
    string[length] = '\0'; 
  }

  String(const String& str)
    : length(str.Length()),
      string(new char[length + 1])
  {
    if (string == NULL)
      {
	OutOfMemory(__FUNCTION__);
      }
    strncpy(string, str.Str(), length);
    string[length] = '\0';
  }

  String(istream& istrm);

  ~String(void)
  {
    delete [] string;
  }

  size_t Length(void) const { return length; }
  const char *Str(void) const { return string; }

  bool operator==(const String& s) const
  {
    return streq(Str(), s.Str());
  }

  bool operator!=(const String& s) const
  {
    return ! (*this == s);
  }

  bool operator==(const char *s) const
  {
    return streq(Str(), s);
  }

  bool operator!=(const char *s) const
  {
    return ! (*this == s);
  }

  // Write a string to the stream in a form that allows it to be read
  // back readily.
  ostream& Save(ostream&) const;
};

// Print out a String in a form that can be read by a person.
extern ostream& operator<<(ostream&, const String&);

#endif	// STRING_QP_H

