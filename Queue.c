#include "stdio.h"
#include "stdlib.h"

#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct Queue_t{
	int front;
	int back;
	int size;
	int data[MAX_CAPACITY];
}Queue;

void QueueInitialize(Queue* que)
{
	que->back = 0;
	que->front = 0;
	que->size = 0;
}

void Enqueue(Queue* que, int value)
{
	if (que->size >= MAX_CAPACITY )
	{
		printf("\n Queue is full.");
		return;
	}
	else
	{
		que->size++;
		que->data[que->back] = value;
		que->back = (++(que->back)) % (MAX_CAPACITY - 1);
	}
}

int Dequeue(Queue* que)
{
	int value;
	if (que->size <= 0)
	{
		printf("\n Queue is empty.");
		return ERROR_VALUE;
	}
	else
	{
		que->size--;
		value = que->data[que->front];
		que->front = (++(que->front)) % (MAX_CAPACITY - 1);
	}
	return value;
}

int QueueIsEmpty(Queue* que)
{
	return que->size == 0;
}

int QueueSize(Queue* que)
{
	return que->size;
}

int main()
{
	Queue que;
	QueueInitialize(&que);
	for (int i = 0; i < 20; i++)
	{
		Enqueue(&que,i);
	}
	for (int i = 0; i < 20; i++)
	{
		printf(" %d ", Dequeue(&que));
	}
	return 0;
}