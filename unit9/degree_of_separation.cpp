/******************************************************************************
 *
 * A client for finding the degree of separation between one distinguished individual and
 * every other individual in a social network.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./degree_of_separation ../data/routes.txt " " "JFK"
 *  LAS
 *     JFK
 *     ORD
 *     DEN
 *     LAS
 *  DFW
 *     JFK
 *     ORD
 *     DFW
 *  EWR
 *     Not in database.
 *
 *  % ./degree_of_separation ../data/movies.txt "/" "Bacon, Kevin"
 *  Kidman, Nicole
 *     Bacon, Kevin
 *     Woodsman, The (2004)
 *     Grier, David Alan
 *     Bewitched (2005)
 *     Kidman, Nicole
 *  Grant, Cary
 *     Bacon, Kevin
 *     Planes, Trains & Automobiles (1987)
 *     Martin, Steve (I)
 *     Dead Men Don't Wear Plaid (1982)
 *     Grant, Cary
 *
 ******************************************************************************/

#include <iostream>
#include <string>

#include "bfs.h"
#include "symbol_graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 4) {
        cerr << "Invalid number of arguments. Call with filename, delimiter and source token." << endl;
        return (1);
    }

    // read the symbol graph from the file
    SymbolGraph sg(argv[1], argv[2][0]);
    if (!sg.contains(argv[3])) {
        cerr << argv[3] << " not in database." << endl;
        return (1);
    }

    // perform the breadth first search
    int s = sg.index_of(argv[3]);
    const Graph* graph = sg.get_graph();
    BreadthFirstSearch bfs(*graph, s);

    // read a string as input
    string sink;
    while (getline(cin, sink)) {
        if (sg.contains(sink)) {
            int t = sg.index_of(sink);
            if (bfs.has_path_to(t)) {
                for (auto v : bfs.path_to(t)) {
                    cout << "   " << sg.name_of(v) << endl;
                }
            } else {
                cout << "Not connected" << endl;
            }
        } else {
            cout << "   Not in database." << endl;
        }
    }

    return (0);
}