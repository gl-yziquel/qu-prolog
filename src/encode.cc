// encode.cc - Term encoding and decoding.
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
// $Id: encode.cc,v 1.9 2005/11/26 23:34:29 qp Exp $

#ifndef ENCODE_CC
#define ENCODE_CC

#include <iostream>
#include <string.h>

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

Object* 
EncodeMap::getObjectVariableNames(Heap& heap)
{
  Object*	result;
  //  int32	i;
  //  int32 offset;
  result = AtomTable::nil;

#if 0  
  for (i = top_table_entry - 1; i >= 0; i--)
    {
      if (vector_of_tables[top_vector_entry - 1][i]->isObjectVariable() &&
	  OBJECT_CAST(ObjectVariable*, vector_of_tables[top_vector_entry - 1][i])->getName() != NULL)
	{
	  Cons* temp = heap.newCons(OBJECT_CAST(ObjectVariable*, vector_of_tables[top_vector_entry - 1][i])->getName(),
				    result);
	  result = temp;
	}
    }
  for (offset = top_vector_entry - 2; offset >= 0; offset--)
    {
      for (i = TABLE_MAX - 1; i >= 0; i--)
	{
	  if (vector_of_tables[offset][i]->isObjectVariable() &&
	      OBJECT_CAST(ObjectVariable*, vector_of_tables[offset][i])->getName() != NULL)
	    {
	      Cons* temp = heap.newCons(OBJECT_CAST(ObjectVariable*, vector_of_tables[offset][i])->getName(),
					result);
	      result = temp;
	    }
	}
    }
#endif // 0
  return(result);
}
  
//
// Write a character.
//
bool
EncodeWrite::writeEncodeChar(QPStream& stream, word8 c)
{
  return stream.good() && stream.put(c) && stream.good();
}

//
// Encode the string and write the result to the stream.
//
bool
EncodeWrite::encodeWriteString(QPStream& stream,
			       Atom* loc,
			       AtomTable& atoms)
{
  const char *string = atoms.getAtomString(loc);
  word32 length = static_cast<word32>(strlen(string));
  bool result = writeEncodeChar(stream, static_cast<word8>(length));

  for (word32 i = 0; i < length; i++)
    {
      result &= writeEncodeChar(stream, string[i]);
    }
  return(result);
}

//
// Encode the variable name and sent it over.
//
bool
EncodeWrite::encodeWriteVarName(Heap& heap,
				QPStream& stream,
				Object* var,
				AtomTable& atoms)
{
  assert(var->isAnyVariable());
  bool result = true;
  
  Reference* ref = OBJECT_CAST(Reference*, var);
  if (ref->hasExtraInfo() && ref->getName() != NULL)
    {
      result = writeEncodeChar(stream, EncodeMap::ENCODE_NAME) &&
	encodeWriteString(stream, ref->getName(), atoms);
    }

  return(result);
}

