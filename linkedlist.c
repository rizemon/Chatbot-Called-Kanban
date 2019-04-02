#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


/*
 * Create and initialize a Node
 *
 * Input:
 *   key      - the entity
 *   content  - the response
 *
 * Returns: the pointer to the newly allocated Node. If not allocated, return NULL
 */
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


/*
 * Append a Node to the head of a linked list
 *
 * Input:
 *   headptr  - the head pointer of a linked list
 *   newNode  - the pointer to the Node that is going to be added
 *
 * Returns: the updated head pointer of the linked list
 */
Node * addNode(Node * headptr, Node * newNode){
    //If linked list is empty, return the new node
    if(headptr == NULL) return newNode;
    if(newNode == NULL) return headptr;
    //Set new node to point to the current head node
    newNode->next = headptr;
    
    //Set new node to be the new head node
    return newNode;
}


/*
 * Modify a Node
 *
 * Input:
 *   node     - the pointer to the node that is going to be modified
 *   original - the entity
 *   content  - the response
 *
 * Returns: the updated head pointer of the linked list
 */
Node * modifyNode(Node * node, const char * original, const char * content){
    if(node == NULL) return NULL;
    //Overwrite content in node
    if(node) {
        snprintf(node-> content, MAX_RESPONSE, "%s", content);
        snprintf(node-> original, MAX_ENTITY, "%s", original);
    }
    return node;
}


/*
 * Search for a Node in a linked list using a key
 *
 * Input:
 *   headptr  - the head pointer of a linked list
 *   key      - the entity
 *
 * Returns: the pointer to the found Node. If not found, return NULL
 */
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


/*
 * Inner function called by findNode
 *
 * Input:
 *   headptr  - the head pointer of a linked list
 *   key      - the entity
 *
 * Returns: the pointer to the found Node. If not found, return NULL
 */
Node * innerFindNode(Node * headptr, const char * key){
    //Node cannot be found
    if(headptr == NULL) return NULL;
    //If node's key matches
    if(strcmp(headptr->key, key) == 0) return headptr;
    //If no match, continue recursing
    else return findNode(headptr->next, key);
}


/*
 * Free a Node
 *
 * Input:
 *   node     - the pointer to the node that is going to be freed
 */
void freeNode(Node * node){
    //Free the node
    free(node);
}


/*
 * Delete a Node in a linked list using a key
 *
 * Input:
 *   headptr  - the head pointer of a linked list
 *   key      - the entity
 *
 * Returns: the pointer to the found Node. If not found, return NULL
 */
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


/*
 * Inner function called by deleteNode
 *
 * Input:
 *   headptr  - the head pointer of a linked list
 *   key      - the entity
 *
 * Returns: the updated head pointer of the linked list
 */
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


/*
 * Free all nodes in a linked list
 *
 * Input:
 *   headptr  - the head pointer of a linked list
 *
 * Returns: the updated head pointer of the linked list
 */
Node * clearAll(Node * headptr){
    //No more nodes to free
    if(headptr==NULL) return NULL;
    //Free from the back 
    clearAll(headptr->next);
    freeNode(headptr);
    return NULL;
}


/*
 * Get the entity of a Node
 *
 * Input:
 *   node     - the pointer to the Node to retrieve the entity from
 *
 * Returns: the entity
 */
char * getNodeKey(Node * node){
    return node->original;
}


/*
 * Get the response of a Node
 *
 * Input:
 *   node     - the pointer to the Node to retrieve the response from
 *
 * Returns: the response
 */
char * getNodeContent(Node * node){
    return node->content;
}


/*
 * Print the contents of a Node
 *
 * Input:
 *   node     - the pointer to the Node to print the contents from
 */
void printNode(Node * node){
    //If node is empty
    if(node == NULL) printf("\n");
    //Print the node
    else printf("%s: %s: %s\n", node->key, node->original, node->content);
}


/*
 * Print the contents of all Nodes in a linked list
 *
 * Input:
 *   headptr  - the head pointer of a linked list
 */
void printAll(Node * headptr){
    //No more nodes to print
    if(headptr == NULL) return;
    //Print node
    printNode(headptr);
    //Recursively print next node
    printAll(headptr->next);
}


