#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

#include "../../../src/PDDL/Domain.hh"
#include "../../../src/PDDL/Parsers/ExternalParser.hh"

using namespace std;

const string TAG = "PDDLConverter ";

const string domainFile = "./TestFiles/gripper.pddl";
const string problemFile = "./TestFiles/gripper-4.pddl";
const string exDomainName = "gripper";
const vector<string> exDomainReq = { ":strips", ":equality" };
const vector<string> exConditions = { "ROOM", "BALL", "GRIPPER", "AT-LOBBY", "AT-BALL", "FREE", "CARRY" };
const vector<string> exActions = { "move", "pick-up", "drop" };
const vector<string> exArgs = { "?z", "?y", "?x" };

bool cmp(vector<string> as, vector<string> bs) {
    bool acc = false;
    for (string a : as)
        for (string b : bs)
            acc = (a == b) ? true : false;

    return acc;
}

TEST_CASE(TAG + "Domain domain name") {
    ExternalParser parser;
    PDDL::Instance result = parser.Parse(domainFile, problemFile);

    REQUIRE(result.domain->name == exDomainName);
}

TEST_CASE(TAG + "Domain requirements") {
    ExternalParser parser;
    PDDL::Instance result = parser.Parse(domainFile, problemFile);

    REQUIRE(cmp(result.domain->requirements, exDomainReq));
}

TEST_CASE(TAG + "Domain preconditions") {
    ExternalParser parser;
    PDDL::Instance result = parser.Parse(domainFile, problemFile);

    auto preds = result.domain->predicates;
    vector<string> predStrings;

    for (auto p : preds)
        predStrings.push_back(p.name);

    REQUIRE(cmp(predStrings, exConditions));
}

TEST_CASE(TAG + "Domain action names") {
    ExternalParser parser;
    PDDL::Instance result = parser.Parse(domainFile, problemFile);

    auto acts = result.domain->actions;
    vector<string> actStrings;

    for (auto a : acts)
        actStrings.push_back(a.name);

    REQUIRE(cmp(actStrings, exActions));
}

TEST_CASE(TAG + "Domain arguments") {
    ExternalParser parser;
    PDDL::Instance result = parser.Parse(domainFile, problemFile);

    auto acts = result.domain->actions;
    unordered_set<string> args;
    vector<string> argString;

    for (auto a : acts)
        for (auto arg : a.parameters)
            args.insert(arg);

    for (string a : args)
        argString.push_back(a);

    REQUIRE(cmp(argString, exArgs));
}