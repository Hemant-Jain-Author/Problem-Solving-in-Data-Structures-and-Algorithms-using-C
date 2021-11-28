#include<stdio.h>
#include<stdlib.h>

void printSubset(int flags[], int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (flags[i])
		{
			printf("%d ",arr[i]);
		}
	}
	printf("\n");
}

void subsetSumUtil(int arr[], int n, int flags[], int sum, int curr, int target)
{
	if (target == sum)
	{
		printSubset(flags, arr, n); // Solution found.
		return;
	}

	if (curr >= n || sum > target)
	{ // Constraint check and Backtracking.
		return;
	}

	flags[curr] = 1; // Current element included.
	subsetSumUtil(arr, n, flags, sum + arr[curr], curr + 1, target);
	
	flags[curr] = 0; // Current element excluded.
	subsetSumUtil(arr, n, flags, sum, curr + 1, target);
}

void subsetSum(int arr[], int n, int target)
{
	int flags[n];
	subsetSumUtil(arr, n, flags, 0, 0, target);
}

int main()
{
	int  arr[] = {15, 22, 14, 26, 32, 9, 16, 8};
	int target = 53;
	int n = sizeof(arr)/sizeof(int);
	subsetSum(arr, n, target);
	return 0;
}

/*
15 22 16 
15 14 16 8 
22 14 9 8 
*/