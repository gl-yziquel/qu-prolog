// display_term.cc -
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
// $Id: display_term.cc,v 1.2 2000/12/13 23:10:01 qp Exp $

#include <ostream.h>

//#include "atom_table.h"
#include "heap_qp.h"
#include "indent.h"

void
Heap::display_term(ostream& ostrm, AtomTable& atoms, Object* term,
		   const size_t depth)
{
  Indent(ostrm, depth);

  if (term->isVariable())
    {
      Object* ref = term;

      ostrm << "VARIABLE ";

      while (ref->isVariable() && 
	     ref != OBJECT_CAST(Reference*, ref)->getReference() &&
	     reinterpret_cast<heapobject*>(ref) < getTop())
	{
	  ostrm.form("%#lx->", reinterpret_cast<word32>(ref));
	  ref = OBJECT_CAST(Reference*, ref)->getReference();
	}

      if (ref->isVariable() &&
	  reinterpret_cast<heapobject*>(ref) >= getTop())
	{
	  ostrm.form("<< Invalid reference: %#lx>>\n", 
		     reinterpret_cast<word32>(ref));
	}
      else if (ref->isVariable() && 
	       ref == OBJECT_CAST(Reference*, ref)->getReference())
	{
	  if (!OBJECT_CAST(Reference*, ref)->hasExtraInfo())
	    {
	      ostrm << "<< No Extra Info >>";
	    }
	  else
	    {
	      Atom* name = OBJECT_CAST(Reference*, ref)->getName();
	      if (name == NULL)
		{
		  ostrm << ": << No Name >>";
		}
	      else
		{
		  ostrm << ":" << atoms.getAtomString(name);
		}
	      // Print out any other information.
	      if (OBJECT_CAST(Reference*, ref)->isOccursChecked())
		{
		  ostrm << ":" << "occurs";
		}
	      if (OBJECT_CAST(Reference*,ref)->isThawed())
		{
		  ostrm << ":" << "thawed";
		}
	      if (OBJECT_CAST(Reference*,ref)->isFrozen())
		{
		  ostrm << ":" << "frozen";
		}
	    }
	}
      else
	{
	  ostrm << endl;
	  
	  display_term(ostrm, atoms, ref, depth);
	}
    }

  else if (term->isObjectVariable())
    {
      Object* ref = term;

      ostrm << "OBJECT_VARIABLE";

      ostrm << " ";

      while (ref->isObjectVariable() && 
	     ref != OBJECT_CAST(Reference*, ref)->getReference() &&
	     reinterpret_cast<heapobject*>(ref) < getTop())
	{
	  ostrm.form("%#lx->", reinterpret_cast<word32>(ref));
	  ref = OBJECT_CAST(Reference*, ref)->getReference();
	}
      if (ref->isObjectVariable() &&
	  reinterpret_cast<heapobject*>(ref) >= getTop())
	{
	  ostrm.form("<< Invalid reference: %#lx>>\n", 
		     reinterpret_cast<word32>(ref));
	}
      else if (ref->isObjectVariable() && 
	       ref == OBJECT_CAST(Reference*, ref)->getReference())
	{
	  if (!OBJECT_CAST(Reference*, ref)->hasExtraInfo())
	    {
	      ostrm << "<< No Extra Info >>";
	    }
	  else
	    {
	      Atom* name = OBJECT_CAST(Reference*, ref)->getName();
	      if (name == NULL)
		{
		  ostrm << ": << No Name >>";
		}
	      else
		{
		  ostrm << ":" << atoms.getAtomString(name);
		}

	      if (ref->isThawedVariable())
		{
		  ostrm << ":" << "thawed";
		}
	      if (ref->isFrozenVariable())
		{
		  ostrm << ":" << "frozen";
		}
	    }
	}
      else
	{
	  ostrm << endl;
      
	  display_term(ostrm, atoms, ref, depth);
	}
    }
  else if (term->isCons())
    {
      ostrm.form("LIST [%#lx]\n", reinterpret_cast<word32>(term));

      display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getHead(), depth+1);
      display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getTail(), depth+1);
    }
  else if (term->isStructure())
    {
      ostrm.form("STRUCTURE [%#lx]", reinterpret_cast<word32>(term));

      ostrm << " " << OBJECT_CAST(Structure*, term)->getArity() << endl;

      display_term(ostrm, atoms, 
		   OBJECT_CAST(Structure*, term)->getFunctor(), depth+1);

      for (u_long i = 1; i <= OBJECT_CAST(Structure*, term)->getArity(); i++)
	{
	  display_term(ostrm, atoms,
		       OBJECT_CAST(Structure*, term)->getArgument(i), depth+1);
	}
    }
  else if (term->isQuantifiedTerm())
    {
      ostrm.form("QUANTIFIER [%#lx]\n", reinterpret_cast<word32>(term));

      display_term(ostrm, atoms, 
		   OBJECT_CAST(QuantifiedTerm*, term)->getQuantifier(), 
		   depth+1);
      display_term(ostrm, atoms, 
		   OBJECT_CAST(QuantifiedTerm*, term)->getBoundVars(), 
		   depth+1);
      display_term(ostrm, atoms, 
		   OBJECT_CAST(QuantifiedTerm*, term)->getBody(), depth+1);
    }
  else if (term->isAtom())
    {
      ostrm.form("ATOM:%#lx:%s\n", 
                 reinterpret_cast<word32>(term),
		 atoms.getAtomString(OBJECT_CAST(Atom*, term)));
    }
  else if (term->isNumber())
    {
      ostrm.form("INTEGER:%#lx:%ld\n", reinterpret_cast<word32>(term),
		 term->getNumber());
    }
  else if (term->isSubstitution())
    {
      ostrm << "SUBSTITUTION" << endl;
    }
  else
    {
      ostrm.form("*** Bad Value = %#lx\n", reinterpret_cast<word32>(term));
    }
}      

