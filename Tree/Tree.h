#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *lChild;
    struct TreeNode *rChild;
} TreeNode;

typedef struct Tree {
    TreeNode* root;
} Tree;

#define ERROR_VALUE -999
#define MAX_CAPACITY 100

typedef struct Stack
{
    int top;
    TreeNode **data;
    int capacity;
} Stack;

Stack* createStack() {
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->data = (TreeNode **)malloc(MAX_CAPACITY * sizeof(TreeNode *));
    stk->top = -1;
    stk->capacity = MAX_CAPACITY;
    return stk;
}

void StackPush(Stack *stk, TreeNode *value) {
    if (stk->top + 1 == stk->capacity){
        printf("Stack is full.\n");
        return;
    }
    stk->top++;
    stk->data[stk->top] = value;
}

TreeNode* StackPop(Stack *stk) {
    if (stk->top == -1) {
        printf("stack empty.\n");
        return NULL;
    }
    
    TreeNode* value = stk->data[stk->top];
    stk->top--;
    return value;
}

TreeNode* StackTop(Stack *stk) {
    TreeNode* value = stk->data[stk->top];
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
        printf("%d ", stk->data[i]->value);
    }
    printf("]\n");
}

typedef struct Queue
{
	int front;
	int back;
	int size;
	TreeNode* data[MAX_CAPACITY];
} Queue;

Queue* createQueue() {
	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->back = 0;
	que->front = 0;
	que->size = 0;
	return que;
}

void QueueAdd(Queue *que, TreeNode * value) {
	if (que->size == MAX_CAPACITY) {
		printf("Queue is full.\n");
		return;
	}
	que->size++;
	que->data[que->back] = value;
	que->back = (que->back + 1) % MAX_CAPACITY;
}

TreeNode * QueueRemove(Queue *que) {
	TreeNode* value;
	if (que->size == 0) {
		printf("Queue is empty.\n");
		return NULL;
	}
	que->size--;
	value = que->data[que->front];
	que->front = (que->front + 1) % MAX_CAPACITY;
	return value;
}

TreeNode * QueueFront(Queue *que) {
	return que->data[que->front];
}

TreeNode * QueueBack(Queue *que) {
	return que->data[que->back-1];
}

TreeNode * QueueRemoveBack(Queue *que) {
	if (que->size == 0) {
		printf("Queue is empty.\n");
		return NULL;
	}
	que->size--;
	TreeNode *value = que->data[que->back - 1];
	que->back = (que->back - 1) % MAX_CAPACITY;
	return value;
}

int QueueIsEmpty(Queue *que) {
	return que->size == 0;
}

int QueueSize(Queue *que) {
	return que->size;
}

void QueuePrint(Queue *que) {
	int size = que->size;
	printf("[ ");
	int index = que->front;
	for (int i=0;i<size;i++) {
			printf("%d ", que->data[index]->value);
			index = (index + 1) % MAX_CAPACITY;
	}
	printf("]\n");
}
