//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
    int count;
    int **adj;
} Graph;

void graphInit(Graph *gph, int count)
{
    gph->count = count;
    gph->adj = (int **)malloc(count * sizeof(int *));
    for (int i = 0; i < count; i++)
    {
        gph->adj[i] = (int *)malloc(count * sizeof(int));
    }
}

void addDirectedEdge(Graph *gph, int src, int dst, int cost)
{
    gph->adj[src][dst] = cost;
}

void addUndirectedEdge(Graph *gph, int src, int dst, int cost)
{
    addDirectedEdge(gph, src, dst, cost);
    addDirectedEdge(gph, dst, src, cost);
}

void graphPrint(Graph *gph)
{
    int count = gph->count;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            printf("%d ", gph->adj[i][j]);
        }
        printf("\n");
    }
}

int main1()
{
    Graph graph;
    graphInit(&graph, 4);
    addUndirectedEdge(&graph, 0, 1, 1);
    addUndirectedEdge(&graph, 0, 2, 1);
    addUndirectedEdge(&graph, 1, 2, 1);
    addUndirectedEdge(&graph, 2, 3, 1);
    graphPrint(&graph);
    return 0;
}
/*
Vertex  0  is connected to   1 2
Vertex  1  is connected to   0 2
Vertex  2  is connected to   0 1 3
Vertex  3  is connected to   2
*/

