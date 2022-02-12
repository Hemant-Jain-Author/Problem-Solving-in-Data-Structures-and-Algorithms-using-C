
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node_t {
	int n; // Current number of keys
	int* keys; // An array of keys
	struct Node_t** arr; // An array of child pointers
	int leaf; // Is true when node is leaf. Otherwise false
} Node;

Node* createNode(int leaf, int max) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->n = 0;
	node->keys = (int*)malloc(max * sizeof(int));
	node->arr = (Node**)malloc((max + 1) * sizeof(Node*));
	node->leaf = leaf;
	return node;
}

typedef struct BTree_t {
	Node *root; // Pointer to root node
	int max; // Maximum degree
	int min; // Minimum degree
} BTree;

BTree* createBTree(int dg) {
	BTree* tree = (BTree*)malloc(sizeof(BTree)); 
	tree->root = NULL;
	tree->max = dg; // Max number of children.
	tree->min = dg / 2; // Min number of children.
	return tree;
}

BTree* createBTree(int dg);
void printTree(BTree* tree);
void insert(BTree* tree, int key);
void delete(BTree* tree, int key);
int search(BTree* tree, int key);

void printTreeUtil(Node *node, char* indent);
int searchUtil(Node *node, int key);
// Insert a new key in this node, Arguments are parent, child, index of child and key.
void insertUtil(Node *parent, Node *child, int index, int key, int max);
void split(Node *parent, Node *child, int index, int max);
void deleteUtil(Node *node, int key, int min);
// Returns the index of first key which is greater than or equal to key.
int findKey(Node *node, int key);
// delete the index key from leaf node.
void deleteFromLeaf(Node *node, int index);
// delete the index key from a non-leaf node.
void deleteFromNonLeaf(Node *node, int index, int min);
// To get predecessor of keys[index]
int getPred(Node *node, int index);
// To get successor of keys[index]
int getSucc(Node *node, int index);
// Make sure that the node have at least min number of keys
void fixBTree(Node *node, int index, int min);
// Move a key from parent to right and left to parent.
void borrowFromLeft(Node *node, int index);
// Move a key from parent to left and right to parent.
void borrowFromRight(Node *node, int index);
// Merge node's children at index and index+1.
void merge(Node *node, int index);


void printTreeUtil(Node *node, char* indent) {
	if (node == NULL)
		return;

	int i;
	for (i = 0; i < node->n; i++) {
		strcat(indent, "    ");
		printTreeUtil(node->arr[i], indent);
		indent[strlen(indent) - 4] = '\0';
		printf("%skey[%d]:%d\n", indent,  i, node->keys[i]);
	}
	strcat(indent, "    ");
	printTreeUtil(node->arr[i], indent);
	indent[strlen(indent) - 4] = '\0';
}

void printTree(BTree* tree) {
	char str[100] = "";
	printTreeUtil(tree->root, str);
	printf("\n");
}

int search(BTree* tree, int key) {
	if (tree->root == NULL)
		return 0;

	return searchUtil(tree->root, key);
}

int searchUtil(Node *node, int key) {
	int i = 0;
	while (i < node->n && node->keys[i] < key)
		i++;

	// If the found key is equal to key, return this node
	if (node->keys[i] == key)
		return 1;

	// If the key is not found and this is a leaf node
	if (node->leaf == 1)
		return 0;

	// Search in the appropriate child
	return searchUtil(node->arr[i], key);
}

void insert(BTree* tree, int key) {
	// If tree is empty
	if (tree->root == NULL) {
		// Allocate memory for root
		tree->root = createNode( 1, tree->max);
		tree->root->keys[0] = key; // Insert key
		tree->root->n = 1; // Update number of keys in root
		return;
	}

	if (tree->root->leaf == 1) {
		// Finds the location where new key can be inserted.
		// By moving all keys greater than key to one place forward.
		int i = tree->root->n - 1;
		while (i >= 0 && tree->root->keys[i] > key) {
			tree->root->keys[i + 1] = tree->root->keys[i];
			i--;
		}

		// Insert the new key at found location
		tree->root->keys[i + 1] = key;
		tree->root->n = tree->root->n + 1;
	} else {
		int i = 0;
		while (i < tree->root->n && tree->root->keys[i] < key)
			i++;
	
		insertUtil(tree->root, tree->root->arr[i], i, key, tree->max);
	}
	if (tree->root->n == tree->max) {
		// If root contains more then allowed nodes, then tree grows in height.
		// Allocate memory for new root
		Node *rt = createNode( 0, tree->max);
		rt->arr[0] = tree->root;
		split(rt, tree->root, 0, tree->max); // divide the child into two and then add the median to the parent.
		tree->root = rt;
	}
}

