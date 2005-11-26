// objects.h
//
// A representation of the Prolog-level obejcts for the Qu-Prolog
// Abstract Machine (QuAM). 
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
// $Id: objects.h,v 1.11 2005/11/26 23:34:30 qp Exp $

#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>

//#include "atom_table.h"
#include "debug.h" // Qu-Prolog debug code facilities
#include "defs.h" // Qu-Prolog data type definitions &c.

#include "string_table.h"
#include "truth3.h"

// Dynamic cast doesn't work the way it should.
#define OBJECT_CAST(type, expr) reinterpret_cast<type>(expr)

// Forward references for all the subclasses of Object, inserted so
// that ordering of the subclasses is not important (and also to
// provide a handy reference :-)

class AtomTable;
class Constant; // abstract
class Atom;
class Short;
class Long;
class Double;
class Reference; // abstract
class Variable;
class ObjectVariable;
class Structure;
class List;	// abstract
class Cons;
class QuantifiedTerm;
class Substitution;
class SubstitutionBlock;


//////////////////////////////////////////////////////////////////////
// The Object class specification

class Object
{
  
  // The Heap and Object classes are tightly bound.  Actually,
  // probably more like besotted teenagers feverishly necking in the
  // back of an old combi van with fogged-up windows and squeaking
  // suspension.  But they claim to be just friends. And who are we
  // to argue?
  
  friend class Heap;
  friend class AtomTable;
  
protected:
  // The following is a summary of the uses of the tagword. The
  // lower byte is always enough to distinguish two types.
  //
  //
  // #=================#============#================#==========#====#
  // | Type            | Top 23 bts | Option (3bts)  | TypeFlag | GC |
  // #=================#============#================#==========#====#
  // | Variable        :      0...0 : occr,info,temp :   0 0 0  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | ObjectVariable  :      0...0 :local,info,temp :   0 0 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // |   Reference     :      x...x :    x,   x,   x :   0 0 x  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Cons            :  see notes : type,type,invrt:   0 1 0  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Structure       : arity      :    0,   0,   0 :   0 1 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // |   Any Structure :      x...x :    x,   x,   x :   0 1 x  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Quantified Term :      0...0 :    0,   0,   0 :   1 0 0  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Atom            : see notes  :    0,   0,   0 :   1 0 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Short           : value      :    1,   0,   0 :   1 0 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Long            :      0...0 :    1,   0,   1 :   1 0 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Double          :      0...0 :    1,   1,   0 :   1 0 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // |   Any Constant  :      x...x :    x,   x,   x :   1 0 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // |   Any Number    :      x...x :    1,   x,   x :   1 0 1  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // | Substitution    :      0...0 :    0,   0,   0 :   1 1 0  : 00 |
  // +-----------------+------------+----------------+----------+----+
  // |SubstitutionBlock:       size :    0,   0,invrt:   1 1 1  : 00 |
  // #=================#============#================#==========#====#   
  //
  // More detail on each type:
  //
  // Object
  // ~~~~~~
  //
  // Variable
  // ~~~~~~~~   
  //             : | byte | byte | byte | x      x        x    ttt gc |
  //         TAG : | 0                  | occurs info blk temp 000 00 |
  //
  //   REFERENCE : ptr to refered Object (unbound, ptr to TAG)
  // [      NAME : info[1] = pointer to Atom        | extra info block
  // |    DELAYS : info[2] = pointer to delays List ] (optional)
  //
  //
  // ObjectVariable
  // ~~~~~~~~~~~~~~
  //             : | byte | byte | byte | x     x        x    ttt gc |
  //         TAG : | 0                  | local info blk temp 001 00 |
  //   REFERENCE : ptr to refered ObjectVariable (unbound, ptr to TAG)
  // [      NAME = info[1] = pointer to Atom          | extra info block
  // |    DELAYS : info[2] = pointer to delays List   | (optional)
  // |  DISTINCT : info[3] = pointer to distinct List ]
  //
  //
  // Cons
  // ~~~~
  //             : | byte | byte | byte | x    x    x      ttt gc |
  //         TAG : | See notes          | type type invert 010 00 |
  //        HEAD = pointer to Object (depending on type)
  //        TAIL = pointer to Object (a Cons, an Atom [ Nil ] or a Variable)
  //
  // A Cons (list) may be restricted to hold only particular objects,
  // by specifying various values as the top two xxx bits:
  //
  //     In particular:
  //
  //          000 -- any Prolog Object
  //          010 -- objvariables only (distinctness info)
  //          10x -- substitution blocks only (substitutions) (x = invertible)
  //          110 -- code (delayed problems)
  //
  // The semantics of restricting a Cons (list) is to assert that the head
  // of the list is of the given type, and that the tail of the list,
  // should it be a list having has the same property.
  //
  // Additionally, if a list is a substitution block list, then
  // information about invertibility is also stored.
  //
  //	     100 -- Not invertible
  //         101 -- Invertible
  //
  // Structure
  // ~~~~~~~~~   
  //             : | byte | byte | byte | xxx ttt gc |
  //         TAG : | arity              | 000 011 00 |
  //     FUNCTOR : pointer to functor
  // { ARGUMENTx : pointer to argument(x) } 
  //                 (arity arguments, indexed from 1. argument 0 is
  //                  defined to be the functor.) 
  //  
  // QuantifiedTerm
  // ~~~~~~~~~~~~~~
  //             : | byte | byte | byte | xxx ttt gc |
  //         TAG : | 0                  | 000 100 00 |
  //       QUANT : pointer to Object (-generally- Atom of Variable)
  //       BOUND : pointer to List of ObjVars
  //        BODY : pointer to Object
  //
  // Atom
  // ~~~~
  //             : | byte | byte | byte             | xxx ttt gc |
  //         TAG : | 0           | 0000 00 atom int | 000 101 00 |
  //        NAME : pointer to asciiz
  //       ASSOC : unsigned long or pointer to Atom as appropriate
  // (NB.  Atoms do not reside on the heap.  They reside in an Atom
  // Table.)
  //
  // Whether another atom or an integer is associated with the
  // atom is represented within the third 
  //
  //               0000 0000 -- no associated info
  //               0000 0001 -- integer associated
  //               0000 0010 -- atom associated 
  //
  // Short
  // ~~~~~
  //             : | byte | byte | byte | xxx ttt gc |
  //         TAG : | value              | 100 101 00 |
  //
  // Value is tored as a 24-bit integer, with the standard integer encoding
  // for the compiler and platform.
  //
  // Long
  // ~~~~
  //             : | byte | byte | byte | xxx TTT GC |
  //         TAG : | 0                  | 101 101 00 |
  //        LONG : long
  //
  // [4] A Long is stored as a C long int, which is at least 32-bits in
  // size.  It is, however, implementation dependent.
  //
  // Double
  // ~~~~~
  //             : | byte | byte | byte | xxx TTT GC |
  //         TAG : | 0                  | 110 101 00 |
  //      DOUBLE : val[2]
  //
  //
  // Substitution
  // ~~~~~~~~~~~~
  //             : | byte | byte | byte | xxx TTT GC |
  //         TAG : | 0                  | 000 110 00 |
  //       SUBST : pointer to List of SubBlocks
  //        TERM : pointer to Object
  //
  // SubstitutionBlock
  // ~~~~~~~~~~~~~~~~~
  //             : | byte | byte | byte | xx x      TTT GC |
  //         TAG : | size               | 00 invert 111 00 |
  // {      DOMx : pointer to ObjectVariable } 
  // {      RANx : pointer to Object         }
  //          (size * pairs of replacements)
  