//
// Encode the substitution and write the result to the stream.
//
bool
EncodeWrite::encodeWriteSub(Thread& th,
			    Heap& heap,
			    QPStream& stream,
			    Object* sub,
			    AtomTable& atoms,
			    const bool remember,
			    NameTable& names)
{
  if (sub->isNil())
    {
      return(true);
    }
  else
    {
      assert(sub->isCons());
      assert(OBJECT_CAST(Cons*, sub)->isSubstitutionBlockList());
      assert(OBJECT_CAST(Cons*, sub)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* subblock =
	OBJECT_CAST(SubstitutionBlock*,OBJECT_CAST(Cons*, sub)->getHead());
      const word32 size = static_cast<const word32>(subblock->getSize());
      bool result =
	encodeWriteSub(th, heap, stream, OBJECT_CAST(Cons*, sub)->getTail(),
		       atoms, remember, names) &&
	writeEncodeChar(stream, 
                        static_cast<word8>(*reinterpret_cast<word32*>(subblock))&0x00000ff)
	&& writeEncodeNumber(stream, size);
      for (word32 i = 1; i <= subblock->getSize(); i++)
	{
	  result &=
	    encodeWriteTerm(th, heap, stream, subblock->getDomain(i),
			    atoms, remember, names) &&
	    encodeWriteTerm(th, heap, stream, subblock->getRange(i),
			    atoms, remember, names);
	}
      return result;
    }
}

//
// Encode write a number
//
bool
EncodeWrite::writeEncodeNumber(QPStream& stream, const int32 val)
{
  return(writeEncodeChar(stream, static_cast<word8>((val & 0xff000000) >> 24)) &&
	 writeEncodeChar(stream, static_cast<word8>((val & 0x00ff0000) >> 16)) &&
	 writeEncodeChar(stream, static_cast<word8>((val & 0x0000ff00) >> 8)) &&
	 writeEncodeChar(stream, static_cast<word8>((val & 0x000000ff))));
}
//
// Encode write a double
//
bool
EncodeWrite::writeEncodeDouble(QPStream& stream, const double val)
{
  word8 w[sizeof(double)];
  memcpy(w, &val, sizeof(double));
  bool result = true;
  for (word32 i = 0; i < sizeof(double); i++)
    {
      result = result && writeEncodeChar(stream, w[i]);
    }
  return result;
}
//
// Encode the term and write the result to the stream.
//
bool
EncodeWrite::encodeWriteTerm(Thread& th,
			     Heap& heap,
			     QPStream& stream,
			     Object* term,
			     AtomTable& atoms,
			     const bool remember, 
			     NameTable& names)
{
  bool result = true;

  term = term->variableDereference();

  switch (term->utag())
    {
    case Object::uVar:
      {
	int32 val = map->lookUp(term);
	if (val != EncodeMap::NOT_FOUND)
	  {
	    if (val >= 256)
	      {
		return (writeEncodeChar(stream, EncodeMap::ENCODE_REF_OFFSET)
			&& writeEncodeChar(stream, static_cast<word8>((val / 256) & 0x000000ff))
			&& writeEncodeChar(stream, EncodeMap::ENCODE_REFERENCE)
                        && writeEncodeChar(stream, static_cast<word8>(val & 0x000000ff)));
	      }
	    else
	      {
		return(writeEncodeChar(stream, EncodeMap::ENCODE_REFERENCE) &&
		       writeEncodeChar(stream, static_cast<word8>(val & 0x000000ff)));
	      }
	  }
	else
	  {
	    map->add(term);
	    result = writeEncodeChar(stream, EncodeMap::ENCODE_VARIABLE);
	    if (remember)
	      {
		term = th.addExtraInfo(OBJECT_CAST(Variable*, term));
		
		if (OBJECT_CAST(Reference*, term)->getName() == NULL)
		  {
		    Atom* name = th.GenerateVarName(&th, th.MetaCounter(), th.getAtomBuf1());
		    names.setNameOldVar(name, term, th);
		  }
	      }
	    result &= encodeWriteVarName(heap, stream, term, atoms);
	  }
      }
      break;
    case Object::uObjVar:
      {
	int32 val = map->lookUp(term);
	if (val != EncodeMap::NOT_FOUND)
	  {
	    if (val >= 256)
	      {
		return (writeEncodeChar(stream, EncodeMap::ENCODE_REF_OFFSET)
			&& writeEncodeChar(stream, static_cast<word8>((val / 256) & 0x000000ff))
			&& writeEncodeChar(stream, 
					   EncodeMap::ENCODE_OB_REFERENCE)
                        && writeEncodeChar(stream, static_cast<word8>(val & 0x000000ff)));
	      }
	    else
	      {
		return(writeEncodeChar(stream, EncodeMap::ENCODE_OB_REFERENCE)
		       &&
		       writeEncodeChar(stream, static_cast<word8>(val & 0x000000ff)));
	      }
	  }
	else
	  {
	    map->add(term);
	    result = writeEncodeChar(stream, EncodeMap::ENCODE_OB_VARIABLE);
	    if (remember)
	      {
		Reference* ref = OBJECT_CAST(Reference*, 
					     term->variableDereference()); 
		
		if (ref->getName() == NULL)
		  {
		    Atom* name = 
		      th.GenerateObjectVariableName(&th, th.ObjectCounter(), th.getAtomBuf1());
		    names.setNameOldVar(name, term, th);
		  }
	      }
	    result &= encodeWriteVarName(heap, stream, term, atoms);
	  }
      }
      break;
    case Object::uCons:
      {
	Cons* list = OBJECT_CAST(Cons*, term);
	return(writeEncodeChar(stream, EncodeMap::ENCODE_LIST) &&
	       encodeWriteTerm(th, heap, stream, list->getHead(),
			       atoms, remember, names) &&
	       encodeWriteTerm(th, heap, stream, list->getTail(),
			       atoms, remember, names));
      }
      break;
    case Object::uStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	word32 arity = static_cast<word32>(str->getArity());
	result = writeEncodeChar(stream, EncodeMap::ENCODE_STRUCTURE) &&
	  writeEncodeNumber(stream, arity) &&
	    encodeWriteTerm(th, heap, stream, str->getFunctor(),
			    atoms, remember, names);
	for (word32 i = 1; i <= arity; i++)
	  {
	    result &= encodeWriteTerm(th, heap, stream,
				      str->getArgument(i),
				      atoms, remember, names);
	  }
	break;
      }
    case Object::uQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, term);
	return(writeEncodeChar(stream, EncodeMap::ENCODE_QUANTIFIER) &&
	       encodeWriteTerm(th, heap, stream, quant->getQuantifier(),
			       atoms, remember, names) &&
	       encodeWriteTerm(th, heap, stream, quant->getBoundVars(),
			       atoms, remember, names) &&
	       encodeWriteTerm(th, heap, stream, quant->getBody(),
			       atoms, remember, names));
      }
      break;
    case Object::uConst:
      {
	if (term->isAtom())
	  {
	    int32 val = map->lookUp(term);
	    if (val != EncodeMap::NOT_FOUND)
	      {
		if (val >= 256)
		  {
		    return (writeEncodeChar(stream, EncodeMap::ENCODE_REF_OFFSET)
			    && writeEncodeChar(stream, static_cast<word8>((val / 256) & 0x000000ff))
			    && writeEncodeChar(stream, 
					       EncodeMap::ENCODE_ATOM_REF)
			    && writeEncodeChar(stream, static_cast<word8>(val & 0x000000ff)));
		  }
		else
		  {
		    return(writeEncodeChar(stream, EncodeMap::ENCODE_ATOM_REF)
			   &&
			   writeEncodeChar(stream, static_cast<word8>(val & 0x000000ff)));
		  }
	      }
	    else
	      {
		map->add(term);
		return(writeEncodeChar(stream, EncodeMap::ENCODE_ATOM) &&
		       encodeWriteString(stream, OBJECT_CAST(Atom*, term), 
					 atoms));
	      }
	  }
	else if (term->isInteger())
	  {
	    return(writeEncodeChar(stream, EncodeMap::ENCODE_INTEGER) &&
		   writeEncodeNumber(stream, term->getNumber()));
	  }
        else
	  {
	    return(writeEncodeChar(stream, EncodeMap::ENCODE_DOUBLE) &&
		   writeEncodeDouble(stream, term->getDouble()));
	  }
      }
      break;

    case Object::uSubst:
      {  
	Substitution* subst = OBJECT_CAST(Substitution*, term);
	return(writeEncodeChar(stream, EncodeMap::ENCODE_SUBSTITUTION) &&
	       encodeWriteSub(th, heap, stream, 
			      subst->getSubstitutionBlockList(),
			      atoms, remember, names) &&
	       writeEncodeChar(stream, EncodeMap::ENCODE_SUBSTITUTION_END) &&
	       encodeWriteTerm(th, heap, stream, subst->getTerm(),
			       atoms, remember, names));
      }
      break;
    default:
      assert(false);
      break;
    }
  return(result);
}

