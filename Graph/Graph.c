#include "Graph.h"

Graph* createGraph(int count) {
    Graph* gph = (Graph*)malloc(sizeof(Graph));
    gph->count = count;
    gph->adj = (GraphEdge **)malloc((count) * sizeof(GraphEdge*));
    for (int i = 0; i < count; i++)
        gph->adj[i] = NULL;
    return gph;
}

GraphEdge* createGraphEdge(int src, int dst, int cost) {
    GraphEdge *edge = (GraphEdge *)malloc(sizeof(GraphEdge));
    edge->src = src;
    edge->dest = dst;
    edge->cost = cost;
    return edge;
}

void addDirectedEdge(Graph *gph, int src, int dst, int cost) {
    GraphEdge *edge = createGraphEdge(src, dst, cost); 
    edge->next = gph->adj[src];
    gph->adj[src] = edge;
}

void addUndirectedEdge(Graph *gph, int src, int dst, int cost) {
    addDirectedEdge(gph, src, dst, cost);
    addDirectedEdge(gph, dst, src, cost);
}

void printGraph(Graph *gph) {
    if (!gph)
        return;

    for (int i = 0; i < gph->count; i++) {
        GraphEdge* head = gph->adj[i];
        printf("Vertex %d is connected to ::", i);
        while (head) {
            printf(" %d(%d) ", head->dest, head->cost);
            head = head->next;
        }
        printf("\n");
    }
}

int main1() {
    int nodeCount = 4;
    Graph* gph = createGraph(nodeCount);
    addUndirectedEdge(gph, 0, 1, 1);
    addUndirectedEdge(gph, 0, 2, 1);
    addUndirectedEdge(gph, 1, 2, 1);
    addUndirectedEdge(gph, 2, 3, 1);
    printGraph(gph);
    return 0;
}

/*
Vertex 0 is connected to :: 2(1)  1(1) 
Vertex 1 is connected to :: 2(1)  0(1) 
Vertex 2 is connected to :: 3(1)  1(1)  0(1) 
Vertex 3 is connected to :: 2(1) 
*/

void dfsUtil(Graph *gph, int index, int *visited) {
    visited[index] = 1;
    GraphEdge *head = gph->adj[index];
    while (head) {
        if (visited[head->dest] == 0)
            dfsUtil(gph, head->dest, visited);
        head = head->next;
    }
}

int DFS(Graph *gph, int source, int target) {
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    dfsUtil(gph, source, visited);
    return visited[target];
}

