#include <stdio.h>
#include<stdlib.h>

int INFINITE = 99999;

int shortestDist(int n, int graph[][n]) {
	// dist[i] is going to store shortest distance from node i to node n-1.
	int dist[n];
	int path[n];
	for (int i = 0; i < n; i++)
		dist[i] = INFINITE;

	int value;
	dist[0] = 0;
	path[0] = -1;

	// Calculating shortest path for the nodes
	for (int i = 0; i < n; i++) {
		// Check all nodes of next 
		for (int j = i; j < n; j++) {
			// Reject if no edge exists
			if (graph[i][j] == INFINITE)
			{
				continue;
			}
			value = graph[i][j] + dist[i];
			if (dist[j] > value)
			{
				dist[j] = value;
				path[j] = i;
			}
		}
	}
	value = n - 1;
	while (value != -1) {
		printf("%d ", value);
		value = path[value];
	}
	printf("\n");
	return dist[n - 1];
}

int main() {
	// Graph stored in the form of an adjacency Matrix
	int n = 8;
	int graph[][8] =
	{
		{INFINITE, 1, 2, 5, INFINITE, INFINITE, INFINITE, INFINITE},
		{INFINITE, INFINITE, INFINITE, INFINITE, 4, 11, INFINITE, INFINITE},
		{INFINITE, INFINITE, INFINITE, INFINITE, 9, 5, 16, INFINITE},
		{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 2, INFINITE},
		{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 18},
		{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 13},
		{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 2},
		{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE}
	};
	
	printf("%d\n", shortestDist(n, graph));
}
/*
7 6 3 0 
9
*/