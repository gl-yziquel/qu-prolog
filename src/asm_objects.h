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
// $Id: asm_objects.h,v 1.6 2002/11/10 07:54:50 qp Exp $

#ifndef	ASM_OBJECTS_H
#define	ASM_OBJECTS_H

#include <vector>

#include "asm_int.h"
#include "code.h"
#include "code_block.h"
#include "labels.h"
//#include "string_qp.h"

using namespace std;

class AtomArityLabel
{
private:
  ASMInt<Code::ConstantSizedType> *atom;
  ASMInt<Code::NumberSizedType> *arity;
  string *label;
public:
  AtomArityLabel(ASMInt<Code::ConstantSizedType> *at,
		 ASMInt<Code::NumberSizedType> *ar,
		 string *l) :
    atom(at), arity(ar), label(l) { }
  
  // For constructing ``default'' switch table entries.
  AtomArityLabel(string *l) : label(l)
    {
      atom = new ASMInt<Code::ConstantSizedType>(0);

      atom->Value(UnsignedMax(atom->Value()));
      
      arity = new ASMInt<Code::NumberSizedType>(0);
    }
  
  ~AtomArityLabel(void)	{ }
  
  bool operator==(const AtomArityLabel& aal) const
    {
      return *atom == *(aal.atom) &&
	*arity == *(aal.arity) &&
	*label == *(aal.label);
    }
  
  void Put(CodeBlock &code, LabelTable& labels,
	   const u_int jump_offset_base) const
    {
      atom->Put(code);
      arity->Put(code);
      labels.AddReference(*label, code, jump_offset_base);
    }
  
  u_int SizeOf(void) const
    {
      return atom->SizeOf() + arity->SizeOf() + Code::SIZE_OF_OFFSET;
    }

  void operator=(const AtomArityLabel& aal)
    {
      atom->Value(aal.atom->Value());
      arity->Value(aal.arity->Value());

      delete label;
      label = new string(*(aal.label));
    }
};

class ConstantLabel
{
private:
  ASMInt<Code::ConstantSizedType> *constant;
  string *label;
public:
  ConstantLabel(ASMInt<Code::ConstantSizedType> *c,
		string *l)
    : constant(c), label(l)
    { }
  
  // For constructing ``default'' switch table entries.
  ConstantLabel(string *l) : label(l)
    {
      constant = new ASMInt<Code::ConstantSizedType>(0);
      constant->Value(UnsignedMax(constant->Value()));
    }
  
  ~ConstantLabel(void)	{ }
  
  bool operator==(const ConstantLabel& cl) const
    {
      return *constant == *(cl.constant) &&
	*label == *(cl.label);
    }
  
  void Put(CodeBlock& code, LabelTable& labels,
	   const u_int jump_offset_base) const
    {
      ASMInt<Code::NumberSizedType> type(constant->Type());
      constant->Put(code);
      type.Put(code);
      labels.AddReference(*label, code, jump_offset_base);
    }
  
  u_int SizeOf(void) const
    {
      return constant->SizeOf() + Code::SIZE_OF_OFFSET;
    }

  void operator=(const ConstantLabel& c)
    {
      constant->Value(c.constant->Value());
      
      delete label;
      label = new string(*(c.label));
    }
};

template <class Item>
class SwitchTable
{
private:
  u_int jump_offset_base;
  ASMInt<Code::TableSizeSizedType> *num_table_entries;
  string *default_label;
  vector<Item *> *list;
public:
  SwitchTable(const u_int job,
	      ASMInt<Code::TableSizeSizedType> *num,
	      string *dl, vector<Item *> *l)
    : jump_offset_base(job),
      num_table_entries(num),
      default_label(dl),
      list(l)
      { }
  
  ~SwitchTable(void) { }
  
  void Put(CodeBlock& code,
	   LabelTable& labels)
    {
      u_int count = 0;			// Count of entries output
      
      Item default_entry(default_label);
      
      default_entry.Put(code, labels, jump_offset_base);
      
      count++;					// ``One wonderful entry!!!''
      
      // Output all the list entries
      for (vector<Item *>::iterator iter = list->begin();
	   iter != list->end();
	   iter++)
	{
	  (*iter)->Put(code, labels, jump_offset_base);
	  count++;
	}
      
      // Fill up extra places with default entries
      
      for (;
	   count < num_table_entries->Value();
	   count++)
	{
	  default_entry.Put(code, labels, jump_offset_base);
	}
    }
};

#endif	// ASM_OBJECTS_H
