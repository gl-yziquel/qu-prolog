// page_table_templates.cc -
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
// $Id: page_table_templates.cc,v 1.5 2001/12/06 02:56:07 qp Exp $

#include "atom_table.h"
#include "objects.h"
#include "prolog_value.h"
#include "record_stack.h"
#include "record_ref_table.h"
#include "stack_qp.h"
#include "trail.h"
#include "dynamic_code.h"
#include "heap_qp.h"

#include "page_table.h"
#include "page_table.cc"

template class PageTable <AtomLoc>;
template class PageTable <word8>;
//template class PageTable <Cell>;
template class PageTable <char>;
template class PageTable <PrologValue>;
template class PageTable <RecordRefInfo>;
//template class PageTable <StackWord>;
template class PageTable <Atom*>;
template class PageTable <Object*>;
template class PageTable <heapobject*>;
template class PageTable <UpdatableObject>;
template class PageTable <RefObject>;
template class PageTable <UpdatableTag>;
