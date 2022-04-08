#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

/********************************************************************************* 
* Giandra Hutama, ghutama
* 2022 Spring CSE101 PA1 
* ListTest.c 
* Test File for the list. 
*********************************************************************************/

    int main(void){
        List A = newList();
        append(A, 1);
        deleteBack(A);
        append(A, 10);
        append(A, 6);
        append(A, 25);
        moveFront(A);
        insertAfter(A, 23);
        deleteBack(A);
        if (length(A) != 3){
            printList(stdout,A);
        } 
        return 0;
    }