
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
// $Id: compiler_support.cc,v 1.10 2006/03/13 00:10:24 qp Exp $

#include "code.h"
#include "compiler_support.h"
#include "objects.h"
#include "regalloc.h"
#include "write_support.h"

extern AtomTable *atoms;

//
// Calculate the lifetime of the x registers - needed for register
// allocation.
//
void
build_lifetime(WordArray& life, xreglife& xregisters, WordArray& varregisters)
{
  Object* first = reinterpret_cast<Object*>(life.Entries()[0]);
  assert(first->isStructure());
  Structure* firststr = OBJECT_CAST(Structure*, first);
  assert(firststr->getFunctor() == AtomTable::start);
  assert(firststr->getArgument(1)->isNumber());
  int offset = 1;

  for (int i = 0; i < firststr->getArgument(1)->getInteger(); i++)
    {
      xregisters.add(i, 0);
    }

  for (int index = 1; index < life.lastEntry(); index++, offset++)
    {
      Object* entry = reinterpret_cast<Object*>(life.Entries()[index]);
      entry = entry->variableDereference();
      
      if (entry->isStructure())
	{
	  Structure* estruct = OBJECT_CAST(Structure*, entry);
	  if (estruct->getFunctor() == AtomTable::yreg)
	    {
	      continue;
	    }
	  else if (estruct->getFunctor() == AtomTable::xreg)
	    {
	      assert(estruct->getArgument(1)->variableDereference()->isNumber());
	      int xreg = estruct->getArgument(1)->variableDereference()->getInteger();
	      xregisters.add(xreg, offset);
	      continue;
	    }
	  assert(estruct->getFunctor() == AtomTable::unify_ref);
	  entry = estruct->getArgument(1)->variableDereference();
	}
      if (entry->isVariable())
	{
	  Variable* var = OBJECT_CAST(Variable*, entry);
	  if (var->isLifeSet())
	    {
	      assert(var->getLife() != 0);
	      u_int varoffset = var->getLife();
	      varregisters.Entries()[varoffset] = offset;
	    }
	  else
	    {
	      varregisters.addEntry(offset);
	      var->setLife(varregisters.lastEntry());
	      varregisters.addEntry(offset);
	    }
	}
      else
	{
	  assert(entry->isInteger());
	  for (int i = 0; i < entry->getInteger(); i++)
	    {
	      xregisters.add(i, offset);
	    }
	}
    }
  
}

//
// Attempt to assign register with range (s,e) to register i
//
bool 
xreglife::addRange(int i, int s, int e)
{
  if (i > size)
    {
      Fatal(__FUNCTION__, "Out of bounds in xreglife");
    }
  llist* n = reginfo[i];
  if (n == NULL)
    {
      llist* add = new llist;
      add->getStart() = s;
      add->getEnd() = e;
      reginfo[i] = add;
      return true;
    }
  if (e < n->getStart())
    {
      llist* add = new llist;
      add->getStart() = s;
      add->getEnd() = e;
      add->getNext() = n;
      reginfo[i] = add;
      return true;
    }
  llist* next = n->getNext();
  while (next != NULL && s > next->getStart())
    {
      n = next;
      next = next->getNext();
    }
  if (next == NULL)
    {
      if (s < n->getEnd())
	{
	  return false;
	}
      llist* add = new llist;
      add->getStart() = s;
      add->getEnd() = e;
      n->getNext() = add;
      return true;
    }
  if ((e > next->getStart()) || (s < n->getEnd()))
    {
      return false;
    }
  
  llist* add = new llist;
  add->getStart() = s;
  add->getEnd() = e;
  add->getNext() = next;
  n->getNext() = add;
  return true;
}

//
// Add (what will be) X registers to the lifetime list
//
void
updateLife(WordArray& life, Object* t)
{
  t = t->variableDereference();
  if (t->isVariable())
    {
      life.addEntry(reinterpret_cast<word32>(t));
    }
  else if (t->isStructure())
    {
      Structure* st = OBJECT_CAST(Structure*, t);
      if (st->getArity() == 1 && st->getFunctor() == AtomTable::xreg)
	{
	  life.addEntry(reinterpret_cast<word32>(t));
	}
    }
}

//
// Test if the supplied term is of the form '$xreg'(A).
// It is assumed A is an integer and is returned if the test succeeds.
//
bool is_xreg(Object* arg, int& reg)
{
  if (!arg->isStructure())
    {
      return false;
    }
  Structure* argstr = OBJECT_CAST(Structure*, arg);
  if (argstr->getFunctor() == AtomTable::xreg)
    {
      assert(argstr->getArity() == 1);
      assert(argstr->getArgument(1)->variableDereference()->isInteger());
      reg = argstr->getArgument(1)->variableDereference()->getInteger();
      return true;
    }
  return false;
}

//
// Test if the supplied term is of the form '$yreg'(A)
//
bool is_yreg(Object* arg)
{
  if (!arg->isStructure())
    {
      return false;
    }
  Structure* argstr = OBJECT_CAST(Structure*, arg);
  return (argstr->getFunctor() == AtomTable::yreg);
}

//
// Return the y register number.
// Assumes input is of the form '$yreg'(A,..)
// and A is a number.
//
int yreg_num(Object* reg)
{
  assert(reg->isStructure());
  Structure* regstr = OBJECT_CAST(Structure*, reg);
  assert(regstr->getFunctor() == AtomTable::yreg);
  assert(regstr->getArgument(1)->variableDereference()->isInteger());
  return(regstr->getArgument(1)->variableDereference()->getInteger());
}

// Test if both terms represent equal registers. 
// I.E. both are '$xreg'(X) or both '$yreg'(Y,...).
//
bool equal_regs(Object* reg1, Object* reg2)
{
  assert(reg1 == reg1->variableDereference());
  assert(reg2 == reg2->variableDereference());
  if (!reg1->isStructure())
    {
      return false;
    }
  assert(reg2->isStructure());
  Structure* s1 = OBJECT_CAST(Structure*, reg1);
  Structure* s2 = OBJECT_CAST(Structure*, reg2);
  if (!s1->getArgument(1)->variableDereference()->isInteger() ||
      !s2->getArgument(1)->variableDereference()->isInteger())
    {
      return false;
    }
  return (s1->getFunctor() == s2->getFunctor() &&
	  s1->getArgument(1)->variableDereference()->getInteger() ==
	  s2->getArgument(1)->variableDereference()->getInteger());
}