  // Buckybits for the broadest types in the tag
  static const heapobject TypeMask =	0x0000001CUL;
  static const heapobject TypeVar =	0x00000000UL;	// variable
  static const heapobject TypeObjVar =	0x00000004UL;	// object variable
  static const heapobject TypeCons =	0x00000008UL;	// Cons (list)
  static const heapobject TypeStruct =	0x0000000CUL;	// struct
  static const heapobject TypeQuant =	0x00000010UL;	// quantifier
  static const heapobject TypeConst =	0x00000014UL;	// constant
  static const heapobject TypeSubst =	0x00000018UL;	// substitution
  static const heapobject TypeSubBlock =0x0000001CUL;   // substitution block

protected:			// contents of structure
  heapobject tag;

public:
  // For masking the top bits
  static const heapobject TopMask =    0xffffff00UL;

  // Special tag for unify_x_ref instruction
  static const heapobject RefTag = 0x000000FCUL;

  // Garbage collection bits and mask
  static const heapobject GC_M    = 0x00000002UL;
  static const heapobject GC_F    = 0x00000001UL;
  static const heapobject GC_Mask = GC_M | GC_F;

public:
  // uTags == microtags == Small tags used for switching purposes
  static const heapobject uVar = TypeVar >> 2;
  static const heapobject uObjVar = TypeObjVar >> 2;
  static const heapobject uCons = TypeCons >> 2;
  static const heapobject uStruct = TypeStruct >> 2;
  static const heapobject uQuant = TypeQuant >> 2;
  static const heapobject uConst = TypeConst >> 2;
  static const heapobject uSubst = TypeSubst >> 2;
  static const heapobject uSubsBlock = TypeSubBlock >> 2;
  
  typedef heapobject uTag;
  inline uTag utag(void) const;

  inline heapobject getTag(void) const;

public:
  // Returns the first word of the storage after the tag
  inline heapobject *storage(void);

public:
  // Some boolean functions for eliciting the type of Object being
  // pointed to.
  
  inline bool isRefTag(void) const;
  inline bool isVariable(void) const;
  inline bool isNormalVariable(void) const;
  inline bool isFrozenVariable(void) const;
  inline bool isThawedVariable(void) const;
  inline bool isObjectVariable(void) const;
  inline bool isLocalObjectVariable(void) const;
  inline bool isAnyVariable(void) const;
  
  inline bool isStructure(void) const;

  inline bool isList(void) const;	// isCons() || isNil()
  inline bool isCons(void) const;
  inline bool isNil(void) const;	// isAtom() && this == AtomTable::Nil
  inline bool inList(Object*);  

  inline bool isAnyStructure(void) const;
  
  inline bool isQuantifiedTerm(void) const;

  inline bool isConstant(void) const;
  inline bool isNumber(void) const;
  inline bool isInteger(void) const;
  inline bool isAtom(void) const;
  inline bool isShort(void) const;
  inline bool isLong(void) const;
  inline bool isDouble(void) const;
  inline bool isSubstitution(void) const;
  inline bool isSubstitutionBlock(void) const;
  
  // Returns the value of a Short or Long.
  inline int getNumber(void);
  inline double getDouble(void);

  inline heapobject* last(void);

  // Garbage collection methods
  inline bool gc_isMarked(void) const;
  inline void gc_mark(void);
  inline void gc_setfs(void);
  inline bool gc_isFset(void) const;
  inline void gc_unsetf(void);

public:
  // Dummy constructor - needed for atom constructor.
  Object(void) {}

  // Dispatching for the size() message, which returns the size of
  // the Object being pointed to
  size_t size_dispatch(void);
  
#ifdef QP_DEBUG
public:
  // Testing substitution block lists to see if they are legal
  inline bool isLegalSub(void);
  inline bool hasLegalSub(void);

  // Dispatching for the DEBUG printMe() message, which displays a
  // representation of the Object being pointed to
  inline void printMe_dispatch(AtomTable&, bool all = true);
#endif

  //
  // variableDereference() follows the (ob)variable-reference chain from
  // an object -- iteratively, not recursively -- and returns the object
  // at the end of the (ob)variable chain.
  //
  inline Object* variableDereference();
  
  //
  // Check whether the object variable is in the distinctness information list.
  // NOTE:
  //	ObjectVariable should be dereferenced before this function is called.
  //
  bool isObjectVariableInDistinctList(const ObjectVariable *objvar) const;
  
  //
  // Check whether two object variables are distinct. 
  // Return true if object variables are known to be distinct.
  // NOTE:
  //	ObjectVariable1 and ObjectVariable2 should be dereferenced 
  //	before this function is called.
  //
  bool distinctFrom(const Object *objvar) const; 
  
  //
  // The function returns true if the object_variable is distinct from
  // all domains in the i-th to SubSize-th entry of the substitution.
  // 
  bool distinctFromDomains(const SubstitutionBlock *sub_block, size_t i);


  //
  // The substitution is scanned from right to left for the local object 
  // variable on a domain or range place. If the last occurrence of the 
  // local object variable is as a range element, then save the corresponding
  // domain element and the new end of the substitution which 
  // is one where local object variable is found.
  //
  bool containLocalObjectVariable(Object* sub, Object*& domElem, 
				  Object*& newEnd);
  
  inline bool equalConstants(Object* const2);
  
  //
  // Return the length of the bound variables list.
  //
  size_t boundListLength(void);
  
};


//////////////////////////////////////////////////////////////////////
// The Constant class specification
// (NB. This is intended to be an ``abstract'' class)

class Constant : public Object
{
protected:
  friend class Heap;
  friend class Object;
  friend class AtomTable;

