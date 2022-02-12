#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = node->prev = node;
    return node;
}

typedef struct DCLL {
    Node *head;
} DCLL;

DCLL* createDCLL() {
    DCLL *list = (DCLL *)malloc(sizeof(DCLL));
    list->head = NULL;
    return list;
}

int insertAtHead(DCLL *list, int value) {
    Node *temp = createNode(value); 
    Node *head = list->head;
    if (!head) {
        list->head = temp;
    } else {
        temp->prev = head->prev;
        temp->prev->next = temp;

        temp->next = head;
        head->prev = temp;

        list->head = temp;
    }
    return 1;
}

int insertAtTail(DCLL *list, int value) {
    Node *temp = createNode(value); 
    Node *head = list->head;
    if (!head) {
        list->head = temp;
    } else {
        temp->prev = head->prev;
        temp->prev->next = temp;
        temp->next = head;
        head->prev = temp;
    }
    return 1;
}

int deleteFromHead(DCLL *list) {
    Node *head = list->head;
    if (!head) {
        printf("Empty List Error");
        return -99999;
    }

    int value = head->value;
    if (head->next == head) {
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

int deleteFromTail(DCLL *list) {
    Node *head = list->head;
    if (!head) {
        printf("Empty List Error");
        return -99999;
    }
    
    Node *tail = head->prev;
    int value = tail->value;

    if (tail->next == tail) {
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

int searchList(DCLL *list, int key) {
    Node *head = list->head;
    if (!head)
        return 0;

    Node *curr = head;

    do
    {
        if (curr->value == key) {
            return 1;
        }
        curr = curr->next;
    } while (curr != head);

    return 0;
}

void deleteList(DCLL *list) {
    Node *head = list->head;
    if (!head)
        return;

    Node *curr = head->next;
    Node *next;
    while (curr != head) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(head);
    list->head = NULL;
}

int printList(DCLL *list) {
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

int main1() {
    DCLL* list = createDCLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    deleteFromHead(list);
    printList(list);
    deleteList(list);
    printList(list);
    return 0;
}
/*
3 2 1 
2 1 
*/

int main2() {
    DCLL* list = createDCLL();
    insertAtTail(list, 1);
    insertAtTail(list, 2);
    insertAtTail(list, 3);
    printList(list);
    return 0;
}

/*
1 2 3
*/

int main3() {
    DCLL* list = createDCLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    printf("Search list : %d\n", searchList(list, 3));
    printf("Search list : %d\n", searchList(list, 6)); 
    deleteFromTail(list);  
    printList(list);
    return 0;
}
/*
3 2 1 
Search list : 1
Search list : 0
3 2 
*/


int main() {
    main1();
    main2();
    main3();
    return 0;
}