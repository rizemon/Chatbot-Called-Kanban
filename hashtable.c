/*
 * Hash table implementation using Seperate Chaining for hash collisions
 */


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


/*
 * Compute a large hash value from a given string
 *
 * Input:
 *   str      - the given string
 *
 * Returns: a large number used for computing the slot
 */
unsigned long hash_fn(const char * str){
    //Hash function using djb2 algorithm
    unsigned long magic_number = 5381;
    int i;
    for(i = 0; i < strlen(str); i++){
        int c = tolower(str[i]);
        magic_number = (magic_number<<5) + magic_number + c;
    }
    
    return magic_number;
}


/*
 * Create and initialize a hash table
 *
 * Returns: the pointer to the newly hashTable of size BUCKET_SIZE
 */
Node ** createHashTable(){
    //Allocate array of linked lists
    Node ** newTable = (Node **)malloc(BUCKET_SIZE * sizeof(Node *));
    //Initialize head pointer of each linked list to NULL
    for(int i = 0; i < BUCKET_SIZE; i++){
        newTable[i] = NULL;
    }
    return newTable;
}


/*
 * Search for a Node in a hash table using a key
 *
 * Input:
 *   hashTable- the pointer to the hash table
 *   key      - the entity
 *
 * Returns: the pointer to the found Node. If not found, return NULL
 */
Node * findHashTable(Node ** hashTable, const char * key){
    if(hashTable == NULL) return NULL;
    //Calculate hash
    unsigned long hash = hash_fn(key) % BUCKET_SIZE;
    //Retrieve node from linked list
    return findNode(hashTable[hash], key);
}


/*
 * Insert a new node into a hash table. If a node with the same key already
 * exists, the contents of that node is overwritten with the contents of 
 * the new node
 *
 * Input:
 *   hashTable- the pointer to the hash table
 *   node     - the pointer to the Node that is going to be added
 *
 * Returns: the pointer to the updated hash table
 */
Node ** insertHashTable(Node ** hashTable, Node * node){
    if(hashTable == NULL) return NULL;
    if(node == NULL) return hashTable;
    //Calculate hash
    unsigned long hash = hash_fn(node->key) % BUCKET_SIZE;
    //Retrieve node from linked list
    Node * found = findNode(hashTable[hash], node->original);

    //If exist, update content of node
    if(found){
        found = modifyNode(found, node->original, node->content);
        //Free the node
        freeNode(node);
    }
    //If not, add node to linked list
    else hashTable[hash] = addNode(hashTable[hash], node);
    
    return hashTable;
}


/*
 * Delete a Node in the hash table that has the given key
 *
 * Input:
 *   hashTable- the pointer to the hash table
 *   key      - the entity
 *
 * Returns: the pointer to the updated hash table
 */
Node ** deleteHashTable(Node ** hashTable, const char * key){
    if(hashTable == NULL) return NULL;
    //Calculate hash
    unsigned long hash = hash_fn(key) % BUCKET_SIZE;
    //Delete node from linked list
    hashTable[hash] = deleteNode(hashTable[hash], key);
    return hashTable;
}


/*
 * Free a hash table
 * 
 * Input:
 *   hashTable- the pointer to the hash table
 *
 * Returns: NULL
 */
Node ** clearHashTable(Node ** hashTable){
    if(hashTable == NULL) return NULL;
    //Loop through each slot
    int i;
    for(i=0; i < BUCKET_SIZE; i++){
        //Clear linked list
        hashTable[i] = clearAll(hashTable[i]);
    }
    free(hashTable);
    return NULL;
}