//#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct Queue_t
{
	int front;
	int back;
	int size;
	int data[MAX_CAPACITY];
} Queue;

void QueueInitialize(Queue *que)
{
	que->back = 0;
	que->front = 0;
	que->size = 0;
}

void QueueAdd(Queue *que, int value)
{
	if (que->size >= MAX_CAPACITY)
	{
		printf("\n Queue is full.");
		return;
	}
	else
	{
		que->size++;
		que->data[que->back] = value;
		que->back = (que->back + 1) % (MAX_CAPACITY - 1);
	}
}

int QueueRemove(Queue *que)
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
		que->front = (que->front + 1) % (MAX_CAPACITY - 1);
	}
	return value;
}

int QueueFront(Queue *que)
{
	return que->data[que->front];
}
int QueueBack(Queue *que)
{
	return que->data[que->back - 1];
}
int QueueRemoveBack(Queue *que)
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
		value = que->data[que->back - 1];
		que->back = (que->back - 1) % (MAX_CAPACITY - 1);
	}
	return value;
}

int QueueIsEmpty(Queue *que)
{
	return que->size == 0;
}

int QueueSize(Queue *que)
{
	return que->size;
}

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

int main1()
{
	Queue que;
	QueueInitialize(&que);
	for (int i = 0; i < 20; i++)
	{
		QueueAdd(&que, i);
	}
	for (int i = 0; i < 20; i++)
	{
		printf(" %d ", QueueRemove(&que));
	}
	return 0;
}
void printArray(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		printf(" %d ", arr[i]);
	printf("\n");
}
int CircularTour(int arr[][2], int n)
{
	Queue que;
	QueueInitialize(&que);
	int nextPump = 0, prevPump;
	int count = 0;
	int petrol = 0;

	while (QueueSize(&que) != n)
	{
		while (petrol >= 0 && QueueSize(&que) != n)
		{
			QueueAdd(&que, nextPump);
			petrol += (arr[nextPump][0] - arr[nextPump][1]);
			nextPump = (nextPump + 1) % n;
		}
		while (petrol < 0 && QueueSize(&que) > 0)
		{
			prevPump = QueueRemove(&que);
			petrol -= (arr[prevPump][0] - arr[prevPump][1]);
		}
		count += 1;
		if (count == n)
			return -1;
	}
	if (petrol >= 0)
		return QueueRemove(&que);
	else
		return -1;
}
int main2()
{
	// Testing code
	int tour[3][2] = { { 8, 6 },{ 1, 4 },{ 7, 6 } };
	printf(" Circular Tour : %d ", CircularTour(tour, 3));
	return 0;
}

int convertXY(int src, int dst)
{
	Queue que;
	int arr[100];
	int steps = 0;
	int index = 0;
	int value;
	QueueInitialize(&que);
	QueueAdd(&que, src);
	while (QueueSize(&que) != 0)
	{
		value = QueueRemove(&que);
		arr[index++] = value;

		if (value == dst)
		{
			printArray(arr, index);
			return steps;
		}
		steps++;
		if (value < dst)
			QueueAdd(&que, value * 2);
		else
			QueueAdd(&que, value - 1);
	}
	return -1;
}

int main3()
{
	convertXY(2, 7);
	return 0;
}

void maxSlidingWindows(int arr[], int size, int k)
{
	Queue que;
	QueueInitialize(&que);
	for (int i = 0; i < size; i++)
	{
		//Remove out of range elements
		if (QueueSize(&que) && QueueFront(&que) <= i - k)
			QueueRemove(&que);
		//Remove smaller values at left.
		while (QueueSize(&que) && arr[QueueBack(&que)] <= arr[i])
			QueueRemoveBack(&que);

		QueueAdd(&que, i);
		//Largest value in window of size k is at index que[0]
		//It is displayed to the screen.
		if (i >= (k - 1))
			printf(" %d ", arr[QueueFront(&que)]);
	}
}

int main4()
{
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	maxSlidingWindows(arr, 7, 3);
	return 0;
	//Output 75, 92, 92, 92, 90
}

int minOfMaxSlidingWindows(int arr[], int size, int k)
{
	Queue que;
	QueueInitialize(&que);
	int minVal = 999999;
	for (int i = 0; i < size; i++)
	{
		//Remove out of range elements 
		if (QueueSize(&que) && QueueFront(&que) <= i - k)
			QueueRemove(&que);
		//Remove smaller values at left.
		while (QueueSize(&que) && arr[QueueBack(&que)] <= arr[i])
			QueueRemove(&que);
		QueueAdd(&que, i);
		//window of size k
		if (i >= (k - 1) && minVal > arr[QueueFront(&que)])
			minVal = arr[QueueFront(&que)];
	}
	printf("Min of max is :: %d ", minVal);
	return minVal;
}

int main5()
{
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	minOfMaxSlidingWindows(arr, 7, 3);
	return 0;
	//Output 75
}

void maxOfMinSlidingWindows(int arr[], int size, int k)
{

	Queue que;
	QueueInitialize(&que);
	int maxVal = -999999;
	for (int i = 0; i < size; i++)
	{
		//Remove out of range elements 
		if (QueueSize(&que) && QueueFront(&que) <= i - k)
			QueueRemove(&que);
		//Remove smaller values at left.
		while (QueueSize(&que) && arr[QueueBack(&que)] >= arr[i])
			QueueRemove(&que);
		QueueAdd(&que, i);
		//window of size k
		if (i >= (k - 1) && maxVal < arr[QueueFront(&que)])
			maxVal = arr[QueueFront(&que)];
	}
	printf("Max of min is :: %d ", maxVal);
}

int main6()
{
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	maxOfMinSlidingWindows(arr, 7, 3);
	return 0;
	//Output  59, as minimum values in sliding windows are [2, 2, 59, 59, 55]
}

void firstNegSlidingWindows(int arr[], int size, int k)
{
	Queue que;
	QueueInitialize(&que);
	for (int i = 0; i < size; i++)
	{
		//Remove out of range elements 
		if (QueueSize(&que) && QueueFront(&que) <= i - k)
			QueueRemove(&que);
		if (arr[i] < 0)
			QueueAdd(&que, i);
		//window of size k
		if (i >= (k - 1))
		{
			if (QueueSize(&que) > 0)
				printf("%d ", arr[QueueFront(&que)]);
			else
				printf("NAN");
		}
	}
}

int main()
{
	int arr[] = { 3, -2, -6, 10, -14, 50, 14, 21 };
	int k = 3;
	firstNegSlidingWindows(arr, 8, 3);
	return 0;
	//Output  [-2, -2, -6, -14, -14, NAN]
}