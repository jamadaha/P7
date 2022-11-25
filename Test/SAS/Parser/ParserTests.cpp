#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/SAS/Parser/Parser.hh"

using namespace std;
using namespace SAS;

const std::string TAG = "Parser ";

TEST_CASE(TAG + "SingleAction") {
    Parser Parser;
    std::string testCase = "(test_action)\n; cost = 1 (general cost)";
    Plan plan = Parser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(1 == plan.actions.size());
    REQUIRE("test_action" == plan.actions[0].name);
    REQUIRE(0 == plan.actions[0].parameters.size());
}

TEST_CASE(TAG + "SingleAction_TrailingSpace") {
    Parser Parser;
    std::string testCase = "(test_action) \n; cost = 1 (general cost) ";
    Plan plan = Parser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(1 == plan.actions.size());
    REQUIRE("test_action" == plan.actions[0].name);
    REQUIRE(0 == plan.actions[0].parameters.size());
}

TEST_CASE(TAG + "SingleAction_PrecedingSpace") {
    Parser Parser;
    std::string testCase = " (test_action)\n ; cost = 1 (general cost)";
    Plan plan = Parser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(1 == plan.actions.size());
    REQUIRE("test_action" == plan.actions[0].name);
    REQUIRE(0 == plan.actions[0].parameters.size());
}

TEST_CASE(TAG + "SingleAction_Parameters") {
    Parser Parser;
    std::string testCase = "(test_action a b)\n ; cost = 1 (general cost)";
    Plan plan = Parser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(1 == plan.actions.size());
    REQUIRE("test_action" == plan.actions[0].name);
    REQUIRE(2 == plan.actions[0].parameters.size());
    REQUIRE("a" == plan.actions[0].parameters[0]);
    REQUIRE("b" == plan.actions[0].parameters[1]);
}

TEST_CASE(TAG + "MultiAction") {
    Parser Parser;
    std::string testCase = "(test_action1)\n(test_action2)\n ; cost = 1 (general cost)";
    Plan plan = Parser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(2 == plan.actions.size());
    REQUIRE("test_action1" == plan.actions[0].name);
    REQUIRE("test_action2" == plan.actions[1].name);
    REQUIRE(0 == plan.actions[0].parameters.size());
    REQUIRE(0 == plan.actions[1].parameters.size());
}

TEST_CASE(TAG + "MultiAction_Parameters") {
    Parser Parser;
    std::string testCase = "(test_action1 a b)\n(test_action2 c d)\n ; cost = 1 (general cost)";
    Plan plan = Parser.Parse(testCase);
    REQUIRE(1 == plan.cost);
    REQUIRE(2 == plan.actions.size());
    REQUIRE("test_action1" == plan.actions[0].name);
    REQUIRE("test_action2" == plan.actions[1].name);
    REQUIRE(2 == plan.actions[0].parameters.size());
    REQUIRE(2 == plan.actions[1].parameters.size());
    REQUIRE("a" == plan.actions[0].parameters[0]);
    REQUIRE("b" == plan.actions[0].parameters[1]);
    REQUIRE("c" == plan.actions[1].parameters[0]);
    REQUIRE("d" == plan.actions[1].parameters[1]);
}


