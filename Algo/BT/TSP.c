#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int tspUtil(int n, int graph[n][n], int path[], int pSize, int pCost, int visited[], int ans, int ansPath[]) {
    if(pCost > ans) // Ignore useless paths.
        return ans;
	
	int curr = path[n - 1];
	if (pSize == n && graph[curr][0] > 0){
		if(ans > pCost + graph[curr][0]) {
			for (int i = 0; i <= n; i++) {
				ansPath[i] = path[i%n];
			}
			return pCost + graph[curr][0];
		}
		return ans;
	}

	for (int i = 0; i < n; i++)	{
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
	path[0] = 0;
	visited[0] = 1;
	int ans = 99999;
	ans = tspUtil(n, graph, path, 1, 0, visited, ans, ansPath);
	printf("Shortest Path weight: %d\n", ans);
	printf("Shortest Path is: ");
	for (int i = 0; i <= n; i++) 
            printf("%d ", ansPath[i]);
	printf("\n");
	return ans;
}

int main() {
	int n = 4;
	int graph[4][4] = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
	tsp(n, graph);
	return 0;
}
/*
Shortest Path weight: 65
Shortest Path is: 0 1 2 3 0 
*/