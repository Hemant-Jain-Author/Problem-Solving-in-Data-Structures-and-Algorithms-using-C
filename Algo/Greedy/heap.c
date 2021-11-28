#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int greater(int a, int b) // min heap compare function.
{
    return a > b;
}

int less(int a, int b) // max heap compare function.
{
    return a < b;
}


typedef struct Heap_t
{
    int capacity;
    int size;
    int *array;
    int(* compare)(int , int);
} Heap;

void proclateDown(int *a, int position, int size, int(* compare)(int , int))
{
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;

    int small = -1;
    int temp;

    if (lChild < size)
        small = lChild;

    if (rChild < size && compare(a[lChild], a[rChild]))
        small = rChild;

    if (small != -1 && compare(a[position], a[small]))
    {
        temp = a[position];
        a[position] = a[small];
        a[small] = temp;

        proclateDown(a, small, size, compare);
    }
}

void proclateUp(int *a, int position, int(* compare)(int , int))
{
    int parent = (position - 1) / 2;
    int temp;

    if (parent >= 0)
    {
        if (compare(a[parent], a[position]))
        {
            temp = a[position];
            a[position] = a[parent];
            a[parent] = temp;

            proclateUp(a, parent, compare);
        }
    }
}

void heapify(int arr[], int size, int(* compare)(int , int))
{
    for (int i = size/2; i >= 0; i--)
        proclateDown(arr, i, size, compare);
}


Heap* createHeap2(int arr[], int size, int(* compare)(int , int))
{
    Heap* hp = (Heap*) malloc(sizeof(Heap));
    hp->size = hp->capacity = size;
    hp->array = arr;
    hp->compare = compare;
    heapify(arr, size, compare);
    return hp;
}

Heap* createHeap(int(* compare)(int , int))
{
    Heap* hp = (Heap*) malloc(sizeof(Heap));
    hp->size = 0; 
    hp->capacity = 100;
    hp->array = (int *)malloc((hp->capacity) * sizeof(int));
    hp->compare = compare;
    return hp;
}

int heapRemove(Heap *hp)
{
    int value = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    proclateDown(hp->array, 0, hp->size, hp->compare);
    return value;
}

void heapAdd(Heap *hp, int value)
{
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = value;
    proclateUp(hp->array, hp->size - 1, hp->compare);
}

int heapTop(Heap *hp)
{
    return hp->array[0];
}

int heapsize(Heap *hp)
{
    return hp->size;
}

void heapSort(int arr[], int size, int(* compare)(int , int))
{
    Heap* hp = createHeap2(arr, size, compare);
    for (int i = size-1; i >=0; i--)
        arr[i] = heapRemove(hp);
}

void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
        printf(" %d ", array[i]);
    printf("\n");
}

void printHeap(Heap *hp)
{
    for (int i = 0; i < hp->size; i++)
        printf(" %d ", hp->array[i]);
    printf("\n");
}

int main()
{
    int a[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    Heap* hp = createHeap2(a, 10, greater);
    printHeap(hp);

    printf("Value returned from deleteMin %d \n", heapRemove(hp));
    printHeap(hp);

    heapAdd(hp, 1);
    printHeap(hp);
    
    heapAdd(hp, 20);
    printHeap(hp);

    int b[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    heapSort(b, 10, greater); // decreasing
    printArray(b, 10);
    
    heapSort(b, 10, less); // increasing
    printArray(b, 10);
    return 0;
}