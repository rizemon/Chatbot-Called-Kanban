#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define MAX_SIZE 256

typedef struct NodeStruct {
    char key[MAX_SIZE];
    char original[MAX_SIZE];
    char content[MAX_SIZE];
    struct NodeStruct * next;
}Node;

Node * createNode(char * key, char * content);
Node * addNode(Node * headptr, Node * newNode);
Node * findNode(Node * headptr, char * key);
Node * deleteNode(Node * headptr, char * key);

Node * clearAll(Node * headptr);
void printAll(Node * headptr);

Node * modifyNode(Node * node, char * content);
void freeNode(Node * node);
void printNode(Node * node);

void getNodeKey(Node * node, char * key);
void getNodeContent(Node * node, char * content);

Node * innerDeleteNode(Node * headptr, char * key);
Node * innerFindNode(Node * headptr, char * key);

#endif
