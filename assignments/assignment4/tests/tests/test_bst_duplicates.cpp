#include <doctest.h>

#include "../src/bst.h"

TEST_CASE("A2.1: BST Erweiterung") {
    BST<int, int> bst;
    bst.put(100, 1);
    bst.put(100, 2);
    bst.put(100, 3);
    bst.put(100, 4);
    SUBCASE("Abfrage") {
        // nimmt an das get einen std::vector an Value Objekten (hier int)
        // zurückgibt
        std::vector<int> v = bst.get_all(100);
        CHECK(v.size() == 4);
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
        CHECK(v[2] == 3);
        CHECK(v[3] == 4);
    }
    SUBCASE("Löschen") {
        bst.remove_all(100);
        CHECK_FALSE(bst.contains(100));
        CHECK(bst.get_all(100).size() == 0);
    }
}