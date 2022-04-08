#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define MAX 100

/********************************************************************************* 
* Giandra Hutama, ghutama
* 2022 Spring CSE101 PA1 
* Lex.c 
* Lex file. 
*********************************************************************************/

int main(int argc, char *argv[]){
    int lNum, lCount = 0;
    char str[MAX];
    char **strArr;
    FILE *in, *out;

    if(argc < 3 || argc > 3){
        printf("Error");
        exit(1);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    while(fgets(str, MAX, in) != NULL){
        lCount++;
    }
    rewind(in);

    strArr = malloc((lCount) * sizeof(char*));
    for(int i = 0; i < lCount; i++){
        strArr[i] = malloc((MAX) * sizeof(char));
    }

    while(fgets(str, sizeof(str), in) != NULL){
        strcpy(strArr[lNum], str);
        lNum++;
    }

    List nList = newList();
    append(nList, 0);
    for(int i = 1; i < lCount; i++){
        moveFront(nList);
        char* lElement = strArr[i];
        int j = i;
        while(j > 0 && strcmp(lElement, strArr[get(nList)]) >= 0){
            moveNext(nList);
            j--;
        }
        if(index(nList) >= 0){
            insertBefore(nList, i);
        }
        else{
            append(nList, i);
        }
    }

    moveFront(nList);
    while(index(nList) >= 0){
        fprintf(out, "%s", strArr[get(nList)]);
        moveNext(nList);
    }
    fclose(in);
    fclose(out);
    freeList(&nList);

    for(int i = 0; i< lCount; i++){
        free(strArr[i]);
    }
    free(strArr);
    return 0;
}