#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../Heap/Heap.c"

void bubbleSort(int arr[], int size, int (*comp)(int p1, int p2)) {
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

int chotaBhim(int cups[], int size) {
	int time = 60;
	bubbleSort(cups, size, less); // decreasing order.
	int total = 0;
	int index, temp;
	while (time > 0) {
		total += cups[0];
		cups[0] = ceil(cups[0] / 2.0);
		index = 0;
		temp = cups[0];
		while (index < size - 1 && temp < cups[index + 1]) {
			cups[index] = cups[index + 1];
			index += 1;
		}
		cups[index] = temp;
		time -= 1;
	}
	printf("Total : %d\n" , total );
	return total;
}

int chotaBhim2(int cups[], int size) {
    int time = 60;
    Heap* hp = createHeap2(cups, size, less); // max heap
    int total = 0;
    int value;
    while (time > 0) {
        value = heapRemove(hp);
        total += value;
        value = ceil(value / 2.0);
        heapAdd(hp, value);
        time -= 1;
    }
    printf("Total : %d\n", total);
    return total;
}

int main() {
	int cups[] = {2, 1, 7, 4, 2};
    chotaBhim(cups, sizeof(cups) / sizeof(int));
    int cups2[] = {2, 1, 7, 4, 2};
    chotaBhim2(cups2, sizeof(cups) / sizeof(int));
	return 0;
}

/*
Total : 76
Total : 76
*/