  // Buckybits
  static const heapobject ConstMask =	0x000000e0UL;
  static const heapobject ConstAtom =	0x00000000UL;
  static const heapobject ConstShort =	0x00000080UL;
  static const heapobject ConstLong =	0x000000a0UL;
  static const heapobject ConstDouble =	0x000000c0UL;
  // The high 2 bits of the tag are used for the high two bits of
  // The long - the long is shifted up by 2 bits to free the bottom
  // two bits for garbage collection bits.
  static const heapobject LongBits =    0xc0000000UL;
  // The bottom 2 bits of a double (each word) is stored in the top
  // 4 bits of the tag
  static const heapobject DoubleBits1   = 0xc0000000UL;
  static const heapobject DoubleBits2   = 0x30000000UL;
  static const heapobject DoubleLowbits = 0x00000003UL;
 
  
public:
  // Dummy constructor - needed for atom constructor
  Constant(void):Object() {}

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
  
};

//////////////////////////////////////////////////////////////////////
// The Atom class specification
// (NB. These do not appear on the heap.)

class Atom : public Constant
{
protected:
  // Offset into the string table for the atom's name
  StringLoc string_table_loc;

  // Either an Atom * or int, depending on hasAssociatedItem()
  word32 associatedval;

  // Pointers into the Record database.
  StackLoc first_ref;
  StackLoc last_ref;
  
public:
  // Buckybits 
  static const heapobject AssociatedMask =	0x00000300UL;
  static const heapobject AssociatedNone =	0x00000000UL;
  static const heapobject AssociatedInteger =	0x00000100UL;
  static const heapobject AssociatedAtom =	0x00000200UL;
  
  typedef heapobject AssociatedItem;

public:
  // Constructor - needed to initialize atom table.
  Atom(void):Constant()
    {
      tag = TypeConst | Constant::ConstAtom;
      string_table_loc = EMPTY_LOC;
      associatedval = 0;
      first_ref = EMPTY_LOC;
      last_ref = EMPTY_LOC;
    }

public:  
  // String related things
  inline void setStringTableLoc(const StringLoc);
  inline StackLoc getStringTableLoc(void) const;

  inline bool isEmpty(void) const;

  inline bool getBool(void) const;

public:
  // Accessors and mutators
  inline bool hasAssociatedItem(void) const;

  inline bool hasAssociatedAtom(void) const;
  inline bool hasAssociatedInteger(void) const;

  inline void associateInteger(const int val);
  inline void associateAtom(Atom *atm);
  inline Atom *getAssociatedAtom(void) const;
  inline int getAssociatedInteger(void) const;

public:
  // Record database stuff.
  inline StackLoc getFirstRef(void) const;
  inline StackLoc getLastRef(void) const;

  inline void setFirstRef(const StackLoc);
  inline void setLastRef(const StackLoc);

public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Short class specification

class Short : public Constant
{
protected:
  // Value is encoded in tag; no extra elements required
  
public:
  static const heapobject Zero    = (TypeConst | Constant::ConstShort);
  // Accessors and mutators
  inline long getValue(void) const;
  
public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
  
};

//////////////////////////////////////////////////////////////////////
// The Double class specification

class Double : public Constant
{
protected:
  // The value of the Double, stored as a pointer to a double in C
  // memory
  heapobject x[2];
  
public:
  // Accessor (no mutator)
  inline double getValue(void) const;
  
public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Long class specification

class Long : public Constant
{
protected:
  // The value of the Long
  word32 value;
  
public:
  // Accessor (no mutator)
  inline long getValue(void) const;
  
public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Structure class specification
// (A functor and n arguments.  The functor is argument 0.)

class Structure : public Object 
{
protected:
  // Arity is encoded in the tag
  Object *argument[1]; // arity + 1 arguments (argument[0] is functor)
  
public:
  // Accessor for arity (there is no mutator to avoid realloc() type
  // problems.
  inline size_t getArity(void) const;
  
  // Accessor and mutator for arguments.  Argument 0 is the functor,
  // arguments proper are in the range 1..`arity'.
  inline Object *getArgument(const size_t n) const;
  inline void setArgument(const size_t n, Object * plobj);
  
  // Additional wrappers for argument 0
  inline Object *getFunctor(void) const;
  inline void setFunctor(Object * plobj);
  
public:
  // Note, not static, since the size depends on the number of
  // arguments.
  inline size_t size(void) const;

  // Does the real work of figuring out the size.
  static inline size_t size(size_t arity);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Cons class specification
//

class Cons: public Object
{
protected:
  Object *head;
  Object *tail;

public:
  static const heapobject FlagTypeMask =		0x000000c0UL;

  static const heapobject FlagAnyList =			0x00000000UL;
  static const heapobject FlagObjectVariableList = 	0x00000040UL;
  static const heapobject FlagSubstitutionBlockList =	0x00000080UL;
  static const heapobject FlagDelayedProblemList =	0x000000c0UL;

  static const heapobject FlagInvertibleMask =		0x00000020UL;
  
  static const heapobject FlagNotInvertible =		0x00000000UL;
  static const heapobject FlagInvertible =		0x00000020UL;
  static const u_int TailOffset = 2;

public:
  static inline size_t size(void);
  inline void makeSubstitutionBlockList(void);
  inline void makeObjectVariableList(void);
  inline void makeDelayedProblemList(void);

  inline bool isAnyList(void) const;
  inline bool isSubstitutionBlockList(void) const;
  inline bool isObjectVariableList(void) const;
  inline bool isDelayedProblemList(void) const;

public:
  inline void makeInvertible(void);

  inline bool isInvertible(void) const;

public:
  inline void setHead(Object * const);
  inline Object *getHead(void) const;
  
  inline void setTail(Object * const);
  inline Object *getTail(void) const;
  inline Object **getTailAddress(void);
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The QuantifiedTerm class specification

class QuantifiedTerm : public Object
{
protected:
  Object *quantifier;
  Object *boundvars;
  Object *body;
  
public:
  // Accessors
  inline Object *getQuantifier(void) const;
  inline Object *getBoundVars(void) const; // A list of some sort
  inline Object *getBody(void) const;
  
  // Mutators
  inline void setQuantifier(Object *o);
  inline void setBoundVars(Object *l);
  inline void setBody(Object *o);
  
  
public:
  static inline size_t size(void);
  
#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Substitution class specification

class Substitution : public Object
{
protected:
  Object *sub_block_list; // A Prolog list of parallel substitutions
  Object *term;

public:
  // Accessors
  inline Object *getSubstitutionBlockList(void) const;
  inline Object *getTerm(void) const;

  // Mutators/
  inline void setSubstitutionBlockList(Object *l);
  inline void setTerm(Object *o);

public:
  static inline size_t size(void);

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The SubstitutionBlock class specification
// (A list of parallel substitutions to be performed on a term)

class SubstitutionBlock: public Object
{  
  friend class Heap;
protected:
  // Size of block is encoded in the tag
  struct {
    ObjectVariable *dom;
    Object *ran;
  } substitution[1];

public:
  // Buckybits
  static const heapobject InvertibleMask =      0x00000020UL;
  static const heapobject FlagInvertible =	0x00000020UL;
  static const heapobject FlagNotInvertible =	0x00000000UL;

