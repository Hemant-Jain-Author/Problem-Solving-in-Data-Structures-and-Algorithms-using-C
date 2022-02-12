#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_t {
	char c;
	int freq;
	struct Node_t *left;
	struct Node_t *right;
} Node;

typedef struct Heap_t {
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
        if (compare(arr[parent], arr[position])} {
            Node* temp = arr[position];
            arr[position] = arr[parent];
            arr[parent] = temp;

            proclateUp(arr, parent, compare);
        }
    }
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

int greater(Node *n1, Node *n2){
	return n1->freq > n2->freq;
}


typedef struct HuffmanTree_t {
	Node *root;
} HuffmanTree ;

Node* createNode(char ch, int fr, Node *l, Node *r) {
	Node *nd = (Node*)malloc(sizeof(Node));
	nd->c = ch;
	nd->freq = fr;
	nd->left = l;
	nd->right = r;
}

HuffmanTree* createHuffmanTree(char arr[], int freq[], int n) {
	HuffmanTree* tree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
	Heap* hp = createHeap(greater);
	for (int i = 0; i < n; i++) {
		Node *node = createNode(arr[i], freq[i], NULL, NULL);
		heapAdd(hp, node);
	}

	while (heapSize(hp) > 1} {
		Node *lt = heapRemove(hp);
		Node *rt = heapRemove(hp);
		Node *nd = createNode('+', lt->freq + rt->freq, lt, rt);
		heapAdd(hp, nd);
	}
	tree->root = heapRemove(hp);
	return tree;
}

void printHuffmanTreeUtil(Node* root, char* s) {
	if (root->left == NULL && root->right == NULL && root->c != '+'} {
		printf("%c  =  %s\n", root->c, s);
		return;
	}
	strcat(s, "0");
	printHuffmanTreeUtil(root->left, s);
	s[strlen(s)-1]='\0';
	strcat(s, "1");
	printHuffmanTreeUtil(root->right, s);
	s[strlen(s)-1]='\0';
}

void printHuffmanTree(HuffmanTree* tree) {
	printf("Char = Huffman code\n" );
	char str[100]="";
	printHuffmanTreeUtil(tree->root, str);
}

int main() {
	char ar[] = {'A', 'B', 'C', 'D', 'E'};
	int fr[] = {30, 25, 21, 14, 10};
	HuffmanTree* tree = createHuffmanTree(ar, fr, 5);
	printHuffmanTree(tree);
}

/*
Char = Huffman code
C = 00
E = 010
D = 011
B = 10
A = 11
*/