// thread.cc - Define the components of a thread.
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
// $Id: thread.cc,v 1.11 2005/03/08 00:35:16 qp Exp $

#include <iostream>
#include <sstream>

#include "thread_qp.h"
#include "trace_qp.h"
#include "global.h"

void Thread::changeTimeslice(bool makeSet)
{
  if (makeSet)
    {
      	scheduler->Status().setEnableTimeslice();
	TInfo().setForbidThread(false);
    }
  else
    {
      scheduler->Status().resetEnableTimeslice();
      TInfo().setForbidThread(true);
    }
}

void
Thread::InitThread(void)
{
  programCounter = NULL;

  continuationInstr = NULL;
  currentEnvironment = envStack.getTop();
  currentEnvironment = envStack.push(currentEnvironment, continuationInstr, 0);

  currentChoicePoint = choiceStack.firstChoice();
  cutPoint = EMPTY_LOC;
  catchPoint = EMPTY_LOC;

  metaCounter = 0;
  objectCounter = 0;
  ForeignFile = NULL;
  error_value = EV_NO_ERROR;

  for (u_int i = 0; i < NUMBER_X_REGISTERS; i++) 
    {
      //X[i] = NULL;
     X[i] = AtomTable::nil;
    }
  EscapeInit();
}

//
// Save the X registers in SavedX
//
void    
Thread::SaveXRegisters(void)
{
  word32 i;
  for (i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      SavedX[i] = X[i];
    }
}
//
// Restore the X registers in SavedX
//
void    
Thread::RestoreXRegisters(void)
{
  word32 i;
  for (i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      X[i] = SavedX[i];
    }
}

Thread::Thread(Thread *pt,
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
	       const word32 IPSize)
  : thread_info(pt),
    localAreas(true),
    names(*(new NameTable(NameSize))),
    ipTable(*(new IPTable(IPSize))),
    buffers(*(new HeapBufferManager(20))),
    heap(*(new Heap("heap", HeapSize, true))),
    scratchpad(*(new Heap("scratchpad", ScratchpadSize))),
    bindingTrail(*(new BindingTrail(BindingTrailSize, 0))),
    objectTrail(*(new UpdatableObjectTrail(ObjectTrailSize, 0, "updatable object trail"))),
    ipTrail(*(new UpdatableObjectTrail(IPTrailSize, 0, "IP trail"))),
    tagTrail(*(new UpdatableTagTrail(TagTrailSize, 0))),
    refTrail(*(new RefTrail(RefTrailSize, 0))),
    envStack(EnvSize),
    choiceStack(ChoiceSize)
#ifdef QP_DEBUG
    , trace(0)
#endif //QP_DEBUG
{
  InitThread();
};

Thread::Thread(Thread *pt,
	       ThreadOptions& thread_options)
  : thread_info(pt),
    localAreas(true),
    names(*(new NameTable(thread_options.NameTableSize()))),
    ipTable(*(new IPTable(thread_options.IPTableSize()))),
    buffers(*(new HeapBufferManager(20))),
    heap(*(new Heap("heap", thread_options.HeapSize(), true))),
    scratchpad(*(new Heap("scratchpad", thread_options.ScratchpadSize()))),
    bindingTrail(*(new BindingTrail(thread_options.BindingTrailSize(), 0))),
    objectTrail(*(new UpdatableObjectTrail(thread_options.ObjectTrailSize(),0,"updatable object trail"))),
    ipTrail(*(new UpdatableObjectTrail(thread_options.IPTrailSize(),0,"IP trail"))),
    tagTrail(*(new UpdatableTagTrail(thread_options.TagTrailSize(),0))),
    refTrail(*(new RefTrail(thread_options.RefTrailSize(), 0))),
    envStack(thread_options.EnvironmentStackSize()),
    choiceStack(thread_options.ChoiceStackSize())
#ifdef QP_DEBUG
    , trace(0)
#endif // QP_DEBUG
{
  InitThread();
};

Thread::Thread(Thread *pt,
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
	       const word32 ChoiceSize)
  : thread_info(pt),
    localAreas(false),
    names(SharedNames),
    ipTable(SharedIPTable),
    buffers(SharedBuffers),
    heap(SharedHeap),
    scratchpad(SharedScratchpad),
    bindingTrail(SharedBindingTrail),
    objectTrail(SharedObjectTrail),
    ipTrail(SharedIPTrail),
    tagTrail(SharedTagTrail),
    refTrail(SharedRefTrail),
    envStack(EnvSize),
    choiceStack(ChoiceSize)
#ifdef QP_DEBUG
    , trace(0)
#endif
{
  InitThread();
}

Thread::~Thread(void)
{

  if (localAreas)
    {
      delete &buffers;
      delete &scratchpad;
      delete &heap;
      delete &names;
      delete &ipTable;
      delete &bindingTrail;
      delete &objectTrail;
      delete &ipTrail;
      delete &tagTrail;
      delete &refTrail;
    }
}

ostream&
operator<<(ostream& ostrm, Thread& thread)
{
  ostrm << (ThreadCondition) thread << endl;

  return ostrm;
}

//
// Save the data area and the registers.
//
void
Thread::save(ostream&)
{
// TO DO: Thread::save()
}

//
// Load the data area and the registers.
//
word32
Thread::load(istream&, word32)
{
// TO DO: Thread::load()
  return 0;
}









