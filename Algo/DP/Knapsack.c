#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
	return (a > b)? a : b;
}

int getMaxCost01Util(int wt[], int cost[], int n, int capacity) {
	// Base Case
	if (n == 0 || capacity == 0)
		return 0;

	// Return the maximum of two cases:
	// (1) nth item is included
	// (2) nth item is not included
	int first = 0;
	if (wt[n - 1] <= capacity)
		first = cost[n - 1] + getMaxCost01Util(wt, cost, n - 1, capacity - wt[n - 1]);

	int second = getMaxCost01Util(wt, cost, n - 1, capacity);
	return max(first, second);
}

int getMaxCost01(int wt[], int cost[], int n, int capacity) {
	return getMaxCost01Util(wt, cost, n, capacity);
}

int getMaxCost01TDUtil(int n, int dp[][n+1], int wt[], int cost[], int i, int w) {
	if (w == 0 || i == 0)
		return 0;

	if (dp[w][i] != 0)
		return dp[w][i];

	// Their are two cases:
	// (1) ith item is included
	// (2) ith item is not included
	int first = 0;
	if (wt[i - 1] <= w)
		first = getMaxCost01TDUtil(n, dp, wt, cost, i - 1, w - wt[i - 1]) + cost[i - 1];

	int second = getMaxCost01TDUtil(n, dp, wt, cost, i - 1, w);
	return dp[w][i] = max(first,second);
}

int getMaxCost01TD(int wt[], int cost[], int n, int capacity) {
	int dp[capacity + 1][n + 1];
	memset(dp, 0, sizeof(dp));
	return getMaxCost01TDUtil(n, dp, wt, cost, n, capacity);
}

int getMaxCost01BU(int wt[], int cost[], int n, int capacity) {
	int dp[capacity + 1][n + 1] ;
	memset(dp, 0, sizeof(dp));
	// Build table dp[][] in bottom up approach.
	// Weights considered against capacity.
	for (int w = 1; w <= capacity; w++) {
		for (int i = 1; i <= n; i++) {
			// Their are two cases:
			// (1) ith item is included
			// (2) ith item is not included
			int first = 0;
			if (wt[i - 1] <= w)
				first = dp[w - wt[i - 1]][i - 1] + cost[i - 1];

			int second = dp[w][i - 1];
			dp[w][i] = max(first,second);
		}
	}
	return dp[capacity][n]; // Number of weights considered and final capacity.
}

int KS01UnboundBU(int wt[], int cost[], int n, int capacity) {
	int dp[capacity + 1];
	memset(dp, 0, sizeof(dp));

	// Build table dp[] in bottom up approach.
	// Weights considered against capacity.
	for (int w = 1; w <= capacity; w++) {
		for (int i = 1; i <= n; i++) {
			// Their are two cases:
			// (1) ith item is included 
			// (2) ith item is not included
			if (wt[i - 1] <= w)
				dp[w] = max(dp[w], dp[w - wt[i - 1]] + cost[i - 1]);
		}
	}
	return dp[capacity]; // Number of weights considered and final capacity.
}

int main() {
	int  wt[] = {10, 40, 20, 30};
	int  cost[] = {60, 40, 90, 120};
	int capacity = 50;
	int n = 4;
	double maxCost = KS01UnboundBU(wt, cost, n, capacity);
	printf("Maximum cost obtained = %f\n" , maxCost );
	maxCost = getMaxCost01(wt, cost, n, capacity);
	printf("Maximum cost obtained = %f\n" , maxCost );
	maxCost = getMaxCost01BU(wt, cost, n, capacity);
	printf("Maximum cost obtained = %f\n" , maxCost );
	maxCost = getMaxCost01TD(wt, cost, n, capacity);
	printf("Maximum cost obtained = %f\n" , maxCost );
	return 0;
}

/*
Maximum cost obtained = 300.000000
Maximum cost obtained = 210.000000
Maximum cost obtained = 210.000000
Maximum cost obtained = 210.000000
*/