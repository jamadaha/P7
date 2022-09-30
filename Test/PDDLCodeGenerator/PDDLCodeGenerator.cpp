#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "../../src/PDDLCodeGenerator/PDDLDomainCodeGenerator.h"
#include "../../src/PDDLCodeGenerator/PDDLProblemCodeGenerator.h"

using namespace std;

const string TAG = "PDDLCodeGenerator ";
const string domainFile = "./TestFiles/gripper.pddl";
const string problemFile = "./TestFiles/gripper-4.pddl";

TEST_CASE(TAG + "PDDLDomainGenerator") {
    PDDLDriver driver;
    driver.parse(domainFile);
    Domain* domain = driver.domain;
    PDDLDomainCodeGenerator PDDLDomainGen = PDDLDomainCodeGenerator();
    string domainString = PDDLDomainGen.GenerateDomainString(domain);

    ofstream newfile ("domain.pddl", ofstream::out | ofstream::trunc);
    newfile << domainString;
    newfile.close();

    PDDLDriver driver2;
    driver2.parse("domain.pddl");
    Domain* generatedDomain = driver2.domain;
    REQUIRE(generatedDomain->_requirements->size() == domain->_requirements->size());
    REQUIRE(generatedDomain->_predicates->size() == domain->_predicates->size());
    REQUIRE(generatedDomain->_actions->size() == domain->_actions->size());
}

TEST_CASE(TAG + "PDDLProblemGenerator") {
    PDDLDriver driver;
    driver.parse(problemFile);
    Problem* problem = driver.problem;
    PDDLProblemCodeGenerator PDDLProblemGen = PDDLProblemCodeGenerator();
    string problemString = PDDLProblemGen.GenerateProblemString(problem);

    ofstream newfile ("problem.pddl", ofstream::out | ofstream::trunc);
    newfile << problemString;
    newfile.close();

    PDDLDriver driver2;
    driver2.parse("problem.pddl");
    Problem* generatedProblem = driver2.problem;
    REQUIRE(generatedProblem->_name == problem->_name);
    REQUIRE(generatedProblem->_domain == problem->_domain);
    REQUIRE(generatedProblem->_objects->size() == problem->_objects->size());
    REQUIRE(generatedProblem->_init->size() == problem->_init->size());
    REQUIRE(generatedProblem->_goal->size() == problem->_goal->size());
}