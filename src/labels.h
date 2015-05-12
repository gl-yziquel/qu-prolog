// labels.h -
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: labels.h,v 1.7 2006/01/31 23:17:51 qp Exp $

#ifndef	LABELS_H
#define	LABELS_H

#include <vector>

#include "asm_int.h"
#include "asm_string_table.h"
#include "code.h"
#include "code_block.h"
//#include "string_qp.h"

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

  string *name;

  bool resolved;
  
  vector<Reference *> *references;
public:
  explicit Label(const string& s) 
    : name(new string(s)),
    resolved(false),
    references(new vector<Reference *>)
    {
    }
  ~Label(void)
  {
    delete name;
    assert(resolved);
    delete references;
  }
  
  const string& Name(void) const { return *name; }

  bool operator==(const Label& l) const
  {
    return Name() == l.Name();
  }

  void AddReference(CodeBlock& code, const u_int jump_offset_base)
  {
    Reference *ref = new Reference(code.Current(), jump_offset_base);

    references->push_back(ref);
    code.Advance(Code::SIZE_OF_OFFSET);
  }

  void Resolve(CodeBlock& code)
  {
    assert(!resolved);
    
    resolved = true;
    
    for (vector<Reference *>::iterator iter = references->begin();
	 iter != references->end();
	 iter++)
      {
	const ASMInt<Code::OffsetSizedType> ref(static_cast<const Code::OffsetSizedType>(code.Current() - (*iter)->JumpOffsetBase()));
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
      name = new string(*(l.name));
      resolved = l.resolved;

      delete references;
      references = new vector<Reference *>(*(l.references));
    }
};

inline ostream& operator<<(ostream& ostrm, const Label& label)
{
  return ostrm << label.Name();
}


class LabelTable
{
private:
  vector<Label *> labels;
public:
  // s is the name of the label
  // code is the code block where it references
  // job is the jump offset base
  void AddReference(const string& s, CodeBlock& code, const u_int job)
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
	label->AddReference(code, job);
	
	labels.push_back(label);
      }
  }
  
  void Resolve(const string& s, CodeBlock &code)
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
