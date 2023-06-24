/******************************************************************************
 *
 * A depth first search on an undirected graph that computes connected components.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./cc_test ../data/tinyG.txt
 *  3 components
 *  0 1 2 3 4 5 6
 *  7 8
 *  9 10 11 12
 *
 *  % ./cc_test ../data/mediumG.txt
 *  1 components
 *  0 1 2 3 4 5 6 7 8 9 10 ...
 *
 ******************************************************************************/

#include "cc.h"

#include <fstream>
#include <iostream>

#include "queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 2) {
        cerr << "Invalid number of arguments. Call with filename." << endl;
        return (1);
    }

    // read the graph from the file
    ifstream graph_file;
    graph_file.open(argv[1]);
    if (!graph_file) {
        cerr << "Unable to open file" << argv[1] << endl;
        return (1);
    }
    Graph g(graph_file);
    graph_file.close();

    // compute the connected components
    CC cc(g);

    // output the connected components on the screen
    int m = cc.count();
    cout << m << " components" << endl;

    // compute list of vertices in each connected component
    Queue<int> components[m];

    for (auto v = 0; v < g.V(); v++) components[cc.id(v)].enqueue(v);

    // print results
    for (auto i = 0; i < m; i++) {
        for (int v : components[i]) cout << v << " ";
        cout << endl;
    }

    return (0);
}