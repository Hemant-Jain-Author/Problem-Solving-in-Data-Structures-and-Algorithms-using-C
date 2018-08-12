// LinkedList.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} ListNode;

int insertNode(ListNode **ptrHead, int value)
{
    ListNode *tempNode = (ListNode *)malloc(sizeof(ListNode));
    if (!tempNode)
        return -1;
    tempNode->value = value;
    tempNode->next = *ptrHead;
    *ptrHead = tempNode;
    return 1;
}

int findLenght(ListNode *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}

ListNode *nthNodeFromBegening(ListNode *head, int index)
{
    int count = 0;
    while (head && count < index - 1)
    {
        count++;
        head = head->next;
    }

    if (head)
        return head;
    else
        return NULL;
}

ListNode *nthNodeFromEnd1(ListNode *head, int index)
{
    int size = findLenght(head);
    int startIndex;
    if (size && size < index)
    {
        printf("list does not have % elements", index);
        return NULL;
    }
    startIndex = size - index + 1;
    return nthNodeFromBegening(head, index);
}

ListNode *nthNodeFromEnd2(ListNode *head, int index)
{
    int count = 0;
    ListNode *temp = NULL;
    ListNode *curr = head;
    while (curr && count < index - 1)
    {
        count++;
        curr = curr->next;
    }

    if (!curr)
        return NULL;

    temp = head;

    while (curr)
    {
        temp = temp->next;
        curr = curr->next;
    }
    return temp;
}

ListNode *nthNodeFromEnd3(ListNode *head, int index)
{
    static int count = 0;
    ListNode *retval;

    if (!head)
        return NULL;

    retval = nthNodeFromEnd3(head->next, index);
    if (retval)
        return retval;

    count++;
    if (count == index)
        return head;
    else
        return NULL;
}

