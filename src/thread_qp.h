// thread_qp.h - Define the components of a thread.
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
// $Id: thread_qp.h,v 1.5 2001/12/17 04:27:34 qp Exp $

#ifndef	THREAD_QP_H
#define	THREAD_QP_H

#include <iostream.h>
#include <list>
#include <stdarg.h>

#include "area_offsets.h"
#include "block.h"
#include "objects.h"
#include "choice.h"
#include "compiler_support.h"
//#include "decompile.h"
#include "defs.h"
#include "encode.h"
#include "environment.h"
#include "error_value.h"
#include "foreign_handle.h"
#include "heap_qp.h"
#include "heap_buffer.h"
#include "icm_environment.h"
#include "indexing.h"
#include "name_table.h"
#include "obj_index.h"
#include "pile.h"
//#include "pred_table.h"
#include "prolog_value.h"
#include "thread_condition.h"
#include "thread_info.h"
#include "thread_options.h"
#include "trace_qp.h"
#include "trail.h"

//
// Was the thread interrupted? If so, what sort of interruption was
// it?
//
class RestartStatus: public Status <word8>
{
private:
  static const word8 RESTART_BLOCK	= 0x01;
  static const word8 RESTART_SIGNAL	= 0x02;
  static const word8 RESTART_TIMESLICE	= 0x04;
public:
  bool testRestartBlock(void) const { return test(RESTART_BLOCK); }
  bool testRestartSignal(void) const { return test(RESTART_SIGNAL); }
  bool testRestartTimeslice(void) const { return test(RESTART_TIMESLICE); }
  
  bool IsRestart(void) const
  {
    return (testRestartBlock() ||
	    testRestartSignal() ||
	    testRestartTimeslice());
  }
  
  void setRestartBlock(void) { set(RESTART_BLOCK); }
  void setRestartSignal(void) { set(RESTART_SIGNAL); }
  void setRestartTimeslice(void) { set(RESTART_TIMESLICE); }
  
  void resetRestartBlock(void) { reset(RESTART_BLOCK); }
  void resetRestartSignal(void) { reset(RESTART_SIGNAL); }
  void resetRestartTimeslice(void) { reset(RESTART_TIMESLICE); }
  
  void Clear(void) { clear(); }
};

//
// Qu-Prolog thread
//
class Thread : public ThreadCondition
{
  // The Trace class may gaze into a Thread's soul.
  friend class Trace;
  friend class Scheduler;

private:
  CodeLoc programCounter;		// PC
  BlockStatus block_status;
  RestartStatus restart_status;

  void InitThread(void);

  // Execution environment information.
  ThreadInfo thread_info;

  static const word32 maxXRegs = NUMBER_X_REGISTERS;
  
  Object* X[NUMBER_X_REGISTERS];		// X registers
  Object* SavedX[NUMBER_X_REGISTERS];	// Saved value of X registers
  
  PushDownStack	pushDownStack;
  
  bool localAreas;
  NameTable& names;
  IPTable& ipTable;

  HeapBufferManager& buffers;
  Heap& heap;
  Heap& scratchpad;

  BindingTrail& bindingTrail;
  UpdatableObjectTrail& objectTrail;
  UpdatableObjectTrail& ipTrail;
  UpdatableTagTrail& tagTrail;
  RefTrail& refTrail;
  
  CodeLoc continuationInstr;	// CP
  EnvLoc currentEnvironment;	// CE
  
  EnvironmentStack envStack;

  ChoiceLoc currentChoicePoint;		// B
  ChoiceLoc cutPoint;			// B0
  ChoiceLoc catchPoint;			// exception

  ChoiceStack choiceStack;

  // Messages that are pending.
  list<ICMMessage *> icm_queue;

  // Number of active ICM queue scans in progress. 
  size_t icm_level;

  CodeLoc savedPC;

  // Counts of numbers of sorts of variables created.
  word32	metaCounter;
  word32	objectCounter;

