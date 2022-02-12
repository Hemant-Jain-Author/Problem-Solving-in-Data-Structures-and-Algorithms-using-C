#include "GraphAM.h"

Graph* createGraph(int count) {
    Graph *gph = (Graph *)malloc(sizeof(Graph));
    gph->count = count;
    gph->adj = (int **)malloc(count * sizeof(int *));
    for (int i = 0; i < count; i++) {
        gph->adj[i] = (int *)calloc(count, sizeof(int));
    }
    return gph;
}

void addDirectedEdge(Graph *gph, int src, int dst, int cost) {
    gph->adj[src][dst] = cost;
}

void addUndirectedEdge(Graph *gph, int src, int dst, int cost) {
    addDirectedEdge(gph, src, dst, cost);
    addDirectedEdge(gph, dst, src, cost);
}

void printGraph(Graph *gph) {
    int count = gph->count;
    for (int i = 0; i < count; i++) {
        printf("Vertex %d is connected to ::", i);
        for (int j = 0; j < count; j++) {
            if (gph->adj[i][j] != 0)
                printf(" %d(%d) ", j, gph->adj[i][j]);
        }
        printf("\n");
    }
}

int main1() {
    Graph* graph = createGraph(4);
    addUndirectedEdge(graph, 0, 1, 1);
    addUndirectedEdge(graph, 0, 2, 1);
    addUndirectedEdge(graph, 1, 2, 1);
    addUndirectedEdge(graph, 2, 3, 1);
    printGraph(graph);
    return 0;
}

/*
Vertex 0 is connected to :: 1(1)  2(1) 
Vertex 1 is connected to :: 0(1)  2(1) 
Vertex 2 is connected to :: 0(1)  1(1)  3(1) 
Vertex 3 is connected to :: 2(1) 
*/

int HamiltonianCycleUtil(Graph *graph, int path[], int pSize, int added[]) {
    // Base case full length path is found
    // this last check can be modified to make it a path.
    if (pSize == graph->count) {
        if (graph->adj[path[pSize - 1]][path[0]] == 1) {
            path[pSize] = path[0];
            return 1;
        } 
        else
            return 0;
    }
    for (int vertex = 0; vertex < graph->count; vertex++) {
        // there is a path from last element and next vertex
        if (pSize == 0 || (graph->adj[path[pSize - 1]][vertex] == 1 && added[vertex] == 0)) {
            path[pSize++] = vertex;
            added[vertex] = 1;
            if (HamiltonianCycleUtil(graph, path, pSize, added))
                return 1;
            // backtracking
            pSize--;
            added[vertex] = 0;
        }
    }
    return 0;
}

int HamiltonianCycle(Graph *graph) {
    int *path = (int *)calloc(graph->count + 1, sizeof(int));
    int *added = (int *)calloc(graph->count, sizeof(int));
    if (HamiltonianCycleUtil(graph, path, 0, added)) {
        printf("Hamiltonian Cycle found :: ");
        for (int i = 0; i <= graph->count; i++)
            printf("%d ", path[i]);
        return 1;
    }
    printf("Hamiltonian Cycle not found");
    return 0;
}

int HamiltonianPathUtil(Graph *graph, int path[], int pSize, int added[]) {
    // Base case full length path is found
    if (pSize == graph->count) {
        return 1;
    }
    for (int vertex = 0; vertex < graph->count; vertex++) {
        // there is a path from last element and next vertex
        // and next vertex is not already included in path.
        if (pSize == 0 || (graph->adj[path[pSize - 1]][vertex] == 1 && added[vertex] == 0)) {
            path[pSize++] = vertex;
            added[vertex] = 1;
            if (HamiltonianPathUtil(graph, path, pSize, added))
                return 1;
            // backtracking
            pSize--;
            added[vertex] = 0;
        }
    }
    return 0;
}
int HamiltonianPath(Graph *graph) {
    int *path = (int *)calloc(graph->count, sizeof(int));
    int *added = (int *)calloc(graph->count, sizeof(int));

    if (HamiltonianPathUtil(graph, path, 0, added)) {
        printf("Hamiltonian Path found :: ");
        for (int i = 0; i < graph->count; i++)
            printf("%d ", path[i]);

        return 1;
    }

    printf("Hamiltonian Path not found");
    return 0;
}

	int main2() {
		int count = 5;
		int adj[5][5] = {{0, 1, 0, 1, 0},
						 {1, 0, 1, 1, 0},
						 {0, 1, 0, 0, 1},
						 {1, 1, 0, 0, 1},
						 {0, 1, 1, 1, 0}};
	
		Graph* graph = createGraph(count);
		for (int i = 0; i < count; i++)
			for (int j = 0; j < count; j++)
				if (adj[i][j])
					addDirectedEdge(graph, i, j, 1);
		int retval = HamiltonianPath(graph);
		printf("\nHamiltonianPath : %d \n", retval);
		retval = HamiltonianCycle(graph);
		printf("\nHamiltonianCycle : %d \n", retval);
	
		int adj2[5][5] = {{0, 1, 0, 1, 0},
						  {1, 0, 1, 1, 0},
						  {0, 1, 0, 0, 1},
						  {1, 1, 0, 0, 0},
						  {0, 1, 1, 0, 0}};
		Graph* graph2 = createGraph(count);
	
		for (int i = 0; i < count; i++)
			for (int j = 0; j < count; j++)
				if (adj2[i][j])
					addDirectedEdge(graph2, i, j, 1);
	
		retval = HamiltonianPath(graph2);
		printf("\nHamiltonianPath : %d \n", retval);
		retval = HamiltonianCycle(graph2);
		printf("\nHamiltonianCycle : %d \n", retval);
		return 0;
	}

