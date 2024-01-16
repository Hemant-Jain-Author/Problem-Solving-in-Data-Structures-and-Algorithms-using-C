#include <stdio.h>
#include<stdlib.h>

int min(int a, int b) {
	return (a < b)? a : b;
}

int sum(int freq[], int i, int j) {
	int s = 0;
	for (int k = i; k <= j; k++)
		s += freq[k];

	return s;
}

void sumInit(int sum[], int freq[], int n) {
	sum[0] = freq[0];
	for (int i = 1; i < n; i++)
		sum[i] = sum[i - 1] + freq[i];
}

int sumRange(int sum[], int i, int j) {
	if (i == 0)
		return sum[j];
	return sum[j] - sum[i - 1];
}

int optimalBstUtil(int freq[], int i, int j) {
	if (i > j)
		return 0;

	if (j == i) // one element in this subarray
		return freq[i];

	int minval = 99999;
	for (int r = i; r <= j; r++)
		minval = min(minval, optimalBstUtil(freq, i, r - 1) + optimalBstUtil(freq, r + 1, j));
	
	return minval + sum(freq, i, j);
}

int optimalBst(int keys[], int freq[], int n) {
	return optimalBstUtil(freq, 0, n - 1);
}

int optimalBstTDUtil(int freq[], int n, int cost[][n], int i, int j) {
	if (i > j)
		return 0;

	if (cost[i][j] != 99999)
		return cost[i][j];

	int s = sum(freq, i, j);
	for (int r = i; r <= j; r++) {
		cost[i][j] = min(cost[i][j], optimalBstTDUtil(freq, n, cost, i, r - 1) + 
									optimalBstTDUtil(freq, n, cost, r + 1, j) + s);
	}
	return cost[i][j];
}

int optimalBstTD(int keys[], int freq[], int n) {
	int cost[n][n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cost[i][j] = 99999;

	for (int i = 0; i < n; i++)
		cost[i][i] = freq[i];

	return optimalBstTDUtil(freq, n,  cost, 0, n - 1);
}

int optimalBstBU(int keys[], int freq[], int n) {
	int cost[n][n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cost[i][j] = 99999;

	for (int i = 0; i < n; i++)
		cost[i][i] = freq[i];

	int sm = 0;
	for (int l = 1; l < n; l++) { // l is length of range. 
		for (int i = 0, j = i + l; j < n; i++, j++) {
			sm = sum(freq, i, j);
			for (int r = i; r <= j; r++) {
				cost[i][j] = min(cost[i][j], sm + ((r - 1 >= i)? cost[i][r - 1] : 0) + ((r + 1 <= j)? cost[r + 1][j] : 0));
			}
		}
	}
	return cost[0][n - 1];
}

int optimalBstBU2(int keys[], int freq[], int n) {
	int cost[n][n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cost[i][j] = 99999;

	for (int i = 0; i < n; i++)
		cost[i][i] = freq[i];

	int  sumArr[n];
	sumInit(sumArr, freq, n);
	int sm = 0;
	for (int l = 1; l < n; l++) { // l is length of range.
		for (int i = 0, j = i + l; j < n; i++, j++) {
			sm = sumRange(sumArr, i, j);
			for (int r = i; r <= j; r++) {
				cost[i][j] = min(cost[i][j], sm + ((r - 1 >= i)? cost[i][r - 1] : 0) + ((r + 1 <= j)? cost[r + 1][j] : 0));
			}
		}
	}
	return cost[0][n - 1];
}

int main() {
	int  keys[] = {9, 15, 25};
	int  freq[] = {30, 10, 40};
	int size = 3;
	printf("OBst cost: %d\n", optimalBst(keys, freq, size));
	printf("OBst cost: %d\n", optimalBstTD(keys, freq, size));
	printf("OBst cost: %d\n", optimalBstBU(keys, freq, size));
	printf("OBst cost: %d\n", optimalBstBU2(keys, freq, size));
}

/*
OBst cost:130
OBst cost:130
OBst cost:130
OBst cost:130
*/