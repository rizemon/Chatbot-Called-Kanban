#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "knowledgebase.h"

KnowledgeBase * createKnowledgeBase(){
    //Allocate space for knowledge base
    KnowledgeBase * kb = (KnowledgeBase *)malloc(sizeof(KnowledgeBase));
    if(kb == NULL) return NULL;
    //Initialise each dictionary
    kb->whereDict = createHashTable();
    kb->whatDict = createHashTable();
    kb->whoDict = createHashTable();
    return kb;
}

Node * searchKnowledgeBase(KnowledgeBase * kb, const char * intent, const char * entity){
    Node * found = NULL;
    //Search for node corresponding to entity
    if(strcmp("where",intent) == 0) found = findHashTable(kb->whereDict, entity);
    if(strcmp("what",intent) == 0) found = findHashTable(kb->whatDict, entity);
    if(strcmp("who",intent) == 0) found = findHashTable(kb->whoDict, entity);
    
    return found;
}

KnowledgeBase * insertKnowledgeBase(KnowledgeBase * kb, const char * intent, Node * node){
    if(node==NULL) return kb;
    if(kb == NULL) return NULL;

    //Insert entity and response to corresponding dictioanry
    if(strcmp("where",intent) == 0) kb->whereDict = insertHashTable(kb->whereDict, node);
    if(strcmp("what",intent) == 0) kb->whatDict = insertHashTable(kb->whatDict, node);
    if(strcmp("who",intent) == 0) kb->whoDict = insertHashTable(kb->whoDict, node);
    return kb;
}

KnowledgeBase * clearKnowledgeBase(KnowledgeBase * kb){
    if(kb == NULL) return NULL;
    //Free each dictionary
    kb->whereDict = clearHashTable(kb->whereDict);
    kb->whatDict = clearHashTable(kb->whatDict);
    kb->whoDict = clearHashTable(kb->whoDict);
    return kb;
}