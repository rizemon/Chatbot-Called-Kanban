#include "linkedlist.h"
#include "hashtable.h"
#include "knowledgebase.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){ 

    FILE * fp = fopen("./knowledgebase.ini","w");

    fprintf(fp, "%s\n", "[what]");

    fclose(fp);

     
    return 0; 
}

