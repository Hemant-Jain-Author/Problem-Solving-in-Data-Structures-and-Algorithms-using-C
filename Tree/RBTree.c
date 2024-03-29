#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	struct Node *left, *right, *parent, *nullNode;
	int data;
	int colour; // true for red colour, false for black colour
} Node;

typedef struct RBTree {
	Node *root;
	Node *nullNode;
}RBTree;

void printTree(RBTree* tree);
void printTreeUtil(RBTree* tree, Node *node, char* indent, int isLeft);

void insert(RBTree* tree, int data);
Node *insertUtil(RBTree* tree, Node *node, int data);

void delete(RBTree* tree, int data);
void deleteUtil(RBTree* tree, Node *node, int key);

Node * find(RBTree *tree, int data);

int isRed(Node *node); // To check whether node is of colour red or not.
Node *getUncle(RBTree* tree, Node *node);
Node *rightRotate(RBTree* tree, Node *x); // Function to right rotate subtree rooted with x
Node *leftRotate(RBTree* tree, Node *x); // Function to left rotate subtree rooted with x
Node *rightLeftRotate(RBTree* tree, Node *node);
Node *leftRightRotate(RBTree* tree, Node *node);
void fixRedRed(RBTree* tree, Node *x);
void fixDoubleBlack(RBTree* tree, Node *x);
Node *getSibling(RBTree* tree, Node *node);
void joinParentChild(RBTree* tree, Node *u, Node *v);
Node *minimum(RBTree* tree, Node *node);

Node* createNode(int data, Node *nullNode) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->left = nullNode;
	node->right = nullNode;
	node->colour = 1; // New node are red in colour.
	node->parent = nullNode;
	node->nullNode = nullNode; // used only in delete to prevent double delete.
	return node;
}

RBTree* createRBTree() {
	RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
	tree->nullNode = createNode(0, NULL);
	tree->nullNode->colour = 0;
	tree->root = tree->nullNode;
	return tree;
}

// To check whether node is of colour red or not.
int isRed(Node *node) {
	return (node == NULL) ? 0 : (node->colour == 1);
}

Node *getUncle(RBTree* tree, Node *node) {
	// If no parent or grandparent, then no uncle
	if (node->parent == tree->nullNode || node->parent->parent == tree->nullNode)
		return NULL;

	if (node->parent == node->parent->parent->left) // uncle on right
		return node->parent->parent->right;
	else // uncle on left
		return node->parent->parent->left;
}

// Function to right rotate subtree rooted with x
Node *rightRotate(RBTree* tree, Node *x) {
	Node *y = x->left;
	Node *T = y->right;

	// Rotation
	y->parent = x->parent;
	y->right = x;
	x->parent = y;
	x->left = T;

	if (T != tree->nullNode)
		T->parent = x;

	if (x == tree->root) {
		tree->root = y;
		return y;
	}

	if (y->parent->left == x)
		y->parent->left = y;
	else
		y->parent->right = y;

	return y; // Return new root
}

// Function to left rotate subtree rooted with x
Node *leftRotate(RBTree* tree, Node *x) {
	Node *y = x->right;
	Node *T = y->left;

	// Rotation
	y->parent = x->parent;
	y->left = x;
	x->parent = y;
	x->right = T;

	if (T != tree->nullNode)
		T->parent = x;

	if (x == tree->root) {
		tree->root = y;
		return y;
	}

	if (y->parent->left == x)
		y->parent->left = y;
	else
		y->parent->right = y;
	
	return y; // Return new root
}

Node *rightLeftRotate(RBTree* tree, Node *node) {
	node->right = rightRotate(tree, node->right);
	return leftRotate(tree, node);
}

Node *leftRightRotate(RBTree* tree, Node *node) {
	node->left = leftRotate(tree, node->left);
	return rightRotate(tree, node);
}

Node * find(RBTree *tree, int data) {
	Node *curr = tree->root;
	while (curr != tree->nullNode) {
		if (curr->data == data)
			return curr;
		else if (curr->data > data)
			curr = curr->left;
		else
			curr = curr->right;
	}
	return NULL;
}

