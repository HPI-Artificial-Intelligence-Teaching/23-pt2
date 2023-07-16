#include <doctest.h>
#include "../src/Stack.h"

TEST_CASE("A1.1T1: Testen der Axiome")
{
    Stack<int> s;
    SUBCASE("is_empty axioms")
    {
        CHECK(s.is_empty() == true);
        s.push(1);
        CHECK(s.is_empty() == false);
        s.pop();
        CHECK(s.is_empty() == true);
    }
    SUBCASE("adding to stack makes it longer, and length is correct")
    {
        for (int i = 0; i < 10; i++)
        {
            s.push(i);
        }
        CHECK(s.length() == 10);
    }
    SUBCASE("test LIFO")
    {
        s.push(1);
        CHECK(s.top() == 1);
    }
}