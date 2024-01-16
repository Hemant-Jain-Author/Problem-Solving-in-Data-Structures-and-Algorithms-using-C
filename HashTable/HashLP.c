#include <stdio.h>
#include <stdlib.h>

#define EMPTY_NODE 0
#define FILLED_NODE 1
#define DELETED_NODE 2

int Hash(int key, int size) { //division method
    return key % size;
}

int CollisionFunction(int i) {
    //return i*i;
    return i;
}

typedef struct HashTable {
    int size;
    int *array;
    char *flag;
} HashTable;

HashTable * createHashTable(int size) {
    HashTable *hTable = (HashTable*)malloc(sizeof(HashTable));
    hTable->size = size;
    hTable->array = (int *)malloc(hTable->size * sizeof(int));
    hTable->flag = (char *)malloc(hTable->size * sizeof(char));
    for (int i = 0; i < hTable->size; i++)
        hTable->flag[i] = EMPTY_NODE;
    return hTable;
}

void HashPrint(HashTable *hTable) {
    for (int i = 0; i < hTable->size; i++) {
        if (hTable->flag[i] == FILLED_NODE)
            printf("%d ", hTable->array[i]);
    }
    printf("\n");
}


int HashFind(HashTable *hTable, int value) {
    int hashValue = Hash(value, hTable->size);
    for (int i = 0; i < hTable->size; i++) {
        if ((hTable->flag[hashValue] == FILLED_NODE &&
            hTable->array[hashValue] == value) ||
            hTable->flag[hashValue] == EMPTY_NODE) {
            break;
        }
        hashValue += CollisionFunction(i);
        hashValue = hashValue % hTable->size;
    }

    if (hTable->flag[hashValue] == FILLED_NODE && 
        hTable->array[hashValue] == value)
        return 1;
    else
        return 0;
}

int HashAdd(HashTable *hTable, int value) {
    int hashValue = Hash(value, hTable->size);
    int i = 0;
    for (i = 0; i < hTable->size; i++) {
        if (hTable->flag[hashValue] == EMPTY_NODE ||
            hTable->flag[hashValue] == DELETED_NODE) {
            hTable->array[hashValue] = value;
            hTable->flag[hashValue] = FILLED_NODE;
            break;
        }
        hashValue += CollisionFunction(i);
        hashValue = hashValue % hTable->size;
    }

    if (i != hTable->size)
        return 1;
    else
        return 0; /* Table is full */
}

int HashRemove(HashTable *hTable, int value) {
    int hashValue = Hash(value, hTable->size);
    for (int i = 0; i < hTable->size; i++) {
        if (( hTable->flag[hashValue] == FILLED_NODE &&
            hTable->array[hashValue] == value ) || 
            hTable->flag[hashValue] == EMPTY_NODE) {
            break;
        }
        hashValue += CollisionFunction(i);
        hashValue = hashValue % hTable->size;
    }

    if (hTable->flag[hashValue] == FILLED_NODE && 
        hTable->array[hashValue] == value) {
        hTable->flag[hashValue] = DELETED_NODE;
        return 1;
    }
    else
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