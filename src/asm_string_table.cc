// asm_string_table.cc -
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
// $Id: asm_string_table.cc,v 1.4 2002/11/08 00:44:13 qp Exp $

#include "asm_string_table.h"
#include "code.h"

template <class EntryType>
ASMTable<EntryType>::ASMTable(int size)
{
  table_size = size;
  
  table = new (EntryType)[table_size];
  
  table_num_entries = 0;
}

template <class EntryType>
ASMTable<EntryType>::~ASMTable(void)
{
  delete [] table;
}

ostream&
ASMStringTable::save(ostream& ostrm) const
{
  // Count up all the characters
  Code::AddressSizedType num_bytes = 0;
  
  for (ASMLoc i = 0; i < tableNumEntries(); i++)
    {
      // Number of characters + 1 for null byte
      num_bytes += (getEntry(i).value)->length() + 1;
    }
  
  // Write out the number of bytes
  IntSave<Code::AddressSizedType>(ostrm, num_bytes);
  
  // Write out the strings.
  for (ASMLoc i = 0; i < tableNumEntries(); i++)
    {
      ostrm << *(getEntry(i).value) << ends;
      if (ostrm.fail())
	{
	  SaveFailure(__FUNCTION__, "strings");
	}
    }
  
  return ostrm;
}


template class ASMTable <ASMStringPointer>;













