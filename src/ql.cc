// ql.cc - The main program for the Qu-Prolog linker.
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
// $Id: ql.cc,v 1.6 2002/11/10 07:54:53 qp Exp $

#include <stdlib.h>

#include "area_offsets.h"
#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "executable.h"
#include "instructions.h"
#include "obj_index.h"
#include "pred_table.h"
#include "ql.h"
#include "ql_options.h"
#include "string_map.h"

const char *Program = "ql";

//
// Handler for out of memory via new
//
//typedef void (*new_handler) ();
//new_handler set_new_handler(new_handler p) throw();

void noMoreMemory()
{
   cerr << "No more memory available for " << Program << endl;
   abort();
}

//
// A 3-steps Qu-Prolog linker:
//	1. Load the files.
//	2. Resolve the code and symbols.
//	3. Save the result.
//

AtomTable *atoms = NULL;
Code *code = NULL;

int
main(int32 argc, char** argv)
{
  // set the out-of-memory handler
  std::set_new_handler(noMoreMemory);

  QlOptions ql_options(argc, argv);

  if (! ql_options.Valid())
    {
      Usage(Program, ql_options.Usage());
    }

  //
  // Allocate areas in the Qu-Prolog Abstract Machine.
  //
  atoms =
    new AtomTable(ql_options.AtomTableSize(),
		ql_options.StringTableSize(), 0);

  PredTab predicates(atoms, ql_options.PredicateTableSize());
  
  code = new Code(ql_options.CodeSize());
  
  StringMap *string_map =
    new StringMap(ql_options.StringMapSize(), 0); 

  //
  // Step 1 - load all the files in.
  // 
  ObjectIndex **ObjectIndices =
    new (ObjectIndex *)[ql_options.NumObjectFiles()];

  word32 NumQuery = 0;
  for (int i = 0; i < ql_options.NumObjectFiles(); i++)
    {
      ObjectIndices[i] = 
	new ObjectIndex(*code, *atoms, predicates);
      ObjectIndices[i]->loadObjectFile(ql_options.ObjectArgv()[i],
				    NumQuery,
				    *string_map, predicates);
    }

  //
  // Step 2 - Resolve the code and query.
  //
  CodeLoc SizeLoc = (CodeLoc)EMPTY_LOC;
  if (NumQuery > 0)
    {
      //
      // Put in the header for the query.
      //
      Atom* query = atoms->add("$query");
      predicates.addPredicate(atoms, 
			      query,
			      0, PredCode::STATIC_PRED,
			      code->getTop(), code);
      code->pushConstant(query);
      code->pushNumber((word8) 0);
      SizeLoc = code->getTop();
      code->pushOffset((word16) 0);
      code->pushInstruction(ALLOCATE);
      code->pushNumber((word8) 0);
    }
  for (int32 i = 0; i < ql_options.NumObjectFiles(); i++)
    {
      Object* QName;
      ObjectIndices[i]->resolveObject(*string_map, predicates, true, QName);
    }
  if (NumQuery > 0)
    {
      //
      // Put in the trailer for the query.
      //
      code->pushInstruction(DEALLOCATE);
      code->pushInstruction(PROCEED);
      updateOffset(SizeLoc,
		   (word16) (code->getTop()-SizeLoc-Code::SIZE_OF_OFFSET));
    }

  //
  // Step 3 - Save the resolved code to a file.
  //
  SaveExecutable(ql_options.ExecutableFile(),
		 *code, *atoms, predicates);

  exit(EXIT_SUCCESS);
}







