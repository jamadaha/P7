#include <catch2/catch_test_macros.hpp>

#include "../../src/MacroGenerator/MacroGenerator.hh"

const std::string TAG = "Macro ";

TEST_CASE(TAG + "two different actions") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "overlapping preconditions") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "precon - positive eff") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "positive - negative eff") {
    REQUIRE(1==0);
}

TEST_CASE(TAG + "negative - positive eff") {
    REQUIRE(1==0);
}