  // Accessor type for Invertible
  enum Invertible {
    NotInvertible = 0UL,
    IsInvertible = FlagInvertible
  };

  // Accessors
  inline size_t getSize(void) const;
  inline ObjectVariable *getDomain(const size_t n) const;
  inline Object *getRange(const size_t n) const;

  // Mutators
  inline void decrementSize(void);

  inline void setDomain(const size_t n, Object *dom);
  inline void setRange(const size_t n, Object *ran);
  inline void setSubstitutionPair(const size_t n,
				  Object *dom, Object *ran);

  // Invertibility operations
  inline bool isInvertible(void) const;
  inline void makeInvertible(void);

  // Miscellaneous
  inline bool containsLocal(void) const;


public:
  // Note, not static, as size depends on the size of storage for
  // underlying domain/range pairs.
  inline size_t size(void) const;

  // Does the real work of figuring out the size.
  static inline size_t size(size_t sub_size);

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The Reference class specification
// (NB. This is intended to be an ``abstract'' class)

class Reference : public Object
{
protected:
  Object *info[1];

  // In a Variable that has extra information:
  // info[0] = reference
  // info[1] = name (Atom *)
  // info[2] = delayed problem list (Object *)

  // In an ObjectVariable that has extra information:
  // info[0] = reference
  // info[1] = name (Atom *)
  // info[2] = delayed problem list (Object *)
  // info[3] = distinctness information (Object *)

public:
  static const u_int NameOffset = 2;
  static const u_int DelaysOffset = 3;
  // Buckybits
  static const heapobject FlagExtraMask = 	0x000000d0UL;

  static const heapobject FlagOccurs =		0x00000080UL;
  static const heapobject FlagExtraInfo =	0x00000040UL;
  static const heapobject FlagTemperature =	0x00000020UL;
  static const heapobject FlagCollected =       0x00000100UL;
  static const heapobject FlagPerm =            0x00000200UL;

  // Accessor type for Temperature
  enum Temperature {
    Thawed = 0UL,
    Frozen = FlagTemperature
  };

  // Accessor type for OccursCheck
  enum OccursCheck {
    NoOccursCheck = 0UL,
    HasOccursCheck = FlagOccurs
  };

  // Accessors and mutators
  inline Object *getReference(void) const;
  inline void setReference(Object *plobj);

  inline bool hasExtraInfo(void) const;
  inline void setExtraInfo(void);

  inline Atom *getName(void) const;
  inline heapobject *getNameAddress(void);
  inline void setName(Object*);

  // Delay chains
  inline Object *getDelays(void) const;
  inline heapobject *getDelaysAddress(void);
  inline void setDelays(Object*);

  // Temperature operations
  inline void freeze(void);
  inline bool isFrozen(void);
  inline void thaw(void);
  inline bool isThawed(void);

  // OccursCheck operations
  inline bool isOccursChecked(void) const;
  inline void setOccursCheck(void);

  // Collection operations
  inline bool isCollected(void) const;
  inline void setCollectedFlag(void);
  inline void unsetCollectedFlag(void);

  // Perm vars operations
  inline bool isPerm(void) const;
  inline void setPermFlag(void); 

  inline bool isUnbound(void) const;
};

//////////////////////////////////////////////////////////////////////
// The Variable class specification
// (An Object which is a reference to another Object)

class Variable : public Reference
{
public:
  // No extra functionality required beyond what is inherited from
  // Reference

public:
  // Note, not static, since the size depends on the 
  // possible presence of extra information.
  inline size_t size(void) const;
  
  // Does the real work of figuring out the size.
  static inline size_t size(bool has_extra_info);

  inline bool isLifeSet(void) const;
  inline u_int getLife(void) const;
  inline void setLife(u_int); 

  // Copy the tags of another variable (without extra info)
  // to this var (with extra info).

  inline void copyTag(Object*);
  
#ifdef QP_DEBUG
public:
    inline void printMe(AtomTable&, bool);
#endif
};

//////////////////////////////////////////////////////////////////////
// The ObjectVariable class specification

class ObjectVariable: public Reference
{
public:
  static const u_int DistinctnessOffset = 4;
  static const heapobject FlagLocalMask = 	0x00000080UL;

  static const heapobject FlagLocal =		0x00000080UL;


  // Accessors and mutators
  inline Object *getDistinctness(void) const;
  inline heapobject *getDistinctnessAddress(void);
  inline void setDistinctness(Object * l);

  inline void setLocal(void);
  inline bool isLocal(void) const;

public:
  // Note, not static, as the size depends on the possible presence of
  // extra information.
  inline size_t size(void) const;

  // Does the real work of figuring out the size.
  static inline size_t size(bool has_extra_info);

  bool isObjectVariableInDomain(SubstitutionBlock *);

