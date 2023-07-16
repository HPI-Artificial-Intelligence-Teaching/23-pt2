#include <doctest.h>

#include "../src/trie.h"

TEST_CASE("A3: Trie") {
    Trie<char, int, 5> kt(strtoarr<5>("GCATN"));
    // add a few elements to trie
    kt.add(strtoarr<4>("GCAT"));
    kt.add(strtoarr<4>("GCTA"));
    kt.add(strtoarr<5>("GCTAG"));
    kt.add(strtoarr<4>("CTAG"));
    kt.add(strtoarr<3>("TAG"));
    kt.add(strtoarr<2>("TA"));

    SUBCASE("Nur Elemente des Alphabets können hinzugefügt werden") {
        CHECK_THROWS(kt.add(strtoarr<5>("GCTAM")));
    }

    SUBCASE("Test des Contain Verhaltens") {
        // Added element is contained in the trie
        CHECK(kt.contains(strtoarr<4>("GCAT")));

        // Non-added element is not contained in the trie
        CHECK_FALSE(kt.contains(strtoarr<3>("MMM")));

        // Prefix of an added element is contained in the trie
        CHECK(kt.contains(strtoarr<2>("GC")));
    }

    SUBCASE("Test Observing Verhalten") {
        // check that a added element is observed
        CHECK(kt.observed(strtoarr<4>("GCAT")));
        // check that a prefix of an added element is not observed
        CHECK_FALSE(kt.observed(strtoarr<2>("GC")));
    }
}