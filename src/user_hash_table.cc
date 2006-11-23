#include "user_hash_table.h"
#include <assert.h>

UserHashTable::UserHashTable(const int size) :
  DynamicHashTable<UserHashEntry> (size)
{ }

UserHashTable::~UserHashTable(void) {}

void UserHashState::addEntry(Object* h1, Object* h2, Object* term, Heap& heap)
{
  int index;
  word32 sh2;
  bool isint;
  if (h2->isInteger())
    {
      sh2 = (word32)(h2->getInteger());
      isint = true;
    }
  else
    {
      sh2 = (word32)h2;
      isint = false;
    }
  // Garbage Collect?
  if (userhashheap->doGarbageCollection())
    garbageCollect();
  
  UserHashEntry* new_entry = new UserHashEntry((word32)h1, sh2, isint);
  heapobject* old_top = userhashheap->getTop();
  Object* copy = heap.copyTerm(term, *userhashheap);
  int size = userhashheap->getTop() - old_top;
  index = hash_table.search(*new_entry);
  if (index == -1)
    {
      new_entry->setValue(copy);
      new_entry->setSize(size);
      if (userhashheap->isHeapPtr((heapobject*)copy))
	new_entry->setPtr((heapobject*)copy);
      hash_table.insert(*new_entry, index);
    }
  else
    {
      int old_size = hash_table.getEntry(index).getSize();
      if ((old_size >= size) && (size != 0))
        {
	  userhashheap->setTop(hash_table.getEntry(index).getPtr());
	  Object* replace = userhashheap->copyTerm(copy, *userhashheap);
	  userhashheap->setTop(old_top);
	  hash_table.getEntry(index).setValue(replace);
	  //hash_table.getEntry(index).setSize(size);
        }
      else
        {
          total_garbage += old_size;
          if (size != 0) hash_table.getEntry(index).setSize(size);
          hash_table.getEntry(index).setValue(copy);
          if (userhashheap->isHeapPtr((heapobject*)copy))
	    hash_table.getEntry(index).setPtr((heapobject*)copy);
        }
    }
}

bool UserHashState::lookupEntry(Object* h1, Object* h2, Object*& ret, Heap& heap)
{
  word32 sh2;
  bool isint;
  if (h2->isInteger())
    {
      sh2 = (word32)(h2->getInteger());
      isint = true;
    }
  else
    {
      sh2 = (word32)h2;
      isint = false;
    }
  UserHashEntry entry((word32)h1, sh2, isint);
  const int index = hash_table.search(entry);
  if (index == -1) return false;
  Object* val = hash_table.getEntry(index).getValue();
  ret = userhashheap->copyTerm(val, heap);
  return true;
}

bool UserHashState::removeEntry(Object* h1, Object* h2)
{
  word32 sh2;
  bool isint;
  if (h2->isInteger())
    {
      sh2 = (word32)(h2->getInteger());
      isint = true;
    }
  else
    {
      sh2 = (word32)h2;
      isint = false;
    }
  UserHashEntry entry((word32)h1, sh2, isint);
  const int index = hash_table.search(entry);
  if (index == -1) return false;
  hash_table.remove(index);
  return true;
}

void UserHashState::hashIterReset(void)
{
  hash_table.iter_reset();
}

bool UserHashState::hashIterNext(Object*& a, Object*& b, Object*& c, 
				 Heap& heap)
{
  int index  = hash_table.iter_next();
  if (index == -1) return false;
  UserHashEntry entry = hash_table.getEntry(index);
  a = (Object*)(entry.getFstEntry());
  if (entry.getIsInt())
    {
      b = heap.newInteger((int)(entry.getSndEntry()));
    }
  else
    {
      b = (Object*)(entry.getSndEntry());
    }
  c = userhashheap->copyTerm(entry.getValue(), heap);
  return true;
}

void UserHashState::garbageCollect(void)
{
  Heap* newheap;
  if (total_garbage * 2 > heap_size)
    {
      newheap = new Heap("User Hash Table Heap", heap_sizeK, true);
    }
  else
    {
      heap_sizeK *= 2;
      heap_size *= 2;
      newheap = new Heap("User Hash Table Heap", heap_sizeK, true);
    }
  total_garbage = 0;
  hash_table.iter_reset();
  for (int index = hash_table.iter_next(); index != -1;
       index = hash_table.iter_next())
    {
      heapobject* old_top = newheap->getTop();
      Object* copy = userhashheap->copyTerm(hash_table.getEntry(index).getValue(), *newheap);
      int size = newheap->getTop() - old_top;
      hash_table.getEntry(index).setValue(copy);
      hash_table.getEntry(index).setSize(size);
      if (newheap->isHeapPtr((heapobject*)copy))
	hash_table.getEntry(index).setPtr((heapobject*)copy);
      else
	hash_table.getEntry(index).setPtr(NULL);
    }
  delete userhashheap;
  userhashheap = newheap;
}
