#include <stdio.h>
#include<stdlib.h>
#include "../../Heap/Heap.c"

void sort(int arr[], int size, int (*comp)(int p1, int p2)) {
    int i, j;
	int temp;
    for (i = 0; i < (size - 1); i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (comp(arr[j], arr[j + 1])) {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int JoinRopes(int ropes[], int size) {
    sort(ropes, size, less); // decreasing
    int total = 0;
    int value = 0;
    int temp, index;
    int length = size;

    while (length >= 2) {
        value = ropes[length - 1] + ropes[length - 2];
        total += value;
        index = length - 2;

        while (index > 0 && ropes[index - 1] < value) {
            ropes[index] = ropes[index - 1];
            index -= 1;
        }
        ropes[index] = value;
        length--;
    }
    printf("Total : %d \n", total);
    return total;
}

int JoinRopes2(int ropes[], int size) {
    Heap* hp = createHeap2(ropes, size, greater);
    int total = 0;
    int value = 0;
    while (heapSize(hp) > 1) {
        value = heapRemove(hp);
        value += heapRemove(hp);
        heapAdd(hp, value);
        total += value;
    }
    printf("Total : %d \n", total);
    return total;
}

int main() {
    int ropes[] = {4, 3, 2, 6};
    JoinRopes(ropes, sizeof(ropes) / sizeof(int));
    int rope2[] = {4, 3, 2, 6};
    JoinRopes2(rope2, sizeof(rope2) / sizeof(int));
    return 0;
}

/*
Total : 29 
Total : 29
*/