  //
  // For manipulating strings on the fly.
  //
  // XXX It's definitely possible to use the same buffer for 
  // XXX strings, io and encoding BUT each of these sets of operations
  // XXX operate under different constraints e.g. maximum length of
  // XXX strings. It probably isn't a good idea to merge their uses.
  //
  char atom_buf1[ATOM_LENGTH];
  char atom_buf2[ATOM_LENGTH];

  //
  // I/O (including TCP).
  //
  // XXX It's definitely possible to use the same buffer for 
  // XXX strings, io and encoding BUT each of these sets of operations
  // XXX operate under different constraints e.g. maximum length of
  // XXX strings. It probably isn't a good idea to merge their uses.
  //
  char io_buf[IO_BUF_LENGTH];

  // Foreign function interface file.
  Handle *ForeignFile;

  // Used for passing back information about failed pseudo-instructions.
  ErrorValue error_value;
  word32 error_arg;

  ThreadStatus status;

  // Trace class used for following the actions of the WAM.
  Trace trace;

  // Save the X registers in SavedX
  void SaveXRegisters(void);

  // Restore the X registers in SavedX
  void RestoreXRegisters(void);

public:
  RefTrail& getRefTrail(void) { return refTrail; }

  // Pending IPC messages.
  list<ICMMessage *>& ICMQueue(void) { return icm_queue; }

  // Get the IP table
  IPTable& getIPTable(void) { return ipTable; }
  
  // Status of this thread.
  ThreadStatus& getStatus(void) { return status; }

  char* getAtomBuf1(void) { return atom_buf1; }

  // Thread identification, etc.
  ThreadInfo& TInfo(void) { return thread_info; }
  const ThreadInfo& InspectTInfo(void) const { return thread_info; }

  // Trace information.
  Trace& GetTrace(void) { return trace; }

  // Save the state of the heap and trails for choice pointes.
  void saveHeapAndTrails(HeapAndTrailsChoice& state)
    {
      state.save(heap.getTop(), bindingTrail.getTop(), objectTrail.getTop(),
		 ipTrail.getTop(), tagTrail.getTop(), refTrail.getTop());
      heap.setSavedTop(heap.getTop());
    }


  // Backtrack - reset tops of heap and trails and backtrack trails.
  void backtrackTo(const HeapAndTrailsChoice& state)
    {
      heapobject* savedHT;
      TrailLoc savedBindingTrailTop;
      TrailLoc savedObjectTrailTop;
      TrailLoc savedIPTrailTop;
      TrailLoc savedTagTrailTop;
      TrailLoc savedRefTrailTop;

      state.restore(savedHT, savedBindingTrailTop, 
		    savedObjectTrailTop,
		    savedIPTrailTop, savedTagTrailTop,
                    savedRefTrailTop);
      bindingTrail.backtrackTo(savedBindingTrailTop);
      objectTrail.backtrackTo(savedObjectTrailTop);
      ipTrail.backtrackTo(savedIPTrailTop);
      tagTrail.backtrackTo(savedTagTrailTop);
      refTrail.backtrackTo(savedRefTrailTop);
      heap.setSavedTop(savedHT);
      heap.setTop(savedHT);
    }

  void changeTimeslice(bool makeSet);

  void backtrackTo(Choice* cp)
  {
    word32 i;
    
    ThreadStatus& curr_status = getStatus();
    if (cp->status.testTimeslicing() != curr_status.testTimeslicing())
      {
	changeTimeslice(cp->status.testTimeslicing());
      }
    curr_status = cp->status;
    continuationInstr = cp->continuationInstr;
    backtrackTo(cp->heapAndTrailsState);
    currentEnvironment = cp->currentEnvironment;
    
    envStack.setTop(cp->envStackTop);
    
    metaCounter = cp->metaCounter;
    objectCounter = cp->objectCounter;
    
    word32 nargs = cp->NumArgs;
    for (i = 0; i < nargs; i++)
      {
	X[i] = cp->X[i];
      }
  }

