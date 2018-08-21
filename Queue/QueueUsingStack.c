#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"
#include <math.h>

#define MAX_CAPACITY 50
#define ERROR_VALUE -999

typedef struct stack
{
	int top;
	int data[MAX_CAPACITY];
} Stack;

int min(int a, int b)
{
	return a > b ? b : a;
}

int max(int a, int b)
{
	return a < b ? b : a;
}
void StackInitialize(Stack *stk);
void StackPush(Stack *stk, int value);
int StackPop(Stack *stk);
int StackTop(Stack *stk);
int StackIsEmpty(Stack *stk);
int StackSize(Stack *stk);

void StackInitialize(Stack *stk)
{
	stk->top = -1;
}


void StackPush(Stack *stk, int value)
{
	if (stk->top < MAX_CAPACITY - 1)
	{
		stk->top++;
		stk->data[stk->top] = value;
	}
	else
	{
		printf("stack overflow\n");
	}
}

int StackPop(Stack *stk)
{
	if (stk->top >= 0)
	{
		int value = stk->data[stk->top];
		stk->top--;
		return value;
	}
	printf("stack empty\n");
	return ERROR_VALUE;
}

int StackTop(Stack *stk)
{
	int value = stk->data[stk->top];
	return value;
}

int StackIsEmpty(Stack *stk)
{
	return (stk->top == -1);
}

int StackSize(Stack *stk)
{
	return (stk->top + 1);
}

void StackPrint(Stack *stk)
{
	printf("Stack :: ");
	for (int i = stk->top; i >= 0; i--)
	{
		printf("%d ", stk->data[i]);
	}
	printf("\n");
}

typedef struct Queue_t
{
	Stack stk1;
	Stack stk2;
}Queue;

void QueueInitialize(Queue* que)
{
	StackInitialize(&que->stk1);
	StackInitialize(&que->stk2);
}

void QueueAdd(Queue* que, int value)
{
	StackPush(&que->stk1, value);
}

int QueueRemove(Queue* que)
{
	int value;
	if (!StackIsEmpty(&que->stk2))
		return StackPop(&que->stk2);
	
	while (!StackIsEmpty(&que->stk1))
	{
		value = StackPop(&que->stk1);
		StackPush(&que->stk2, value);
	}
	return StackPop(&que->stk2);
}

int main()
{
	Queue que;
	QueueInitialize(&que);
	QueueAdd(&que, 1);
	QueueAdd(&que, 2);
	QueueAdd(&que, 3);
    QueueAdd(&que, 4);
	QueueAdd(&que, 5);
	QueueAdd(&que, 6);
	printf("%d  ", QueueRemove(&que));
	printf("%d  ", QueueRemove(&que));
	printf("%d  ", QueueRemove(&que));
}