  inline void makeLocalObjectVariable(void);

#ifdef QP_DEBUG
public:
  inline void printMe(AtomTable&, bool);
#endif
};

//
//
// ----------------------------
//  Bodies of inline functions
// ----------------------------
//
//

#endif // OBJECTS_H
#ifndef OBJECTS_H_INLINE // MEGA-KLUDGE!!!!!!
#define OBJECTS_H_INLINE
//#ifndef HEAP_H
//#include "heap.h" // KLUDGE!!!!!!

#include "atom_table.h"

//////////////////////////////////////////////////////////////////////
// Inline functions for the Object class



inline Object::uTag
Object::utag(void) const
{
  return static_cast<uTag>((tag & TypeMask) >> 2);
}

inline heapobject 
Object::getTag(void) const
{
  return tag;
}

inline heapobject *
Object::storage(void)
{
  assert(isCons() ||
	       isAnyVariable() ||
	       isStructure() ||
	       isQuantifiedTerm() ||
	       isSubstitutionBlock());

  return reinterpret_cast<heapobject *>(this) + 1;
}

inline bool Object::isRefTag(void) const
{
  return tag == RefTag;
}

inline bool Object::isVariable(void) const
{
  return (tag & TypeMask) == TypeVar;
}

inline bool Object::isNormalVariable(void) const
{
  return tag == TypeVar;
}

inline bool Object::isFrozenVariable(void) const
{
  return (tag & (TypeMask | Reference::FlagTemperature))
    == (TypeVar | Reference::Frozen);
}

inline bool Object::isThawedVariable(void) const
{
  return (tag & (TypeMask | Reference::FlagTemperature))
    == (TypeVar | Reference::Thawed);
}

inline bool Object::isObjectVariable(void) const
{
  return (tag & TypeMask) == TypeObjVar;
}

inline bool Object::isLocalObjectVariable(void) const
{
  return ((tag & (TypeMask | ObjectVariable::FlagLocalMask))
    == (TypeObjVar | ObjectVariable::FlagLocal));
}

inline bool Object::isAnyVariable(void) const
{
  return (tag & TypeMask & (~(TypeVar ^ TypeObjVar))) == TypeVar;
}

inline bool Object::isStructure(void) const
{
  return (tag & TypeMask) == TypeStruct;
}

inline bool Object::isCons() const
{
  return (tag & TypeMask) == TypeCons;
}

inline bool Object::isNil(void) const
{
  return this == AtomTable::nil;
}

inline bool Object::isList(void) const
{
  return isCons() || isNil();
}

inline bool Object::isAnyStructure(void) const
{
  return isStructure() || isCons();
}

inline bool Object::isQuantifiedTerm(void) const
{
  return (tag & TypeMask) == TypeQuant;
}

inline bool Object::isConstant(void) const
{
  return (tag & TypeMask) == TypeConst;
}

inline bool Object::isNumber(void) const
{
  return isConstant ()
    && ((tag & Constant::ConstMask) != Constant::ConstAtom);
}

inline bool Object::isAtom(void) const
{
  return (tag & (TypeMask | Constant::ConstMask))
    == (TypeConst | Constant::ConstAtom);
}

inline bool Object::isShort(void) const
{
  return (tag & (TypeMask | Constant::ConstMask))
    == (TypeConst | Constant::ConstShort);
}

inline bool Object::isLong(void) const
{
  return (tag & (TypeMask | Constant::ConstMask))
    == (TypeConst | Constant::ConstLong);
}

inline bool Object::isInteger(void) const
{
  return 
    ((tag & (TypeMask | Constant::ConstMask))
      == (TypeConst | Constant::ConstShort))
    ||
    ((tag & (TypeMask | Constant::ConstMask))
      == (TypeConst | Constant::ConstLong));
}

inline bool Object::isDouble(void) const
{
  return (tag & (TypeMask | Constant::ConstMask))
    == (TypeConst | Constant::ConstDouble);
}

inline bool Object::isSubstitution(void) const
{
  return (tag & TypeMask) == TypeSubst;
}

inline bool Object::isSubstitutionBlock(void) const
{
  return (tag & TypeMask ) == TypeSubBlock;
}

inline heapobject* Object::last(void)
{
  assert(!isNumber());
  assert(size_dispatch() > 1);
  return (reinterpret_cast<heapobject*>(this) + size_dispatch() - 1);
}

inline bool Object::gc_isMarked(void) const
{
  return ((tag & GC_M) == GC_M);
}

inline void Object::gc_mark(void)
{
  tag |= GC_M;
}

// Set the F bit for the GC on all but the first "argument" of the
// object.
inline void Object::gc_setfs(void)
{
  assert(!isNumber());
  assert(size_dispatch() > 1);
  heapobject* x = reinterpret_cast<heapobject*>(this);
  for (u_int i = 1; i < size_dispatch(); i++)
    {
      x[i] |= GC_F;
    }
}

inline bool Object::gc_isFset(void) const
{
  return ((tag & GC_M) == GC_F);
}

inline void Object::gc_unsetf(void)
{
  tag &= ~GC_F;
}

#ifdef QP_DEBUG

inline bool Object::isLegalSub(void)
{
   if (isNil())
     {
       return true;
     }
   if (!isCons())
     {
       return false;
     }
   Cons* sub = OBJECT_CAST(Cons*, this);
   if (!sub->isSubstitutionBlockList() || 
       !sub->getTail()->isLegalSub() || !sub->getHead()->isSubstitutionBlock())
     {
       return false;
     }
   SubstitutionBlock* subblock = OBJECT_CAST(SubstitutionBlock*, sub->getHead());
   if (subblock->getSize() == 0)
     {
       return false;
     }
   for (size_t i = 1; i <= subblock->getSize(); i++)
     {
        if (!subblock->getRange(i)->variableDereference()->hasLegalSub())
         {
           return false;
         }
      }
   return true;
}

inline bool Object::hasLegalSub(void)
{
   if (!isSubstitution())
     {
        return true;
     }
   return (OBJECT_CAST(Substitution*, this)->getSubstitutionBlockList()->isLegalSub());
}
   
// The next best thing to generic dispatching

inline void Object::printMe_dispatch(AtomTable& atoms, bool all)
{
  if (this == NULL)
    {
	    std::cerr << "(undefined)";
      return;
    }
  
  switch (utag ())
    {
    case uVar:
      OBJECT_CAST(Variable *, this)->printMe(atoms, all);
      break;
    case uObjVar:
      OBJECT_CAST(ObjectVariable *, this)->printMe(atoms, all);
      break;
    case uStruct:
      OBJECT_CAST(Structure *, this)->printMe(atoms, all);
      break;
    case uCons:
      OBJECT_CAST(Cons *, this)->printMe(atoms, all);
      break;
    case uQuant:
      OBJECT_CAST(QuantifiedTerm *, this)->printMe(atoms, all);
      break;
    case uConst:
      if (isAtom())
	OBJECT_CAST(Atom *, this)->printMe(atoms, all);
      else if (isShort())
	OBJECT_CAST(Short *, this)->printMe(atoms, all);
      else if (isLong())
	OBJECT_CAST(Long *, this)->printMe(atoms, all);
      else if (isDouble())
	OBJECT_CAST(Double *, this)->printMe(atoms, all);
      else
	{
		std::cerr << "Bogus const type" << std::endl;
		std::cerr << (word32)(this) << " -> " << *((heapobject*)(this)) << std::endl;
	  assert(false);
	  return;
	}
      break;
    case uSubst:
      OBJECT_CAST(Substitution *, this)->printMe(atoms, all);
      break;
    case uSubsBlock:
      OBJECT_CAST(SubstitutionBlock *, this)->printMe(atoms, all);
      break;
    default:
      // Not all uTags considered!
      std::cerr << "Bogus type" << std::endl;
      std::cerr << (word32)(this) << " -> " << *((heapobject*)(this)) << std::endl;
      assert(false);
    }
}

#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Atom class


inline StringLoc Atom::getStringTableLoc(void) const
{
  assert(sizeof(StringLoc) == sizeof(heapobject));

  return string_table_loc;
}

inline void Atom::setStringTableLoc(const StringLoc stl)
{
  assert(sizeof(StringLoc) == sizeof(heapobject));
  assert(string_table_loc == EMPTY_LOC);

  string_table_loc = stl;
}

inline bool Atom::isEmpty(void) const
{
  assert(sizeof(StringLoc) == sizeof(heapobject));

  return string_table_loc == EMPTY_LOC;
}

inline bool Atom::getBool(void) const
{
  return this == AtomTable::success;
}

inline bool
Atom::hasAssociatedItem(void) const
{
  return (tag & AssociatedMask) != 0;
}

inline bool
Atom::hasAssociatedAtom(void) const
{
  return (tag & AssociatedMask) == AssociatedAtom;
}

inline bool
Atom::hasAssociatedInteger(void) const
{
  return (tag & AssociatedMask) == AssociatedInteger;
}

inline void Atom::associateInteger(const int val)
{
  tag = (tag & ~AssociatedMask) | AssociatedInteger;
  associatedval = val;
}

inline void Atom::associateAtom(Atom *atm)
{
  tag = (tag & ~AssociatedMask) | AssociatedAtom;
  associatedval = reinterpret_cast<word32>(atm);
}

inline Atom *Atom::getAssociatedAtom(void) const
{
  assert(sizeof(void *) == sizeof(heapobject));
  assert(hasAssociatedAtom());

  return reinterpret_cast<Atom *>(associatedval);
}

inline int Atom::getAssociatedInteger (void) const
{
  assert(sizeof(void *) == sizeof(heapobject));
  assert(hasAssociatedInteger());

  return associatedval;
}
inline StackLoc Atom::getFirstRef(void) const
{
  return(first_ref);
}

inline StackLoc Atom::getLastRef(void) const
{
  return(last_ref);
}

inline void Atom::setFirstRef(const StackLoc loc)
{
  first_ref = loc;
}

inline void Atom::setLastRef(const StackLoc loc)
{
  last_ref = loc;
}

inline size_t Atom::size(void)
{
  return sizeof(Atom) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Atom::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] Atom: \""
       << atoms.getAtomString(this) << "\" ";
  
#ifndef WIN32
  switch (hasAssociatedItem())
    {
    case AssociatedNone:
	    std::cerr << "(no info)";
      break;
    case AssociatedInteger:
      std::cerr << "int: " << getAssociatedInteger();
      break;
    case AssociatedAtom:
      std::cerr << "atom: [" << std::hex << (word32) getAssociatedAtom() << std::dec << "]";
      break;
    }
#endif
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Short class

inline long Short::getValue(void) const
{
  // N.B. The alternative of using >> 8 is apparently not portable
  // in the case of signed quantities.
  return (long)(tag & TopMask) / 256;
}

inline size_t Short::size(void)
{
  return sizeof(Short) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Short::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] Short[" 
       << (word32)(tag & GC_Mask) << "]: \""
       << getValue() << "\" ";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Double class
inline double Double::getValue(void) const
{
  double res;
  word32 d[2];
  d[0] = x[0] | ((tag & DoubleBits1) >> 30);
  d[1] = x[1] | ((tag & DoubleBits2) >> 28);
  memcpy(&res, d, sizeof(double));
  return res;
}

#ifdef QP_DEBUG
inline void Double::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << hex << (word32) this << dec << "] Double: \""
       << getValue() << "\" ";
}
#endif

inline size_t Double::size(void) 
{
  return sizeof(Double) / BYTES_PER_WORD;
}

//////////////////////////////////////////////////////////////////////
// Inline functions for the Long class

inline long Long::getValue(void) const
{
  assert(sizeof(long) == sizeof(heapobject));

  return (long)(((value >> 2) & ~LongBits) | (tag & LongBits));
}

inline size_t Long::size(void)
{
  return sizeof(Long) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Long::printMe(AtomTable& atoms, bool)
{
	std::cerr << "[" << std::hex << (int32) this << std::dec << "] Long:[" 
       << (word32)(tag & GC_Mask) << "] \""
       << getValue() << "\" ";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Structure class

inline size_t Structure::getArity(void) const
{
  return (tag & TopMask) >> 8;
}


// Returns argument `n' of the Structure, with argument 0 being
// considered as a reference to the functor.

inline Object *Structure::getArgument(const size_t n) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only access valid arguments
  assert(0 <= n && n <= getArity());
  
  return argument[n];
}

inline Object *Structure::getFunctor(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return getArgument(0);
}

// Sets argument `n' of the Structure to `plobj', again, with argument
// 0 being considered the functor.
inline void Structure::setArgument(const size_t n, Object * plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid arguments
  assert(0 <= n && n <= getArity ());
  
  argument[n] = plobj;
}

inline void Structure::setFunctor(Object * plobj)
{
  setArgument(0, plobj);
}

inline size_t Structure::size(void) const
{
  return size(getArity());
}

inline size_t Structure::size(size_t arity)
{
  return arity + sizeof(Structure) / BYTES_PER_WORD;
}

#ifdef QP_DEBUG
inline void Structure::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] Structure:[" 
       << (word32)(tag & GC_Mask) << "] functor: [ ";
  getFunctor()->printMe_dispatch(atoms, all);
  std::cerr << " ] ";
  for (size_t i = 1; i <= getArity(); i++)
    {
	    std::cerr << i << ": [ ";
      getArgument(i)->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Cons class

inline size_t Cons::size(void)
{
  return(sizeof(Cons) / BYTES_PER_WORD);
}

inline void 
Cons::makeSubstitutionBlockList(void)
{
  assert(isAnyList());

  tag |= FlagSubstitutionBlockList;
}

inline void
Cons::makeObjectVariableList(void)
{
  assert(isAnyList());

  tag |= FlagObjectVariableList;
}

inline void
Cons::makeDelayedProblemList(void)
{
  assert(isAnyList());

  tag |= FlagDelayedProblemList;
}

inline bool
Cons::isAnyList(void) const
{
  return (tag & FlagTypeMask) == FlagAnyList;
}

inline bool
Cons::isSubstitutionBlockList(void) const
{
  return (tag & FlagSubstitutionBlockList) == FlagSubstitutionBlockList;
}

 
inline bool 
Cons::isDelayedProblemList(void) const
{
  return (tag & FlagTypeMask) == FlagDelayedProblemList;
}

inline void
Cons::makeInvertible(void)
{
  assert(isSubstitutionBlockList());

  tag |= FlagInvertible;
}
  
inline bool
Cons::isInvertible(void) const
{
  assert(isSubstitutionBlockList());

  return (tag & FlagInvertibleMask) == FlagInvertible;
}

inline void
Cons::setHead(Object* const plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  head = plobj;
}

inline Object *
Cons::getHead(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return head;
}

inline void 
Cons::setTail(Object* const plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  tail = plobj;
}

inline Object *
Cons::getTail(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return tail;
}

inline Object **
Cons::getTailAddress(void)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return &tail;
}

#ifdef QP_DEBUG
inline void Cons::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] Cons:[" 
       << (word32)(tag & GC_Mask) << "] ";
  if (isSubstitutionBlockList()) 
    {
	    std::cerr << "(Sub) ";
      if (isInvertible()) std::cerr << "(Invertible) ";
    }
  std::cerr << " head: [ ";
  getHead()->printMe_dispatch(atoms, all);
  std::cerr << " ] tail: [ ";
  getTail()->printMe_dispatch(atoms, all);
  std::cerr << " ]";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the QuantifiedTerm class

inline size_t QuantifiedTerm::size(void)
{
  return sizeof(QuantifiedTerm) / BYTES_PER_WORD;
}

inline Object *QuantifiedTerm::getQuantifier(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return quantifier;
}

inline Object *QuantifiedTerm::getBoundVars(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return boundvars;
}

inline Object *QuantifiedTerm::getBody(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return body;
}

inline void QuantifiedTerm::setQuantifier(Object *o)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  quantifier = o;
}

inline void QuantifiedTerm::setBoundVars(Object *l)
{
  assert(sizeof(Object *) == sizeof(heapobject));
  assert(l->isList() || l->isVariable());

  boundvars = l;
}

inline void QuantifiedTerm::setBody(Object *o)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  body = o;
}

#ifdef QP_DEBUG
inline void QuantifiedTerm::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] QuantifiedTerm: quantifier:[" 
       << (word32)(tag & GC_Mask) << "] [ ";
  getQuantifier()->printMe_dispatch(atoms, all);
  std::cerr << " ] boundvars: [ ";
  getBoundVars()->printMe_dispatch(atoms, all);
  std::cerr << " ] body: [ ";
  getBody()->printMe_dispatch(atoms, all);
  std::cerr << " ]";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the Substitution class

inline size_t Substitution::size(void)
{
  return sizeof(Substitution) / BYTES_PER_WORD;
}

inline Object *Substitution::getSubstitutionBlockList(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return sub_block_list;
}

inline Object *Substitution::getTerm(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return term;
}

inline void Substitution::setSubstitutionBlockList(Object *l)
{
  assert(sizeof(Object *) == sizeof(heapobject));
  assert(l->isList());

  sub_block_list = l;
}

inline void Substitution::setTerm(Object *o)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  term = o;
}



#ifdef QP_DEBUG
inline void Substitution::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] Substitution: subst:[" 
       << (word32)(tag & GC_Mask) << "] [ ";
  getSubstitutionBlockList()->printMe_dispatch(atoms, all);
  std::cerr << " ] term: [ ";
  getTerm()->printMe_dispatch(atoms, all);
  std::cerr << " ]";
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the SubstitutionBlock class

inline size_t SubstitutionBlock::size(void) const
{
  return size(getSize());
}

inline size_t SubstitutionBlock::size(size_t sub_size)
{
  return sizeof(SubstitutionBlock) / BYTES_PER_WORD + (sub_size - 1) * 2;
}

inline bool
SubstitutionBlock::isInvertible(void) const
{
  return (tag & InvertibleMask) == FlagInvertible;
}

inline void SubstitutionBlock::makeInvertible(void)
{
  tag |= FlagInvertible;
}

inline size_t SubstitutionBlock::getSize(void) const
{
  return (tag & TopMask) >> 8;
}

inline ObjectVariable *SubstitutionBlock::getDomain(const size_t n) const
{
  // Can only access valid pairs
  assert(1 <= n && n <= getSize());
  
  return substitution[n-1].dom;
}



inline Object *SubstitutionBlock::getRange(const size_t n) const
{
  // Can only access valid pairs
  assert(1 <= n && n <= getSize());
  
  return substitution[n-1].ran;
}

inline void SubstitutionBlock::decrementSize(void)
{
  assert(getSize() > 0);

  const size_t new_size = getSize() - 1;

  tag = (tag & ~TopMask) | (new_size << 8);
}

inline void SubstitutionBlock::setDomain(const size_t n, Object *dom)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid pairs
//  assert(1 <= n && n <= getSize());
//  assert(dom->isObjectVariable());

  substitution[n-1].dom = OBJECT_CAST(ObjectVariable*, dom);
}

inline void SubstitutionBlock::setRange(const size_t n, Object *ran)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid pairs
//  assert(1 <= n && n <= getSize());

