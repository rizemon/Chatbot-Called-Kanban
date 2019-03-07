#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "linkedlist.h"
#define BUCKET_SIZE 1001
unsigned long hash_fn(char * str);

Node ** createHashTable();
Node * findHashTable(Node ** hashTable, char * key);
Node ** insertHashTable(Node ** hashTable, char * key, char * content);
Node ** deleteHashTable(Node ** hashTable, char * key);
Node ** clearHashTable(Node ** hashTable);

#endif