//
// The C++ equiv of prefer.ql
//
void 
prefer_registers_aux(WordArray& unravel, xreglife& xregisters, 
		     WordArray& varregisters, int start, int end, int inc)
{
  for (int i = start; i != end; i += inc)
    {
      assert(reinterpret_cast<Object*>(unravel.Entries()[i])->variableDereference()->isStructure());
      Structure* istruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(unravel.Entries()[i])->variableDereference());

      if (istruct->getFunctor() == AtomTable::get &&
	  istruct->getArgument(1) == AtomTable::meta &&
	  istruct->getArgument(2) == AtomTable::variable)
	{
	  assert(istruct->getArity() == 4);
	  Object* arg1 = istruct->getArgument(3)->variableDereference();
	  Object* arg2 = istruct->getArgument(4)->variableDereference();
	  int reg;
	  if (arg1->isVariable() && is_xreg(arg2, reg))
	    {
	      Variable* var = OBJECT_CAST(Variable*, arg1);
	      assert(var->isLifeSet());
	      u_int varoffset = var->getLife();
	      int start = varregisters.Entries()[varoffset-1];
	      int end = varregisters.Entries()[varoffset];
	      if (xregisters.addRange(reg, start, end))
		{
		  *(var->storage()) = reinterpret_cast<heapobject>(arg2);
		}
	    }
	}
      else if (istruct->getFunctor() == AtomTable::put &&
	       istruct->getArgument(1) == AtomTable::meta)
	{
	  assert(istruct->getArity() == 4);
	  Object* arg1 = istruct->getArgument(3)->variableDereference();
	  Object* arg2 = istruct->getArgument(4)->variableDereference();
	  int reg;
	  if (arg1->isVariable() && is_xreg(arg2, reg))
	    {
	      Variable* var = OBJECT_CAST(Variable*, arg1);
	      assert(var->isLifeSet());
	      u_int varoffset = var->getLife();
	      int start = varregisters.Entries()[varoffset-1];
	      int end = varregisters.Entries()[varoffset];
	      if (xregisters.addRange(reg, start, end))
		{
		  *(var->storage()) = reinterpret_cast<heapobject>(arg2);
		}
	    }
	}
    }
}


void prefer_registers(WordArray& unravel, xreglife& xregisters, 
		      WordArray& varregisters, int body)
{
  prefer_registers_aux(unravel, xregisters, varregisters, 
		       unravel.lastEntry() - 1, body - 1, -1);
  prefer_registers_aux(unravel, xregisters, varregisters, 0, body, 1);
}

//
// Life/dead management of registers for assn_elim.
// For x registers the xreg_life array is used,
// and for y registers the second argument of the '$yreg' structure
// is used.
//
void init_live(Object** xreg_life)
{
  for (u_int i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      xreg_life[i] = AtomTable::failure;
    }
}

void make_live(Object* reg, Object* other, Object** xreg_life)
{
  assert(reg == reg->variableDereference());
  assert(other == other->variableDereference());
  assert(reg->isStructure());
  Structure* regstr = OBJECT_CAST(Structure*, reg);
  if (regstr->getFunctor() == AtomTable::xreg)
    {
      Object* arg = regstr->getArgument(1)->variableDereference();
      assert(arg->isInteger());
      assert(arg->getInteger() >= 0);
      assert((u_int)(arg->getInteger()) < NUMBER_X_REGISTERS);
      xreg_life[arg->getInteger()] = other;
    }
  else
    {
      regstr->setArgument(2, other);
    }
}

void make_dead(Object* reg, Object** xreg_life)
{
  assert(reg == reg->variableDereference());
  if(!reg->isStructure())
    {
      return;
    }
  Structure* regstr = OBJECT_CAST(Structure*, reg);
  if (regstr->getFunctor() == AtomTable::xreg)
    {
      Object* arg = regstr->getArgument(1)->variableDereference();
      assert(arg->isInteger());
      assert(arg->getInteger() >= 0);
      assert((u_int)(arg->getInteger()) < NUMBER_X_REGISTERS);
      xreg_life[arg->getInteger()] = AtomTable::failure;
    }
}

bool is_live(Object* reg, Object* other, Object** xreg_life)
{
  assert(reg == reg->variableDereference());
  assert(reg->isStructure());
  other = other->variableDereference();
  Structure* regstr = OBJECT_CAST(Structure*, reg);
  if (regstr->getFunctor() == AtomTable::xreg)
    {
      Object* arg = regstr->getArgument(1)->variableDereference();
      assert(arg->isInteger());
      assert(arg->getInteger() >= 0);
      assert((u_int)(arg->getInteger()) < NUMBER_X_REGISTERS);
      if (other == AtomTable::failure)
	{
	  return (xreg_life[arg->getInteger()] == other);
	}
      else
	{
	  return (equal_regs(xreg_life[arg->getInteger()], other));
	}
    }
  else
    {
      if (other == AtomTable::failure)
	{
	  return (regstr->getArgument(2) == other);
	}
      else
	{
	  return (equal_regs(regstr->getArgument(2), other));
	}
    }
}

