#include <stdio.h>
#include<stdlib.h>

int diffWaysBU(int n) {
	if (n <= 2)
		return n;

	int first = 1, second = 2, temp = 0;

	for (int i = 3; i <= n; i++) {
		temp = first + second;
		first = second;
		second = temp;
	}
	return temp;
}

int diffWaysBU2(int n) {
	if (n < 2)
		return n;

	int ways[n];
	ways[0] = 1;
	ways[1] = 2;

	for (int i = 2; i < n; i++)
		ways[i] = ways[i - 1] + ways[i - 2];

	return ways[n - 1];
}

int main() {
	printf("Unique way to reach top:: %d\n" , diffWaysBU(4));
	printf("Unique way to reach top:: %d\n" , diffWaysBU2(4));
}

/*
Unique way to reach top:: 5
Unique way to reach top:: 5
*/