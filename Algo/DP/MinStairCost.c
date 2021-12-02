#include <stdio.h>
#include<stdlib.h>

int min(int a, int b) {
	return (a < b)? a : b;
}

int minCost(int cost[], int n) {
	// base case
	if (n == 1)
		return cost[0];

	int dp[n];
	dp[0] = cost[0];
	dp[1] = cost[1];

	for (int i = 2; i < n; i++)
		dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];

	return min(dp[n - 2], dp[n - 1]);
}

int main() {
	int a[] = {1, 5, 6, 3, 4, 7, 9, 1, 2, 11};
	int n = sizeof(a)/sizeof(int);
	printf("minCost : %d\n", minCost(a, n));
	return 0;
}

/*
minCost : 18
*/