int INFINITE = 99999;

int dijkstra(Graph *gph, int source) {
    int count = gph->count;
    int previous[count];
    int dist[count];
    int visited[count];
    for(int i = 0;i<count;i++) {
        previous[i] = -1;
        dist[i] = INFINITE;
        visited[i] = 0;
    }

    dist[source] = 0;

    Heap* pq = createHeap(greater);
    GraphEdge *edge = createGraphEdge(source, source, 0);
    heapAdd(pq, edge);

    while (heapSize(pq) != 0) {
        edge = heapRemove(pq);
        source = edge->dest;
        visited[source] = 1;

        for (int dest = 0; dest < count; dest++) {
            int alt = gph->adj[source][dest] + dist[source];
            if (gph->adj[source][dest] > 0 && 
            alt < dist[dest] && visited[dest] == 0) {
                dist[dest] = alt;
                previous[dest] = source;
                edge = createGraphEdge(source, dest, alt);
                heapAdd(pq, edge);
            }
        }
    }
    for (int i = 0; i < gph->count; i++) {
        if (dist[i] == INFINITE)
            printf("node id %d prev %d cost : Unreachable", i, previous[i]);
        else
            printf("node id %d prev %d cost : %d\n", i, previous[i], dist[i]);
    }
}

int PrimsMST(Graph *gph) {
    int count = gph->count;
    int previous[count];
    int dist[count];
    int visited[count];
    for(int i = 0;i<count;i++) {
        previous[i] = -1;
        dist[i] = INFINITE;
        visited[i] = 0;
    }
    int source = 0;
    dist[source] = 0;

    Heap* pq = createHeap(greater);
    GraphEdge *edge = createGraphEdge(source, source, 0);
    heapAdd(pq, edge);

    while (heapSize(pq) != 0) {
        edge = heapRemove(pq);
        source = edge->dest;
        visited[source] = 1;

        for (int dest = 0; dest < count; dest++) {
            int alt = gph->adj[source][dest];
            if (gph->adj[source][dest] > 0 && 
            alt < dist[dest] && visited[dest] == 0) {
                dist[dest] = alt;
                previous[dest] = source;
                edge = createGraphEdge(source, dest, alt);
                heapAdd(pq, edge);
            }
        }
    }
    int total = 0;
    printf("Edges are ");
    for (int i = 0; i < gph->count; i++) {
        if (dist[i] == INFINITE)
            printf("(%d is unreachable.)", i);
        else if(previous[i] != -1) {
            printf("(%d, %d, %d) ", previous[i], i, dist[i]);
            total += dist[i];
        }
    }
    printf("\nTotal MST cost: %d\n", total);
}

int main3() {
    int count = 9;
    Graph* graph = createGraph(count);
    addUndirectedEdge(graph, 0, 1, 4);
    addUndirectedEdge(graph, 0, 7, 8);
    addUndirectedEdge(graph, 1, 2, 8);
    addUndirectedEdge(graph, 1, 7, 11);
    addUndirectedEdge(graph, 2, 3, 7);
    addUndirectedEdge(graph, 2, 8, 2);
    addUndirectedEdge(graph, 2, 5, 4);
    addUndirectedEdge(graph, 3, 4, 9);
    addUndirectedEdge(graph, 3, 5, 14);
    addUndirectedEdge(graph, 4, 5, 10);
    addUndirectedEdge(graph, 5, 6, 2);
    addUndirectedEdge(graph, 6, 7, 1);
    addUndirectedEdge(graph, 6, 8, 6);
    addUndirectedEdge(graph, 7, 8, 7);
    dijkstra(graph, 0);
    PrimsMST(graph);
}

int main() {
    main1();
    main2();
    main3();
}