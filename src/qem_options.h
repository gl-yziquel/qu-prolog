// qem_options.h - Options parsing for qem.
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
// $Id: qem_options.h,v 1.5 2006/04/04 01:56:36 qp Exp $

#ifndef QEM_OPTIONS_H
#define QEM_OPTIONS_H

#include <sys/types.h>

#include "defs.h"
#include "option.h"
#include "options.h"
//#include "string_qp.h"

// #include "atom_table.h"

class QemOptions: public Options
{
private:
  Option<word32> code_size;
  Option<word32> string_table_size;
  Option<word32> predicate_table_size;
  Option<word32> atom_table_size;
  Option<word32> name_table_size;
  Option<word32> heap_size;
  Option<word32> environment_stack_size;
  Option<word32> choice_stack_size;
  Option<word32> binding_trail_size;
  Option<word32> other_trail_size;
  Option<word32> string_map_size;
  Option<word32> ip_table_size;
  Option<word32> scratchpad_size;
  Option<word32> thread_table_size;
  Option<bool> stand_alone;
  Option<char *> qx_file;
  Option<char *> pedro_server;
  Option<u_short> pedro_port;	// Host byte order.
  Option<char *> process_symbol;
  Option<bool> debugging;

  int prolog_argc;
  char **prolog_argv;

public:
  word32 CodeSize(void) const { return code_size.Value(); }
  word32 StringTableSize(void) const { return string_table_size.Value(); }
  word32 PredicateTableSize(void) const { return predicate_table_size.Value(); }
  word32 AtomTableSize(void) const { return atom_table_size.Value(); }
  word32 NameTableSize(void) const { return name_table_size.Value(); }
  word32 IPTableSize(void) const { return ip_table_size.Value(); }
  word32 HeapSize(void) const { return heap_size.Value(); }
  word32 ScratchpadSize(void) const { return scratchpad_size.Value(); }
  word32 EnvironmentStackSize(void) const { return environment_stack_size.Value(); }
  word32 ChoiceStackSize(void) const { return choice_stack_size.Value(); }
  word32 BindingTrailSize(void) const { return binding_trail_size.Value(); }
  word32 OtherTrailSize(void) const { return other_trail_size.Value(); }
  word32 StringMapSize(void) const { return string_map_size.Value(); }
  word32 ThreadTableSize(void) const { return thread_table_size.Value(); }

  char *QxFile(void) const { return qx_file.Value(); }

  bool StandAlone(void) const { return stand_alone.Value(); }

  char *PedroServer(void) const { return pedro_server.Value(); }

  // The result is in host byte order.
  u_short PedroPort(void) const { return pedro_port.Value(); }
  
  char *ProcessSymbol(void) const { return process_symbol.Value(); }

  bool Debugging(void) const { return debugging.Value(); }

  int PrologArgc(void) const { return prolog_argc; }
  char **PrologArgv(void) { return prolog_argv; }

  QemOptions(int c,		// Incoming argc
	     char **v);		// Incoming argv
};

#endif // QEM_OPTIONS_H
