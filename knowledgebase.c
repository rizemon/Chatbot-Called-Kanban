#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "knowledgebase.h"


/*
 * Create and initialize a knowledge base
 *
 * Returns: the pointer to the newly allocated knowledge base
 */
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


/*
 * Search for a Node under the given intent in a knowledge base using an entity
 *
 * Input:
 *   kb       - the pointer to the knowledge base
 *   intent   - the intent (e.g "what", "where", "who")
 *   entity   - the entity
 *
 * Returns: the pointer to the found Node. If not found, return NULL
 */
Node * searchKnowledgeBase(KnowledgeBase * kb, const char * intent, const char * entity){
    Node * found = NULL;
    //Search for node corresponding to entity
    if(strcmp("where",intent) == 0) found = findHashTable(kb->whereDict, entity);
    if(strcmp("what",intent) == 0) found = findHashTable(kb->whatDict, entity);
    if(strcmp("who",intent) == 0) found = findHashTable(kb->whoDict, entity);
    
    return found;
}


/*
 * Insert a new node into a knowledge base under the given intent
 *
 * Input:
 *   kb       - the pointer to the knowledge base
 *   intent   - the intent (e.g "what", "where", "who")
 *   node     - the pointer to the Node that is going to be added
 *
 * Returns: the pointer to the found Node. If not found, return NULL
 */
KnowledgeBase * insertKnowledgeBase(KnowledgeBase * kb, const char * intent, Node * node){
    if(node==NULL) return kb;
    if(kb == NULL) return NULL;

    //Insert entity and response to corresponding dictioanry
    if(strcmp("where",intent) == 0) kb->whereDict = insertHashTable(kb->whereDict, node);
    if(strcmp("what",intent) == 0) kb->whatDict = insertHashTable(kb->whatDict, node);
    if(strcmp("who",intent) == 0) kb->whoDict = insertHashTable(kb->whoDict, node);
    return kb;
}


/*
 * Free a knowledge base
 *
 * Input:
 *   kb       - the pointer to the knowledge base
 *
 * Returns: NULL
 */
KnowledgeBase * clearKnowledgeBase(KnowledgeBase * kb){
    if(kb == NULL) return NULL;
    //Free each dictionary

    kb->whereDict = clearHashTable(kb->whereDict);
    kb->whatDict = clearHashTable(kb->whatDict);
    kb->whoDict = clearHashTable(kb->whoDict);

    free(kb);
    return NULL;
}