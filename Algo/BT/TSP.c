#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int tspUtil(int n, int graph[n][n], int path[], int pSize, int pCost, int visited[], int ans, int ansPath[]) {
    if(pCost >= ans) // Ignore useless paths.
        return ans;
	
	int curr = path[pSize - 1];
	if (pSize == n) {
		int first = path[0];
		if(graph[curr][first] > 0 && ans > pCost + graph[curr][first]) {
			for (int i = 0; i <= n; i++) {
				ansPath[i] = path[i%n];
			}
			ans = pCost + graph[curr][first];
		} 
		return ans;
	}

	for (int i = 0; i < n ; i++)	{
		if (visited[i] == 0 && graph[curr][i] > 0) {
			visited[i] = 1;
			path[pSize] = i;
			ans = tspUtil(n, graph, path, pSize+1, pCost + graph[curr][i],visited, ans, ansPath);
			visited[i] = 0;
		}
	}
	return ans;
}

int tsp(int n, int graph[n][n]) {
	int visited[n];
	int  path[n];
	int  ansPath[n+1];

	for(int i = 0; i < n; i++) {
		visited[i] = 0;
		path[i] = 0;
	}
	
	int source = 0;
	path[0] = source;
	visited[source] = 1;
	
	int ans = 99999;
	ans = tspUtil(n, graph, path, 1 /*path length*/, 0 /*path cost*/, 
					visited, ans, ansPath);
	printf("Shortest Path weight: %d\n", ans);
	printf("Shortest Path is: ");
	for (int i = 0; i <= n; i++) 
            printf("%d ", ansPath[i]);
	return ans;
}

int main() {
	int n = 4;
	int graph[4][4] = {{0, 1, 5, 10}, 
					   {1, 0, 25, 15}, 
					   {5, 25, 0, 20}, 
					   {10, 15, 20, 0}};

	tsp(n, graph);
	return 0;
}

/*
Shortest Path weight: 41
Shortest Path is: 0 1 3 2 0 
*/