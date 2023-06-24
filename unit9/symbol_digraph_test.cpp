/******************************************************************************
 *
 * A directed graph, where the vertex names are arbitrary strings.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./symbol_digraph_test ../data/routes.txt " "
 *  JFK
 *     ORD
 *     ATL
 *     MCO
 *  ATL
 *     MCO
 *     HOU
 *  LAX
 *
 ******************************************************************************/

#include "symbol_digraph.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 3) {
        cerr << "Invalid number of arguments. Call with filename and delimiter." << endl;
        return (1);
    }

    // read the symbol graph from the file
    SymbolDigraph sdg(argv[1], argv[2][0]);
    const Digraph* graph = sdg.get_graph();

    // read a string as input
    string source;
    while (getline(cin, source)) {
        if (sdg.contains(source)) {
            int s = sdg.index_of(source);
            for (auto v : graph->adj(s)) {
                cout << "   " << sdg.name_of(v) << endl;
            }

        } else {
            cout << "input does not contain '" << source << "'" << endl;
        }
    }

    return (0);
}