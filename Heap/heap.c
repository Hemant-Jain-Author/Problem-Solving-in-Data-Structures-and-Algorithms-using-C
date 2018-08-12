//remember there is no calculation of array start from zero except in build heap and initialize rest all doesn’t care about it

#include <stdio.h>
#include <stdlib.h>

typedef struct Heap
{
    int Capacity;
    int Size;
    int *Array;
} Heap;

void proclateDown(int *a, int position, int size)
{
    int lChild = 2 * position;
    int rChild = lChild + 1;
    int small = -1;

    if (lChild < size)
        small = lChild;

    if (rChild < size && a[rChild] < a[lChild])
        small = rChild;

    if (small != -1 && a[small] < a[position])
    {
        a[position] ^= a[small] ^= a[position] ^= a[small];
        proclateDown(a, small, size);
    }
}

void proclateUp(int *a, int position)
{
    int parent = position / 2;

    if (parent != 0)
    {
        if (a[parent] > a[position])
        {
            a[position] ^= a[parent] ^= a[position] ^= a[parent];
            proclateUp(a, parent);
        }
    }
}

void HeapInitialize(Heap *hp, int arr[], int size)
{
    hp->Size = hp->Capacity = size;
    hp->Array = (int *)malloc((size + 1) * sizeof(int));

    for (int j = 0; j < size; j++)
        hp->Array[j + 1] = arr[j];

    for (int i = (hp->Size) / 2; i > 0; i--)
        proclateDown(hp->Array, i, hp->Size);
}

void BuildHeap(Heap *hp, int size)
{
    hp->Size = 0;
    hp->Capacity = size;
    hp->Array = (int *)malloc((size + 1) * sizeof(int));
}

int HeapRemove(Heap *hp)
{
    int value = hp->Array[1];
    hp->Array[1] = hp->Array[hp->Size];
    hp->Size--;
    proclateDown(hp->Array, 1, hp->Size);
    return value;
}

void HeapAdd(Heap *hp, int value)
{
    hp->Size++;
    hp->Array[hp->Size] = value;
    proclateUp(hp->Array, hp->Size);
}

void printHeapUtil(int *a, int position, int size)
{
    int lChild, rChild;
    if (2 * position <= size)
        lChild = 2 * position;
    else
        lChild = -1;

    if (2 * position + 1 <= size)
        rChild = (2 * position + 1);
    else
        rChild = -1;

    if (position % 2 == 0)
        printf("   ");
    for (int i = 0; i < position; i++)
        printf("   ");
    printf("[ %d ] \n", a[position]);

    if (lChild != -1)
        printHeapUtil(a, lChild, size);
    if (rChild != -1)
        printHeapUtil(a, rChild, size);
}

void PrintHeap(Heap *hp)
{
    printf("----------------------------\n");
    printHeapUtil(hp->Array, 1, hp->Size);
    printf("----------------------------\n");
}

void HeapSort(int a[], int size)
{
    Heap hp;
    HeapInitialize(&hp, a, 10);
    for (int i = 0; i < size; i++)
    {
        a[i] = HeapRemove(&hp);
    }
}

void PrintArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf(" %d ", arr[i]);
    printf("\n");
}

int main()
{
    int a[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    Heap hp;
    HeapInitialize(&hp, a, 10);
    PrintHeap(&hp);

    printf("Value returned from deleteMin %d \n", HeapRemove(&hp));
    PrintHeap(&hp);

    HeapAdd(&hp, 1);
    PrintHeap(&hp);
    HeapAdd(&hp, 2);
    PrintHeap(&hp);

    Heap hp2;
    BuildHeap(&hp2, 10);
    HeapAdd(&hp2, 5);
    PrintHeap(&hp2);
    HeapAdd(&hp2, 9);
    HeapAdd(&hp2, 6);
    PrintHeap(&hp2);
    HeapAdd(&hp2, 4);
    HeapAdd(&hp2, 2);
    PrintHeap(&hp2);

    int arr[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    HeapSort(arr, sizeof(arr) / sizeof(int));
    PrintArray(arr, sizeof(arr) / sizeof(int));
}