#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 517
#define TABLE_BITS 9

typedef struct dataNode_t
{
    int key;
    int value;
    struct dataNode_t *next;
} DataNode;

typedef struct hashTable_t
{
    int tableSize;
    DataNode **listArray; //double pointer
} HashTable;

unsigned int Hash(int key, int tableSize) //division method
{
    unsigned int hashValue = 0;
    hashValue = key;
    return hashValue % tableSize;
}

void HashInit(HashTable *hTable, int size)
{
    hTable->tableSize = size;
    hTable->listArray = (DataNode **)malloc(hTable->tableSize * sizeof(DataNode *));

    for (int i = 0; i < hTable->tableSize; i++)
        hTable->listArray[i] = NULL;
}

void CounterPrint(HashTable *hTable)
{
    DataNode *head;
    for (int i = 0; i < hTable->tableSize; i++)
    {
        head = hTable->listArray[i];
        while (head)
        {
            printf(" [ %d -> %d ]", head->key, head->value);
            head = head->next;
        }
    }
    printf("\n");
}

int FindKey(HashTable *hTable, int key)
{
    DataNode *head;
    int index = Hash(key, hTable->tableSize);
    head = hTable->listArray[index];
    while (head)
    {
        if (head->key == key)
            return 1;
        head = head->next;
    }
    return 0;
}

int FindCount(HashTable *hTable, int key)
{
    DataNode *head;
    int index = Hash(key, hTable->tableSize);
    head = hTable->listArray[index];
    while (head)
    {
        if (head->key == key)
            return head->value;
        head = head->next;
    }
    return 0;
}

void CounterAdd(HashTable *hTable, int key)
{
    DataNode *head;
    int index = Hash(key, hTable->tableSize);
    head = hTable->listArray[index];
    while (head)
    {
        if (head->key == key)
        {
            head->value += 1;
            return;
        }
        head = head->next;
    }

    DataNode *temp = (DataNode *)malloc(sizeof(DataNode));
    temp->key = key;
    temp->value = 1;
    temp->next = hTable->listArray[index];
    hTable->listArray[index] = temp;
}

int CounterRemove(HashTable *hTable, int key)
{
    DataNode *currNode;
    DataNode *nextNode;
    int index = Hash(key, hTable->tableSize);
    currNode = hTable->listArray[index];

    if (currNode && currNode->key == key)
    {
        if (currNode->value == 1)
        {
            hTable->listArray[index] = currNode->next;
            free(currNode);
        } 
        else 
        {
            currNode->value -= 1;
        }
        return 1;
    }

    while (currNode)
    {
        nextNode = currNode->next;
        if (nextNode && nextNode->key == key)
        {   
            if (nextNode->value == 1)
            {
            currNode->next = nextNode->next;
            free(nextNode);
            }
            else 
            {
                nextNode->value -= 1;
            }
            return 1;
        }
        else
        {
            currNode = nextNode;
        }
    }
    return 0;
}

int main()
{
    HashTable myTable;
    HashInit(&myTable, 10);
    CounterAdd(&myTable, 88);
    CounterAdd(&myTable, 88);
    CounterAdd(&myTable, 18);
    CounterAdd(&myTable, 49);
    CounterAdd(&myTable, 58);
    CounterAdd(&myTable, 69);
    CounterPrint(&myTable);
    CounterRemove(&myTable, 88);
    CounterPrint(&myTable);

    CounterRemove(&myTable, 88);
    CounterPrint(&myTable);
    printf("Find 88 : %d ", FindCount(&myTable, 88));
    printf("Find 18 : %d ", FindCount(&myTable, 18));
    return 0;
}

