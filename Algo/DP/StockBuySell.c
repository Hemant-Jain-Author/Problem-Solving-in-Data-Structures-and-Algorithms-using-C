#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProfit(int arr[], int n)
{
	int buyProfit = -arr[0]; // Buy stock profit
	int sellProfit = 0; // Sell stock profit
	for (int i = 1; i < n; i++)
	{
		int newBuyProfit = (sellProfit - arr[i] > buyProfit)? sellProfit - arr[i] : buyProfit;
		int newSellProfit = (buyProfit + arr[i] > sellProfit)? buyProfit + arr[i] : sellProfit;
		buyProfit = newBuyProfit;
		sellProfit = newSellProfit;
	}
	return sellProfit;
}

int maxProfitTC(int arr[], int n, int t)
{
	int buyProfit = -arr[0];
	int sellProfit = 0;
	for (int i = 1;i < n;i++)
	{
		int newBuyProfit = ((sellProfit - arr[i]) > buyProfit) ? (sellProfit - arr[i]) : buyProfit;
		int newSellProfit = ((buyProfit + arr[i] - t) > sellProfit) ? (buyProfit + arr[i] - t) : sellProfit;
		buyProfit = newBuyProfit;
		sellProfit = newSellProfit;
	}
	return sellProfit;
}

int maxProfit2(int arr[], int n)
{
	int dp[n][2];
	memset(dp, 0, sizeof(dp));
	dp[0][0] = -arr[0]; // Buy stock profit
	dp[0][1] = 0; // Sell stock profit

	for (int i = 1;i < n;i++)
	{
		dp[i][0] = (dp[i - 1][1] - arr[i] > dp[i - 1][0]) ? dp[i - 1][1] - arr[i] : dp[i - 1][0];
		dp[i][1] = (dp[i - 1][0] + arr[i] > dp[i - 1][1]) ? dp[i - 1][0] + arr[i] : dp[i - 1][1];
	}
	return dp[n - 1][1];
}

int maxProfitTC2(int arr[], int n, int t)
{
	int dp[n][2];
	memset(dp, 0, sizeof(dp));
	dp[0][0] = -arr[0];
	dp[0][1] = 0;

	for (int i = 1;i < n;i++)
	{
		dp[i][0] = ((dp[i - 1][1] - arr[i]) > dp[i - 1][0]) ? (dp[i - 1][1] - arr[i]) : dp[i - 1][0];
		dp[i][1] = ((dp[i - 1][0] + arr[i] - t) > dp[i - 1][1]) ? (dp[i - 1][0] + arr[i] - t) : dp[i - 1][1];
	}
	return dp[n - 1][1];
}

int main()
{
	int  arr[] = {10, 12, 9, 23, 25, 55, 49, 70};
	int n = sizeof(arr)/sizeof(int);
	printf("Total profit: %d\n" , maxProfit(arr, n));
	printf("Total profit: %d\n" , maxProfit2(arr, n));
	printf("Total profit: %d\n" , maxProfitTC(arr, n, 2));
	printf("Total profit: %d\n" , maxProfitTC2(arr, n, 2));
}

/*
Total profit: 69
Total profit: 69
Total profit: 63
Total profit: 63
*/