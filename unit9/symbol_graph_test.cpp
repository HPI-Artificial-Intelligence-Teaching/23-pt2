/******************************************************************************
 *
 * An undirected graph, where the vertex names are arbitrary strings.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./symbol_graph_test ../data/routes.txt " "
 *  JFK
 *     MCO
 *     ATL
 *     ORD
 *  LAX
 *     PHX
 *     LAS
 *
 *  % ./symbol_graph_test ../data/movies.txt "/"
 *  Tin Men (1987)
 *     Hershey, Barbara
 *     Geppi, Cindy
 *     Jones, Kathy (II)
 *     Herr, Marcia
 *     ...
 *     Blumenfeld, Alan
 *     DeBoy, David
 *  Bacon, Kevin
 *     Woodsman, The (2004)
 *     Wild Things (1998)
 *     Where the Truth Lies (2005)
 *     Tremors (1990)
 *     ...
 *     Apollo 13 (1995)
 *     Animal House (1978)
 *
 ******************************************************************************/

#include "symbol_graph.h"

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
    SymbolGraph sg(argv[1], argv[2][0]);
    const Graph* graph = sg.get_graph();

    // read a string as input
    string source;
    while (getline(cin, source)) {
        if (sg.contains(source)) {
            int s = sg.index_of(source);
            for (auto v : graph->adj(s)) {
                cout << "   " << sg.name_of(v) << endl;
            }

        } else {
            cout << "input does not contain '" << source << "'" << endl;
        }
    }

    return (0);
}