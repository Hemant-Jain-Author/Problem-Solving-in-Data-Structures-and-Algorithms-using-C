#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    int value;
    struct listNode *next;
    struct listNode *prev;
} Node;

int insertAtStart(Node **ptrHead, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    Node *head = *ptrHead;

    if (!head)
    {
        temp->value = value;
        temp->next = temp;
        temp->prev = temp;
        *ptrHead = temp;
    }
    else
    {
        temp->value = value;
        temp->prev = head->prev;
        temp->prev->next = temp;
        temp->next = head;
        head->prev = temp;
        *ptrHead = temp;
    }
    return 1;
}

int insertAtEnd(Node **ptrHead, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    Node *head = *ptrHead;

    if (!head)
    {
        temp->value = value;
        temp->next = temp;
        temp->prev = temp;
        *ptrHead = temp;
    }
    else
    {
        temp->value = value;
        temp->prev = head->prev;
        temp->prev->next = temp;
        temp->next = head;
        head->prev = temp;
    }
    return 1;
}

int removeFromStart(Node **ptrHead)
{
    Node *head = *ptrHead;

    if (!head)
        printf("EmptyListError");

    int value = head->value;

    if (head->next == head)
    {
        free(head);
        *ptrHead = NULL;
        return value;
    }
    Node *tail = head->prev;
    Node *next = head->next;

    next->prev = tail;
    tail->next = next;
    free(head);
    *ptrHead = next;
    return value;
}

int removeFromEnd(Node **ptrHead)
{
    Node *head = *ptrHead;

    if (!head)
        printf("EmptyListError");

    Node *tail = head->prev;
    int value = tail->value;

    if (tail->next == tail)
    {
        free(tail);
        *ptrHead = NULL;
        return value;
    }

    Node *prev = tail->prev;
    prev->next = head;
    head->prev = prev;
    free(tail);
    return value;
}

int isPresent(Node **ptrHead, int key)
{
    Node *head = *ptrHead;
    Node *curr = head;
    if (!head)
        return 0;

    do
    {
        if (curr->value == key)
        {
            return 1;
        }
        curr = curr->next;
    } while (curr != head);

    return 0;
}

void freeList(Node **ptrHead)
{
    Node *head = *ptrHead;
    if (!head)
        return;

    Node *curr = head->next;
    Node *next;
    while (curr != head)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(head);
    *ptrHead = NULL;
}

int printList(Node *head)
{
    Node *curr = head;
    if (!head)
        return 0;

    do
    {
        printf(" %d ", curr->value);
        curr = curr->next;
    } while (curr != head);

    return 0;
}

int main()
{
    Node *head = NULL;
    Node **ptrHead = &head;
    insertAtStart(ptrHead, 1);
    insertAtStart(ptrHead, 2);
    insertAtStart(ptrHead, 3);
    insertAtStart(ptrHead, 4);
    insertAtStart(ptrHead, 5);
    insertAtStart(ptrHead, 6);
    insertAtStart(ptrHead, 7);
    insertAtEnd(ptrHead, 9);
    printList(*ptrHead);
    removeFromEnd(ptrHead);
    removeFromStart(ptrHead);
    printList(*ptrHead);
    printf("\n %d \n",isPresent(ptrHead,5));
    printf("\n %d \n",isPresent(ptrHead,9));
    freeList(ptrHead);
    printList(*ptrHead);
    return 0;
}