#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"
#include <math.h>

#define MAX_CAPACITY 50
#define ERROR_VALUE -999

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a < b ? b : a;
}

typedef struct Stack
{
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
    if (stk->top + 1 == stk->capacity){
        printf("Stack is full.\n");
        return;
    }
    stk->top++;
    stk->data[stk->top] = value;
}

int stackPop(Stack *stk) {
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

typedef struct Queue {
	Stack* stk1;
	Stack* stk2;
}Queue;

Queue* createQueue() {
	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->stk1 = createStack();	
	que->stk2 = createStack();
	return que;
}

void queueAdd(Queue* que, int value) {
	StackPush(que->stk1, value);
}

int queueRemove(Queue* que) {
	int value;
	if (StackIsEmpty(que->stk2)) {	
		while (!StackIsEmpty(que->stk1)) {
			value = stackPop(que->stk1);
			StackPush(que->stk2, value);
		}
	}
	return stackPop(que->stk2);
}

int queueSize(Queue* que) {
	return stackSize(que->stk1) + stackSize(que->stk2);
}

int main() {
	Queue* que = createQueue();
	queueAdd(que, 1);
	queueAdd(que, 2);
	queueAdd(que, 3);
    queueAdd(que, 4);
	queueAdd(que, 5);
	queueAdd(que, 6);
	while(queueSize(que) > 0)
		printf("%d  ", queueRemove(que));

}