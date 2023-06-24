/******************************************************************************
 *
 * A breadth first search on an undirected graph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#include "bfs.h"

// breadth first search from a single source s
void BreadthFirstSearch::bfs(const Graph& g, const int s) {
    Queue<int> q;

    // initialize distances and visitation
    for (auto v = 0; v < no_vertices; v++) {
        dist_to[v] = std::numeric_limits<int>::max();
        edge_to[v] = -1;
        marked[v] = false;
    }
    dist_to[s] = 0;
    marked[s] = true;
    q.enqueue(s);

    // run BFS by processing the queue
    while (!q.is_empty()) {
        int v = q.dequeue();
        for (auto w : g.adj(v))
            if (!marked[w]) {
                edge_to[w] = v;
                dist_to[w] = dist_to[v] + 1;
                marked[w] = true;
                q.enqueue(w);
            }
    }

    // done!
    return;
}

// returns if there is a path between the source vertex and vertex v
bool BreadthFirstSearch::has_path_to(const int v) const {
    // validate the target index
    if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
    return (marked[v]);
}

// returns the number of edges in a shortest path between the source vertex and vertex v
int BreadthFirstSearch::distance_to(const int v) const {
    // validate the target index
    if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
    return (dist_to[v]);
}

// returns a shortest path between the source vertex and a vertex v
Stack<int> BreadthFirstSearch::path_to(const int v) const {
    Stack<int> path;

    if (!has_path_to(v)) return (path);
    int x = v;
    while (dist_to[x] > 0) {
        path.push(x);
        x = edge_to[x];
    }
    path.push(x);
    return (path);
}
