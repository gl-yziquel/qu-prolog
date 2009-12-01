// thread_options.h - Options for sizing of thread data
//		structures.
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
// $Id: thread_options.h,v 1.2 2001/11/21 00:21:18 qp Exp $

#ifndef THREAD_OPTIONS_H
#define THREAD_OPTIONS_H

#include "defs.h"
#include "option.h"
#include "qem_options.h"

class ThreadOptions
{
private:
  Option<word32> name_table_size;
  Option<word32> ip_table_size;
  Option<word32> heap_size;
  Option<word32> scratchpad_size;
  Option<word32> environment_stack_size;
  Option<word32> choice_stack_size;
  Option<word32> binding_trail_size;
  Option<word32> other_trail_size;
public:
  word32 NameTableSize(void) const { return name_table_size.Value(); }
  word32 IPTableSize(void) const { return ip_table_size.Value(); }
  word32 HeapSize(void) const { return heap_size.Value(); }
  word32 ScratchpadSize(void) const { return scratchpad_size.Value(); }
  word32 EnvironmentStackSize(void) const { return environment_stack_size.Value(); }
  word32 ChoiceStackSize(void) const { return choice_stack_size.Value(); }
  word32 BindingTrailSize(void) const { return binding_trail_size.Value(); }
  word32 OtherTrailSize(void) const { return other_trail_size.Value(); }

  void NameTableSize(const word32 nts) { name_table_size = nts; }
  void IPTableSize(const word32 its) { ip_table_size = its; }
  void HeapSize(const word32 hs) { heap_size = hs; }
  void ScratchpadSize(const word32 hs) { scratchpad_size = hs; }
  void EnvironmentStackSize(const word32 ess) { environment_stack_size = ess; }
  void ChoiceStackSize(const word32 css) { choice_stack_size = css; }
  void BindingTrailSize(const word32 ts) { binding_trail_size = ts; }
  void OtherTrailSize(const word32 ts) { other_trail_size = ts; }


  ThreadOptions(const word32 ntas,
		const word32 itas,
		const word32 hs,
		const word32 ss,
		const word32 ess,
		const word32 css,
		const word32 bts,
		const word32 ots)
    : name_table_size(ntas),
    ip_table_size(itas),
    heap_size(hs),
    scratchpad_size(ss),
    environment_stack_size(ess),
    choice_stack_size(css),
    binding_trail_size(bts),
    other_trail_size(ots) {}


  ThreadOptions(const QemOptions& qem_opts)
    : name_table_size(qem_opts.NameTableSize()),
      ip_table_size(qem_opts.IPTableSize()),
      heap_size(qem_opts.HeapSize()),
      scratchpad_size(qem_opts.ScratchpadSize()),
      environment_stack_size(qem_opts.EnvironmentStackSize()),
      choice_stack_size(qem_opts.ChoiceStackSize()),
      binding_trail_size(qem_opts.BindingTrailSize()),
      other_trail_size(qem_opts.OtherTrailSize())
      {}
};

#endif // THREAD_OPTIONS_H
