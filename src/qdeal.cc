//   main.cc - The main program for the Qu-Prolog deassembler / delinker.
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
// $Id: qdeal.cc,v 1.4 2002/06/30 05:30:02 qp Exp $

#include <stdlib.h>
#include <iostream.h>
#include <string.h>

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "pred_table.h"
#include "string_map.h"
#include "obj_index.h"
#include "executable.h"
#include "delink.h"
#include "qdeal.h"
#include "qdeal_options.h"

const char *Program = "qdeal";

AtomTable *atoms = NULL;
Code *code = NULL;

// a 2-step Qu-Prolog De-linker:
//  	1. Load the .qo  or .qx file
//	2. deassemble and output this file.
//
int
main(int32 argc, char** argv)
{
  QdealOptions *qdeal_options = new QdealOptions(argc, argv);
  if (qdeal_options == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  if (!qdeal_options->Valid())
    {
      Usage(Program, qdeal_options->Usage());
    }

  atoms =
    new AtomTable(qdeal_options->AtomTableSize(),
		qdeal_options->StringTableSize(), 0);
  if (atoms == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  PredTab *predicates =
    new PredTab(atoms, qdeal_options->PredicateTableSize());
  if (predicates == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  code = new Code(qdeal_options->CodeSize());
  if (code == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  StringMap *string_map =
    new StringMap(qdeal_options->StringMapSize(), 0); 
  if (string_map == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  //
  // Step one - Load in the file.
  //
  const CodeLoc codeAreaBase = code->getTop();

  //
  // Determine which type of file we are inputting, ie .qx or .qo, and
  // load that file using approriate load function.
  //
  bool PrintAddr = false;
  const char *qoorqs = strrchr(qdeal_options->QxFile(), '.');
  if (qoorqs != NULL)
    {
      if (streq(qoorqs, ".qx")) 
	{
	  LoadExecutable(qdeal_options->QxFile(),
			 *code, *atoms, *predicates); 
	  PrintAddr = true;
	}
      else if (streq(qoorqs,".qo")) 
	{
	  word32 NumQuery = 0;
	  ObjectIndex ObjIndex(*code, *atoms, *predicates);
	  ObjIndex.loadObjectFile(qdeal_options->QxFile(),
				  NumQuery, *string_map, *predicates);
	  Object* QName;
	  ObjIndex.resolveObject(*string_map, *predicates, false, QName);
	  PrintAddr = false;
	}
      else 
	{
	  Fatal(__FUNCTION__, "%s is not a .qo or .qx file",
		qdeal_options->QxFile());
	}
    }
  else 
    {
      Fatal(__FUNCTION__, "%s is not a .qo or .qx file",
	    qdeal_options->QxFile());
    }

  //
  // Get size of code area.
  // 
  const CodeLoc codeAreaTop = code->getTop();

  //
  // Step Two - Delink the code and output to standard output.
  //
  deassembler(*code, *atoms, *predicates,
	      codeAreaBase, codeAreaTop,
	      PrintAddr);
}