void insertUtil(Node *parent, Node *child, int index, int key, int max) {
	if (child->leaf == 1) {
		// Finds the location where new key will be inserted 
		// by moving all keys greater than key to one place forward.
		int i = child->n - 1;
		while (i >= 0 && child->keys[i] > key) {
			child->keys[i + 1] = child->keys[i];
			i--;
		}

		// Insert the new key at found location
		child->keys[i + 1] = key;
		child->n += 1;
	} else {
		int i = 0;
		// insert the node to the proper child.
		while (i < child->n && child->keys[i] < key) {
			i++;
		}
		insertUtil(child, child->arr[i], i, key, max); // parent, child and index of child.
	}

	if (child->n == max) // More nodes than allowed.
	{
		// divide the child into two and then add the median to the parent.
		split(parent, child, index, max);
	}
}

void split(Node *parent, Node *child, int index, int max) {
	// Getting index of median.
	int median = max / 2;
	// Reduce the number of keys in child
	child->n = median;

	Node *node = createNode(child->leaf, max);
	// Copy the second half keys of child to node
	int j = 0;
	while (median + 1 + j < max) {
		node->keys[j] = child->keys[median + 1 + j];
		j++;
	}
	node->n = j;

	// Copy the second half children of child to node
	j = 0;
	while (child->leaf == 0 && median + j <= max - 1) {
		node->arr[j] = child->arr[median + 1 + j];
		j++;
	}

	// parent is going to have a new child,
	// create space of new child
	for (j = parent->n; j >= index + 1; j--) {
		parent->arr[j + 1] = parent->arr[j];
	}

	// Link the new child to the parent node
	parent->arr[index + 1] = node;

	// A key of child will move to the parent node. 
	// Find the location of new key by moving
	// all greater keys one space forward.
	for (j = parent->n - 1; j >= index; j--) {
		parent->keys[j + 1] = parent->keys[j];
	}

	// Copy the middle key of child to the parent
	parent->keys[index] = child->keys[median];

	// Increment count of keys in this parent
	parent->n += 1;
}

void delete(BTree* tree, int key) {
	deleteUtil(tree->root, key, tree->min);

	if (tree->root->n == 0) {
		// Shrinking : If root is pointing to empty node.
		// If that node is a leaf node then root will become null.
		// Else root will point to first child of node.
		if (tree->root->leaf) {
			tree->root = NULL;
		} else {
			tree->root = tree->root->arr[0];
		}
	}
}

void deleteUtil(Node *node, int key, int min) {
	int index = findKey(node, key);
	if (node->leaf) {
		if (index < node->n && node->keys[index] == key) {
			deleteFromLeaf(node, index); // Leaf node key found.
		} else {
			printf("The key %d not found.\n", key);
			return;
		}
	} else {
		if (index < node->n && node->keys[index] == key) {
			deleteFromNonLeaf(node, index, min); // Internal node key found.
		} else {
			deleteUtil(node->arr[index], key, min);
		}

		// All the property violation in index subtree only.
		// which include delete from leaf case too.
		if (node->arr[index]->n < min) {
			fixBTree(node, index, min);
		}
	}
}

int findKey(Node *node, int key) {
	int index = 0;
	while (index < node->n && node->keys[index] < key)
		index++;

	return index;
}

void deleteFromLeaf(Node *node, int index) {
	// Move all the keys after the index position one step left.
	for (int i = index + 1; i < node->n; ++i)
		node->keys[i - 1] = node->keys[i];

	// Reduce the key count.
	node->n--;
	return;
}

void deleteFromNonLeaf(Node *node, int index, int min) {
	int key = node->keys[index];

	// If the child that precedes key has at least min keys,
	// Find the predecessor 'pred' of key in the subtree rooted at index.
	// Replace key by pred and recursively delete pred in arr[index]
	if (node->arr[index]->n > min) {
		int pred = getPred(node, index);
		node->keys[index] = pred;
		deleteUtil(node->arr[index], pred, min);
	}

	// If the child that succeeds key has at least min keys,
	// Find the successor 'succ' of key in the subtree rooted at index+1.
	// Replace key by succ and recursively delete succ in arr[ index+1].
	else if (node->arr[index + 1]->n > min) {
		int succ = getSucc(node, index);
		node->keys[index] = succ;
		deleteUtil(node->arr[index + 1], succ, min);
	}

	// If both left and right subtree has min number of keys.
	// Then merge left, right child along with parent key.
	// Then call delete on the merged child.
	else {
		merge(node, index);
		deleteUtil(node->arr[index], key, min);
	}
	return;
}

int getPred(Node *node, int index) {
	// Keep moving to the right most node of left subtree until we reach a leaf.
	Node *cur = node->arr[index];
	while (!cur->leaf)
		cur = cur->arr[cur->n];

	// Return the last key of the leaf
	return cur->keys[cur->n - 1];
}