int DFSStack(Graph *gph, int source, int target) {
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int curr, destination;
    Stack* stk = createStack(20);
    stackPush(stk, source);
    visited[source] = 1;
    while (stackSize(stk) != 0) {
        curr = stackPop(stk);
        GraphEdge *head = gph->adj[curr];
        while (head) {
            destination = head->dest;
            if (visited[destination] == 0) {
                stackPush(stk, destination);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return visited[target];
}

int BFS(Graph *gph, int source, int target) {
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    visited[source] = 1;
    int curr, destination;
    Queue* que = createQueue();
    queueAdd(que, source);
    while (queueSize(que) != 0) {
        curr = queueRemove(que);
        GraphEdge *head = gph->adj[curr];
        while (head) {
            destination = head->dest;
            if (visited[destination] == 0) {
                queueAdd(que, destination);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return visited[target];
}

int bestFirstSearchPQ(Graph *gph, int source, int destination) {
    int count = gph->count;
    int previous[count];
    int dist[count];
    int visited[count];
    for(int i = 0;i<count;i++) {
        previous[i] = -1;
        dist[i] = 99999;
        visited[i] = 0;
    }
    dist[source] = 0;

    Heap* pq = createHeap(greater);
    GraphEdge *edge = createGraphEdge(source, source, 0);
    heapAdd(pq, edge);

	while (heapSize(pq) != 0) {
		edge = heapRemove(pq);
		if (edge->dest == destination)
			return 1;

		source = edge->dest;
		visited[source] = 1;

		GraphEdge *head = gph->adj[source];
		while (head) {
			int curr = head->dest;
			int cost = head->cost;
			int alt = cost + dist[source];
			if (alt < dist[curr] && visited[curr] == 0)
			{
				dist[curr] = alt;
				previous[curr] = source;
                edge = createGraphEdge(source, curr, 0);
				heapAdd(pq, edge);
			}
			head = head->next;
		}
	}
	return 0;
}

int main2() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 0, 1, 3);
    addDirectedEdge(gph, 0, 4, 2);
    addDirectedEdge(gph, 1, 2, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 4, 1, 2);
    addDirectedEdge(gph, 4, 3, 1);
    printf("Path between 0 & 6 : %d\n", DFS(gph, 0, 2));
    printf("Path between 0 & 6 : %d\n", DFSStack(gph, 0, 2));
    printf("Path between 0 & 6 : %d\n", BFS(gph, 0, 2));
    printf("Path between 0 & 6 : %d\n", bestFirstSearchPQ(gph, 0, 2));
    return 0;
}

/*
Path between 0 & 6 : 1
Path between 0 & 6 : 1
Path between 0 & 6 : 1
Path between 0 & 6 : 1
*/

void dfsUtil2(Graph *gph, int index, int *visited, Stack *stk) {
    visited[index] = 1;
    GraphEdge* head = gph->adj[index];
    while (head) {
        if (visited[head->dest] == 0)
            dfsUtil2(gph, head->dest, visited, stk);
        head = head->next;
    }
    stackPush(stk, index);
}

void TopologicalSort(Graph *gph) {
    Stack* stk = createStack(100);
    int *visited = (int *)calloc(gph->count, sizeof(int));
    for (int i = 0; i < gph->count; i++) {
        if (visited[i] == 0) {
            dfsUtil2(gph, i, visited, stk);
        }
    }

    printf("TopologicalSort :: ");
    while (stackSize(stk) != 0)
        printf("%d ", stackPop(stk));
    printf("\n");
}

int main3() {
    Graph* gph = createGraph(9);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 1, 2, 1);
    addDirectedEdge(gph, 1, 3, 1);
    addDirectedEdge(gph, 1, 4, 1);
    addDirectedEdge(gph, 3, 2, 1);
    addDirectedEdge(gph, 3, 5, 1);
    addDirectedEdge(gph, 4, 5, 1);
    addDirectedEdge(gph, 4, 6, 1);
    addDirectedEdge(gph, 5, 7, 1);
    addDirectedEdge(gph, 6, 7, 1);
    addDirectedEdge(gph, 7, 8, 1);
    TopologicalSort(gph);
    return 0;
}

/*
TopologicalSort :: 1 3 4 5 6 7 8 0 2 
*/


int pathExist(Graph *gph, int source, int destination) {
    int *visited = (int *)calloc(gph->count, sizeof(int));
    dfsUtil(gph, source, visited);
    return visited[destination];
}

int main4() {
    Graph* gph = createGraph(6);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 1, 3, 1);
    addDirectedEdge(gph, 3, 4, 1);
    addDirectedEdge(gph, 1, 4, 1);
    printf("PathExist :: %d", pathExist(gph, 0, 4));
    return 0;
}

/*
PathExist :: 1
*/

int countAllPathDFS(Graph *gph, int *visited, int source, int dest) {
    if (source == dest)
        return 1;

    int count = 0;
    int destination;
    visited[source] = 1;
    GraphEdge *head = gph->adj[source];
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0)
            count += countAllPathDFS(gph, visited, destination, dest);
        head = head->next;
    }
    visited[source] = 0;
    return count;
}

int countAllPath(Graph *gph, int src, int dest) {
    int *visited = (int *)calloc(gph->count, sizeof(int));
    return countAllPathDFS(gph, visited, src, dest);
}

void printAllPathDFS(Graph *gph, int *visited, int source, int dest, Stack *path) {
    int destination;
    stackPush(path, source);
    if (source == dest) {
        stackPrint(path);
        stackPop(path);
        return;
    }
    visited[source] = 1;

    GraphEdge *head = gph->adj[source];
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0) {
            printAllPathDFS(gph, visited, destination, dest, path);
        }
        head = head->next;
    }
    visited[source] = 0;
    stackPop(path);
}

void printAllPath(Graph *gph, int src, int dest) {
    int *visited = (int *)calloc(gph->count, sizeof(int));
    Stack* stk = createStack(100);
    printAllPathDFS(gph, visited, src, dest, stk);
}

int main5() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 1, 3, 1);
    addDirectedEdge(gph, 3, 4, 1);
    addDirectedEdge(gph, 1, 4, 1);
    printf("All path count : %d\n", countAllPath(gph, 0, 4));
    printAllPath(gph, 0, 4);
    return 0;
}
/*
All path count : 3
[4 3 2 0 ]
[4 1 0 ]
[4 3 1 0 ]
*/
int rootVertex(Graph *gph) {
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int retVal = -1;
    for (int i = 0; i < count; i++) {
        if (visited[i] == 0) {
            dfsUtil(gph, i, visited);
            retVal = i;
        }
    }
    for (int i = 0; i < count; i++)
        visited[i] = 0;

    dfsUtil(gph, retVal, visited);
    for (int i = 0; i < count; i++){
        if (visited[i] == 0) {
            printf("Disconnected graph!");
            return -1;
        }
    }
    printf("Root vertex is :: %d ", retVal);
    return retVal;
}

