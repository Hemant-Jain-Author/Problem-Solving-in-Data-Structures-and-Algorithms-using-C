#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 517
#define TABLE_BITS 9

typedef struct SetNode {
    int key;
    struct SetNode *next;
} SetNode;

SetNode* createSetNode(int key, SetNode* next) {
    SetNode* node = (SetNode*)malloc(sizeof(SetNode));
    node->key = key;
    node->next = next;
    return node;
}

typedef struct Set {
    int tableSize;
    SetNode **listArray; //double pointer
} Set;

Set * createSet() {
    Set *hTable = (Set*) malloc(sizeof(Set));
    hTable->tableSize = TABLE_SIZE;
    hTable->listArray = (SetNode **)malloc(hTable->tableSize * sizeof(SetNode *));
    for (int i = 0; i < hTable->tableSize; i++)
        hTable->listArray[i] = NULL;
    return hTable;
}
/*
unsigned int Hash(int key, int tableSize) { //division method
    unsigned int hashValue = 0;
    hashValue = key;
    return hashValue % tableSize;
}
*/

void SetPrint(Set *hTable) {
    printf("[ ");
    for (int i = 0; i < hTable->tableSize; i++) {
        SetNode *head = hTable->listArray[i];
        while (head) {
            printf("%d ", head->key);
            head = head->next;
        }
    }
    printf("]\n");
}

int SetFind(Set *hTable, int key) {
    SetNode *head;
    int index = Hash(key, hTable->tableSize);
    head = hTable->listArray[index];
    while(head) {
        if (head->key == key)
            return 1;
        head = head->next;
    }
    return 0;
}

void SetAdd(Set *hTable, int key) {
    int index = Hash(key, hTable->tableSize);
    SetNode *head = hTable->listArray[index];
    while(head) {
        if (head->key == key) {
            return;
        }
        head = head->next;
    }
    hTable->listArray[index] = createSetNode(key, hTable->listArray[index]);
}

int SetRemove(Set *hTable, int key) {
    int index = Hash(key, hTable->tableSize);
    SetNode *currNode = hTable->listArray[index];
    if(currNode && currNode->key == key) {
        hTable->listArray[index] = currNode->next;
        free(currNode);
        return 1;
    }

    SetNode *nextNode;
    while (currNode) {
        nextNode = currNode->next;
        if (nextNode && nextNode->key == key) {   
            currNode->next = nextNode->next;
            free(nextNode);
            return 1;
        }
        currNode = nextNode;
    }
    return 0;
}

int mainB() {
    Set* st = createSet();
    SetAdd(st, 2);
    SetAdd(st, 3);
    SetAdd(st, 3);
    SetAdd(st, 5);
    SetAdd(st, 5);
    SetPrint(st);
    printf("SetFind 3 : %d\n", SetFind(st, 3));

    SetRemove(st, 3);
    SetPrint(st);

    printf("SetFind 5 : %d\n", SetFind(st, 5));
    printf("SetFind 3 : %d\n", SetFind(st, 3));
    return 0;
}

/*
[2->1] [3->2] [5->3] 
[2->1] [3->1] [5->3] 
[2->1] [5->3] 
SetFind 5 : 1
SetFind 3 : 0
GetCount 5 : 3
GetCount 3 : 0
*/
