#include <stdio.h>
#include<stdlib.h>
int INFI = 99999 ;

int compare(int a, int b) {
	return (a > b);
}

int min(int a, int b) {
	return (a < b)? a : b;
}

void sort(int arr[], int size, int (*comp)(int p1, int p2)) {
	int temp;
    for (int i = 0; i < (size - 1); i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (comp(arr[j], arr[j + 1])) {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int minCoins(int coins[], int n, int val) {// Greedy may be wrong.
	if (val <= 0)
		return 0;

	int count = 0;
	sort(coins, n, compare);
	for (int i = n - 1; i >= 0 && val > 0;) {
		if (coins[i] <= val) {
			count++;
			val -= coins[i];
		} else {
			i--;
		}
	}
	return (val == 0)? count : -1;
}

int minCoins2(int coins[], int n, int val) // Brute force.
{
	if (val == 0)
		return 0;

	int count = INFI ;
	for (int i = 0; i < n ; i++) {
		if (coins[i] <= val) {
			int subCount = minCoins2(coins, n, val - coins[i]);
			if (subCount >= 0) {
				count = min(count, subCount + 1);
			}
		}
	}
	return (count != INFI )? count : -1;
}

int minCoinsTDUtil(int dp[], int coins[], int n, int val) {
	if (dp[val] != INFI )
		return dp[val];

	// Recursion
	for (int i = 0; i < n; i++) {
		if (coins[i] <= val) { // check validity of a sub-problem
			int subCount = minCoinsTDUtil(dp, coins, n, val - coins[i]);
			if (subCount != INFI ) {
				dp[val] = min(dp[val], subCount + 1);
			}
		}
	}
	return dp[val];
}

int minCoinsTD(int coins[], int n, int val) {
	int dp[val + 1];
	for(int i = 0; i< val + 1; i++)
		dp[i] = INFI ;

	dp[0] = 0; // zero val need zero coins.
	return minCoinsTDUtil(dp, coins, n, val);
}

int minCoinsBU(int coins[], int n, int val) { // DP bottom up approach.
	int dp[val + 1];
	for(int i = 0; i< val + 1; i++)
		dp[i] = INFI ;

	dp[0] = 0; // Base value.

	for (int i = 1; i <= val; i++) {
		for (int j = 0; j < n; j++) {
			// For all coins smaller than or equal to i.
			if (coins[j] <= i) {
				if (dp[i - coins[j]] != INFI ) {
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
				}
			}
		}
	}

	return (dp[val] != INFI )? dp[val] : -1;
}

int main() {
	int  coins[] = {1, 4, 6, 9, 12};
	int value = 15;
	int n = 5;
	printf("Count is : %d\n" , minCoins(coins, n, value));
	printf("Count is : %d\n" , minCoins2(coins, n, value));
	printf("Count is : %d\n" , minCoinsBU(coins, n, value));
	printf("Count is : %d\n" , minCoinsTD(coins, n, value));
}

/*
Count is : 4
Count is : 2
Count is : 2
Count is : 2
*/