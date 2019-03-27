

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "chat1002.h"

typedef struct NodeStruct {
    char key[MAX_ENTITY];
    char original[MAX_ENTITY];
    char content[MAX_RESPONSE];
    struct NodeStruct * next;
}Node;

Node * createNode(const char * key, const char * content);
Node * addNode(Node * headptr, Node * newNode);
Node * findNode(Node * headptr, const char * key);
Node * deleteNode(Node * headptr, const char * key);

Node * clearAll(Node * headptr);
void printAll(Node * headptr);

Node * modifyNode(Node * node, const char * original, const char * content);
void freeNode(Node * node);
void printNode(Node * node);

char * getNodeKey(Node * node);
char * getNodeContent(Node * node);

Node * innerDeleteNode(Node * headptr, const char * key);
Node * innerFindNode(Node * headptr, const char * key);

#endif
