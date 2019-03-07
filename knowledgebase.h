#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

typedef struct KnowledgeBaseStruct {
    Node ** whereDict;
    Node ** whatDict;
    Node ** whoDict;
}KnowledgeBase;

#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

KnowledgeBase * createKnowledgeBase();
Node * searchKnowledgeBase(KnowledgeBase * kb, char * intent, char * entity);
KnowledgeBase * insertKnowledgeBase(KnowledgeBase * kb, char * intent, char * entity, char * response);
KnowledgeBase * clearKnowledgeBase(KnowledgeBase * kb);

#endif