#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

Node * createNode(char * key, char * content){
    //Allocate space for a single node
    Node * newNode = (Node *)malloc(sizeof(Node));
    //Save key and content into node
    strncpy(newNode->key, key, MAX_SIZE);
    for(int i = 0; i < strlen(newNode->key); i++) newNode->key[i] = tolower(newNode->key[i]);
    strncpy(newNode->original, key, MAX_SIZE);
    strncpy(newNode->content, content, MAX_SIZE);
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

Node * modifyNode(Node * node, char * original, char * content){
    if(node == NULL) return NULL;
    //Overwrite content in node
    if(node) {
        strncpy(node-> content, content, MAX_SIZE);
        strncpy(node-> original, original, MAX_SIZE);
    }
    return node;
}

Node * findNode(Node * headptr, char * key){
    
    // Store lowercase version of key
    char * tempKey = (char *)malloc(sizeof(char) * MAX_SIZE);
    for(int i = 0; i < strlen(key); i++) tempKey[i] = tolower(key[i]);

    Node * found = innerFindNode(headptr, tempKey);
    free(tempKey);

    // Return found node
    return found;

}

Node * innerFindNode(Node * headptr, char * key){
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

Node * deleteNode(Node * headptr, char * key){

    // Store lowercase version of key
    char * tempKey = (char *)malloc(sizeof(char) * MAX_SIZE);
    for(int i = 0; i < strlen(key); i++) tempKey[i] = tolower(key[i]);
    
    headptr = innerDeleteNode(headptr, tempKey);
    free(tempKey);
    //Return updated head pointer
    return headptr;
}

Node * innerDeleteNode(Node * headptr, char * key){
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

void getNodeKey(Node * node, char * key){
    if(node) strncpy(key, node->original, MAX_SIZE);
}

void getNodeContent(Node * node, char * content){
    if(node) strncpy(content, node->content, MAX_SIZE);
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


