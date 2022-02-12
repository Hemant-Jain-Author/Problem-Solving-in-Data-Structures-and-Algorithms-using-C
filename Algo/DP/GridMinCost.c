#include <stdio.h>
#include<stdlib.h>

int min(int x, int y, int z) {
	x = (x < y)? x : y;
	x = (x < z)? x : z;
	return x;
}

int minGridCost(int N, int cost[][N], int m, int n ) {	
	if (m == 0 || n == 0)
		return 99999;

	if (m == 1 && n == 1)
		return cost[0][0];

	return cost[m-1][n-1] + min(minGridCost(N, cost,m-1, n-1), 
								minGridCost(N, cost,m-1, n), 
								minGridCost(N, cost,m, n-1));
}

int minGridCostBU(int m, int n, int cost[m][n]) {
	int tc[m][n];
	tc[0][0] = cost[0][0];

	// Initialize first column.
	for (int i = 1; i < m; i++)
		tc[i][0] = tc[i-1][0] + cost[i][0];

	// Initialize first row.
	for (int j = 1; j < n; j++)
		tc[0][j] = tc[0][j-1] + cost[0][j];

	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			tc[i][j] = cost[i][j] + min(tc[i-1][j-1], 
							tc[i-1][j], tc[i][j-1]);
		}
	}
	return tc[m-1][n-1];
}

int main() {
	int cost[3][3] = {{1, 3, 4}, {4, 7, 5}, {1, 5, 3}};
	printf("%d\n", minGridCost(3,cost, 3, 3));
	printf("%d\n", minGridCostBU(3, 3, cost));
}

/*
11
11
*/