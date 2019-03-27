#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

Node * createNode(const char * key, const char * content){
    //Allocate space for a single node
    Node * newNode = (Node *)malloc(sizeof(Node));
    //Save key and content into node
    snprintf(newNode->original, MAX_ENTITY, "%s", key);
    snprintf(newNode->content, MAX_RESPONSE, "%s", content);
    for(int i = 0; i < strlen(newNode->original); i++) newNode->key[i] = tolower(newNode->original[i]);
    newNode->key[strlen(newNode->original)] = '\0';
    //Set pointer to next node to NULL
    newNode->next = NULL;
    return newNode;
}

Node * addNode(Node * headptr, Node * newNode){
    //If linked list is empty, return the new node
    if(headptr == NULL) return newNode;
    if(newNode == NULL) return headptr;
    //Set new node to point to the current head node
    newNode->next = headptr;
    
    //Set new node to be the new head node
    return newNode;
}

Node * modifyNode(Node * node, const char * original, const char * content){
    if(node == NULL) return NULL;
    //Overwrite content in node
    if(node) {
        snprintf(node-> content, MAX_RESPONSE, "%s", content);
        snprintf(node-> original, MAX_ENTITY, "%s", original);
    }
    return node;
}

Node * findNode(Node * headptr, const char * key){
    
    // Store lowercase version of key
    char * tempKey = (char *)malloc(sizeof(char) * MAX_ENTITY);
    for(int i = 0; i < strlen(key); i++) tempKey[i] = tolower(key[i]);
    tempKey[strlen(key)] = '\0';

    Node * found = innerFindNode(headptr, tempKey);
    free(tempKey);

    // Return found node
    return found;

}

Node * innerFindNode(Node * headptr, const char * key){
    //Node cannot be found
    if(headptr == NULL) return NULL;
    //If node's key matches
    if(strcmp(headptr->key, key) == 0) return headptr;
    //If no match, continue recursing
    else return findNode(headptr->next, key);
}

void freeNode(Node * node){
    //Free the node
    free(node);
}

Node * deleteNode(Node * headptr, const char * key){

    // Store lowercase version of key
    char * tempKey = (char *)malloc(sizeof(char) * MAX_ENTITY);
    for(int i = 0; i < strlen(key); i++) tempKey[i] = tolower(key[i]);
    tempKey[strlen(key)] = '\0';
    
    headptr = innerDeleteNode(headptr, tempKey);
    free(tempKey);
    //Return updated head pointer
    return headptr;
}

Node * innerDeleteNode(Node * headptr, const char * key){
    if(headptr == NULL) return NULL;

    //If head node is to be deleted
    if(strcmp(headptr->key,key) == 0){
        //Node to be free-ed
        Node * temp = headptr;
        //Point head pointer to next node
        headptr = headptr->next;
        freeNode(temp);
        //Return updated head pointer
        return headptr; 
    }
    
    //If next node is to be deleted
    if(strcmp(headptr->next->key, key) == 0){
        //Node to be free-ed
        Node * temp = headptr->next;
        //Point current node's next pointer to the next next node
        headptr->next = temp->next;
        freeNode(temp);
        //Return current node
        return headptr;
    }
    //Recursively point current node's next pointer to the next node
    headptr->next = innerDeleteNode(headptr->next,key);
    //Return updated head pointer
    return headptr;
}

Node * clearAll(Node * headptr){
    //No more nodes to free
    if(headptr==NULL) return NULL;
    //Free from the back 
    clearAll(headptr->next);
    freeNode(headptr);
    return NULL;
}

char * getNodeKey(Node * node){
    return node->original;
}

char * getNodeContent(Node * node){
    return node->content;
}

void printNode(Node * node){
    //If node is empty
    if(node == NULL) printf("\n");
    //Print the node
    else printf("%s: %s: %s\n", node->key, node->original, node->content);
}

void printAll(Node * headptr){
    //No more nodes to print
    if(headptr == NULL) return;
    //Print node
    printNode(headptr);
    //Recursively print next node
    printAll(headptr->next);
}