void printList(ListNode *head)
{
    printf("PrintLIst: ");
    while (head)
    {
        printf(" %d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int sortedInsert(ListNode **ptrHead, int value)
{
    ListNode *head = *ptrHead;
    ListNode *tempNode = (ListNode *)malloc(sizeof(ListNode));
    printf("Insert element %d \n", value);
    if (!tempNode)
        return -1;
    tempNode->value = value;
    tempNode->next = NULL;
    if (head == NULL || head->value > value)
    {
        tempNode->next = *ptrHead;
        *ptrHead = tempNode;
        return 1;
    }
    while (head->next != NULL &&
           head->next->value < value)
    {
        head = head->next;
    }
    tempNode->next = head->next;
    head->next = tempNode;
    return 1;
}
int insertAtEnd(ListNode **ptrHead, int value)
{
    ListNode *head = *ptrHead;
    ListNode *tempNode = (ListNode *)malloc(sizeof(ListNode));
    if (!tempNode)
        return -1;
    tempNode->value = value;
    tempNode->next = NULL;
    if (head == NULL)
    {
        tempNode->next = *ptrHead;
        *ptrHead = tempNode;
        return 1;
    }
    while (head->next != NULL)
    {
        head = head->next;
    }
    tempNode->next = head->next;
    head->next = tempNode;
    return 1;
}
int insertNodeEnd2(ListNode **ptrHead, ListNode **ptrTail, int value)
{
    printf("Insert Node:: %d", value);
    ListNode *tempPtr = (ListNode *)malloc(sizeof(ListNode));
    if (!tempPtr)
        return -1;
    tempPtr->value = value;
    tempPtr->next = NULL;
    if (*ptrHead == NULL)
    {
        *ptrTail = *ptrHead = tempPtr;
    }
    else
    {
        ListNode *tail = *ptrTail;
        tail->next = tempPtr;
        *ptrTail = tempPtr;
    }
    return 1;
}
int searchList(ListNode *head, int value)
{
    while (head)
    {
        if (head->value == value)
        {
            printf("\nThe value is found\n");
            return 1;
        }
        head = head->next;
    }
    printf("\nThe value not found\n");
    return 0;
}
void deleteNode(ListNode **ptrHead, int delValue)
{
    printf("\nDelete Node \n");
    ListNode *currNode = *ptrHead;
    ListNode *nextNode;

    if (currNode->value == delValue) /*first node */
    {
        *ptrHead = currNode->next;
        free(currNode);
        return;
    }

    while (currNode != NULL)
    {
        nextNode = currNode->next;
        if (nextNode && nextNode->value == delValue)
        {
            currNode->next = nextNode->next;
            free(nextNode);
            return;
        }
        else
        {
            currNode = nextNode;
        }
    }
}

void deleteFirstNodes(ListNode **ptrHead, int delValue)
{
    ListNode *currNode = *ptrHead;
    ListNode *nextNode;

    if (currNode == NULL)
        return;

    nextNode = currNode->next;
    free(currNode);

    *ptrHead = nextNode;
}

void deleteNodes(ListNode **ptrHead, int delValue)
{
    ListNode *currNode = *ptrHead;
    ListNode *nextNode;
    ListNode *delNode;

    while (currNode != NULL && currNode->value == delValue) /*first node */
    {
        *ptrHead = currNode->next;
        delNode = currNode;
        currNode = currNode->next;
        free(delNode);
    }

    while (currNode != NULL)
    {
        nextNode = currNode->next;
        if (nextNode && nextNode->value == delValue)
        {
            currNode->next = nextNode->next;
            free(nextNode);
        }
        else
        {
            currNode = nextNode;
        }
    }
}

void deleteNodePtr(ListNode **ptrHead, ListNode *ptrDel)
{
    ListNode *currNode = *ptrHead;
    ListNode *nextNode;

    if (ptrDel == NULL)
        return;

    if (currNode == ptrDel) /*first node*/
    {
        *ptrHead = currNode->next;
        free(currNode);
        return;
    }
    while (currNode != NULL)
    {
        nextNode = currNode->next;
        if (nextNode == ptrDel) /*node to be deleated*/
        {
            currNode->next = nextNode->next;
            free(nextNode);
            return;
        }
        currNode = nextNode;
    }
}

void deleteList(ListNode **ptrHead)
{
    ListNode *deleteMe = *ptrHead;
    ListNode *nextNode;
    while (deleteMe != NULL)
    {
        nextNode = deleteMe->next;
        free(deleteMe);
        deleteMe = nextNode;
    }
    *ptrHead = NULL;
}
void reverseList(ListNode **ptrHead)
{
    ListNode *tempNode = *ptrHead;
    ListNode *prevNode;
    ListNode *nextNode;
    if (!tempNode)
    {
        return;
    }
    if (!tempNode->next)
    {
        return;
    }
    prevNode = tempNode;
    tempNode = tempNode->next;
    prevNode->next = NULL;
    while (tempNode)
    {
        nextNode = tempNode->next;
        tempNode->next = prevNode;
        prevNode = tempNode;
        tempNode = nextNode;
    }
    *ptrHead = prevNode;
}
ListNode *reverseRecurse2(ListNode *currentNode, ListNode *nextNode)
{
    ListNode *ret;
    if (!currentNode)
        return NULL;

    if (!currentNode->next)
    {
        currentNode->next = nextNode;
        return currentNode;
    }

    ret = reverseRecurse2(currentNode->next, currentNode);
    currentNode->next = nextNode;
    return ret;
}

void reverseRecurse(ListNode **ptrHead)
{
    *ptrHead = ReverseRecurse2(*ptrHead, NULL);
}

void removeDuplicate(ListNode *head)
{
    ListNode *deleteMe;
    while (head)
    {
        if ((head->next) && head->value == head->next->value)
        {
            deleteMe = head->next;
            head->next = deleteMe->next;
            free(deleteMe);
        }
        else
        {
            head = head->next;
        }
    }
}

void copyListReversed(ListNode *head, ListNode **ptrHead2)
{
    ListNode *tempNode = NULL;
    ListNode *tempNode2 = NULL;
    while (head)
    {
        tempNode2 = (ListNode *)malloc(sizeof(ListNode));
        tempNode2->value = head->value;
        tempNode2->next = tempNode;
        tempNode = tempNode2;
        head = head->next;
    }
    *ptrHead2 = tempNode;
}

void copyList(ListNode *head, ListNode **ptrHead2)
{
    ListNode *headNode = NULL;
    ListNode *tailNode = NULL;
    ListNode *tempNode = NULL;

    if (head == NULL)
        return;

    headNode = (ListNode *)malloc(sizeof(ListNode));
    tailNode = headNode;
    headNode->value = head->value;
    headNode->next = NULL;
    head = head->next;

    while (head)
    {
        tempNode = (ListNode *)malloc(sizeof(ListNode));
        tempNode->value = head->value;
        tempNode->next = NULL;
        tailNode->next = tempNode;
        tailNode = tailNode->next;
        head = head->next;
    }
    *ptrHead2 = headNode;
}

int loopDetect(ListNode *head)
{
    printf("loop detect");
    ListNode *slowPtr;
    ListNode *fastPtr;
    slowPtr = fastPtr = head;

    while (fastPtr->next && fastPtr->next->next)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        if (slowPtr == fastPtr)
        {
            printf("\nloop found \n");
            return 1;
        }
    }
    printf("\nloop not found \n");
    return 0;
}

int loopTypeDetect(ListNode *const head)
{
    ListNode *slowPtr;
    ListNode *fastPtr;

    slowPtr = fastPtr = head;
    while (fastPtr->next && fastPtr->next->next)
    {

        if (head == fastPtr->next || head == fastPtr->next->next)
        {
            printf("circular list detected\n");
            return 2;
        }

        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;

        if (slowPtr == fastPtr)
        {
            printf("loop detected\n");
            return 1;
        }
    }
    printf("No loop detected\n");
    return 0;
}

void makeLoop(ListNode *head)
{
    ListNode *temp = head;
    while (temp)
    {
        if (temp->next == NULL)
        {
            temp->next = head;
            return;
        }
        temp = temp->next;
    }
}

void removeLoop(ListNode **ptrHead)
{
    int loopLength;
    ListNode *slowPtr, *fastPtr, *head;
    slowPtr = fastPtr = head = *ptrHead;
    ListNode *loopNode = NULL;
    while (fastPtr->next && fastPtr->next->next)
    {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;

        if (fastPtr == slowPtr || fastPtr->next == slowPtr)
        {
            loopNode = slowPtr;
            break;
        }
    }

    if (loopNode)
    {
        ListNode *temp = loopNode->next;
        loopLength = 1;
        while (temp != loopNode)
        {
            loopLength++;
            temp = temp->next;
        }
        temp = head;
        ListNode *breakNode = head;

        for (int i = 1; i < loopLength; i++)
        {
            breakNode = breakNode->next;
        }

        while (temp != breakNode->next)
        {
            temp = temp->next;
            breakNode = breakNode->next;
        }
        breakNode->next = NULL;
    }
}

ListNode *findIntersecton(ListNode *head, ListNode *head2)
{
    int l1 = 0;
    int l2 = 0;
    ListNode *tempHead = head;
    ListNode *tempHead2 = head2;

    while (tempHead)
    {
        l1++;
        tempHead = tempHead->next;
    }
    while (tempHead2)
    {
        l2++;
        tempHead2 = tempHead2->next;
    }

    int diff;
    if (l1 < 12)
    {
        ListNode *temp = head;
        head = head2;
        head2 = temp;
        diff = l2 - l1;
    }
    else
    {
        diff = l1 - l2;
    }

    for (; diff > 0; diff--)
    {
        head = head->next;
    }
    while (head != head2)
    {
        head = head->next;
        head2 = head2->next;
    }
    return head;
}

int main()
{

    int arr[5] = {1, 2, 3, 4, 5};
    ListNode *head = NULL;
    int i;

    for (i = 0; i < 5; i++)
    {
        InsertNode(&head, arr[i]);
    }
    ListNode *head2 = head;
    for (i = 0; i < 3; i++)
    {
        InsertNode(&head, 10);
    }
    for (i = 0; i < 5; i++)
    {
        InsertNode(&head2, 20);
    }

    PrintList(head);
    PrintList(head2);

    ListNode *intersection = findIntersecton(head, head2);
    printf("\nvalue at the intersection is %d \n", intersection->value);

    for (i = 0; i < 5; i++)
    {
        InsertNode(&head, arr[i]);
    }

    PrintList(head);

    DeleteList(&head);

    PrintList(head);

    int arr2[5] = {1, 5, 3, 2, 4};

    head = NULL;

    for (i = 0; i < 5; i++)
    {
        SortedInsert(&head, arr2[i]);
    }
    PrintList(head);

    SearchList(head, 6);
    SearchList(head, 5);

    DeleteNode(&head, 5);
    PrintList(head);

    DeleteNode(&head, 3);
    PrintList(head);

    for (i = 0; i < 5; i++)
    {
        SortedInsert(&head, arr2[i]);
    }
    PrintList(head);

    RemoveDuplicate(head);
    PrintList(head);

    ReverseList(&head);
    PrintList(head);

    reverseRecurse(&head);
    PrintList(head);

    DeleteNode(&head, 1);
    PrintList(head);

    DeleteNode(&head, 5);
    PrintList(head);

    DeleteNode(&head, 3);
    PrintList(head);

    for (i = 0; i < 5; i++)
    {
        InsertNode(&head, arr[i]);
        InsertNode(&head, arr[i]);
        InsertNode(&head, arr[i]);
    }
    PrintList(head);

    CopyList(head, &head2);
    PrintList(head2);

    ListNode *head3;
    CopyListReversed(head, &head3);
    PrintList(head3);

    DeleteNodes(&head, 5);
    PrintList(head);

    DeleteNodes(&head, 1);
    PrintList(head);

    DeleteNodes(&head, 4);
    PrintList(head);

    LoopDetect(head);
    LoopTypeDetect(head);

    MakeLoop(head);
    for (i = 0; i < 5; i++)
    {
        InsertNode(&head, arr[i]);
    }
    LoopDetect(head);
    LoopTypeDetect(head);

    RemoveLoop(&head);
    PrintList(head);

    return 0;
}