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

/*
 * Changes made to knowledge.c:
 *
 * void knowledge_init()
 * int startWith()
 * const char * findIntent()
 * void splitEntityResponse()
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "knowledgebase.h"

// Declare a global scope knowledge base
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
	// If intent matches with the word "what", search what knowledge base for entity.
	if(compare_token(intent, "what") == 0) found = searchKnowledgeBase(kb, "what", entity);
	// Else if intent matches with the word "where", search where knowledge base for entity.
	else if(compare_token(intent, "where") == 0) found = searchKnowledgeBase(kb, "where", entity);
	// Else if intent matches with the word "who", search who knowledge base for entity.
	else if(compare_token(intent, "who") == 0) found = searchKnowledgeBase(kb, "who", entity);
    // Else intent is invalid.
	else return KB_INVALID;
	
	if(found == NULL){
		// No response was found for the question. There is no such entity inside the corresponding knowledge base.
		return KB_NOTFOUND;
	}else{
		// Response was found for the question. There is an entity inside the corresponding knowledge base together with it's response.
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
	//If intent matches the word "what"
	if(compare_token(intent, "what")==0){
		Node * newNode = createNode(entity, response);
		//No more memory for allocating a new node
		if(newNode ==NULL){
			return KB_NOMEM;
		}
		else
		{
			//Add a new node that contain entity and response into what knowledge base. 
			kb = insertKnowledgeBase(kb , "what", createNode(entity,response));
			return KB_OK;
		}
		
	}
	//Else if intent matches the word "where"
	else if (compare_token(intent, "where") ==0){
		Node * newNode = createNode(entity, response);
		//No more memory for allocating a new node
		if(newNode ==NULL){
			return KB_NOMEM;
		}
		else
		{
			//Add a new node that contain entity and response into where knowledge base. 
			kb = insertKnowledgeBase(kb , "where", createNode(entity,response));
			return KB_OK;
		}
	}
	//Else if intent matches the word "who"
	else if (compare_token(intent, "who")== 0){
		Node * newNode = createNode(entity, response);
		//No more memory for allocating a new node
		if(newNode ==NULL){
			return KB_NOMEM;
		}
		else
		{
			//Add a new node that contain entity and response into who knowledge base. 
			kb = insertKnowledgeBase(kb , "who", createNode(entity,response));
			return KB_OK;
		}
	}
	else{
		//Else if intent was not "what" or "who" or "where", return KB_INVALID.
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
	// Number of entity/response pairs read
	int lines_read = 0;

    // Holds contents of a single line in the file
	char line[MAX_ENTITY + 1 + MAX_RESPONSE + 1];

    // Holds the found intent in a line 
    // Empty if line is a possible entity/response pair, 
    // "[]" if line is a invalid section heading, 
    // "what" or "who" or "where" if line is a valid intent
	char sectionHeading[MAX_INTENT];

    // Holds the current intent (e.g "what", "where", "who")
    // to insert the entity/response pair under. If invalid
    // section heading, set this to "".
    char intent[MAX_INTENT];

    // Holds the entity of a entity/response pair line
    char entity[MAX_ENTITY];

    // Holds the response of a entity/response pair line.
    // If empty, means invalid entity/response line
    char response[MAX_RESPONSE];


	// Loop through each line until EOF
    while ((fgets(line, MAX_ENTITY + 1 + MAX_RESPONSE + 1, (FILE*)f)) != NULL){
        // Remove newline
        line[strlen(line)-2] = '\0'; 
        // If empty line, ignore
        if(strlen(line) == 0) continue;

        // Find potential section heading and save it
        snprintf(sectionHeading, MAX_INTENT, "%s", findIntent(line) );

        // Check if section heading is found in line
        if(strlen(sectionHeading) != 0){
            // If section heading is an invalid intent, set intent to ""
            if(strcmp(sectionHeading, "[]") == 0) snprintf(intent, MAX_INTENT, "%s", "");
            // else section heading is a valid intent, set intent to section heading
            else snprintf(intent, MAX_INTENT, "%s", sectionHeading );
        
        // line is entity/response pair
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
    // Holds the current node being read from the knowledge base
    Node * temp = NULL;

    // Holds the boolean on whether to write the section heading to the file
    int writeHeading = 1;

    // Loop through each slot in the whatDict hash table
    for(int i = 0; i < BUCKET_SIZE; i++){
        // Update temp to head pointer at the current slot
        temp = kb->whatDict[i];
        // Loop through each node in the linked list
        while(temp != NULL){
            // If there is at least one node in the hash table and heading is not written yet
            if(writeHeading){
                // Write heading
                fprintf(f, "%s\r\n", "[what]");
                // Stop writing heading from next node onwards
                writeHeading = 0;
            }
            // Write entity/response pair
            fprintf(f, "%s=%s\r\n", getNodeKey(temp), getNodeContent(temp));
            // Increment to next node
            temp = temp->next;
        }
    }

    // Reset to write section heading to file
    writeHeading = 1;

    // Loop through each slot in the whereDict hash table
    for(int i = 0; i < BUCKET_SIZE; i++){
        // Update temp to head pointer at the current slot
        temp = kb->whereDict[i];
        // Loop through each node in the linked list
        while(temp != NULL){
            // If there is at least one node in the hash table and heading is not written yet
            if(writeHeading){
                // Write heading
                fprintf(f, "\r\n%s\r\n", "[where]");
                // Stop writing heading from next node onwards
                writeHeading = 0;
            }
            // Write entity/response pair
            fprintf(f, "%s=%s\r\n", getNodeKey(temp), getNodeContent(temp));
            // Increment to next node
            temp = temp->next;
        }
    }

    // Reset to write section heading to file
    writeHeading = 1;

    // Loop through each slot in the whoDict hash table
    for(int i = 0; i < BUCKET_SIZE; i++){
        // Update temp to head pointer at the current slot
        temp = kb->whoDict[i];
        // Loop through each node in the linked list
        while(temp != NULL){
            // If there is at least one node in the hash table and heading is not written yet
            if(writeHeading){
                // Write heading
                fprintf(f, "\r\n%s\r\n", "[who]");
                // Stop writing heading from next node onwards
                writeHeading = 0;
            }
            // Write entity/response pair
            fprintf(f, "%s=%s\r\n", getNodeKey(temp), getNodeContent(temp));
            // Increment to next node
            temp = temp->next;
        }
    }
	
}

/*
 * Initialize global knowledgebase if done so or already resetted
 */