int getSucc(Node *node, int index) {
	// Keep moving to the left most node of right subtree until we reach a leaf
	Node *cur = node->arr[index + 1];
	while (!cur->leaf)
		cur = cur->arr[0];

	// Return the first key of the leaf
	return cur->keys[0];
}

void fixBTree(Node *node, int index, int min) {
	// If the left sibling has more than min keys.
	if (index != 0 && node->arr[index - 1]->n > min)
		borrowFromLeft(node, index);
	// If the right sibling has more than min keys.
	else if (index != node->n && node->arr[index + 1]->n > min)
		borrowFromRight(node, index);
	// If both siblings has less than min keys.
	// When right sibling exist always merge with the right sibling.
	// When right sibling does not exist then merge with left sibling.
	else {
		if (index != node->n) {
			merge(node, index);
		} else {
			merge(node, index - 1);
		}
	}
}

void borrowFromLeft(Node *node, int index) {
	Node *child = node->arr[index];
	Node *sibling = node->arr[index - 1];

	// Moving all key in child one step forward.
	for (int i = child->n - 1; i >= 0; i--)
		child->keys[i + 1] = child->keys[i];

	// Move all its child pointers one step forward.
	for (int i = child->n; !child->leaf && i >= 0; i--)
		child->arr[i + 1] = child->arr[i];

	// Setting child's first key equal to of the current node.
	child->keys[0] = node->keys[index - 1];

	// Moving sibling's last child as child's first child.
	if (!child->leaf)
		child->arr[0] = sibling->arr[sibling->n];

	// Moving the key from the sibling to the parent
	node->keys[index - 1] = sibling->keys[sibling->n - 1];

	// Increase child key count and decrease sibling key count.
	child->n += 1;
	sibling->n -= 1;
	return;
}

void borrowFromRight(Node *node, int index) {
	Node *child = node->arr[index];
	Node *sibling = node->arr[index + 1];

	// node key is inserted as the last key in child.
	child->keys[child->n] = node->keys[index];

	// Sibling's first child is inserted as the last child of child.
	if (!(child->leaf))
		child->arr[(child->n) + 1] = sibling->arr[0];

	//First key from sibling is inserted into node.
	node->keys[index] = sibling->keys[0];

	// Moving all keys in sibling one step left
	for (int i = 1; i < sibling->n; ++i)
		sibling->keys[i - 1] = sibling->keys[i];

	// Moving the child pointers one step behind
	for (int i = 1; !sibling->leaf && i <= sibling->n; ++i)
		sibling->arr[i - 1] = sibling->arr[i];

	// Increase child key count and decrease sibling key count.
	child->n += 1;
	sibling->n -= 1;
	return;
}

void merge(Node *node, int index) {
	Node *left = node->arr[index];
	Node *right = node->arr[index + 1];
	int start = left->n;
	// Adding a key from node to the left child.
	left->keys[start] = node->keys[index];

	// Copying the keys from right to left.
	for (int i = 0; i < right->n; ++i)
		left->keys[start + 1 + i] = right->keys[i];

	// Copying the child pointers from right to left.
	for (int i = 0; !left->leaf && i <= right->n; ++i)
		left->arr[start + 1 + i] = right->arr[i];

	// Moving all keys after  index in the current node one step forward.
	for (int i = index + 1; i < node->n; ++i)
		node->keys[i - 1] = node->keys[i];

	// Moving the child pointers after (index+1) in the current node one step forward.
	for (int i = index + 2; i <= node->n; ++i)
		node->arr[i - 1] = node->arr[i];

	// Updating the key count of child and the current node
	left->n += right->n + 1;
	node->n--;
	return;
}

int main() {
	BTree* tree = createBTree(3); // A B-Tree with max key 3
	insert(tree, 1);
	insert(tree, 2);
	insert(tree, 3);
	insert(tree, 4);
	insert(tree, 5);
	insert(tree, 6);
	insert(tree, 7);
	insert(tree, 8);
	insert(tree, 9);
	insert(tree, 10);
	printTree(tree);
	
	printf("6 found: %d\n", search(tree, 6));
	printf("11 found: %d\n", search(tree, 11));

	delete(tree, 6);
	delete(tree, 3);
	delete(tree, 7);
	printTree(tree);
}

/*
        key[0]:1
    key[0]:2
        key[0]:3
key[0]:4
        key[0]:5
    key[0]:6
        key[0]:7
    key[1]:8
        key[0]:9
        key[1]:10

6 found: 1
11 found: 0

    key[0]:1
    key[1]:2
key[0]:4
    key[0]:5
key[1]:8
    key[0]:9
    key[1]:10
*/
