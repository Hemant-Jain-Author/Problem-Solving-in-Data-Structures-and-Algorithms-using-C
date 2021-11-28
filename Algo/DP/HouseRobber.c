#include <stdio.h>
#include<stdlib.h>

int max(int a, int b){
	return (a > b)? a : b;
}

int maxRobbery(int house[], int n)
{
	int dp[n];
	dp[0] = house[0];
	dp[1] = house[1];
	dp[2] = house[0] + house[2];
	for (int i = 3; i < n; i++)
	{
		dp[i] = max(dp[i - 2], dp[i - 3]) + house[i];
	}
	return max(dp[n - 1], dp[n - 2]);
}

int maxRobbery2(int house[], int n)
{
	int dp[n][2];
	dp[0][1] = house[0];
	dp[0][0] = 0;

	for (int i = 1; i < n; ++i)
	{
		dp[i][1] = max(dp[i - 1][0] + house[i], dp[i - 1][1]);
		dp[i][0] = dp[i - 1][1];
	}
	return max(dp[n - 1][1], dp[n - 1][0]);
}

int main()
{
	int arr[] = {10, 12, 9, 23, 25, 55, 49, 70};
	printf("Total cash: %d \n" , maxRobbery(arr, 8));
	printf("Total cash: %d \n" , maxRobbery2(arr, 8));
	return 0;
}

/*
Total cash: 160
Total cash: 160
*/