void
Heap::displayTerm(ostream& ostrm, AtomTable& atoms,
		  Object* term, const size_t depth)
{
  display_term(ostrm, atoms, term, depth);
}

void
Heap::quick_display_term(ostream& ostrm, AtomTable& atoms, Object* term)
{
  term = term->variableDereference();
  
  if (term->isVariable())
    {
      cerr << "_V";
    }
  else if (term->isObjectVariable())
    {
      ostrm << "_OV";
    }
  else if (term->isCons())
    {
      ostrm << "[";

      quick_display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getHead());
      
      ostrm << "|";
      
      quick_display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getTail());
      
      ostrm << "]";
    }
  else if (term->isStructure())
    {
      quick_display_term(ostrm, atoms,
			 OBJECT_CAST(Structure*, term)->getFunctor() );
      
      if (OBJECT_CAST(Structure*, term)->getArity() > 0)
	{
	  ostrm << "(";
	  
	  for (u_long i = 1; i <= OBJECT_CAST(Structure*, term)->getArity(); i++)
	    {
	      quick_display_term(ostrm, atoms,
				 OBJECT_CAST(Structure*, term)->getArgument(i));
	      if (i < OBJECT_CAST(Structure*, term)->getArity())
		{
		  ostrm << ",";
		}
	    }
	  
	  ostrm << ")";
	}
    }
  else if (term->isQuantifiedTerm())
    {
      quick_display_term(ostrm, atoms,
			 OBJECT_CAST(QuantifiedTerm*, term)->getQuantifier());
      ostrm << " ";
      quick_display_term(ostrm, atoms, 
			 OBJECT_CAST(QuantifiedTerm*, term)->getBoundVars());
      ostrm << " ";
      quick_display_term(ostrm, atoms, 
			 OBJECT_CAST(QuantifiedTerm*, term)->getBody());
    }
  else if (term->isAtom())
    {
      ostrm << atoms.getAtomString(OBJECT_CAST(Atom*, term));
    }
  else if (term->isNumber())
    {
      ostrm << term->getNumber();
    }
  else if (term->isSubstitution())
    {
      ostrm << "SUBSTITUTION" << endl;
    }
  else
    {
      ostrm.form("*** Bad Value = %ld\n", reinterpret_cast<word32>(term));
    }
}      

void
Heap::quickDisplayTerm(ostream& ostrm, AtomTable& atoms, Object* term)
{
  quick_display_term(ostrm, atoms, term);
  ostrm << '\0';
}




