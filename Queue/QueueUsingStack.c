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

void QueueAdd(Queue* que, int value) {
	StackPush(que->stk1, value);
}

int QueueRemove(Queue* que) {
	int value;
	if (StackIsEmpty(que->stk2)) {	
		while (!StackIsEmpty(que->stk1)) {
			value = StackPop(que->stk1);
			StackPush(que->stk2, value);
		}
	}
	return StackPop(que->stk2);
}

int QueueSize(Queue* que) {
	return StackSize(que->stk1) + StackSize(que->stk2);
}

int main() {
	Queue* que = createQueue();
	QueueAdd(que, 1);
	QueueAdd(que, 2);
	QueueAdd(que, 3);
    QueueAdd(que, 4);
	QueueAdd(que, 5);
	QueueAdd(que, 6);
	while(QueueSize(que) > 0)
		printf("%d  ", QueueRemove(que));

}