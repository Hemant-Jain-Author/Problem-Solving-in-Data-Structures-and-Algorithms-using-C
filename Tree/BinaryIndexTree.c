#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BinaryIndexTree_t
{
	int* BIT;
	int size;
}BinaryIndexTree;
	
BinaryIndexTree* createBinaryIndexTree(int arr[], int n);
void set(BinaryIndexTree*, int arr[], int index, int val);
void update(BinaryIndexTree*, int index, int val);
int rangeSum(BinaryIndexTree*, int start, int end); // Range sum in the range start to end.
int prefixSum(BinaryIndexTree*, int index); // Prefix sum in the range 0 to index.

BinaryIndexTree* createBinaryIndexTree(int arr[], int n)
{
	BinaryIndexTree* tree = (BinaryIndexTree*)malloc(sizeof(BinaryIndexTree));
	tree->size = n;
	tree->BIT = (int*)malloc((n+1)*sizeof(int)); 
	for (int i = 0; i < tree->size; i++) // Populating bit.
	{
		update(tree, i, arr[i]);
	}
	return tree;
}

void set(BinaryIndexTree* tree, int arr[], int index, int val)
{
	int diff = val - arr[index];
	arr[index] = val;

	// Difference is propagated.
	update(tree, index, diff);
}

void update(BinaryIndexTree* tree, int index, int val)
{
	// Index in bit is 1 more than the input array.
	index = index + 1;

	// Traverse to ancestors of nodes.
	while (index <= tree->size)
	{
		// Add val to current node of Binary Index Tree.
		tree->BIT[index] += val;

		// Next element which need to store val.
		index += index & (-index);
	}
}

int rangeSum(BinaryIndexTree* tree, int start, int end)
{
	// Check for error conditions.
	if (start > end || start < 0 || end > tree->size - 1)
	{
		printf("Invalid Input.\n");
		return -1;
	}

	return prefixSum(tree, end) - prefixSum(tree, start - 1);
}

int prefixSum(BinaryIndexTree* tree, int index)
{
	int sum = 0;
	index = index + 1;

	// Traverse ancestors of Binary Index Tree nodes.
	while (index > 0)
	{
		// Add current element to sum.
		sum += tree->BIT[index];

		// Parent index calculation.
		index -= index & (-index);
	}
	return sum;
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	BinaryIndexTree *tree = createBinaryIndexTree(arr, 10);
	printf("Sum of elements in range(0, 5): %d\n", prefixSum(tree, 5));
	printf("Sum of elements in range(2, 5): %d\n", rangeSum(tree, 2, 5));
	// Set fourth element to 10.
	set(tree, arr, 3, 10); 

	// Find sum after the value is updated
	printf("Sum of elements in range(0, 5): %d\n", prefixSum(tree, 5));
	//delete tree;
}

/*
Sum of elements in range(0, 5): 21
Sum of elements in range(2, 5): 18
Sum of elements in range(0, 5): 27
*/