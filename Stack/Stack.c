#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#ifndef ERROR_VALUE
#define ERROR_VALUE -99999
#endif 



typedef struct Stack {
    int top;
    int *data;
    int capacity;
} Stack;


#define STACK_CAPACITY 100

Stack* createStack() {
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->data = (int *)malloc(STACK_CAPACITY * sizeof(int));
    stk->top = -1;
    stk->capacity = STACK_CAPACITY;
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
    if (stk->top == -1) {
        printf("stack empty.\n");
        return ERROR_VALUE;
    }    
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

typedef struct Stack2 {
    int top;
    int *data;
    int capacity;
    int mincapacity;
} Stack2;

Stack2* createStack2(int size) {
    Stack2 *stk = (Stack2*)malloc(sizeof(Stack));
    stk->data = (int *)malloc(size * sizeof(int));
    stk->top = -1;
    stk->capacity = size;
    stk->mincapacity = size; // flex stack
    return stk;
}

// flex stack push
void stackPush2(Stack2 *stk, int value) {
    if (stk->top + 1 == stk->capacity) {
        printf("Stack size doubled.\n");
        stk->capacity = stk->capacity * 2;
        stk->data = (int *)realloc(stk->data, stk->capacity * sizeof(int));
    }
    stk->top++;
    stk->data[stk->top] = value;
}

// flex stack pop
int stackPop2(Stack2 *stk) {
    if (stk->top == -1) {
        printf("stack empty.\n");
        return ERROR_VALUE;
    }

    int topVal = stk->data[stk->top];
    stk->top--;

    if (stk->top + 1 < (stk->capacity / 2) && stk->capacity > stk->mincapacity) {
        printf("Stack size halfed.\n");
        stk->capacity = stk->capacity / 2;
        stk->data = (int *)realloc(stk->data, stk->capacity * sizeof(int));
    }
    return topVal;
}

int mainC() {
    Stack2* stk = createStack2(5);
    for (int i = 0; i <= 11; i++)
        stackPush2(stk, i);
    for (int i = 0; i <= 11; i++)
        printf("%d ", stackPop2(stk));
    return 0;
}

int main() {
    //mainA();
    //mainB();
    mainC();
}