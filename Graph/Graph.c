#include <stdio.h>
#include <stdlib.h>

typedef struct graphNode
{
    int cost;
    int dest;
    struct graphNode *next;
} GraphNode;

typedef struct graph
{
    int count;
    GraphNode *adj;
} Graph;

void graphInit(Graph *gph, int count)
{
    gph->count = count;
    gph->adj = (GraphNode *)malloc((count) * sizeof(GraphNode));

    for (int i = 0; i < count; i++)
        gph->adj[i].next = NULL;
}

int addDirectedEdge(Graph *gph, int src, int dst, int cost)
{
    GraphNode *temp = (GraphNode *)malloc(sizeof(GraphNode));
    if (!temp)
    {
        printf("Memory Allocation Error");
        return 0;
    }
    temp->cost = cost;
    temp->dest = dst;
    temp->next = gph->adj[src].next;
    gph->adj[src].next = temp;
    return 1;
}

int addUndirectedEdge(Graph *gph, int src, int dst, int cost)
{
    return addDirectedEdge(gph, src, dst, cost) &&
           addDirectedEdge(gph, dst, src, cost);
}

void printGraph(Graph *gph)
{
    GraphNode *head;
    if (!gph)
    {
        printf("Graph empty");
        return;
    }
    printf("Graph count count : %d \n", gph->count);
    for (int i = 0; i < gph->count; i++)
    {
        head = gph->adj[i].next;
        printf(" Node [ %d ] ::", i);
        while (head)
        {
            printf(" %d(%d) ", head->dest, head->cost);
            head = head->next;
        }
        printf("\n");
    }
}

typedef struct tableNode
{
    int visited;
    int cost;
    int prev;
} TableNode;

#define INFINITE 9999999

TableNode *createTable(int count)
{
    TableNode *temp = (TableNode *)malloc((count) * sizeof(TableNode));

    for (int i = 0; i <= count; i++)
    {
        temp[i].visited = 0;
        temp[i].cost = INFINITE;
        temp[i].prev = -1;
    }

    return temp;
}

void printTable(TableNode *table, int size)
{
    if (!table)
    {
        printf("Table is empty.");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        printf("node id :: %d  visited :: %d  cost :: %d previous :: %d \n",
               i, table[i].visited, table[i].cost, table[i].prev);
    }
}

int main1()
{
    int nodeCount = 7;
    Graph myGraph1;
    graphInit(&myGraph1, nodeCount);
    addDirectedEdge(&myGraph1, 1, 2, 2);
    addDirectedEdge(&myGraph1, 1, 4, 1);
    addDirectedEdge(&myGraph1, 2, 4, 3);
    addDirectedEdge(&myGraph1, 2, 5, 10);
    addDirectedEdge(&myGraph1, 3, 1, 4);
    addDirectedEdge(&myGraph1, 3, 6, 5);
    addDirectedEdge(&myGraph1, 4, 3, 2);
    addDirectedEdge(&myGraph1, 4, 5, 7);
    addDirectedEdge(&myGraph1, 4, 6, 8);
    addDirectedEdge(&myGraph1, 4, 7, 4);
    addDirectedEdge(&myGraph1, 5, 7, 6);
    addDirectedEdge(&myGraph1, 7, 6, 1);
    printGraph(&myGraph1);
    return 0;
}

void BellmanFordShortestPath(Graph *gph, int source)
{
    int count = gph->count;
    TableNode *table = createTable(count);
    table[source].cost = source;

    /* Outer loop will run (V-1) number of times. 
     Inner for loop and while loop runs combined will 
     run for Edges number of times.
     Which make the total complexity as O(V*E)
    */
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count; j++)
        {
            GraphNode *head = gph->adj[j].next;
            while (head)
            {
                int newcost = table[j].cost + head->cost;
                int k = head->dest;
                if (table[k].cost > newcost)
                {
                    table[k].cost = newcost;
                    table[k].prev = j;
                }
                head = head->next;
            }
        }
    }
    printTable(table, count);
}

int main2()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 0, 1, 3);
    addDirectedEdge(&myGraph, 0, 4, 2);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 4, 1, -2);
    addDirectedEdge(&myGraph, 4, 3, 1);
    printGraph(&myGraph);
    BellmanFordShortestPath(&myGraph, 0);
    return 0;
}

