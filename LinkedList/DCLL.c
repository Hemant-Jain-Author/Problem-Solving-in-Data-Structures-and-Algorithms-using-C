#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t
{
    int value;
    struct Node_t *next;
    struct Node_t *prev;
} Node;

typedef struct DCLL_t
{
    Node *head;
} DCLL;

void InitDCLL(DCLL *list){
    list->head = NULL;
}

int insertAtStart(DCLL *list, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }
    temp->value = value;

    Node *head = list->head;
    if (!head)
    {
        temp->next = temp;
        temp->prev = temp;
        list->head = temp;
    }
    else
    {
        temp->prev = head->prev;
        temp->prev->next = temp;
        temp->next = head;
        head->prev = temp;
        list->head = temp;
    }
    return 1;
}

int insertAtEnd(DCLL *list, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }
    temp->value = value;

    Node *head = list->head;
    if (!head)
    {
        temp->next = temp;
        temp->prev = temp;
        list->head = temp;
    }
    else
    {
        temp->prev = head->prev;
        temp->prev->next = temp;
        temp->next = head;
        head->prev = temp;
    }
    return 1;
}

int removeFromStart(DCLL *list)
{
    Node *head = list->head;
    if (!head)
        printf("Empty List Error");

    int value = head->value;

    if (head->next == head)
    {
        free(head);
        list->head = NULL;
        return value;
    }

    Node *tail = head->prev;
    Node *next = head->next;

    next->prev = tail;
    tail->next = next;
    free(head);
    list->head = next;
    return value;
}

int removeFromEnd(DCLL *list)
{
    Node *head = list->head;
    if (!head)
        printf("Empty List Error");

    Node *tail = head->prev;
    int value = tail->value;

    if (tail->next == tail)
    {
        free(tail);
        list->head = NULL;
        return value;
    }

    Node *prev = tail->prev;
    prev->next = head;
    head->prev = prev;
    free(tail);
    return value;
}

int searchList(DCLL *list, int key)
{
    Node *head = list->head;
    if (!head)
        return 0;

    Node *curr = head;

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

void freeList(DCLL *list)
{
    Node *head = list->head;
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
    list->head = NULL;
}

int printList(DCLL *list)
{
    Node *head = list->head;
    if (!head)
        return 0;
    Node *curr = head;
    do
    {
        printf("%d ", curr->value);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
    return 0;
}

int main()
{
    DCLL list;
    InitDCLL(&list);
    insertAtStart(&list, 1);
    insertAtStart(&list, 2);
    insertAtStart(&list, 3);
    insertAtStart(&list, 4);
    insertAtStart(&list, 5);
    insertAtEnd(&list, 6);
    insertAtEnd(&list, 7);
    printList(&list);

    removeFromEnd(&list);
    removeFromStart(&list);
    printList(&list);

    printf("searchList: %d \n",searchList(&list,3));
    printf("searchList: %d \n",searchList(&list,6));
    
    freeList(&list);
    printList(&list);
    return 0;
}