void knowledge_init(){
    if (kb == NULL) kb = createKnowledgeBase();
}


/*
 * Checks whether a string starts with a given prefix
 *
 * Input:
 *   buffer   - the string to check on
 *   prefix   - the prefix
 *
 * Returns:
 *   0, if prefix not found at the start of the prefix
 *   1, if prefix is found at the start of the prefix
 */
int startWith(char buffer[], char prefix[]){
    int i = 0;

    // Loop through each character in both buffer and prefix until the end of one of them
    while(buffer[i] != '\0' && prefix[i] != '\0'){
        // If one of the character don't match, return false
        if(toupper(prefix[i]) != toupper(buffer[i])) return 0;
        // Increment to next character
        i++;
    }
    // If reached the end of prefix, return true
    if(prefix[i] == '\0') return 1;
    // Else return false
    return 0;

}


/*
 * Extract the possible intent in a given line
 *
 * Input:
 *   buffer   - the given line
 *
 * Returns:
 *   "", if line is a possible entity/response pair
 *   "[]", if line is a invalid section heading
 *   "what", if line is the "what" section heading
 *   "where", if line is the "where" section heading
 *   "who", if line is the "who" section heading
 */
const char * findIntent(char buffer[]){
    // If does not start with "[", means it is a possible entity/response pair
    if(buffer[0] != '[') return "";

    // If start with [what], [where], [who], return "what", "where", "who"
    if(startWith(buffer, "[what]")) return "what";
    if(startWith(buffer, "[where]")) return "where";
    if(startWith(buffer, "[who]")) return "who";

    // Check if section heading 
    for(int i = 1; i < strlen(buffer); i++) if (buffer[i] == ']') return "[]";

    // it is a possible entity/response pair
    return "";
}


/*
 * Extact the entity and response from a given line
 *
 * Input:
 *   buffer   - the given line
 *   entity   - a buffer to receive the entity
 *   response - a buffer to receive the response
 */
void splitEntityResponse(char buffer[], char * entity, char * response){
    // Next index in entity to place the character 
    int entityidx = 0;
    // Next index in response to place the character 
    int responseidx = 0;

    // Holds the boolean on whether to start inserting response
    int delimited = 0;

    // Loop through each character in the given line
    for(int i = 0; i < strlen(buffer); i++){
        // If current character is '=' and still inserting into entity
        if(buffer[i] == '=' && delimited == 0){
            // Stop inserting into entity, start inserting into response
            delimited = 1;
        }else{
            //If still inserting into entity
            if(delimited == 0) entity[entityidx++] = buffer[i];
            //If started inserting into response
            else response[responseidx++] = buffer[i];
        }
    }
    //Terminate both entity and response
    entity[entityidx] = '\0';
    response[responseidx] = '\0';
} 
