int HamiltonianCycleUtil(Graph *graph, int path[], int added)
{ // Base case full length path is found
    // this last check can be modified to make it a path.
    if (len(path) == graph->count)
    {
        if (graph->adj[path[-1]][path[0]] == 1)
        {
            path.append(path[0]);
            return 1;
        }
        else
            return 0;
    }
    for (vertex in range(graph->count))
    { // there is a path from last element and next vertex
        if (graph->adj[path[-1]][vertex] == 1 and added[vertex] == 0)
        {
            path.append(vertex);
            added[vertex] = 1;
            if (HamiltonianCycleUtil(graph, path, added))
                return 1;
            // backtracking
            path.pop();
            added[vertex] = 0;
        }
    }
    return 0;
}

int HamiltonianCycle(graph)
{
    path = [];
    path.append(0);
    added = [0] * graph -> count;
    added[0] = 1;
    if (HamiltonianCycleUtil(graph, path, added))
    {
        print "Hamiltonian Cycle found", path return 1;
    }
    print "Hamiltonian Cycle not found" return 0
}

int HamiltonianPathUtil(graph, path, added)
    // Base case full length path is found
    if (len(path) == graph->count) return 1;

for (vertex in range(graph->count))
{ // there is a path from last element and next vertex
    // and next vertex is not already included in path.
    if
        graph->adj[path[-1]][vertex] == 1 and added[vertex] == 0
        {
            path.append(vertex)
                added[vertex] = 1;
            if (HamiltonianPathUtil(graph, path, added))
                return 1;
            // backtracking
            path.pop();
            added[vertex] = 0;
        }
}
return 0;

def HamiltonianPath(graph)
{
    path = [];
    path.append(0);
    added = [0] * graph -> count;
    added[0] = 1;
    ;
    if (HamiltonianPathUtil(graph, path, added))
    {
        print "Hamiltonian Path found", path;
        return 1;
    }
    print "Hamiltonian Path not found";
    return 0;
}

int main2()
{
    Graph graph;
    graph->count = 5;
    graph->adj = {{0, 1, 0, 1, 0},
                  {1, 0, 1, 1, 0},
                  {
                      0,
                      1,
                      0,
                      0,
                      1,
                  },
                  {1, 1, 0, 0, 1},
                  {0, 1, 1, 1, 0}};
    print HamiltonianPath(graph);

    Graph g2;
    g2->count = 5;
    g2.adj = {{0, 1, 0, 1, 0},
              {1, 0, 1, 1, 0},
              {
                  0,
                  1,
                  0,
                  0,
                  1,
              },
              {1, 1, 0, 0, 0},
              {0, 1, 1, 0, 0}};

    print HamiltonianPath(g2);
}