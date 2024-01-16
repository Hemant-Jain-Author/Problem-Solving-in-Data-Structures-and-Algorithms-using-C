
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

Node* createNode(int value, Node* next, Node* prev) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = next;
    node->prev = prev;
    return node;
}

typedef struct DLL {
    Node *head;
    Node *tail;
} DLL;

DLL *createDLL() {
    DLL *list = (DLL*)malloc(sizeof(DLL));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insertAtHead(DLL *list, int value) {
    Node *temp = createNode(value, NULL, NULL);
    Node *head = list->head;
    if (!head) {
        list->head = temp;
        list->tail = temp;
    } else {
        temp->next = head;
        head->prev = temp;
        list->head = temp;
    }
}

void sortedInsert(DLL *list, int value) {
    Node *temp = createNode(value, NULL, NULL);    
    Node *curr = list->head;
    if (!curr) /*first element*/
    {
        list->head = temp;
        return;
    }

    if (curr->value >= value) /*at the begining*/
    {
        temp->next = curr;
        curr->prev = temp;
        list->head = temp;
        return;
    }

    while (curr->next && curr->next->value < value) /*traversal*/
    {
        curr = curr->next;
    }

    if (!curr->next) /*at the end*/
    {
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
}

/* Print A singly linked list */
void printList(DLL *list) {
    Node *head = list->head;
    while (head != NULL) {
        printf("%d  ", head->value);
        head = head->next;
    }
    printf("\n");
}

void printReverseListUtil(Node *head) {
    if (!head)
        return;

    printReverseListUtil(head->next);
    printf("%d ", head->value);
}

void printReverseList(DLL *list) {
    Node *head = list->head;
    printReverseListUtil(head);
}

/* Reverse a doubly linked List iteratively */
void reverseList(DLL *list) {
    Node *curr = list->head;
    list->tail = list->head;
    Node *tempNode;

    while (curr) {
        tempNode = curr->next;
        curr->next = curr->prev;
        curr->prev = tempNode;

        if (!curr->prev) {
            list->head = curr;
            return;
        }
        curr = curr->prev;
    }
    return;
}

void deleteList(DLL *list) {
    Node *curr = list->head;
    Node *next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void deleteFirstNode(DLL *list) {
    if(list->head == NULL)
        return;
    
    Node *deleteMe = list->head;
    list->head = list->head->next;
    if(list->head != NULL)
        list->head->prev = NULL;
    else
        list->tail = NULL;

    free(deleteMe);
}

void deleteNode(DLL *list, int value) {
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

    while (curr->next != NULL) {
        if (curr->next->value == value) {
            deleteMe = curr->next;
            curr->next = curr->next->next;
            if (curr->next)
                curr->next->prev = curr;
            else
                list->tail = curr;
            free(deleteMe);
            return;
        }
        curr = next;
        next = next->next;
    }
}

void removeDuplicates(DLL *list) {
    Node *curr = list->head;
    Node *deleteMe;
    while (curr) {
        if ((curr->next) && curr->value == curr->next->value) {
            deleteMe = curr->next;
            curr->next = deleteMe->next;
            if(curr->next)
                curr->next->prev = curr;
            else
                list->tail = curr; 
            free(deleteMe);
        } else {
            curr = curr->next;
        }
    }
}

DLL *copyListReversed(DLL *list) {
    DLL *list2 = createDLL();
    Node *head = list->head;
    while (head) {
        insertAtHead(list2, head->value);
        head = head->next;
    }
    return list2;
}


void insertAtTail(DLL *list, int value) {
    Node *temp = createNode(value, NULL, NULL);
    Node *tail = list->tail;
    if (!tail) {
        list->head = temp;
        list->tail = temp;
    } else {
        temp->prev = list->tail;
        list->tail->next = temp;
        list->tail = temp;
    }
}

DLL *copyList(DLL *list) {
    DLL *list2 = createDLL();
    Node *head = list->head;
    while (head) {
        insertAtTail(list2, head->value);
        head = head->next;
    }
    return list2;
}
/*
DLL *copyListReversed(DLL *list) {
    DLL *list2 = createDLL();
    Node *head = list->head;
    if (!head)
        return list2;

    Node *head2 = createNode(head->value, NULL, NULL); 
    Node *tail2 = head2;
    Node *temp = NULL;
    head = head->next;

    while (head) {
        temp = createNode(head->value, NULL, NULL);
        temp->next = head2;
        head2->prev = temp;
        head2 = temp;
        head = head->next;
    }
    list2->head = head2;
    list2->tail = tail2;
    return list2;
}

DLL *copyList(DLL *list) {
    Node *head2 = NULL;
    Node *tail2 = NULL;
    Node *tempNode = NULL;
    Node *head = list->head;
    DLL *list2 = createDLL();

    if (!head)
        return list2;

    head2 = createNode(head->value, NULL, NULL); 
    tail2 = head2;
    head = head->next;

    while (head) {
        tempNode = createNode(head->value, NULL, NULL); 
        tail2->next = tempNode;
        tempNode->prev = tail2;
        tail2 = tempNode;
        head = head->next;
    }
 
    list2->head = head2;
    list2->tail = tail2;
    return list2;
}
*/
int compareListUtil(Node *head1, Node *head2) {
    if (head1 == NULL && head2 == NULL)
        return 1;
    else if ((head1 == NULL) || (head2 == NULL) || (head1->value != head2->value))
        return 0;
    else
        return compareListUtil(head1->next, head2->next);
}

int compareList(DLL* list1, DLL* list2) {
    return compareListUtil(list1->head, list2->head);
}

int compareList2(DLL* list1, DLL* list2) {
    Node *head1 = list1->head;
    Node *head2 = list2->head;
    while (head1 != NULL && head2 != NULL) {
        if (head1->value != head2->value)
            return 0;
        head1 = head1->next;
        head2 = head2->next;
    }
    if (head1 == NULL && head2 == NULL)
        return 1;
    return 0;
}

int main1() {
    DLL* list = createDLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    deleteFirstNode(list);
    printList(list);
    return 0;
}
/*
3  2  1  
2  1  
*/

int main2() {
    DLL* list = createDLL();
    sortedInsert(list, 1);
    sortedInsert(list, 3);
    sortedInsert(list, 2);
    sortedInsert(list, 4);
    printList(list);
    return 0;
}
/*
1  2  3  4  
*/
int main3() {
    DLL* list = createDLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    deleteNode(list, 2);
    printList(list);
    return 0;
}
/*
3  2  1  
3  1  
*/

int main4() {
    DLL* list = createDLL();
    sortedInsert(list, 1);
    sortedInsert(list, 2);
    sortedInsert(list, 3);
    sortedInsert(list, 1);
    sortedInsert(list, 2);
    sortedInsert(list, 3);
    printList(list);
    removeDuplicates(list);
    printList(list);
    return 0;
}
/*
1  1  2  2  3  3  
1  2  3 
*/

int main5() {
    DLL* list = createDLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    reverseList(list);
    printList(list);
	return 0;
}
/*
3  2  1  
1  2  3  
*/

int main6() {
    DLL* list = createDLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    DLL* list2 = copyListReversed(list);
    printList(list2);
    DLL* list3 = copyList(list);
    printList(list3);
	return 0;
}
/*
3  2  1  
1  2  3 
3  2  1 
*/

int main() {
    main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    return 0;
}