#include <stdio.h>
#include <stdlib.h>
#define ERROR_VALUE 9999;
typedef struct queueNode_t
{
    int value;
    struct queueNode_t *next;
} QueueNode;


int QueueAdd(QueueNode **ptrTail, int value)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    QueueNode *tail = *ptrTail;

    if (!tail)
    {
        temp->value = value;
        temp->next = temp;
        *ptrTail = temp;
    }
    else
    {
        temp->value = value;
        temp->next = tail->next;
        tail->next = temp;
        *ptrTail = temp;
    }
    return 1;
}

int QueueRemove(QueueNode **ptrTail)
{
    QueueNode *tail = *ptrTail;
    QueueNode *deleteMe;
    int value;

    if (!tail)
        return ERROR_VALUE;

    if (tail->next == tail)
    {
        value = tail->value;
        free(tail);
        *ptrTail = NULL;
        return value;
    }
    deleteMe = tail->next;
    value = deleteMe->value;
    tail->next = deleteMe->next;
    free(deleteMe);
    return value;
}

void printList(QueueNode *tail)
{
    if (!tail)
        return;

    QueueNode *head = tail->next;
    printf("\n%d ", head->value);
    QueueNode *currNode = head->next;

    while (currNode != head)
    {
        printf("%d ", currNode->value);
        currNode = currNode->next;
    }
}

int main()
{
    QueueNode *tail = NULL;
    QueueAdd(&tail, 1);
    QueueAdd(&tail, 2);
    QueueAdd(&tail, 3);
    QueueAdd(&tail, 4);
    QueueAdd(&tail, 5);
    for (int i = 0; i < 5; i++)
        printf("%d ", QueueRemove(&tail));
    return 0;

}