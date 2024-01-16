#include "HuffmanTree.h"

Node* createNode(char ch, int fr, Node *l, Node *r) {
	Node *nd = (Node*)malloc(sizeof(Node));
	nd->c = ch;
	nd->freq = fr;
	nd->left = l;
	nd->right = r;
	return nd;
}

int greater(Node *n1, Node *n2) {
	return n1->freq > n2->freq;
}

HuffmanTree* createHuffmanTree(char arr[], int freq[], int n) {
	HuffmanTree* tree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
	Heap* hp = createHeap(greater);
	for (int i = 0; i < n; i++) {
		Node *node = createNode(arr[i], freq[i], NULL, NULL);
		heapAdd(hp, node);
	}

	while (heapSize(hp) > 1) {
		Node *lt = heapRemove(hp);
		Node *rt = heapRemove(hp);
		Node *nd = createNode('+', lt->freq + rt->freq, lt, rt);
		heapAdd(hp, nd);
	}
	tree->root = heapRemove(hp);
	return tree;
}

void printHuffmanTreeUtil(Node* root, char* s) {
	if (root->left == NULL && root->right == NULL && root->c != '+') {
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