// asm_string_table.h - 
//
// Tables used by the assembler to store atom strings and numbers.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: asm_string_table.h,v 1.9 2006/01/31 23:17:49 qp Exp $

#ifndef	ASM_STRING_TABLE_H
#define	ASM_STRING_TABLE_H

#include <iostream>

#include "asm_int.h"
#include "code.h"
#include "defs.h"
//#include "string_qp.h"

typedef u_int ASMLoc;

template <class EntryType>
class ASMTable
{
private:
  EntryType *table;             // Table of entries

  ASMLoc table_size;		// Total size of lookup array
  ASMLoc table_num_entries;	// Number of entries in use

  void expandTable(void)
  {
    ASMLoc new_size = 2 * table_size;
    
    EntryType *tmp = new EntryType[new_size];

    for (u_int i = 0; i < table_size; i++)
      {
	tmp[i] = table[i];
      }
    
    delete [] table;
    
    table = tmp;
    
    table_size = new_size;
  }
  
public:
  ASMTable(int size = 512);
  
  virtual ~ASMTable(void);

  ASMLoc tableNumEntries(void) const { return table_num_entries; }
  
  const EntryType& getEntry(const ASMLoc i) const
  {
    assert(i < table_num_entries);
    
    return table[i];
  }
  
  ASMLoc lookup(const EntryType& s)
  { 
    ASMLoc i;
    
    for (i = 0; i < table_num_entries; i++)
      {
	if (s == table[i])
	  {
	    break;
	  }
      }
    if (i < table_num_entries)
      {
	return i;
      }
    else
      {
	if (table_num_entries == table_size)
	  {
	    expandTable();
	  }
	
	ASMLoc index = table_num_entries;
	
	table[index] = EntryType(s);
	
	table_num_entries++;
	return index;
      }
  }

  virtual ostream& save(ostream&) const = 0;
};

//
// String pointers are used as the entries of ASMStringTable
//
class ASMStringPointer
{
public:
  string* value;

  bool operator==(const ASMStringPointer s) const
    { return (*value == *s.value); }

   ASMStringPointer(void)
    {
      value = NULL;
    }

  ASMStringPointer(string* s)
    {
      value = new string(*s);
    }

  ~ASMStringPointer(void)
    {
      //    delete value;
    }
};

//
// The string table for relocation of atoms
//
class ASMStringTable : public ASMTable <ASMStringPointer>
{
public:
  ASMStringTable(void) : ASMTable <ASMStringPointer>() {}

  const string& operator[](const ASMLoc i) const
  {
    assert(i < tableNumEntries());
    
    return *(getEntry(i).value);
  }

  ostream& save(ostream& ostrm) const;
};


#endif	// ASM_STRING_TABLE_H


