#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

/********************************************************************************* 
* Giandra Hutama, ghutama
* 2022 Spring CSE101 PA1 
* List.c 
* Functions for the list. 
*********************************************************************************/

typedef struct NodeObj{
    struct NodeObj* next;
    struct NodeObj* prev;
    int data;
}NodeObj;

typedef struct NodeObj* Node;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
}ListObj;

Node newNode(int data){
    Node N = NULL;
    N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return N;
}

void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN =NULL;
    }
}

List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->index = -1;
    L->length = 0;
    return L;
}

void freeList(List* pL){
    if(pL != NULL && *pL != NULL)
    {
        while(length(*pL) > 0){
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

int length(List L){
    return L->length;
}

int index(List L){
    if(length(L) <= 0){
        return -1;
    }
    return L->index;
}

int front(List L){
    if(length(L) <= 0){
        printf("Error: front() cannot be called. The list is empty.");
    }
    return L->front->data;
}

int back(List L){
    if(length(L) <= 0){
        printf("Error: back() cannot be called. The list is empty.");
    }
    return L->back->data;
}

int get(List L){
    if(length(L) <= 0){
        printf("Error: get() cannot be called. The list is empty.");
    }
    return L->cursor->data;
}

bool equals(List A, List B){
    bool eq;
    Node N1, N2;
    eq = (A->length == B->length);
    N1 = A->front;
    N2 = B->front;
    while(eq && N1 != NULL){
        eq = (N1->data == N2->data);
        N1 = N1->next;
        N2 = N2->next;
    }
    return eq;
}

void clear(List L){
    while(length(L) > 0){
        deleteFront(L);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->index = -1;
    L->length = 0;
}

void moveFront(List L){
    if (L == NULL){
        printf("List Error: calling moveFront() on a NULL List reference\n");
        exit(1);
    }
        if(length(L) > 0){
            L->cursor = L->front;
            L->index = 0;
    }
}

void moveBack(List L){
    if(length(L) > 0){
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L){
    if(L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        L->cursor = L->cursor->prev;
        L->index--;
    }
}

void moveNext(List L){
    if(L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        L->cursor = L->cursor->next;
        L->index++;
    }
}

void prepend(List L, int x){
    Node N = newNode(x);
    if(L->front == NULL){
        L->front = N;
        L->back = N;
        L->cursor = L->front;
    }
    else{
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
        L->index++;
    }
    L->length++;
}

void append(List L, int x){
    Node N = newNode(x);
    if(L->front == NULL){
        L->front = N;
        L->back = N;
        L->cursor = L->back;
    }
    else{
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
        N->next = NULL;
    }
    L->length++;
}

void insertBefore(List L, int x){
    if(L->cursor == L->front){
        prepend(L, x);
    }
    else{
        Node N = newNode(x);
        N->prev = L->cursor->prev;
        N->next = L->cursor;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->index++;
        L->length++;
    }
}

void insertAfter(List L, int x){
        if(L->cursor == L->back){
        append(L, x);
    }
    else{
        Node N = newNode(x);
        L->cursor->next->prev = N;
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next = N;
        L->length++;
    }
}

void deleteFront(List L){
    if(length(L) <= 0){
        printf("Error: deletefront() cannot be called. The list is empty.");
    }
        if(L->length == 1){
            Node N = L->front;
            freeNode(&N);
            L->cursor = NULL;
            L->front = L->back = NULL;
            L->index = -1;
        }
        else{
            Node N = L->front;
            L->front = L->front->next;
            L->front->prev = NULL;
            if(L->cursor != NULL){
                L->index--;
            }
            freeNode(&N);
        }
        L->length--;
}

void deleteBack(List L){
    if(length(L) <= 0){
        printf("Error: deleteBack() cannot be called. The list is empty.");
    }
        if(L->length == 1){
            Node N = L->back;
            freeNode(&N);
            L->cursor = NULL;
            L->front = L->back = NULL;
            L->index = -1;
        }
        else{
            Node N = L->back;
            L->back = L->back->prev;
            L->back->next = NULL;
            if(L->index == L->length - 1){
                L->index = -1;
            }
            freeNode(&N);
        }
        L->length--;

}

void delete(List L){
    if(L->cursor == L->front){
        deleteFront(L);
    }
    else if(L->cursor == L->back){
        deleteBack(L);
    }
    else{
        Node N = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&N);
        L->length--;
    }
    L->index = -1;
}

void printList(FILE* out, List L){
    Node N = NULL;
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d", N->data);
        fprintf(out," ");
    }
}

List copyList(List L){
    List L2 = newList();
    if(length(L) > 0){
        Node N = L->front;
        while(N != NULL){
            append(L2, N->data);
            N = N->next;
        }
    }
    L2->cursor = NULL;
    L2->index = -1;
    return L2;
}