//
// Read a character.
//
bool
EncodeRead::encodeReadChar(QPStream& stream, word8& c)
{
  int ch;
  ch = stream.get();
  c = (word8)ch;
  return (ch != EOF);
}

//
// Read a number.
//
bool
EncodeRead::encodeReadNumber(QPStream& stream, int32& num)
{
  word8 c;
  bool result;
  result = encodeReadChar(stream, c);
  num = c;
  result &= encodeReadChar(stream, c);
  num = (num << 8) | c;
  result &= encodeReadChar(stream, c);
  num = (num << 8) | c;
  result &= encodeReadChar(stream, c);
  num = (num << 8) | c;
  return result;
}
//
// Read a double.
//
bool
EncodeRead::encodeReadDouble(QPStream& stream, double& num)
{
  bool result = true;
  word8 w[sizeof(double)];
  for (word32 i = 0; i < sizeof(double); i++)
    {
      result &= encodeReadChar(stream, w[i]);
    }
  memcpy(&num, w, sizeof(double));
  return result;
}
//
// Read from a stream and decode back to a string.
//
bool
EncodeRead::encodeReadString(QPStream& stream,
			     Atom*& name,
			     AtomTable& atoms)
{
  word8 c;
  bool result = encodeReadChar(stream, c);
  word32 length = c;
  for (word32 i = 0; (i < length) && result; i++)
    {
      result &= encodeReadChar(stream, c);
      string[i] = c;
    }
  string[length] = '\0';
  name = atoms.add(string);
  return result;
}

