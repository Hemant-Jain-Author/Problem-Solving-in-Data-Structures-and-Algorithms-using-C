
#include <stdio.h>
#include <string.h>

int min(int a, int b) {
	return (a < b)? a : b;
}

int max(int a, int b) {
	return (a > b)? a : b;
}

int minCost(int days[], int n, int costs[]) {
	int maxVal = days[n - 1];
	int dp[maxVal + 1];
	memset(dp, 0, sizeof(dp));

	int j = 0;
	for (int i = 1; i <= maxVal; i++) {
		if (days[j] == i) // That days is definitely travelled.
		{
			j++;
			dp[i] = dp[i - 1] + costs[0];
			dp[i] = min(dp[i], dp[max(0, i - 7)] + costs[1]);
			dp[i] = min(dp[i], dp[max(0, i - 30)] + costs[2]);
		}
		else
			dp[i] = dp[i - 1]; // day may be ignored.
	}
	return dp[maxVal];
}

int main() {
	int days[] = {1, 3, 5, 7, 12, 20, 30};
	int n = 7;
	int costs[] = {2, 7, 20};
	printf("Min cost is: %d", minCost(days, n, costs));
	return 0;
}

/*
Min cost is:13
*/