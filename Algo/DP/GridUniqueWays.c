#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int uniqueWays(int m, int n) {
	int  dp[m][n];
	memset(dp, 0, m*n*sizeof(int));
	dp[0][0] = 1;

	// Initialize first column - Streight path.
	for (int i = 1; i < m; i++)
		dp[i][0] = 1;

	// Initialize first row - Streight path.
	for (int j = 1; j < n; j++)
		dp[0][j] = 1;

	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
	
	return dp[m - 1][n - 1];
}

int unique3Ways(int m, int n) {
	int  dp[m][n];
	memset(dp, 0, m*n*sizeof(int));
	dp[0][0] = 1;

	// Initialize first column - Streight path.
	for (int i = 1; i < m; i++)
		dp[i][0] = 1;
	
	// Initialize first row - Streight path.
	for (int j = 1; j < n; j++)
		dp[0][j] = 1;

	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
			dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + dp[i][j - 1];
	
	return dp[m - 1][n - 1];
}

int main() {
	printf("%d \n", uniqueWays(3, 3));
	printf("%d \n", unique3Ways(3, 3));
	return 0;
}
/*
6
13
*/