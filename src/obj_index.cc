// obj_index.cc - Object for handling a .qo file during linking.
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
// $Id: obj_index.cc,v 1.8 2003/06/18 04:33:36 qp Exp $

//
// Format of a .qo file
// --------------------
//
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
//	| size	|	} SIZE_OF_ADDRESS
//	+-------+
//	|   n	|	} ignore 1st byte ???????
//	|   u	|	}
//	|   m	|	} size bytes
//	|   b	|	}
//	|   e	|	}
//	|   r	|	}
//	|   s	|	}
//	+-------+
//	| size	|	} SIZE_OF_OFFSET
//	+-------+
//	| q  c	|	}
//	| u  o	|	}
//	| e  d	|	} size bytes
//	| r  e	|	}
//	| y	|	}
//	+-------+
//	|string#|	} SIZE_OF_ADDRESS	}
//	+-------+				}
//	| arity	|	} SIZE_OF_NUMBER	}
//	+-------+				}
//	| size	|	} SIZE_OF_OFFSET	} repeat for each predicate
//	+-------+				}
//	|  c	|	}			}
//	|  o	|	} size bytes		}
//	|  d	|	}			}
//	|  e	|	}			}
//	+-------+
//

#include <iostream>
#include <fstream>

#include "config.h"

#include "area_offsets.h"
#include "atom_table.h"
#include "objects.h"
#include "defs.h"
#include "global.h"
#include "obj_index.h"
#include "instructions.h"
#include "int.h"
#include "pred_table.h"
#include "string_map.h"

//
// Load a .qo file into the memory and record the boundaries of string map,
// and code areas.
// Return whether it is successful or not.
//
bool
ObjectIndex::loadObjectFile(const char *file, word32& NumQuery, 
			    StringMap& string_map,
			    PredTab& predicates)
{
  bool status = true;

  //
  // Record the details before reading.
  //
  name = file;
  stringMap = string_map.getTop();

  codeAreaBase = code.getTop();

  //
  // Open the file for reading.
  //
  ifstream istrm(file);
  if (istrm.fail())
    {
      //
      // Fail to open the file.
      //
      name = NULL;
      WarningS(__FUNCTION__, "cannot open the file ", file);
      istrm.close();
      return(false);
    }
  
  //
  // Read in the strings.
  //
  status &= string_map.loadStrings(istrm, file, atoms);
  
  //
  // Read in the queries.
  //
  const Code::OffsetSizedType QuerySize =
    IntLoad<Code::OffsetSizedType>(istrm);
  
  //
  // Perform loading process only if there is something to load.
  //
  if (QuerySize <= 1)
    {
      if (istrm.good() &&
	  istrm.seekg(QuerySize, ios::cur).fail())
	{
	  ReadFailure(__FUNCTION__, "query", file);
	}
    }
  else
    {
      NumQuery++;
      
      if (istrm.good() &&
	  istrm.seekg(Code::SIZE_OF_INSTRUCTION, ios::cur).fail())
	{
	  ReadFailure(__FUNCTION__, "query", file);
	}

      queryName = IntLoad<Code::PredSizedType>(istrm);
      
      query = true;
      
      if (istrm.good() &&
	  istrm.seekg(Code::SIZE_OF_NUMBER, ios::cur).fail())
	{
	  ReadFailure(__FUNCTION__, "query", file);
	}
    }
  
  //
  // Read in predicates.
  //
  while (istrm.peek() != EOF)
    {
      status &= code.addPredicate(istrm, file, string_map, stringMap,
				  &atoms, predicates, &code);
    }
  codeAreaTop = code.getTop();

  //
  // Close the file.
  //
  istrm.close();
  
  return(status);
}

//
// Resolve the references to atoms and predicates in each object file.
//
void
ObjectIndex::resolveObject(const StringMap& string_map, 
			   PredTab& predicates, bool dump_query_calls,
			   Object*& query_name)
{
  word32	size;
  CodeLoc	start, SizeLoc;

  //
  // Resolve the query by adding a call to the queries in a file.
  //
  query_name = AtomTable::failure;
  if (query)
    {
      // Return the query name
      query_name = string_map.convert(stringMap, queryName);
      // Add calls to code area - for linked files
      if (dump_query_calls)
	{
	  code.pushInstruction(CALL_ADDRESS);
	  code.pushCodeLoc(predicates.getCode(
	    predicates.lookUp(string_map.convert(stringMap, queryName),
			      0, &atoms, &code)).getPredicate(&code));
	  code.pushNumber((word8) 0);
	}
    }
  
  for (start = codeAreaBase;
       start < codeAreaTop;
       start += Code::SIZE_OF_HEADER + size)
    {
      SizeLoc = start + Code::SIZE_OF_ADDRESS + Code::SIZE_OF_NUMBER;
      size = getOffset(SizeLoc);
      //
      // Resolve a predicate.
      //
      code.resolveCode(start + Code::SIZE_OF_HEADER,
		       start + Code::SIZE_OF_HEADER + size,
		       string_map, stringMap, 
		       predicates, &atoms, &code);
    }
}


