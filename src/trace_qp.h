// trace_qp.h - The Qu-Prolog  Abstract Machine tracer
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// email: svrc@cs.uq.oz.au
//
// $Id: trace_qp.h,v 1.4 2005/03/08 00:35:18 qp Exp $

#ifndef TRACE_QP_H
#define TRACE_QP_H

#ifdef QP_DEBUG

#include <stdarg.h>

#include "atom_table.h"
#include "code.h"
#include "environment.h"
#include "choice.h"
#include "heap_qp.h"
#include "pred_table.h"

class Thread;

class Trace {
private:
  word32 trace_level;
  bool trace_init_env;
  bool trace_init_choice;

  heapobject* trace_top_of_heap;

  EnvironmentStack::Environment *trace_env;
  EnvLoc trace_current_environment;
  EnvLoc trace_top_of_env;
 
  Choice *trace_choice;
  ChoiceLoc trace_current_choice_point;
  ChoiceLoc trace_cut_point;
  ChoiceLoc trace_top_of_choice;
  
  void TraceInOut(const word32, const word32, const word32);

  void Trace0(const char *s);
  void Trace1(const char *s, const int32 x);
  void Trace2(const char *s, const int32 x, const int32 y);
  void Trace3(const char *s, const int32 x, const int32 y, const int32 z);
  void Trace4(const char *s, const int32 x, const int32 y, const int32 z,
	      const int32 w);
  void Trace5(const char *s, const int32 x, const int32 y, const int32 z,
	      const int32 w, const int32 u);

  void TraceConst0(AtomTable& atoms, Heap& heap, const char *s, Object* c);
  void TraceConst1(AtomTable& atoms, Heap& heap, const char *s, Object* c,
		   const int32 x);
  void TraceConst2(AtomTable& atoms, Heap& heap, const char *s, Object* c,
		   const int32 x, const int32 y);

  void TraceInt0(const char *s, const int32 n);
  void TraceInt1(const char *s, const int32 n, const int32 x);

  void TraceString1(const char *s, const char *t);
  void TraceString2(const char *s, const char *t, const int32 x);
  void TraceString3(const char *s, const char *t, const int32 x,
		    const int32 y);
 
  void TraceXReg(Thread& th, AtomTable& atoms, const word32 reg);
  void TraceYReg(Thread& th, AtomTable& atoms, const word32 reg);

  void TracePseudoRegs(Thread& th, AtomTable& atoms,
		       const word32, const word32, ...);

  void TracePseudo0(Thread& th, AtomTable& atoms, const word32 n);
  void TracePseudo1(Thread& th, AtomTable& atoms, 
		    const word32 n, const word32 reg1);
  void TracePseudo2(Thread& th, AtomTable& atoms,
		    const word32 n, const word32 reg1, const word32 reg2);
  void TracePseudo3(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1, const word32 reg2,
		    const word32 reg3);
  void TracePseudo4(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1, const word32 reg2,
		    const word32 reg3, const word32 reg4);
  void TracePseudo5(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1, const word32 reg2,
		    const word32 reg3, const word32 reg4,
		    const word32 reg5);

public:
  // Various trace levels
  static const word32 TRACE_INSTR = 	0x00000001;
  static const word32 TRACE_REGS =      0x00000002;
  static const word32 TRACE_BACKTRACK =	0x00000004;
  static const word32 TRACE_ENV = 	0x00000008;
  static const word32 TRACE_CHOICE =	0x00000010;
  static const word32 TRACE_CUT =	0x00000020;
  static const word32 TRACE_HEAP = 	0x00000040;

  // For convenience.
  // trace_dest_regs isn't included because we don't want to go poking about
  // in potentially uninitialised registers.
  static const word32 TRACE_ALL = 		(TRACE_INSTR |
#if 0
						 TRACE_REGS |
#endif
						 TRACE_BACKTRACK |
						 TRACE_ENV |
						 TRACE_CHOICE |
						 TRACE_CUT |
						 TRACE_HEAP);

  Trace(const word32 level);
 
  word32& TraceLevel(void) { return trace_level; }

  void SetTraceFlag(const word32 flag) { trace_level |= flag; }
  void ClearTraceFlag(const word32 flag) { trace_level &= ~flag; }
  bool TestTraceFlag(const word32 flag) { return trace_level & flag; }

  void TraceStart(Thread& th);
 
  void TraceInstr(Thread& th,
		  AtomTable& atoms,
		  Code& code,
		  PredTab& predicates,
		  const CodeLoc);
 
  void TraceBacktrack(Thread& th, const CodeLoc);
 
  void TraceEnd(Thread& th);
};

#endif // QP_DEBUG
#endif	// TRACE_QP_H



