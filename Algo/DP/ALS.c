#include <stdio.h>
#include<stdlib.h>

int min(int a, int b) {
	return (a < b)? a : b;
}

int fastestWayBU2(int n, int a[][n], int t[][n],	int e[], int x[]) {
	int f1[n], f2[n];
	for(int i=0;i<n;i++) {
		f1[i] = 0;
		f2[i] = 0;	
	}

	// Time taken to leave first station.
	f1[0] = e[0] + a[0][0];
	f2[0] = e[1] + a[1][0];

	// Fill the tables f1[] and f2[] using bottom up approach.
	for (int i = 1; i < n; ++i) {
		f1[i] = min(f1[i - 1] + a[0][i], f2[i - 1] + t[1][i - 1] + a[0][i]);
		f2[i] = min(f2[i - 1] + a[1][i], f1[i - 1] + t[0][i - 1] + a[1][i]);
	}

	// Consider exit times and return minimum.
	return min(f1[n - 1] + x[0], f2[n - 1] + x[1]);
}

int fastestWayBU(int n, int a[][n], int t[][n], int e[], int x[]) {
	int f[2][n];
	for(int i=0;i<n;i++) {
		f[0][i] = 0;
		f[1][i] = 0;	
	}
	
	// Time taken to leave first station.
	f[0][0] = e[0] + a[0][0];
	f[1][0] = e[1] + a[1][0];

	// Fill the tables f1[] and f2[] using bottom up approach.
	for (int i = 1; i < n; ++i) {
		f[0][i] = min(f[0][i - 1] + a[0][i], f[1][i - 1] + t[1][i - 1] + a[0][i]);
		f[1][i] = min(f[1][i - 1] + a[1][i], f[0][i - 1] + t[0][i - 1] + a[1][i]);
	}

	// Consider exit times and return minimum.
	return min(f[0][n - 1] + x[0], f[1][n - 1] + x[1]);
}

void fastestWayTDUtil(int n, int  f[][n], int  a[][n], int  t[][n], int i) {
	if (i == 0)
		return;

	fastestWayTDUtil(n, f, a, t, i - 1);

	// Fill the tables f1[] and f2[] using top-down approach.
	f[0][i] = min(f[0][i - 1] + a[0][i], f[1][i - 1] + t[1][i - 1] + a[0][i]);
	f[1][i] = min(f[1][i - 1] + a[1][i], f[0][i - 1] + t[0][i - 1] + a[1][i]);
}

int fastestWayTD(int n, int a[][n], int t[][n], int e[], int x[]) {
	int f[2][n];
	for(int i=0;i<n;i++) {
		f[0][i] = 0;
		f[1][i] = 0;	
	}

	// Time taken to leave first station.
	f[0][0] = e[0] + a[0][0];
	f[1][0] = e[1] + a[1][0];

	fastestWayTDUtil(n, f, a, t, n - 1);
	return min(f[0][n - 1] + x[0], f[1][n - 1] + x[1]);
}

int main() {
	int a[][6] ={{7, 9, 3, 4, 8, 4}, {8, 5, 6, 4, 5, 7}};
	int t[][6] ={{2, 3, 1, 3, 4}, {2, 1, 2, 2, 1}};
	int e[] = {2, 4};
	int x[] = {3, 2};
	int n = 6;
	printf("fastestWay : %d\n", fastestWayBU2(n, a, t, e, x));
	printf("fastestWay : %d\n", fastestWayBU(n, a, t, e, x));
	printf("fastestWay : %d\n", fastestWayTD(n, a, t, e, x));
}

/*
fastestWay : 38
fastestWay : 38
fastestWay : 38
*/