int HamiltonianCycleUtil(Graph *graph, int path[], int pSize, int added[])
{
    // Base case full length path is found
    // this last check can be modified to make it a path.
    if (pSize == graph->count)
    {
        if (graph->adj[path[pSize - 1]][path[0]] == 1)
        {
            path[pSize] = path[0];
            return 1;
        }
        else
            return 0;
    }
    for (int vertex = 0; vertex < graph->count; vertex++)
    {
        // there is a path from last element and next vertex
        if (pSize == 0 || (graph->adj[path[pSize - 1]][vertex] == 1 && added[vertex] == 0))
        {
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

int HamiltonianCycle(Graph *graph)
{
    int *path = (int *)calloc(graph->count + 1, sizeof(int));
    int *added = (int *)calloc(graph->count, sizeof(int));
    if (HamiltonianCycleUtil(graph, path, 0, added))
    {
        printf("Hamiltonian Cycle found :: ");
        for (int i = 0; i <= graph->count; i++)
            printf("[%d]", path[i]);
        return 1;
    }
    printf("Hamiltonian Cycle not found");
    return 0;
}

int HamiltonianPathUtil(Graph *graph, int path[], int pSize, int added[])
{
    // Base case full length path is found
    if (pSize == graph->count)
    {
        return 1;
    }
    for (int vertex = 0; vertex < graph->count; vertex++)
    {
        // there is a path from last element and next vertex
        // and next vertex is not already included in path.
        if (pSize == 0 || (graph->adj[path[pSize - 1]][vertex] == 1 && added[vertex] == 0))
        {
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
int HamiltonianPath(Graph *graph)
{
    int *path = (int *)calloc(graph->count, sizeof(int));
    int *added = (int *)calloc(graph->count, sizeof(int));

    if (HamiltonianPathUtil(graph, path, 0, added))
    {
        printf("Hamiltonian Path found :: ");
        for (int i = 0; i < graph->count; i++)
            printf("[%d]", path[i]);

        return 1;
    }

    printf("Hamiltonian Path not found");
    return 0;
}

int main2()
{
    Graph graph;
    int count = 5;
    int adj[5][5] = {{0, 1, 0, 1, 0},
                     {1, 0, 1, 1, 0},
                     {0, 1, 0, 0, 1},
                     {1, 1, 0, 0, 1},
                     {0, 1, 1, 1, 0}};

    graphInit(&graph, count);
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            if (adj[i][j])
                addDirectedEdge(&graph, i, j, 1);
    printf("\nHamiltonianPath : %d \n", HamiltonianPath(&graph));
    printf("\nHamiltonianCycle : %d \n", HamiltonianCycle(&graph));

    Graph graph2;
    int adj2[5][5] = {{0, 1, 0, 1, 0},
                      {1, 0, 1, 1, 0},
                      {0, 1, 0, 0, 1},
                      {1, 1, 0, 0, 0},
                      {0, 1, 1, 0, 0}};
    graphInit(&graph2, count);
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            if (adj2[i][j])
                addDirectedEdge(&graph2, i, j, 1);

    printf("\nHamiltonianPath : %d \n", HamiltonianPath(&graph2));
    printf("\nHamiltonianCycle : %d \n", HamiltonianCycle(&graph2));
    return 0;
}

typedef struct prique
{
    int demo;
} PriorityQueue;

void PriorityQueueInit(PriorityQueue *pq)
{
}

void PriorityQueueAdd(PriorityQueue *pq, int a, int b)
{
}

void PriorityQueueUpdateKey(PriorityQueue *pq, int a, int b)
{
}

int PriorityQueuePop(PriorityQueue *pq)
{
    return 1;
}

int PriorityQueueSize(PriorityQueue *pq)
{
    return 1;
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

int Dijkstra(Graph *gph, int source)
{
    int count = gph->count;
    int val, alt, dest, cost;
    TableNode *table = createTable(count);
    table[source].cost = 0;

    PriorityQueue pq;
    PriorityQueueInit(&pq);

    for (int i = 0; i < count; i++)
    {
        PriorityQueueAdd(&pq, INFINITE, i);
    }
    PriorityQueueUpdateKey(&pq, 0, source);

    while (PriorityQueueSize(&pq) != 0)
    {
        source = PriorityQueuePop(&pq);
        table[source].visited = 1;

        for (int dest = 0; dest < count; dest++)
        {
            alt = gph->adj[source][dest] + table[source].cost;
            if (gph->adj[source][dest] > 0 && alt < table[dest].cost && table[dest].visited == 0)
            {
                table[dest].cost = alt;
                table[dest].prev = source;
                PriorityQueueUpdateKey(&pq, alt, dest);
            }
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

int Prims(Graph *gph)
{
    int count = gph->count;
    int source = 0;
    int val, alt, dest, cost;
    TableNode *table = createTable(count);
    table[source].cost = 0;

    PriorityQueue pq;
    PriorityQueueInit(&pq);

    for (int i = 0; i < count; i++)
    {
        PriorityQueueAdd(&pq, INFINITE, i);
    }
    PriorityQueueUpdateKey(&pq, 0, source);

    while (PriorityQueueSize(&pq) != 0)
    {
        source = PriorityQueuePop(&pq);
        table[source].visited = 1;

        for (int dest = 0; dest < count; dest++)
        {
            alt = gph->adj[source][dest];
            if (gph->adj[source][dest] > 0 && alt < table[dest].cost && table[dest].visited == 0)
            {
                table[dest].cost = alt;
                table[dest].prev = source;
                PriorityQueueUpdateKey(&pq, alt, dest);
            }
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

int main()
{
    Graph graph;
    int count = 9;
    graphInit(&graph, count);
    addUndirectedEdge(&graph, 0, 1, 4);
    addUndirectedEdge(&graph, 0, 7, 8);
    addUndirectedEdge(&graph, 1, 2, 8);
    addUndirectedEdge(&graph, 1, 7, 11);
    addUndirectedEdge(&graph, 2, 3, 7);
    addUndirectedEdge(&graph, 2, 8, 2);
    addUndirectedEdge(&graph, 2, 5, 4);
    addUndirectedEdge(&graph, 3, 4, 9);
    addUndirectedEdge(&graph, 3, 5, 14);
    addUndirectedEdge(&graph, 4, 5, 10);
    addUndirectedEdge(&graph, 5, 6, 2);
    addUndirectedEdge(&graph, 6, 7, 1);
    addUndirectedEdge(&graph, 6, 8, 6);
    addUndirectedEdge(&graph, 7, 8, 7);
    Dijkstra(&graph, 0);
    //Prims(graph);
    // graph.Print();
}