#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <filesystem>

#include "../../src/SAS/CodeGenerator/CodeGenerator.hh"
#include "../../src/SAS/Parser/Parser.hh"

using namespace std;
using namespace SAS;

const string tag = "SASCodeGenerator: ";

void CheckIfValid(Plan result, int expectedCost, vector<string> expectedActions, vector<vector<string>> expectedObjects) {
    REQUIRE(expectedCost == result.cost);
    for (int i = 0; i < expectedActions.size(); i++) {
        REQUIRE(expectedActions.at(i) == result.actions.at(i).name);
        for (int j = 0; j < expectedObjects.at(i).size(); j++)
            REQUIRE(expectedObjects.at(i).at(j) == result.actions.at(i).parameters.at(j));
    }
}

TEST_CASE(tag + "-CanParseFile-test1") {
    string testFile = "sas-test1.sas";
    vector<string> expectedActions{
        "action1",
        "action1"
    };
    vector<vector<string>> expectedObjects{
        {"obj1", "obj2"},
        {"obj1", "obj2"}
    };
    int expectedCost = 2;

    Parser parser;
    Plan result = parser.Parse(std::filesystem::path("./TestFiles/" + testFile));

    CheckIfValid(result, expectedCost, expectedActions, expectedObjects);
}

TEST_CASE(tag + "-CanParseFile-test2") {
    string testFile = "sas-test2.sas";
    vector<string> expectedActions{
        "action1",
        "action2"
    };
    vector<vector<string>> expectedObjects{
        {"obj1", "obj2"},
        {"obj2", "obj1"}
    };
    int expectedCost = 2;

    Parser parser;
    Plan result = parser.Parse(std::filesystem::path("./TestFiles/" + testFile));

    CheckIfValid(result, expectedCost, expectedActions, expectedObjects);
}

TEST_CASE(tag + "-CanParseFile-test3") {
    string testFile = "sas-test3.sas";
    vector<string> expectedActions{
    };
    vector<vector<string>> expectedObjects{
    };
    int expectedCost = 0;

    Parser parser;
    Plan result = parser.Parse(std::filesystem::path("./TestFiles/" + testFile));

    CheckIfValid(result, expectedCost, expectedActions, expectedObjects);
}

TEST_CASE(tag + "-CanParseFile-test4") {
    string testFile = "sas-test4.sas";
    vector<string> expectedActions{
        "action1",
        "action2"
    };
    vector<vector<string>> expectedObjects{
        {"obj1", "obj2"},
        {"obj2", "obj1"}
    };
    int expectedCost = 2;

    Parser parser;
    Plan result = parser.Parse(std::filesystem::path("./TestFiles/" + testFile));

    CheckIfValid(result, expectedCost, expectedActions, expectedObjects);
}

TEST_CASE(tag + "-CanParseFile-test5") {
    string testFile = "sas-test5.sas";
    vector<string> expectedActions{
        "action1",
        "action2"
    };
    vector<vector<string>> expectedObjects{
        {"obj1", "obj2"},
        {"obj2", "obj1"}
    };
    int expectedCost = 2;

    Parser parser;
    Plan result = parser.Parse(std::filesystem::path("./TestFiles/" + testFile));

    CheckIfValid(result, expectedCost, expectedActions, expectedObjects);
}
