// string_table.cc - The table holds the atoms in C++ string format.  That is,
//		     a sequence of characters terminated by '\0'.  The strings
//		     are stored in the table consecutively.
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
// $Id: string_table.cc,v 1.3 2005/03/08 00:35:15 qp Exp $

#include <string.h>

#include "area_offsets.h"
#include "defs.h"
#include "string_table.h"

//
// Add a new string to the table.
//
char*
StringTab::add(const char *string)
{
  StringLoc   start = allocateBlock(static_cast<word32>(strlen(string) + 1));

  if (start == EMPTY_LOC)
    {
      //
      // Hopefully we should never get here, so we return an
      // "arbitrary" value.  OutOfPage in allocateBlock
      // should recover the program in the appropriate manner.
      //
      return(NULL);
    }
  else
    {
      //
      // Save the string in the string table.
      //
      strcpy(fetchAddr(start), string);
      return(fetchAddr(start));
    }
}











