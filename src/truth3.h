// truth3.h - 3 valued truth manipulation.
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: truth3.h,v 1.2 2005/06/29 22:05:34 qp Exp $

#ifndef	TRUTH3_H
#define	TRUTH3_H

class truth3
{
public:
  //
  // These are not for general direct use.
  //
  enum	truth3type	{ UNSURE = -1, NO, YES }	value;

  truth3(void) { value = NO; }
  truth3(const truth3type val) { value = val; }
  truth3(const bool b) { value = b ? YES : NO; }
  
  //
  // Overload logical operators.
  //
  truth3 operator&&(const truth3& other) const
  {
    if (value == NO || other.value == NO)
      {
	return(NO);
      }
    else if (value == YES && other.value == YES)
      {
	return(YES);
      }
    else
      {
	return(UNSURE);
      }
    return(NO);
  }
  truth3 operator||(const truth3& other) const
  {
    if (value == NO && other.value == NO)
      {
	return(NO);
      }
    else if (value == YES || other.value == YES)
      {
	return(YES);
      }
    else
      {
	return(UNSURE);
      }
    return(NO);
  }
  truth3 operator!(void) const
  {
    truth3 result = UNSURE;
    
    switch (value)
      {
      case UNSURE:
	result = UNSURE;
	break;
      case NO:
	result = YES;
	break;
      case YES:
	result = NO;
	break;
      }
    
    return result;
  }
  bool operator==(const truth3& other) const
  { return(value == other.value); }
  bool operator!=(const truth3& other) const
  { return(! (*this == other)); }
};


#endif	// TRUTH3_H