  substitution[n-1].ran = ran;
}

inline void SubstitutionBlock::setSubstitutionPair(const size_t n,
						   Object *dom,
						   Object *ran)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Can only set valid pairs
  assert(1 <= n && n <= getSize());

  assert(dom->isObjectVariable());

  substitution[n-1].dom = OBJECT_CAST(ObjectVariable*, dom);
  substitution[n-1].ran = ran;
}

//
// Check whether the substitution contains any local object variable on 
// the first range (or domain) position. If it is the case, it means that
// all the other ranges (or domains) are local object variables as well.
//
inline bool SubstitutionBlock::containsLocal(void) const
{
  assert(getSize() > 0);

  return getDomain(1)->isLocalObjectVariable() ||
    getRange(1)->isLocalObjectVariable();
}

#ifdef QP_DEBUG
inline void SubstitutionBlock::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] SubstitutionBlock:[" 
       << (word32)(tag & GC_Mask) << "] ";
  if (isInvertible()) { std::cerr << "(invertible) "; }
  for (size_t i = 1; i <= getSize(); i++)
    {
	    std::cerr << "dom: [ ";
      getDomain(i)->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
      std::cerr << "ran: [ ";
      getRange(i)->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the (abstract) Reference class

inline void Reference::freeze(void)
{
  tag = (tag & ~FlagTemperature) | Frozen;
}

inline bool Reference::isFrozen(void)
{
  return (tag & FlagTemperature) == Frozen;
}

inline void Reference::thaw(void)
{
  tag = (tag & ~FlagTemperature) | Thawed;
}

inline bool Reference::isThawed(void)
{
  return (tag & FlagTemperature) == Thawed;
}

inline bool Reference::isOccursChecked(void) const
{
  return (tag & FlagOccurs) == HasOccursCheck;
}

inline void Reference::setOccursCheck(void)
{
  tag = tag | FlagOccurs;
}

inline bool Reference::isCollected(void) const
{
  return (tag & FlagCollected) == FlagCollected;
}

inline void Reference::setCollectedFlag(void)
{
  tag = tag | FlagCollected;
}

inline void Reference::unsetCollectedFlag(void)
{
  tag = tag & ~FlagCollected;
}

inline bool Reference::isPerm(void) const
{
  return (tag & FlagPerm) == FlagPerm;
}
   
inline void Reference::setPermFlag(void)
{
  tag = tag | FlagPerm;
}               

inline Object *Reference::getReference(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  return info[0];
}

inline void Reference::setReference(Object *plobj)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  info[0] = plobj;
}


inline bool Reference::hasExtraInfo(void) const
{
  return tag & FlagExtraInfo;
}

inline void Reference::setExtraInfo(void)
{
  tag |= FlagExtraInfo;
}

inline Atom *
Reference::getName(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  if(hasExtraInfo())
    {
      return OBJECT_CAST(Atom *, info[1]);
    }
  else
    {
      return NULL;
    }
}

inline heapobject*
Reference::getNameAddress(void)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  // Only a valid operation if Reference has extra information
  assert(hasExtraInfo());
  
  return reinterpret_cast<heapobject*>(&info[1]);
}

inline void
Reference::setName(Object* name)
{
  assert(name->isAtom());
  assert(hasExtraInfo());
  info[1] = name;
}

inline Object *Reference::getDelays(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  if (hasExtraInfo())
    {
      return info[2];
    }
  else
    {
      return AtomTable::nil;
    }
}

inline void
Reference::setDelays(Object *delays)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());
  assert(delays->isList() || delays->isVariable());

