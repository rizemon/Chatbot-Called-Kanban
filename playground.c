#include "linkedlist.h"
#include "hashtable.h"
#include "knowledgebase.h"
 
int main(){ 
    Node ** newHashTable = NULL; 
 
    newHashTable = createHashTable(); 
 
    Node * newNode = createNode("fuck", "you"); 
 
    newHashTable = insertHashTable(newHashTable, newNode); 
 
    newHashTable = insertHashTable(newHashTable, createNode("fuck", "someone")); 
 
    Node * found = findHashTable(newHashTable, "fuck"); 
    if(found == NULL){ 
        //cannot find 
    }else{ 
        //can find 
        printNode(found); 
    } 
 
    newHashTable = deleteHashTable(newHashTable, "fuck"); 
    newHashTable = clearHashTable(newHashTable); 
 
    KnowledgeBase * kb = NULL; 
    kb = createKnowledgeBase(); 
    kb = insertKnowledgeBase(kb , "what", createNode("SIT","fucked up")); 
    kb = insertKnowledgeBase(kb , "where", createNode("SIT","fucked up")); 
    kb = insertKnowledgeBase(kb , "who", createNode("SIT","fucked up")); 
     
    found = searchKnowledgeBase(kb, "who", "SIT"); 
    if(found == NULL){ 
        //cannot find 
    }else{ 
        printNode(found); 
    } 
    kb = clearKnowledgeBase(kb); 
     
 
 
 
     
     
    return 0; 
}