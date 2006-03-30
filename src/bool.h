// bool.h - Class for handling booleans. Mainly useful for when they have
//	to bre read or written.
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
// $Id: bool.h,v 1.4 2006/01/31 23:17:49 qp Exp $

#ifndef	BOOL_H
#define	BOOL_H

#include <iostream>

#include "int.h"

class Bool: public Int<bool>
{
public:
  explicit Bool(const bool b) : Int<bool>(b) { }
  explicit Bool(istream& istrm) : Int<bool>(istrm) { }
};

// Print out a Bool in a form that can be read by a person.
extern ostream& operator<<(ostream&, const Bool&);

inline ostream&
BoolWrite(ostream& ostrm, const bool b)
{
  if (! ostrm.good())
    {
      SaveFailure(__FUNCTION__, "bool write");
    }

  const Bool B(b);
  B.Save(ostrm);

  if (ostrm.fail())
    {
      SaveFailure(__FUNCTION__, "bool write");
    }

  return ostrm;
}

#endif	// BOOL_H