//
// Search for any associated puts or sets - used in assn_elim.
//
bool any_assoc_putset(Object* reg, int start, WordArray& instr)
{
  assert(reg == reg->variableDereference());
  for (int i = start; i < instr.lastEntry(); i++)
    {
      assert(reinterpret_cast<Object*>(instr.Entries()[i])->isStructure());
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instr.Entries()[i]));
      if (tstruct->getFunctor() == AtomTable::call_pred)
	{
	  return false;
	}
      else if (tstruct->getFunctor() == AtomTable::get)
	{
	  if (equal_regs(tstruct->getArgument(4), reg))
	    {
	      return true;
	    }
	  else if (tstruct->getArgument(1) == AtomTable::meta &&
		   tstruct->getArgument(2) == AtomTable::value &&
		   equal_regs(tstruct->getArgument(3), reg))
	    {
	      return true;
	    }
	  else if (equal_regs(tstruct->getArgument(3), reg))
	    {
	      return false;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::unify)
	{
	  if (tstruct->getArgument(1) == AtomTable::meta &&
	      tstruct->getArgument(2) == AtomTable::value &&
	      equal_regs(tstruct->getArgument(3), reg))
	    {
	      return true;
	    }
	  else if (tstruct->getArgument(2) == AtomTable::variable &&
		   equal_regs(tstruct->getArgument(3), reg))
	    {
	      return false;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::unify_ref)
	{
	  if (equal_regs(tstruct->getArgument(1), reg))
	    {
	      return false;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::put)
	{
	  Object* arg1 = tstruct->getArgument(1);
	  if (arg1 == AtomTable::meta &&
	      tstruct->getArgument(2) == AtomTable::value &&
	      equal_regs(tstruct->getArgument(3), reg))
	    {
	      return true;
	    }
	  else if (arg1 == AtomTable::substitution ||
		   arg1 == AtomTable::empty_substitution ||
		   arg1 == AtomTable::sub_term)
	    {
	      continue;
	    }
	  else if (tstruct->getArgument(3) != tstruct->getArgument(4) &&
		   equal_regs(tstruct->getArgument(4), reg))
	    {
	      return false;
	    }
	  else if (tstruct->getArgument(2) == AtomTable::variable &&
		   equal_regs(tstruct->getArgument(3), reg))
	    {
	      return false;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::set)
	{
	  if (tstruct->getArgument(1) == AtomTable::meta &&
	      tstruct->getArgument(2) == AtomTable::value &&
	      equal_regs(tstruct->getArgument(3), reg))
	    {
	      return true;
	    }
	  else if (tstruct->getArgument(2) == AtomTable::variable &&
		   equal_regs(tstruct->getArgument(3), reg))
	    {
	      return false;
	    }
	}

    }
    return false;
}

//
// Determine if an allocate is needed.
//
bool
alloc_needed(Object* i) 
{
  i = i->variableDereference();
  Structure* istruct = OBJECT_CAST(Structure*, i);
  Object* fun = istruct->getFunctor();

  if (fun == AtomTable::call_pred)
    {
      return true;
    }
  else if (fun == AtomTable::get_level ||
	   fun == AtomTable::get_level_ancestor)
    {
      Object* arg = istruct->getArgument(1)->variableDereference();
      return (is_yreg(arg));
    }
  if (fun == AtomTable::get ||
      fun == AtomTable::put)
    {
      Object* arg = istruct->getArgument(3)->variableDereference();
      return (is_yreg(arg));
    }
  if (fun == AtomTable::unify ||
      fun == AtomTable::set)
    {
      Object* arg = istruct->getArgument(3)->variableDereference();
      return (is_yreg(arg));
    }
  if (fun == AtomTable::unify_ref)
    {
      Object* arg = istruct->getArgument(1)->variableDereference();
      return (is_yreg(arg));
     }
  return false;
}

//
// Determine the "register number" used for the register arguments
// of pseudo instructions.
//
int psi_reg(Object* arg)
{
  arg = arg->variableDereference();
  int reg;
  if (is_xreg(arg, reg))
    {
      return reg;
    }
  else
    {
      assert(is_yreg(arg));
      return (NUMBER_X_REGISTERS + yreg_num(arg));
    }
}

//
// Write an atom with escapes added as necessary.
//
void writeCAtom(char* atom, QPStream* stream)
{
  for (; *atom != '\0'; atom++)
    {
      if (*atom == '\\' || *atom == '\'')
	    {
	      *stream << *atom;
	    }
      *stream << *atom;
    }
}

//
// Translate instruction data structures and write them to the stream.
//
void writeInstructions(WordArray& instrs, QPStream* stream)
{
  for (int i = 0; i < instrs.lastEntry(); i++)
    {
      assert(reinterpret_cast<Object*>(instrs.Entries()[i])->isStructure());
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instrs.Entries()[i]));
      
      if (tstruct->getFunctor() == AtomTable::call_pred)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  assert(arg1->isAtom());
	  assert(arg2->isInteger());
	  assert(arg3->isInteger());
	  *stream << "\tcall_predicate('";
	  writeCAtom(OBJECT_CAST(Atom*, arg1)->getName(), stream);
	  *stream << "', ";
	  *stream << arg2->getInteger();
	  *stream << ", ";
	  *stream << arg3->getInteger();
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::execute_pred)
	{
	  assert(tstruct->getArity() == 2);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  assert(arg1->isAtom());
	  assert(arg2->isInteger());
	  *stream << "\texecute_predicate('"; 
	  writeCAtom(OBJECT_CAST(Atom*, arg1)->getName(), stream);
	  *stream << "', ";
	  *stream << arg2->getInteger();
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::checkBinder)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  int reg;
	  assert(is_xreg(arg1, reg));
	  (void)is_xreg(arg1, reg);
	  *stream << "\tcheck_binder("; 
	  *stream << reg;
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::allocate)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  *stream << "\tallocate("; 
	  *stream << arg1->getInteger();
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::deallocate)
	{
	  assert(tstruct->getArity() == 1);
	  *stream << "\tdeallocate\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cproceed)
	{
	  assert(tstruct->getArity() == 1);
	  *stream << "\tproceed\n";
	}
      else if (tstruct->getFunctor() == AtomTable::failure)
	{
	  assert(tstruct->getArity() == 1);
	  *stream << "\tfail\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cneck_cut)
	{
	  assert(tstruct->getArity() == 1);
	  *stream << "\tneck_cut\n";
	}
      else if (tstruct->getFunctor() == AtomTable::get_level ||
	       tstruct->getFunctor() == AtomTable::get_level_ancestor)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  int reg;
	  if (is_xreg(arg1, reg))
	    {
	      *stream << "\tget_x_level("; 
	      *stream << reg;
	      *stream << ")\n";
	    }
	  else 
	    {
	      assert(is_yreg(arg1));
	      *stream << "\tget_y_level("; 
	      *stream << yreg_num(arg1);
	      *stream << ")\n";
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::ccut ||
	       tstruct->getFunctor() == AtomTable::cut_ancestor)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();

	  assert(is_yreg(arg1));
	  *stream << "\tcut("; 
	  *stream << yreg_num(arg1);
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr0)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  *stream << "\tpseudo_instr0("; 
	  *stream << arg1->getInteger();
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr1)
	{
	  assert(tstruct->getArity() == 2);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  *stream << "\tpseudo_instr1("; 
	  *stream << arg1->getInteger();
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(2));
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr2)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  *stream << "\tpseudo_instr2("; 
	  *stream << arg1->getInteger();
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(2));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(3));
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr3)
	{
	  assert(tstruct->getArity() == 4);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  *stream << "\tpseudo_instr3("; 
	  *stream << arg1->getInteger();
	  *stream << ", "; 
	  *stream << psi_reg(tstruct->getArgument(2));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(3));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(4));
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr4)
	{
	  assert(tstruct->getArity() == 5);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  *stream << "\tpseudo_instr4("; 
	  *stream << arg1->getInteger();
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(2));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(3));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(4));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(5));
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr5)
	{
	  assert(tstruct->getArity() == 6);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  *stream << "\tpseudo_instr5("; 
	  *stream << arg1->getInteger();
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(2));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(3));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(4));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(5));
	  *stream << ", ";
	  *stream << psi_reg(tstruct->getArgument(6));
	  *stream << ")\n";
	}
      else if (tstruct->getFunctor() == AtomTable::unify_ref)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  int reg;
	  if (is_xreg(arg1, reg))
	    {
	      *stream << "\tunify_x_ref("; 
	      *stream << reg;
	      *stream << ")\n";
	    }
	  else 
	    {
	      assert(is_yreg(arg1));
	      *stream << "\tunify_y_ref("; 
	      *stream << yreg_num(arg1);
	      *stream << ")\n";
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::put)
	{
	  assert(tstruct->getArity() == 4);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  Object* arg4 = tstruct->getArgument(4)->variableDereference();
	  *stream << "\tput_";
	  int reg1, reg2;
	  if (arg1 == AtomTable::constant)
	    {
	      if (arg3->isInteger())
		{
                  *stream << "integer(";
		  *stream << arg3->getInteger();
		  *stream << ", ";
		}
	      else if (arg3->isDouble())
		{
                  *stream << "double(";
		  *stream << arg3->getDouble();
		  *stream << ", ";
		}
	      else if (arg3->isString())
		{
                  *stream << "string(";
		  *(stream) << "\"";
		  string str = OBJECT_CAST(StringObject*, arg3)->getChars();
		  addEscapes(str, '"');
		  *(stream) << str.c_str();
		  *(stream) << "\"";
		  *stream << ", ";
		}

	      else
		{
		  assert(arg3->isAtom());
	          *stream << "constant(";
		  *stream << "'";
		  writeCAtom(OBJECT_CAST(Atom*, arg3)->getName(), stream);
		  *stream << "', ";
		}
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::structure)
	    {
	      *stream << "structure(";
	      assert(arg3->isNumber());
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << arg3->getInteger();
	      *stream << ", ";
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::list)
	    {
	      *stream << "list(";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::quantifier)
	    {
	      *stream << "quantifier(";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::empty_substitution)
	    {
	      *stream << "initial_empty_substitution(";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    } 
	  else if (arg1 == AtomTable::sub_term)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  *stream << "x_term_substitution("; 
		  *stream << reg1;
		  *stream  << ", ";
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  *stream << "y_term_substitution("; 
		  *stream << yreg_num(arg3);
		  *stream << ", ";
		}
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::substitution)
	    {
	      *stream << "substitution(";
	      assert(is_xreg(arg4, reg2));
	      assert(arg3->isNumber());
	      *stream << arg3->getInteger();
	      *stream << ", ";
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  *stream << "x_";
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  *stream << "y_";
		}
	      assert(arg2->isAtom());
	      *stream << OBJECT_CAST(Atom*, arg2)->getName();
	      *stream << "(";
	      *stream << reg1;
	      *stream << ", ";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::object)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  *stream << "x_object_";
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  *stream << "y_object_"; 
		}
	      assert(arg2->isAtom());
	      *stream << OBJECT_CAST(Atom*, arg2)->getName();
	      *stream << "(";
	      *stream << reg1;
	      *stream << ", ";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else
	    {
	      assert(false);
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::get)
	{
	  assert(tstruct->getArity() == 4);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  Object* arg4 = tstruct->getArgument(4)->variableDereference();
	  *stream << "\tget_";
	  int reg1, reg2;
	  if (arg1 == AtomTable::constant)
	    {
	      if (arg3->isInteger())
		{
	          *stream << "integer(";
		  *stream << arg3->getInteger();
		  *stream << ", ";
		}
	      else if (arg3->isDouble())
		{
	          *stream << "double(";
		  *stream << arg3->getDouble();
		  *stream << ", ";
		}
	      else if (arg3->isString())
		{
                  *stream << "string(";
		  *(stream) << "\"";
		  *(stream) << OBJECT_CAST(StringObject*, arg3)->getChars();
		  *(stream) << "\"";
		  *stream << ", ";
		}
	      else
		{
		  assert(arg3->isAtom());
	          *stream << "constant(";
		  *stream << "'";
		  writeCAtom(OBJECT_CAST(Atom*, arg3)->getName(), stream);
		  *stream << "', ";
		}
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::structure)
	    {
	      *stream << "structure('";
	      assert(arg2->isAtom());
	      assert(arg3->isNumber());
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      writeCAtom(OBJECT_CAST(Atom*, arg2)->getName(), stream);
	      *stream << "', ";
	      *stream << arg3->getInteger();
	      *stream << ", ";
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::structure_frame)
	    {
	      *stream << "structure_frame(";
	      assert(arg3->isInteger());
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << arg3->getInteger();
	      *stream << ", ";
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::list)
	    {
	      *stream << "list(";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  *stream << "x_";
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  *stream << "y_"; 
		}
	      assert(arg2->isAtom());
	      *stream << OBJECT_CAST(Atom*, arg2)->getName();
	      *stream << "(";
	      *stream << reg1;
	      *stream << ", ";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::object)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  *stream << "x_object_";
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  *stream << "y_object_"; 
		}
	      assert(arg2->isAtom());
	      *stream << OBJECT_CAST(Atom*, arg2)->getName();
	      *stream << "(";
	      *stream << reg1;
	      *stream << ", ";
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      *stream << reg2;
	      *stream << ")\n";
	    }
	  else
	    {
	      assert(false);
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::unify)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  *stream << "\tunify_";
	  int reg1;
	  if (arg1 == AtomTable::constant)
	    {
	      if (arg3->isInteger())
		{
	          *stream << "integer(";
		  *stream << arg3->getInteger();
		}
	      else if (arg3->isDouble())
		{
	          *stream << "double(";
		  *stream << arg3->getDouble();
		}
	      else if (arg3->isString())
		{
                  *stream << "string(";
		  *(stream) << "\"";
		  *(stream) << OBJECT_CAST(StringObject*, arg3)->getChars();
		  *(stream) << "\"";
		}
	      else
		{
		  assert(arg3->isAtom());
	          *stream << "constant(";
		  *stream << "'";
		  writeCAtom(OBJECT_CAST(Atom*, arg3)->getName(), stream);
		  *stream << "'";
		}
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (arg2 == atoms->add("void"))
		{
		  assert(arg3->isInteger());
		  *stream << "void(";
		  *stream << arg3->getInteger();
		  *stream << ")\n";
		}
	      else
		{
		  if (is_xreg(arg3, reg1))
		    {
		      *stream << "x_";
		    }
		  else 
		    {
		      assert(is_yreg(arg3));
		      reg1 = yreg_num(arg3);
		      *stream << "y_"; 
		    }
		  assert(arg2->isAtom());
		  *stream << OBJECT_CAST(Atom*, arg2)->getName();
		  *stream << "(";
		  *stream << reg1;
		  *stream << ")\n";
		}
	    }
	  else if (arg1 == AtomTable::object)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  *stream << "x_object_";
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  *stream << "y_object_"; 
		}
	      assert(arg2->isAtom());
	      *stream << OBJECT_CAST(Atom*, arg2)->getName();
	      *stream << "(";
	      *stream << reg1;
	      *stream << ")\n";
	    }
	  else
	    {
	      assert(false);
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::set)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  *stream << "\tset_";
	  int reg1;
	  if (arg1 == AtomTable::constant)
	    {
	      if (arg3->isInteger())
		{
	          *stream << "integer(";
		  *stream << arg3->getInteger();
		}
	      else if (arg3->isDouble())
		{
	          *stream << "double(";
		  *stream << arg3->getDouble();
		}
	      else if (arg3->isString())
		{
                  *stream << "string(";
		  *(stream) << "\"";
		  *(stream) << OBJECT_CAST(StringObject*, arg3)->getChars();
		  *(stream) << "\"";
		}
	      else
		{
		  assert(arg3->isAtom());
	          *stream << "constant(";
		  *stream << "'";
		  writeCAtom(OBJECT_CAST(Atom*, arg3)->getName(), stream);
		  *stream << "'";
		}
	      *stream << ")\n";
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (arg2 == atoms->add("void"))
		{
		  assert(arg3->isInteger());
		  *stream << "void(";
		  *stream << arg3->getInteger();
		  *stream << ")\n";
		}
	      else
		{
		  if (is_xreg(arg3, reg1))
		    {
		      *stream << "x_";
		    }
		  else 
		    {
		      assert(is_yreg(arg3));
		      reg1 = yreg_num(arg3);
		      *stream << "y_"; 
		    }
		  assert(arg2->isAtom());
		  *stream << OBJECT_CAST(Atom*, arg2)->getName();
		  *stream << "(";
		  *stream << reg1;
		  *stream << ")\n";
		}
	    }
	  else if (arg1 == AtomTable::object)
	    {
	      if (arg2 == atoms->add("void"))
		{
		  assert(arg3->isInteger());
		  *stream << "object_void(";
		  *stream << arg3->getInteger();
		  *stream << ")\n";
		}
	      else
		{
		  if (is_xreg(arg3, reg1))
		    {
		      *stream << "x_object_";
		    }
		  else 
		    {
		      assert(is_yreg(arg3));
		      reg1 = yreg_num(arg3);
		  *stream << "y_object_"; 
		    }
		  assert(arg2->isAtom());
		  *stream << OBJECT_CAST(Atom*, arg2)->getName();
		  *stream << "(";
		  *stream << reg1;
		  *stream << ")\n";
		}
	    }
	  else
	    {
	      assert(false);
	    }
	} 
      else
	{
	  assert(false);
	}
    }
}

