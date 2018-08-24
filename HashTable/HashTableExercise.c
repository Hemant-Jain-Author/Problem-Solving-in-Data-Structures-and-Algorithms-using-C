
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void HashInit(HashTable *hTable)
{
    hTable->tableSize = TABLE_SIZE;
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

int isAnagram(char *str1, char *str2)
{
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    if (size1 != size2)
        return 0;
    HashTable cm;
    HashInit(&cm);

    for (int i = 0; i < size1; i++)
        CounterAdd(&cm, str1[i]);

    for (int i = 0; i < size2; i++)
    {
        if (FindCount(&cm, str2[i]) == 0)
            return 0;
        else
            CounterRemove(&cm, str2[i]);
    }
    return 1;
}

char *removeDuplicate(char *str, int size)
{
    HashTable hs;
    HashInit(&hs);
    char *ret = (char *)malloc(sizeof(char) * size);
    int retIndex = 0;
    for (int i = 0; i < size; i++)
    {
        if (FindCount(&hs, str[i]) == 0)
        {
            ret[retIndex] = str[i];
            retIndex += 1;
            CounterAdd(&hs, str[i]);
        }
    }
    ret[retIndex] = '\0';
    return ret;
}

int findMissing(int arr[], int size, int start, int end)
{
    HashTable cm;
    HashInit(&cm);

    for (int i = 0; i < size; i++)
        CounterAdd(&cm, arr[i]);

    int curr = start;
    while (curr <= end)
    {
        if (FindCount(&cm, curr) == 0)
            return curr;
        curr += 1;
    }
    return -99999;
}

void printRepeating(int arr[], int size)
{
    HashTable cm;
    HashInit(&cm);
    int val;
    printf("Repeating elements are:");
    for (int i = 0; i < size; i++)
    {
        val = arr[i];
        if (FindCount(&cm, val))
            printf(" %d ", val);
        else
            CounterAdd(&cm, val);
    }
}
int printFirstRepeating(int arr[], int size)
{
    HashTable cm;
    HashInit(&cm);
    int i = 0;
    for (i = 0; i < size; i++)
    {
        CounterAdd(&cm, arr[i]);
    }
    for (i = 0; i < size; i++)
    {
        if (FindCount(&cm, arr[i]) > 1)
        {
            printf("\n First Repeating number is : %d", arr[i]);
            return arr[i];
        }
    }
}

void PrintSortByOrder(int arr[], int size, int arr2[], int size2)
{
    int i, key, count;
    HashTable cm;
    //int *temp = (int*)malloc(sizeof(int)*size);
    //int tempIndex = 0;
    HashInit(&cm);
    for (i = 0; i < size; i++)
    {
        CounterAdd(&cm, arr[i]);
    }

    for (i = 0; i < size2; i++)
    {
        key = arr2[i];
        count = FindCount(&cm, key);
        for (int j = 0; j < count; j++)
        {
            printf("%d ", key);
            CounterRemove(&cm, key);
        }
    }
    for (i = 0; i < size; i++)
    {
        key = arr[i];
        if (FindCount(&cm, key))
        {
            printf("%d ", key);
            CounterRemove(&cm, key);
        }
    }
}

//Testing code
int main()
{
    int arr[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
    int arr2[] = {2, 1, 8, 3};
    PrintSortByOrder(arr, 11, arr2, 4);
}

int hornerHash(char key[], int size, int tableSize)
{
    int h = 0;
    int i = 0;
    while (i < size)
    {
        h = (32 * h + key[i]) % tableSize;
        i += 1;
    }
    return h;
}

int main4()
{
    char *first = "hello";
    char *second = "elloh";
    char *third = "world";
    printf("isAnagram : %d \n",
           isAnagram(first, second));
    printf("isAnagram : %d \n",
           isAnagram(first, third));
    printf(" %s \n", removeDuplicate(first, strlen(first)));
    int arr[] = {1, 2, 3, 5, 6, 7, 8, 9, 10};
    int size = 9;
    printf("findMissing : %d \n", findMissing(arr, 9, 1, 10));
    int arr1[] = {1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 1};
    int size2 = 11;
    printRepeating(arr1, 11);
    printFirstRepeating(arr1, 11);
    return 0;
}