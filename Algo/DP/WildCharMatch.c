#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matchExpUtil(char* exp, char* str, int m, int n) {
	if (m ==  strlen(exp) && (n ==  strlen(str) || exp[m - 1] == '*'))
		return 1;
	
	if ((m ==  strlen(exp) && n !=  strlen(str)) || (m !=  strlen(exp) && n ==  strlen(str)))
		return 0;
	
	if (exp[m] == '?' || exp[m] == str[n])
		return matchExpUtil(exp, str, m + 1, n + 1);
	
	if (exp[m] == '*')
		return matchExpUtil(exp, str, m + 1, n) || matchExpUtil(exp, str, m, n + 1);

	return 0;
}

int matchExp(char* exp, char* str) {
	return matchExpUtil(exp, str, 0, 0);
}

int matchExpDPUtil(char* exp, char* str, int m, int n) {
	int lookup[m + 1][n + 1];
	lookup[0][0] = 1; // empty exp and empty str match.

	// 0 row will remain all 0. empty exp can't match any str.
	// '*' can match with empty string, column 0 update.
	for (int i = 1; i <= m; i++) {
		if (exp[i - 1] == '*')
			lookup[i][0] = lookup[i - 1][0];
		else
			break;
	}

	// Fill the table in bottom-up fashion
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			// If we see a '*' in pattern:
			// 1) We ignore '*' character and consider next character in the pattern.
			// 2) We ignore one character in the input str and consider next character.
			if (exp[i - 1] == '*')
				lookup[i][j] = lookup[i - 1][j] || lookup[i][j - 1];
			// Condition when both the pattern and input string have same character. 
			// Also '?' match with all the characters.
			else if (exp[i - 1] == '?' || str[j - 1] == exp[i - 1])
				lookup[i][j] = lookup[i - 1][j - 1];
			// If characters don't match
			else
				lookup[i][j] = 0;
		}
	}
	return lookup[m][n];
}

int matchExpDP(char* exp, char* str) {
	return matchExpDPUtil(exp, str,  strlen(exp),  strlen(str));
}

int main() {
	printf("%d\n",matchExp("*llo,?World?", "Hello, World!"));
	printf("%d\n",matchExpDP("*llo,?World?", "Hello, World!"));
}

/*
1
1
*/