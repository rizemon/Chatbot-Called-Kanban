#include "linkedlist.h"
#include "hashtable.h"
#include "knowledgebase.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* the maximum number of characters we expect in a line of input (including the terminating null)  */
#define MAX_INPUT    256

/* the maximum number of characters allowed in the name of an intent (including the terminating null)  */
#define MAX_INTENT   32

/* the maximum number of characters allowed in the name of an entity (including the terminating null)  */
#define MAX_ENTITY   64

/* the maximum number of characters allowed in a response (including the terminating null) */
#define MAX_RESPONSE 256

#define TRUE 1
#define FALSE 0


int startWith(char buffer[], char prefix[]){
    int i = 0;

    while(buffer[i] != '\0' && prefix[i] != '\0'){
        if(toupper(prefix[i]) != toupper(buffer[i])) return FALSE;
        i++;
    }
    if(prefix[i] == '\0') return TRUE;
    return FALSE;

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

int main(){ 


    // printf("%d\n", startWith("ay","yay"));
    // Node ** newHashTable = NULL; 
 
    // newHashTable = createHashTable(); 
 
    // Node * newNode = createNode("fuck", "you"); 
 
    // newHashTable = insertHashTable(newHashTable, newNode); 
 
    // newHashTable = insertHashTable(newHashTable, createNode("fuck", "someone")); 
 
    // Node * found = findHashTable(newHashTable, "fuck"); 
    // if(found == NULL){ 
    //     //cannot find 
    // }else{ 
    //     //can find 
    //     printNode(found); 
    // } 
 
    // newHashTable = deleteHashTable(newHashTable, "fuck"); 
    // newHashTable = clearHashTable(newHashTable); 
 
    // KnowledgeBase * kb = NULL; 
    // kb = createKnowledgeBase(); 
    // kb = insertKnowledgeBase(kb , "what", createNode("SIT","fucked up")); 
    // kb = insertKnowledgeBase(kb , "where", createNode("SIT","fucked up")); 
    // kb = insertKnowledgeBase(kb , "who", createNode("SIT","fucked up")); 
     
    // found = searchKnowledgeBase(kb, "who", "SIT"); 
    // if(found == NULL){ 
    //     //cannot find 
    // }else{ 
    //     printNode(found); 
    // } 
    // kb = clearKnowledgeBase(kb); 

    FILE *fp;

    int size = MAX_ENTITY + 1 + MAX_RESPONSE + 1;

    char buff[MAX_ENTITY + 1 + MAX_RESPONSE + 1];
    
    char sectionHeading[MAX_ENTITY + 1 + MAX_RESPONSE + 1];
    char intent[MAX_ENTITY + 1 + MAX_RESPONSE + 1];

    char entity[MAX_ENTITY];
    char response[MAX_RESPONSE];

    Node * what = NULL;
    Node * where = NULL;
    Node * who = NULL;



    fp = fopen("/mnt/c/Users/Tan Jia Le/Documents/Chatbot-Called-Kanban/sample.ini", "r");

    // Loop through each line until EOF
    while ((fgets(buff, size, (FILE*)fp)) != NULL){
        // Remove newline
        buff[strlen(buff)-2] = '\0'; 
        // If empty line, ignore
        if(strlen(buff) == 0) continue;

        // Find section heading
        strcpy(sectionHeading, findIntent(buff));

        // If section heading is found in buff
        if(strlen(sectionHeading) != 0){
            // If section heading is an invalid intent, set intent to ""
            if(strcmp(sectionHeading, "[]") == 0) strcpy(intent, "");
            // else section heading is a valid intent, set intent to section heading
            else strcpy(intent, sectionHeading);
        
        // buff is a line
        }else{
            //Split into entity and response
            splitEntityResponse(buff, entity, response);
            //If there is a reponse
            if(strlen(response) > 0){
                // If valid intent, save entity and response
                if (strcmp(intent, "what") == 0) what = addNode(what, createNode(entity, response));
                if (strcmp(intent, "where") == 0) where = addNode(where, createNode(entity, response));
                if (strcmp(intent, "who") == 0) who = addNode(who, createNode(entity, response));
                // If invalid intent, entity and response not saved
            }
            
        }

    }

    printAll(what);
    printf("\n");
    printAll(where);
    printf("\n");
    printAll(who);
    fclose(fp);


     
    return 0; 
}

