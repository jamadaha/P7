#include <catch2/catch_test_macros.hpp>

static int factorial(int n) {
    if (n <= 1) {
        return n;
    }
    return n * factorial(n - 1);
}

TEST_CASE("Case 1") {
    REQUIRE(factorial( 1) == 1);
    REQUIRE(factorial(10) == 3'628'800);
    REQUIRE(factorial( 0) == 1);
}

TEST_CASE("Case 2") {
    REQUIRE(1 == 1);
}