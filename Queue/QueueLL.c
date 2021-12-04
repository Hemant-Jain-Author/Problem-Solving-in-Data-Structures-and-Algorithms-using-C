#include <stdio.h>
#include <stdlib.h>
#define ERROR_VALUE 999999;

typedef struct QueueNode
{
    int value;
    struct QueueNode *next;
} QueueNode;

typedef struct QueueNode
{
    QueueNode *tail;
} QueueNode;

Queue* createQueue() 
{
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->tail = NULL;
    return queue;
}

int queueIsEmpty(Queue *queue) {
    return queue->tail == NULL;
}

int queueAdd(Queue *queue, int value) {
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    if (!temp) {
        printf("Memory Allocation Error");
        return 0;
    }
    temp->value = value;

    if (!queue->tail) {
        temp->next = temp;
        queue->tail = temp;    
    } else {
        temp->next = queue->tail->next;    
        queue->tail->next = temp;
        queue->tail = temp;
    }
    return 1;
}
int queueRemove(Queue *queue) {
    int value;
    QueueNode *deleteMe;

    if (!queue->tail)
        return ERROR_VALUE;

    if (queue->tail->next == queue->tail) {
        value = queue->tail->value;
        free(queue->tail);
        queue->tail = NULL;
        return value;
    }

    deleteMe = queue->tail->next;
    value = deleteMe->value;
    queue->tail->next = deleteMe->next;
    free(deleteMe);
    return value;
}

void queuePrint(Queue *queue) {
    if (!queue->tail)
        return;

    QueueNode *head = queue->tail->next;
    printf("Queue %d ", head->value);
    QueueNode *currNode = head->next;
    while (currNode != head) {
        printf("%d ", currNode->value);
        currNode = currNode->next;
    }
    printf("\n");
}

int main() {
    Queue* queue = createQueue();
    queueAdd(queue, 1);
    queueAdd(queue, 2);
    queueAdd(queue, 3);

    while(!queueIsEmpty(queue))
        printf("%d ", queueRemove(queue));
    return 0;
}