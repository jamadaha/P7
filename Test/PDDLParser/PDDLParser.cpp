#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/PDDLParser/pddldriver.hh"

const std::string TAG = "PDDLParser ";
const std::string domainFile = "./TestFiles/gripper.pddl";
const std::string problemFile = "./TestFiles/gripper-4.pddl";

#pragma region Domain Parsing

TEST_CASE(TAG + "CanParseDomainFile") {
    PDDLDriver driver;
    driver.parse(domainFile);
    REQUIRE(driver.domain != nullptr);
    REQUIRE(driver.problem == nullptr);
}

TEST_CASE(TAG + "CanParseDomainFile_Requirements") {
    PDDLDriver driver;
    driver.parse(domainFile);
    Domain* domain = driver.domain;
    REQUIRE(domain->_requirements->size() == 2);
}

TEST_CASE(TAG + "CanParseDomainFile_Predicates") {
    PDDLDriver driver;
    driver.parse(domainFile);
    Domain* domain = driver.domain;
    REQUIRE(domain->_predicates->size() == 7);
}

TEST_CASE(TAG + "CanParseDomainFile_Actions") {
    PDDLDriver driver;
    driver.parse(domainFile);
    Domain* domain = driver.domain;
    REQUIRE(domain->_actions->size() == 3);
}

#pragma endregion

#pragma region Problem Parsing

TEST_CASE(TAG + "CanParseProblemFile") {
    PDDLDriver driver;
    driver.parse(problemFile);
    REQUIRE(driver.domain == nullptr);
    REQUIRE(driver.problem != nullptr);
}

TEST_CASE(TAG + "CanParseProblemFile_Objects") {
    PDDLDriver driver;
    driver.parse(problemFile);
    Problem* problem = driver.problem;
    REQUIRE(problem->_objects->size() == 8);
}

TEST_CASE(TAG + "CanParseProblemFile_Inits") {
    PDDLDriver driver;
    driver.parse(problemFile);
    Problem* problem = driver.problem;
    REQUIRE(problem->_init->size() == 15);
}

TEST_CASE(TAG + "CanParseProblemFile_Goals") {
    PDDLDriver driver;
    driver.parse(problemFile);
    Problem* problem = driver.problem;
    REQUIRE(problem->_goal->size() == 4);
}

#pragma endregion