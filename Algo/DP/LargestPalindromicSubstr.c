#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palindromicSubstring(char* str) {
	int n = strlen(str);
	int dp[n][n];
	memset(dp, 0, sizeof(dp));

	for (int i = 0;i < n;i++)
		dp[i][i] = 1;

	int max = 1;
	int start = 0;

	for (int l = 1; l < n; l++) {
		for (int i = 0, j = i + l; j < n; i++, j++) {
			if (str[i] == str[j] && dp[i + 1][j - 1] == j - i - 1) {
				dp[i][j] = dp[i + 1][j - 1] + 2;
				if (dp[i][j] > max) {
					max = dp[i][j]; // Keeping track of max length and
					start = i; // starting position of sub-string.
				}
			} else {
				dp[i][j] = 0;
			}
		}
	}
	return max;
}

int main() {
	char* str = "ABCAUCBCxxCBA";
	int length = palindromicSubstring(str);
	printf("Max Palindromic Substrings len: %d." , length );
	return 0;
}

/*
Max Palindromic Substrings len: 6
*/