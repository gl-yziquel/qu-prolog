// code.h - Storage for holding compiled programs and functions for the
//	    manipulation.
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
// $Id: code.h,v 1.4 2001/11/21 00:21:11 qp Exp $ 

#ifndef	CODE_H
#define	CODE_H

#include <iostream.h>

#include "config.h"

#include "area_offsets.h"
#include "defs.h"
#include "heap_qp.h"
#include "instructions.h"
#include "magic.h"
#include "objects.h"
#include "string_map.h"

//
// Forward declaration.
//
class	PredTab;

//typedef word8 	*CodeLoc;
typedef word32   CodeOffset;

  
//
// Fetch 'n' bytes from the code area.
//
inline word8 get1Byte(CodeLoc& loc)
  {
    // No endian issues for a single byte quantity
    return(*loc++);
  }

inline word16	get2Bytes(CodeLoc& loc)
{
  word16 data;

  data = *loc++;
  data = (data << 8) | *loc++;

  return(data);
}

inline word32	get4Bytes(CodeLoc& loc)
{
  word32 data;

  data = *loc++;
  data = (data << 8) | *loc++;
  data = (data << 8) | *loc++;
  data = (data << 8) | *loc++;

  return(data);
}

//
// Update the specified location with new data.
//
inline void	update1Byte(CodeLoc loc, word8 data)
{
  //Stamp();

  *loc = data;
}
inline void	update2Bytes(CodeLoc loc, word16 data)
{
  //Stamp();

  *loc++ = (data & 0xff00) >> 8;
  *loc   =  data & 0x00ff;
}
inline void	update4Bytes(CodeLoc loc, word32 data)
{
  //Stamp();

  *loc++ = (data & 0xff000000) >> 24;
  *loc++ = (data & 0x00ff0000) >> 16;
  *loc++ = (data & 0x0000ff00) >> 8;
  *loc   =  data & 0x000000ff;
}
//
// Fetch different kinds of data from the code area.  The pointer to
// the area (the parameter) is incremented past the data after reading.
//
//
inline word8 getInstruction(CodeLoc& loc) { return(get1Byte(loc)); }
inline Object* getConstant(CodeLoc& loc) 
{
  return(reinterpret_cast<Object*>(get4Bytes(loc)));
}
inline word8 getRegister(CodeLoc& loc) { return(get1Byte(loc)); }
inline word8 getNumber(CodeLoc& loc)  { return(get1Byte(loc)); }
inline word32 getAddress(CodeLoc& loc)  { return(get4Bytes(loc)); }
inline int32 getInteger(CodeLoc& loc)  { return((int32)(get4Bytes(loc))); }
inline CodeLoc getCodeLoc(CodeLoc& loc)  
{ return((CodeLoc)get4Bytes(loc)); }
inline word16 getOffset(CodeLoc& loc)  { return(get2Bytes(loc)); }
inline Atom* getPredAtom(CodeLoc& loc)  
{ 
  Object* a = reinterpret_cast<Object*>(get4Bytes(loc));
  DEBUG_ASSERT(a->isAtom());
  return(reinterpret_cast<Atom*>(a));
}
inline word16 getTableSize(CodeLoc& loc)  { return(get2Bytes(loc)); }

//
// Update the code area with the new data.
//
inline void	updateInstruction(const CodeLoc loc, const word8 data)
{ update1Byte(loc, data); }
inline void	updateConstant(const CodeLoc loc, Object* data)
{ update4Bytes(loc, reinterpret_cast<word32>(data)); }
inline void	updateInteger(const CodeLoc loc, int32 data)
{ update4Bytes(loc, (word32)(data)); }
inline void	updateRegister(const CodeLoc loc, const word8 data)
{ update1Byte(loc, data); }
inline void	updateNumber(const CodeLoc loc, const word8 data)
{ update1Byte(loc, data); }
inline void	updateAddress(const CodeLoc loc, const word32 data)
{ update4Bytes(loc, data); }
inline void	updateCodeLoc(const CodeLoc loc, const CodeLoc data)
{ update4Bytes(loc, (word32)data); }
inline void	updateOffset(const CodeLoc loc, const word16 data)
{ update2Bytes(loc, data); }
inline void	updatePredAtom(const CodeLoc loc, const Atom* data)
{ update4Bytes(loc, reinterpret_cast<word32>(data)); }
inline void	updateTableSize(const CodeLoc loc, const word16 data)
{ update2Bytes(loc, data); }
//
//  Area for storing static code
//
class   StaticCodeArea
{

private:
  word32	allocated_size;
  CodeLoc       base;
  CodeLoc       top;
  CodeLoc       last;

protected:
  virtual       const char      *getAreaName(void) const = 0;

public:
  StaticCodeArea(word32 size);
  virtual ~StaticCodeArea(void);

  CodeLoc getTopOfStack(void) const       { return(top); }
  CodeLoc getBaseOfStack(void) const       { return(base); }
  word32  allocatedSize(void) const       { return(allocated_size); }

  CodeLoc allocateElements(const word32 n)
  {
    CodeLoc currtop = top;
    if (top + n >= last)
    {
      OutOfPage(__FUNCTION__,
                getAreaName(),
		allocated_size / K);
    }
    else
    {
      top += n;
      return(currtop);
    }
  }
  void saveArea(ostream& ostrm, const u_long magic) const;

  void readData(istream& istrm, const word32 readSize);

  void loadArea(istream& istrm);

  void loadFileSegment(istream& istrm, const word32 size)
    {
      readData(istrm, size);
    }
  
};

