#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	int height;
}Node;

Node* createNode(int d, Node* l, Node* r) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = d;
	node->left = l;
	node->right = r;
	node->height = 0;
	return node;
}

typedef struct AVLTree {
	Node* root;
} AVLTree;

AVLTree*  createAVLTree() {
	AVLTree* tree = (AVLTree*) malloc (sizeof(AVLTree));
	tree->root = NULL;
	return tree;
}

void insert(AVLTree* tree, int data);
Node* insertUtil(Node* node, int data);
void delete(AVLTree* tree, int data);
Node* deleteUtil(Node* node, int data);
void printTree(AVLTree* tree);
void printTreeUtil(Node* node, char* indent, int isLeft);
int max(int a, int b);
Node* rightRotate(Node* x); 
Node* leftRotate(Node* x); 
Node* rightLeftRotate(Node* x); 
Node* leftRightRotate(Node* x);
Node* findMin(Node* curr);
int height(Node* n);
int getBalance(Node* node);


int height(Node* n) {
	if (n == NULL)
		return -1;

	return n->height;
}

int getBalance(Node* node) {
	return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

int max(int x, int y) {
	if (x > y)
		return x;
	return y;
}

void insert(AVLTree* tree, int data) {
	tree->root = insertUtil(tree->root, data);
}

Node* insertUtil(Node* node, int data) {
	if (node == NULL)
		return createNode(data, NULL, NULL);

	if (node->data > data)
		node->left = insertUtil(node->left, data);
	else if (node->data < data)
		node->right = insertUtil(node->right, data);
	else
		return node; // Duplicate data not allowed

	node->height = max(height(node->left), height(node->right)) + 1;
	int balance = getBalance(node);

	if (balance > 1) {
		if (data < node->left->data) // Left Left Case
			return rightRotate(node);
		
		if (data > node->left->data) // Left Right Case
			return leftRightRotate(node);
	}

	if (balance < -1) {
		if (data > node->right->data) // Right Right Case
			return leftRotate(node);

		if (data < node->right->data) // Right Left Case
			return rightLeftRotate(node);
	}
	return node;
}

// Function to right rotate subtree rooted with x
Node* rightRotate(Node* x) {
	Node* y = x->left;
	Node* T = y->right;

	// Rotation
	y->right = x;
	x->left = T;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}

// Function to left rotate subtree rooted with x
Node* leftRotate(Node* x) {
	Node* y = x->right;
	Node* T = y->left;

	// Rotation
	y->left = x;
	x->right = T;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}

// Function to right then left rotate subtree rooted with x
Node* rightLeftRotate(Node* x) {
	x->right = rightRotate(x->right);
	return leftRotate(x);
}

// Function to left then right rotate subtree rooted with x
Node* leftRightRotate(Node* x) {
	x->left = leftRotate(x->left);
	return rightRotate(x);
}
Node* findMin(Node* curr) {
    Node* node = curr;
    if (node == NULL)
        return NULL;
    while (node->left != NULL)
        node = node->left;
    return node;
}

void delete(AVLTree* tree, int data) {
	tree->root = deleteUtil(tree->root, data);
}

Node* deleteUtil(Node* node, int data) {
	if (node == NULL)
		return NULL;

	if (node->data == data) {
		if (node->left == NULL && node->right == NULL)
			return NULL;
		else if (node->left == NULL)
			return node->right; // no need to modify height
		else if (node->right == NULL)
			return node->left; // no need to modify height
		else
		{
			Node* minNode = findMin(node->right);
			node->data = minNode->data;
			node->right = deleteUtil(node->right, minNode->data);
		}
	} else {
		if (node->data > data)
			node->left = deleteUtil(node->left, data);
		else
			node->right = deleteUtil(node->right, data);
	}

	node->height = max(height(node->left), height(node->right)) + 1;
	int balance = getBalance(node);

	if (balance > 1) {
		if (data >= node->left->data) // Left Left Case
			return rightRotate(node);

		if (data < node->left->data) // Left Right Case
			return leftRightRotate(node);
	}

	if (balance < -1) {
		if (data <= node->right->data) // Right Right Case
			return leftRotate(node);
		
		if (data > node->right->data) // Right Left Case
			return rightLeftRotate(node);
	}
	return node;
}


void printTreeUtil(Node* node, char* indent, int isLeft) {
	if (node == NULL)
		return;

	if (isLeft) {
		printf("%s%s", indent, "L:");
		strcat(indent, "|  ");
	} else {
		printf("%s%s", indent, "R:");
		strcat(indent, "   ");
	}

	printf("%d(%d)\n", node->data, node->height);
	printTreeUtil(node->left, indent, 1);
	printTreeUtil(node->right, indent,  0);
	indent[strlen(indent) - 3] = '\0';
}

void printTree(AVLTree* tree) {
	char str[100] = "";
	printTreeUtil(tree->root, str,  0);
	printf("\n");
}

int main() {
	AVLTree *tree = createAVLTree();
	insert(tree, 1);
	insert(tree, 2);
	insert(tree, 3);
	insert(tree, 4);
	insert(tree, 5);
	insert(tree, 6);
	insert(tree, 7);
	insert(tree, 8);
	printTree(tree);

	delete(tree, 5);
	printTree(tree);

	delete(tree, 1);
	printTree(tree);

	delete(tree, 2);
	printTree(tree);
}

/*
R:4(3)
   L:2(1)
   |  L:1(0)
   |  R:3(0)
   R:6(2)
      L:5(0)
      R:7(1)
         R:8(0)

R:4(2)
   L:2(1)
   |  L:1(0)
   |  R:3(0)
   R:7(1)
      L:6(0)
      R:8(0)

R:4(2)
   L:2(1)
   |  R:3(0)
   R:7(1)
      L:6(0)
      R:8(0)

R:4(2)
   L:3(0)
   R:7(1)
      L:6(0)
      R:8(0)
*/