  info[2] = delays;
}

inline heapobject*
Reference::getDelaysAddress(void)
{
  assert(hasExtraInfo());
  return (reinterpret_cast<heapobject*>(&info[2]));
}

//////////////////////////////////////////////////////////////////////
// Inline functions for the Variable class

inline size_t Variable::size(void) const
{
  return size(hasExtraInfo());
}

inline size_t Variable::size(bool has_extra_info)
{
  return sizeof(Variable) / BYTES_PER_WORD + (has_extra_info ? 2 : 0);
}

inline bool Variable::isLifeSet(void) const
{
  return ((tag & 0xffff0000) != 0);
}
   
inline u_int Variable::getLife(void) const
{
  return (tag >> 16);
}
      
inline void Variable::setLife(u_int i)
{
  tag |= i << 16;
}                 

inline void Variable::copyTag(Object* other)
{
  assert(hasExtraInfo());
  assert(other->isVariable());
  assert(!OBJECT_CAST(Variable*, other)->hasExtraInfo());
  tag = other->getTag() | FlagExtraInfo;
}
  
#ifdef QP_DEBUG
inline void Variable::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] Variable:[" 
       << (word32)(tag & GC_Mask) << "] ";
  if (isFrozen()) { std::cerr << "(frozen) "; }
  if (isOccursChecked()) { std::cerr << "(occurs checked) "; }
  if (getReference() != (Object *) this)
    {
	    std::cerr << "<" <<std::hex << (word32)(getReference()) << std::dec << ">ref: [ ";
      getReference()->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
  else
    {
	    std::cerr << "(unbound)";
      if (hasExtraInfo())
	{
		std::cerr << "Name {";
	  getName()->printMe_dispatch(atoms, all);
	  if (all)
	    {
		    std::cerr << "} Delays {";
	      getDelays()->printMe_dispatch(atoms, false);
	    }
	  std::cerr << "}";
	}
    }
}
#endif

//////////////////////////////////////////////////////////////////////
// Inline functions for the ObjectVariable class

inline Object *ObjectVariable::getDistinctness(void) const
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());

  return info[3];
}

