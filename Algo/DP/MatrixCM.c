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

void PrintOptPar(int n, int pos[][n], int i, int j) {
    if (i == j) 
        printf ("M%d ", pos[i][i]);
    else {
        printf("( ");
        PrintOptPar(n, pos, i, pos[i][j]);
        PrintOptPar(n, pos, pos[i][j]+1, j);
        printf (") ");
	}
}

void PrintOptimalParenthesis(int n, int pos[][n]) {
	printf("OptimalParenthesis : ");
	PrintOptPar(n, pos, 1, n-1);
	printf("\n");
}

int MatrixChainMulBU2(int p[], int n) {
	int  dp[n][n];
	int  pos[n][n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = INFINITE;
		}
	}
	
	for (int i = 1; i < n; i++) {
		dp[i][i] = 0;
		pos[i][i] = i;
	}

	for (int l = 1; l < n; l++) { // l is length of range.
		for (int i = 1,j = i + l ; j < n; i++, j++) {
			for (int k = i; k < j; k++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + p[i-1]*p[k]*p[j] + dp[k+1][j]);
				pos[i][j] = k;
			}
		}
	}
	
	PrintOptimalParenthesis(n, pos);
	return dp[1][n - 1];
}

int main() {
	int arr[] = {40, 10, 50, 20, 15};
	int n = sizeof(arr)/sizeof(int);
	printf("Matrix Chain Multiplication is: %d.\n" , MatrixChainMulBruteForce(arr, n) );
	printf("Matrix Chain Multiplication is: %d.\n" , MatrixChainMulTD(arr, n) );
	printf("Matrix Chain Multiplication is: %d.\n" , MatrixChainMulBU(arr, n) );
	printf("Matrix Chain Multiplication is: %d.\n" , MatrixChainMulBU2(arr, n) );
	return 0;
}

/*
Matrix Chain Multiplication is: 19000.
Matrix Chain Multiplication is: 19000.
Matrix Chain Multiplication is: 19000.
( ( ( M1 M2 ) M3 ) M4 ) Matrix Chain Multiplication is: 19000.
*/
