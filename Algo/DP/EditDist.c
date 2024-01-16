#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int x, int y, int z) {
	x = (x < y)? x : y;
	return x = (x < z)? x : z;
}

int editDistUtil(char* str1, char* str2, int m, int n) {
	// If any one string is empty, then empty the other string.
	if (m == 0 || n == 0) 
		return m + n;

	// If last characters of both strings are same then ignore last characters.
	if (str1[m - 1] == str2[n - 1]) {
		return editDistUtil(str1, str2, m - 1, n - 1);
	}

	// If last characters are different then consider all three cases:
	// 1) Insert last char of second into first.
	// 2) Remove last char of first.
	// 3) Replace last char of first with second.
	return 1 + min(editDistUtil(str1, str2, m, n - 1), 
				editDistUtil(str1, str2, m - 1, n), 
				editDistUtil(str1, str2, m - 1, n - 1)); // Replace
}

int editDist(char* str1, char* str2) {
	int m = strlen(str1);
	int n = strlen(str2);
	return editDistUtil(str1, str2, m, n);
}

int editDistDP(char* str1, char* str2) { // bottom up approach
	int m = strlen(str1);
	int n = strlen(str2);
	int dp[m + 1][n + 1];

	// Fill dp[][] in bottom up manner.
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			// If any one string is empty then empty the other string.
			if (i == 0 || j == 0) {
				dp[i][j] = (i + j);
			}
			// If last characters of both strings are same then ignore last characters.
			else if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			// If last characters are different then consider all three operations:
			// 1) Insert last char of second into first.
			// 2) Remove last char of first.
			// 3) Replace last char of first with second.
			else {
				dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]); // Replace
			}
		}
	}
	return dp[m][n];
}

int main() {
	char* str1 = "sunday";
	char* str2 = "saturday";
	printf("EditDist is %d\n", editDist(str1, str2));
	printf("EditDist is %d\n", editDistDP(str1, str2));
	return 0;
}

/*
EditDist is 3
EditDist is 3
*/