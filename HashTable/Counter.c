#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 517
#define TABLE_BITS 9

unsigned int Hash(int key, int tableSize) { //division method
    unsigned int hashValue = 0;
    hashValue = key;
    return hashValue % tableSize;
}

typedef struct CounterNode {
    int key;
    int value;
    struct CounterNode *next;
} CounterNode;

CounterNode* createCounterNode(int key, int value, CounterNode* next) {
    CounterNode* node = (CounterNode*)malloc(sizeof(CounterNode));
    node->key = key;
    node->value = value;
    node->next = next;
    return node;
}

typedef struct Counter {
    int tableSize;
    CounterNode **listArray; //double pointer
} Counter;

Counter * createCounter() {
    Counter *hTable = (Counter*) malloc(sizeof(Counter));
    hTable->tableSize = TABLE_SIZE;
    hTable->listArray = (CounterNode **)malloc(hTable->tableSize * sizeof(CounterNode *));

    for (int i = 0; i < hTable->tableSize; i++)
        hTable->listArray[i] = NULL;
    return hTable;
}

void CounterPrint(Counter *hTable) {
    for (int i = 0; i < hTable->tableSize; i++) {
        CounterNode *head = hTable->listArray[i];
        while (head) {
            printf("[%d->%d] ", head->key, head->value);
            head = head->next;
        }
    }
    printf("\n");
}

int FindKey(Counter *hTable, int key) {
    CounterNode *head;
    int index = Hash(key, hTable->tableSize);
    head = hTable->listArray[index];
    while(head) {
        if (head->key == key)
            return 1;
        head = head->next;
    }
    return 0;
}

int GetCount(Counter *hTable, int key) {
    int index = Hash(key, hTable->tableSize);
    CounterNode *head = hTable->listArray[index];
    while(head) {
        if(head->key == key)
            return head->value;
        head = head->next;
    }
    return 0;
}

void CounterAdd(Counter *hTable, int key) {
    int index = Hash(key, hTable->tableSize);
    CounterNode *head = hTable->listArray[index];
    while(head) {
        if (head->key == key) {
            head->value += 1;
            return;
        }
        head = head->next;
    }
    hTable->listArray[index] = createCounterNode(key, 1, hTable->listArray[index]);
}

int CounterRemove(Counter *hTable, int key) {
    int index = Hash(key, hTable->tableSize);
    CounterNode *currNode = hTable->listArray[index];

    if(currNode && currNode->key == key) {
        if(currNode->value == 1) {
            hTable->listArray[index] = currNode->next;
            free(currNode);
        } else {
            currNode->value -= 1;
        }
        return 1;
    }

    CounterNode *nextNode;
    while (currNode) {
        nextNode = currNode->next;
        if (nextNode && nextNode->key == key) {   
            if (nextNode->value == 1) {
            currNode->next = nextNode->next;
            free(nextNode);
            } else {
                nextNode->value -= 1;
            }
            return 1;
        }
        currNode = nextNode;
    }
    return 0;
}

int main() {
    Counter* ctr = createCounter();
    CounterAdd(ctr, 2);
    CounterAdd(ctr, 3);
    CounterAdd(ctr, 3);
    CounterAdd(ctr, 5);
    CounterAdd(ctr, 5);
    CounterAdd(ctr, 5);
    CounterPrint(ctr);

    CounterRemove(ctr, 3);
    CounterPrint(ctr);
    CounterRemove(ctr, 3);
    CounterPrint(ctr);

    printf("FindKey 5 : %d\n", FindKey(ctr, 5));
    printf("FindKey 3 : %d\n", FindKey(ctr, 3));
    printf("GetCount 5 : %d\n", GetCount(ctr, 5));
    printf("GetCount 3 : %d\n", GetCount(ctr, 3));
    return 0;
}

/*
[2->1] [3->2] [5->3] 
[2->1] [3->1] [5->3] 
[2->1] [5->3] 
FindKey 5 : 1
FindKey 3 : 0
GetCount 5 : 3
GetCount 3 : 0
*/
