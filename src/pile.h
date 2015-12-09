// pile.h - Definition of the pile (Qu-Prolog stack).
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: pile.h,v 1.5 2006/01/31 23:17:51 qp Exp $

#ifndef	PILE_H
#define	PILE_H

#include "defs.h"
#include "prolog_value.h"
#include "stack_qp.h"

template <class StoredType>
class	Pile : public PrologStack <StoredType>
{

private:

	//
	// Return the name of the area.
	//
virtual	const char	*getAreaName(void)	const	{ return("pile"); }

public:

	//
	// Push a StoredType onto the pile.
	//
	void	push(const StoredType s){ this->pushElement(s); }

	//
	// Pop a StoredType off the pile.
	//
	StoredType	pop(void)	{ return(this->popElement()); }

	//
	// Pop n entries of StoredType off the pile.
	//
	void	popNEntries(word32 n)	{ this->setTopOfStack(this->getTopOfStack() - n); }

	//
	// Check whether the pile is empty or not.
	//
	bool	isEmpty(void)	const	{ return(this->getTopOfStack() == 0); }

	//
	// Return the size of the pile in use.
	//
	word32	size(void)	const	{ return(this->sizeOfStack()); }

	//
	// Empty the pile.
	//
	void	clear(void)		{ this->clearStack(); }

	explicit Pile(word32 size = PILE_SIZE) :
			PrologStack <StoredType> (size, PILE_SIZE / 10)
					{}
};

class	PushDownStack : public Pile <Object*>
{

public:

	explicit PushDownStack(word32 size = PILE_SIZE) : Pile <Object*> (size)
					{}
	~PushDownStack(void)		{}
};

#endif	// PILE_H
