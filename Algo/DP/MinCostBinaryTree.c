
#include <stdio.h>

int INFINITY = 99999;

int max(int a, int b){
	return (a > b)? a : b;
}

int min(int a, int b){
	return (a < b)? a : b;
}

int maxVal(int n, int maxArr[][n], int i, int j)
{
	if (maxArr[i][j] != 0)
		return maxArr[i][j];

	for (int k = i;k < j;k++)
		maxArr[i][j] = max(maxArr[i][j], max(maxVal(n, maxArr, i, k), maxVal(n, maxArr, k + 1, j)));
	
	return maxArr[i][j];
}

int findSumTDUtil(int n, int dp[][n], int maxArr[][n], int i, int j)
{
	if (dp[i][j] != INFINITY)
		return dp[i][j];

	for (int k = i;k < j;k++)
	{
		dp[i][j] = min(dp[i][j], findSumTDUtil(n, dp, maxArr, i, k) + 
									findSumTDUtil(n, dp, maxArr, k + 1, j) + 
									maxVal(n, maxArr, i, k) * maxVal(n, maxArr, k + 1,j));
	}
	return dp[i][j];
}

int findSumTD(int arr[], int n)
{
	int dp[n][n];
	int maxArr[n][n];

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			dp[i][j] = INFINITY; // unknown product is infinity.
			maxArr[i][j] = 0;// unknown max is 0
		}
	}

	for (int i = 0;i < n;i++){
		maxArr[i][i] = arr[i]; // single element max is itself.
		dp[i][i] = 0; //  single element product cost 0
	}

	return findSumTDUtil(n, dp, maxArr, 0, n - 1);
}

int findSumBU(int arr[], int n)
{
	int dp[n][n];
	int maxArr[n][n];

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			dp[i][j] = INFINITY; // unknown product is infinity.
			maxArr[i][j] = 0;// unknown max is 0
		}
	}

	for (int i = 0;i < n;i++){
		maxArr[i][i] = arr[i]; // single element max is itself.
		dp[i][i] = 0; //  single element product cost 0
	}

	for (int l = 1; l < n; l++) // l is length of range.
	{
		for (int i = 0, j = i + l; j < n; i++, j++)
		{
			for (int k = i; k < j; k++)
			{
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + maxArr[i][k] * maxArr[k + 1][j]);
				maxArr[i][j] = max(maxArr[i][k], maxArr[k + 1][j]);
			}
		}
	}
	return dp[0][n - 1];
}

int main()
{
	int arr[] = {6, 2, 4};
	printf("Total cost: %d\n" , findSumTD(arr, 3));
	printf("Total cost: %d\n" , findSumBU(arr, 3));
	return 0;
}

/*
Total cost: 32
Total cost: 32
*/