
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
    gph->adj = (int**)malloc(count*sizeof(int*));
	for(int i=0;i<count;i++)
    {
        gph->adj[i] = (int*)malloc(count*sizeof(int));
        gph->adj[i] = 0;
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
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<count;j++)
        {
            printf("%d ", gph->adj[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    Graph graph; 
    graphInit(&graph, 4);
    addUndirectedEdge(&graph, 0, 1, 1);
    addUndirectedEdge(&graph, 0, 2, 1);
    addUndirectedEdge(&graph, 1, 2, 1);
    addUndirectedEdge(&graph, 2, 3, 1);
    graphPrint(&graph);
}
/*
Vertex  0  is connected to :  1 2
Vertex  1  is connected to :  0 2
Vertex  2  is connected to :  0 1 3
Vertex  3  is connected to :  2
*/
/*
class PriorityQueue(object):
    def __init__(self):
        pQueue = []
        count = 0
    
    def Add(self, key, value):
        heapq.heappush(pQueue, (key, value))
    
    def UpdateKey(self, key, value):
        heapq.heappush(pQueue, (key, value))

    def Pop(self):
        val = heapq.heappop(pQueue)
        return val

    def Size(self):
        return len(pQueue)
    
def printPath(count, previous, dist):
    for i in range(count):
        if dist[i] == sys.maxsize:
            print("node id" , i , "prev" , previous[i] , "distance : Unreachable")
        else:
            print("node id" , i , "prev" , previous[i] , "distance :" , dist[i])




def Dijkstra(gph, source):
    previous = [-1] * gph.count
    dist = [sys.maxsize] * gph.count
    visited = [False] * gph.count
    dist[source] = 0
    previous[source] = -1
    
    pq = PriorityQueue()
    for i in range(gph.count):
        pq.Add(sys.maxint, i)
    pq.UpdateKey(0, source)
    
    while pq.Size() != 0:
        val = pq.Pop()
        source = val[1]
        visited[source] = True
        
        for dest in range(gph.count):
            alt = gph.adj[source][dest] + dist[source]
            if gph.adj[source][dest] > 0 and alt < dist[dest] and visited[dest] == False:
                dist[dest] = alt
                previous[dest] = source
                pq.UpdateKey(alt, dest)
    printPath(graph.count, previous,dist)


def Prims(gph):
    previous = [-1] * gph.count
    dist = [sys.maxsize] * gph.count
    visited = [False] * gph.count
    source = 0
    dist[source] = 0
    previous[source] = -1
    pq = PriorityQueue()
    for i in range(gph.count):
        pq.Add(sys.maxint, i)
    pq.UpdateKey(0, source)
    
    while pq.Size() != 0:
        val = pq.Pop()
        source = val[1]
        visited[source] = True
        
        for dest in range(gph.count):
            alt = gph.adj[source][dest]
            if gph.adj[source][dest] > 0 and alt < dist[dest] and visited[dest] == False:
                dist[dest] = alt
                previous[dest] = source
                pq.UpdateKey(alt, dest)
    
    printPath(graph.count, previous,dist)

int main()
{
graph = Graph(9)
addUndirectedEdge(&graph,0, 1, 4)
addUndirectedEdge(&graph,0, 7, 8)
addUndirectedEdge(&graph,1, 2, 8)
addUndirectedEdge(&graph,1, 7, 11)
addUndirectedEdge(&graph,2, 3, 7)
addUndirectedEdge(&graph,2, 8, 2)
addUndirectedEdge(&graph,2, 5, 4)
addUndirectedEdge(&graph,3, 4, 9)
addUndirectedEdge(&graph,3, 5, 14)
addUndirectedEdge(&graph,4, 5, 10)
addUndirectedEdge(&graph,5, 6, 2)
addUndirectedEdge(&graph,6, 7, 1)
addUndirectedEdge(&graph,6, 8, 6)
addUndirectedEdge(&graph,7, 8, 7)
#Dijkstra(graph, 0)
Prims(graph)
# graph.Print()
}

def HamiltonianCycleUtil(graph , path, added):
    # Base case: full length path is found 
    # this last check can be modified to make it a path.
    if len(path) == graph.count:
        if graph.adj[ path[-1] ][ path[0] ] == 1:
            path.append(path[0])
            return True
        else:
            return False
    
    for vertex in range(graph.count):
        # there is a path from last element and next vertex 
        if graph.adj[path[-1]][vertex] == 1 and added[vertex] == False:
            path.append(vertex)
            added[vertex] = True
            if HamiltonianCycleUtil(graph, path, added):
                return True
            # backtracking
            path.pop()
            added[vertex] = False
    return False

def HamiltonianCycle(graph):
    path = []
    path.append(0)
    added = [False]*graph.count
    added[0] = True
    if HamiltonianCycleUtil(graph, path, added):
        print "Hamiltonian Cycle found", path
        return True
    print "Hamiltonian Cycle not found"
    return False

def HamiltonianPathUtil(graph , path, added):
    # Base case: full length path is found 
    if len(path) == graph.count:
            return True
    
    for vertex in range(graph.count):
        # there is a path from last element and next vertex 
        # and next vertex is not already included in path.
        if graph.adj[path[-1]][vertex] == 1 and added[vertex] == False:
            path.append(vertex)
            added[vertex] = True
            if HamiltonianPathUtil(graph, path, added):
                return True
            # backtracking
            path.pop()
            added[vertex] = False
    return False

def HamiltonianPath(graph):
    path = []
    path.append(0)
    added = [False]*graph.count
    added[0] = True
    if HamiltonianPathUtil(graph, path, added):
        print "Hamiltonian Path found", path
        return True
    print "Hamiltonian Path not found"
    return False

int main2()
{
graph = Graph(5)
graph.adj = [ [0, 1, 0, 1, 0], 
                [1, 0, 1, 1, 0], 
                [0, 1, 0, 0, 1,],
                [1, 1, 0, 0, 1], 
                [0, 1, 1, 1, 0] ]
print HamiltonianPath(graph)


g2 = Graph(5)
g2.adj = [ [0, 1, 0, 1, 0], 
            [1, 0, 1, 1, 0], 
            [0, 1, 0, 0, 1,], 
            [1, 1, 0, 0, 0], 
            [0, 1, 1, 0, 0] ]
 
print HamiltonianPath(g2)
}
*/