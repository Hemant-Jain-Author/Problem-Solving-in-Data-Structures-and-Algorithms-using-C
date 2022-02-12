#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 50
#define ERROR_VALUE 999999

typedef struct stack {
    int top1;
    int top2;
    int data[MAX_SIZE];
} Stack;

Stack* createStack() {
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->top1 = -1;
    stk->top2 = MAX_SIZE;
    return stk;
}

void StackPush1(Stack *stk, int data) {
    if (stk->top1 < stk->top2 - 1) {
        stk->data[++stk->top1] = data;
    } else {
        printf("Stack is Full!\n");
    }
}

void StackPush2(Stack *stk, int data) {
    if (stk->top1 < stk->top2 - 1) {
        stk->data[--stk->top2] = data;
    } else {
        printf("Stack is Full!\n");
    }
}

int StackPop1(Stack *stk) {
    if (stk->top1 >= 0) {
        int value = stk->data[stk->top1--];
        return value;
    } else {
        printf("Stack Empty!\n");
    }
    return ERROR_VALUE;
}

int StackPop2(Stack *stk) {
    if (stk->top2 < MAX_SIZE) {
        int value = stk->data[stk->top2++];
        return value;
    } else {
        printf("Stack Empty!\n");
    }
    return ERROR_VALUE;
}

int main() {
    Stack* stk = createStack();
    StackPush1(stk, 1);       
    StackPush1(stk, 2);
    StackPush2(stk, 3);
    StackPush2(stk, 4);
    printf("%d \n",StackPop1(stk));
    printf("%d \n",StackPop1(stk));
    printf("%d \n",StackPop2(stk));
    printf("%d \n",StackPop2(stk));
}

/*
2 
1 
4 
3 
*/