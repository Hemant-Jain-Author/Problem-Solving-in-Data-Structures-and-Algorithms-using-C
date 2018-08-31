#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 517
#define TABLE_BITS 9

typedef struct dataNode_t{
	int value;
	struct dataNode_t* next;
} DataNode;

typedef struct hashTable_t{
	int tableSize;
	DataNode** listArray;//double pointer
}HashTable;

unsigned int Hash(int key, int tableSize)//division method
{
	unsigned int hashValue = 0;
	hashValue = key;
	return hashValue % tableSize;
}

void HashInit(HashTable* hTable, int size)
{
	hTable->tableSize = size;
	hTable->listArray = (DataNode**)malloc(hTable->tableSize * sizeof(DataNode*));

	for (int i = 0; i<hTable->tableSize; i++)
		hTable->listArray[i] = NULL;
}

void HashPrint(HashTable* hTable)
{
    DataNode* head;
	for (int i = 0; i<hTable->tableSize; i++)
	{
		head = hTable->listArray[i];
		while (head)
		{
			printf(" %d ", head->value);
			head = head->next;
		}
	}
    printf("\n");
}

int HashFind(HashTable* hTable, int value)
{
	DataNode* head;
	int index = Hash(value, hTable->tableSize);
	head = hTable->listArray[index];
	while (head)
	{
        if(head->value == value)
            return 1;
		head = head->next;
	}
	return 0;
}


void HashAdd(HashTable* hTable, int value)
{
	int index = Hash(value, hTable->tableSize);
	DataNode* temp = (DataNode*)malloc(sizeof(DataNode));
	temp->value = value;
	temp->next = hTable->listArray[index];
	hTable->listArray[index] = temp;
}

int HashRemove(HashTable* hTable, int value)
{
	DataNode* currNode;
    DataNode* nextNode;
	int index = Hash(value, hTable->tableSize);
	currNode = hTable->listArray[index];

	if (currNode && currNode->value == value)
	{
		hTable->listArray[index] = currNode->next;
		free(currNode);
		return 1;
	}

	while (currNode)
	{
		nextNode = currNode->next;
		if (nextNode && nextNode->value == value)
		{
			currNode->next = nextNode->next;
			free(nextNode);
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
    HashAdd(&myTable, 88);
    HashAdd(&myTable, 88);
    HashAdd(&myTable, 18);
    HashAdd(&myTable, 49);
    HashAdd(&myTable, 58);
    HashAdd(&myTable, 69);
    HashPrint(&myTable);
    HashRemove(&myTable, 88);
    HashRemove(&myTable, 88);
    HashPrint(&myTable);
    printf("Find 88 : %d ", HashFind(&myTable, 88));
    printf("Find 18 : %d ", HashFind(&myTable, 18));
    return 0;
}