int main6() {
    Graph* gph = createGraph(7);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 1, 3, 1);
    addDirectedEdge(gph, 4, 1, 1);
    addDirectedEdge(gph, 6, 4, 1);
    addDirectedEdge(gph, 5, 6, 1);
    addDirectedEdge(gph, 5, 2, 1);
    addDirectedEdge(gph, 6, 0, 1);
    rootVertex(gph);
    return 0;
}

/*
Root vertex is :: 5
*/

void transitiveClosureUtil(Graph *gph, int source, int index, int **tc) {
    if (tc[source][index] == 1)
        return;

    tc[source][index] = 1;
    GraphEdge *head = gph->adj[index];
    
    while (head) {
        transitiveClosureUtil(gph, source, head->dest, tc);
        head = head->next;
    }
}

int **transitiveClosure(Graph *gph) {
    int count = gph->count;
    int **tc = (int **)calloc(count, sizeof(int *));
    for (int i = 0; i < count; i++)
        tc[i] = (int *)calloc(count, sizeof(int));

    for (int i = 0; i < count; i++)
        transitiveClosureUtil(gph, i, i, tc);

    return tc;
}

int main7() {
    Graph* gph = createGraph(4);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 1, 2, 1);
    addDirectedEdge(gph, 2, 0, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 3, 3, 1);
    int **tc = transitiveClosure(gph);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf(" %d ", tc[i][j]);
        }
        printf("\n");
    }
    return 0;
}
/*
 1  1  1  1 
 1  1  1  1 
 1  1  1  1 
 0  0  0  1 
 */

