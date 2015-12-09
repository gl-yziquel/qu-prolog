// user_hash_table.h - support for Prolog-level hash table.
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: user_hash_table.h,v 1.2 2006/03/30 22:50:31 qp Exp $

#include "heap_qp.h"
#include "dynamic_hash_table.h"


//
// Entries in user-level hash table
// Two-level indexing using fst_entry and snd_entry
//
class UserHashEntry
{
private:
    Object* fst_entry;
    Object* snd_entry;
    int size;
    Object* value;
    heapobject* ptr;
    bool removed;
public:
    void clearEntry(void) { fst_entry = 0; }
    bool isEmpty(void) const {  return (fst_entry == 0); }
    bool isRemoved(void) { return removed; }
    void makeRemoved(void) { removed = true; }
    int hashFn(void) const 
    {
      wordlong fst_hash;
      switch (fst_entry->tTag())
        {
        case Object::tShort:
          fst_hash = (wordlong)(OBJECT_CAST(Short *, fst_entry)->getValue());
          break;
        case Object::tLong:
          fst_hash = (wordlong)(OBJECT_CAST(Long *, fst_entry)->getValue());
          break;
        case Object::tAtom:
          fst_hash = (wordlong)(OBJECT_CAST(Long *, fst_entry)->getValue());
          break;
        case Object::tDouble:
          fst_hash = (wordlong)(OBJECT_CAST(Double *, fst_entry)->hashFn());
          break;
        case Object::tString:
          fst_hash = (wordlong)(OBJECT_CAST(StringObject *, fst_entry)->hashFn());
          break;
        default:
          // Not all Tags considered!
          std::cerr << "Bogus type" << std::endl;
          std::cerr << (wordptr)(this) << " -> " << *((heapobject*)(this)) << std::endl;
          assert(false);
        }
      wordlong snd_hash;
      switch (snd_entry->tTag())
        {
        case Object::tShort:
          snd_hash = (wordlong)(OBJECT_CAST(Short *, snd_entry)->getValue());
          break;
        case Object::tLong:
          snd_hash = (wordlong)(OBJECT_CAST(Long *, snd_entry)->getValue());
          break;
        case Object::tAtom:
          snd_hash = (wordlong)(OBJECT_CAST(Long *, snd_entry)->getValue());
          break;
        case Object::tDouble:
          snd_hash = (wordlong)(OBJECT_CAST(Double *, snd_entry)->hashFn());
          break;
        case Object::tString:
          snd_hash = (wordlong)(OBJECT_CAST(StringObject *, snd_entry)->hashFn());
          break;
        default:
          // Not all Tags considered!
          std::cerr << "Bogus type" << std::endl;
          std::cerr << (wordptr)(this) << " -> " << *((heapobject*)(this)) << std::endl;
          assert(false);
        }
      return (int)(fst_hash ^ snd_hash);
    }

    bool operator==(const UserHashEntry entry) const
      { return ((fst_entry == entry.fst_entry) &&
                (snd_entry == entry.snd_entry) ); }
    void operator=(const UserHashEntry entry)
      { fst_entry = entry.fst_entry; snd_entry = entry.snd_entry;
        value = entry.value;
        ptr = entry.ptr; size = entry.size; removed = entry.removed; }

    void setSize(int s) { size = s; }
    int getSize(void) {return size; }

    void setPtr(heapobject* o) { ptr = o; }
    heapobject*  getPtr() { return ptr; }

    void setValue(Object* o) { value = o; }
    Object* getValue(void) {return value; }

    Object* getFstEntry(void) {return fst_entry; }
    Object* getSndEntry(void) {return snd_entry; }

    UserHashEntry(Object* t = AtomTable::dollar, Object* s = AtomTable::dollar)
    : fst_entry(t), snd_entry(s), size(0),
      value(NULL),  ptr(NULL), removed(false)
  {};

};

//
// Instantiation of DynamicHashTable for user hash table
//
class UserHashTable : public DynamicHashTable<UserHashEntry>
{
public:
  UserHashTable(const int size);

  ~UserHashTable(void);

   int   hashFunction(const UserHashEntry entry) const
      { return (entry.hashFn()); }

};

//
// Hash Table including heap for storing data
//
class UserHashState
{
private:
   UserHashTable hash_table;
   Heap* userhashheap;
   int total_garbage, heap_size, heap_sizeK;


public:

  void addEntry(Object* h1, Object* h2, Object* term, Heap& heap);
  bool lookupEntry(Object* h1, Object* h2, Object*& ret, Heap& heap);
  bool removeEntry(Object* h1, Object* h2);
  void hashIterReset(void);
  bool hashIterNext(Object*& a, Object*& b, Object*& c, Heap& heap);
  void garbageCollect(void);

  UserHashState(int hts, int hs)
    : hash_table(hts)
  {
    userhashheap = new Heap("User Hash Table Heap", hs * K, true);
    total_garbage = 0;
    heap_size = hs * K / sizeof (heapobject);
    heap_sizeK = hs;
  }


};
