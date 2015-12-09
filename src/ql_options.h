// ql_options.h - Options parsing for ql.
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
// $Id: ql_options.h,v 1.2 2001/11/21 00:21:16 qp Exp $

#ifndef QL_OPTIONS_H
#define QL_OPTIONS_H

#include "defs.h"
#include "option.h"
#include "options.h"

#include "ql_options.h"

// #include "atom_table.h"

class QlOptions: public Options
{
private:
  Option<word32> code_size;
  Option<word32> string_table_size;
  Option<word32> atom_table_size;
  Option<word32> predicate_table_size;
  Option<word32> string_map_size;
  Option<char *> executable_file;

  int num_object_files;

  int object_argc;
  char **object_argv;

public:
  word32 CodeSize(void) const { return code_size.Value(); }
  word32 StringTableSize(void) const { return string_table_size.Value(); }
  word32 PredicateTableSize(void) const { return predicate_table_size.Value(); }
  word32 AtomTableSize(void) const { return atom_table_size.Value(); }
  word32 StringMapSize(void) const { return string_map_size.Value(); }

  const char *ExecutableFile(void) const { return executable_file.Value(); }

  int NumObjectFiles(void) const { return num_object_files; }
  int ObjectArgc(void) const { return object_argc; }
  char **ObjectArgv(void) { return object_argv; }

  QlOptions(int c,		// Incoming argc
	     char **v);		// Incoming argv
};

#endif // QL_OPTIONS_H