void printTreeUtil(RBTree* tree, Node *node, char* indent, int isLeft) {
	if (node == tree->nullNode)
		return;
	
	if (isLeft) {
		printf("%s%s", indent, "L:");
		strcat(indent, "|  ");
	} else {
		printf("%s%s", indent, "R:");
		strcat(indent, "   ");
	}

	printf("%d(%d)\n", node->data, node->colour);
	printTreeUtil(tree, node->left, indent, 1);
	printTreeUtil(tree, node->right, indent, 0);
	indent[strlen(indent) - 3] = '\0';
}
void printTree(RBTree *tree) {
	char indent[100] = "";
	printTreeUtil(tree, tree->root, indent, 0);
	printf("\n");
}
void insert(RBTree *tree, int data) {
	tree->root = insertUtil(tree, tree->root, data);
	Node *temp = find(tree, data);
	fixRedRed(tree, temp);
}

Node *insertUtil(RBTree* tree, Node *node, int data) {
	if (node == tree->nullNode) {
		node = createNode(data, tree->nullNode);
	}
	else if (node->data > data) {
		node->left = insertUtil(tree, node->left, data);
		node->left->parent = node;
	}
	else if (node->data < data) {
		node->right = insertUtil(tree, node->right, data);
		node->right->parent = node;
	}
	return node;
}

void fixRedRed(RBTree* tree, Node *x) {
	// if x is root colour it black and return
	if (x == tree->root) {
		x->colour = 0;
		return;
	}

	if (x->parent == tree->nullNode || x->parent->parent == tree->nullNode) {
		return;
	}
	// Initialize parent, grandparent, uncle
	Node *parent = x->parent, *grandparent = parent->parent, *uncle = getUncle(tree, x);
	Node *mid = NULL;

	if (parent->colour == 0) {
		return;
	}

	// parent colour is red. gp is black.
	if (uncle != tree->nullNode && uncle->colour == 1) {
		// uncle and parent is red.
		parent->colour = 0;
		uncle->colour = 0;
		grandparent->colour = 1;
		fixRedRed(tree, grandparent);
		return;
	}

	// parent is red, uncle is black and gp is black.
	// Perform LR, LL, RL, RR
	if (parent == grandparent->left && x == parent->left) // LL
	{
		mid = rightRotate(tree, grandparent);
	} 
	else if (parent == grandparent->left && x == parent->right) // LR
	{
		mid = leftRightRotate(tree, grandparent);
	} 
	else if (parent == grandparent->right && x == parent->left) // RL
	{
		mid = rightLeftRotate(tree, grandparent);
	} 
	else if (parent == grandparent->right && x == parent->right) // RR
	{
		mid = leftRotate(tree, grandparent);
	}

	mid->colour = 0;
	mid->left->colour = 1;
	mid->right->colour = 1;
}

void delete(RBTree *tree, int data) {
    deleteUtil(tree, tree->root, data);
}
void joinParentChild(RBTree* tree, Node *u, Node *v) {
    if (u->parent == tree->nullNode) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}
