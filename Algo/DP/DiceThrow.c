#include <stdio.h>
#include<stdlib.h>

int findWaysBU(int n, int m, int V) {
	int dp[n + 1][V + 1];
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= V; j++)
			dp[i][j] = 0;

	// Table entries for only one dice.
	for (int j = 1; j <= m && j <= V; j++)
		dp[1][j] = 1;

	for (int i = 2; i <= n; i++) { // i is number of dice
		for (int j = 1; j <= V; j++) { // j is target value 
			for (int k = 1; k <= j && k <= m; k++) { // k value of m face dice.
				dp[i][j] += dp[i - 1][j - k];
			}
		}
	}
	return dp[n][V];
}

int main() {
	for (int i = 1;i <= 6;i++) {
		printf("%d\n", findWaysBU(i, 6, 6) );
	}
}

/*
1
5
10
10
5
1
*/