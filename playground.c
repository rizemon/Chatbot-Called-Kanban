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



const char * findIntent(char buffer[]){
    // If does not start with "[", means it is a line
    if(buffer[0] != '[') return "";

    // *ptr points to a character in *.
    char * whatptr = "what";
    char * whereptr = "where";
    char * whoptr = "who";

    //If is* == 1, continue check for *.
    int iswhat = 1;
    int iswhere = 1;
    int iswho = 1;

    // Loop through each character starting after "["
    for(int i = 1; i < strlen(buffer); i++){

        //If found closing bracket
        if(buffer[i] == ']'){
            //If *ptr is pointing to end of string, means * is found
            if(*whatptr == '\0') return "what";
            else if(*whereptr == '\0') return "where";
            else if(*whoptr == '\0') return "who";
            //Else it is a invalid section heading
            else return "[]";
        }

        //If you are still checking for "what" and current character in "what" matches current character in buffer, increment to next character.
        if(iswhat && buffer[i] == *whatptr) whatptr++;
        //Else stop checking for "what"
        else iswhat = 0;

        //If you are still checking for "where" and current character in "where" matches current character in buffer, increment to next character.
        if(iswhere && buffer[i] == *whereptr) whereptr++;
        //Else stop checking for "where"
        else iswhere = 0;

        //If you are still checking for "who" and current character in "who" matches current character in buffer, increment to next character.
        if(iswho && buffer[i] == *whoptr) whoptr++;
        else iswho = 0;
        
    }

    //Its a line
    return "[]";
    

    
}
 
int main(){ 
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

    //should be ok
    
    // printf("%s\n", findIntent("[where]"));
    // printf("%s\n", findIntent("[who]"));
    // printf("%s\n", findIntent("[what]abc"));
    // printf("%s\n", findIntent("[what]\[w]gfdg[who]dfgd"));

    // //should not be ok
    // printf("%s\n", findIntent("[whatabc"));
    // printf("%s\n", findIntent("[w]"));
    // printf("%s\n", findIntent("what]"));
    // printf("%s\n", findIntent("[fuck]"));
    // printf("%s\n", findIntent("a[what]"));

    int isSection = FALSE;
    char checkIntent[MAX_ENTITY + 1 + MAX_RESPONSE + 1];
    char sectionHeading[MAX_ENTITY + 1 + MAX_RESPONSE + 1];

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

        // Find intent if any. If not found, buff is a line
        strcpy(checkIntent,findIntent(buff));

        // If buff is section heading
        if(strlen(checkIntent) != 0){
            // If section heading is an invalid intent, set sectionHeading = ""
            if(strcmp(checkIntent, "[]") == 0) strcpy(sectionHeading, "");
            // else section heading is a valid intent, set sectionHeading to intent
            else strcpy(sectionHeading, checkIntent);
        
        // buff is a line
        }else{
            

            // If valid sectionHeading, save
            if(strcmp(sectionHeading, "what") == 0) what = addNode(what, createNode(buff,""));
            if(strcmp(sectionHeading, "where") == 0) where = addNode(where, createNode(buff,""));
            if(strcmp(sectionHeading, "who") == 0) who = addNode(who, createNode(buff,""));
            // Invalid sectionHeading is not saved
            
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

