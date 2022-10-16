#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/IntermediatePDDL/PDDLConverter.hh"
#include "../../src/PDDLCodeGenerator/PDDLCodeGenerator.hh"
#include "../../src/PDDLCodeGenerator/PDDLDomainCodeGenerator.hh"
#include "../../src/PDDLCodeGenerator/PDDLProblemCodeGenerator.hh"

using namespace std;

const string TAG = "PDDLCodeGenerator ";
const string domainFile = "./TestFiles/gripper.pddl";
const string problemFile = "./TestFiles/gripper-4.pddl";

TEST_CASE(TAG + "PDDLDomainGenerator") {
    PDDLDriver driver;
    driver.parse(domainFile);
    Domain* driverDomain = driver.domain;
    PDDLDomain domain = PDDLConverter::Convert(driverDomain);
    PDDLDomainCodeGenerator PDDLDomainGen = PDDLDomainCodeGenerator(&domain);
    string domainString = PDDLDomainGen.GenerateDomainString();

    ofstream newfile ("domain.pddl", ofstream::out | ofstream::trunc);
    newfile << domainString;
    newfile.close();

    PDDLDriver driver2;
    driver2.parse("domain.pddl");
    Domain* driverGeneratedDomain = driver2.domain;
    PDDLDomain generatedDomain = PDDLConverter::Convert(driverDomain);
    REQUIRE(generatedDomain.requirements.size() == domain.requirements.size());
    REQUIRE(generatedDomain.predicates.size() == domain.predicates.size());
    REQUIRE(generatedDomain.actions.size() == domain.actions.size());
}

TEST_CASE(TAG + "PDDLProblemGenerator") {
    PDDLDriver driver;
    driver.parse(domainFile);
    driver.parse(problemFile);
    Domain* driverDomain = driver.domain;
    PDDLDomain domain = PDDLConverter::Convert(driverDomain);
    Problem* driverProblem = driver.problem;
    PDDLProblem problem = PDDLConverter::Convert(&domain, driverProblem);
    PDDLProblemCodeGenerator PDDLProblemGen = PDDLProblemCodeGenerator(&domain, &problem);
    string problemString = PDDLProblemGen.GenerateProblemString();

    ofstream newfile ("problem.pddl", ofstream::out | ofstream::trunc);
    newfile << problemString;
    newfile.close();

    PDDLDriver driver2;
    driver2.parse("problem.pddl");
    Problem* driverGeneratedProblem = driver2.problem;
    PDDLProblem generatedProblem = PDDLConverter::Convert(&domain, driverGeneratedProblem);
    REQUIRE(generatedProblem.name == problem.name);
    //REQUIRE(generatedProblem->_domain == problem->_domain);
    REQUIRE(generatedProblem.objects.size() == problem.objects.size());
    REQUIRE(generatedProblem.initState.unaryFacts.size() == problem.initState.unaryFacts.size());
    REQUIRE(generatedProblem.initState.multiFacts.size() == problem.initState.multiFacts.size());
    REQUIRE(generatedProblem.goalState.unaryFacts.size() == problem.goalState.unaryFacts.size());
    REQUIRE(generatedProblem.goalState.multiFacts.size() == problem.goalState.multiFacts.size());
    for (auto itr = generatedProblem.initState.unaryFacts.begin(); itr != generatedProblem.initState.unaryFacts.end(); itr++)
        REQUIRE((*itr).second.size() == problem.initState.unaryFacts.at((*itr).first).size());
    for (auto itr = generatedProblem.initState.multiFacts.begin(); itr != generatedProblem.initState.multiFacts.end(); itr++)
        REQUIRE((*itr).second.size() == problem.initState.multiFacts.at((*itr).first).size());
    for (auto itr = generatedProblem.goalState.unaryFacts.begin(); itr != generatedProblem.goalState.unaryFacts.end(); itr++)
        REQUIRE((*itr).second.size() == problem.goalState.unaryFacts.at((*itr).first).size());
    for (auto itr = generatedProblem.goalState.multiFacts.begin(); itr != generatedProblem.goalState.multiFacts.end(); itr++)
        REQUIRE((*itr).second.size() == problem.goalState.multiFacts.at((*itr).first).size());
}

