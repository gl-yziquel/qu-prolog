// atom_table.cc - The atom table is a hash table providing a fast search
//                through the string table.
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
// $Id: atom_table.cc,v 1.3 2005/03/28 06:19:13 qp Exp $

#include "area_offsets.h"
#include "objects.h"
#include "defs.h"
#include "atom_table.h"
#include "string_table.h"

//
// Pre-assigned atoms.
//
Atom *AtomTable::nil;
Atom *AtomTable::cons;
Atom *AtomTable::comma;
Atom *AtomTable::success;
Atom *AtomTable::failure;

Atom *AtomTable::unsure;
Atom *AtomTable::colon;
Atom *AtomTable::dollar;

Atom *AtomTable::equal;
Atom *AtomTable::nfi;
Atom *AtomTable::checkBinder;
Atom *AtomTable::delays;
Atom *AtomTable::equalVar;
Atom *AtomTable::equalObjectVariable;
Atom *AtomTable::arrayIP;
Atom *AtomTable::neckcut;
Atom *AtomTable::cut_atom;
Atom *AtomTable::delayneckcut;
Atom *AtomTable::psi0_call;
Atom *AtomTable::psi1_call;
Atom *AtomTable::psi2_call;
Atom *AtomTable::psi3_call;
Atom *AtomTable::psi4_call;
Atom *AtomTable::psi5_call;
Atom *AtomTable::psi0_resume;
Atom *AtomTable::psi1_resume;
Atom *AtomTable::psi2_resume;
Atom *AtomTable::psi3_resume;
Atom *AtomTable::psi4_resume;
Atom *AtomTable::psi5_resume;
Atom *AtomTable::psi0_error_handler;
Atom *AtomTable::psi1_error_handler;
Atom *AtomTable::psi2_error_handler;
Atom *AtomTable::psi3_error_handler;
Atom *AtomTable::psi4_error_handler;
Atom *AtomTable::psi5_error_handler;

Atom *AtomTable:: unify_ref;
Atom *AtomTable:: xreg;
Atom *AtomTable:: yreg;
Atom *AtomTable:: put;
Atom *AtomTable:: get;
Atom *AtomTable:: meta;
Atom *AtomTable:: variable;
Atom *AtomTable:: value;
Atom *AtomTable:: substitution;
Atom *AtomTable:: empty_substitution;
Atom *AtomTable:: sub_term;
Atom *AtomTable:: call_pred;
Atom *AtomTable:: execute_pred;
Atom *AtomTable:: ccut;
Atom *AtomTable:: cneck_cut;
Atom *AtomTable:: cut_ancestor;
Atom *AtomTable:: allocate;
Atom *AtomTable:: deallocate;
Atom *AtomTable:: do_cleanup;
Atom *AtomTable:: cproceed;
Atom *AtomTable:: get_level_ancestor;
Atom *AtomTable:: get_level;
Atom *AtomTable:: structure;
Atom *AtomTable:: structure_frame;
Atom *AtomTable:: list;
Atom *AtomTable:: quantifier;
Atom *AtomTable:: constant;
Atom *AtomTable:: noarg;
Atom *AtomTable:: object;
Atom *AtomTable:: unify;
Atom *AtomTable:: set;
Atom *AtomTable:: piarg;
Atom *AtomTable:: pieq;
Atom *AtomTable:: psi_life;
Atom *AtomTable:: cpseudo_instr0;
Atom *AtomTable:: cpseudo_instr1;
Atom *AtomTable:: cpseudo_instr2;
Atom *AtomTable:: cpseudo_instr3;
Atom *AtomTable:: cpseudo_instr4;
Atom *AtomTable:: cpseudo_instr5;
Atom *AtomTable:: start;



