// display_term.cc -
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
// $Id: display_term.cc,v 1.7 2005/03/08 00:35:02 qp Exp $

#include "config.h"
#ifdef GCC_VERSION_2
#include <ostream.h>
#else
#include <ostream>
#endif

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
	  ostrm << hex << reinterpret_cast<word32>(ref) << "->" << dec;
	  ref = OBJECT_CAST(Reference*, ref)->getReference();
	}

      if (ref->isVariable() &&
	  reinterpret_cast<heapobject*>(ref) >= getTop())
	{
	  ostrm << "<< Invalid reference: " << hex << reinterpret_cast<word32>(ref) << dec << ">>" << endl;
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
	  ostrm << hex << reinterpret_cast<word32>(ref) << "->" << dec;
	  ref = OBJECT_CAST(Reference*, ref)->getReference();
	}
      if (ref->isObjectVariable() &&
	  reinterpret_cast<heapobject*>(ref) >= getTop())
	{
	  ostrm << "<< Invalid reference: " << hex << reinterpret_cast<word32>(ref) << dec << ">>" << endl;
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
      ostrm << "LIST [" << hex << reinterpret_cast<word32>(term) << "]" << dec << endl;

      display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getHead(), depth+1);
      display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getTail(), depth+1);
    }
  else if (term->isStructure())
    {
      ostrm << "STRUCTURE [" << hex << reinterpret_cast<word32>(term) << "]" << dec << endl;

      ostrm << " " << static_cast<u_int>(OBJECT_CAST(Structure*, term)->getArity()) << endl;

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
      ostrm << "QUANTIFIER [" << hex << reinterpret_cast<word32>(term) << "]" << dec << endl;

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
      ostrm << "ATOM:" << hex << reinterpret_cast<word32>(term) << ":" << dec <<atoms.getAtomString(OBJECT_CAST(Atom*, term)) <<  endl;
    }
  else if (term->isNumber())
    {
      ostrm << "INTEGER:" << hex << reinterpret_cast<word32>(term) << ":" << dec << term->getNumber() <<  endl;
    }
  else if (term->isSubstitution())
    {
      ostrm << "SUBSTITUTION" << endl;
    }
  else
    {
      ostrm << "*** Bad Value = " << hex << reinterpret_cast<word32>(term) << ":" << dec <<  endl;
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
      ostrm << "*** Bad Value = " << hex << reinterpret_cast<word32>(term) << dec << endl;
    }
}      

void
Heap::quickDisplayTerm(ostream& ostrm, AtomTable& atoms, Object* term)
{
  quick_display_term(ostrm, atoms, term);
  ostrm << '\0';
}




