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
    if(buffer[0] != '[') return "";

    char * what = "what";
    char * where = "where";
    char * who = "who";

    //If iswhat == 1, continue check for "what"
    int iswhat = 1;
    //If iswhere == 1, continue check for "where"
    int iswhere = 1;
    //If iswho == 1, continue check for "who"
    int iswho = 1;

    int i;
    for(i = 1; i < strlen(buffer); i++){

        //If "what", "where" or "who" is found, break
        if(*what == '\0' || *who == '\0' || *where == '\0') break;

        //If you are still checking for "what" and current character match, increment to next character
        if(iswhat && buffer[i] == *what) what++;
        //Else stop checking for "what"
        else iswhat = 0;

        if(iswhere && buffer[i] == *where) where++;
        else iswhere = 0;

        if(iswho && buffer[i] == *who) who++;
        else iswho = 0;
        
        if(iswhat == 0 && iswhere == 0 && iswho == 0) return "[]"
    }

    if(buffer[i] == ']') {
        if(*what == '\0') return "what";
        else if(*where == '\0') return "where";
        else if(*who == '\0') return "who";
    // Invalid section
        else {
            return "[]";
            
        }
    }
    //Its a line
    return "";
    

    
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
    printf("%s\n", findIntent("[wtf]"));
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
    char realIntent[MAX_ENTITY + 1 + MAX_RESPONSE + 1];

    Node * what = NULL;
    Node * where = NULL;
    Node * who = NULL;



    // fp = fopen("/mnt/c/Users/Tan Jia Le/Documents/Chatbot-Called-Kanban/sample.ini", "r");
    // while ((fgets(buff, size, (FILE*)fp)) != NULL){
    //     //Remove newline
    //     buff[strlen(buff)-2] = '\0'; 
    //     //If empty line, ignore
    //     if(strlen(buff) == 0) continue;

    //     //Find intent if any. If not found, intent == ""
    //     strcpy(checkIntent,findIntent(buff));

    //     // If line is section heading
    //     if(strlen(checkIntent) != 0){
    //         //If section heading is an invalid intent
    //         if(strcmp(checkIntent, "[]") == 0){
    //             strcpy(realIntent, "");
    //         }else{
    //             // Set realIntent to section heading
    //             strcpy(realIntent, checkIntent);
    //         }
    //     }else{
    //         if(strcmp(realIntent, "what") == 0) what = addNode(what, createNode(buff,""));
    //         if(strcmp(realIntent, "where") == 0) where = addNode(where, createNode(buff,""));
    //         if(strcmp(realIntent, "who") == 0) who = addNode(who, createNode(buff,""));
            
    //     }

    // }

    // printAll(what);
    // printf("\n");
    // printAll(where);
    // printf("\n");
    // printAll(who);
    // fclose(fp);


     
    return 0; 
}

