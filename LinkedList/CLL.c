
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = node;
    return node;
}


typedef struct CircularLL {
    Node *tail;
} CircularLL;

CircularLL* createCircularLL() {
    CircularLL *list = (CircularLL *)malloc(sizeof(CircularLL));
    list->tail = NULL;
    return list;
}

int insertAtStart(CircularLL* list, int value) {
    Node *temp = createNode(value);
    Node *tail = list->tail;
    if (!tail) 
    {
        list->tail = temp;
    } else {
        temp->next = tail->next;
        tail->next = temp;
    }
    return 1;
}

int insertAtEnd(CircularLL *list, int value) {
    Node *temp = createNode(value);
    Node *tail = list->tail;
    if (!tail) {
        list->tail = temp;
    } else {
        temp->next = tail->next;
        tail->next = temp;
        list->tail = temp;
    }
    return 1;
}

void printList(CircularLL *list) {
    Node* tail = list->tail;
    if (!tail)
        return;
    
    Node *curr = tail->next;
    while (curr != tail) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("%d \n", curr->value);
}

int searchList(CircularLL *list, int value) {
    Node* tail = list->tail;
    if (!tail)
        return 0;

    if (tail->value == value)
        return 1;

    Node *curr = tail->next;
    while (curr != tail) {
        if (curr->value == value)
            return 1;
        curr = curr->next;
    }
    return 0;
}

void deleteList(CircularLL *list) {
    Node *tail = list->tail;
    if (!tail)
        return;

    Node *curr = tail->next;
    free(tail);
    Node *next;
    
    while (curr != tail) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->tail = NULL;
}

int deleteNode(CircularLL *list, int value) {
    Node *tail = list->tail;
    if (!tail)
        return 0;

    Node *curr = tail;
    Node *prev = curr;
    curr = curr->next;
    while (curr != tail) {
        if (curr->value == value) {
            prev->next = curr->next;
            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->value == value) {
        prev->next = curr->next;
        free(curr);
        list->tail = prev;
        return 1;
    }
    return 0;
}

int deleteHeadNode(CircularLL *list) {
    Node *tail = list->tail;
    if (!tail)
        return 0;

    if (tail->next == tail) {
        free(tail);
        list->tail = NULL;
        return 1;
    }
    Node *deleteMe = tail->next;
    tail->next = deleteMe->next;
    free(deleteMe);
    return 1;
}

int main() {
    CircularLL* list = createCircularLL();
    insertAtStart(list, 1);
    insertAtStart(list, 2);
    insertAtStart(list, 3);
    insertAtStart(list, 4);
    insertAtStart(list, 5);
    insertAtEnd(list, 6);
    insertAtEnd(list, 7);
    printList(list);

    deleteNode(list, 4);
    printList(list);

    printf("Search list : %d\n", searchList(list, 3));
    printf("Search list : %d\n", searchList(list, 6));
    printf("Search list : %d\n", searchList(list, 4));

    deleteHeadNode(list);
    printList(list);

    deleteList(list);
    printList(list);
    return 0;
}