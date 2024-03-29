//#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

#define QUEUE_CAPACITY 2000

#ifndef ERROR_VALUE
#define ERROR_VALUE -99999
#endif 

typedef struct Queue {
	int front;
	int back;
	int size;
	int data[QUEUE_CAPACITY];
} Queue;

Queue* createQueue() {
	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->back = 0;
	que->front = 0;
	que->size = 0;
	return que;
}

void queueAdd(Queue *que, int value) {
	if (que->size == QUEUE_CAPACITY) {
		printf("Queue is full.\n");
		return;
	}
	que->size++;
	que->data[que->back] = value;
	que->back = (que->back + 1) % QUEUE_CAPACITY;
}

int queueRemove(Queue *que) {
	int value;
	if (que->size == 0) {
		printf("Queue is empty.\n");
		return ERROR_VALUE;
	}
	que->size--;
	value = que->data[que->front];
	que->front = (que->front + 1) % QUEUE_CAPACITY;
	return value;
}

int queueFront(Queue *que) {
	return que->data[que->front];
}

int queueBack(Queue *que) {
	return que->data[que->back-1];
}

int queueRemoveBack(Queue *que) {
	int value;
	if (que->size == 0) {
		printf("Queue is empty.\n");
		return ERROR_VALUE;
	}
	que->size--;
	value = que->data[que->back - 1];
	que->back = (que->back - 1) % QUEUE_CAPACITY;
	return value;
}

int queueIsEmpty(Queue *que) {
	return que->size == 0;
}

int queueSize(Queue *que) {
	return que->size;
}

void queuePrint(Queue *que) {
	int size = que->size;
	printf("[ ");
	int index = que->front;
	for (int i=0;i<size;i++) {
			printf("%d ", que->data[index]);
			index = (index + 1) % QUEUE_CAPACITY;
	}
	printf("]\n");
}