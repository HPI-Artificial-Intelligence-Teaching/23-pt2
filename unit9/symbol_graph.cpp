/******************************************************************************
 *
 * An undirected graph, where the vertex names are arbitrary strings.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#include "symbol_graph.h"

#include <fstream>
#include <iostream>
#include <sstream>

// constructor
SymbolGraph::SymbolGraph(const string& file_name, const char delimiter) {
    ifstream file;
    string line;

    // First pass builds the index by reading strings to associate distinct strings with an index
    st = new RedBlackBST<string, int>();

    file.open(file_name);
    if (!file) {
        cerr << "Unable to open file" << file_name << endl;
        exit(-1);
    }
    while (getline(file, line)) {
        string token;
        stringstream ss(line);
        while (getline(ss, token, delimiter)) {
            if (!st->contains(token))
                st->put(token, st->size());
        }
    }
    file.close();

    // Second pass builds the inverse index
    keys = new string[st->size()];

    file.open(file_name);
    while (getline(file, line)) {
        string token;
        stringstream ss(line);
        while (getline(ss, token, delimiter)) {
            keys[*(st->get(token))] = token;
        }
    }
    file.close();

    // Third pass builds the graph
    graph = new Graph(st->size());

    file.open(file_name);
    while (getline(file, line)) {
        string key;
        stringstream ss(line);
        getline(ss, key, delimiter);
        int v = *(st->get(key));

        string token;
        while (getline(ss, token, delimiter)) {
            int w = *(st->get(token));
            graph->add_edge(v, w);
        }
    }
    file.close();
}
