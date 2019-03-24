/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "knowledgebase.h"


/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {
	Node * found = NULL;
	if(compare_token(intent, "what") == 0) found = searchKnowledgeBase(kb, "what", entity);
	else if(compare_token(intent, "where") == 0) found = searchKnowledgeBase(kb, "where", entity);
	else if(compare_token(intent, "who") == 0) found = searchKnowledgeBase(kb, "who", entity);
	else return KB_INVALID;
	
	if(found == NULL){
		return KB_NOTFOUND;
	}else{
		getNodeContent(found, response);
        return KB_OK;
	}

}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_OK, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {
	if(compare_token(intent, "what")==0){
		Node * newNode = createNode(entity, response);
		if(newNode ==NULL){
			return KB_NOMEM;
		}
		else
		{
			kb = insertKnowledgeBase(kb , "what", createNode(entity,response));
			return KB_OK;
		}
		
	}
	else if (compare_token(intent, "where") ==0){
		Node * newNode = createNode(entity, response);
		if(newNode ==NULL){
			return KB_NOMEM;
		}
		else
		{
			kb = insertKnowledgeBase(kb , "where", createNode(entity,response));
			return KB_OK;
		}
	}
	else if (compare_token(intent, "who")== 0){	
		Node * newNode = createNode(entity, response);
		if(newNode ==NULL){
			return KB_NOMEM;
		}
		else
		{
			kb = insertKnowledgeBase(kb , "who", createNode(entity,response));
			return KB_OK;
		}
	}
	else{
		return KB_INVALID;
	}
}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {
	
	/* to be implemented */
	
	return 0;
}


/*
 * Reset the knowledge base, removing all know entities from all intents.
 */
void knowledge_reset() {
	kb = clearKnowledgeBase(kb);
	
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {
	
	/* to be implemented */
	
}