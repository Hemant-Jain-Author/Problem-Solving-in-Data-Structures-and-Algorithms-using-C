#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double min(int a, int b) {
	return (a < b)? a : b;
}

int tspUtil(int n, int graph[n][n], 
		int path[], int pSize, int pCost, 
		int visited[], int ans)
{
	int curr = path[n - 1];
	if (pSize == n && graph[curr][0] > 0)
	{
		ans = min(ans, pCost + graph[curr][0]);
		return ans;
	}

	for (int i = 0; i < n; i++)
	{
		if (visited[i] == 0 && graph[curr][i] > 0)
		{
			visited[i] = 1;
			path[pSize] = i;
			ans = tspUtil(n, graph, path, pSize+1, pCost + graph[curr][i],visited, ans);
			visited[i] = 0;
		}
	}
	return ans;
}

int tsp(int n, int graph[n][n])
{

	int visited[n];
	int  path[n];
	for(int i = 0; i < n; i++)
	{
		visited[i] = 0;
		path[i] = 0;
	}	
	path[0] = 0;
	visited[0] = 1;
	int ans = 99999;
	ans = tspUtil(n, graph, path, 1, 0, visited, ans);
	return ans;
}

int main()
{
	int n = 4;
	int graph[4][4] = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
	printf("Minimum path cost : %d", tsp(n, graph));
	return 0;
}
/*
Minimum path cost : 65
*/