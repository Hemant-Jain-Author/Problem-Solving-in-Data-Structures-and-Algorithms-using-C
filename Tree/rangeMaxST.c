#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct RangeMaxST_t
{
	int* segArr;
	int n;
}RangeMaxST;

RangeMaxST* createRangeMaxST(int input[], int n);
int constructST(RangeMaxST*  tree, int* input, int start, int end, int index);
int getMax(RangeMaxST*  tree, int start, int end);
void update(RangeMaxST*  tree, int ind, int val);
int getMaxUtil(RangeMaxST*  tree, int segStart, int segEnd, int queryStart, int queryEnd, int index);
int updateUtil(RangeMaxST*  tree, int segStart, int segEnd, int ind, int val, int index);
int max(int first, int second);

RangeMaxST* createRangeMaxST(int input[], int n) {
	RangeMaxST* tree = (RangeMaxST*)malloc(sizeof(RangeMaxST));
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

int constructST(RangeMaxST*  tree, int* input, int start, int end, int index) {
	// Store it in current node of the segment tree and return
	if (start == end) {
		tree->segArr[index] = input[start];
		return input[start];
	}

	// If there are more than one elements, 
	// then traverse left and right subtrees 
	// and store the minimum of values in current node.
	int mid = (start + end) / 2;
	tree->segArr[index] = max(constructST(tree, input, start, mid, index * 2 + 1), 
				constructST(tree, input, mid + 1, end, index * 2 + 2));
	 return tree->segArr[index];
}

int max(int first, int second) {
	return (first > second)? first :  second;
}

int getMax(RangeMaxST* tree, int start, int end) {
	// Check for error conditions.
	if (start > end || start < 0 || end > tree->n - 1) {
		printf("Invalid Input.\n");
		return -999999;
	}
	return getMaxUtil(tree, 0, tree->n - 1, start, end, 0);
}

int getMaxUtil(RangeMaxST* tree, int segStart, int segEnd, int queryStart, int queryEnd, int index) {
	if (queryStart <= segStart && segEnd <= queryEnd) // complete overlapping case.
	{
		return tree->segArr[index];
	}

	if (segEnd < queryStart || queryEnd < segStart) // no overlapping case.
	{
		return -999999;
	}

	// Segment tree is partly overlaps with the query range.
	int mid = (segStart + segEnd) / 2;
	return max(getMaxUtil(tree, segStart, mid, queryStart, queryEnd, 2 * index + 1), 
		getMaxUtil(tree, mid + 1, segEnd, queryStart, queryEnd, 2 * index + 2));
}

void update(RangeMaxST* tree, int ind, int val) {
	// Check for error conditions.
	if (ind < 0 || ind > tree->n - 1) {
		printf("Invalid Input.\n");
		return;
	}

	// Update the values in segment tree
	updateUtil(tree, 0, tree->n - 1, ind, val, 0);
}

int updateUtil(RangeMaxST* tree, int segStart, int segEnd, int ind, int val, int index) {
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
		}
		else
		{
			return tree->segArr[index]; // index value is not changed.
		}
	}

	int mid = (segStart + segEnd) / 2;

	// Current node value is updated with min. 
	tree->segArr[index] = max(updateUtil(tree, segStart, mid, ind, val, 2 * index + 1), 
				updateUtil(tree, mid + 1, segEnd, ind, val, 2 * index + 2));

	// Value of diff is propagated to the parent node.
	return tree->segArr[index];
}

int main() {
	int arr[] = {1, 8, 2, 7, 3, 6, 4, 5};
	RangeMaxST *tree = createRangeMaxST(arr, 8);
	printf("Max value in the range(1, 5): %d\n",  getMax(tree, 1, 5));
	printf("Max value in the range(2, 7): %d\n",  getMax(tree, 2, 7));
	printf("Max value of all the elements: %d\n",  getMax(tree, 0, sizeof(arr)/sizeof(int) - 1));
	update(tree, 2, 9);
	printf("Max value in the range(1, 5): %d\n",  getMax(tree, 1, 5));
	printf("Max value of all the elements: %d\n",  getMax(tree, 0, sizeof(arr)/sizeof(int) - 1));
	return 0;
}

/*
Max value in the range(1, 5): 8
Max value in the range(2, 7): 7
Max value of all the elements: 8
Max value in the range(1, 5): 9
Max value of all the elements: 9
*/