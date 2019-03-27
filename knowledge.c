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

KnowledgeBase * kb = NULL;

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
        snprintf(response, n, "%s", getNodeContent(found));
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
	
	int lines_read = 0;

	char line[MAX_ENTITY + 1 + MAX_RESPONSE + 1];
	char sectionHeading[MAX_INTENT+2];
    char intent[MAX_INTENT+2];

    char entity[MAX_ENTITY];
    char response[MAX_RESPONSE];


	// Loop through each line until EOF
    while ((fgets(line, MAX_ENTITY + 1 + MAX_RESPONSE + 1, (FILE*)f)) != NULL){
        // Remove newline
        line[strlen(line)-2] = '\0'; 
        // If empty line, ignore
        if(strlen(line) == 0) continue;

        // Find section heading
        strcpy(sectionHeading, findIntent(line));

        // If section heading is found in buff
        if(strlen(sectionHeading) != 0){
            // If section heading is an invalid intent, set intent to ""
            if(strcmp(sectionHeading, "[]") == 0) strcpy(intent, "");
            // else section heading is a valid intent, set intent to section heading
            else strcpy(intent, sectionHeading);
        
        // buff is entity/response pair
        }else{
            //Split into entity and response
            splitEntityResponse(line, entity, response);
            //If there is a response
            if(strlen(response) > 0){
                // If valid intent, increment lines_read
				if (strcmp(intent,"") != 0) lines_read++;
				// For each valid intent, save entity and response
                if (strcmp(intent, "what") == 0) kb = insertKnowledgeBase(kb , "what", createNode(entity,response));
                if (strcmp(intent, "where") == 0) kb = insertKnowledgeBase(kb , "where", createNode(entity,response));
                if (strcmp(intent, "who") == 0) kb = insertKnowledgeBase(kb , "who", createNode(entity,response));
                // If invalid intent, entity and response not saved
            }
            
        }

    }
	
	return lines_read;
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

    Node * temp = NULL;
    int writeHeading = 1;

    for(int i = 0; i < BUCKET_SIZE; i++){
        temp = kb->whatDict[i];
        while(temp != NULL){
            
            if(writeHeading){
                fprintf(f, "%s\r\n", "[what]");
                writeHeading = 0;
            }
            fprintf(f, "%s=%s\r\n", getNodeKey(temp), getNodeContent(temp));
            temp = temp->next;
        }
    }

    writeHeading = 1;

    for(int i = 0; i < BUCKET_SIZE; i++){
        temp = kb->whereDict[i];
        while(temp != NULL){
            if(writeHeading){
                fprintf(f, "\r\n%s\r\n", "[where]");
                writeHeading = 0;
            }
            fprintf(f, "%s=%s\r\n", getNodeKey(temp), getNodeContent(temp));
            temp = temp->next;
        }
    }
    writeHeading = 1;

    for(int i = 0; i < BUCKET_SIZE; i++){
        temp = kb->whoDict[i];
        while(temp != NULL){
            if(writeHeading){
                fprintf(f, "\r\n%s\r\n", "[who]");
                writeHeading = 0;
            }
            fprintf(f, "%s=%s\r\n", getNodeKey(temp), getNodeContent(temp));
            temp = temp->next;
        }
    }


    
	/* to be implemented */
	
}

int startWith(char buffer[], char prefix[]){
    int i = 0;

    while(buffer[i] != '\0' && prefix[i] != '\0'){
        if(toupper(prefix[i]) != toupper(buffer[i])) return 0;
        i++;
    }
    if(prefix[i] == '\0') return 1;
    return 0;

}

const char * findIntent(char buffer[]){
    // If does not start with "[", means it is a line
    if(buffer[0] != '[') return "";

    // If start with [what], [where], [who], return what, where, who
    if(startWith(buffer, "[what]")) return "what";
    if(startWith(buffer, "[where]")) return "where";
    if(startWith(buffer, "[who]")) return "who";

    // Check if section heading 
    for(int i = 1; i < strlen(buffer); i++) if (buffer[i] == ']') return "[]";

    // It is a line
    return "";
}


void splitEntityResponse(char buffer[], char * entity, char * response){
    int entityidx = 0;
    int responseidx = 0;

    int delimited = 0;

    for(int i = 0; i < strlen(buffer); i++){
        if(buffer[i] == '=' && delimited == 0){
            delimited = 1;
        }else{
            if(delimited == 0) entity[entityidx++] = buffer[i];
            else response[responseidx++] = buffer[i];
        }
    }
    entity[entityidx] = '\0';
    response[responseidx] = '\0';
} 

void knowledge_init(){
    if (kb == NULL) kb = createKnowledgeBase();
}