//
// Translate the instructions to object code and dump them into a code block.
//
CodeLoc dumpInstructions(WordArray& instrs)
{
  word8 code[4*WARRAYSIZE];
  CodeLoc pc = code;

  for (int i = 0; i < instrs.lastEntry(); i++)
    {
      assert(reinterpret_cast<Object*>(instrs.Entries()[i])->isStructure());
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instrs.Entries()[i]));
      
      if (tstruct->getFunctor() == AtomTable::put)
	{
	  assert(tstruct->getArity() == 4);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  Object* arg4 = tstruct->getArgument(4)->variableDereference();
	  int reg1, reg2;
	  if (arg1 == AtomTable::constant)
	    {
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
              if (arg3->isAtom())
		{
		  updateInstruction(pc, PUT_CONSTANT);
		  pc += Code::SIZE_OF_INSTRUCTION; 
		  updateConstant(pc,arg3);
		  pc += Code::SIZE_OF_CONSTANT;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		}
	      else if (arg3->isInteger())
		{
		  updateInstruction(pc, PUT_INTEGER);
		  pc += Code::SIZE_OF_INSTRUCTION; 
		  updateInteger(pc,arg3->getInteger());
		  pc += Code::SIZE_OF_INTEGER;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		}
              else if (arg3->isDouble())
		{
		  updateInstruction(pc, PUT_DOUBLE);
		  pc += Code::SIZE_OF_INSTRUCTION; 
		  updateDouble(pc,arg3->getDouble());
		  pc += Code::SIZE_OF_DOUBLE;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		}
	      else
		{
		  assert(arg3->isString());
		  updateInstruction(pc, PUT_STRING);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		  char* c = OBJECT_CAST(StringObject*, arg3)->getChars();
		  int size = strlen(c);
		  strcpy((char*)pc, c);
		  pc += size+1;
		}
	    }
	  else if (arg1 == AtomTable::structure)
	    {
	      assert(arg3->isNumber());
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, PUT_STRUCTURE);
	      pc += Code::SIZE_OF_INSTRUCTION; 
	      updateNumber(pc, arg3->getInteger());
	      pc += Code::SIZE_OF_NUMBER;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::list)
	    {
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, PUT_LIST);
	      pc += Code::SIZE_OF_INSTRUCTION;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::quantifier)
	    {
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, PUT_QUANTIFIER);
	      pc += Code::SIZE_OF_INSTRUCTION;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::empty_substitution)
	    {
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, PUT_INITIAL_EMPTY_SUBSTITUTION);
	      pc += Code::SIZE_OF_INSTRUCTION;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    } 
	  else if (arg1 == AtomTable::sub_term)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  updateInstruction(pc, PUT_X_TERM_SUBSTITUTION);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateRegister(pc, reg1);
		  pc += Code::SIZE_OF_REGISTER;
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  updateInstruction(pc, PUT_Y_TERM_SUBSTITUTION);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateRegister(pc, yreg_num(arg3));
		  pc += Code::SIZE_OF_REGISTER;
		}
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::substitution)
	    {
	      assert(is_xreg(arg4, reg2));
	      assert(arg3->isNumber());
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, PUT_SUBSTITUTION);
	      pc += Code::SIZE_OF_INSTRUCTION;
	      updateNumber(pc, arg3->getInteger());
	      pc += Code::SIZE_OF_NUMBER;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, PUT_X_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, PUT_X_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, PUT_Y_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, PUT_Y_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      updateRegister(pc, reg1);
	      pc += Code::SIZE_OF_REGISTER;
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::object)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, PUT_X_OBJECT_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, PUT_X_OBJECT_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, PUT_Y_OBJECT_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, PUT_Y_OBJECT_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      updateRegister(pc, reg1);
	      pc += Code::SIZE_OF_REGISTER;
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else
	    {
	      assert(false);
	      return NULL;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::get)
	{
	  assert(tstruct->getArity() == 4);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  Object* arg4 = tstruct->getArgument(4)->variableDereference();
	  int reg1, reg2;
	  if (arg1 == AtomTable::constant)
	    {
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
              if (arg3->isAtom())
		{
		  updateInstruction(pc, GET_CONSTANT);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateConstant(pc,arg3);
		  pc += Code::SIZE_OF_CONSTANT;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		}
	      else if (arg3->isInteger())
		{ 
		  updateInstruction(pc, GET_INTEGER);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateInteger(pc,arg3->getInteger());
		  pc += Code::SIZE_OF_INTEGER;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		}
	      else if (arg3->isDouble())
		{ 
		  updateInstruction(pc, GET_DOUBLE);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateDouble(pc,arg3->getDouble());
		  pc += Code::SIZE_OF_DOUBLE;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		}
	      else
		{
		  assert(arg3->isString());
		  updateInstruction(pc, GET_STRING);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateRegister(pc, reg2);
		  pc += Code::SIZE_OF_REGISTER;
		  char* c = OBJECT_CAST(StringObject*, arg3)->getChars();
		  int size = strlen(c);
		  strcpy((char*)pc, c);
		  pc += size+1;
		}

	    }
	  else if (arg1 == AtomTable::structure)
	    {
	      assert(arg2->isAtom());
	      assert(arg3->isNumber());
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, GET_STRUCTURE);
	      pc += Code::SIZE_OF_INSTRUCTION;
	      updateConstant(pc,arg2);
              pc += Code::SIZE_OF_CONSTANT;
	      updateNumber(pc, arg3->getInteger());
	      pc += Code::SIZE_OF_NUMBER;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::structure_frame)
	    {
	      assert(arg3->isNumber());
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, GET_STRUCTURE_FRAME);
	      pc += Code::SIZE_OF_INSTRUCTION;
	      updateNumber(pc, arg3->getInteger());
	      pc += Code::SIZE_OF_NUMBER;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::list)
	    {
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateInstruction(pc, GET_LIST);
	      pc += Code::SIZE_OF_INSTRUCTION;
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, GET_X_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, GET_X_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, GET_Y_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, GET_Y_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      updateRegister(pc, reg1);
	      pc += Code::SIZE_OF_REGISTER;
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else if (arg1 == AtomTable::object)
	    {
	      if (is_xreg(arg3, reg1))
		{
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, GET_X_OBJECT_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, GET_X_OBJECT_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      else 
		{
		  assert(is_yreg(arg3));
		  reg1 = yreg_num(arg3);
		  if (arg2 == AtomTable::variable)
		    {
		      updateInstruction(pc, GET_Y_OBJECT_VARIABLE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		  else
		    {
		      assert(arg2 == AtomTable::value);
		      updateInstruction(pc, GET_Y_OBJECT_VALUE);
		      pc += Code::SIZE_OF_INSTRUCTION;
		    }
		}
	      updateRegister(pc, reg1);
	      pc += Code::SIZE_OF_REGISTER;
	      assert(is_xreg(arg4, reg2));
	      (void)is_xreg(arg4, reg2);
	      updateRegister(pc, reg2);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else
	    {
	      assert(false);
	      return NULL;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::unify)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  int reg1;
	  if (arg1 == AtomTable::constant)
	    {
	      if (arg3->isAtom())
		{
		  updateInstruction(pc, UNIFY_CONSTANT);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateConstant(pc,arg3);
		  pc += Code::SIZE_OF_CONSTANT;
		}
	      else if (arg3->isInteger())
		{
		  updateInstruction(pc, UNIFY_INTEGER);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateInteger(pc,arg3->getInteger());
		  pc += Code::SIZE_OF_INTEGER;
		}
	      else if (arg3->isDouble())
		{
		  updateInstruction(pc, UNIFY_DOUBLE);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateDouble(pc,arg3->getDouble());
		  pc += Code::SIZE_OF_DOUBLE;
		}
	      else
		{
		  assert(arg3->isString());
		  updateInstruction(pc, UNIFY_STRING);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  char* c = OBJECT_CAST(StringObject*, arg3)->getChars();
		  int size = strlen(c);
		  strcpy((char*)pc, c);
		  pc += size+1;
		}
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (arg2 == atoms->add("void"))
		{
		  assert(arg3->isNumber());
		  updateInstruction(pc, UNIFY_VOID);
		  pc += Code::SIZE_OF_INSTRUCTION; 
		  updateNumber(pc, arg3->getInteger());
		  pc += Code::SIZE_OF_NUMBER;
		}
	      else
		{
		  if (is_xreg(arg3, reg1))
		    {
		      if (arg2 == AtomTable::variable)
			{
			  updateInstruction(pc, UNIFY_X_VARIABLE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		      else
			{
			  assert(arg2 == AtomTable::value);
			  updateInstruction(pc, UNIFY_X_VALUE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		    }
		  else 
		    {
		      assert(is_yreg(arg3));
		      reg1 = yreg_num(arg3);
		      if (arg2 == AtomTable::variable)
			{
			  updateInstruction(pc, UNIFY_Y_VARIABLE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		      else
			{
			  assert(arg2 == AtomTable::value);
			  updateInstruction(pc, UNIFY_Y_VALUE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		    }
		  updateRegister(pc, reg1);
		  pc += Code::SIZE_OF_REGISTER;
		}
	    }
	  else 
	    {
	      assert(false);
	      return NULL;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::set)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  int reg1;
	  if (arg1 == AtomTable::constant)
	    {
	      if (arg3->isAtom())
		{
		  updateInstruction(pc, SET_CONSTANT);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateConstant(pc,arg3);
		  pc += Code::SIZE_OF_CONSTANT;
		}
	      else if (arg3->isInteger())
		{
		  updateInstruction(pc, SET_INTEGER);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateInteger(pc,arg3->getInteger());
		  pc += Code::SIZE_OF_INTEGER;
		}
	      else if (arg3->isDouble())
		{
		  updateInstruction(pc, SET_DOUBLE);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  updateDouble(pc,arg3->getDouble());
		  pc += Code::SIZE_OF_DOUBLE;
		}
	      else
		{
		  assert(arg3->isString());
		  updateInstruction(pc, SET_STRING);
		  pc += Code::SIZE_OF_INSTRUCTION;
		  char* c = OBJECT_CAST(StringObject*, arg3)->getChars();
		  int size = strlen(c);
		  strcpy((char*)pc, c);
		  pc += size+1;
		}
	    }
	  else if (arg1 == AtomTable::meta)
	    {
	      if (arg2 == atoms->add("void"))
		{
		  assert(arg3->isNumber());
		  updateInstruction(pc, SET_VOID);
		  pc += Code::SIZE_OF_INSTRUCTION; 
		  updateNumber(pc, arg3->getInteger());
		  pc += Code::SIZE_OF_NUMBER;
		}
	      else
		{
		  if (is_xreg(arg3, reg1))
		    {
		      if (arg2 == AtomTable::variable)
			{
			  updateInstruction(pc, SET_X_VARIABLE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		      else
			{
			  assert(arg2 == AtomTable::value);
			  updateInstruction(pc, SET_X_VALUE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		    }
		  else 
		    {
		      assert(is_yreg(arg3));
		      reg1 = yreg_num(arg3);
		      if (arg2 == AtomTable::variable)
			{
			  updateInstruction(pc, SET_Y_VARIABLE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		      else
			{
			  assert(arg2 == AtomTable::value);
			  updateInstruction(pc, SET_Y_VALUE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		    }
		  updateRegister(pc, reg1);
		  pc += Code::SIZE_OF_REGISTER;
		}
	    }
	  else if (arg1 == AtomTable::object)
	    {
	      if (arg2 == atoms->add("void"))
		{
		  assert(arg3->isNumber());
		  updateInstruction(pc, SET_OBJECT_VOID);
		  pc += Code::SIZE_OF_INSTRUCTION; 
		  updateNumber(pc, arg3->getInteger());
		  pc += Code::SIZE_OF_NUMBER;
		}
	      else
		{
		  if (is_xreg(arg3, reg1))
		    {
		      if (arg2 == AtomTable::variable)
			{
			  updateInstruction(pc, SET_X_OBJECT_VARIABLE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		      else
			{
			  assert(arg2 == AtomTable::value);
			  updateInstruction(pc, SET_X_OBJECT_VALUE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		    }
		  else 
		    {
		      assert(is_yreg(arg3));
		      reg1 = yreg_num(arg3);
		      if (arg2 == AtomTable::variable)
			{
			  updateInstruction(pc, SET_Y_OBJECT_VARIABLE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		      else
			{
			  assert(arg2 == AtomTable::value);
			  updateInstruction(pc, SET_Y_OBJECT_VALUE);
			  pc += Code::SIZE_OF_INSTRUCTION;
			}
		    }
		  updateRegister(pc, reg1);
		  pc += Code::SIZE_OF_REGISTER;
		}
	    }
	  else
	    {
	      assert(false);
	      return NULL;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::call_pred)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg3 = tstruct->getArgument(3)->variableDereference();
	  assert(arg1->isAtom());
	  assert(arg2->isNumber());
	  assert(arg3->isNumber());
	  updateInstruction(pc, CALL_PREDICATE);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateConstant(pc, arg1);
	  pc += Code::SIZE_OF_CONSTANT;
	  updateNumber(pc, arg2->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	  updateNumber(pc, arg3->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	}
      else if (tstruct->getFunctor() == AtomTable::execute_pred)
	{
	  assert(tstruct->getArity() == 2);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  assert(arg1->isAtom());
	  assert(arg2->isNumber());
	  updateInstruction(pc, DB_EXECUTE_PREDICATE);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateConstant(pc, arg1);
	  pc += Code::SIZE_OF_CONSTANT;
	  updateNumber(pc, arg2->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	}
      else if (tstruct->getFunctor() == AtomTable::checkBinder)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  int reg;
	  assert(is_xreg(arg1, reg));
	  (void)is_xreg(arg1, reg);
	  updateInstruction(pc, CHECK_BINDER);
	  pc += Code::SIZE_OF_INSTRUCTION;
 	  updateNumber(pc, reg);
	  pc += Code::SIZE_OF_NUMBER;
	}
      else if (tstruct->getFunctor() == AtomTable::allocate)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isNumber());
	  updateInstruction(pc, ALLOCATE);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateNumber(pc, arg1->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	}
      else if (tstruct->getFunctor() == AtomTable::deallocate)
	{
	  assert(tstruct->getArity() == 1);
	  updateInstruction(pc, DEALLOCATE);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	}
      else if (tstruct->getFunctor() == AtomTable::cproceed)
	{
	  assert(tstruct->getArity() == 1);
	  updateInstruction(pc, DB_PROCEED);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	}
      else if (tstruct->getFunctor() == AtomTable::failure)
	{
	  assert(tstruct->getArity() == 1);
	  updateInstruction(pc, FAIL);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	}
      else if (tstruct->getFunctor() == AtomTable::cneck_cut)
	{
	  assert(tstruct->getArity() == 1);
	  updateInstruction(pc, NECK_CUT);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	}
      else if (tstruct->getFunctor() == AtomTable::get_level ||
	       tstruct->getFunctor() == AtomTable::get_level_ancestor)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  int reg;
	  if (is_xreg(arg1, reg))
	    {
	      updateInstruction(pc, GET_X_LEVEL);
	      pc += Code::SIZE_OF_INSTRUCTION; 
	      updateRegister(pc, reg);
	      pc += Code::SIZE_OF_REGISTER; 
	    }
	  else 
	    {
	      assert(is_yreg(arg1));
	      updateInstruction(pc, GET_Y_LEVEL);
	      pc += Code::SIZE_OF_INSTRUCTION; 
	      updateRegister(pc, yreg_num(arg1));
	      pc += Code::SIZE_OF_REGISTER; 
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::ccut ||
	       tstruct->getFunctor() == AtomTable::cut_ancestor)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  
	  assert(is_yreg(arg1));
	  updateInstruction(pc, CUT);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateRegister(pc, yreg_num(arg1));
	  pc += Code::SIZE_OF_REGISTER; 
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr0)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isNumber());
	  updateInstruction(pc, PSEUDO_INSTR0);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateNumber(pc, arg1->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr1)
	{
	  assert(tstruct->getArity() == 2);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isNumber());
	  updateInstruction(pc, PSEUDO_INSTR1);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateNumber(pc, arg1->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	  updateRegister(pc, psi_reg(tstruct->getArgument(2)));
	  pc += Code::SIZE_OF_REGISTER; 
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr2)
	{
	  assert(tstruct->getArity() == 3);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isNumber());
	  updateInstruction(pc, PSEUDO_INSTR2);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateNumber(pc, arg1->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	  updateRegister(pc, psi_reg(tstruct->getArgument(2)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(3)));
	  pc += Code::SIZE_OF_REGISTER;
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr3)
	{
	  assert(tstruct->getArity() == 4);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isNumber());
	  updateInstruction(pc, PSEUDO_INSTR3);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateNumber(pc, arg1->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	  updateRegister(pc, psi_reg(tstruct->getArgument(2)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(3)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(4)));
	  pc += Code::SIZE_OF_REGISTER;
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr4)
	{
	  assert(tstruct->getArity() == 5);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isNumber());
	  updateInstruction(pc, PSEUDO_INSTR4);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateNumber(pc, arg1->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	  updateRegister(pc, psi_reg(tstruct->getArgument(2)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(3)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(4)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(5)));
	  pc += Code::SIZE_OF_REGISTER;
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr5)
	{
	  assert(tstruct->getArity() == 6);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isNumber());
	  updateInstruction(pc, PSEUDO_INSTR5);
	  pc += Code::SIZE_OF_INSTRUCTION; 
	  updateNumber(pc, arg1->getInteger());
	  pc += Code::SIZE_OF_NUMBER;
	  updateRegister(pc, psi_reg(tstruct->getArgument(2)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(3)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(4)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(5)));
	  pc += Code::SIZE_OF_REGISTER;
 	  updateRegister(pc, psi_reg(tstruct->getArgument(6)));
	  pc += Code::SIZE_OF_REGISTER;
	}
      else if (tstruct->getFunctor() == AtomTable::unify_ref)
	{
	  assert(tstruct->getArity() == 1);
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  int reg;
	  if (is_xreg(arg1, reg))
	    {
	      updateInstruction(pc, UNIFY_X_REF);
	      pc += Code::SIZE_OF_INSTRUCTION; 
	      updateRegister(pc, reg);
	      pc += Code::SIZE_OF_REGISTER;
	    }
	  else 
	    {
	      assert(is_yreg(arg1));
	      updateInstruction(pc, UNIFY_Y_REF);
	      pc += Code::SIZE_OF_INSTRUCTION; 
	      updateRegister(pc, yreg_num(arg1));
	      pc += Code::SIZE_OF_REGISTER;
	    }
	}
      else
	{
	  assert(false);
	  return NULL;
	}
    }
  size_t codeLen = pc - code;

  CodeLoc result = new word8[codeLen];
  memcpy(result, code, codeLen);
  return result;
}

