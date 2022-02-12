#include <stdio.h>
#include <stdlib.h>
#define ERROR_VALUE 999999;

typedef struct QueueNode {
    int value;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *tail;
} Queue;

Queue* createQueue() {
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->tail = NULL;
    return queue;
}

int QueueIsEmpty(Queue *queue) {
    return queue->tail == NULL;
}

int QueueAdd(Queue *queue, int value) {
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
int QueueRemove(Queue *queue) {
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

void QueuePrint(Queue *queue) {
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
    QueueAdd(queue, 1);
    QueueAdd(queue, 2);
    QueueAdd(queue, 3);
    printf("%d ", QueueRemove(queue));
    printf("%d ", QueueRemove(queue));
    printf("%d ", QueueRemove(queue));
    return 0;
}