#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/SASParser/SASParser.h"

TEST_CASE("SASParser Base") {
    SASParser sasParser = SASParser();
    std::string testCase = "(test_action)\n; cost = 1 (general cost)";
    SASPlan plan = sasParser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(1 == plan.actions.size());
    REQUIRE("test_action" == plan.actions[0].name);
    REQUIRE(0 == plan.actions[0].parameters.size());
}

TEST_CASE("SASParser Base_TrailingSpace") {
    SASParser sasParser = SASParser();
    std::string testCase = "(test_action) \n; cost = 1 (general cost) ";
    SASPlan plan = sasParser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(1 == plan.actions.size());
    REQUIRE("test_action" == plan.actions[0].name);
    REQUIRE(0 == plan.actions[0].parameters.size());
}

TEST_CASE("SASParser Base_PrecedingSpace") {
    SASParser sasParser = SASParser();
    std::string testCase = " (test_action)\n ; cost = 1 (general cost)";
    SASPlan plan = sasParser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(1 == plan.actions.size());
    REQUIRE("test_action" == plan.actions[0].name);
    REQUIRE(0 == plan.actions[0].parameters.size());
}