  // Tidy up the trails.
  void tidyTrails(const HeapAndTrailsChoice& state)
    {
      heapobject* savedHT;
      TrailLoc savedBindingTrailTop;
      TrailLoc savedObjectTrailTop;
      TrailLoc savedIPTrailTop;
      TrailLoc savedTagTrailTop;
      TrailLoc savedRefTrailTop;

      state.restore(savedHT, savedBindingTrailTop, 
		    savedObjectTrailTop,
		    savedIPTrailTop, savedTagTrailTop, savedRefTrailTop);
      bindingTrail.tidyUpTrail(savedBindingTrailTop, savedHT);
      objectTrail.tidyUpTrail(savedObjectTrailTop, heap);
      ipTrail.tidyUpTrail(savedIPTrailTop, heap);
      tagTrail.tidyUpTrail(savedTagTrailTop, heap);
      refTrail.tidyUpTrail(savedRefTrailTop, currentChoicePoint);
      heap.setSavedTop(savedHT);
    }

  //
  // Copy the current state of the thread into a choice point.
  //
  inline void assignChoicePoint(Choice* choice,
		     const word32 NumXRegs, 
		     const EnvLoc TopEnv)
  {
    word32	i;
    
    choice->status = getStatus();
    choice->continuationInstr = continuationInstr;
    saveHeapAndTrails(choice->heapAndTrailsState);
    choice->envStackTop = TopEnv;
    choice->currentEnvironment = currentEnvironment;
    choice->previousChoicePoint = currentChoicePoint;
    choice->cutPoint = cutPoint;
    
    choice->metaCounter = metaCounter;
    choice->objectCounter = objectCounter;
    
    choice->NumArgs = NumXRegs;
    for (i = 0; i < NumXRegs; i++)
      {
	choice->X[i] = X[i];
      }
  }

  //
  // Push a new choice point onto the choice point stack.  
  // The current state of the
  // thread is saved in the choice point and the location of the
  // alternative is recorded.  The pointer to the newly created choice
  // point is then returned.
  // If ChoiceLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  ChoiceLoc pushChoicePoint(const CodeLoc alternative, const word32 NumXRegs)
  {
    ChoiceLoc	index;
    EnvLoc	TopEnv;
    
    index = choiceStack.pushCP(choiceStack.size(NumXRegs));
    
    if (choiceStack.isEnvProtected(currentChoicePoint, currentEnvironment))
      {
	TopEnv = choiceStack.getEnvTop(currentChoicePoint);
      }
    else
      {
	TopEnv = currentEnvironment +
	  envStack.envSize(currentEnvironment);
      }
    assignChoicePoint(choiceStack.fetchChoice(index), NumXRegs, TopEnv);
    choiceStack.nextClause(index) = alternative;
    
    return(index);
  }


  // Declarations for many of the thread methods, most notably, the
  // pseudo-instructions.

#include "return.h"

#include "arithmetic.h"
#include "atoms.h"
#include "bind.h"
#include "bios.h"
#include "buffers.h"
#include "c_to_prolog.h"
#include "compare.h"
#include "compile_qp.h"
#include "cut.h"
#include "decompile.h"
#include "delay_qp.h"
#include "delay_escape.h"
#include "distinction.h"
#include "dyn_code.h"
#include "encode_stream.h"
#include "env.h"
#include "env_var.h"
#include "equal.h"
#include "equal_escape.h"
#include "esc_init.h"
#include "examine_term.h"
#include "exception.h"
#include "execute.h"
#include "foreign.h"
#include "free_in.h"
#include "freeness.h"
#include "gc_escapes.h"
#include "generate_var_names.h"
#include "get_args.h"
#include "interrupt_qp.h"
#include "ip_qp.h"
#include "icm_escapes.h"
#include "ipc_escapes.h"
#include "load.h"
#include "machine.h"
#include "name.h"
#include "object_variable.h"
#include "occurs_check.h"
#include "pipe.h"
#include "process.h"
#include "pseudo_instr.h"
#include "quantifier.h"
#include "read_qp.h"
#include "record.h"
#include "signal_escapes.h"
#include "state.h"
#include "statistics.h"
#include "stream_escapes.h"
#include "string_escapes.h"
#include "structure.h"
#include "sub_escape.h"
#include "symbols.h"
#include "system_qp.h"
#include "tcp_escapes.h"
#include "temperature.h"
#include "thread_escapes.h"
#include "token.h"
#include "trace_escapes.h"
#include "trail.h"
#include "unify.h"
#include "varname.h"
#include "write.h"

