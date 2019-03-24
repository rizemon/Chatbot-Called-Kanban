/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */
 
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "knowledgebase.h"

/** Global Variable for hashtable containing all the smalltalk phrases*/
/** Initialise smalltalks variable as NULL*/
Node ** smalltalks = NULL;

KnowledgeBase * kb = NULL;
 
/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chatbot";
	
}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";
	
}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {
    /** Checks if hashtable has been created before invoking create hashtable function */
    if (smalltalks == NULL){
        /** Creates smalltalk hash table*/
        smalltalk_hashtable();
    }
	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}
	if (kb == NULL){
		kb = createKnowledgeBase();
	}
	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
    else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {
	
	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;
	
}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {
	 
	snprintf(response, n, "Goodbye!");
	 
	return 1;
	 
}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {
	
	/*When user types in load(case-insensitive) */
	return compare_token(intent, "load") == 0;
	
}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */

	return 0;
	 
}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {
	/*When user types in what,where or who(case-insensitive) */
	return compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 || compare_token(intent, "who") == 0;
	
}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {
	char *intent = inv[0];
	char entity[MAX_ENTITY];
	char *removed[MAX_ENTITY];
	int counter =0;
	for(int i =1; i<inc; i++){
		//checks for if/are and removes them from entity
		if(compare_token(inv[i], "is") != 0){
			if(compare_token(inv[i], "are") != 0){
				if(counter == 0){
					strcpy(entity, inv[i]);
					strcat(entity, " ");
				}else{
					strcat(entity,inv[i]);
					strcat(entity," ");
				}
			}else{
				strcpy(removed,inv[i]);
			}
			counter++;
		}else{
			strcpy(removed,inv[i]);
		}
	}	
	printf("[DEBUG]Entity:%s\n",entity);
	if(knowledge_get(intent, entity, response, n) == KB_NOTFOUND){
		char answer[MAX_RESPONSE];
		prompt_user(answer, n,"I don't know. %s %s %s?",intent,removed,entity);
		knowledge_put(intent,entity, answer);
		snprintf(response, n, "Thank you");	

	}
	return 0;
}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {
	/*When user types in reset(case-insensitive) */
	return compare_token(intent, "reset") == 0;
	
}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 *   0 (the chatbot always continues chatting after benign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {
	knowledge_reset();
	char buffer[MAX_RESPONSE];
	strcpy(buffer, chatbot_botname());
	strcat(buffer, " resetted");
	snprintf(response, n, buffer);
	
	return 0;
	 
}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {
	

	/*When user types in reset(case-insensitive) */

	return compare_token(intent, "save") == 0;
	
}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	
	return 0;
	 
}

/** This function creates a hashtable filled with smalltalk nodes that store key value pairs of smalltalk intent and response respectively
    This functions directly modifies the values of the global variable smalltalks so all other functions can reference directly reference the smalltalk hashtable
 */
void smalltalk_hashtable(){
    /** Create smalltalk nodes containing key pair values of all the small talk phrases*/
    Node * smalltalk1 = createNode("bye", "goodbye");
    Node * smalltalk5 = createNode("goodbye", "bye");
    Node * smalltalk2 = createNode("hi", "hello");
    Node * smalltalk3 = createNode("hey", "hello");
    Node * smalltalk4 = createNode("sup", "whatsup");
    
    /** Create a hashtable to store smalltalks*/
    smalltalks = createHashTable();
    
    /** Insert nodes into smalltalks hashtable*/
    smalltalks = insertHashTable(smalltalks, smalltalk1 );
    smalltalks = insertHashTable(smalltalks, smalltalk2 );
    smalltalks = insertHashTable(smalltalks, smalltalk3 );
    smalltalks = insertHashTable(smalltalks, smalltalk4 );
    smalltalks = insertHashTable(smalltalks, smalltalk5 );
}
 
/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent) {
    /** If intent matches key inside linkedlist smalltalk, return 1, otherwise, return 0 */
    if (findHashTable(smalltalks, intent) != NULL) {
        return 1;
    }
    else {
        return 0;
    }
 
}


/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {
    char *intent = inv[0];
    char *smalltalk_response = findHashTable(smalltalks, intent)->content;
    char end_phrases[][10] = {"bye", "goodbye"};
    int index, str_cmp, found= 0;
    /* Check if intent is any of the ending phrases */
    for(index = 0; index < sizeof(end_phrases) / sizeof(char *); index++)
    {
            str_cmp = strcmp(intent, end_phrases[index]);
            if (str_cmp == 0) {
                /** smalltalk matches end_phrases */
                found += 1;
            }
    }
    /** If no matching end_phrases found, print smalltalk_response and return 0 to continue catting*/
    if (found == 0) {
        snprintf(response,  n, smalltalk_response);
        return 0;
    }
    /** If a matching end_phrase was found, print smalltalk_response and return 1 to end the chat*/
    else {
        snprintf(response,  n, smalltalk_response);
        return 1;
    }
    
}
  
