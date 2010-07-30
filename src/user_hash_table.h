// user_hash_table.h - support for Prolog-level hash table.
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
    word32 fst_entry;
    word32 snd_entry;
    int size;
    Object* value;
    heapobject* ptr;
    bool removed;
    bool isInt;
public:
    void clearEntry(void) { fst_entry = 0; }
    bool isEmpty(void) const {  return (fst_entry == 0); }
    bool isRemoved(void) { return removed; }
    void makeRemoved(void) { removed = true; }
    int hashFn(void) const { return (fst_entry*31 + snd_entry); }
    bool operator==(const UserHashEntry entry) const
      { return ((fst_entry == entry.fst_entry) &&
                (snd_entry == entry.snd_entry) &&
                (isInt == entry.isInt)); }
    void operator=(const UserHashEntry entry)
      { fst_entry = entry.fst_entry; snd_entry = entry.snd_entry;
        isInt = entry.isInt; value = entry.value;
        ptr = entry.ptr; size = entry.size; removed = entry.removed; }

    void setSize(int s) { size = s; }
    int getSize(void) {return size; }

    void setPtr(heapobject* o) { ptr = o; }
    heapobject*  getPtr() { return ptr; }

    void setValue(Object* o) { value = o; }
    Object* getValue(void) {return value; }

    word32 getFstEntry(void) {return fst_entry; }
    word32 getSndEntry(void) {return snd_entry; }
    bool   getIsInt(void) { return isInt; }

    UserHashEntry(word32 t = 0, word32 s = 0, bool i = true)
    : fst_entry(t), snd_entry(s), size(0),
      value(NULL),  ptr(NULL), removed(false), isInt(i)
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