typedef struct prique
{
    int demo;
} PrintiorityQueue;

void PrintiorityQueueInit(PrintiorityQueue *pq)
{
}

void PrintiorityQueueAdd(PrintiorityQueue *pq, int a, int b)
{
}

void PrintiorityQueueUpdateKey(PrintiorityQueue *pq, int a, int b)
{
}

int PrintiorityQueuePop(PrintiorityQueue *pq)
{
}

int PrintiorityQueueSize(PrintiorityQueue *pq)
{
}

typedef struct stackstruct
{
    int demo;
} Stack;

void StackInit(Stack *stk)
{
}

void StackPush(Stack *stk, int a)
{
}

int StackPop(Stack *stk)
{
    return 1;
}

int StackSize(Stack *stk)
{
    return 1;
}

void StackPrint(Stack *stk)
{
}

void Dijkstra(Graph *gph, int source)
{
    int count = gph->count;
    int val, destination, cost;
    GraphNode *head;
    TableNode *table = createTable(count);
    table[source].cost = 0;

    PrintiorityQueue pq;
    PrintiorityQueueInit(&pq);

    for (int i = 0; i < gph->count; i++)
    {
        PrintiorityQueueAdd(&pq, INFINITE, i);
    }
    PrintiorityQueueUpdateKey(&pq, 0, source);

    while (PrintiorityQueueSize(&pq) != 0)
    {
        source = PrintiorityQueuePop(&pq);
        table[source].visited = 1;
        head = gph->adj[source].next;
        while (head)
        {
            destination = head->dest;
            cost = head->cost;
            int alt = cost + table[source].cost;

            if (alt < table[destination].cost && table[destination].visited == 0)
            {
                table[destination].cost = alt;
                table[destination].prev = source;
                PrintiorityQueueUpdateKey(&pq, alt, destination);
            }
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (table[i].cost == INFINITE)
            printf("node id %d prev %d cost : Unreachable",
                   i, table[i].prev);
        else
            printf("node id %d prev %d cost : %d",
                   i, table[i].prev, table[i].cost);
    }
}

void Prims(Graph *gph)
{
    int count = gph->count;
    int val, destination, cost;
    GraphNode *head;
    int source = 0;
    TableNode *table = createTable(count);
    table[source].cost = 0;

    PrintiorityQueue pq;
    PrintiorityQueueInit(&pq);

    for (int i = 0; i < gph->count; i++)
    {
        PrintiorityQueueAdd(&pq, INFINITE, i);
    }
    PrintiorityQueueUpdateKey(&pq, 0, source);

    while (PrintiorityQueueSize(&pq) != 0)
    {
        source = PrintiorityQueuePop(&pq);
        table[source].visited = 1;
        head = gph->adj[source].next;
        while (head)
        {
            destination = head->dest;
            cost = head->cost;

            if (cost < table[destination].cost && table[destination].visited == 0)
            {
                table[destination].cost = cost;
                table[destination].prev = source;
                PrintiorityQueueUpdateKey(&pq, cost, destination);
            }
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (table[i].cost == INFINITE)
            printf("node id %d prev %d cost : Unreachable",
                   i, table[i].prev);
        else
            printf("node id %d prev %d cost : %d",
                   i, table[i].prev, table[i].cost);
    }
}

int main3()
{
    Graph myGraph;
    graphInit(&myGraph, 9);
    addUndirectedEdge(&myGraph, 0, 1, 4);
    addUndirectedEdge(&myGraph, 0, 7, 8);
    addUndirectedEdge(&myGraph, 1, 2, 8);
    addUndirectedEdge(&myGraph, 1, 7, 11);
    addUndirectedEdge(&myGraph, 2, 3, 7);
    addUndirectedEdge(&myGraph, 2, 8, 2);
    addUndirectedEdge(&myGraph, 2, 5, 4);
    addUndirectedEdge(&myGraph, 3, 4, 9);
    addUndirectedEdge(&myGraph, 3, 5, 14);
    addUndirectedEdge(&myGraph, 4, 5, 10);
    addUndirectedEdge(&myGraph, 5, 6, 2);
    addUndirectedEdge(&myGraph, 6, 7, 1);
    addUndirectedEdge(&myGraph, 6, 8, 6);
    addUndirectedEdge(&myGraph, 7, 8, 7);
    Prims(&myGraph);
    Dijkstra(&myGraph, 0);
}

void DFSUtil(Graph *gph, int index, int *visited)
{
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head)
    {
        if (visited[head->dest] == 0)
            DFSUtil(gph, head->dest, visited);
        head = head->next;
    }
}

int RootVertex(Graph *gph)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int retVal = -1;
    for (int i = 0; i < count; i++)
    {
        if (visited[i] == 0)
        {
            DFSUtil(gph, i, visited);
            retVal = i;
        }
    }
    printf("Root vertex is :: %d ", retVal);
    return retVal;
}

