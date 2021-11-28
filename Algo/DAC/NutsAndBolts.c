#include <stdio.h>
#include<stdlib.h>

void printArray(int arr[], int n)
{
	printf("[ ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i] );
	}
	printf("] ");
}

void swap(int arr[], int first, int second)
{
	int temp = arr[first];
	arr[first] = arr[second];
	arr[second] = temp;
}

int partition(int arr[], int low, int high, int pivot)
{
	int i = low;
	for (int j = low; j < high; j++)
	{
		if (arr[j] < pivot)
		{
			swap(arr, i, j);
			i++;
		}
		else if (arr[j] == pivot)
		{
			swap(arr, high, j);
			j--;
		}
	}
	swap(arr, i, high);
	return i;
}

void makePairsUtil(int nuts[], int bolts[], int low, int high)
{
	if (low < high)
	{
		// Choose first element of bolts array as pivot to partition nuts.
		int pivot = partition(nuts, low, high, bolts[low]);
		// Using nuts[pivot] as pivot to partition bolts.
		partition(bolts, low, high, nuts[pivot]);
		// Recursively lower and upper half of nuts and bolts are matched.
		makePairsUtil(nuts, bolts, low, pivot - 1);
		makePairsUtil(nuts, bolts, pivot + 1, high);
	}
}

void makePairs(int nuts[], int bolts[], int size)
{
	makePairsUtil(nuts, bolts, 0, size-1);
	printf("Matched nuts and bolts are : ");
	printArray(nuts, size);
	printArray(bolts, size);
}

int main()
{
	int nuts[] = {1, 2, 6, 5, 4, 3};
	int bolts[] = {6, 4, 5, 1, 3, 2};
	makePairs(nuts, bolts, 6);
	return 0;
}

/*
Matched nuts and bolts are : [ 1 2 3 4 5 6 ] [ 1 2 3 4 5 6 ] 
*/