#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 517
#define TABLE_BITS 9

int Hash(int key, int tableSize) { //division method
	return key % tableSize;
}

typedef struct HTNode {
	int value;
	struct HTNode* next;
} HTNode;

HTNode* createHTNode(int value, HTNode* next) {
    HTNode* node = (HTNode*)malloc(sizeof(HTNode));
    node->value = value;
    node->next = next;
    return node;
}

typedef struct HashTable {
	int tableSize;
	HTNode** listArray;//double pointer
} HashTable;

HashTable* createHashTable(int size) {
	HashTable* hTable = (HashTable*)malloc(sizeof(HashTable));
	hTable->tableSize = size;
	hTable->listArray = (HTNode**)malloc(hTable->tableSize * sizeof(HTNode*));

	for (int i = 0; i<hTable->tableSize; i++)
		hTable->listArray[i] = NULL;

	return hTable;
}

void HashPrint(HashTable* hTable) {
    HTNode* head;
	for (int i = 0; i<hTable->tableSize; i++) {
		head = hTable->listArray[i];
		while (head) {
			printf("%d ", head->value);
			head = head->next;
		}
	}
    printf("\n");
}

int HashFind(HashTable* hTable, int value) {
	HTNode* head;
	int index = Hash(value, hTable->tableSize);
	head = hTable->listArray[index];
	while (head) {
        if(head->value == value)
            return 1;
		head = head->next;
	}
	return 0;
}


void HashAdd(HashTable* hTable, int value) {
	int index = Hash(value, hTable->tableSize);
	hTable->listArray[index] = createHTNode(value, hTable->listArray[index]);
}

int HashRemove(HashTable* hTable, int value) {
	int index = Hash(value, hTable->tableSize);
	HTNode*currNode = hTable->listArray[index];

	if (currNode && currNode->value == value) {
		hTable->listArray[index] = currNode->next;
		free(currNode);
		return 1;
	}

    HTNode* nextNode;
	while (currNode) {
		nextNode = currNode->next;
		if (nextNode && nextNode->value == value) {
			currNode->next = nextNode->next;
			free(nextNode);
			return 1;
		}
		currNode = nextNode;
	}
	return 0;
}


int main() {
    HashTable* ht = createHashTable(100);
    HashAdd(ht, 1);
    HashAdd(ht, 2);
    HashAdd(ht, 3);
    HashPrint(ht);
    printf("Find 2 : %d\n", HashFind(ht, 2));
    HashRemove(ht, 2);
    printf("Find 2 : %d\n", HashFind(ht, 18));
    HashPrint(ht);
    return 0;
}

/*
1 2 3 
Find 2 : 1
Find 2 : 0
1 3 
*/