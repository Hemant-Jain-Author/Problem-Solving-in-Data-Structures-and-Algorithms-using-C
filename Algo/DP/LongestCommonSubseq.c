#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintLCS(int n, int p[][n], char X[], int i, int j) {
	if (i == 0 || j == 0)
		return;

	if (p[i][j] == 0) {
		PrintLCS(n, p, X, i - 1, j - 1);
		printf("%c", X[i - 1]);
	} else if (p[i][j] == 1) {
		PrintLCS(n, p, X, i - 1, j);
	} else {
		PrintLCS(n, p, X, i, j - 1);
	}
}

int LCSubStr(char* X, char* Y) {
	int m = strlen(X);
	int n = strlen(Y);
	int dp[m + 1][n + 1]; // Dynamic programming array.
	int p[m + 1][n + 1]; // For printing the subchar*.
	memset(dp, 0, sizeof(dp));
	memset(dp, 0, sizeof(p));

	// Fill dp array in bottom up fashion.
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
				p[i][j] = 0;
			} else {
				dp[i][j] = (dp[i - 1][j] > dp[i][j - 1])? dp[i - 1][j]: dp[i][j - 1];
				p[i][j] = (dp[i - 1][j] > dp[i][j - 1])? 1 : 2;
			}
		}
	}
	PrintLCS(n+1, p, X, m, n);
	printf("\n");
	return dp[m][n];
}

int main() {
	char* X = "carpenter";
	char* Y = "sharpener";
	printf("%d", LCSubStr(X, Y) );
	return 0;
}

/*
arpener
7
*/