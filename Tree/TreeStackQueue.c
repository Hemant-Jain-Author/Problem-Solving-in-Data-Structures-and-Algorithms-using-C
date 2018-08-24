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
treeNode *levelOrderBinaryTree(int arr[], int size)
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

void PrintDepthFirst(treeNode *root)
{
    Stack stk;
    StackInitialize(&stk);
    treeNode *temp = NULL;
    if (root != NULL)
        StackPush(&stk, (int)root);
    while (StackSize(&stk) != 0)
    {
        temp = (treeNode *)StackPop(&stk);
        printf("%d ", temp->value);
        if (temp->rChild != NULL)
            StackPush(&stk, (int)temp->rChild);
        if (temp->lChild != NULL)
            StackPush(&stk, (int)temp->lChild);
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

    treeNode *temp = NULL;
    if (root != NULL)
        StackPush(&stk1, (int)root);
    while (StackSize(&stk1) != 0 || StackSize(&stk2) != 0)
    {
        while (StackSize(&stk1) != 0)
        {
            temp = (treeNode *)StackPop(&stk1);
            printf("%d ", temp->value);
            if (temp->rChild != NULL)
                StackPush(&stk2, (int)temp->rChild);
            if (temp->lChild != NULL)
                StackPush(&stk2, (int)temp->lChild);
        }
        while (StackSize(&stk2) != 0)
        {
            temp = (treeNode *)StackPop(&stk2);
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

int isCompleteTree(treeNode *root)
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
    return 1;
}

int isCompleteTreeUtil(treeNode *curr, int index, int count)
{
    if (curr == NULL)
        return 1;
    if (index > count)
        return 0;
    return isCompleteTreeUtil(curr->lChild, index * 2 + 1, count) && isCompleteTreeUtil(curr->rChild, index * 2 + 2, count);
}

int isCompleteTree2(treeNode *root)
{
    int count = findCount(root);
    return isCompleteTreeUtil(root, 0, count);
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

void printAllPathUtil(treeNode *curr, Stack *stk)
{
    if (curr == NULL)
        return;
    StackPush(stk, curr->value);
    if (curr->lChild == NULL && curr->rChild == NULL)
    {
        StackPrint(stk);
        StackPop(stk);
        return;
    }
    printAllPathUtil(curr->rChild, stk);
    printAllPathUtil(curr->lChild, stk);
    StackPop(stk);
}

void printAllPath(treeNode *root)
{
    Stack stk;
    StackInitialize(&stk);
    printAllPathUtil(root, &stk);
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

void iterativePreOrder(treeNode *root)
{
    Stack stk;
    StackInitialize(&stk);
    treeNode *curr = NULL;
    if (root != NULL)
        StackPush(&stk, (int)root);
    while (StackSize(&stk) != 0)
    {
        curr = (treeNode *)StackPop(&stk);
        printf("%d ", curr->value);
        if (curr->rChild != NULL)
            StackPush(&stk, (int)curr->rChild);
        if (curr->lChild != NULL)
            StackPush(&stk, (int)curr->lChild);
    }
}

void iterativePostOrder(treeNode *root)
{
    Stack stk;
    StackInitialize(&stk);
    Stack visited;
    StackInitialize(&visited);
    treeNode *curr = NULL;
    int vtd;
    if (root != NULL)
    {
        StackPush(&stk, (int)root);
        StackPush(&visited, 0);
    }
    while (StackSize(&stk) != 0)
    {
        curr = (treeNode *)StackPop(&stk);
        vtd = StackPop(&visited);
        if (vtd == 1)
            printf("%d ", curr->value);
        else
        {
            StackPush(&stk, (int)curr);
            StackPush(&visited, 1);
            if (curr->rChild != NULL)
            {
                StackPush(&stk, (int)curr->rChild);
                StackPush(&visited, 0);
            }
            if (curr->lChild != NULL)
            {
                StackPush(&stk, (int)curr->lChild);
                StackPush(&visited, 0);
            }
        }
    }
}
void iterativeInOrder(treeNode *root)
{
    Stack stk;
    StackInitialize(&stk);
    Stack visited;
    StackInitialize(&visited);
    treeNode *curr = NULL;
    int vtd;
    if (root != NULL)
    {
        StackPush(&stk, (int)root);
        StackPush(&visited, 0);
    }

    while (StackSize(&stk) != 0)
    {
        curr = (treeNode *)StackPop(&stk);
        vtd = StackPop(&visited);
        if (vtd == 1)
            printf("%d ", curr->value);
        else
        {
            if (curr->rChild != NULL)
            {
                StackPush(&stk, (int)curr->rChild);
                StackPush(&visited, 0);
            }
            StackPush(&stk, (int)curr);
            StackPush(&visited, 1);
            if (curr->lChild != NULL)
            {
                StackPush(&stk, (int)curr->lChild);
                StackPush(&visited, 0);
            }
        }
    }
}

int isBSTArray(int preorder[], int size)
{
    Stack stk;
    int value;
    StackInitialize(&stk);
    int root = -999999;
    for (int i = 0; i < size; i++)
    {
        value = preorder[i];

        // If value of the right child is less than root.
        if (value < root)
            return 0;
        // First left child values will be popped
        // Last popped value will be the root.
        while (StackSize(&stk) > 0 && StackTop(&stk) < value)
            root = StackPop(&stk);
        // add current value to the stack.
        StackPush(&stk, value);
    }
    return 1;
}

int main()
{
    int preorder1[] = {30, 20, 25, 70, 200};
    printf("Is BST Array : %d \n", isBSTArray(preorder1, 5));
}

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    treeNode *t = levelOrderBinaryTree(arr, sizeof(arr) / sizeof(int));
    printAllPath(t);
    PrintBredthFirst(t);
    printf("\n");
    PrintDepthFirst(t);
    printf("\n");
    PrintLevelOrderLineByLine(t);
    printf("\n");
    PrintLevelOrderLineByLine2(t);
    printf("\n");
    PrintSpiralTree(t);
    printf("\n");
    printf("Total nodes count :: %d \n", findCount(t));
    printf("\n");
    printf("Is CompleteTree :: %d \n", isCompleteTree(t));
    printf("Is CompleteTree :: %d \n", isCompleteTree2(t));
    printf("Is Heap :: %d \n", isHeap(t));
    printf("Is Heap :: %d \n", isHeap2(t));
    iterativePreOrder(t);
    printf("\n");

    iterativePostOrder(t);
    printf("\n");

    iterativeInOrder(t);

    /*printf("Level order sum:: \n");
	printf("level order max:: \n");
	printf("Level order sum max:: \n");
	*/
    return 0;
}