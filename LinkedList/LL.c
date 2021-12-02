#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

Node* createNode(int value, Node* next) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

typedef struct LinkedList
{
    Node *head;
} LinkedList;

LinkedList* createLinkedList(){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void insertNode(LinkedList* list, int value) {
    list->head = createNode(value, list->head);
}

int findLength(LinkedList* list) {
    Node *head = list->head;
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

Node* nthNodeFromBeginning(LinkedList* list, int index) {
    Node *head = list->head;
    int count = 0;
    while (head && count < index - 1) {
        count++;
        head = head->next;
    }

    if (head)
        return head;
    else
        return NULL;
}

Node *nthNodeFromEnd(LinkedList* list, int index) {
    Node *head = list->head;
    int size = findLength(list);
    if (size && size < index) {
        printf("list does not have %d elements", index);
        return NULL;
    }
    int startIndex = size - index + 1;
    return nthNodeFromBeginning(list, startIndex);
}

Node *nthNodeFromEnd2(LinkedList* list, int index) {
    int count = 0;
    Node *head = list->head;
    Node *first = head;
    while (first && count < index ) {
        count++;
        first = first->next;
    }
    if (count != index)
        return NULL;

    while (first) {
        head = head->next;
        first = first->next;
    }
    return head;
}

Node *nthNodeFromEndUtil(Node* head, int index) {
    static int count = 0;
    if (!head)
        return NULL;

    Node *retval = nthNodeFromEndUtil(head->next, index);
    if (retval)
        return retval;

    count++;
    if (count == index)
        return head;
    else
        return NULL;
}

Node *nthNodeFromEnd3(LinkedList* list, int index) {
    return nthNodeFromEndUtil(list->head, index);
}

void printList(LinkedList* list) {
    Node* head = list->head;
    printf("[ ");
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("]\n");
}

void sortedInsert(LinkedList* list, int value) {
    Node *head = list->head;
    Node *tempNode = createNode(value, NULL); 
    
    if (head == NULL || head->value > value) {
        tempNode->next = head;
        list->head = tempNode;
        return;
    }

    while (head->next != NULL &&
           head->next->value < value) {
        head = head->next;
    }

    tempNode->next = head->next;
    head->next = tempNode;
}

void insertAtEnd(LinkedList* list, int value) {
    Node *head = list->head;
    Node *tempNode = createNode(value, NULL);

    if (head == NULL) {
        list->head = tempNode;
        return;
    }

    while (head->next != NULL) {
        head = head->next;
    }
    head->next = tempNode;
}

int searchList(LinkedList* list, int value) {
    Node *head = list->head;
    while (head) {
        if (head->value == value)
            return 1;

        head = head->next;
    }
    return 0;
}

void deleteFirstNodes(LinkedList* list) {
    Node *head = list->head;
    if (head == NULL)
        return;

    Node *next = head->next;
    free(head);
    list->head = next;
}

void deleteNode(LinkedList* list, int delValue) {
    Node *head = list->head;
    if(head == NULL)
        return;

    if (head->value == delValue) /*first node */
    {
        list->head = head->next;
        free(head);
        return;
    }

    Node *nextNode;
    while (head != NULL) {
        nextNode = head->next;
        if (nextNode && nextNode->value == delValue) {
            head->next = nextNode->next;
            free(nextNode);
            return;
        }
        head = nextNode;
    }
}

void deleteNodes(LinkedList* list, int delValue) {
    Node *curr = list->head;
    Node *delNode;
    while (curr != NULL && curr->value == delValue) /*first node */
    {
        delNode = curr;
        curr = curr->next;
        free(delNode);
        list->head = curr;
    }

    Node *nextNode;
    while (curr != NULL) {
        nextNode = curr->next;
        if (nextNode && nextNode->value == delValue) {
            curr->next = nextNode->next;
            free(nextNode);
            continue;
        }
        curr = nextNode;
    }
}

void deleteListPtr(LinkedList* list, Node *ptrDel) {
    Node *curr = list->head;
    Node *nextNode;

    if (ptrDel == NULL)
        return;

    if (curr == ptrDel) /*first node*/
    {
        list->head = curr->next;
        free(curr);
        return;
    }
    while (curr != NULL) {
        nextNode = curr->next;
        if (nextNode == ptrDel) /*node to be deleted*/
        {
            curr->next = nextNode->next;
            free(nextNode);
            return;
        }
        curr = nextNode;
    }
}

void deleteList(LinkedList* list) {
    Node *deleteMe = list->head;
    Node *nextNode;
    while (deleteMe != NULL) {
        nextNode = deleteMe->next;
        free(deleteMe);
        deleteMe = nextNode;
    }
    list->head = NULL;
}

void reverseList(LinkedList* list) {
    Node *curr = list->head;
    Node *prev = NULL;
    Node *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;

}

Node *reverseRecurseUtil(Node *currentNode, Node *nextNode) {
    if (!currentNode)
        return NULL;

    if (!currentNode->next) {
        currentNode->next = nextNode;
        return currentNode;
    }

    Node *ret = reverseRecurseUtil(currentNode->next, currentNode);
    currentNode->next = nextNode;
    return ret;
}

void reverseRecurse(LinkedList* list) {
    list->head = reverseRecurseUtil(list->head, NULL);
}

void removeDuplicate(LinkedList* list) {
    Node *head = list->head;
    Node *deleteMe;
    while (head) {
        if ((head->next) && head->value == head->next->value) {
            deleteMe = head->next;
            head->next = deleteMe->next;
            free(deleteMe);
        } else {
            head = head->next;
        }
    }
}

LinkedList* copyListReversed(LinkedList* list) {
    LinkedList* list2 = createLinkedList();
    Node *head = list->head;
    Node *head2 = NULL;
    while (head) {
        head2 = createNode(head->value, head2); 
        head = head->next;
    }
    list2->head = head2;
    return list2;
}

LinkedList* copyList(LinkedList* list) {
    Node *head = list->head;
    LinkedList* list2 = createLinkedList();
    if (head == NULL)
        return list2;

    list2->head = createNode(head->value, NULL);
    Node *tailNode = list2->head;
    head = head->next;

    while (head) {
        tailNode->next = createNode(head->value, NULL);
        tailNode = tailNode->next;
        head = head->next;
    }
    return list2;
}

int compareListUtil(Node *head1, Node *head2) {
    if (head1 == NULL && head2 == NULL)
        return 1;
    else if ((head1 == NULL) || (head2 == NULL) || (head1->value != head2->value))
        return 0;
    else
        return compareListUtil(head1->next, head2->next);
}

int compareList(LinkedList* list1, LinkedList* list2) {
    return compareListUtil(list1->head, list2->head);
}

int compareList2(LinkedList* list1, LinkedList* list2) {
    Node *head1 = list1->head;
    Node *head2 = list2->head;
    while (head1 != NULL && head2 != NULL ) {
        if (head1->value != head2->value)
            return 0;
        
        head1 = head1->next;
        head2 = head2->next;
    }

    if (head1 == NULL && head2 == NULL)
        return 1;
    return 0;
}

int loopDetect(LinkedList* list) {
    Node *slowPtr = list->head;
    Node *fastPtr = list->head;

    while (fastPtr->next && fastPtr->next->next) {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        if (slowPtr == fastPtr) {
            printf("Loop found \n");
            return 1;
        }
    }
    printf("Loop not found \n");
    return 0;
}

int reverseListloopDetect(LinkedList* list) {
    Node *head2 = list->head;
    reverseList(list);
    if (list->head == head2) {
        reverseList(list);
        return 1;
    } else {
        reverseList(list);
        return 0;
    }
}

int loopTypeDetect(LinkedList* list) {
    Node *slowPtr = list->head;
    Node *fastPtr = list->head;

    while (fastPtr->next && fastPtr->next->next) {
        if (list->head == fastPtr->next || list->head == fastPtr->next->next) {
            printf("Circular list detected\n");
            return 2;
        }

        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;

        if (slowPtr == fastPtr) {
            printf("Loop detected\n");
            return 1;
        }
    }
    printf("No loop detected\n");
    return 0;
}

void makeLoop(LinkedList* list) {
    Node *temp = list->head;
    while (temp) {
        if (temp->next == NULL) {
            temp->next = list->head;
            return;
        }
        temp = temp->next;
    }
}

void removeLoop(LinkedList* list) {
    Node *slowPtr, *fastPtr, *head;
    slowPtr = fastPtr = head = list->head;
    Node *loopNode = NULL;
    while (fastPtr->next && fastPtr->next->next) {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;

        if (fastPtr == slowPtr || fastPtr->next == slowPtr) {
            loopNode = slowPtr;
            break;
        }
    }

    if (loopNode) {
        Node *temp = loopNode->next;
        int loopLength = 1;
        while (temp != loopNode) {
            loopLength++;
            temp = temp->next;
        }
        temp = head;
        Node *breakNode = head;

        for (int i = 1; i < loopLength; i++) {
            breakNode = breakNode->next;
        }

        while (temp != breakNode->next) {
            temp = temp->next;
            breakNode = breakNode->next;
        }
        breakNode->next = NULL;
    }
}

Node *findIntersecton(LinkedList* list1, LinkedList* list2) {
    int l1 = 0;
    Node *tempHead = list1->head;
    while (tempHead) {
        l1++;
        tempHead = tempHead->next;
    }

    int l2 = 0;
    Node *tempHead2 = list2->head;
    while (tempHead2) {
        l2++;
        tempHead2 = tempHead2->next;
    }

    Node* head = list1->head;
    Node* head2 = list2->head;

    int diff = l1 - l2;
    if (l1 < l2) {
        Node *temp = head;
        head = head2;
        head2 = temp;
        diff = l2 - l1;
    }
    
    while (diff > 0) {
        head = head->next;
        diff--;
    }

    while (head != head2) {
        head = head->next;
        head2 = head2->next;
    }

    return head;
}

Node *findIntersecton2(LinkedList* list1, LinkedList* list2) {
    Node* head1 = list1->head;
    Node* head2 = list2->head;

    while (head1 && head2) {
        head1 = head1->next;
        head2 = head2->next;
    }

    Node* diff;
    if(!head1){
        diff = head2;
        head1 = list1->head;
        head2 = list2->head;
        while(diff) {
            diff = diff->next;
            head2 = head2->next;
        }
    } else {
        diff = head1;
        head1 = list1->head;
        head2 = list2->head;
        while(diff){
            diff = diff->next;
            head1 = head1->next;
        }
    }

    while (head1 != head2) {
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1;
}

int main1() {
    LinkedList* list = createLinkedList();
    insertNode(list, 1);
    insertNode(list, 2);
    insertNode(list, 3);
    insertNode(list, 4);
    printList(list);
    printf("Length is : %d\n", findLength(list));
    printf("Search : %d\n", searchList(list, 3));
    printf("Search : %d\n", searchList(list, 5));
    
    deleteNodes(list, 3);
    printList(list);

    deleteNodes(list, 5);
    printList(list);
    return 0;
}
/*
[ 4  3  2  1 ]
Length is : 4
Search : 1
Search : 0
[ 4  2  1 ]
[ 4  2  1 ]
*/

int main2() {
    LinkedList* list = createLinkedList();
    int arr[] = {1, 5, 3, 2, 4};
    for (int i = 0; i < 5; i++) {
        sortedInsert(list, arr[i]);
    }
    printList(list);
    return 0;
}

/*
[ 1  2  3  4  5 ]
*/

int main3() {
    LinkedList* list = createLinkedList();
    insertNode(list, 1);
    insertNode(list, 2);
    insertNode(list, 3);
    insertNode(list, 4);
    printList(list);

    reverseList(list);
    printList(list);

    reverseRecurse(list);
    printList(list);


    LinkedList* list2 = copyList(list);
    printList(list2);

    LinkedList* list3 =  copyListReversed(list);
    printList(list3);

    printf("Compare list : %d\n", compareList(list, list2));
    printf("Compare list : %d\n", compareList(list, list3));
    printf("Compare list : %d\n", compareList2(list, list2));
    printf("Compare list : %d\n", compareList2(list, list3));
    return 0;
}

/*
[ 4  3  2  1 ]
[ 1  2  3  4 ]
[ 4  3  2  1 ]
[ 4  3  2  1 ]
[ 1  2  3  4 ]
Compare list : 1
Compare list : 0
Compare list : 1
Compare list : 0
*/

int main4() {
    LinkedList* list = createLinkedList();
    insertNode(list, 1);
    insertNode(list, 2);
    insertNode(list, 3);
    insertNode(list, 4);
    printList(list);
    printf("Nth Node : %d\n", nthNodeFromBeginning(list, 2)->value);
    printf("Nth Node : %d\n", nthNodeFromEnd(list, 2)->value);
    printf("Nth Node : %d\n", nthNodeFromEnd2(list, 2)->value);
    printf("Nth Node : %d\n", nthNodeFromEnd3(list, 2)->value);
    return 0;
}
/*
[ 4  3  2  1 ]
Nth Node : 3
Nth Node : 2
Nth Node : 2
Nth Node : 2
*/

int main5() {
    LinkedList* list = createLinkedList();
    int arr[] = {1, 5, 3, 2, 4};
    for (int i = 0; i < 5; i++)
        sortedInsert(list, arr[i]);

    for (int i = 0; i < 5; i++)
        sortedInsert(list, arr[i]);
    
    printList(list);
    removeDuplicate(list);
    printList(list);
    return 0;
}
/*
[ 1  1  2  2  3  3  4  4  5  5 ]
[ 1  2  3  4  5 ]
*/

int main6() {
    LinkedList* list = createLinkedList();
    insertNode(list, 1);
    insertNode(list, 2);
    insertNode(list, 3);
    insertNode(list, 4);
    printList(list);

    loopDetect(list);
    loopTypeDetect(list);

    makeLoop(list);
    loopDetect(list);
    loopTypeDetect(list);

    removeLoop(list);
    printList(list);
    return 0;
}
/*
[ 4  3  2  1 ]
Loop not found 
No loop detected
Loop found 
Circular list detected
[ 4  3  2  1 ]
*/

int main7() {
    LinkedList* list = createLinkedList();
    insertNode(list, 1);
    insertNode(list, 2);
    insertNode(list, 3);

    LinkedList* list2 = createLinkedList();
    list2->head = list->head;
    for (int i = 0; i < 5; i++)
        insertNode(list, 10);

    for (int i = 0; i < 3; i++)
        insertNode(list2, 20);

    printList(list);
    printList(list2);

    Node *intersection = findIntersecton(list, list2);
    printf("Value at the intersection is %d \n", intersection->value);

    Node *intersection2 = findIntersecton2(list, list2);
    printf("Value at the intersection is %d \n", intersection2->value);
    return 0;
}
/*
[ 10  10  10  10  10  3  2  1 ]
[ 20  20  20  3  2  1 ]
Value at the intersection is 3 
Value at the intersection is 3 
*/


void bubbleSort(LinkedList* list) {
    Node* head = list->head;
    if (head == NULL || head->next == NULL) {
        return;
    }
    Node* curr = NULL;
    Node* end = NULL;
    int temp;
    int flag = 1;
    while(flag) {
        flag = 0;
        curr = head;
        while (curr->next != end) {
            if(curr->value > curr->next->value) {
                flag = 1;
                temp = curr->value;
                curr->value = curr->next->value;
                curr->next->value = temp;
            }
            curr = curr->next;
        }
        end = curr;
    }
}

void selectionSort(LinkedList* list) {
    Node* head = list->head;
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    Node* curr = NULL;
    Node* end = NULL;
    Node* maxNode;
    int temp, max;
    
    while(head != end) {
        curr = head;
        max = curr->value;
        maxNode = curr;
        while (curr->next != end) {
            if(max < curr->next->value) {
                maxNode = curr->next;
                max = curr->next->value;
            }
            curr = curr->next;
        }
        end = curr;
        if(curr->value < max) {
            temp = curr->value;
            curr->value = max;
            maxNode->value = temp;
        }
    }
}

void insertionSort(LinkedList* list) {
    Node* head = list->head;
    if (head == NULL || head->next == NULL) {
        return;
    }

    Node* curr = NULL;
    Node* stop = NULL;

    stop = head->next;
    while(stop != NULL) {
        curr = head;
        while (curr != stop) {
            if(curr->value > stop->value) {
                int temp = curr->value;
                curr->value = stop->value;
                stop->value = temp;
            }
            curr = curr->next;
        }
        stop = stop->next;
    }
}


int main8() {
    LinkedList* list = createLinkedList();
    insertNode(list, 1);
    insertNode(list, 1);
    insertNode(list, 10);
    insertNode(list, 9);
    insertNode(list, 7);
    insertNode(list, 2);
    insertNode(list, 3);
    insertNode(list, 5);
    insertNode(list, 4);
    insertNode(list, 6);
    insertNode(list, 8);
    printList(list);    
    //bubbleSort(list);
    //selectionSort(list);
    insertionSort(list);
    printList(list);
    return 0; 
}

int main() {
    main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    main7();
    main8();
    return 0;
}