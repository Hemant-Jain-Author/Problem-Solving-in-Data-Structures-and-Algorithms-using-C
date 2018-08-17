/*
   For any linked list there are only three cases zero element ,one element,general
   Any program which is likely to change head pointer is to be passed a double pointer 

   for doubly linked list we have few more things 

   0> NULL values
   1> only element (tail case)
   2> first element
   3> general case
   4> last element (tail case)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    int value;
    struct listNode *next;
    struct listNode *prev;
} Node;

int insertNode(Node **ptrHead, int value)
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
        temp->next = NULL;
        temp->prev = NULL;
        *ptrHead = temp;
    }
    else
    {
        temp->value = value;
        temp->prev = NULL;
        temp->next = head;
        head->prev = temp;
        *ptrHead = temp;
    }
    return 1;
}

int sortedInsert(Node **ptrHead, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    temp->value = value;
    Node *curr = *ptrHead;

    if (!curr) /*first element*/
    {
        temp->next = NULL;
        temp->prev = NULL;
        *ptrHead = temp;
        return 1;
    }
    if (curr->value <= value) /*at the begining*/
    {
        temp->next = curr;
        temp->prev = NULL;
        curr->prev = temp;
        *ptrHead = temp;
        return 1;
    }

    while (curr->next && curr->next->value > value) /*treversal*/
    {
        curr = curr->next;
    }

    if (!curr->next) /*at the end*/
    {
        temp->next = NULL;
        temp->prev = curr;
        curr->next = temp;
    }
    else /*all other*/
    {
        temp->next = curr->next;
        temp->next->prev = temp;
        temp->prev = curr;
        curr->next = temp;
    }
    return 1;
}

/* Print A singly linked list */
void printList(Node *head)
{
    while (head != NULL)
    {
        printf(" %d  ", head->value);
        head = head->next;
    }
    printf("\n");
}

void printReverseList(Node *head)
{
    if (!head)
        return;

    printReverseList(head->next);
    printf(" %d ", head->value);
}

/* Reverse a doubly linked List iteratively */
void reverseList(Node **ptrHead)
{
    Node *curr = *ptrHead;
    Node *tempNode;

    while (curr)
    {
        tempNode = curr->next;
        curr->next = curr->prev;
        curr->prev = tempNode;

        if (!curr->prev)
        {
            *ptrHead = curr;
            return;
        }
        curr = curr->prev;
    }
    return;
}

/* Delete a singly linked list */
void deleteList(Node **ptrHead)
{
    Node *curr = *ptrHead;
    Node *next;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *ptrHead = NULL;
}

void deleteFirstNode(Node **ptrHead)
{
    Node *head = *ptrHead;
    Node *deleteMe;

    if(head == NULL)
        return;
    
    deleteMe = head;
    head = head->next;
    *ptrHead = head;

    if (head != NULL)
        head->prev = NULL;

    free(deleteMe);
}


/* Delete a node given its pointer */
void deleteNodePtr(Node **ptrHead, Node *ptrDel)
{
    Node *curr = *ptrHead;
    Node *next;

    if (ptrDel == NULL)
        return;

    if (curr == ptrDel) /*first node*/
    {
        *ptrHead = curr->next;
        curr->next->prev = NULL;
        free(curr);
        return;
    }
    while (curr != NULL)
    {
        next = curr->next;
        if (next == ptrDel) /*node to be deleated*/
        {
            curr->next = next->next;
            next->next->prev = curr;
            free(next);
            return;
        }
        curr = next;
    }
}

void deleteNode(Node **ptrHead, int value)
{
    Node *curr = *ptrHead;
    Node *next;
    Node *deleteMe;
    if(curr == NULL)
        return;

    if (curr->value == value) /*first node*/
    {
        deleteMe = curr;
        curr = curr->next;
        if(curr)
            curr->prev = NULL;
        
        *ptrHead = curr;
        free(deleteMe);
        return;
    }
    next = curr->next;
    while (next != NULL)
    {
        if (next->value == value)
        {
            curr->next = next->next;
            if (curr->next)
                curr->next->prev = curr;
            free(next);
            return;
        }
        curr = next;
        next = next->next;
    }
}

void removeDuplicates(Node *head)
{
    Node *deleteMe;
    while (head)
    {
        if ((head->next) && head->value == head->next->value)
        {
            deleteMe = head->next;
            head->next = deleteMe->next;
            if(head->next)
                head->next->prev = head;
            free(deleteMe);
        }
        else
        {
            head = head->next;
        }
    }
}

Node *copyListReversed(Node *head)
{
    Node *temp = NULL;
    Node *head2 = NULL;
    Node *curr = head;
    while (curr)
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->value = curr->value;
        temp->next = head2;
        temp->prev = NULL;
        if (head2)
            head2->prev = temp;
        head2 = temp;
        curr = curr->next;
    }
    return head2;
}

Node *copyList(Node *head)
{
    Node *head2 = NULL;
    Node *tail2 = NULL;
    Node *tempNode = NULL;

    if (!head)
        return NULL;

    head2 = (Node *)malloc(sizeof(Node));
    tail2 = head2;
    head2->value = head->value;
    head2->next = NULL;
    head2->prev = NULL;
    head = head->next;

    while (head)
    {
        tempNode = (Node *)malloc(sizeof(Node));
        tempNode->value = head->value;
        tempNode->next = NULL;
        tail2->next = tempNode;
        tempNode->prev = tail2;
        tail2 = tail2->next;
        head = head->next;
    }

    return head2;
}

int compareList(Node *head1, Node *head2)
{
    if (head1 == NULL && head2 == NULL)
        return 1;
    else if ((head1 == NULL) || (head2 == NULL) || (head1->value != head2->value))
        return 0;
    else
        return compareList(head1->next, head2->next);
}

int compareList2(Node *head1, Node *head2)
{
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->value != head2->value)
            return 0;
        head1 = head1->next;
        head2 = head2->next;
    }
    if (head1 == head2)
        return 1;
    else
        return 0;
}

int main()
{
    Node *head = NULL;
    Node **ptrHead = &head;

    sortedInsert(ptrHead, 1);
    sortedInsert(ptrHead, 7);
    sortedInsert(ptrHead, 3);
    sortedInsert(ptrHead, 4);
    sortedInsert(ptrHead, 6);
    sortedInsert(ptrHead, 5);
    sortedInsert(ptrHead, 2);
    sortedInsert(ptrHead, 1);
    sortedInsert(ptrHead, 7);
    sortedInsert(ptrHead, 3);
    sortedInsert(ptrHead, 4);
    sortedInsert(ptrHead, 6);
    sortedInsert(ptrHead, 5);
    sortedInsert(ptrHead, 2);
    printList(*ptrHead);
    reverseList(ptrHead);
    printList(*ptrHead);
    removeDuplicates(*ptrHead);
    printList(*ptrHead);
    
    Node *head3 = copyList(*ptrHead);
    printList(head3);
    printf("comparision result %d ", compareList2(head, head3));
    Node *head4 = copyListReversed(*ptrHead);
    printList(head4);
    return 0;
}