//
// Read from a stream and decode back to the substitution.
//
bool
EncodeRead::encodeReadSub(Thread& th,
			  Heap& heap,
			  QPStream& stream,
			  Object*& sub,
			  AtomTable& atoms,
			  const bool remember,
			  NameTable& names)
{
  sub = AtomTable::nil;

  word8 c;
  bool result = encodeReadChar(stream, c);
  do {
//    word32 tag = c;
    int32 size;
    result &= encodeReadNumber(stream, size);
    SubstitutionBlock* subblock = heap.newSubstitutionBlock(size);
//    *(reinterpret_cast<word32*>(subblock)) |= tag;
    for (int32 i = 1; result && (i <= size); i++)
      {
	Object* temp;
	result &= encodeReadTerm(th, heap, stream, temp,
				 atoms, remember, names);
	subblock->setDomain(i, temp);
	result &= encodeReadTerm(th, heap, stream, temp,
				 atoms, remember, names);
	subblock->setRange(i, temp);
      }
    if (result)
      {
        sub = heap.newSubstitutionBlockList(subblock, sub); 
      }
    result &= encodeReadChar(stream, c);
  }
  while (result && (c != EncodeMap::ENCODE_SUBSTITUTION_END));
  return(result);
}

bool
EncodeRead::encodeReadTerm(Thread& th,
			   Heap& heap,
			   QPStream& stream,
			   Object*& term,
			   AtomTable& atoms,
			   const bool remember,
			   NameTable& names)
{
  word8 c;
  bool result = false;

  if (! encodeReadChar(stream, c))
    {
      return(false);
    }
  switch (c)
    {
    case EncodeMap::ENCODE_REF_OFFSET:
      {
	if (! encodeReadChar(stream, c))
	  {
	    return(false);
	  }
        word8 offset = c;
        if (! encodeReadChar(stream, c))
	  {
	    return(false);
	  }
	if (c != EncodeMap::ENCODE_REFERENCE 
	    && c != EncodeMap::ENCODE_OB_REFERENCE 
	    && c != EncodeMap::ENCODE_ATOM_REF)
	  {
	    return(false);
	  }
        if (! encodeReadChar(stream, c))
	  {
	    return(false);
	  }
	term = map->lookUp(offset, c);
	return true;
      }
      break;
    case EncodeMap::ENCODE_REFERENCE:
    case EncodeMap::ENCODE_OB_REFERENCE:
    case EncodeMap::ENCODE_ATOM_REF:
      if (! encodeReadChar(stream, c))
        {
          return(false);
        }
      term = map->lookUp(0,c);
      return true;
      break;
    case EncodeMap::ENCODE_VARIABLE:
      result = encodeReadChar(stream, c);
      if (remember && c == EncodeMap::ENCODE_NAME)
	{
	  Atom* name;

	  if (! encodeReadString(stream, name, atoms))
            {
              return(false);
            }
	  term = names.getVariable(name);
	  if (term == NULL)
	    {
	      term = heap.newVariable(true);
	      names.setNameNewVar(name, term, th);
	    }
	}
      else
	{
	  if (c == EncodeMap::ENCODE_NAME)
	    {
	      if (! encodeReadChar(stream, c))
                {
                  return false;
                }
	      word32 length = c;
	      if (!stream.seekg(length, ios::cur))
                {
                  return false;
                }
	    }
	  else if (!result)
	    {
	      stream.clear();
	    }
	  else
	    {
	      stream.unget();
	    }
	  term = heap.newVariable();
	}
      map->add(term);
      return true;
      break;
    case EncodeMap::ENCODE_OB_VARIABLE:
      result = encodeReadChar(stream, c);
      if (remember && c == EncodeMap::ENCODE_NAME)
	{
	  Atom* name;

	  if (! encodeReadString(stream, name, atoms))
            {
              return(false);
            }
	  term = names.getVariable(name);
	  if (term == NULL)
	    {
	      term = heap.newObjectVariable();
	      names.setNameNewVar(name, term, th);
	    }
	}
      else
	{
	  if (c == EncodeMap::ENCODE_NAME)
	    {
	      if (! encodeReadChar(stream, c))
                {
                  return false;
                }
	      word32 length = c;
	      if (! stream.seekg(length, ios::cur))
                {
                  return false;
                }
	    }
	  else if (!result)
	    {
	      stream.clear();
	    }
	  else
	    {
	      stream.unget();
	    }
	  term = heap.newObjectVariable();
	}
      map->add(term);
      return true;
      break;
    case EncodeMap::ENCODE_LIST:
      Object *head, *tail;
      result = encodeReadTerm(th, heap, stream, head,
			      atoms, remember, names) &&
	encodeReadTerm(th, heap, stream, tail,
		       atoms, remember, names);
      term = heap.newCons(head, tail);
      return(result);
      break;
    case EncodeMap::ENCODE_STRUCTURE:
      {
	int32 length;
	if (! encodeReadNumber(stream, length))
          {
            return false;
          }

	Structure* str = heap.newStructure(length);
	Object* temp;
	if (! encodeReadTerm(th, heap, stream, temp,
			      atoms, remember, names))
          {
            return false;
          }
	str->setFunctor(temp);
	for (int32 i = 1; i <= length; i++)
	  {
	    if (! encodeReadTerm(th, heap, stream, temp,
				 atoms, remember, names))
              {
                return false;
              }
	    str->setArgument(i, temp);
	  }
	term = str;
        return true;
      }
      break;
    case EncodeMap::ENCODE_QUANTIFIER:
      {
	Object *q, *bv, *body;

 	result = 
	  encodeReadTerm(th, heap, stream, q, atoms, remember, names) &&
	  encodeReadTerm(th, heap, stream, bv, atoms, remember, names) &&
	  encodeReadTerm(th, heap, stream, body, atoms, remember, names) &&
	  th.checkBinder(bv, AtomTable::nil);
	term = heap.newQuantifiedTerm();
	OBJECT_CAST(QuantifiedTerm*, term)->setQuantifier(q);
	OBJECT_CAST(QuantifiedTerm*, term)->setBoundVars(bv);
	OBJECT_CAST(QuantifiedTerm*, term)->setBody(body);
        return result;
      }
      break;
    case EncodeMap::ENCODE_ATOM:
      {
	Atom* a;
	
	if (encodeReadString(stream, a, atoms))
          {
	    term = a;
	    map->add(term);
            return true;
          }
        else
          {
            return false;
          }
      }
      break;
    case EncodeMap::ENCODE_INTEGER:
      {
	int32 integer;
	result = encodeReadNumber(stream, integer);
	term = heap.newNumber(integer);
	return result;
      }
      break;
    case EncodeMap::ENCODE_DOUBLE:
      {
	double d;
	result = encodeReadDouble(stream, d);
	term = heap.newDouble(d);
	return result;
      }
      break;
    case EncodeMap::ENCODE_SUBSTITUTION:
      {
	Object *s, *t;
	result = 
	  encodeReadSub(th, heap, stream, s,
			atoms, remember, names) &&
	  encodeReadTerm(th, heap, stream, t,
			 atoms, remember, names);
        if (result)
          {
            assert(s->isCons());
	    term = heap.newSubstitution(s, t);
            return true;
          }
        else
          {
            return false;
          }
      }
      break;
    default:
      result = false;
      break;
    }
  return(result);
}

#endif	// ENCODE_CC







