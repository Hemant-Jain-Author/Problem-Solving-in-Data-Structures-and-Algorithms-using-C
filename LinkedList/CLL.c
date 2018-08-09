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

typedef struct Node
{
    int value;
    struct Node *next;
} CLNode;

int insertNode(CLNode **ptrHead, CLNode **ptrTail, int value)
{
    CLNode *temp = (CLNode *)malloc(sizeof(CLNode));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    CLNode *head = *ptrHead;
    CLNode *tail = *ptrTail;

    if (!head)
    {
        temp->value = value;
        temp->next = temp;
        *ptrTail = temp;
        *ptrHead = temp;
    }
    else
    {
        temp->value = value;
        temp->next = head;
        tail->next = temp;
        *ptrHead = temp;
    }
    return 1;
}

void printList(CLNode *head)
{
    CLNode *currNode = head;

    if (currNode != NULL)
    {
        printf(" %d  ", currNode->value);
        currNode = currNode->next;
    }

    while (currNode != head)
    {
        printf(" %d  ", currNode->value);
        currNode = currNode->next;
    }
}

void deleteList(CLNode** ptrHead, CLNode **ptrTail)
{
    CLNode *head = *ptrHead;
    CLNode *currNode = *ptrHead;
    CLNode *nextNode;

    if (currNode != NULL)
    {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }

    while (currNode != head)
    {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    *ptrHead = NULL;
    *ptrTail = NULL;
}

/* Delete a node given its pointer */
void deleteNodePtr(CLNode **ptrHead, CLNode **ptrTail, CLNode *ptrDel)
{
    CLNode *head = *ptrHead;
    CLNode *tail = *ptrTail;
    CLNode *curr = head;
    CLNode *prev = NULL;
    CLNode *deleteMe;

    if (ptrDel == NULL || !head)
        return;

    if (curr == ptrDel) /* one element and first element case */
    {
        if (curr->next == curr)
        {
            *ptrHead = NULL;
            *ptrTail = NULL;
            free(curr);
            return;
        }
        else
        {
            deleteMe = curr;
            curr = curr->next;
            *ptrHead = curr;
            tail->next = curr;
            free(deleteMe);
            return;
        }
    }
    prev = curr;
    curr = curr->next;
    while (curr != head)
    {
        if (curr == ptrDel)
        {
            if (curr == tail) /* tail change case */
                *ptrTail = prev;
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

/* REMOVE DUPLICATE */
void removeDuplicate(CLNode *head)
{
    CLNode *deleteMe;
    CLNode *curr = head;

    while (curr && curr->next != head)
    {
        if (curr->value == curr->next->value)
        {
            deleteMe = curr->next;
            curr->next = deleteMe->next;
            free(deleteMe);
        }
        else
        {
            curr = curr->next;
        }
    }
}

/* COPY LIST */
CLNode* copyListReversed(CLNode *head)
{
    CLNode *head2 = NULL;
    CLNode *tempNode = NULL;
    CLNode *curr = head;

    if (curr)
    {
        head2 = (CLNode *)malloc(sizeof(CLNode));
        head2->value = curr->value;
        head2->next = head2;
        curr = curr->next;
    }

    while (head != curr)
    {
        tempNode = (CLNode *)malloc(sizeof(CLNode));
        tempNode->value = curr->value;
        tempNode->next = head2;
        head2 = tempNode;
        curr = curr->next;
    }
    return head2;
}

CLNode* copyList(CLNode *head)
{
    CLNode *curr = head;
    CLNode *head2 = NULL;
    CLNode *tail2 = NULL;
    CLNode *tempNode = NULL;

    if (curr)
    {
        head2 = (CLNode *)malloc(sizeof(CLNode));
        head2->value = curr->value;
        head2->next = head2;
        tail2 = head2;
        curr = curr->next;
    }

    while (curr != head)
    {
        tempNode = (CLNode *)malloc(sizeof(CLNode));
        tempNode->value = curr->value;
        tempNode->next = head2;
        tail2->next = tempNode;
        tail2 = tempNode;
        curr = curr->next;
    }
    return head2;
}

/* COMPARE LIST */
int compareList(CLNode *head1, CLNode *head2)
{
    if (head1 == NULL && head2 == NULL)
        return 1;

    if (head1 == NULL || head2 == NULL)
        return 0;

    CLNode *curr1 = head1;
    CLNode *curr2 = head2;

    if (curr1->value != curr2->value)
        return 0;

    curr1 = curr1->next;
    curr2 = curr2->next;

    while (curr1 != head1 && curr2 != head2)
    {
        if (curr1->value != curr2->value)
            return 0;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    if (curr1 == head1 && curr2 == head2)
        return 1;
    else
        return 0;
}

int main()
{
    CLNode *head;
    CLNode *tail;
    return 0;
}
