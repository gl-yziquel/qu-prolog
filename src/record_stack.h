// record_stack.h - Stack class deals with individual elements while
//		    RecordStack class handles variable size records.  Hence,
//		    RecordStack is derived from Stack.
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
// $Id: record_stack.h,v 1.3 2001/06/07 05:18:12 qp Exp $

#ifndef	RECORD_STACK_H
#define	RECORD_STACK_H

#include "area_offsets.h"
#include "defs.h"
#include "stack_qp.h"

//
// After a record is pushed onto the stack, the previous top of stack is
// pushed onto the stack.  So poping a record is a matter restoring the top of
// stack to previous value.  Hence, the size of the record is not required.
// This approach makes the stack management simplier in the multiple page
// model because no record is not allowed to break up and store in two pages,
// and no need to worry about the amount of unused space left on previous
// page.
//
class	RecordStack : public PrologStack <StackWord>
{

protected:

	//
	// Return the name of the table.
	//
virtual	const char	*getAreaName(void) const
			{ return("record stack"); }

	//
	// Push a record onto the stack.
	// The old top of stack is pushed after the allocation of the record.
	// This makes internal maintenance easier.
	//
	StackLoc	pushRecord(const word32 size)
          {
	    StackLoc	OldTop, record;

	    OldTop = getTopOfStack();
	    record = allocateBlock(size);		// Allocate record.
	    pushElement((StackWord)(OldTop));	// Push the old top of stack.
	    return(record);
          }
	
	//
	// Pop the topmost record off the stack.
	//
	void		popRecord(void)
			{
				setTopOfStack((StackLoc)(popElement()));
			}

	//
	// Reduce the size of the record on the top of the stack, pointed by
	// 'loc', to 'size'.  The size is defined in bytes.
	//
	void		trimRecord(const StackLoc loc, const word32 size)
          {
	    StackLoc	OldTop;

	    OldTop = (StackLoc)(popElement());
	    setTopOfStack(loc + roundBasicUnit(size, sizeof(StackWord)));
	    pushElement((StackWord)(OldTop));
          }

	//
	// Return the previous top of stack, which is stored at the location
	// beneath the start of the record.
	//
	StackLoc	previousTop(const StackLoc loc)	const
			{ return(*inspectAddr(loc - 1)); }

	//
	// Change the value for the previous top of stack.
	//
	void		changePreviousTop(const StackLoc loc,
					  const StackLoc NewValue)
			{ *fetchAddr(loc - 1) = NewValue; }

	//
	// Get the number of StackWords in a record of size bytes
	// including the internal maintenance data.
	//
	word32		numberOfStackWords(const word32 size) const
			{
				return(roundBasicUnit(size,sizeof(StackWord))
				       + 1);
			}

	//
	// Reset the top of stack to after the record pointed by 'loc',
	// including the internal maintenance data.  The size of the record is
	// defined by 'size' in bytes.
	//
	void		resetTopOfStack(const StackLoc loc, const word32 size)
			{
				setTopOfStack(loc +
					      roundBasicUnit(size, 
							sizeof(StackWord)) +
					      1);
			}

public:

	RecordStack(word32 size, word32 overflow) :
				PrologStack <StackWord> (size, overflow)
			{}

};

#endif	// RECORD_STACK_H
