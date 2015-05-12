// name.cc - Functions which build up a string which corresponds to a 
//           given list, or build up a list whose elements correspond 
//           to a given name.
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
// $Id: name.cc,v 1.8 2006/02/20 03:18:51 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

/*
void
Thread::addEscapes(string& str, char quote)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      switch ((int)c)
	{
	case 7:  // \a
	  tmp.push_back('\\');
	  tmp.push_back('a');
	  break;
	case 8:  // \b
	  tmp.push_back('\\');
	  tmp.push_back('b');
	  break;
	case 9:  // \t
	  tmp.push_back('\\');
	  tmp.push_back('t');
	  break;
	case 10:  // \n
	  tmp.push_back('\\');
	  tmp.push_back('n');
	  break;
	case 11:  // \v
	  tmp.push_back('\\');
	  tmp.push_back('v');
	  break;
	case 12:  // \f
	  tmp.push_back('\\');
	  tmp.push_back('f');
	  break;
	case 13:  // \r
	  tmp.push_back('\\');
	  tmp.push_back('r');
	  break;
	case 92:  
	  tmp.push_back('\\');
	  tmp.push_back('\\');
	  break;
	default:
	  if (c == quote)
	    {
	      tmp.push_back('\\');
	      tmp.push_back('c');
	    }
	  else
	      tmp.push_back('c');
	  break;
	}
    }
  str = tmp;
}

void
Thread::removeEscapes(string& str, char quote)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      if (c == '\\')
	{
	  iter++;
	  assert(iter != str.end());
	  char d = *iter;
	  switch (d)
	    {  
	    case 'a':  // \a
	      tmp.push_back('\a');
	      break;
	    case 'b':  // \b
	      tmp.push_back('\b');
	      break;
	    case 't':  // \t
	      tmp.push_back('\t');
	      break;
	    case 'n':  // \n
	      tmp.push_back('\n');
	      break;
	    case 'v':  // \v
	      tmp.push_back('\v');
	      break;
	    case 'f':  // \f
	      tmp.push_back('\f');
	      break;
	    case 'r':  // \r
	      tmp.push_back('\r');
	      break;
	    case '\\': 
	      tmp.push_back('\\');
	      break;
	    default:
	      tmp.push_back('c');
	      break;
	    }
	}
      else if (c == quote)
	{
	  iter++;
	  assert(iter != str.end());
	  assert(*iter == quote);
	  tmp.push_back(c);
	}
      else
	tmp.push_back(c);
    }
  str = tmp;
}
*/

//
// psi_atom_codes(atom, var)
// Convert an atom to a list of character codes.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_atom_codes(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isAtom());
 
  Object* tail = AtomTable::nil;
  string atomstring(OBJECT_CAST(Atom*, val1)->getName());
  
  for (string::reverse_iterator iter = atomstring.rbegin();
       iter != atomstring.rend(); iter++)
    {
      Object* head = heap.newInteger(*iter);
      Cons* temp = heap.newCons(head, tail);
      tail = temp;
    }
  
  object2 = tail;
  return(RV_SUCCESS);
}

//
// psi_codes_atom(list integer, var)
// Convert from a list of character codes to an atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_codes_atom(Object *& object1, Object *& object2)
{
  Object* list = object1->variableDereference();
  string atomname;
  while (list->isCons())
    {
      Cons* clist = OBJECT_CAST(Cons*, list);
      Object* head = clist->getHead()->variableDereference();
      list = clist->getTail()->variableDereference();
      assert(head->isShort());
      atomname.push_back(head->getInteger());
    }
  if (list->isString()) {
    atomname.append(OBJECT_CAST(StringObject*, list)->getChars());
  }
    
  object2 = atoms->add(atomname.c_str());
  return(RV_SUCCESS);
}

//
// psi_char_code(char, var)
// Convert a character to its character code.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_char_code(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isAtom());
  
  const char *string = OBJECT_CAST(Atom*, val1)->getName();
  if (string[1] != '\0')
    {
      return(RV_FAIL);
    }
  else
    {
      object2 = heap.newShort(string[0]);
      return(RV_SUCCESS);
    }
}

//
// psi_code_char(integer, var)
// Convert a character code to its character.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_code_char(Object *& object1, Object *& object2)
{
  char string[2];
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  assert(val1->isShort());
  
  string[0] = val1->getInteger();
  string[1] = '\0';
  object2 = atoms->add(string);
  return(RV_SUCCESS);
}

//
// psi_number_codes(number, list)
// Convert number to ASCII representation
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_number_codes(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  assert(val1->isNumber());

  ostringstream strm;
  if (val1->isDouble())
    strm << val1->getDouble();
  else
    strm << val1->getInteger();

  const char* code_list = strm.str().data();

  if (*code_list == '\0')
    {
      object2 = AtomTable::nil;
      return(RV_SUCCESS);
    }

  Cons* list = TheHeap().newCons();
  object2 = list;
      
  while (true)
    {
      list->setHead(heap.newInteger((int)(*code_list)));
      code_list++;
      if (*code_list == '\0')
        {
          list->setTail(AtomTable::nil);
          break;
        }
      Cons* list_tmp = heap.newCons();
      list->setTail(list_tmp);
      list = list_tmp;
    }
   return(RV_SUCCESS);
}

//
// psi_codes_number(number, list)
// Convert a list (an ASCII representation of a number) iinto that number
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_codes_number(Object *& object1, Object *& object2)
{
  Object* arg = heap.dereference(object1);

  ostringstream str;

  while (arg->isCons())
    {
      Cons* list = OBJECT_CAST(Cons*, arg);
      if (!(list->getHead()->variableDereference()->isInteger()))
	return(RV_FAIL);
      str << (char)(list->getHead()->variableDereference()->getInteger());
      arg = list->getTail()->variableDereference();
    }
  if (arg->isString()) {
    str << OBJECT_CAST(StringObject*, arg)->getChars();
  } 
  else if (!arg->isNil())  
    return(RV_FAIL);
  bool has_dot = false;
  bool has_e = false;
  bool has_sign = false;
  bool has_digit = false;
  const char* c = str.str().data();
  const char* numstr = c;

  while (*c != '\0')
    {
      if ((*c == '+') || (*c == '-'))
        {
          if (has_sign)
            return(RV_FAIL);
          else
            has_sign = true;
        }
      else if ((*c == 'e') || (*c == 'E'))
        {
          if (has_e)
            return(RV_FAIL);
          else
            {
              has_e = true;
              has_sign = false;
            }
        }
      else if (*c == '.')
        {
          if (has_dot)
            return(RV_FAIL);
          else
            has_dot = true;
        }
      else if ((*c < '0') || (*c > '9'))
        {
          return(RV_FAIL);
        }
      else
        {
          has_digit = true;
        }
      c++;
    } 
    if (!has_digit) return(RV_FAIL);
    if (has_dot || has_e)
      object2 = TheHeap().newDouble(atof(numstr));
    else
      object2 = TheHeap().newInteger(atol(numstr));
    return(RV_SUCCESS);
}
