
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    int value;
    struct listNode *next;
    struct listNode *prev;
} Node;

typedef struct DLL_t
{
    Node *head;
    Node *tail;
} DLL;

void InitDLL(DCLL *list){
    list->head = NULL;
    list->tail = NULL;
}

int insertNode(DLL *list, int value)
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
        temp->next = NULL;
        temp->prev = NULL;
        list->head = temp;
        list->tail = temp;
    }
    else
    {
        temp->prev = NULL;
        temp->next = head;
        head->prev = temp;
        list->head = temp;
    }
    return 1;
}

int sortedInsert(DLL *list, int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }

    temp->value = value;
    Node *curr = list->head;

    if (!curr) /*first element*/
    {
        temp->next = NULL;
        temp->prev = NULL;
        list->head = temp;
        return 1;
    }
    if (curr->value <= value) /*at the begining*/
    {
        temp->next = curr;
        temp->prev = NULL;
        curr->prev = temp;
        list->head = temp;
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
        list->tail = temp;
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
void printList(DCLL *list)
{
    Node *head = list->head;
    while (head != NULL)
    {
        printf("%d  ", head->value);
        head = head->next;
    }
    printf("\n");
}

void printReverseListUtil(Node *head)
{
    if (!head)
        return;

    printReverseListUtil(head->next);
    printf("%d ", head->value);
}

void printReverseList(DCLL *list)
{
    Node *head = list->head;
    printReverseListUtil(head);
}

/* Reverse a doubly linked List iteratively */
void reverseList(DLL *list)
{
    Node *curr = list->head;
    list->tail = list->head;
    Node *tempNode;

    while (curr)
    {
        tempNode = curr->next;
        curr->next = curr->prev;
        curr->prev = tempNode;

        if (!curr->prev)
        {
            list->head = curr;
            return;
        }
        curr = curr->prev;
    }
    return;
}

/* Delete a singly linked list */
void deleteList(DLL *list)
{
    Node *curr = list->head;
    Node *next;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void deleteFirstNode(DLL *list)
{
    Node *head = list->head;
    if(head == NULL)
        return;
    
    Node *deleteMe = head;
    head = head->next;
    list->head = head;
    if(head == NULL)
        list->tail = NULL:

    if (head != NULL)
        head->prev = NULL;

    free(deleteMe);
}

void deleteNode(DLL *list, int value)
{
    Node *curr = list->head;
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
        else
            list->tail = NULL;
        
        list->head = curr;
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
            if(next == list->tail)
                list->tail = curr;
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
    DLL list;

    sortedInsert(&list, 1);
    sortedInsert(&list, 7);
    sortedInsert(&list, 3);
    sortedInsert(&list, 4);
    sortedInsert(&list, 6);
    sortedInsert(&list, 5);
    sortedInsert(&list, 2);
    sortedInsert(&list, 1);
    sortedInsert(&list, 7);
    sortedInsert(&list, 3);
    sortedInsert(&list, 4);
    sortedInsert(&list, 6);
    sortedInsert(&list, 5);
    sortedInsert(&list, 2);
    printList(&list);
    reverseList(&list);
    printList(&list);
    removeDuplicates(&list);
    printList(&list);
    
    Node *head3 = copyList(&list);
    printList(head3);
    printf("comparision result %d ", compareList2(head, head3));
    Node *head4 = copyListReversed(&list);
    printList(head4);
    return 0;
}