#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct SegmentTree_t
{
	int* segArr;
	int size;
}SegmentTree;

SegmentTree* createSegmentTree(int input[], int n);
int constructST(SegmentTree* tree, int input[], int start, int end, int index);

int getSum(SegmentTree* tree, int start, int end);
int getSumUtil(SegmentTree* tree, int segStart, int segEnd, int queryStart, int queryEnd, int index);

void set(SegmentTree* tree, int arr[], int ind, int val);
int setUtil(SegmentTree* tree, int segStart, int segEnd, int ind, int val, int index);


SegmentTree* createSegmentTree(int input[], int size) {
	SegmentTree* tree = (SegmentTree*)malloc(sizeof(SegmentTree));
	// Height of segment tree.
	int x = ceil(log(size)/log(2));
	//Maximum size of segment tree
	int maxSize = 2 * pow(2, x) - 1;
	// Allocate memory for segment tree
	tree->segArr = (int*) malloc(sizeof(int) *maxSize);
	tree->size = size;
	constructST(tree, input, 0, size - 1, 0);
	return tree;
}

int constructST(SegmentTree* tree, int input[], int start, int end, int index) {
	// Store it in current node of the segment tree and return
	if (start == end) {
		tree->segArr[index] = input[start];
		return input[start];
	}

	// If there are more than one elements, 
	// then traverse left and right subtrees 
	// and store the sum of values in current node.
	int mid = (start + end) / 2;
	tree->segArr[index] = constructST(tree, input, start, mid, index * 2 + 1) + 
						constructST(tree, input, mid + 1, end, index * 2 + 2);
	 return tree->segArr[index];
}

int getSum(SegmentTree* tree, int start, int end) {
	// Check for error conditions.
	if (start > end || start < 0 || end > tree->size - 1) {
		printf("Invalid Input.");
		return -1;
	}
	return getSumUtil(tree, 0, tree->size - 1, start, end, 0);
}

int getSumUtil(SegmentTree* tree, int segStart, int segEnd, int queryStart, int queryEnd, int index) {
	if (queryStart <= segStart && segEnd <= queryEnd) // complete overlapping case.
	{
		return tree->segArr[index];
	}

	if (segEnd < queryStart || queryEnd < segStart) // no overlapping case.
	{
		return 0;
	}

	// Segment tree is partly overlaps with the query range.
	int mid = (segStart + segEnd) / 2;
	return getSumUtil(tree, segStart, mid, queryStart, queryEnd, 2 * index + 1) + 
		getSumUtil(tree, mid + 1, segEnd, queryStart, queryEnd, 2 * index + 2);
}

void set(SegmentTree* tree, int arr[], int ind, int val) {
	// Check for error conditions.
	if (ind < 0 || ind > tree->size - 1) {
		printf("Invalid Input.");
		return;
	}

	arr[ind] = val;

	// Set new value in segment tree
	setUtil(tree, 0, tree->size - 1, ind, val, 0);
}

int setUtil(SegmentTree* tree, int segStart, int segEnd, int ind, int val, int index) {
	// set index lies outside the range of current segment.
	// So diff to its parent node will be zero.
	if (ind < segStart || ind > segEnd) {
		return 0;
	}

	// If the input index is in range of this node, then set the
	// value of the node and its children

	if (segStart == segEnd) {
		if (segStart == ind) { // Index that need to be set.
			int diff = val - tree->segArr[index];
			tree->segArr[index] = val;
			return diff;
		}
		else
		{
			return 0;
		}
	}

	int mid = (segStart + segEnd) / 2;
	int diff = setUtil(tree, segStart, mid, ind, val, 2 * index + 1) + 
	setUtil(tree, mid + 1, segEnd, ind, val, 2 * index + 2);

	// Current node value is set with diff. 
	tree->segArr[index] = tree->segArr[index] + diff;

	// Value of diff is propagated to the parent node.
	return diff;
}

int main() {
	int arr[] = {1, 2, 4, 8, 16, 32, 64};
	int n = 7;
	SegmentTree *tree = createSegmentTree(arr, n);
	printf("Sum of values in the range(0, 3): %d\n",  getSum(tree, 1, 3));
	printf("Sum of values of all the elements: %d\n",  getSum(tree, 0, n - 1));

	set(tree, arr, 1, 10);
	printf("Sum of values in the range(0, 3): %d\n",  getSum(tree, 1, 3));
	printf("Sum of values of all the elements: %d\n",  getSum(tree, 0, n - 1));
}

/*
Sum of values in the range(0, 3): 14
Sum of values of all the elements: 127
Sum of values in the range(0, 3): 22
Sum of values of all the elements: 135
*/