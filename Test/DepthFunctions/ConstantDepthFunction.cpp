#include <catch2/catch_test_macros.hpp>

#include "../../src/DepthFunctions/ConstantDepthFunction.h"

using namespace std;
const string TAG = "ConstantDepthFunction ";

TEST_CASE(TAG + "SimpleTest") {
    vector<int> testCases = {1,2,10,75,1245623,0,1241};
    PDDLInstance emptyInstace(nullptr, nullptr);
    for (auto testCase : testCases) {
        BaseDepthFunction* function = new ConstantDepthFunction(testCase);
        int expected = testCase;
        int actual = function->GetDepth(emptyInstace);
        REQUIRE(expected == actual);
    }
}

TEST_CASE(TAG + "WithModifier") {
    double modifier = 0.5;
    vector<int> testCases = { 1,2,10,75,1245623,0,1241 };
    PDDLInstance emptyInstace(nullptr, nullptr);
    for (auto testCase : testCases) {
        BaseDepthFunction* function = new ConstantDepthFunction(testCase, modifier);
        int expected = testCase * modifier;
        int actual = function->GetDepth(emptyInstace);
        REQUIRE(expected == actual);
    }
}