#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int less(int a, int b) {
	return a < b;
}

void sort(int arr[], int size, int (*comp)(int p1, int p2)) {
    int i, j;
	int temp;
    for (i = 0; i < (size - 1); i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (comp(arr[j], arr[j + 1])} {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

typedef struct Heap_t {
    int capacity;
    int size;
    int *array;
    int(* compare)(int , int);
} Heap;

void proclateDown(int arr[], int position, int size, int(* compare)(int , int)) {
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;

    int small = -1;
    int temp;

    if (lChild < size)
        small = lChild;

    if (rChild < size && compare(arr[lChild], arr[rChild]))
        small = rChild;

    if (small != -1 && compare(arr[position], arr[small])) {
        temp = arr[position];
        arr[position] = arr[small];
        arr[small] = temp;

        proclateDown(arr, small, size, compare);
    }
}

void proclateUp(int arr[], int position, int(* compare)(int , int)) {
    int parent = (position - 1) / 2;
    int temp;

    if (parent >= 0) {
        if (compare(arr[parent], arr[position])} {
            temp = arr[position];
            arr[position] = arr[parent];
            arr[parent] = temp;
            proclateUp(arr, parent, compare);
        }
    }
}

void heapify(int arr[], int size, int(* compare)(int , int)) {
    for (int i = size/2; i >= 0; i--)
        proclateDown(arr, i, size, compare);
}


Heap* createHeap2(int arr[], int size, int(* compare)(int , int)) {
    Heap* hp = (Heap*) malloc(sizeof(Heap));
    hp->size = hp->capacity = size;
    hp->array = arr;
    hp->compare = compare;
    heapify(arr, size, compare);
    return hp;
}

Heap* createHeap(int(* compare)(int , int)) {
    Heap* hp = (Heap*) malloc(sizeof(Heap));
    hp->size = 0; 
    hp->capacity = 100;
    hp->array = (int *)malloc((hp->capacity) * sizeof(int));
    hp->compare = compare;
    return hp;
}

int heapRemove(Heap *hp) {
    int value = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    proclateDown(hp->array, 0, hp->size, hp->compare);
    return value;
}

void heapAdd(Heap *hp, int value) {
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = value;
    proclateUp(hp->array, hp->size - 1, hp->compare);
}

int heapTop(Heap *hp) {
    return hp->array[0];
}

int heapSize(Heap *hp) {
    return hp->size;
}

int chotaBhim(int cups[], int size) {
	int time = 60;
	sort(cups, size, less); // decreasing order.
	int total = 0;
	int index, temp;
	while (time > 0} {
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