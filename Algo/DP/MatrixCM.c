#include <stdio.h>
#include<stdlib.h>

int min(int a, int b) {
	return (a < b)? a : b;
}
int INFINITE = 99999;
int MatrixChainMulBruteForceUtil(int p[], int i, int j) {
	if (i == j) // self product cost 0
		return 0;

	int min = INFINITE;

	// place parenthesis at different places between first and last matrix, recursively calculate
	// count of multiplications for each parenthesis placement and return the minimum count
	for (int k = i; k < j; k++) {
		int count = MatrixChainMulBruteForceUtil(p, i, k) + 
					MatrixChainMulBruteForceUtil(p, k + 1, j) + 
					p[i - 1] * p[k] * p[j];

		if (count < min)
			min = count;
	}
	return min; // Return minimum count
}

int MatrixChainMulBruteForce(int p[], int n) {
	return MatrixChainMulBruteForceUtil(p, 1, n - 1);
}


int MatrixChainMulTDUtil(int n, int dp[][n], int p[], int i, int j) {
	if (dp[i][j] != INFINITE)
		return dp[i][j];

	for (int k = i; k < j; k++) {
		dp[i][j] = min(dp[i][j], MatrixChainMulTDUtil(n, dp, p, i, k) + 
						MatrixChainMulTDUtil(n, dp, p, k+1, j) + p[i-1]*p[k]*p[j]);
	}
	return dp[i][j];
}

int MatrixChainMulTD(int p[], int n) {
	int  dp[n][n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = INFINITE;
	
	for (int i = 1; i < n; i++)
			dp[i][i] = 0;
	
	return MatrixChainMulTDUtil(n, dp, p, 1, n - 1);
}

int MatrixChainMulBU(int p[], int n) {
	int  dp[n][n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = INFINITE;
	
	for (int i = 1; i < n; i++)
			dp[i][i] = 0;

	for (int l = 1; l < n; l++) { // l is length of range.
		for (int i = 1,j = i + l ; j < n; i++, j++) {
			for (int k = i; k < j; k++)
				dp[i][j] = min(dp[i][j], dp[i][k] + p[i-1]*p[k]*p[j] + dp[k+1][j]);
		}
	}
	return dp[1][n - 1];
}

int main() {
	int arr[] = {1, 2, 3, 4};
	int n = sizeof(arr)/sizeof(int);
	printf("Matrix Chain Multiplication is: %d.\n" , MatrixChainMulBruteForce(arr, n) );
	printf("Matrix Chain Multiplication is: %d.\n" , MatrixChainMulTD(arr, n) );
	printf("Matrix Chain Multiplication is: %d.\n" , MatrixChainMulBU(arr, n) );
	return 0;
}

/*
Matrix Chain Multiplication is: 18
Matrix Chain Multiplication is: 18
Matrix Chain Multiplication is: 18
*/