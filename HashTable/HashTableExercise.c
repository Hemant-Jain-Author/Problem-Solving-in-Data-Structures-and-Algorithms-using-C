
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashLP.c"

int isAnagram(char *str1, char *str2) {
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    if (size1 != size2)
        return 0;
    
    HashTable* ht = createHashTable(100);

    for (int i = 0; i < size1; i++)
        HashAdd(ht, str1[i]);

    for (int i = 0; i < size2; i++) {
        if (HashRemove(ht, str2[i]) == 0)
            return 0;
    }
    return 1;
}

char *removeDuplicate(char *str, int size) {
    HashTable* hs = createHashTable(100);
    char *ret = (char *)malloc(sizeof(char) * size);
    int retIndex = 0;
    for (int i = 0; i < size; i++) {
        if (HashFind(hs, str[i]) == 0) {
            ret[retIndex] = str[i];
            retIndex += 1;
            HashAdd(hs, str[i]);
        }
    }
    ret[retIndex] = '\0';
    return ret;
}

int findMissing(int arr[], int size, int start, int end) {
    HashTable* ht = createHashTable(100);

    for (int i = 0; i < size; i++)
        HashAdd(ht, arr[i]);

    for (int i = start; i <= end; i++) {
        if (HashFind(ht, i) == 0)
            return i;
    }
    return -99999;
}

void printRepeating(int arr[], int size) {
    HashTable* ht = createHashTable(100);    
    printf("Repeating elements are: ");
    for (int i = 0; i < size; i++) {
        if (HashFind(ht, arr[i]))
            printf("%d ", arr[i]);
        else
            HashAdd(ht, arr[i]);
    }
    printf("\n");
}

int printFirstRepeating(int arr[], int size) {
    HashTable* ht = createHashTable(100);    
    int firstRepeating = -99999;
    
    for (int i = size - 1; i >= 0; i--) {
        if (HashFind(ht, arr[i])) {
            firstRepeating = arr[i];
        } else {
            HashAdd(ht, arr[i]);
        }
    }
    if(firstRepeating != -99999)
        printf("First Repeating number is : %d\n", firstRepeating);
    else
        printf("No Repeating number\n");

    return firstRepeating;
}

void PrintSortByOrder(int arr[], int size, int arr2[], int size2) {
    int i;
    HashTable* ht = createHashTable(100);
    for (i = 0; i < size; i++) {
        HashAdd(ht, arr[i]);
    }
    i = 0;
    while (i < size2) {
        if (HashRemove(ht, arr2[i]) == 1) {
            printf("%d ", arr2[i]);
            continue;
        }
        i++;
    }
    for (i = 0; i < size; i++) {
        if (HashRemove(ht, arr[i]) == 1)
            printf("%d ", arr[i]);
    }
}

int hornerHash(char key[], int size, int tableSize) {
    int h = 0;
    int i = 0;
    while (i < size) {
        h = (32 * h + key[i]) % tableSize;
        i += 1;
    }
    return h;
}

//Testing code
int main() {
    char *first = "hello";
    char *second = "elloh";
    char *third = "world";
    printf("isAnagram : %d\n", isAnagram(first, second));
    printf("isAnagram : %d\n", isAnagram(first, third));
    printf(" %s \n", removeDuplicate(first, strlen(first)));
    int arr[] = {1, 2, 3, 5, 6, 7, 8, 9, 10};
    int size = 9;
    printf("findMissing : %d\n", findMissing(arr, 9, 1, 10));
    int arr1[] = {1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 1};
    int size2 = 11;
    printRepeating(arr1, 11);
    printFirstRepeating(arr1, 11);

    int arr2[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
    int arr3[] = {2, 1, 8, 3};
    PrintSortByOrder(arr2, 11, arr3, 4);
    return 0;
}

/*
isAnagram : 1
isAnagram : 0
 helo 
findMissing : 4
Repeating elements are: 4 1 
First Repeating number is : 1
2 2 1 1 8 8 3 5 7 9 6 
*/
