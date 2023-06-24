/******************************************************************************
 *
 * A depth first search on an undirected graph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./dfs_tet ../data/tinyG.txt 0
 *  0 to 0:  0
 *  0 to 1:  0-1
 *  0 to 2:  0-2
 *  0 to 3:  0-6-4-5-3
 *  0 to 4:  0-6-4
 *  0 to 5:  0-6-4-5
 *  0 to 6:  0-6
 *  0 to 7:  not connected
 *  0 to 8:  not connected
 *  0 to 9:  not connected
 *  0 to 10:  not connected
 *  0 to 11:  not connected
 *  0 to 12:  not connected
 *
 *  NOT fully connected
 *
 *  % ./dfs_test ../data/tinyG.txt 9
 *  9 to 0:  not connected
 *  9 to 1:  not connected
 *  9 to 2:  not connected
 *  9 to 3:  not connected
 *  9 to 4:  not connected
 *  9 to 5:  not connected
 *  9 to 6:  not connected
 *  9 to 7:  not connected
 *  9 to 8:  not connected
 *  9 to 9:  9
 *  9 to 10:  9-10
 *  9 to 11:  9-11
 *  9 to 12:  9-11-12
 *
 *  NOT fully connected
 *
 *  % ./dfs_test ../data/mediumG.txt 0
 *  0 to 0:  0
 *  0 to 1:  0-225-15-222-23-9-195-142-118-57-7-230-21-240-4-239-26-5-226-32-248-44-231-52-208-65-27-233-62-188-71-184-125-101-42-2-141-18-14-166-6-236-16-178-98-36-12-242-28-223-17-229-53-22-145-34-120-56-161-46-186-72-1
 *  0 to 2:  0-225-15-222-23-9-195-142-118-57-7-230-21-240-4-239-26-5-226-32-248-44-231-52-208-65-27-233-62-188-71-184-125-101-42-2
 *  ...
 *  0 to 249:  0-225-15-222-23-9-195-142-118-57-7-230-21-240-4-239-26-5-226-32-248-44-231-52-208-65-27-233-62-188-71-184-125-101-42-2-141-18-14-166-6-236-16-178-98-36-12-242-28-223-17-229-53-22-145-34-120-56-161-46-186-72-1-220-20-247-40-194-61-234-87-136-55-217-45-3-241-31-228-37-153-76-115-95-83-48-232-50-201-104-185-49-204-58-33-163-24-211-39-209-66-206-149-80-59-144-93-202-68-191-97-176-160-187-77-151-138-78-159-112-128-69-173-90-113-198-35-88-41-182-121-170-158-249
 *
 *  Fully connected
 *
 ******************************************************************************/

#include "dfs.h"

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
    DepthFirstSearch dfs(g, s);

    // output the graph on the screen
    // output the graph on the screen
    for (auto v = 0; v < g.V(); v++) {
        if (dfs.has_path_to(v)) {
            cout << s << " to " << v << ":  ";
            for (auto x : dfs.path_to(v)) {
                if (x == s)
                    cout << x;
                else
                    cout << "-" << x;
            }
            cout << endl;
        } else {
            cout << s << " to " << v << ":  not connected" << endl;
        }
    }
    cout << endl
         << ((dfs.count() == g.V()) ? "Fully connected" : "NOT fully connected") << endl;

    return (0);
}