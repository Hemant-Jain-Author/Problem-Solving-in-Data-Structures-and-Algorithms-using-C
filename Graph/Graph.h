#include <stdio.h>
#include <stdlib.h>

typedef struct GraphEdge_t
{
    int src;
    int dest;
    int cost;
    struct GraphEdge_t *next;
} GraphEdge;

typedef struct graph
{
    int count;
    GraphEdge **adj;
} Graph;

int greater(GraphEdge* a, GraphEdge* b){
    return a->cost > b->cost;
}

int max(int first, int second) {
    return (first > second) ? first : second;
}

typedef struct stack
{
    int top;
    int *data;
    int capacity;
} Stack;

Stack* createStack(int size) {
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->data = (int *)malloc(size * sizeof(int));
    stk->top = -1;
    stk->capacity = size;
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



#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct Queue_t
{
	int front;
	int back;
	int size;
	int data[MAX_CAPACITY];
} Queue;

Queue* createQueue() {
	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->back = 0;
	que->front = 0;
	que->size = 0;
	return que;
}

void QueueAdd(Queue *que, int value) {
	if (que->size == MAX_CAPACITY) {
		printf("Queue is full.\n");
		return;
	}
	que->size++;
	que->data[que->back] = value;
	que->back = (que->back + 1) % MAX_CAPACITY;
}

int QueueRemove(Queue *que) {
	int value;
	if (que->size == 0) {
		printf("Queue is empty.\n");
		return ERROR_VALUE;
	}
	que->size--;
	value = que->data[que->front];
	que->front = (que->front + 1) % MAX_CAPACITY;
	return value;
}

int QueueFront(Queue *que) {
	return que->data[que->front];
}

int QueueBack(Queue *que) {
	return que->data[que->back-1];
}

int QueueRemoveBack(Queue *que) {
	int value;
	if (que->size == 0) {
		printf("Queue is empty.\n");
		return ERROR_VALUE;
	}
	que->size--;
	value = que->data[que->back - 1];
	que->back = (que->back - 1) % MAX_CAPACITY;
	return value;
}

int QueueIsEmpty(Queue *que) {
	return que->size == 0;
}

int QueueSize(Queue *que) {
	return que->size;
}

#define INFINITE 9999999

typedef struct Heap_t
{
    int capacity;
    int size;
    GraphEdge**array;
    int(* compare)(GraphEdge* , GraphEdge*);
} Heap;

Heap* createHeap(int(* compare)(GraphEdge* , GraphEdge*)) {
    Heap* hp = (Heap*)malloc(sizeof(Heap));
    hp->size = 0;
    hp->capacity = 100;
    hp->array = (GraphEdge **)malloc((hp->capacity) * sizeof(GraphEdge));
    hp->compare = compare;
    return hp;
}

void proclateDown(GraphEdge* arr[], int position, int size, int(* compare)(GraphEdge* , GraphEdge*)) {
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;
    int small = -1;

    if (lChild < size)
        small = lChild;

    if (rChild < size && compare(arr[lChild], arr[rChild]))
        small = rChild;

    if (small != -1 && compare(arr[position], arr[small])) {
        GraphEdge* temp = arr[position];
        arr[position] = arr[small];
        arr[small] = temp;
        proclateDown(arr, small, size, compare);
    }
}

void proclateUp(GraphEdge* arr[], int position, int(* compare)(GraphEdge* , GraphEdge*)) {
    int parent = (position - 1) / 2;
    if (parent >= 0) {
        if (compare(arr[parent], arr[position])) {
            GraphEdge* temp = arr[position];
            arr[position] = arr[parent];
            arr[parent] = temp;

            proclateUp(arr, parent, compare);
        }
    }
}

void heapify(GraphEdge* arr[], int size, int(* compare)(GraphEdge* , GraphEdge*)) {
    for (int i = size/2; i >= 0; i--)
        proclateDown(arr, i, size, compare);
}

GraphEdge* heapRemove(Heap *hp) {
    GraphEdge* value = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    proclateDown(hp->array, 0, hp->size, hp->compare);
    return value;
}

void heapAdd(Heap *hp, GraphEdge* value) {
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = value;
    proclateUp(hp->array, hp->size - 1, hp->compare);
}

int heapSize(Heap *hp) {
    return hp->size;
}