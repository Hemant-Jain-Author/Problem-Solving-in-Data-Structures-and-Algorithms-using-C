
#include <stdio.h>
#include <string.h>

int max(int a, int b){
	return (a > b)? a : b;
}

int palindromicSubsequence(char* str) {
	int n = strlen(str);
	int dp[n][n];
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < n; i++) // each char is itself palindromic with length 1
		dp[i][i] = 1;

	for (int l = 1; l < n; l++) {
		for (int i = 0, j = l; j < n; i++, j++) {
			if (str[i] == str[j])
				dp[i][j] = dp[i + 1][j - 1] + 2;
			else
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
		}
	}
	return dp[0][n - 1];
}

int main() {
	char *str = "ABCAUCBCxxCBA";
	printf("Max Palindromic Subsequence length: %d", palindromicSubsequence(str));
	return 0;
}

/*
Max Palindromic Subsequence length: 9
*/