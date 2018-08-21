#include <stdlib.h>
#include <stdio.h>
#define ERROR_VALUE -99999

typedef struct stackNode_t
{
    int value;
    struct stackNode_t *next;
} StackNode;

void StackPush(StackNode **ptrHead, int value)
{
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    if (!temp)
    {
        printf("Memory allocation error");
        return;
    }
    temp->value = value;
    temp->next = *ptrHead;
    *ptrHead = temp;
}

int StackPop(StackNode **ptrHead) //free the returned node yourself
{
    StackNode *deleteMe;
    int value;
    if (*ptrHead)
    {
        deleteMe = *ptrHead;
        *ptrHead = deleteMe->next;
        value = deleteMe->value;
        free(deleteMe);
        return value;
    }
    else
    {
        printf("Stack is empty \n");
        return ERROR_VALUE;
    }
}

int main()
{
    StackNode *head = NULL;
    StackPush(&head, 1);
    StackPush(&head, 2);
    StackPush(&head, 3);
    StackPush(&head, 4);
    StackPush(&head, 5);
    for (int i = 0; i < 5; i++)
        printf("%d", StackPop(&head));
    return 0;
}