// qem_options.cc - Options for qem.
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
// $Id: qem_options.cc,v 1.5 2006/04/04 01:56:36 qp Exp $

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>

#ifdef WIN32
#include "../win32/src/XGetopt.h"
#endif
#include "qem_options.h"
#include "tcp_qp.h"

#include "defaults.h"


QemOptions::QemOptions(int argc, char **argv)
  : Options("[-d code-size]\n"
	    "\t[-p predicate-table-size]\n"
	    "\t[-s string-table-size]\n"
	    "\t[-m string-map-size]\n"
	    "\t[-a atom-table-size]\n"
	    "\t[-B binding-trail-size]\n"
	    "\t[-O other-trail-size]\n"
	    "\t[-i ip-table-size]\n"
	    "\t[-n name-table-size]\n"
	    "\t[-C choice-stack-size]\n"
	    "\t[-e environment-stack-size]\n"
	    "\t[-h heap-size]\n"
	    "\t[-H scratchpad-size]\n"
	    "\t[-z thread-table-size]\n"
	    "\t[-N pedro-server-name]\n"
	    "\t[-P pedro-server-port]\n"
	    "\t[-A process-symbol]\n"
            "\t[-g initial-goal]\n"
	    "\t[-L]\n"	// Standalone
	    "\t[-X]\n"	// QuAM level debugging turned on.
	    "\t-Q qx-file\n"),
    code_size(CODE_SIZE),
    string_table_size(STRING_TABLE_SIZE),
    predicate_table_size(PREDICATE_TABLE_SIZE),
    atom_table_size(ATOM_TABLE_SIZE),
    name_table_size(NAME_TABLE_SIZE),
    heap_size(HEAP_SIZE),
    environment_stack_size(ENVIRONMENT_STACK_SIZE),
    choice_stack_size(CHOICE_STACK_SIZE),
    binding_trail_size(BINDING_TRAIL_SIZE),  
    other_trail_size(OTHER_TRAIL_SIZE),   
    string_map_size(STRING_MAP_SIZE),
    ip_table_size(IP_TABLE_SIZE),
    scratchpad_size(SCRATCHPAD_SIZE),
    thread_table_size(THREAD_TABLE_SIZE),
    stand_alone(STAND_ALONE),
    qx_file(QX_FILE),
    pedro_server(NULL),
    pedro_port(PEDRO_PORT),
    process_symbol(PROCESS_SYMBOL),
    initial_goal(INITIAL_GOAL),
    debugging(DEBUGGING)
{
  int32 c;

  static const char *opts =  "d:p:s:m:a:B:O:i:n:C:e:h:H:Q:z:N:P:A:g:LX";

  char* lh = new char[10];
  strcpy(lh, "localhost");
  pedro_server.Value(lh);

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
	case 'p':
	  predicate_table_size.Value(atoi(optarg));
	  break;
	case 's':
	  string_table_size.Value(atoi(optarg));
	  break;
	case 'm':
	  string_map_size.Value(atoi(optarg));
	  break;
	case 'a':
	  atom_table_size.Value(atoi(optarg));
	  break;
	case 'B':
	  binding_trail_size.Value(atoi(optarg));
	  break;
	case 'O':
	  other_trail_size.Value(atoi(optarg));
	  break;
	case 'n':
	  name_table_size.Value(atoi(optarg));
	  break;
	case 'i':
	  ip_table_size.Value(atoi(optarg));
	  break;
	case 'C':
	  choice_stack_size.Value(atoi(optarg));
	  break;
	case 'e':
	  environment_stack_size.Value(atoi(optarg));
	  break;
	case 'h':
	  heap_size.Value(atoi(optarg));
	  break;
	case 'H':
	  scratchpad_size.Value(atoi(optarg));
	  break;
	case 'Q':
	  qx_file.Value(optarg);
	  break;
	case 'z':
	  thread_table_size.Value(atoi(optarg));
	  break;
	case 'N':
	  // Will override earlier setting of standalone flag
	  pedro_server.Value(optarg);
	  stand_alone.Value(false);
	  break;
	case 'P':
	  pedro_port.Value(atoi(optarg));
	  break;
	case 'A':
	  process_symbol.Value(optarg);
	  break;
	case 'g':
	  initial_goal.Value(optarg);
	  break;
	case 'L':
	  // Will override earlier setting of name server name
	  stand_alone.Value(true);
	  break;
	case 'X':
	  debugging.Value(true);
	  break;
	}
    }
  
  //
  // Set up Prolog command line arguments.
  //
  prolog_argc = argc - optind;
  prolog_argv = argv + optind;

  valid = qx_file.Value() != NULL;
}




