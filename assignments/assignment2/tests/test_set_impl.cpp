#include <doctest.h>
#include "../src/Set.h"

TEST_CASE("A3.1T1: Testen der Axiome")
{
    Set<int> s;
    SUBCASE("Test der 'contains' Axiome")
    {
        CHECK(s.contains(1) == false);
        s.add(1);
        CHECK(s.contains(1) == true);
        s.remove(1);
        CHECK(s.contains(1) == false);
        s.remove(2);
    }
    SUBCASE("Test der 'size' Axiome")
    {
        CHECK(s.size() == 0);
        s.add(1);
        CHECK(s.size() == 1);
        s.add(2);
        CHECK(s.size() == 2);
        SUBCASE("Adding the same element twice does not change size")
        {
            s.add(2);
            CHECK(s.size() == 2);
        }
        s.remove(1);
        s.remove(2);
        CHECK(s.size() == 0);
    }
    SUBCASE("Test der 'add' & 'remove' Axiome")
    {
        s.add(1).add(1);
        CHECK(s.size() == 1);
        CHECK(s.contains(1) == true);
        s.remove(1);
        CHECK(s.size() == 0);
    }
}