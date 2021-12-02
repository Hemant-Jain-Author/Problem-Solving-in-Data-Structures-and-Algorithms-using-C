#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node_t
{
	int data;
	struct Node_t* left;
	struct Node_t* right;
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

typedef struct AVLTree_t
{
	Node* root;
}AVLTree;

AVLTree*  createAVLTree() {
	AVLTree* tree = (AVLTree*) malloc (sizeof(AVLTree));
	tree->root = NULL;
	return tree;
}

void insertData(AVLTree* tree, int data);
Node* insertDataUtil(Node* node, int data);
void deleteData(AVLTree* tree, int data);
Node* deleteDataUtil(Node* node, int data);
void printTree(AVLTree* tree);
void printTreeUtil(Node* node, char* indent, int isLeft);
int max(int a, int b);
Node* rightRotate(Node* x); // Function to right rotate subtree rooted with x
Node* leftRotate(Node* x); // Function to left rotate subtree rooted with x
Node* rightLeftRotate(Node* x); // Function to right then left rotate subtree rooted with x
Node* leftRightRotate(Node* x); // Function to left then right rotate subtree rooted with x
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

void insertData(AVLTree* tree, int data) {
	tree->root = insertDataUtil(tree->root, data);
}

Node* insertDataUtil(Node* node, int data) {
	if (node == NULL)
		return createNode(data, NULL, NULL);

	if (node->data > data)
		node->left = insertDataUtil(node->left, data);
	else if (node->data < data)
		node->right = insertDataUtil(node->right, data);
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

Node* rightLeftRotate(Node* x) {
	x->right = rightRotate(x->right);
	return leftRotate(x);
}

Node* leftRightRotate(Node* x) {
	x->left = leftRotate(x->left);
	return rightRotate(x);
}

void deleteData(AVLTree* tree, int data) {
	tree->root = deleteDataUtil(tree->root, data);
}

Node* deleteDataUtil(Node* node, int data) {
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
			node->right = deleteDataUtil(node->right, minNode->data);
		}
	}
	else
	{
		if (node->data > data)
			node->left = deleteDataUtil(node->left, data);
		else
			node->right = deleteDataUtil(node->right, data);
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

Node* findMin(Node* curr) {
	Node* node = curr;
	if (node == NULL)
		return NULL;

	while (node->left != NULL)
		node = node->left;
	
	return node;
}

void printTree(AVLTree* tree) {
	char str[100] = "";
	printTreeUtil(tree->root, str,  0);
	printf("\n");
}

void printTreeUtil(Node* node, char* indent, int isLeft) {
	if (node == NULL)
		return;

	if (isLeft) {
		printf("%s%s", indent, "L:");
		strcat(indent, "|  ");
	}
	else
	{
		printf("%s%s", indent, "R:");
		strcat(indent, "   ");
	}

	printf("%d(%d)\n", node->data, node->height);
	printTreeUtil(node->left, indent, 1);
	printTreeUtil(node->right, indent,  0);
	indent[strlen(indent) - 3] = '\0';
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	AVLTree *tree = createAVLTree();
	insertData(tree, 1);
	insertData(tree, 2);
	insertData(tree, 3);
	insertData(tree, 4);
	insertData(tree, 5);
	insertData(tree, 6);
	insertData(tree, 7);
	insertData(tree, 8);
	printTree(tree);

	deleteData(tree, 5);
	printTree(tree);

	deleteData(tree, 1);
	printTree(tree);

	deleteData(tree, 2);
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
