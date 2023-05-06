/******************************************************************************
 *
 *  A generic bag or multiset, implemented using a singly linked list.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % more ../data/tobe.txt
 *  to be or not to - be - - that - - - is
 *
 *  % ./bag_test < ../data/tobe.txt
 *  size of bag = 14
 *  is
 *  -
 *  -
 *  -
 *  that
 *  -
 *  -
 *  be
 *  -
 *  to
 *  not
 *  or
 *  be
 *  to
 *
 ******************************************************************************/

#include "bag.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    Bag<string> bag;
    string item;
    while (cin >> item)
        bag.add(item);

    cout << "size of bag = " << bag.size() << endl;
    for (auto& s : bag)
        cout << s << endl;

    return (0);
}