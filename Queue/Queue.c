// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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
		que->back = (++(que->back)) % (MAX_CAPACITY - 1);
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
		que->front = (++(que->front)) % (MAX_CAPACITY - 1);
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
		que->back = (que->front - 1) % (MAX_CAPACITY - 1);
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
	int arr[20];
	int steps = 0;
	int index = 0;
	int value;
	QueueInitialize(&que);
	QueueAdd(&que, (src, 0));
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
		if (value > 0)
			QueueAdd(&que, value - 1);
	}
	return -1;
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

int main3()
{
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	return 0;
	//Output 75, 92, 92, 92, 90
}

void minOfMaxSlidingWindows(int arr[], int size, int k)
{
	Queue que;
	QueueInitialize(&que);
	int minVal = 999999;
	for (int i = 0; i < size; i++)
	{
		//Remove out of range elements if (que && que[0] <= i - k)
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
}

int main4()
{
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
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
		//Remove out of range elements if (que && que[0] <= i - k)
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

int main5()
{
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	return 0;
	//Output  59, as minimum values in sliding windows are [2, 2, 59, 59, 55]
}

void firstNegSlidingWindows(int arr[], int size, int k)
{
	Queue que;
	QueueInitialize(&que);
	for (int i = 0; i < size; i++)
	{
		//Remove out of range elements if (que && que[0] <= i - k)
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

int main6()
{
	int arr[] = { 3, -2, -6, 10, -14, 50, 14, 21 };
	int k = 3;
	return 0;

	//Output  [-2, -2, -6, -14, -14, NAN]
}

typedef struct tNode
{
	int value;
	struct tNode *lChild;
	struct tNode *rChild;
} treeNode;

treeNode *levelOrderBinaryTreeUtil(int arr[], int size, int start)
{
	treeNode *curr = (treeNode *)malloc(sizeof(treeNode));
	curr->value = arr[start];
	curr->lChild = curr->rChild = NULL;
	int left = 2 * start + 1;
	int right = 2 * start + 2;
	if (left < size)
		curr->lChild = levelOrderBinaryTreeUtil(arr, size, left);
	if (right < size)
		curr->rChild = levelOrderBinaryTreeUtil(arr, size, right);
	return curr;
}
treeNode* levelOrderBinaryTree(int arr[], int size)
{
	return levelOrderBinaryTreeUtil(arr, size, 0);
}
void PrintBredthFirst(treeNode *root)
{
	Queue que;
	QueueInitialize(&que);
	treeNode *temp = NULL;
	if (root != NULL)
		QueueAdd(&que, (int)root);
	while (QueueSize(&que) != 0)
	{
		temp = (treeNode *)QueueRemove(&que);
		printf("%d ", temp->value);
		if (temp->lChild != NULL)
			QueueAdd(&que, (int)temp->lChild);
		if (temp->rChild != NULL)
			QueueAdd(&que, (int)temp->rChild);
	}
}

void PrintLevelOrderLineByLine(treeNode *root)
{
	Queue que1;
	QueueInitialize(&que1);
	Queue que2;
	QueueInitialize(&que2);
	treeNode *temp = NULL;
	if (root != NULL)
		QueueAdd(&que1, (int)root);
	while (QueueSize(&que1) != 0 || QueueSize(&que2) != 0)
	{
		while (QueueSize(&que1) != 0)
		{
			temp = (treeNode *)QueueRemove(&que1);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				QueueAdd(&que2, (int)temp->lChild);
			if (temp->rChild != NULL)
				QueueAdd(&que2, (int)temp->rChild);
		}
		printf("\n");
		;
		while (QueueSize(&que2) != 0)
		{
			temp = (treeNode *)QueueRemove(&que2);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				QueueAdd(&que1, (int)temp->lChild);
			if (temp->rChild != NULL)
				QueueAdd(&que1, (int)temp->rChild);
		}
		printf("\n");
		;
	}
}

void PrintLevelOrderLineByLine2(treeNode *root)
{
	Queue que;
	QueueInitialize(&que);
	treeNode *temp = NULL;
	int count;

	if (root != NULL)
		QueueAdd(&que, (int)root);
	while (QueueSize(&que) != 0)
	{
		count = QueueSize(&que);
		while (count > 0)
		{
			temp = (treeNode *)QueueRemove(&que);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				QueueAdd(&que, (int)temp->lChild);
			if (temp->rChild != NULL)
				QueueAdd(&que, (int)temp->rChild);
			count -= 1;
		}
		printf("\n");
		;
	}
}

void PrintSpiralTree(treeNode *root)
{
	Stack stk1;
	StackInitialize(&stk1);

	Stack stk2;
	StackInitialize(&stk2);

	treeNode* temp = NULL;
	if (root != NULL)
		StackPush(&stk1, (int)root);
	while (StackSize(&stk1) != 0 || StackSize(&stk2) != 0)
	{
		while (StackSize(&stk1) != 0)
		{
			temp = (treeNode*)StackPop(&stk1);
			printf("%d ", temp->value);
			if (temp->rChild != NULL)
				StackPush(&stk2, (int)temp->rChild);
			if (temp->lChild != NULL)
				StackPush(&stk2, (int)temp->lChild);
		}
		while (StackSize(&stk2) != 0)
		{
			temp = (treeNode*)StackPop(&stk2);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				StackPush(&stk1, (int)temp->lChild);
			if (temp->rChild != NULL)
				StackPush(&stk1, (int)temp->rChild);
		}
	}
}

/*
To see if tree is a heap we need to check two conditions
1) It is a complete tree.
2) Value of a node is grater than || equal to it's left and right child.
*/

int findCount(treeNode *curr)
{
	if (curr == NULL)
		return 0;
	return (1 + findCount(curr->lChild) + findCount(curr->rChild));
}

int isCompleteTreeUtil(treeNode *curr, int index, int count)
{
	if (curr == NULL)
		return 1;
	if (index > count)
		return 0;
	return isCompleteTreeUtil(curr->lChild, index * 2 + 1, count) && isCompleteTreeUtil(curr->rChild, index * 2 + 2, count);
}

int isCompleteTree(treeNode *root)
{
	int count = findCount(root);
	return isCompleteTreeUtil(root, 0, count);
}

int isCompleteTree2(treeNode *root)
{
	Queue que;
	QueueInitialize(&que);
	treeNode *temp = NULL;
	int noChild = 0;
	if (root != NULL)
		QueueAdd(&que, (int)root);
	while (QueueSize(&que) != 0)
	{
		temp = (treeNode *)QueueRemove(&que);
		if (temp->lChild != NULL)
		{
			if (noChild == 1)
				return 0;
			QueueAdd(&que, (int)temp->lChild);
		}
		else
			noChild = 1;

		if (temp->rChild != NULL)
		{
			if (noChild == 1)
				return 0;
			QueueAdd(&que, (int)temp->rChild);
		}
		else
			noChild = 1;
	}
}

int isHeapUtil(treeNode *curr, int parentValue)
{
	if (curr == NULL)
		return 1;
	if (curr->value < parentValue) 
		return 0;
	return (isHeapUtil(curr->lChild, curr->value) && isHeapUtil(curr->rChild, curr->value));
}

int isHeap(treeNode *root)
{
	int infi = -9999999;
	return (isCompleteTree(root) && isHeapUtil(root, infi));
}

int isHeapUtil2(treeNode *curr, int index, int count, int parentValue)
{
	if (curr == NULL)
		return 1;
	if (index > count)
		return 0;
	if (curr->value < parentValue)
		return 0;
	return isHeapUtil2(curr->lChild, index * 2 + 1, count, curr->value) && isHeapUtil2(curr->rChild, index * 2 + 2, count, curr->value);
}

int isHeap2(treeNode *root)
{
	int count = findCount(root);
	int parentValue = -9999999;
	return isHeapUtil2(root, 0, count, parentValue);
}
/*
void isHeap3(treeNode *root)
{
	Queue que;
	QueueInitialize(&que);
	QueueAdd(&que, root);
	QueueAdd(&que, 0);
	QueueAdd(&que, -99999);
	int count = 0;
	while (QueueSize(&que) != 0)
	{
		curr = QueueRemove(&que);
		currIndex = QueueRemove(&que);
		parentValue = QueueRemove(&que);

		if (curr->value < parentValue || currIndex != count)
			return 0;
		count += 1;
		if (curr->lChild != NULL)
		{
			QueueAdd(&que, curr->lChild);
			QueueAdd(&que, currIndex * 2 + 1);
			QueueAdd(&que, curr->value);
		}
		if (curr->rChild != NULL)
		{
			QueueAdd(&que, curr->rChild);
			QueueAdd(&que, currIndex * 2 + 2);
			QueueAdd(&que, curr->value);
		}
	}
	return 1;
}
*/

/*
Use queue to traverse the tree. In queue you will keep index and parent value.
When you dequeue element from queue you will keep track count of element
count should be equal to the index value.
*/

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	treeNode *t = levelOrderBinaryTree(arr, sizeof(arr) / sizeof(int));
	PrintBredthFirst(t);
	printf("\n");
	//PrintBredthFirst(t);
	PrintLevelOrderLineByLine(t);
	printf("Is CompleteTree :: %d", isCompleteTree(t));
	printf("isHeap",  isHeap(t));
	//PrintSpiralTree(t);
	PrintLevelOrderLineByLine(t);
	PrintLevelOrderLineByLine2(t);
	printf("Level order sum");
	printf("level order max");
	printf("Level order sum max");
}