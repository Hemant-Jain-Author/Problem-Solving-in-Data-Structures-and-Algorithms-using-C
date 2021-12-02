
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Counter.c"

int isAnagram(char *str1, char *str2) {
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    if (size1 != size2)
        return 0;
    
    Counter* cm = createCounter();

    for (int i = 0; i < size1; i++)
        CounterAdd(cm, str1[i]);

    for (int i = 0; i < size2; i++) {
        if (GetCount(cm, str2[i]) == 0)
            return 0;
        else
            CounterRemove(cm, str2[i]);
    }
    return 1;
}

char *removeDuplicate(char *str, int size) {
    Counter* hs = createCounter();
    char *ret = (char *)malloc(sizeof(char) * size);
    int retIndex = 0;
    for (int i = 0; i < size; i++) {
        if (GetCount(hs, str[i]) == 0) {
            ret[retIndex] = str[i];
            retIndex += 1;
            CounterAdd(hs, str[i]);
        }
    }
    ret[retIndex] = '\0';
    return ret;
}

int findMissing(int arr[], int size, int start, int end) {
    Counter* cm = createCounter();

    for (int i = 0; i < size; i++)
        CounterAdd(cm, arr[i]);

    int curr = start;
    while (curr <= end) {
        if (GetCount(cm, curr) == 0)
            return curr;
        curr += 1;
    }
    return -99999;
}

void printRepeating(int arr[], int size) {
    Counter* cm = createCounter();
    int val;
    printf("Repeating elements are: ");
    for (int i = 0; i < size; i++) {
        val = arr[i];
        if (GetCount(cm, val))
            printf("%d ", val);
        else
            CounterAdd(cm, val);
    }
    printf("\n");
}

int printFirstRepeating(int arr[], int size) {
    Counter* cm = createCounter();
    int i = 0;
    for (i = 0; i < size; i++) {
        CounterAdd(cm, arr[i]);
    }
    for (i = 0; i < size; i++) {
        if (GetCount(cm, arr[i]) > 1) {
            printf("First Repeating number is : %d\n", arr[i]);
            return arr[i];
        }
    }
}

void PrintSortByOrder(int arr[], int size, int arr2[], int size2) {
    int i, key, count;
    Counter* cm = createCounter();
    for (i = 0; i < size; i++) {
        CounterAdd(cm, arr[i]);
    }

    for (i = 0; i < size2; i++) {
        key = arr2[i];
        count = GetCount(cm, key);
        for (int j = 0; j < count; j++) {
            printf("%d ", key);
            CounterRemove(cm, key);
        }
    }
    for (i = 0; i < size; i++) {
        key = arr[i];
        if (GetCount(cm, key)) {
            printf("%d ", key);
            CounterRemove(cm, key);
        }
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