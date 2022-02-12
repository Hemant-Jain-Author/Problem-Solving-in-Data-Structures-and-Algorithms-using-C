#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// min heap compare function.
int greater(int a, int b) {
    return a > b;
}

// max heap compare function.
int less(int a, int b) {
    return a < b;
}


typedef struct Heap {
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
        if (compare(arr[parent], arr[position])) {
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

int isEmpty(Heap *hp) {
    return hp->size == 0;
}

void printHeap(Heap *hp) {
    for (int i = 0; i < hp->size; i++)
        printf("%d ", hp->array[i]);
    printf("\n");
}

void heapSort(int arr[], int size, int inc) {
    int(* comp )(int , int);
    if(inc)
        comp = less; // max heap for increasing.
    else
        comp = greater; // min heap for decreasing.

    Heap* hp = createHeap2(arr, size, comp);
    for (int i = size-1; i >=0; i--)
        arr[i] = heapRemove(hp);
}

int heapDelete(Heap *hp, int value) {
    for (int i = 0; i < hp->size; i++) {
        if(hp->array[i] == value){
            hp->array[i] = hp->array[hp->size-1];
            hp->size -= 1;
            proclateDown(hp->array, i, hp->size, hp->compare);
            return 1;
        }
    }
    return 0;
}

int mainA() {
    int a[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    Heap* hp = createHeap2(a, 10, greater);//min heap
    printHeap(hp);
    while (!isEmpty(hp))
    	printf("%d ", heapRemove(hp));
    return 0;
}

/*
1 2 3 4 5 7 10 8 9 6 
1 2 3 4 5 6 7 8 9 10
*/

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int mainB() {
    int b[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    heapSort(b, 10, 1); // increasing
    printArray(b, 10);
    
    heapSort(b, 10, 0); // decreasing
    printArray(b, 10);
    return 0;
}

/*
1 2 3 4 5 6 7 8 9 10 
10 9 8 7 6 5 4 3 2 1 
*/