// global.h -
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
// $Id: global.h,v 1.2 2001/11/21 00:21:14 qp Exp $

#ifndef	GLOBAL_H
#define	GLOBAL_H

#include "atom_table.h"
#include "objects.h"
#include "code.h"
#include "cond_list.h"
#include "icm_environment.h"
#include "icm_message.h"
#include "pred_table.h"
#include "qem_options.h"
#include "record_ref_table.h"
#include "scheduler.h"
#include "scheduler_status.h"
#include "signals.h"
//#include "string_table.h"
#include "thread_options.h"
#include "thread_table.h"

//#include "heap.h"

extern AtomTable *atoms;
extern Object** lib_path;
extern Code *code;
extern ICMEnvironment *icm_environment;
extern CondList<ICMMessage *> *incoming_icm_message_queue;
extern IOManager *iom;
extern SocketManager *sockm;
extern PredTab *predicates;
extern QemOptions *qem_options;
extern RecordDB *record_db;
extern Scheduler *scheduler;
extern SchedulerStatus *scheduler_status;
extern Signals *signals;
extern ThreadOptions *thread_options;
extern ThreadTable *thread_table;
extern pthread_t *interrupt_handler_thread;

#endif	// GLOBAL_H
