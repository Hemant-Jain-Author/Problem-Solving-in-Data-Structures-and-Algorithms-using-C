#include<stdio.h>
#include<stdlib.h>

void printArray(int arr[], int n) {
	for (int i = 0;i < n;i++) 
		printf("%d ", arr[i]);
	printf("\n");
}

void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void permutation(int arr[], int i, int length) {
	if (length == i) {
		printArray(arr, length);
		return;
	}

	for (int j = i; j < length; j++) {
		swap(arr, i, j);
		permutation(arr, i + 1, length);
		swap(arr, i, j);
	}
	return;
}

int isValid(int arr[], int n) {
	for (int j = 1;j < n;j++) {
		if (abs(arr[j] - arr[j - 1]) < 2) {
			return 0;
		}
	}
	return 1;
}

void permutation2(int arr[], int i, int length) {
	if (length == i) {
		if (isValid(arr, length)) {
			printArray(arr, length);
		}
		return;
	}

	for (int j = i; j < length; j++) {
		swap(arr, i, j);
		permutation2(arr, i + 1, length);
		swap(arr, i, j);
	}
	return;
}

int isValid2(int arr[], int i) {
	if (i < 1 || abs(arr[i] - arr[i - 1]) >= 2) {
		return 1;
	}
	return 0;
}

void permutation3(int arr[], int i, int length) {
	if (length == i) {
		printArray(arr, length);
		return;
	}

	for (int j = i; j < length; j++) {
		swap(arr, i, j);
		if (isValid2(arr, i)) {
			permutation3(arr, i + 1, length);
		}
		swap(arr, i, j);
	}
	return;
}

int main() {
	int arr[4];
	for (int i = 0; i < 4; i++) {
		arr[i] = i + 1;
	}
	permutation(arr, 0, 4);
	printf("\n");
	permutation2(arr, 0, 4);
	printf("\n");
	permutation3(arr, 0, 4);
	return 0;
}

/*
1 2 3 4 
1 2 4 3 
....
4 1 3 2 
4 1 2 3 

2 4 1 3 
3 1 4 2 

2 4 1 3 
3 1 4 2 
*/