void BFSLevelNode(Graph *gph, int source) {
    int *visited = (int *)calloc(gph->count, sizeof(int));
    visited[source] = 1;
    Queue* que = createQueue();
    queueAdd(que, source);
    queueAdd(que, 0);
    printf("Node - Level\n");
    while (queueSize(que) != 0) {
        int curr = queueRemove(que);
        int depth = queueRemove(que);
        printf("%d - %d\n", curr, depth);
        GraphEdge *head = gph->adj[curr];
        while (head) {
            int destination = head->dest;
            if (visited[destination] == 0) {
                queueAdd(que, destination);
                queueAdd(que, depth + 1);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
}

int BFSDistance(Graph *gph, int source, int dest) {
    int *visited = (int *)calloc(gph->count, sizeof(int));
    Queue* que = createQueue();
    queueAdd(que, source);
    queueAdd(que, 0);
    visited[source] = 1;
    while (queueSize(que) != 0) {
        int curr = queueRemove(que);
        int depth = queueRemove(que);
        GraphEdge *head = gph->adj[curr];
        while (head) {
            int destination = head->dest;
            if (destination == dest)
                return depth + 1;
            if (visited[destination] == 0) {
                queueAdd(que, destination);
                queueAdd(que, depth + 1);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return -1;
}

int main8() {
    Graph* gph = createGraph(7);
    addUndirectedEdge(gph, 0, 1, 1);
    addUndirectedEdge(gph, 0, 2, 1);
    addUndirectedEdge(gph, 0, 4, 1);
    addUndirectedEdge(gph, 1, 2, 1);
    addUndirectedEdge(gph, 2, 5, 1);
    addUndirectedEdge(gph, 3, 4, 1);
    addUndirectedEdge(gph, 4, 5, 1);
    addUndirectedEdge(gph, 4, 6, 1);
    BFSLevelNode(gph, 1);
    printf("BFSDistance(1, 6) : %d ", BFSDistance(gph, 1, 6));
    return 0;
}
/*
Node - Level
1 - 0
2 - 1
0 - 1
5 - 2
4 - 2
6 - 3
3 - 3
BFSDistance(1, 6) : 3 
*/

int isCyclePresentUndirectedDFS(Graph *graph, int index, int parentIndex, int *visited) {
    visited[index] = 1;
    GraphEdge *head = graph->adj[index];
    while (head) {
        int dest = head->dest;
        if (visited[dest] == 0) {
            if (isCyclePresentUndirectedDFS(graph, dest, index, visited))
                return 1;
        } else if (parentIndex != dest)
            return 1;
        head = head->next;
    }
    return 0;
}

int isCyclePresentUndirected(Graph *graph) {
    int *visited = (int *)calloc(graph->count, sizeof(int));
    for (int i = 0; i < graph->count; i++)
        if (visited[i] == 0)
            if (isCyclePresentUndirectedDFS(graph, i, -1, visited))
                return 1;
    return 0;
}

int main9() {
    Graph* gph = createGraph(6);
    addUndirectedEdge(gph, 0, 1, 1);
    addUndirectedEdge(gph, 1, 2, 1);
    addUndirectedEdge(gph, 3, 4, 1);
    addUndirectedEdge(gph, 4, 2, 1);
    addUndirectedEdge(gph, 2, 5, 1);
    // addUndirectedEdge(gph, 4, 1, 1);
    printf("isCyclePresentUndirected : %d\n", isCyclePresentUndirected(gph));
    return 0;
}

/*
isCyclePresentUndirected : 0
*/

int isCyclePresentDFS(Graph *graph, int index, int *visited, int *marked) {
    visited[index] = 1;
    marked[index] = 1;

    GraphEdge *head = graph->adj[index];
    while (head) {
        int dest = head->dest;
        if (marked[dest] == 1)
            return 1;

        if (visited[dest] == 0)
            if (isCyclePresentDFS(graph, dest, visited, marked))
                return 1;
        head = head->next;
    }
    marked[index] = 0;
    return 0;
}

int isCyclePresent(Graph *graph) {
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int *marked = (int *)calloc(count, sizeof(int));
    for (int index = 0; index < count; index++) {
        if (visited[index] == 0)
            if (isCyclePresentDFS(graph, index, visited, marked))
                return 1;
    }
    return 0;
}

int isCyclePresentDFSColor(Graph *graph, int index, int *visited) {
    visited[index] = 1; // 2 = grey
    int dest;

    GraphEdge *head = graph->adj[index];
    while (head) {
        dest = head->dest;
        if (visited[dest] == 1) //"Grey":
            return 1;

        if (visited[dest] == 0) //"White":
            if (isCyclePresentDFSColor(graph, dest, visited))
                return 1;
        head = head->next;
    }
    visited[index] = 2; // "Black"
    return 0;
}

int isCyclePresentColor(Graph *graph) {
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    for (int i = 0; i < count; i++) {
        if (visited[i] == 0) //"White"
            if (isCyclePresentDFSColor(graph, i, visited))
                return 1;
    }
    return 0;
}

int main10() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 1, 3, 1);
    addDirectedEdge(gph, 3, 4, 1);
    addDirectedEdge(gph, 4, 1, 1);
    printf("isCyclePresent : %d\n", isCyclePresent(gph));
    printf("isCyclePresent : %d\n", isCyclePresentColor(gph));
    return 0;
}

/*
isCyclePresent : 1
isCyclePresent : 1
*/

Graph *TransposeGraph(Graph *gph) {
    int count = gph->count;
    Graph *gph2 = createGraph(count);
    
    for (int i = 0; i < count; i++) {
        GraphEdge *head = gph->adj[i];
        while (head) {
            addDirectedEdge(gph2, head->dest, i, head->cost);
            head = head->next;
        }
    }
    return gph2;
}

int main11() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 1, 3, 1);
    addDirectedEdge(gph, 3, 4, 1);
    addDirectedEdge(gph, 4, 1, 1);

    Graph *gph2 = TransposeGraph(gph);
    printGraph(gph2);
    return 0;
}

/*
Vertex 0 is connected to ::
Vertex 1 is connected to :: 4(1)  0(1) 
Vertex 2 is connected to :: 0(1) 
Vertex 3 is connected to :: 2(1)  1(1) 
Vertex 4 is connected to :: 3(1)
*/

int isConnectedUndirected(Graph *gph) {
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    dfsUtil(gph, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

int main12() {
    Graph* gph = createGraph(6);
    addUndirectedEdge(gph, 0, 1, 1);
    addUndirectedEdge(gph, 1, 2, 1);
    addUndirectedEdge(gph, 3, 4, 1);
    addUndirectedEdge(gph, 4, 2, 1);
    addUndirectedEdge(gph, 2, 5, 1);
    //addDirectedEdge(gph, 4, 1, 1);
    printf("isConnectedUndirected :: %d", isConnectedUndirected(gph));
    return 0;
}

/*
isConnectedUndirected :: 1
*/

int isStronglyConnected(Graph *gph) {
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    dfsUtil(gph, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;

    Graph *gReversed = TransposeGraph(gph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;

    dfsUtil(gReversed, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

int main13() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 1, 2, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 3, 0, 1);
    addDirectedEdge(gph, 2, 4, 1);
    addDirectedEdge(gph, 4, 2, 1);
    printf("IsStronglyConnected:: %d \n", isStronglyConnected(gph));
    return 0;
}

/*
IsStronglyConnected:: 1 
*/

void DFSRec2(Graph *gph, int index, int *visited, Stack *stk) {
    visited[index] = 1;
    GraphEdge *head = gph->adj[index];
    while (head) {
        if (visited[head->dest] == 0)
            DFSRec2(gph, head->dest, visited, stk);
    
        head = head->next;
    }
    stackPush(stk, index);
}

void stronglyConnectedComponent(Graph *gph) {
    int count = gph->count;
    int index;
    int *visited = (int *)calloc(count, sizeof(int));
    Stack* stk = createStack(100);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            DFSRec2(gph, i, visited, stk);

    Graph *gReversed = TransposeGraph(gph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;
    
    while (stackSize(stk) != 0) {
        index = stackPop(stk);
        if (visited[index] == 0) {
            Stack* stk2 = createStack(100);
            DFSRec2(gReversed, index, visited, stk2);
            stackPrint(stk2);
        }
    }
}

int main14() {
    Graph* gph = createGraph(7);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 1, 2, 1);
    addDirectedEdge(gph, 2, 0, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 3, 4, 1);
    addDirectedEdge(gph, 4, 5, 1);
    addDirectedEdge(gph, 5, 3, 1);
    addDirectedEdge(gph, 5, 6, 1);
    stronglyConnectedComponent(gph);
    return 0;
}

/*
[0 2 1 ]
[3 5 4 ]
[6 ]
*/

int heightTreeParentArr(int arr[], int count) {
	Graph* gph = createGraph(count);
	int source;
	for (int i = 0; i < count; i++) {
		if (arr[i] != -1)
			addDirectedEdge(gph, arr[i], i, 1);
		else
			source = i;
	}
	int *visited = (int *)calloc(count, sizeof(int));
	visited[source] = 1;
	Queue* que = createQueue();
	queueAdd(que, source);
    queueAdd(que, 0);
	int maxHeight = 0;
	while (queueSize(que) != 0) {
		int curr = queueRemove(que);
        int height = queueRemove(que);
		if (height > maxHeight)
			maxHeight = height;
        
		GraphEdge *head = gph->adj[curr];
		while (head) {
			if (visited[head->dest] == 0)
			{
                visited[head->dest] = 1;
				queueAdd(que, head->dest);
                queueAdd(que, height + 1);			
			}
			head = head->next;
		}
	}
	return maxHeight;
}

int getHeight(int arr[], int count, int index) {
    if (arr[index] == -1)
        return 0;
    else
        return getHeight(arr, count, arr[index]) + 1;
}

int heightTreeParentArr2(int arr[], int count) {
    int *height = (int *)calloc(count, sizeof(int));
    int maxHeight = -1;
    for (int i = 0; i < count; i++) {
        height[i] = -1;
    }

    for (int i = 0; i < count; i++) {
        height[i] = getHeight(arr, count, i);
        maxHeight = max(maxHeight, height[i]);
    }
    return maxHeight;
}

int main15() {
    int parentArray[] = {-1, 0, 1, 2, 3};
    printf("Height : %d\n", heightTreeParentArr(parentArray, 5));
    printf("Height : %d\n", heightTreeParentArr2(parentArray, 5));
    return 0;
}

/*
Height : 4
Height : 4
*/


int isConnected(Graph *graph) {
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    GraphEdge *head;

    //Find a vertex with non - zero degree
    //DFS traversal of graph from a vertex with non - zero degree
    for (int i = 0; i < count; i++) {
        head = graph->adj[i];
        if (head) {
            dfsUtil(graph, i, visited);
            break;
        }
    }
    //Check if all non - zero degree count are visited
    for (int i = 0; i < count; i++) {
        head = graph->adj[i];
        if (head)
            if (visited[i] == 0 && head)
                return 0;
    }
    return 1;
}

void primsMST(Graph *gph) {
    int previous[gph->count];
    int dist[gph->count];
    int visited[gph->count];
    for(int i = 0;i<gph->count;i++) {
        previous[i] = -1;
        dist[i] = 99999;
        visited[i] = 0;
    }
    
    int source = 0;
    dist[source] = 0;
    previous[source] = source;

    Heap* pq = createHeap(greater);
    GraphEdge *edge = createGraphEdge(source, source, 0);
    heapAdd(pq, edge);
    GraphEdge *head;
    while (heapSize(pq) != 0) {
        edge = heapRemove(pq);
        source = edge->dest;
        visited[source] = 1;
        head = gph->adj[source];
        while (head) {
            int dest = head->dest;
            int alt = head->cost;

            if (alt < dist[dest] && visited[dest] == 0) {
                dist[dest] = alt;
                previous[dest] = source;
                edge = createGraphEdge(source, dest, alt);
                heapAdd(pq, edge);
            }
            head = head->next;
        }
    }
        
    int total = 0;
    printf("Edges are : ");
    for (int i = 0; i < gph->count; i++) {
        if (dist[i] == INFINITE)
            printf("(%d is unreachable.)", i);
        else if(previous[i] != i) {
            printf("(%d->%d @ %d) ", previous[i], i, dist[i]);
            total += dist[i];
        }
    }
    printf("\nTotal MST cost: %d\n", total);

}

void printPathUtil(int previous[], int source, int dest) {
    if (dest == source)
            printf("%d", source);
    else {
        printPathUtil(previous, source, previous[dest]);
        printf("->%d", dest);
    }
}

void printPath(int previous[], int dist[], int count, int source) {
    printf("Shortest Paths: ");
    for (int i = 0; i < count; i++) {
        if (dist[i] == INFINITE)
            printf("(%d->%d @ Unreachable) ", source, i);
        else if(i != previous[i]) {
            printf("(");
            printPathUtil(previous, source, i);
            printf(" @ %d) ", dist[i]);
        }
    }
    printf("\n");
}

void dijkstra(Graph *gph, int source) {
    int previous[gph->count];
    int dist[gph->count];
    int visited[gph->count];
    for(int i = 0;i<gph->count;i++) {
        previous[i] = -1;
        dist[i] = 99999;
        visited[i] = 0;
    }

    dist[source] = 0;
    previous[source] = source;
    
    Heap* pq = createHeap(greater);
    GraphEdge *edge = createGraphEdge(source, source, 0);
    heapAdd(pq, edge);
    GraphEdge *head;
    int curr;

    while (heapSize(pq) != 0) {
        edge = heapRemove(pq);
        curr = edge->dest;
        visited[curr] = 1;
        head = gph->adj[curr];
        while (head) {
            int dest = head->dest;
            int alt = head->cost + dist[curr];

            if (alt < dist[dest] && visited[dest] == 0) {
                dist[dest] = alt;
                previous[dest] = curr;
                edge = createGraphEdge(curr, dest, alt);
                heapAdd(pq, edge);
            }
            head = head->next;
        }
    }
    printPath(previous, dist, gph->count, source);
}

typedef struct Set_t {
    int parent;
    int rank;
}Set;

Set* createSets(int p, int r) {
    Set* set = (Set*)malloc(sizeof(Set));
	set->parent = p;
	set->rank = r;
    return set;
}

int findSetRoot(Set* sets[], int index) {
	int p = sets[index]->parent;
	while (p != index) {
		index = p;
		p = sets[index]->parent;
	}
	return index;
}

void unionSets(Set* sets[], int x, int y) {
	if (sets[x]->rank < sets[y]->rank)
		sets[x]->parent = y;
	else if (sets[y]->rank < sets[x]->rank)
		sets[y]->parent = x;
	else {
		sets[x]->parent = y;
		sets[y]->rank++;
	}
}

void sort(GraphEdge* arr[], int size, int (*comp)(GraphEdge* p1, GraphEdge* p2)) {
    int i, j;
	GraphEdge* temp;
    for (i = 0; i < (size - 1); i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (comp(arr[j], arr[j + 1])) {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void kruskalMST(Graph *gph) {
    int count = gph->count;
	//Different subsets are created.
	Set* sets[count];
	for (int i = 0; i < count; i++)
		sets[i] = createSets(i, 0);

	// Edges are added to array and sorted.
	int E = 0;
	GraphEdge* edge[100];
    GraphEdge *head;
	for (int i = 0; i < count; i++) {
		head = gph->adj[i];
		while (head) {
			edge[E++] = createGraphEdge(head->src, head->dest, head->cost);
            head = head->next;
        }
	}
	sort(edge, E, greater);
	int sum = 0;
	printf("Edges are : ");
    for (int i = 0; i < E; i++) {
		int x = findSetRoot(sets, edge[i]->src);
		int y = findSetRoot(sets, edge[i]->dest);
		if (x != y) {
			printf("(%d->%d @ %d) ", edge[i]->src, edge[i]->dest, edge[i]->cost);
			sum += edge[i]->cost;
			unionSets(sets, x, y);
		}
	}
	printf("\nTotal MST cost: %d\n", sum);
}

int main16() {
    Graph* gph = createGraph(9);
    addUndirectedEdge(gph, 0, 1, 4);
    addUndirectedEdge(gph, 0, 7, 8);
    addUndirectedEdge(gph, 1, 2, 8);
    addUndirectedEdge(gph, 1, 7, 11);
    addUndirectedEdge(gph, 2, 3, 7);
    addUndirectedEdge(gph, 2, 8, 2);
    addUndirectedEdge(gph, 2, 5, 4);
    addUndirectedEdge(gph, 3, 4, 9);
    addUndirectedEdge(gph, 3, 5, 14);
    addUndirectedEdge(gph, 4, 5, 10);
    addUndirectedEdge(gph, 5, 6, 2);
    addUndirectedEdge(gph, 6, 7, 1);
    addUndirectedEdge(gph, 6, 8, 6);
    addUndirectedEdge(gph, 7, 8, 7);
    kruskalMST(gph);
    primsMST(gph);
    dijkstra(gph, 0);
    return 0;
}

/*
//Kruskal
Edges are : (6->7 @ 1) (2->8 @ 2) (5->6 @ 2) (0->1 @ 4) (2->5 @ 4) (2->3 @ 7) (0->7 @ 8) (3->4 @ 9) 
Total MST cost: 37

//Prims
Edges are : (0->1 @ 4) (5->2 @ 4) (2->3 @ 7) (3->4 @ 9) (6->5 @ 2) (7->6 @ 1) (0->7 @ 8) (2->8 @ 2) 
Total MST cost: 37

//dijkstra
Shortest Paths: (0->1 @ 4) (0->1->2 @ 12) (0->1->2->3 @ 19) (0->7->6->5->4 @ 21) 
                (0->7->6->5 @ 11) (0->7->6 @ 9) (0->7 @ 8) (0->1->2->8 @ 14) 

*/

void shortestPath(Graph *gph, int source) {
    int count = gph->count;
    int *dist = (int *)calloc(count, sizeof(int));
    int *previous = (int *)calloc(count, sizeof(int));
    int curr, destination;
    for (int i = 0; i < count; i++) {
        dist[i] = -1;
        previous[i] = -1;
    }
    Queue* que = createQueue();
    queueAdd(que, source);
    dist[source] = 0;
    previous[source] = source;

    while (queueSize(que) != 0) {
        curr = queueRemove(que);
        GraphEdge *head = gph->adj[curr];
        while (head) {
            destination = head->dest;
            if (dist[destination] == -1) {
                dist[destination] = dist[curr] + 1;
                previous[destination] = curr;
                queueAdd(que, destination);
            }
            head = head->next;
        }
    }

    printPath(previous, dist, gph->count, source);
}

int main17() {
    Graph* gph = createGraph(9);
    addUndirectedEdge(gph, 0, 1, 1);
    addUndirectedEdge(gph, 0, 7, 1);
    addUndirectedEdge(gph, 1, 2, 1);
    addUndirectedEdge(gph, 1, 7, 1);
    addUndirectedEdge(gph, 2, 3, 1);
    addUndirectedEdge(gph, 2, 8, 1);
    addUndirectedEdge(gph, 2, 5, 1);
    addUndirectedEdge(gph, 3, 4, 1);
    addUndirectedEdge(gph, 3, 5, 1);
    addUndirectedEdge(gph, 4, 5, 1);
    addUndirectedEdge(gph, 5, 6, 1);
    addUndirectedEdge(gph, 6, 7, 1);
    addUndirectedEdge(gph, 6, 8, 1);
    addUndirectedEdge(gph, 7, 8, 1);
    shortestPath(gph, 0);
    return 0;
}

/*
Shortest Paths: (0->1 @ 1) (0->1->2 @ 2) (0->1->2->3 @ 3) (0->7->6->5->4 @ 4) 
               (0->7->6->5 @ 3) (0->7->6 @ 2) (0->7 @ 1) (0->7->8 @ 2) 

*/

void bellmanFordshortestPath(Graph *gph, int source) {
    int count = gph->count;
    int previous[count];
    int dist[count];
    int visited[count];
    for(int i = 0;i<count;i++) {
        previous[i] = -1;
        dist[i] = 99999;
        visited[i] = 0;
    }
    dist[source] = 0;
    previous[source] = source;
    /* Outer loop will run (V-1) number of times.
	Inner for loop and while loop runs combined will
	run for Edges number of times.
	Which make the total complexity as O(V*E)
	*/
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count; j++) {
            GraphEdge *head = gph->adj[j];
            while (head) {
                int newcost = dist[j] + head->cost;
                int k = head->dest;
                if (dist[k] > newcost) {
                    dist[k] = newcost;
                    previous[k] = j;
                }
                head = head->next;
            }
        }
    }
    printPath(previous, dist, gph->count, source);
}

int main18() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 0, 1, 3);
    addDirectedEdge(gph, 0, 4, 2);
    addDirectedEdge(gph, 1, 2, 1);
    addDirectedEdge(gph, 2, 3, 1);
    addDirectedEdge(gph, 4, 1, -2);
    addDirectedEdge(gph, 4, 3, 1);
    bellmanFordshortestPath(gph, 0);
    return 0;
}

/*
Shortest Paths: (0->4->1 @ 0) (0->4->1->2 @ 1) (0->4->1->2->3 @ 2) (0->4 @ 2) 
*/

int isEulerian(Graph *graph) {
    //Check if all non - zero degree nodes are connected
    if (isConnected(graph) == 0) {
        printf("graph is not Eulerian.\n");
        return 0;
    } else {
        int count = graph->count;
        //Count odd degree
        int odd = 0;
        int* inDegree = (int *)calloc(count, sizeof(int));
        int* outDegree = (int *)calloc(count, sizeof(int));

        for (int i = 0; i < count; i++) {
            GraphEdge *head = graph->adj[i];
            while (head) {
                outDegree[i] += 1;
                inDegree[head->dest] += 1;
                head = head->next;
            }
        }
        for (int i = 0; i < count; i++) {
            if ((inDegree[i] + outDegree[i]) % 2 != 0) {
                odd += 1;
            }
        }

        if (odd > 2) {
            printf("graph is not Eulerian.\n");
            return 0;
        } else if (odd == 2) {
            printf("graph is Semi-Eulerian.\n");
            return 1;
        } else if (odd == 0) {
            printf("graph is Eulerian.\n");
            return 2;
        }
    }
}

int main19() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 1, 0, 1);
    addDirectedEdge(gph, 0, 2, 1);
    addDirectedEdge(gph, 2, 1, 1);
    addDirectedEdge(gph, 0, 3, 1);
    addDirectedEdge(gph, 3, 4, 1);
    printf("isEulerian %d\n", isEulerian(gph));
    return 0;
}

/*
graph is Semi-Eulerian.
isEulerian 1
*/

int isStronglyConnected2(Graph *graph) {
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    GraphEdge *head;
    Graph *gReversed;
    int index;
    //Find a vertex with non - zero degree
    for (index = 0; index < count; index++) {
        head = graph->adj[index];
        if (head)
            break;
    }
    //DFS traversal of graph from a vertex with non - zero degree
    dfsUtil(graph, index, visited);

    for (int i = 0; i < count; i++) {
        head = graph->adj[i];
        if (visited[i] == 0 && head)
            return 0;
    }

    gReversed = TransposeGraph(graph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;
    dfsUtil(gReversed, index, visited);

    for (int i = 0; i < count; i++) {
        head = graph->adj[i];
        if (visited[i] == 0 && head)
            return 0;
    }
    return 1;
}

int isEulerianCycle(Graph *graph) {
    //Check if all non - zero degree count are connected
    int count = graph->count;
    GraphEdge *head;
    int *inDegree = (int *)calloc(count, sizeof(int));
    int *outDegree = (int *)calloc(count, sizeof(int));
    if (isStronglyConnected2(graph) == 0)
        return 0;

    //Check if in degree and out degree of every vertex is same
    for (int i = 0; i < count; i++) {
        head = graph->adj[i];
        while (head) {
            outDegree[i] += 1;
            inDegree[head->dest] += 1;
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++)
        if (inDegree[i] != outDegree[i])
            return 0;
    return 1;
}

int main20() {
    Graph* gph = createGraph(5);
    addDirectedEdge(gph, 0, 1, 1);
    addDirectedEdge(gph, 1, 2, 1);
    addDirectedEdge(gph, 2, 0, 1);
    addDirectedEdge(gph, 0, 4, 1);
    addDirectedEdge(gph, 4, 3, 1);
    addDirectedEdge(gph, 3, 0, 1);
    printf("isEulerianCycle %d\n", isEulerianCycle(gph));
    return 0;
}

/*
isEulerianCycle 1
*/

void DFSRec(Graph *gph, int index, int *visited) {
    int destination;
    visited[index] = 1;
    GraphEdge *head = gph->adj[index];
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0)
            DFSRec(gph, destination, visited);
        head = head->next;
    }
}

int main() {
    main1();
    main2();
    main3();
    main4();
    main5(); 
    main6();
    main7();
    main8();
    main9();
    main10();
    main11();
    main12();
    main13();
    main14();
    main15();
    main16();
    main17();
    main18();
    main19();
    main20();
   return 0;
}
