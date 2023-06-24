/******************************************************************************
 *
 * Min oriented indexed priority queue implementation using a binary heap
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  ./index_min_pq_test
 *  3 best
 *  0 it
 *  6 it
 *  4 of
 *  8 the
 *  2 the
 *  5 times
 *  7 was
 *  1 was
 *  9 worst
 *
 ******************************************************************************/

#include "index_min_pq.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    // insert a bunch of strings
    string str[] = {"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};
    const int length = sizeof(str) / sizeof(string);

    IndexMinPQ<string> pq(length);
    for (auto i = 0; i < length; i++) {
        pq.insert(i, str[i]);
    }

    // delete and print each key
    while (!pq.is_empty()) {
        int i = pq.del_min();
        cout << i << " " << str[i] << endl;
    }
    cout << endl;

    return (0);
}