int main4()
{
    Graph myGraph;
    graphInit(&myGraph, 7);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 0, 2, 1);
    addDirectedEdge(&myGraph, 1, 3, 1);
    addDirectedEdge(&myGraph, 4, 1, 1);
    addDirectedEdge(&myGraph, 6, 4, 1);
    addDirectedEdge(&myGraph, 5, 6, 1);
    addDirectedEdge(&myGraph, 5, 2, 1);
    addDirectedEdge(&myGraph, 6, 0, 1);
    printGraph(&myGraph);
    RootVertex(&myGraph);
}

void TopologicalSortDFS(Graph *gph, int index, int *visited, Stack *stk)
{
    int destination;
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head)
    {
        destination = head->cost;
        if (visited[destination] == 0)
            TopologicalSortDFS(gph, destination, visited, stk);
        StackPush(stk, index);
        head = head->next;
    }
}
void TopologicalSort(Graph *gph)
{
    Stack stk;
    StackInit(&stk);
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));

    for (int i = 0; i < count; i++)
    {
        if (visited[i] == 0)
        {
            TopologicalSortDFS(gph, i, visited, &stk);
        }
    }
    printf("TopologicalSort :: ");
    while (StackSize(&stk) != 0)
        printf(" %d ", StackPop(&stk));
    printf("\n");
}

int main5()
{
    Graph myGraph;
    graphInit(&myGraph, 6);
    addDirectedEdge(&myGraph, 5, 2, 1);
    addDirectedEdge(&myGraph, 5, 0, 1);
    addDirectedEdge(&myGraph, 4, 0, 1);
    addDirectedEdge(&myGraph, 4, 1, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 3, 1, 1);
    printGraph(&myGraph);
    TopologicalSort(&myGraph);
}

void DFSRec(Graph *gph, int index, int *visited)
{
    int destination;
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head)
    {
        destination = head->cost;
        if (visited[destination] == 0)
            DFSRec(gph, destination, visited);
        head = head->next;
    }
}

int PathExist(Graph *gph, int source, int destination)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, source, visited);
    return visited[destination];
}

Graph *TransposeGraph(Graph *gph)
{
    int count = gph->count;
    Graph *gph2 = (Graph *)malloc(sizeof(Graph));
    int destination, cost;
    graphInit(gph2, count);

    for (int i = 0; i < count; i++)
    {
        GraphNode *head = gph->adj[i].next;
        while (head)
        {
            destination = head->cost;
            cost = head->cost;
            addDirectedEdge(gph2, destination, i, cost);
            head = head->next;
        }
    }
    return gph2;
}
/*
Kosaraju Algorithm

Kosaraju’s Algorithm to find strongly connected directed graph based on DFS :
1)	Create a visited array of size V, and Initialize all count in visited array as 0.
2)	Choose any vertex and perform a DFS traversal of graph. For all visited count mark them visited as 1. 
3)	If DFS traversal does not mark all count as 1, then return 0.
4)	Find transpose or reverse of graph
5)	Repeat step 1, 2 and 3 for the reversed graph. 
6)	If DFS traversal mark all the count as 1, then return 1.
*/

int isStronglyConnected(Graph *gph)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, 0, visited);
    ;
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;

    Graph *gReversed = TransposeGraph(gph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;

    DFSRec(gReversed, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

int main6()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 3, 0, 1);
    addDirectedEdge(&myGraph, 2, 4, 1);
    addDirectedEdge(&myGraph, 4, 2, 1);
    printf(" IsStronglyConnected:: %d \n", isStronglyConnected(&myGraph));
}