inline heapobject*
ObjectVariable::getDistinctnessAddress(void)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());

  return reinterpret_cast<heapobject*>(&info[3]);
}

inline void ObjectVariable::setDistinctness(Object *distinctness)
{
  assert(sizeof(Object *) == sizeof(heapobject));

  assert(hasExtraInfo());
  assert(distinctness->isList() || distinctness->isVariable());

  info[3] = distinctness;
}

inline size_t ObjectVariable::size(void) const
{
  return size(hasExtraInfo());
}

inline size_t ObjectVariable::size(bool has_extra_info)
{
  return sizeof(ObjectVariable) / BYTES_PER_WORD + (has_extra_info ? 3 : 0);
}

inline void ObjectVariable::makeLocalObjectVariable(void)
{
  tag |= ObjectVariable::FlagLocal;
}

/////////////////////////////////////////////////////////
// Other methods

inline int Object::getNumber(void)
{
  assert(isShort() || isLong());

  if (isShort())
    {
      return OBJECT_CAST(Short *, this)->getValue();
    }
  else
    {
      return OBJECT_CAST(Long *, this)->getValue();
    }
}

inline double Object::getDouble(void)
{ 
  assert(isDouble());
  return OBJECT_CAST(Double *, this)->getValue();
}

#ifdef QP_DEBUG
inline void ObjectVariable::printMe(AtomTable& atoms, bool all)
{
	std::cerr << "[" << std::hex << (word32) this << std::dec << "] ObjVar:[" 
       << (word32)(tag & GC_Mask) << "] ";
  if (isFrozen()) { std::cerr << "(frozen) "; }
  if (getReference() != OBJECT_CAST(const Object*, this))
    {
	    std::cerr << "ref: [ ";
      getReference()->printMe_dispatch(atoms, all);
      std::cerr << " ] ";
    }
  else
    {
	    std::cerr << "(unbound)";
      if (hasExtraInfo())
	{
		std::cerr << "Name {";
	  getName()->printMe_dispatch(atoms, all);
	  std::cerr << "} Delays {";
	  if (all)
	    {
	      getDelays()->printMe_dispatch(atoms, false);
	      std::cerr << "} Distinctness {";
	      getDistinctness()->printMe_dispatch(atoms, false);
	    }
	  std::cerr << "}";
	}
    }
}
#endif // QP_DEBUG

//
// variableDereference() follows the (ob)variable-reference chain from
// an object -- iteratively, not recursively -- and returns the object
// at the end of the (ob)variable chain.
//
inline Object*
Object::variableDereference()
{
  Object* o = this;
  //
  // Ensure we're not about to dereference a NULL pointer
  //
  assert(o != NULL);
  
  while (o->isAnyVariable()) 
    {
      //
      // While still an (ob)variable, hence referring to something else,
      // move to what it's referring to
      //
      Object* n = OBJECT_CAST(Reference*, o)->getReference();
      assert(n != NULL);
      if ( n == o ) 
          {
	    break; // An unbound (ob)variable
	  }
      o = n;
    }
  return o;
}


inline bool Object::inList(Object* o) 
{
  for (Object* l = this;
       l->isCons();
       l = OBJECT_CAST(Cons*, l)->getTail()->variableDereference())
    {
      if (o == OBJECT_CAST(Cons*, l)->getHead()->variableDereference())
        {
          return true;
        }
    }
  return false;
}      


//
// Equal constant.
//
inline bool Object::equalConstants(Object* const2)
{
  assert(this->isConstant());
  assert(const2->isConstant());

  return(this == const2 ||
	 (this->isInteger() && const2->isInteger() &&
	  this->getNumber() == const2->getNumber())
	 || (this->isDouble() && const2->isDouble() &&
	  this->getDouble() == const2->getDouble())
        );
}


//#endif // HEAP_H

#endif // OBJECTS_H_INLINE


