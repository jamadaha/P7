#include <catch2/catch_test_macros.hpp>
#include <string>

#include <filesystem>

#include "../../src/PDDL/Instance.hh"
#include "../../src/PDDL/Parsers/ExternalParser.hh"
#include "../../src/PDDL/CodeGenerators/CodeGenerator.hh"
#include "../../src/PDDL/CodeGenerators/DomainCodeGenerator.hh"
#include "../../src/PDDL/CodeGenerators/ProblemCodeGenerator.hh"

using namespace std;

const string TAG = "PDDLCodeGenerator ";
const string resultDomainFile = "./TestFiles/intermediate-domain.pddl";
const string resultProblemFile = "./TestFiles/intermediate-problem.pddl";
const string domainFile = "./TestFiles/gripper.pddl";
const string problemFile = "./TestFiles/gripper-4.pddl";

TEST_CASE(TAG + "PDDLDomainGenerator - Domain") {
    ExternalParser parser;
    PDDL::Instance result = parser.Parse(domainFile, problemFile);
    PDDL::DomainCodeGenerator PDDLDomainGen = PDDL::DomainCodeGenerator(result.domain);
    string domainString = PDDLDomainGen.GenerateDomainString();

    ofstream newfile (resultDomainFile, ofstream::out | ofstream::trunc);
    newfile << domainString;
    newfile.close();

    PDDL::Instance result2 = parser.Parse(resultDomainFile, problemFile);
    REQUIRE(result.domain->requirements.size() == result2.domain->requirements.size());
    REQUIRE(result.domain->predicates.size() == result2.domain->predicates.size());
    REQUIRE(result.domain->actions.size() == result2.domain->actions.size());
}

TEST_CASE(TAG + "PDDLProblemGenerator - Problem") {
    ExternalParser parser;
    PDDL::Instance result = parser.Parse(domainFile, problemFile);
    PDDL::ProblemCodeGenerator PDDLProblemGen = PDDL::ProblemCodeGenerator(result.domain, result.problem);
    string problemString = PDDLProblemGen.GenerateProblemString();

    ofstream newfile (resultProblemFile, ofstream::out | ofstream::trunc);
    newfile << problemString;
    newfile.close();

    PDDL::Instance result2 = parser.Parse(domainFile, resultProblemFile);
    REQUIRE(result.problem->name == result2.problem->name);
    //REQUIRE(generatedProblem->_domain == problem->_domain);
    REQUIRE(result.problem->objects.size() == result2.problem->objects.size());
    REQUIRE(result.problem->initState.unaryFacts.size() == result2.problem->initState.unaryFacts.size());
    REQUIRE(result.problem->goalState.unaryFacts.size() == result2.problem->goalState.unaryFacts.size());
    for (auto itr = result.problem->initState.unaryFacts.begin(); itr != result.problem->initState.unaryFacts.end(); itr++)
        REQUIRE((*itr).second.size() == result2.problem->initState.unaryFacts.at((*itr).first).size());
    for (auto itr = result.problem->goalState.unaryFacts.begin(); itr != result.problem->goalState.unaryFacts.end(); itr++)
        REQUIRE((*itr).second.size() == result2.problem->goalState.unaryFacts.at((*itr).first).size());
}

