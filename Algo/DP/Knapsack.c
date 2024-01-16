#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
	return (a > b)? a : b;
}

int maxCost01KnapsackUtil(int wt[], int cost[], int n, int capacity) {
	// Base Case
	if (n == 0 || capacity == 0)
		return 0;

	// Return the maximum of two cases:
	// (1) nth item is included
	// (2) nth item is not included
	int first = 0;
	if (wt[n - 1] <= capacity)
		first = cost[n - 1] + maxCost01KnapsackUtil(wt, cost, n - 1, capacity - wt[n - 1]);

	int second = maxCost01KnapsackUtil(wt, cost, n - 1, capacity);
	return max(first, second);
}

int maxCost01Knapsack(int wt[], int cost[], int n, int capacity) {
	return maxCost01KnapsackUtil(wt, cost, n, capacity);
}

int maxCost01KnapsackTDUtil(int n, int dp[][n+1], int wt[], int cost[], int i, int w) {
	if (w == 0 || i == 0)
		return 0;

	if (dp[w][i] != 0)
		return dp[w][i];

	// Their are two cases:
	// (1) ith item is included
	// (2) ith item is not included
	int first = 0;
	if (wt[i - 1] <= w)
		first = maxCost01KnapsackTDUtil(n, dp, wt, cost, i - 1, w - wt[i - 1]) + cost[i - 1];

	int second = maxCost01KnapsackTDUtil(n, dp, wt, cost, i - 1, w);
	return dp[w][i] = max(first,second);
}

int maxCost01KnapsackTD(int wt[], int cost[], int n, int capacity) {
	int dp[capacity + 1][n + 1];
	memset(dp, 0, sizeof(dp));
	return maxCost01KnapsackTDUtil(n, dp, wt, cost, n, capacity);
}


void printItems(int n, int dp[][n+1], int wt[], int cost[], int capacity) {
	int totalProfit = dp[capacity][n];
    printf("Selected items are: ");
	for (int i = n-1; i > -1 && totalProfit > 0; i--) {
        if (totalProfit != dp[capacity][i - 1]) {
            printf("(wt:%d, cost:%d) ", wt[i] ,cost[i]);
            capacity -= wt[i];
            totalProfit -= cost[i];
		}
	}
	printf("\n");
}

int maxCost01KnapsackBU(int wt[], int cost[], int n, int capacity) {
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
	printItems(n, dp, wt, cost, capacity);
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
	maxCost = maxCost01Knapsack(wt, cost, n, capacity);
	printf("Maximum cost obtained = %f\n" , maxCost );
	maxCost = maxCost01KnapsackBU(wt, cost, n, capacity);
	printf("Maximum cost obtained = %f\n" , maxCost );
	maxCost = maxCost01KnapsackTD(wt, cost, n, capacity);
	printf("Maximum cost obtained = %f\n" , maxCost );
	return 0;
}

/*
Maximum cost obtained = 300.000000
Maximum cost obtained = 210.000000
Selected items are: (wt:30, cost:120) (wt:20, cost:90) 
Maximum cost obtained = 210.000000
Maximum cost obtained = 210.000000
*/