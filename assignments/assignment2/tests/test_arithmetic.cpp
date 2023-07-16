#include <doctest.h>
#include <stdexcept>
#include "../src/arithmetic.cpp"

TEST_CASE("A2.1 Test der Infix to Postfix umwandlung")
{
    SUBCASE("Hilfestellung") // nur um den Output für ein komplexen Fall zu Zeigen
    {
        MESSAGE(
            "\nIn: (1.0 / 3.0) + (2.0 * 4.0)",
            "\nOut: ", infix_to_postfix("(1.0 / 3.0) + (2.0 * 4.0)"));
    }
    SUBCASE("Gültiger Infix Input, keine Klammern")
    {
        CHECK(infix_to_postfix("1.0 + 2.0") == std::string("1.0 2.0 +"));
        CHECK(infix_to_postfix("1.0 + 2.0 - 3.0") == std::string("1.0 2.0 + 3.0 -"));
    }
    SUBCASE("Gültiger Infix Input, mit Klammern")
    {
        CHECK(infix_to_postfix("(1.0 + 2.0)") == std::string("1.0 2.0 +"));
        CHECK(infix_to_postfix("(1.0 / 3.0) + (2.0 * 4.0)") == std::string("1.0 3.0 / 2.0 4.0 * +"));
    }
    SUBCASE("Ungültiger Infix Input, mit Klammern")
    {
        CHECK_THROWS_AS(infix_to_postfix("( 1.0 + 2.0"), std::invalid_argument);
        CHECK_THROWS_AS(infix_to_postfix("1.0 + 2.0 )"), std::invalid_argument);
    }
}
TEST_CASE("A2.2 Test der Auswertung Arithmetischer Ausdrücke")
{
    SUBCASE("Gültige Postfix Inputs")
    {
        CHECK(evaluate_infix("1.0 + 2.0") == 3.0);
        CHECK(evaluate_infix("1.0 + 2.0 - 3.0") == 0.0);
        CHECK(evaluate_infix("(1.0 / 2.0) + (2.0 * 4.0)") == 8.5);
    }
    SUBCASE("Ungültige Postfix Inputs")
    {
        CHECK_THROWS_AS(evaluate_infix("1.0 + 2.0 +"), std::invalid_argument);
        CHECK_THROWS_AS(evaluate_infix("1.0 + 2.0 + 3.0)"), std::invalid_argument);
    }
}