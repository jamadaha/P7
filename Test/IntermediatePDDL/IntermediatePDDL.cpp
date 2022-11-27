#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

#include "../../src/IntermediatePDDL/PDDL::Domain.hh"
#include "../../src/PDDLParser/pddldriver.hh"
#include "../../src/IntermediatePDDL/PDDLConverter.hh"

using namespace std;


const string TAG = "IntermediatePDDL ";

const string domainFile = "./TestFiles/gripper.pddl";
const string exDomainName = "gripper";
const vector<string> exDomainReq = {":strips", ":equality"};
const vector<string> exConditions = {"ROOM", "BALL", "GRIPPER", "AT-LOBBY", "AT-BALL", "FREE", "CARRY"};
const vector<string> exActions = {"move", "pick-up", "drop"};
const vector<string> exArgs = {"?z", "?y", "?x"};

bool cmp(vector<string> as, vector<string> bs){
    bool acc = false;
    for(string a : as)
        for (string b : bs)
            acc = (a == b) ? true : false;

    return acc;
}

TEST_CASE(TAG + "PDDL::Domain domain name") {
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDL::Domain domain = PDDLConverter::Convert(driver.domain);

    REQUIRE(domain.name == exDomainName);
}

TEST_CASE(TAG + "PDDL::Domain requirements") {
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDL::Domain domain = PDDLConverter::Convert(driver.domain);

    REQUIRE(cmp(domain.requirements, exDomainReq));
}

TEST_CASE(TAG + "PDDL::Domain preconditions"){
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDL::Domain domain = PDDLConverter::Convert(driver.domain);

    auto preds = domain.predicates;
    vector<string> predStrings;

    for (auto p : preds)
        predStrings.push_back(p.name);

    REQUIRE(cmp(predStrings, exConditions));
}

TEST_CASE(TAG + "PDDL::Domain action names"){
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDL::Domain domain = PDDLConverter::Convert(driver.domain);

    auto acts = domain.actions;
    vector<string> actStrings;

    for (auto a : acts)
	    actStrings.push_back(a.name);

    REQUIRE(cmp(actStrings, exActions));
}

TEST_CASE(TAG + "PDDL::Domain arguments"){
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDL::Domain domain = PDDLConverter::Convert(driver.domain);

    auto acts = domain.actions;
    unordered_set<string> args;
	vector<string> argString;

    for (auto a : acts)
        for (auto arg : a.parameters)
            args.insert(arg);

	for (string a : args)
		argString.push_back(a);
    
    REQUIRE(cmp(argString, exArgs));
}