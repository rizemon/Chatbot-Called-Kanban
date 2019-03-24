#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

//Hash table implementation in C using Seperate Chaining for hash collisions

unsigned long hash_fn(char * str){
    //Hash function using djb2 algorithm
    unsigned long magic_number = 5381;
    int i;
    for(i = 0; i < strlen(str); i++){
        int c = tolower(str[i]);
        magic_number = (magic_number<<5) + magic_number + c;
    }
    
    return magic_number;
}

Node ** createHashTable(){
    //Allocate array of linked lists
    return (Node **)malloc(BUCKET_SIZE * sizeof(Node *));
}

Node * findHashTable(Node ** hashTable, char * key){
    if(hashTable == NULL) return NULL;
    //Calculate hash
    unsigned long hash = hash_fn(key) % BUCKET_SIZE;
    //Retrieve node from linked list
    return findNode(hashTable[hash], key);
}

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

Node ** deleteHashTable(Node ** hashTable, char * key){
    if(hashTable == NULL) return NULL;
    //Calculate hash
    unsigned long hash = hash_fn(key) % BUCKET_SIZE;
    //Delete node from linked list
    hashTable[hash] = deleteNode(hashTable[hash], key);
    return hashTable;
}

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