void DFSRec2(Graph *gph, int index, int *visited,
             Stack *stk)
{
    int destination;
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head)
    {
        destination = head->cost;
        if (visited[destination] == 0)
            DFSRec2(gph, destination, visited, stk);
        head = head->next;
    }
    StackPush(stk, index);
}

void stronglyConnectedComponent(Graph *gph)
{
    int count = gph->count;
    int index;
    int *visited = (int *)calloc(count, sizeof(int));
    Stack stk;
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            DFSRec2(gph, i, visited, &stk);

    Graph *gReversed = TransposeGraph(gph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;
    while (StackSize(&stk) != 0)
    {
        index = StackPop(&stk);
        if (visited[index] == 0)
        {
            Stack stk2;
            DFSRec2(gReversed, index, visited, &stk2);
            StackPrint(&stk2);
        }
    }
}

int main()
{
    Graph myGraph;
    graphInit(&myGraph, 7);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 0, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 3, 4, 1);
    addDirectedEdge(&myGraph, 4, 5, 1);
    addDirectedEdge(&myGraph, 5, 3, 1);
    addDirectedEdge(&myGraph, 5, 6, 1);
    stronglyConnectedComponent(&myGraph);
}

int isConnectedUndirected(Graph *gph)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

int DFSStack(gph, source, target)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int curr;
    Stack stk;

    StackPush(&stk, source);
    visited[source] = 1;
    while (StackSize(&stk) != 0)
    {
        curr = StackPop(&stk);
        GraphNode *head = gph->adj[curr].next;
        while (head)
        {
            destination = head->cost;
            if (visited[destination] == 0)
            {
                StackPush(&stk, destination);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return visited[target]
}

int DFS(Graph *gph, int source, int target)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, source, visited);
    return visited[target];
}

