#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node;

typedef struct SPLAYTree {
	Node *root;
} SPLAYTree;

int find(SPLAYTree* tree, int data);
void insert(SPLAYTree* tree, int data);
void delete(SPLAYTree* tree, int data);
void printTree(SPLAYTree* tree);
void splay(SPLAYTree* tree, Node *node);

void printTreeUtil(Node *node, char* indent, int isLeft);
Node *rightRotate(Node *x); // Function to right rotate subtree rooted with x
Node *leftRotate(Node *x); // Function to left rotate subtree rooted with x
Node *getParent(Node *node);
Node *findMinNode(Node *curr);

Node* createNode(int d, Node *l, Node *r) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = d;
	node->left = l;
	node->right = r;
	node->parent = NULL;
	return node;
}

SPLAYTree* createSPLAYTree() {
	SPLAYTree* tree = (SPLAYTree*)malloc(sizeof(SPLAYTree));
	tree->root = NULL;
	return tree;
}

void printTreeUtil(Node *node, char* indent, int isLeft) {
	if (node == NULL)
		return;

	if (isLeft) {
		printf("%s%s", indent, "L:");
		strcat(indent, "|  ");
	} else {
		printf("%s%s", indent, "R:");
		strcat(indent, "   ");
	}

	printf("%d\n", node->data);
	printTreeUtil(node->left, indent, 1);
	printTreeUtil(node->right, indent, 0);
	indent[strlen(indent) - 3] = '\0';
}

void printTree(SPLAYTree* tree) {
	char indent[100] = "";
	printTreeUtil(tree->root, indent, 0);
	printf("\n");
}

// Function to right rotate subtree rooted with x
Node *rightRotate(Node *x) {
	Node *y = x->left;
	Node *T = y->right;

	// Rotation
	y->parent = x->parent;
	y->right = x;
	x->parent = y;
	x->left = T;
	if (T != NULL) {
		T->parent = x;
	}

	if (y->parent != NULL && y->parent->left == x) {
		y->parent->left = y;
	} else if (y->parent != NULL && y->parent->right == x) {
		y->parent->right = y;
	}
	// Return new root
	return y;
}

// Function to left rotate subtree rooted with x
Node *leftRotate(Node *x) {
	Node *y = x->right;
	Node *T = y->left;

	// Rotation
	y->parent = x->parent;
	y->left = x;
	x->parent = y;
	x->right = T;
	if (T != NULL) {
		T->parent = x;
	}

	if (y->parent != NULL && y->parent->left == x) {
		y->parent->left = y;
	} else if (y->parent != NULL && y->parent->right == x) {
		y->parent->right = y;
	}
	// Return new root
	return y;
}

Node *getParent(Node *node) {
	if (node == NULL || node->parent == NULL) {
		return NULL;
	}
	return node->parent;
}

void splay(SPLAYTree* tree, Node *node) {
	Node *parent, *grand;
	while (node != tree->root) {
		parent = getParent(node);
		grand = getParent(parent);
		if (parent == NULL) { // rotations had created new root, always last condition.
			tree->root = node;
		} else if (grand == NULL) { // single rotation case.
			if (parent->left == node) {
			   node = rightRotate(parent);
			} else {
				node = leftRotate(parent);
			}
		} else if (grand->left == parent && parent->left == node) { // Zig Zig case.
			rightRotate(grand);
			node = rightRotate(parent);
		} else if (grand->right == parent && parent->right == node) { // Zag Zag case.
			leftRotate(grand);
			node = leftRotate(parent);
		} else if (grand->left == parent && parent->right == node) { //Zig Zag case.
			leftRotate(parent);
			node = rightRotate(grand);
		} else if (grand->right == parent && parent->left == node) { // Zag Zig case.
			rightRotate(parent);
			node = leftRotate(grand);
		}
	}
}

int find(SPLAYTree* tree, int data) {
	Node *curr = tree->root;
	while (curr != NULL) {
		if (curr->data == data) {
			splay(tree, curr);
			return 1;
		} else if (curr->data > data)
			curr = curr->left;
		else
			curr = curr->right;
	}
	return 0;
}

void insert(SPLAYTree* tree, int data) {
	Node *newNode = createNode(data, NULL, NULL);
	if (tree->root == NULL) {
		tree->root = newNode;
		return;
	}

	Node *node = tree->root;
	Node *parent = NULL;
	while (node != NULL) {
		parent = node;
		if (node->data > data)
			node = node->left;
		else if (node->data < data)
			node = node->right;
		else {
			splay(tree, node); // duplicate insertion not allowed but splaying for it.
			return;
		}
	}

	newNode->parent = parent;
	if (parent->data > data)
		parent->left = newNode;
	else
		parent->right = newNode;

	splay(tree, newNode);
}

Node *findMinNode(Node *curr) {
	Node *node = curr;
	if (node == NULL)
		return NULL;
	
	while (node->left != NULL)
		node = node->left;

	return node;
}

void delete(SPLAYTree* tree, int data) {
	Node *node = tree->root;
	Node *parent = NULL;
	Node *next = NULL;
	while (node != NULL) {
		if (node->data == data) {
			parent = node->parent;
			if (node->left == NULL && node->right == NULL)
				next = NULL;
			else if (node->left == NULL)
				next = node->right;
			else if (node->right == NULL)
				next = node->left;

			if (node->left == NULL || node->right == NULL) {
				if (node == tree->root) {
					tree->root = next;
					return;
				}

				if (parent->left == node)
					parent->left = next;
				else
					parent->right = next;

				if (next != NULL)
					next->parent = parent;
				break;
			}

			Node *minNode = findMinNode(node->right);
			data = minNode->data; // new data to be deleted.
			node->data = data;			
			node = node->right;
		} else if (node->data > data) {
			parent = node;
			node = node->left;
		} else {
			parent = node;
			node = node->right;
		}
	}
	splay(tree, parent); // Splaying for the parent of the node deleted.
}

int main() {
	SPLAYTree *tree = createSPLAYTree();
	insert(tree, 5);
	insert(tree, 4);
	insert(tree, 6);
	insert(tree, 3);
	insert(tree, 2);
	insert(tree, 1);
	insert(tree, 3);
	printTree(tree);

	printf("Value 2 found: %d\n",  find(tree, 2));
	delete(tree, 2);
	delete(tree, 5);
	printTree(tree);
}

/*
R:3
   L:2
   |  L:1
   R:6
      L:4
      |  R:5

Value 2 found: 1
R:4
   L:3
   |  L:1
   R:6 
*/