#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

typedef struct KnowledgeBaseStruct {
    Node ** whereDict;
    Node ** whatDict;
    Node ** whoDict;
}KnowledgeBase;

KnowledgeBase * createKnowledgeBase();
Node * searchKnowledgeBase(KnowledgeBase * kb, char * intent, char * entity);
KnowledgeBase * insertKnowledgeBase(KnowledgeBase * kb, char * intent, Node * node);
KnowledgeBase * clearKnowledgeBase(KnowledgeBase * kb);

#endif