#include<stdio.h>

void printSolution(int V, int colour[]) {
	printf("Assigned colours are::"); 
	for (int i = 0; i < V; i++)
		printf(" %d" , colour[i]);
	
	printf("\n");
}

int isSafe2(int V, int graph[][V], int colour[]) {
	for (int i = 0; i < V; i++) 	{
		for (int j = i + 1; j < V; j++) {
			if (graph[i][j] && colour[j] == colour[i])
				return 0;
		}
	}
	return 1;
}

int graphColouring2Util(int V, int graph[][V], int m, int colour[], int i) {
	if (i == V) {
		if (isSafe2(V, graph, colour)) {
			printSolution(V, colour);
			return 1;
		}
		return 0;
	}

	// Assign each colour from 1 to m
	for (int j = 1; j <= m; j++) {
		colour[i] = j;
		if (graphColouring2Util(V, graph, m, colour, i + 1)) 
			return 1;
	}
	return 0;
}

int graphColouring2(int V, int graph[][V], int m) {
	int  colour[V];
	if (graphColouring2Util(V, graph, m, colour, 0)) 
		return 1;

	return 0;
}

int isSafe(int V, int graph[][V], int colour[], int v, int c) {
	for (int i = 0; i < V; i++) {
		if (graph[v][i] == 1 && c == colour[i])
			return 0;
	}
	return 1;
}

int graphColouringUtil(int V, int graph[][V], int m, int colour[], int i) {
	if (i == V) {
		printSolution(V, colour);
		return 1;
	}

	for (int j = 1; j <= m; j++) {
		if (isSafe(V, graph, colour, i, j)) {
			colour[i] = j;
			if (graphColouringUtil(V, graph, m, colour, i + 1))
				return 1;
		}
	}
	return 0;
}

int graphColouring(int V, int graph[][V], int m) {
	int colour[V];
	if (graphColouringUtil(V, graph, m, colour, 0))
		return 1;

	return 0;
}

int main() {
	int graph[][5] = {{0, 1, 0, 0, 1},
					  {1, 0, 1, 0, 1},
					  {0, 1, 0, 1, 1},
					  {0, 0, 1, 0, 1},
					  {1, 1, 1, 1, 0}};
	int V = 5; // Number of vertices
	int m = 4; // Number of colours
	if (!graphColouring2(V, graph, m)) 
		printf("Solution does not exist");
	
	if (!graphColouring(V, graph, m))
		printf("Solution does not exist");

	return 0;
}

/*
Assigned colours are:: 1 2 1 2 3
Assigned colours are:: 1 2 1 2 3
*/