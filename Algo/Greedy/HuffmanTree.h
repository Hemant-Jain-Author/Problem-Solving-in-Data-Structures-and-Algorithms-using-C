#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char c;
	int freq;
	struct Node *left;
	struct Node *right;
} Node;

typedef struct HuffmanTree {
	Node *root;
}HuffmanTree;

typedef struct Heap {
    int capacity;
    int size;
    Node**array;
    int(* compare)(Node* , Node*);
} Heap;

void proclateDown(Node* arr[], int position, int size, int(* compare)(Node* , Node*)) {
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;
    int small = -1;

    if (lChild < size)
        small = lChild;

    if (rChild < size && compare(arr[lChild], arr[rChild]))
        small = rChild;

    if (small != -1 && compare(arr[position], arr[small])) {
        Node* temp = arr[position];
        arr[position] = arr[small];
        arr[small] = temp;
        proclateDown(arr, small, size, compare);
    }
}

void proclateUp(Node* arr[], int position, int(* compare)(Node* , Node*)) {
    int parent = (position - 1) / 2;
    if (parent >= 0) {
        if (compare(arr[parent], arr[position])) {
            Node* temp = arr[position];
            arr[position] = arr[parent];
            arr[parent] = temp;

            proclateUp(arr, parent, compare);
        }
    }
}

void heapify(Node* arr[], int size, int(* compare)(Node* , Node*)) {
    for (int i = size/2; i >= 0; i--)
        proclateDown(arr, i, size, compare);
}

Node* heapRemove(Heap *hp) {
    Node* value = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    proclateDown(hp->array, 0, hp->size, hp->compare);
    return value;
}

void heapAdd(Heap *hp, Node* value) {
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = value;
    proclateUp(hp->array, hp->size - 1, hp->compare);
}

Heap* createHeap2(Node* arr[], int size, int(* compare)(Node* , Node*)) {
    Heap* hp = (Heap*)malloc(sizeof(Heap));
    hp->size = hp->capacity = size;
    hp->array = arr;
    hp->compare = compare;
    heapify(arr, size, compare);
    return hp;
}

Heap* createHeap(int(* compare)(Node* , Node*)) {
    Heap* hp = (Heap*)malloc(sizeof(Heap));
    hp->size = 0;
    hp->capacity = 100;
    hp->array = (Node **)malloc((hp->capacity) * sizeof(Node));
    hp->compare = compare;
    return hp;
}

int heapSize(Heap *hp) {
    return hp->size;
}
