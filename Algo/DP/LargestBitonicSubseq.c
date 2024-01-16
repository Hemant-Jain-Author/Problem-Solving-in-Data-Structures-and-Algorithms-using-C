#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
	return (a > b)? a : b;
}

int lbs(int arr[], int n) {
	int lis[n]; // Initialize LIS values for all indexes as 1.
	int lds[n]; // Initialize LDS values for all indexes as 1.
	
	for (int i = 0; i < n; i++) {
		lis[i] = 1;
		lds[i] = 1;
	}
	
	int maxVal = 0;

	// Populating LIS values in bottom up manner.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i] && lis[i] < lis[j] + 1)
				lis[i] = lis[j] + 1;
		}
	}

	// Populating LDS values in bottom up manner.
	for (int i = n - 1; i > 0; i--) {
		for (int j = n - 1; j > i; j--) {
			if (arr[j] < arr[i] && lds[i] < lds[j] + 1)
				lds[i] = lds[j] + 1;
		}
	}

	for (int i = 0; i < n; i++)
		maxVal = max(maxVal, lis[i] + lds[i] - 1);
	return maxVal;
}

int main() {
	int arr[] = {1, 6, 3, 11, 1, 9, 5, 12, 3, 14, 6, 17, 3, 19, 2, 19};
	int n = 16;
	printf("Length of lbs is %d." , lbs(arr, n) );
}

/*
Length of lbs is 8
*/