#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/PDDLParser/pddldriver.hh"

const std::string TAG = "PDDLParser ";

TEST_CASE(TAG + "CanParseDomainFile") {
    PDDLDriver driver;
    driver.parse("../../Test/PDDLParser/TestFiles/gripper.pddl");
    REQUIRE(driver.domain != nullptr);
    REQUIRE(driver.problem == nullptr);
}

TEST_CASE(TAG + "CanParseProblemFile") {
    PDDLDriver driver;
    driver.parse("../../Test/PDDLParser/TestFiles/gripper-4.pddl");
    REQUIRE(driver.domain == nullptr);
    REQUIRE(driver.problem != nullptr);
}