Atom *AtomTable::plus;
Atom *AtomTable::minus;
Atom *AtomTable::multiply;
Atom *AtomTable::divide;
Atom *AtomTable::intdivide;
Atom *AtomTable::mod;
Atom *AtomTable::power;
Atom *AtomTable::bitwiseand;
Atom *AtomTable::bitwiseor;
Atom *AtomTable::shiftl;
Atom *AtomTable::shiftr;
Atom *AtomTable::bitneg;
Atom *AtomTable::pi;
Atom *AtomTable::e;
Atom *AtomTable::abs;
Atom *AtomTable::round;
Atom *AtomTable::floor;
Atom *AtomTable::ceiling;
Atom *AtomTable::sqrt;
Atom *AtomTable::sin;
Atom *AtomTable::cos;
Atom *AtomTable::tan;
Atom *AtomTable::asin;
Atom *AtomTable::acos;
Atom *AtomTable::atan;
Atom *AtomTable::log;


Atom *AtomTable::stream_user;
Atom *AtomTable::stream_stdin;
Atom *AtomTable::stream_stdout;
Atom *AtomTable::stream_stderr;
Atom *AtomTable::stream_user_input;
Atom *AtomTable::stream_user_output;
Atom *AtomTable::stream_user_error;

Atom *AtomTable::block;
Atom *AtomTable::poll;

Atom *AtomTable::anonymous;

Atom *AtomTable::ipc_send_options;
Atom *AtomTable::tcp_recv_options;
Atom *AtomTable::thread_defaults;
Atom *AtomTable::thread_wait_conditions;

Atom *AtomTable::undefined_predicate;
Atom *AtomTable::recoverable;
Atom *AtomTable::retry_woken_delays;
Atom *AtomTable::exception;
Atom *AtomTable::call_exception;
Atom *AtomTable::default_atom;
Atom *AtomTable::signal_exception;
Atom *AtomTable::qup_shorten;
Atom *AtomTable::query;

Atom *AtomTable::debug_write;

// TCP
Atom *AtomTable::inaddr_any;

Atom *AtomTable::sock_stream;
Atom *AtomTable::sock_dgram;
Atom *AtomTable::sock_raw;
Atom *AtomTable::ipproto_ip;
Atom *AtomTable::ipproto_udp;
Atom *AtomTable::ipproto_tcp;
Atom *AtomTable::ipproto_icmp;
Atom *AtomTable::ipproto_raw;
Atom *AtomTable::so_debug;
Atom *AtomTable::so_reuseaddr;
Atom *AtomTable::so_keepalive;
Atom *AtomTable::so_dontroute;
Atom *AtomTable::so_broadcast;
Atom *AtomTable::so_oobinline;
Atom *AtomTable::so_sndbuf;
Atom *AtomTable::so_rcvbuf;
Atom *AtomTable::so_sndtimeo;
Atom *AtomTable::so_rcvtimeo;
Atom *AtomTable::so_error;
Atom *AtomTable::so_type;
Atom *AtomTable::poll_read;
Atom *AtomTable::poll_write;

// Tracing
Atom *AtomTable::trace_instr;
Atom *AtomTable::trace_backtrack;
Atom *AtomTable::trace_env;
Atom *AtomTable::trace_choice;
Atom *AtomTable::trace_cut;
Atom *AtomTable::trace_heap;
Atom *AtomTable::trace_regs;
Atom *AtomTable::trace_all;

// Locking
Atom *AtomTable::code;
Atom *AtomTable::record_db;

// ICM
Atom *AtomTable::icm_handle;

//
// Using the string to hash into the atom table.
// No idea of this algorithm.  It is from Ross.
//
AtomLoc
AtomKey::hashFn(void) const
{
  const	char	*s;
  word32	value = 0;
  
  s = string;
  while (*s != '\0')
    {
      value *= 167;
      value ^= *s++;
    }
  return(value);
}

//
// Add a new entry to the atom table if it does not exist.  Otherwise, return
// the existing one.
//
Atom *
AtomTable::add(const char *string)
{
  AtomKey key(string, &stringTable);
  
  const AtomLoc index = search(key);
  Atom& entry = getEntry(index);
  if (entry.isEmpty())
    {
      //
      // Add the new entry.
      //
      entry.setStringTableLoc(stringTable.add(string));
    }

  //
  // Return the location of string in the atom table.
  // 
  return(&entry);
}

//
// Get the atom from the offset
//
Atom* 
AtomTable::getAtom(const AtomLoc loc)
{
  Atom& a = getEntry(loc);
  return(&a);
}


bool
AtomTable::atomToBool(Object* c)
{
  return(c == success);
}







