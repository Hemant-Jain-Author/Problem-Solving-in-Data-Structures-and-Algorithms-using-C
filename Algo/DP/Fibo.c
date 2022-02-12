#include <stdio.h>
#include<stdlib.h>

int fibonacci(int n) {
	if (n <= 2)
		return n - 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

void fibonacciSeries(int n) {
	for (int i = 1;i <= n;i++)
		printf("%d ", fibonacci(i));
}

int fibonacciBU(int n) {
	if (n <= 2)
		return n - 1;

	int first = 0, second = 1, temp = 0;

	for (int i = 2; i < n; i++) {
		temp = first + second;
		first = second;
		second = temp;
	}
	return temp;
}

void fibonacciSeriesBU(int n) {
	if (n < 1)
		return;

	int dp[n];
	dp[0] = 0;
	if(n > 1)
		dp[1] = 1;

	for (int i = 2; i < n; i++)
		dp[i] = dp[i - 2] + dp[i - 1];

	for (int i = 0; i < n; i++)
		printf("%d ", dp[i]);
}

int fibonacciSeriesTDUtil(int n, int dp[]) {
	if (dp[n] == 0)
		dp[n] = fibonacciSeriesTDUtil(n - 1, dp) + fibonacciSeriesTDUtil(n - 2, dp);	
	return dp[n];
}

void fibonacciSeriesTD(int n) {
	if (n < 1)
		return;

	int dp[n];
	dp[0] = 0;
	if(n > 1)
		dp[1] = 1;

	fibonacciSeriesTDUtil(n - 1, dp);

	for (int i = 0;i < n;i++)
		printf("%d ", dp[i]);
}

int main() {
	fibonacciSeries(6);
	printf("\n");

	fibonacciSeriesBU(6);
	printf("\n");

	fibonacciSeriesTD(6);
	printf("\n");
	
	printf("%d \n", fibonacci(6));
	printf("%d \n", fibonacciBU(6));
	return 0;
}

/*
0 1 1 2 3 5 
0 1 1 2 3 5 
0 1 1 2 3 5 
5
5
*/