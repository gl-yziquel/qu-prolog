// executable.h - Saving and loading a .qx file.
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: executable.h,v 1.2 2001/11/21 00:21:13 qp Exp $

//
// Format of a .qx file:
//
//	+-----------------------+
//	| code area's magic	| Size of word32.
//	+-----------------------+
//	| code area size	| Size of word32.
//	+-----------------------+
//	| string#		| } SIZE_OF_ADDRESS	}
//	+-----------------------+			}
//	| arity			| } SIZE_OF_NUMBER	}
//	+-----------------------+			} Repeat
//	| size			| } SIZE_OF_OFFSET	} for
//	+-----------------------+			} each
//	|  c			| }			} predicate.
//	|  o			| } size bytes		}
//	|  d			| }			}
//	|  e			| }			}
//	+-----------------------+
//	| code area's top	| Size of word32.
//	+-----------------------+
//	| string table's magic	| Size of word32.
//	+-----------------------+
//	| string table size	| Size of word32.
//	+-----------------------+
//	| String Table		|
//	|	List		|
//	|	of		|
//	|	'\0'		|
//	|	terminated	|
//	|	strings.	|
//	+-----------------------+
//	| string table's top	| Size of word32.
//	+-----------------------+
//	| atom table's magic	| Size of word32.
//	+-----------------------+
//	| atom table size	| Size of word32.
//	+-----------------------+
//	| Atom Table		|
//	|	Offsets		|
//	|	to		|
//	|	the		|
//	|	string		|
//	|	table.		|
//	+-----------------------+
//      | number table magic    |
//      +-----------------------+
//      | number table size     |
//      +-----------------------+
//      | heap of number objects|
//      +-----------------------+
//	| predicate's magic	| Size of word32.
//	+-----------------------+
//	| predicate table size	| Size of word32.
//	+-----------------------+
//	| Predicate Table	|
//	|	Offsets		|
//	|	to		|
//	|	the		|
//	|	code		|
//	|	area.		|
//	+-----------------------+
//

#ifndef	EXECUTABLE_H
#define	EXECUTABLE_H

#include "atom_table.h"
#include "code.h"
#include "pred_table.h"

//
// Save the areas to a .qx file.
//
extern void SaveExecutable(const char *file, Code& code,
			   AtomTable& atoms,
			   PredTab& predicates);

//
// Load the areas from a .qx file.
//
extern void LoadExecutable(const char *file, Code& code, AtomTable& atoms,
			   PredTab& predicates);

#endif	// EXECUTABLE_H

