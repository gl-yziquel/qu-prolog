// string_map.cc - Used for relocation of atoms and numbers during loading.
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
// $Id: string_map.cc,v 1.5 2005/03/08 00:35:15 qp Exp $

#include <iostream>
#include <string.h>
#include <stdio.h>

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "int.h"
#include "string_map.h"

//
// Read in the strings.
// Return whether it is successful or not.
//
// The .qo file format is:
//	+-------+
//	| size	|	} SIZE_OF_ADDRESS
//	+-------+
//	|   s	|	}
//	|   t	|	}
//	|   r	|	} size bytes
//	|   i	|	}
//	|   n	|	}
//	|   g	|	}
//	|   s	|	}
//	+-------+
//
bool
StringMap::loadStrings(istream& istrm, const char *file, AtomTable& atoms)
{
  for (Code::AddressSizedType StringSize = 
	 IntLoad<Code::AddressSizedType>(istrm);
       StringSize > 0;
       )
    {
      char string[ATOM_LENGTH];

      //
      // Get string.
      //
      if (istrm.good() && istrm.getline(string, ATOM_LENGTH, '\0').fail())
	{
	  WrongFileFormat(__FUNCTION__, file);
	  return(false);
	}

      //
      // Add to atom table and string map.
      //
      pushElement(atoms.add(string));

      StringSize -= static_cast<Code::AddressSizedType>(strlen(string) + 1);
    }
  
  return(true);
}

bool
NumberMap::loadNumbers(istream& istrm, Heap& number_heap)
{
  for (Code::AddressSizedType size = 
	 IntLoad<Code::AddressSizedType>(istrm);
       size > 0; size--)
    {
      int32 i = IntLoad<Code::AddressSizedType>(istrm);
      pushElement(number_heap.newNumber(i));
      
    }
  return(true);
}