int BFS(Graph *gph, int source, int target)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    visited[source] = 1;
    Queue que;
    QueueInit(&que);
    QueueAdd(&que, source);
    while (QueueSize(&que) != 0)
    {
        curr = QueueRemove(&que);
        GraphNode *head = gph->adj[curr].next;
        while (head)
        {
            destination = head->cost;
            if (visited[destination] == 0)
            {
                QueueAdd(&que, destination);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return visited[target];
}

typedef struct LevelNodeStruct
{
    int value;
    int depth;
} LevelNode;

def BFSLevelNode(Graph *gph, int source)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    visited[source] = 1;
    LevelNode node;
    Queue que;
    QueueInit(&que);
    QueueAdd(&que, source, 0);
    printf("\nNode  - Level");
    while (QueueSize(&que) != 0)
    {
        node = QueueRemove(&que);
        curr = node.value;
        depth = node.depth;
        printf("%d - %d", curr, depth);
        GraphNode *head = gph->adj[curr].next;
        while (head)
        {
            destination = head->cost;
            if (visited[destination] == 0)
            {
                QueueAdd(&que, destination, depth + 1);
                visited[destination] = 1;
            }
        }
    }
}

int BFSDistance(Graph *gph, int source, int dest)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    visited[source] = 1;
    Queue que;
    QueueInit(&que);
    QueueAdd(&que, source, 0);
    while (QueueSize(&que) != 0)
    {
        node = QueueRemove(&que);
        curr = node.value;
        depth = node.depth;
        GraphNode *head = gph->adj[curr].next;
        while (head)
        {
            destination = head->cost;
            if (destination == dest)
                return depth;
            if (visited[destination] == 0)
            {
                QueueAdd(&que, destination, depth + 1);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return -1
}

int main()
{
    Graph myGraph;
    graphInit(&myGraph, 7);
    addUndirectedEdge(&myGraph, 0, 1, 1);
    addUndirectedEdge(&myGraph, 0, 2, 1);
    addUndirectedEdge(&myGraph, 0, 4, 1);
    addUndirectedEdge(&myGraph, 1, 2, 1);
    addUndirectedEdge(&myGraph, 2, 5, 1);
    addUndirectedEdge(&myGraph, 3, 4, 1);
    addUndirectedEdge(&myGraph, 4, 5, 1);
    addUndirectedEdge(&myGraph, 4, 6, 1);
    printf(" %d ", BFSDistance(g, 1, 3));
    return 0;
}

void ShortestPath(Graph *gph, int source)
{
    int count = gph->count;
    int *cost = (int *)calloc(count, sizeof(int));
    int *path = (int *)calloc(count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        cost[i] = -1;
        path[i] = -1;
    }
    Queue que;
    QueueInit(&que);
    QueueAdd(&que, source);
    cost[source] = 0;
    while (QueueSize(&que) != 0)
    {
        curr = QueueRemove(&que);
        GraphNode *head = gph->adj[curr].next;
        while (head)
        {
            destination = head->cost;
            if (cost[destination] == -1)
            {
                cost[destination] = cost[curr] + 1;
                path[destination] = curr;
                QueueAdd(&que, destination);
            }
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++)
        printf("%d to %d cost %d ", path[i], i, cost[i]);
}

int main()
{
    Graph myGraph;
    graphInit(&myGraph, 9);
    addUndirectedEdge(&myGraph, 0, 2, 1);
    addUndirectedEdge(&myGraph, 1, 2, 5);
    addUndirectedEdge(&myGraph, 1, 3, 7);
    addUndirectedEdge(&myGraph, 1, 4, 9);
    addUndirectedEdge(&myGraph, 3, 2, 2);
    addUndirectedEdge(&myGraph, 3, 5, 4);
    addUndirectedEdge(&myGraph, 4, 5, 6);
    addUndirectedEdge(&myGraph, 4, 6, 3);
    addUndirectedEdge(&myGraph, 5, 7, 1);
    addUndirectedEdge(&myGraph, 6, 7, 7);
    addUndirectedEdge(&myGraph, 7, 8, 17);
    DFS(gph, 0);
    BFS(gph, 0);
    BFSLevelNode(gph, 0);
    BellmanFordShortestPath(gph, 1);
    Dijkstra(gph, 1);
    Prims(gph);
    print(PathExist(gph, 1, 5));
    print(isConnectedUndirected(gph));
    ShortestPath(gph, 1);
}
/*
Given a directed graph, 
fidn transitive closure matrix or reachablity matrix
vertex v is reachable form vertex u 
if their is a path from u to v.
*/

def TransitiveClosureUtil(gph, source ,index, tc):
    if tc[source][index] == 1:
        return
    tc[source][index] = 1
    for edge in gph.adj[index]:
            TransitiveClosureUtil(gph, source, edge[0], tc)

def TransitiveClosure(Graph* gph):
    int count = gph->count;
    tc = [[0 for _ in range(count)] for _ in range(count)]
    for source in range(count):
        TransitiveClosureUtil(gph, source, source, tc)
    for row in tc:
        print row


g = Graph(4)
addDirectedEdge(0, 1)
addDirectedEdge(0, 2)
addDirectedEdge(1, 2)
addDirectedEdge(2, 0)
addDirectedEdge(2, 3)
addDirectedEdge(3, 3)
g.Print()
TransitiveClosure(g)
/*
def countAllPathDFS((Graph* gph, int* visited, int source, int dest)):
    if source == dest:
        return 1

    count = 0
    visited[source] = 1
    for edge in gph.adj[source]:
        if visited[edge[0]] == 0:
            count += countAllPathDFS(gph, visited, edge[0], dest)
    visited[source] = 0
    return count

def countAllPath(gph, src ,dest):
    visited = [0]*gph.count
    return countAllPathDFS(gph, visited, src, dest)

def printAllPathDFS((Graph* gph, int* visited, int source, int dest), path):
    path.append(source)
    if source == dest:
        print path
        return

    visited[source] = 1
    for edge in gph.adj[source]:
        if visited[edge[0]] == 0:
            printAllPathDFS(gph, visited, edge[0], dest, path)
    visited[source] = 0
    path.pop()

def printAllPath(gph, src ,dest):
    visited = [0]*gph.count
    path = []
    printAllPathDFS(gph, visited, src, dest, path)
"""
g = Graph(5)
addDirectedEdge(0, 1)
addDirectedEdge(0, 2)
addDirectedEdge(2, 3)
addDirectedEdge(1, 3)
addDirectedEdge(3, 4)
addDirectedEdge(1, 4)
print countAllPath(g, 0, 4)
printAllPath(g, 0, 4)
"""
def HeightTreeParentArr(arr):
    count = len(arr)
    gph = Graph(count)
    for i in range(len(arr)):
        if arr[i] != -1 :
            gph.addDirectedEdge(arr[i], i)
        else:
            source = i

    int *visited = (int *)calloc(count, sizeof(int));
    visited[source] = 1
    Queue que; QueueInit(&que);
    QueueAdd(&que, (source, 0))
    maxHeight = 0
    while(QueueSize(&que) != 0){
        node = QueueRemove(&que);
        curr = node[0]
        height = node[1]
        if height > maxHeight:
            maxHeight = height
        for edge in gph.adj[curr]:
            destination = edge[0]
            if visited[destination] == 0:
                QueueAdd(&que, (destination, height+1))
                visited[destination] = 1
    return maxHeight

def getHeight(arr, height, index):
    if arr[index] == -1:
        return 0
    else:
        return getHeight(arr, height, arr[index]) + 1

def HeightTreeParentArr2(arr):
    count = len(arr)
    height = [-1] * count
    maxHeight = -1
    for i in range(len(arr)):
        height[i] = getHeight(arr, height, i)
        maxHeight = max(maxHeight, height[i])
    return maxHeight
"""
parentArray = [-1, 0, 1, 2, 3]
print HeightTreeParentArr(parentArray)
print HeightTreeParentArr2(parentArray)
parentArray = [-1, 0, 0, 0, 3, 1, 1, 2]
print HeightTreeParentArr(parentArray)
print HeightTreeParentArr2(parentArray)
"""

def BestFirstSearchPQ(Graph* gph, int source, int dest):
    previous = [-1] * gph.count
    dist = [sys.maxsize] * gph.count
    visited = [0] * gph.count
    pq = PriorityQueue()
    dist[source] = 0
    previous[source] = -1
    PrintiorityQueueAdd(pq, 0, source)
    
    while PrintiorityQueueSize(pq, ) != 0:
        val = PrintiorityQueuePop(pq, )
        if val[1] == dest:
            return val[0]
        source = val[1]
        visited[source] = 1
        for edge in gph.adj[source]:
            destination = edge[0]
            cost = edge[1]
            alt = cost + dist[source]
            if alt < dist[destination] and visited[destination] == 0:
                dist[destination] = alt
                previous[destination] = source
                PrintiorityQueueAdd(pq, alt, destination)
    return -1



"""
Given a directed graph find if there is a cycle in it. 
"""
def isCyclePresentDFS(graph, index, visited, marked):
    visited[index] = 1
    marked[index] = 1

    for node in graph.adj[index]:
        dest = node[0]
        if marked[dest] == 1:
            return 1

        if visited[dest] == 0:
            if isCyclePresentDFS(graph, dest, visited, marked) :
                return 1
        
    marked[index] = 0
    return 0

def isCyclePresent(graph):
    count = graph.count
    int *visited = (int *)calloc(count, sizeof(int));
    marked = [0] * count
    for index in range(count):
        if visited[index] == 0:
            if isCyclePresentDFS(graph, index, visited, marked) :
                return 1
    return 0


def isCyclePresentDFSColor(graph, index, visited):
    visited[index] = "Grey"

    for node in graph.adj[index]:
        dest = node[0]
        if visited[dest] == "Grey":
            return 1
            
        if visited[dest] == "White":
            if isCyclePresentDFSColor(graph, dest, visited) :
                return 1
        
    visited[index] = "Black"
    return 0

def isCyclePresentColor(graph):
    count = graph.count
    visited = ["White"] * count
    for index in range(count):
        if visited[index] == "White":
            if isCyclePresentDFSColor(graph, index, visited) :
                return 1
    return 0

"""
g = Graph(5)
addDirectedEdge(0, 1)
addDirectedEdge(0, 2)
addDirectedEdge(1, 3)
addDirectedEdge(2, 3)
addDirectedEdge(3, 4)
#addDirectedEdge(4, 1)
print isCyclePresentColor(g)
"""

def isCyclePresentUndirectedDFS(graph, index, parentIndex, visited):
    visited[index] = 1
    for node in graph.adj[index]:
        dest = node[0]
        if visited[dest] == 0:
            if isCyclePresentUndirectedDFS(graph, dest, index, visited) :
                return 1
        elif parentIndex != dest :
            return 1
    return 0


def isCyclePresentUndirected(graph):
    count = graph.count
    int *visited = (int *)calloc(count, sizeof(int));
    for index in range(count):
        if visited[index] == 0:
            if isCyclePresentUndirectedDFS(graph, index, -1, visited) :
                return 1
    return 0
"""
g = Graph(6)
addUndirectedEdge(0, 1)
addUndirectedEdge(1, 2)
addUndirectedEdge(3, 4)
addUndirectedEdge(4, 2)
addUndirectedEdge(2, 5)
#addUndirectedEdge(4, 1)
#print isCyclePresentUndirected(g)
"""

def isConnected(graph):
    count = graph.count
    visited =[0]*count

#Find a vertex with non - zero degree
    for (int i = 0; i < count; i++)
        if len(graph.adj[i]) > 1:
#DFS traversal of graph from a vertex with non - zero degree
            DFSUtil(graph, i, visited)
            break

#Check if all non - zero degree count are visited
    for (int i = 0; i < count; i++)
        if visited[i]==0 and len(graph.adj[i]) > 0:
            return 0
        
    return 1

'''
The function returns one of the following values
Return 0 if graph is not Eulerian
Return 1 if graph has an Euler path (Semi-Eulerian)
Return 2 if graph has an Euler Circuit (Eulerian)
'''
def isEulerian(graph):
    count = graph.count
#Check if all non - zero degree count are connected
    if isConnected(graph) == 0:
        print "graph is not Eulerian"
        return 0
    else:
#Count count with odd degree
        odd = 0
        for (int i = 0; i < count; i++)
            if len(graph.adj[i]) % 2 !=0:
                odd +=1

        if odd > 2:
            print "graph is not Eulerian"
            return 0
        elif odd == 2:
            print "graph is Semi-Eulerian"
            return 1
        elif odd == 0:
            print "graph is Eulerian"
            return 2

g1 = Graph(5)
g1.AddUndirectedEdge(1, 0)
g1.AddUndirectedEdge(0, 2)
g1.AddUndirectedEdge(2, 1)
g1.AddUndirectedEdge(0, 3)
g1.AddUndirectedEdge(3, 4)
isEulerian(g1)
 
g2 = Graph(5)
g2.AddUndirectedEdge(1, 0)
g2.AddUndirectedEdge(0, 2)
g2.AddUndirectedEdge(2, 1)
g2.AddUndirectedEdge(0, 3)
g2.AddUndirectedEdge(3, 4)
g2.AddUndirectedEdge(4, 0)
isEulerian(g2)
 
g3 = Graph(5)
g3.AddUndirectedEdge(1, 0)
g3.AddUndirectedEdge(0, 2)
g3.AddUndirectedEdge(2, 1)
g3.AddUndirectedEdge(0, 3)
g3.AddUndirectedEdge(3, 4)
g3.AddUndirectedEdge(1, 3)
isEulerian(g3)

def isStronglyConnected2(graph):
    count = graph.count
    int *visited = (int *)calloc(count, sizeof(int));

#Find a vertex with non - zero degree
    for index in range(count):
        if len(graph.adj[index]) > 1:
            break
#DFS traversal of graph from a vertex with non - zero degree
    DFSUtil(graph, index, visited)
            
    for (int i = 0; i < count; i++)
        if visited[i] == 0 and len(graph.adj[i]) > 0:
            return 0

    gReversed = TransposeGraph(graph)
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gReversed, index, visited)
    
    for (int i = 0; i < count; i++)
        if visited[i] == 0 and len(graph.adj[i]) > 0:
            return 0
    return 1

def isEulerianCycle(graph):
#Check if all non - zero degree count
#are connected
    if isStronglyConnected2(graph) == 0:
        return 0
    count = graph.count
    inDegree = [0] * count
    outDegree = [0] * count

#Check if in degree and out degree of
#every vertex is same
    for (int i = 0; i < count; i++)
        outDegree[i] = len(graph.adj[i])
        for j in graph.adj[i]:
            inDegree[j[0]] += 1
        
    for (int i = 0; i < count; i++)
        if inDegree[i] != outDegree[i]:
            return 0
    return 1

g = Graph(5)
addDirectedEdge(0, 1)
addDirectedEdge(1, 2)
addDirectedEdge(2, 0)
addDirectedEdge(0, 4)
addDirectedEdge(4, 3)
addDirectedEdge(3, 0)
print isEulerianCycle(g)
*/