#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define ERROR_VALUE -999
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

void StackPush(Stack *stk, int value) {
    if (stk->top + 1 == stk->capacity) {
        printf("Stack is full.\n");
        return;
    }
    stk->top++;
    stk->data[stk->top] = value;
}

int StackPop(Stack *stk) {
    if (stk->top == -1) {
        printf("stack empty.\n");
        return -99999;
    }
    
    int value = stk->data[stk->top];
    stk->top--;
    return value;
}

int StackTop(Stack *stk) {
    int value = stk->data[stk->top];
    return value;
}

int StackIsEmpty(Stack *stk) {
    return (stk->top == -1);
}

int StackSize(Stack *stk) {
    return (stk->top + 1);
}

void StackPrint(Stack *stk) {
    printf("[");
    for (int i = stk->top; i >= 0; i--) {
        printf("%d ", stk->data[i]);
    }
    printf("]\n");
}

int mainA() {
    Stack* stk = createStack();
    StackPush(stk, 1);       
    StackPush(stk, 2);
    StackPush(stk, 3);
    StackPrint(stk);
    printf("%d ",StackPop(stk));
    printf("%d ",StackPop(stk));
    return 0;
}

/*
[3 2 1 ]
3 2
*/

int mainB() {
    Stack* stk = createStack();
    for (int i = 0; i < 20; i++)
        StackPush(stk, i);
    printf("StackTop %d \n", StackTop(stk));
    printf("StackSize %d \n", StackSize(stk));
    printf("StackIsEmpty %d \n", StackIsEmpty(stk));
    StackPrint(stk);
    for (int i = 0; i < 20; i++)
        printf("%d ",StackPop(stk));
    printf("StackIsEmpty %d \n", StackIsEmpty(stk));
    return 0;
}