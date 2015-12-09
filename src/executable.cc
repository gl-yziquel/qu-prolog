// executable.cc - Saving and loading a .qx file.
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: executable.cc,v 1.7 2005/03/08 00:35:05 qp Exp $

//
// Format of a .qx file:
//
//	+-----------------------+
//	| code area's magic	| Size of word32.
//	+-----------------------+
//	| code area size	| Size of word32.
//	+-----------------------+
//	| string#		| } SIZE_OF_ADDRESS	}
//	+-----------------------+			}
//	| arity			| } SIZE_OF_NUMBER	}
//	+-----------------------+			} Repeat
//	| size			| } SIZE_OF_OFFSET	} for
//	+-----------------------+			} each
//	|  c			| }			} predicate.
//	|  o			| } size bytes		}
//	|  d			| }			}
//	|  e			| }			}
//	+-----------------------+
//	| code area's top	| Size of word32.
//	+-----------------------+
//	| string table's magic	| Size of word32.
//	+-----------------------+
//	| string table size	| Size of word32.
//	+-----------------------+
//	| String Table		|
//	|	List		|
//	|	of		|
//	|	'\0'		|
//	|	terminated	|
//	|	strings.	|
//	+-----------------------+
//	| string table's top	| Size of word32.
//	+-----------------------+
//	| atom table's magic	| Size of word32.
//	+-----------------------+
//	| atom table size	| Size of word32.
//	+-----------------------+
//	| Atom Table		|
//	|	Offsets		|
//	|	to		|
//	|	the		|
//	|	string		|
//	|	table.		|
//	+-----------------------+
//	| predicate's magic	| Size of word32.
//	+-----------------------+
//	| predicate table size	| Size of word32.
//	+-----------------------+
//	| Predicate Table	|
//	|	Offsets		|
//	|	to		|
//	|	the		|
//	|	code		|
//	|	area.		|
//	+-----------------------+
//

#include <iostream>
#include <fstream>

#include "config.h"

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "executable.h"
#include "int.h"
#include "magic.h"
#include "pred_table.h"

//
// Save the areas to a .qx file.
//
void
SaveExecutable(const char *file, Code& code, AtomTable& atoms,
	       PredTab& predicates)
{
  //
  // Open a file for writing.
  //
  ofstream ostrm(file, ios::out|ios::trunc|ios::binary);
  if (ostrm.fail())
    {
      //
      // Fail to open the file.
      //
      FatalS(__FUNCTION__, "cannot open ", file);
    }
  else
    {
      //
      // Write the version identification.
      //
      IntSave<word32>(ostrm, QU_PROLOG_VERSION);
      
      //
      // Save the areas.
      //
      atoms.saveStringTable(ostrm);
      //save the pointer to the beginning of the sring table
      IntSave<wordptr>(ostrm, (wordptr)(atoms.getStringTableBase()));
      atoms.save(ostrm);
      code.save(ostrm, atoms);
      predicates.save(ostrm);

      //
      // Close the file.
      //
      ostrm.close();
    }
}

//
// Load the areas from a .qx file.
//
void
LoadExecutable(const char *file, Code& code, AtomTable& atoms,
	       PredTab& predicates)
{
  char* old_atom_string_base = NULL;
  //
  // Open a file for reading.
  //
  ifstream istrm(file, ifstream::binary);
  if (istrm.fail())
    {
      FatalS(__FUNCTION__, "cannot open ", file);
    }
  else
    {
      word32 magic = 0;
  
      //
      // Read the version identification.
      //
      if (istrm.good())
	{
	  magic = IntLoad<word32>(istrm);
	}

      if (magic != QU_PROLOG_VERSION)
	{
	  Warning(__FUNCTION__, "incompatible version");
	  return;
	}
      
      //
      // Restore the areas.
      //
      while (istrm.peek() != EOF)
	{
	  magic = IntLoad<word32>(istrm);
	  if (magic == CODE_MAGIC_NUMBER)
            {
              code.load(istrm, atoms);
            }
          else if (magic == PRED_TABLE_MAGIC_NUMBER)
	    {
	      predicates.load(istrm);
	    }
	  else if (magic ==  STRING_TABLE_MAGIC_NUMBER)
	    {
	      atoms.loadStringTable(istrm);
	      old_atom_string_base = (char*)(IntLoad<wordptr>(istrm));
	    }
	  else if (magic ==  ATOM_TABLE_MAGIC_NUMBER)
	    {
	      atoms.load(istrm);
	    }
	  else
	    {
	      ReadFailure(__FUNCTION__,
			  "illegal magic number",
			  file);
	    }
	} 
      //
      // Close the file.
      //
      istrm.close();
      assert(old_atom_string_base != NULL);
      atoms.shiftStringPtrs(old_atom_string_base);
    }
}












