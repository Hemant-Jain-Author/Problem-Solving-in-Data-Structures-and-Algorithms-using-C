/*
   For any linked list there are only three cases zero element ,one element,general
   Any program which is likely to change head pointer is to be passed a double pointer 

   for doubly linked list we have few more things 
   0> NULL values
   1> only element (it genaralt introduce an if statement with null)
   2> Always an if before while. which will check from this head .
   3> general case (check with the initial head kept)
   4> Avoide using recursion solutions it makes life harder
  
  */

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    int value;
    struct listNode *next;
} Node;

int insertAtStart(Node **ptrTail, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    Node *tail = *ptrTail;

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
    }
    return 1;
}

int insertAtEnd(Node **ptrTail, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    Node *tail = *ptrTail;

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

void printList(Node *tail)
{
    if (!tail)
        return;

    Node *head = tail->next;
    printf("\n%d ", head->value);
    Node *currNode = head->next;

    while (currNode != head)
    {
        printf("%d ", currNode->value);
        currNode = currNode->next;
    }
}

int searchList(Node *tail, int value)
{
    if (!tail)
        return 0;

    if (tail->value == value)
        return 1;

    Node *curr = tail->next;
    while (curr != tail)
    {
        if (curr->value == value)
            return 1;
        curr = curr->next;
    }
    return 0;
}

void deleteList(Node **ptrTail)
{
    Node *tail = *ptrTail;
    Node *curr;
    Node *next;
    if (!tail)
        return;

    curr = tail->next;
    free(tail);

    while (curr != tail)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *ptrTail = NULL;
}

/* Delete a node given its pointer */
void deleteNodePtr(Node **ptrTail, Node *ptrDel)
{
    Node *tail = *ptrTail;
    Node *curr = tail;
    Node *prev = NULL;
    Node *deleteMe;

    if (ptrDel == NULL || !tail)
        return;

    prev = curr;
    curr = curr->next;
    while (curr != tail)
    {
        if (curr == ptrDel)
        {
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr == ptrDel)
    {
        prev->next = curr->next;
        free(curr);
        *ptrTail = prev;
    }
}

int deleteNode(Node **ptrTail, int value)
{
    Node *tail = *ptrTail;
    Node *curr = tail;
    Node *prev = NULL;
    Node *deleteMe;

    if (!tail)
        return 0;

    prev = curr;
    curr = curr->next;
    while (curr != tail)
    {
        if (curr->value == value)
        {
            prev->next = curr->next;
            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->value == value)
    {
        prev->next = curr->next;
        free(curr);
        *ptrTail = prev;
        return 1;
    }
    return 0;
}

int deleteHeadNode(Node **ptrTail)
{
    Node *tail = *ptrTail;
    Node *deleteMe;

    if (!tail)
        return 0;

    if (tail->next == tail)
    {
        free(tail);
        *ptrTail = NULL;
        return 1;
    }
    deleteMe = tail->next;
    tail->next = deleteMe->next;
    free(deleteMe);
    return 1;
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
    printList(*ptrHead);
    deleteNode(ptrHead, 6);
    printList(*ptrHead);

    Node *head2 = NULL;
    Node **ptrHead2 = &head2;

    insertAtEnd(ptrHead2, 1);
    insertAtEnd(ptrHead2, 2);
    insertAtEnd(ptrHead2, 3);
    insertAtEnd(ptrHead2, 4);
    insertAtEnd(ptrHead2, 5);
    insertAtEnd(ptrHead2, 6);
    insertAtEnd(ptrHead2, 7);
    printList(*ptrHead2);
    return 0;
}