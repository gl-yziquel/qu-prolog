// labels.h -
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
// $Id: labels.h,v 1.2 2000/12/13 23:10:02 qp Exp $

#ifndef	LABELS_H
#define	LABELS_H

#include <vector>

#include "asm_int.h"
#include "asm_string_table.h"
#include "code.h"
#include "code_block.h"
#include "string_qp.h"

class Label
{
private:
  class Reference
    {
    private:
      u_int reference;			// Actual loc of reference
      u_int jump_offset_base;
    public:
      Reference(const u_int r, const u_int job)
	: reference(r), jump_offset_base(job) {	}
      ~Reference(void) { }
      
      u_int Ref(void) const { return reference; }
      u_int JumpOffsetBase(void) const { return jump_offset_base; }

      void operator=(const Reference& r)
	{
	  reference = r.reference;
	  jump_offset_base = r.jump_offset_base;
	}
    };

  String *name;

  bool resolved;
  
  vector<Reference *> *references;
public:
  Label(const String& s) 
    : name(new String(s)),
    resolved(false),
    references(new vector<Reference *>)
    {
      if (name == NULL || references == NULL)
	{
	  OutOfMemory(__FUNCTION__);
	}
    }
  ~Label(void)
  {
    delete name;
    DEBUG_ASSERT(resolved);
    delete references;
  }
  
  const String& Name(void) const { return *name; }

  bool operator==(const Label& l) const
  {
    return Name() == l.Name();
  }

  void AddReference(CodeBlock& code, const u_int jump_offset_base)
  {
    Reference *ref = new Reference(code.Current(), jump_offset_base);
    if (ref == NULL)
      {
	OutOfMemory(__FUNCTION__);
      }

    references->push_back(ref);
    code.Advance(Code::SIZE_OF_OFFSET);
  }

  void Resolve(CodeBlock& code)
  {
    DEBUG_ASSERT(!resolved);
    
    resolved = true;
    
    for (vector<Reference *>::iterator iter = references->begin();
	 iter != references->end();
	 iter++)
      {
	const ASMInt<Code::OffsetSizedType> ref(code.Current() -
						(*iter)->JumpOffsetBase());
	ref.Put((*iter)->Ref(), code);
      }
  }

  // Specialised version of Resolve() for resovling failure labels, who always
  // turn into an offset of -1.
  void ResolveFail(CodeBlock& code)
  {
    resolved = true;
    
    for (vector<Reference *>::iterator iter = references->begin();
	 iter != references->end();
	 iter++)
      {
	ASMInt<Code::OffsetSizedType> ref(0);
	ref.Value(UnsignedMax(ref.Value()));
	
	ref.Put((*iter)->Ref(), code);
      }
  }

  void operator=(const Label& l)
    {
      delete name;
      name = new String(*(l.name));
      if (name == NULL)
	{
	  OutOfMemory(__FUNCTION__);
	}

      resolved = l.resolved;

      delete references;
      references = new vector<Reference *>(*(l.references));
      if (references == NULL)
	{
	  OutOfMemory(__FUNCTION__);
	}
    }
};

inline ostream& operator<<(ostream& ostrm, const Label& label)
{
  return ostrm << label.Name().Str();
}


class LabelTable
{
private:
  vector<Label *> labels;
public:
  // s is the name of the label
  // code is the code block where it references
  // job is the jump offset base
  void AddReference(const String& s, CodeBlock& code, const u_int job)
  {
    Label *found = NULL;
    
    for (vector<Label *>::iterator iter = labels.begin();
	 iter != labels.end();
	 iter++)
      {
	if (s == (*iter)->Name())
	  {
	    found = *iter;
	    break;
	  }
      }
    
    if (found)
      {
	found->AddReference(code, job);
      }
    else
      {
	// Not found, so add it
	Label *label = new Label(s);
	if (label == NULL)
	  {
	    OutOfMemory(__FUNCTION__);
	  }
	
	label->AddReference(code, job);
	
	labels.push_back(label);
      }
  }
  
  void Resolve(const String& s, CodeBlock &code)
  {
    Label *found = NULL;
    
    for (vector<Label *>::iterator iter = labels.begin();
	 iter != labels.end();
	 iter++)
      {
	if (s == (*iter)->Name())
	  {
	    found = *iter;
	    break;
	  }
      }

    if (found)
      {
	found->Resolve(code);
      }
  }

  void ResolveFail(CodeBlock& code)
  {
    Label *found = NULL;

    for (vector<Label *>::iterator iter = labels.begin();
	 iter != labels.end();
	 iter++)
      {
	if ((*iter)->Name() == "fail")
	  {
	    found = *iter;
	    break;
	  }
      }
    
    if (found)
      {
	found->ResolveFail(code);
      }
  }
};

#endif	// LABELS_H
