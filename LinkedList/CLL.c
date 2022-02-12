
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

int insertAtHead(CircularLL* list, int value) {
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

int insertAtTail(CircularLL *list, int value) {
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

CircularLL*  copyListReversed(CircularLL *list) {
    CircularLL* l2 = createCircularLL();
    Node* tail = list->tail;
    if (!tail)
        return l2;
    
    Node *curr = tail->next;
    while (curr != tail) {
        insertAtHead(l2, curr->value);
        curr = curr->next;
    }
    insertAtHead(l2, curr->value);
    return l2;
}

CircularLL*  copyList(CircularLL *list) {
    CircularLL* l2 = createCircularLL();
    Node* tail = list->tail;
    if (!tail)
        return l2;
    
    Node *curr = tail->next;
    while (curr != tail) {
        insertAtTail(l2, curr->value);
        curr = curr->next;
    }
    insertAtTail(l2, curr->value);
    return l2;
}

int main1() {
    CircularLL* list = createCircularLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    deleteHeadNode(list);
    printList(list);
    deleteList(list);
    printList(list);
    return 0;
}
/*
3 2 1 
2 1 */

int main2() {
    CircularLL* list = createCircularLL();
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
    CircularLL* list = createCircularLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    printf("Search list : %d\n", searchList(list, 3));
    printf("Search list : %d\n", searchList(list, 6)); 
    deleteNode(list, 2);  
    printList(list);
    return 0;
}
/*
3 2 1 
Search list : 1
Search list : 0
3 1 
*/

int main4() {
    CircularLL* list = createCircularLL();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    printList(list);
    CircularLL* list2 = copyList(list);
    printList(list2);
    CircularLL* list3 = copyListReversed(list);
    printList(list3);
    return 0;
}

int main() {
    /*
    main1();
    main2();
    main3();
    */
    main4();
    return 0;
}