  //
  // Set the cpu up for the execution of the next alternative from the current 
  // choice point. If there is no choice point an appropriate fatal error message 
  // is given.
  // NOTE: The state is not reset.
  //
#ifdef DEBUG
  void Backtrack(Thread& th, 
		 const CodeLoc pc)
  {
    trace.TraceBacktrack(th, pc);

  programCounter = choiceStack.nextClause(currentChoicePoint);
  cutPoint = choiceStack.fetchChoice(currentChoicePoint)->getCutPoint();
  //  choiceStack.getNextAlternative(*this, currentChoicePoint);
  }
#else	// DEBUG
  void Backtrack(CodeLoc& PC)
  {
  PC = choiceStack.nextClause(currentChoicePoint);
  cutPoint = choiceStack.fetchChoice(currentChoicePoint)->getCutPoint();
//    choiceStack.getNextAlternative(*this, currentChoicePoint);
  }
#endif	// DEBUG

  Thread(Thread *parent,
	 const word32 ScratchpadSize,
	 const word32 HeapSize,
	 const word32 BindingTrailSize,
	 const word32 ObjectTrailSize,
	 const word32 IPTrailSize,
	 const word32 TagTrailSize,
	 const word32 RefTrailSize,
	 const word32 EnvSize,
	 const word32 ChoiceSize,
	 const word32 NameSize,
	 const word32 IPSize);

  Thread(Thread *parent,
	 ThreadOptions& thread_options);
  
  Thread(Thread *parent,
	 HeapBufferManager& SharedBuffers,
	 Heap& SharedScratchpad,
	 Heap& SharedHeap,
	 NameTable& SharedNames,
	 IPTable& SharedIPTable,
	 BindingTrail& SharedBindingTrail,
	 UpdatableObjectTrail& SharedObjectTrail,
	 UpdatableObjectTrail& SharedIPTrail,
	 UpdatableTagTrail& SharedTagTrail,
	 RefTrail& SharedRefTrail,
	 const word32 EnvSize,
	 const word32 ChoiceSize);

  ~Thread(void);

  bool operator==(const Thread& th) const
  {
    return this == &th;
  }

  //
  //
  // Save the data area and registers.
  //
  void save(ostream&);

  //
  // Load the data area and registers.
  //
  word32 load(istream& strm, word32 magic);

  CodeLoc& ProgramCounter(void) { return programCounter; }
  Heap& TheHeap(void) { return heap; }
  Heap& TheScratchpad(void) { return scratchpad; }
  BindingTrail& TheBindingTrail(void) { return bindingTrail; }
  UpdatableObjectTrail& TheObjectTrail(void) { return objectTrail; }
  UpdatableObjectTrail& TheIPTrail(void) { return ipTrail; }
  UpdatableTagTrail& TheTagTrail(void) { return tagTrail; }
  RefTrail& TheRefTrail(void) { return refTrail; }
  ChoiceStack& TheChoiceStack(void) { return choiceStack; }


  const Heap& InspectHeap(void) const { return heap; }
  CodeLoc& ContinuationInstr(void) { return continuationInstr; }
  EnvLoc& CurrentEnvironment(void) { return currentEnvironment; }
  EnvironmentStack& EnvStack(void) { return envStack; }
  word32& MetaCounter(void) { return metaCounter; }
  word32& ObjectCounter(void) { return objectCounter; }
  Object **XRegs(void) { return X; }
  ChoiceLoc& CurrentChoicePoint(void) { return currentChoicePoint; }
  ChoiceLoc& CutPoint(void) { return cutPoint; }

  NameTable& getNames(void) { return names; }

  BlockStatus& getBlockStatus(void) { return block_status; }
  RestartStatus& getRestartStatus(void) { return restart_status; }
};

// Print out some information about the thread in a human readable form.
extern ostream& operator<<(ostream&, Thread&);

#endif	// THREAD_QP_H
