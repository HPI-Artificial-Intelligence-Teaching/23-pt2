/******************************************************************************
 *
 * A breadth first search on an undirected graph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./dfs_test ../data/tinyCG.txt 0
 *  0 to 0 (0):  0
 *  0 to 1 (1):  0-1
 *  0 to 2 (1):  0-2
 *  0 to 3 (2):  0-2-3
 *  0 to 4 (2):  0-2-4
 *  0 to 5 (1):  0-5
 *
 *  % ./dfs_test ../data/mediumG.txt 0
 *  0 to 0 (0):  0
 *  0 to 1 (8):  0-160-32-5-4-159-234-130-1
 *  0 to 2 (7):  0-204-168-151-57-7-42-2
 *  0 to 3 (5):  0-204-144-48-45-3
 *  0 to 4 (4):  0-160-32-5-4
 *  0 to 5 (3):  0-160-32-5
 *  0 to 6 (10):  0-204-168-151-57-7-42-2-14-166-6
 *  0 to 7 (5):  0-204-168-151-57-7
 *  ...
 *
 ******************************************************************************/

#include "bfs.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 3) {
        cerr << "Invalid number of arguments. Call with filename and index of source vertex." << endl;
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

    // read the source vertex and initialize the depth-first search
    int s = atoi(argv[2]);
    BreadthFirstSearch bfs(g, s);

    // output the graph on the screen
    for (auto v = 0; v < g.V(); v++) {
        if (bfs.has_path_to(v)) {
            cout << s << " to " << v << " (" << bfs.distance_to(v) << "):  ";
            for (auto x : bfs.path_to(v)) {
                if (x == s)
                    cout << x;
                else
                    cout << "-" << x;
            }
            cout << endl;
        } else {
            cout << s << " to " << v << " (-):  not connected" << endl;
        }
    }

    return (0);
}