#include <stdio.h>
#include <stdlib.h>

#include "../Stack/Stack.c"
#include "../Queue/Queue.c"

typedef struct GraphEdge_t
{
    int src;
    int dest;
    int cost;
    struct GraphEdge_t *next;
} GraphEdge;

typedef struct graph
{
    int count;
    GraphEdge **adj;
} Graph;

int greater(GraphEdge* a, GraphEdge* b){
    return a->cost > b->cost;
}

int max(int first, int second) {
    return (first > second) ? first : second;
}

#define MAX_CAPACITY 100
#define ERROR_VALUE -999

#define INFINITE 9999999

typedef struct Heap_t
{
    int capacity;
    int size;
    GraphEdge**array;
    int(* compare)(GraphEdge* , GraphEdge*);
} Heap;

Heap* createHeap(int(* compare)(GraphEdge* , GraphEdge*)) {
    Heap* hp = (Heap*)malloc(sizeof(Heap));
    hp->size = 0;
    hp->capacity = 100;
    hp->array = (GraphEdge **)malloc((hp->capacity) * sizeof(GraphEdge));
    hp->compare = compare;
    return hp;
}

void proclateDown(GraphEdge* arr[], int position, int size, int(* compare)(GraphEdge* , GraphEdge*)) {
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;
    int small = -1;

    if (lChild < size)
        small = lChild;

    if (rChild < size && compare(arr[lChild], arr[rChild]))
        small = rChild;

    if (small != -1 && compare(arr[position], arr[small])) {
        GraphEdge* temp = arr[position];
        arr[position] = arr[small];
        arr[small] = temp;
        proclateDown(arr, small, size, compare);
    }
}

void proclateUp(GraphEdge* arr[], int position, int(* compare)(GraphEdge* , GraphEdge*)) {
    int parent = (position - 1) / 2;
    if (parent >= 0) {
        if (compare(arr[parent], arr[position])) {
            GraphEdge* temp = arr[position];
            arr[position] = arr[parent];
            arr[parent] = temp;

            proclateUp(arr, parent, compare);
        }
    }
}

void heapify(GraphEdge* arr[], int size, int(* compare)(GraphEdge* , GraphEdge*)) {
    for (int i = size/2; i >= 0; i--)
        proclateDown(arr, i, size, compare);
}

GraphEdge* heapRemove(Heap *hp) {
    GraphEdge* value = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    proclateDown(hp->array, 0, hp->size, hp->compare);
    return value;
}

void heapAdd(Heap *hp, GraphEdge* value) {
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = value;
    proclateUp(hp->array, hp->size - 1, hp->compare);
}

int heapSize(Heap *hp) {
    return hp->size;
}