void deleteUtil(RBTree* tree, Node *node, int key) {
    Node *z = tree->nullNode;
    Node *x, *y;
    while (node != tree->nullNode) {
        if (node->data == key) {
            z = node;
            break;
        }
        else if (node->data <= key) {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }

    if (z == tree->nullNode) {
        printf("Couldn't find key in the tree\n");
        return;
    }

    y = z;
    int yColour = y->colour;

    if (z->left == tree->nullNode) {
        x = z->right;
        joinParentChild(tree, z, z->right);
    } else if (z->right == tree->nullNode) {
        x = z->left;
        joinParentChild(tree, z, z->left);
    } else {
        y = minimum(tree, z->right);
        yColour = y->colour;
        z->data = y->data;
        joinParentChild(tree, y, y->right);
        x = y->right;
    }

    if (yColour == 0) {
        if (x->colour == 1) {
            x->colour = 0;
            return;
        } else {
            fixDoubleBlack(tree, x);
        }
    }
}

Node* minimum(RBTree* tree, Node *node) {
	while (node->left != tree->nullNode) {
		node = node->left;
	}
	return node;
}


Node* getSibling(RBTree* tree, Node *node) {
	// sibling null if no parent
	if (node->parent == tree->nullNode) {
		return NULL;
	}

	if (node->parent->left == node) {
		return node->parent->right;
	}

	return node->parent->left;
}

void fixDoubleBlack(RBTree* tree, Node *x) {
	if (x == tree->root) // Root node.
		return;

	Node *sib = getSibling(tree, x);
	Node *parent = x->parent;
	if (sib == tree->nullNode) {
		// No sibling double black shifted to parent.
		fixDoubleBlack(tree, parent);
	} else {
		if (sib->colour == 1) {
			// Sibling colour is red.
			parent->colour = 1;
			sib->colour = 0;
			if (sib->parent->left == sib) {
				// Sibling is left child.
				rightRotate(tree, parent);
			} else {
				// Sibling is right child.
				leftRotate(tree, parent);
			}
			fixDoubleBlack(tree, x);
		} else {
			// Sibling colour is black
			// At least one child is red.
			if (sib->left->colour == 1 || sib->right->colour == 1) {
				if (sib->parent->left == sib) {
					// Sibling is left child.
					if (sib->left != tree->nullNode && sib->left->colour == 1) {
						// left left case.
						sib->left->colour = sib->colour;
						sib->colour = parent->colour;
						rightRotate(tree, parent);
					} else {
						// left right case.
						sib->right->colour = parent->colour;
						leftRotate(tree, sib);
						rightRotate(tree, parent);
					}
				} else {
					// Sibling is right child.
					if (sib->left != tree->nullNode && sib->left->colour == 1) {
						// right left case.
						sib->left->colour = parent->colour;
						rightRotate(tree, sib);
						leftRotate(tree, parent);
					} else {
						// right right case.
						sib->right->colour = sib->colour;
						sib->colour = parent->colour;
						leftRotate(tree, parent);
					}
				}
				parent->colour = 0;
			} else {
				// Both children black.
				sib->colour = 1;
				if (parent->colour == 0) {
					fixDoubleBlack(tree, parent);
				} else {
					parent->colour = 0;
				}
			}
		}
	}
}

void removeDataUtil(RBTree* tree, Node *node, int key) {
	Node *z = tree->nullNode;
	Node *x, *y;
	while (node != tree->nullNode) {
		if (node->data == key) {
			z = node;
			break;
		} else if (node->data <= key) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	if (z == tree->nullNode) {
		printf("Couldn't find key in the tree\n");
		return;
	}

	y = z;
	int yColour = y->colour;
	if (z->left == tree->nullNode) {
		x = z->right;
		joinParentChild(tree, z, z->right);
	} else if (z->right == tree->nullNode) {
		x = z->left;
		joinParentChild(tree, z, z->left);
	} else {
		y = minimum(tree, z->right);
		yColour = y->colour;
		z->data = y->data;
		joinParentChild(tree, y, y->right);
		x = y->right;
	}

	if (yColour == 0) {
		if (x->colour == 1) {
			x->colour = 0;
			return;
		} else {
			fixDoubleBlack(tree, x);
		}
	}
}

void removeData(RBTree *tree, int data) {
	removeDataUtil(tree, tree->root, data);
}

int main() {
	RBTree *tree = createRBTree();
	insert(tree, 1);
	insert(tree, 2);
	insert(tree, 3);
	insert(tree, 4);
	insert(tree, 5);
	insert(tree, 7);
	insert(tree, 6);
	insert(tree, 8);
	insert(tree, 9);
	printTree(tree);

	delete(tree, 4);
	printTree(tree);

	delete(tree, 7);
	printTree(tree);
}

/*
R:4(0)
   L:2(1)
   |  L:1(0)
   |  R:3(0)
   R:6(1)
      L:5(0)
      R:8(0)
         L:7(1)
         R:9(1)

R:5(0)
   L:2(1)
   |  L:1(0)
   |  R:3(0)
   R:7(1)
      L:6(0)
      R:8(0)
         R:9(1)

R:5(0)
   L:2(1)
   |  L:1(0)
   |  R:3(0)
   R:8(1)
      L:6(0)
      R:9(0)
*/