class	Code : public StaticCodeArea,
	       public Timestamp
{

private:
  //
  // Return the name of the table.
  //
  virtual const char *getAreaName(void) const { return("code area"); }
  
  //
  // Push 'n' bytes into the code area.
  //
  void push1Byte(word8 data) { update1Byte(allocateElements(1), data); }
  void push2Bytes(word16 data) { update2Bytes(allocateElements(2), data); }
  void push4Bytes(word32 data) { update4Bytes(allocateElements(4), data); }
  
  //
  // Resolve the CALL_PREDICATE and EXECUTE_PREDICATE instructions.
  //
  void resolveCallInstruction(const CodeLoc loc,
			      const PredLoc pred,
			      const word8 EscInst,
			      const word8 AddrInst,
			      PredTab& predicates,
			      Code* code);

  //
  // Turn atom and number pointers into tagged offsets and turn code pointers
  // into code offsets.
  //
  void pointersToOffsets(CodeLoc pc, const CodeLoc end, AtomTable& atoms);

  //
  // Turn tagged offsets into atoms and numbers and turn code offsets
  // into code pointers.
  //
  void offsetsToPointers(CodeLoc pc, const CodeLoc end, AtomTable& atoms);

public:
  
  //
  // Size of different kinds of data in the code area.
  //
  static const	size_t	SIZE_OF_INSTRUCTION	= 1;
  typedef word8 InstructionSizedType;

  static const	size_t	SIZE_OF_CONSTANT	= 4;
  typedef word32 ConstantSizedType;

  static const	size_t	SIZE_OF_INTEGER	        = 4;
  typedef word32 IntegerSizedType;

  static const	size_t	SIZE_OF_REGISTER	= 1;
  typedef word8 RegisterSizedType;

  static const	size_t	SIZE_OF_NUMBER		= 1;
  typedef word8 NumberSizedType;

  static const size_t	SIZE_OF_ADDRESS		= 4;
  typedef word32 AddressSizedType;

  static const	size_t	SIZE_OF_OFFSET		= 2;
  typedef word16 OffsetSizedType;

  static const	size_t	SIZE_OF_PRED		= 4;
  typedef word32 PredSizedType;

  static const	size_t	SIZE_OF_TABLE_SIZE	= 2;
  typedef word16 TableSizeSizedType;
  
  static const word32	SIZE_OF_HEADER		=
    SIZE_OF_CONSTANT + SIZE_OF_NUMBER + SIZE_OF_OFFSET;

  //
  // The Fail label for hash tables in code area.
  //
  // XXX This is very probably broken.
  static const	word32	FAIL			= 65535;
  
  Code(word32 CodeSize)
    : StaticCodeArea (CodeSize)
    {}
  
  //
  // Push different kinds of data into the code area.
  //
  // If AtomLoc or word32 changes representation, then a bug may occur
  // if putPredAtom is not changed.
  //
  void	pushInstruction(const word8 data) { push1Byte(data); }
  void	pushConstant(const Object* data) 
    { 
      push4Bytes(reinterpret_cast<word32>(data)); 
    }
  void	pushRegister(const word8 data) { push1Byte(data); }
  void	pushNumber(const word8 data) { push1Byte(data); }
  void	pushAddress(const word32 data) { push4Bytes(data); }
  void	pushCodeLoc(const CodeLoc data) { push4Bytes((word32)data); }
  void	pushOffset(const word16 data) { push2Bytes(data); }
  void	pushPredAtom(const Atom* data) 
    { 
      push4Bytes(reinterpret_cast<word32>(data)); 
    }
  void	pushTableSize(const word16 data) { push2Bytes(data); }
  
  //
  // The following manipulation requires a bit of finesse.
  // The CALL_ADDRESS and CALL_ESCAPE instructions are smaller than the 
  // EXECUTE_PREDICATE instruction, so we have to move stuff around a bit.
  // The EXECUTE_ADDRESS and EXECUTE_ESCAPE instructions are likewise smaller.
  // 
  void	updateCallInstruction(const CodeLoc loc,
			      const word8 inst,
			      const CodeLoc addr);
  
  //
  // Retrieve the number of Y registers available from a CALL
  // instruction.
  //
  word32	getNumYRegs(const CodeLoc loc) const
  {
    CodeLoc	calln;
    
    calln = loc - SIZE_OF_NUMBER;
    return(getNumber(calln));
  }
  
  //
  // Return the top of the area.
  //
  CodeLoc getTop(void) const { return(getTopOfStack()); }
  CodeLoc getBase(void) const { return(getBaseOfStack()); }
  
  //
  // Procedures for linking.
  //
  
  //
  // Read the predicate together with its preamble and store them in the
  // code area.
  // Return whether it is successful or not.
  //
  bool	addPredicate(istream& istrm, const char *file, const StringMap& map,
		     const StringMapLoc base,
		     AtomTable* atoms, PredTab& predicates, Code* code);
  
  //
  // Resolve all the references to atoms, predicates, and create hash
  // table for "switch" instructions.
  //
  void resolveCode(CodeLoc pc, 
		   const CodeLoc end, 
		   const StringMap& string_map, 
		   const StringMapLoc string_base,
		   PredTab& predicates,
		   AtomTable* atoms,
		   Code* code);

  //
  // Returns the size of the argument type indicated by char.
  //
  size_t argSize(const char) const;

  //
  // Total size of the code area.
  //
  word32 size(void) const { return(allocatedSize()); }
  
  //
  // Save the code area.
  //
  void	save(ostream& ostrm, AtomTable& atoms); 
  
  //
  // Restore the code area.
  //
  void	load(istream& istrm, AtomTable& atoms);

};

#endif	// CODE_H


