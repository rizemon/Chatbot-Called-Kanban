#include "linkedlist.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define BUCKET_SIZE 1001
unsigned long hash_fn(const char * str);

Node ** createHashTable();
Node * findHashTable(Node ** hashTable, const char * key);
Node ** insertHashTable(Node ** hashTable, Node * node);
Node ** deleteHashTable(Node ** hashTable, const char * key);
Node ** clearHashTable(Node ** hashTable);

#endif
