#include <stdio.h>
#include<stdlib.h>

const int INF = 99999;

void printSolution(int V, int dist[V][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				printf("INF ");
			else
				printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
}

void floydWarshall(int V, int graph[V][V]) { // Bottom up.
	int dist[V][V];
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			dist[i][j] = graph[i][j]; // Direct path.

	for (int k = 0; k < V; k++) { // Pick intermediate vertices.
		for (int i = 0; i < V; i++) { // Pick source vertices one by one.
			for (int j = 0; j < V; j++) { // Pick destination vertices.
				// If we have shorter path from i to j via k, then update dist[i][j]
				if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	// Print the shortest distance matrix
	printSolution(V, dist);
}

int main() {
	int graph[7][7] =
	{
		{0, 2, 4, INF, INF, INF, INF},
		{2, 0, 4, 1, INF, INF, INF},
		{4, 4, 0, 2, 8, 4, INF},
		{INF, 1, 2, 0, 3, INF, 6},
		{INF, INF, 6, 4, 0, 3, 1},
		{INF, INF, 4, INF, 4, 0, 2},
		{INF, INF, INF, 4, 2, 3, 0}
	};
	floydWarshall(7, graph);
}

/*
0 2 4 3 6 8 7 
2 0 3 1 4 7 5 
4 3 0 2 5 4 6 
3 1 2 0 3 6 4 
7 5 6 4 0 3 1 
8 7 4 6 4 0 2 
7 5 6 4 2 3 0 
*/