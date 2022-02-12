#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#ifndef ERROR_VALUE
#define ERROR_VALUE -99999
#endif 

#define MAX_CAPACITY 100

typedef struct Stack {
    int top;
    int *data;
    int capacity;
} Stack;

Stack* createStack() {
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->data = (int *)malloc(MAX_CAPACITY * sizeof(int));
    stk->top = -1;
    stk->capacity = MAX_CAPACITY;
    return stk;
}

void stackPush(Stack *stk, int value) {
    if (stk->top + 1 == stk->capacity) {
        printf("Stack is full.\n");
        return;
    }
    stk->top++;
    stk->data[stk->top] = value;
}

int stackPop(Stack *stk) {
    if (stk->top == -1) {
        printf("stack empty.\n");
        return ERROR_VALUE;
    }
    
    int value = stk->data[stk->top];
    stk->top--;
    return value;
}

int stackTop(Stack *stk) {
    int value = stk->data[stk->top];
    return value;
}

int stackIsEmpty(Stack *stk) {
    return (stk->top == -1);
}

int stackSize(Stack *stk) {
    return (stk->top + 1);
}

void stackPrint(Stack *stk) {
    printf("[");
    for (int i = stk->top; i >= 0; i--) {
        printf("%d ", stk->data[i]);
    }
    printf("]\n");
}

int mainA() {
    Stack* stk = createStack();
    stackPush(stk, 1);       
    stackPush(stk, 2);
    stackPush(stk, 3);
    stackPrint(stk);
    printf("%d ",stackPop(stk));
    printf("%d ",stackPop(stk));
    return 0;
}

/*
[3 2 1 ]
3 2
*/

int mainB() {
    Stack* stk = createStack();
    for (int i = 0; i < 20; i++)
        stackPush(stk, i);
    printf("stackTop %d \n", stackTop(stk));
    printf("stackSize %d \n", stackSize(stk));
    printf("stackIsEmpty %d \n", stackIsEmpty(stk));
    stackPrint(stk);
    for (int i = 0; i < 20; i++)
        printf("%d ",stackPop(stk));
    printf("stackIsEmpty %d \n", stackIsEmpty(stk));
    return 0;
}