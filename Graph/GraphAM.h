#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
    int count;
    int **adj;
} Graph;

typedef struct graphNode
{
    int src;
    int dest;
    int cost;
} GraphNode;

GraphNode* createGraphNode(int src, int dst, int cost){
    GraphNode *edge = (GraphNode *)malloc(sizeof(GraphNode));
    edge->src = src;
    edge->dest = dst;
    edge->cost = cost;
    return edge;
}

int greater(GraphNode* a, GraphNode* b) {
    return a->cost > b->cost;
}

int max(int first, int second) {
    return (first > second) ? first : second;
}

typedef struct Heap_t
{
    int capacity;
    int size;
    GraphNode**array;
    int(* compare)(GraphNode* , GraphNode*);
} Heap;

Heap* createHeap(int(* compare)(GraphNode* , GraphNode*))
{
    Heap* hp = (Heap*)malloc(sizeof(Heap));
    hp->size = 0;
    hp->capacity = 100;
    hp->array = (GraphNode **)malloc((hp->capacity) * sizeof(GraphNode));
    hp->compare = compare;
    return hp;
}

void proclateDown(GraphNode* arr[], int position, int size, int(* compare)(GraphNode* , GraphNode*))
{
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;
    int small = -1;

    if (lChild < size)
        small = lChild;

    if (rChild < size && compare(arr[lChild], arr[rChild]))
        small = rChild;

    if (small != -1 && compare(arr[position], arr[small]))
    {
        GraphNode* temp = arr[position];
        arr[position] = arr[small];
        arr[small] = temp;
        proclateDown(arr, small, size, compare);
    }
}

void proclateUp(GraphNode* arr[], int position, int(* compare)(GraphNode* , GraphNode*))
{
    int parent = (position - 1) / 2;
    if (parent >= 0)
    {
        if (compare(arr[parent], arr[position]))
        {
            GraphNode* temp = arr[position];
            arr[position] = arr[parent];
            arr[parent] = temp;

            proclateUp(arr, parent, compare);
        }
    }
}

void heapify(GraphNode* arr[], int size, int(* compare)(GraphNode* , GraphNode*))
{
    for (int i = size/2; i >= 0; i--)
        proclateDown(arr, i, size, compare);
}

GraphNode* heapRemove(Heap *hp)
{
    GraphNode* value = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    proclateDown(hp->array, 0, hp->size, hp->compare);
    return value;
}

void heapAdd(Heap *hp, GraphNode* value)
{
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = value;
    proclateUp(hp->array, hp->size - 1, hp->compare);
}

int heapSize(Heap *hp)
{
    return hp->size;
}
