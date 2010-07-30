// ql_options.cc - Options for ql.
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
// $Id: ql_options.cc,v 1.3 2005/03/08 00:35:13 qp Exp $

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>

#ifdef WIN32
#include "WinXGetopt.h" //#include "../win32/src/XGetopt.h"
#endif
#include "ql_options.h"

#include "defaults.h"

//static char *EXECUTABLE_FILE = NULL;

QlOptions::QlOptions(int argc, char **argv)
  : Options("[-d code-size]\n"
	    "\t[-a atom-table-size]\n"
	    "\t[-s string-table-size]\n"
	    "\t[-m string-map-size]\n"
	    "\t[-p predicate-table-size]\n"
	    "\t-o output-file\n"
	    "\tobject-file ... \n"),
    code_size(CODE_SIZE),
    string_table_size(STRING_TABLE_SIZE),
    atom_table_size(ATOM_TABLE_SIZE),
    predicate_table_size(PREDICATE_TABLE_SIZE),
    string_map_size(STRING_MAP_SIZE),
    executable_file(NULL)
{
  int32 c;
  static const char opts[] =  "d:a:s:m:u:M:p:o:";

  //
  // Parse command line options.
  //
#ifdef LINUX
  while ((c = getopt(argc, argv, opts)),
	 (c != -1 && c != '?'))
#else	// LINUX
#ifdef WIN32
  while ((c = getopt(argc, argv, const_cast<TCHAR*>(opts))) != -1)
#else
  while ((c = getopt(argc, argv, opts)) != -1)
#endif	// LINUX
#endif
    {
      switch ((char) c)
	{
	case 'd':
	  code_size.Value(atoi(optarg));
	  break;
	case 'a':
	  atom_table_size.Value(atoi(optarg));
	  break;
	case 's':
	  string_table_size.Value(atoi(optarg));
	  break;
	case 'm':
	  string_map_size.Value(atoi(optarg));
	  break;
	case 'p':
	  predicate_table_size.Value(atoi(optarg));
	  break;
	case 'o':
	  executable_file.Value(optarg);
	  break;
	}
    }

  valid = executable_file.Value() != NULL;

  num_object_files = argc - optind;

  object_argc = optind;
  object_argv = &argv[object_argc];
}

