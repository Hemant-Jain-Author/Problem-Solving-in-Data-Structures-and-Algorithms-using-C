#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct RmqST {
	int* segArr;
	int n;
}RmqST;

int min(int a, int b) {
	return (a < b)? a : b;
}

int constructST(RmqST* tree, int input[], int start, int end, int index) {
	// Store it in current node of the segment tree and return
	if (start == end) {
		tree->segArr[index] = input[start];
		return input[start];
	}

	// If there are more than one elements, 
	// then traverse left and right subtrees 
	// and store the minimum of values in current node.
	int mid = (start + end) / 2;
	tree->segArr[index] = min(constructST(tree, input, start, mid, index * 2 + 1), 
						constructST(tree, input, mid + 1, end, index * 2 + 2));
	 return tree->segArr[index];
}

RmqST* createRmqST(int input[], int n) {
	RmqST* tree = (RmqST*)malloc(sizeof(RmqST));
	// Height of segment tree.
	int x = ceil(log(n)/log(2));
	//Maximum size of segment tree
	int maxSize = 2 * pow(2, x) - 1;
	// Allocate memory for segment tree
	tree->segArr = (int*) malloc(sizeof(int) *maxSize);
	tree->n = n;
	constructST(tree, input, 0, n - 1, 0);
	return tree;
}

int getMinUtil(RmqST* tree, int segStart, int segEnd, int queryStart, int queryEnd, int index) {
	if (queryStart <= segStart && segEnd <= queryEnd) // complete overlapping case.
	{
		return tree->segArr[index];
	}

	if (segEnd < queryStart || queryEnd < segStart) // no overlapping case.
	{
		return 99999;
	}

	// Segment tree is partly overlaps with the query range.
	int mid = (segStart + segEnd) / 2;
	return min(getMinUtil(tree, segStart, mid, queryStart, queryEnd, 2 * index + 1), 
				getMinUtil(tree, mid + 1, segEnd, queryStart, queryEnd, 2 * index + 2));
}

int getMin(RmqST* tree, int start, int end) {
	// Check for error conditions.
	if (start > end || start < 0 || end > tree->n - 1) {
		printf("Invalid Input.\n");
		return 99999;
	}
	return getMinUtil(tree, 0, tree->n - 1, start, end, 0);
}

int updateUtil(RmqST* tree, int segStart, int segEnd, int ind, int val, int index) {
	// Update index lies outside the range of current segment.
	// So minimum will not change.
	if (ind < segStart || ind > segEnd) {
		return tree->segArr[index];
	}

	// If the input index is in range of this node, then update the
	// value of the node and its children

	if (segStart == segEnd) {
		if (segStart == ind) { // Index value need to be updated.
			tree->segArr[index] = val;
			return val;
		} else {
			return tree->segArr[index]; // index value is not changed.
		}
	}

	int mid = (segStart + segEnd) / 2;

	// Current node value is updated with min. 
	tree->segArr[index] = min(updateUtil(tree, segStart, mid, ind, val, 2 * index + 1), 
							updateUtil(tree, mid + 1, segEnd, ind, val, 2 * index + 2));

	// Value of diff is propagated to the parent node.
	return tree->segArr[index];
}

void update(RmqST* tree, int ind, int val) {
	// Check for error conditions.
	if (ind < 0 || ind > tree->n - 1) {
		printf("Invalid Input.\n");
		return;
	}

	// Update the values in segment tree
	updateUtil(tree, 0, tree->n - 1, ind, val, 0);
}

int main() {
	int arr[] = {2, 3, 1, 7, 12, 5};
	int n = 6;
	RmqST *tree = createRmqST(arr, 6);
	printf("Min value in the range(1, 5): %d\n",  getMin(tree, 1, 5));
	printf("Min value of all the elements: %d\n",  getMin(tree, 0, n - 1));

	update(tree, 2, -1);
	printf("Min value in the range(1, 5): %d\n",  getMin(tree, 1, 5));
	printf("Min value of all the elements: %d\n",  getMin(tree, 0, n - 1));

	update(tree, 5, -2);
	printf("Min value in the range(0, 4): %d\n",  getMin(tree, 0, 4));
	printf("Min value of all the elements: %d\n",  getMin(tree, 0, n - 1));
}

/*
Min value in the range(1, 5): 1
Min value of all the elements: 1
Min value in the range(1, 5): -1
Min value of all the elements: -1
Min value in the range(0, 4): -1
Min value of all the elements: -2
*/
