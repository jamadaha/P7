#include <iostream>
#include <memory>
#include <unordered_set>
#include "PDDLParser/pddldriver.hh"
#include "SASParser/SASParser.h"
#include "PDDLCodeGenerator/PDDLCodeGenerator.h"
#include "Config/config.h"
#include "SASCodeGenerator/SASCodeGenerator.h"
#include "FileVerifier/FileVerifier.h"
#include "CommonInterface/CommonInterface.h"
#include "Reformulators/SameOutputReformulator.h"
#include "Heuristics/BaseHeuristics.hh"
#include "Heuristics/RandomHeuristic.hh"

#include "Report.hh"

using namespace std;

int main(int argc, char** argv)
{   
    PDDLDriver driver;
    driver.parse("./TestFiles/gripper.pddl");
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    auto acts = domain->actions;
    unordered_set<string> args;
	vector<string> argString;

    for (auto a : acts)
        for (auto arg : a.parameters)
            args.insert(arg.name);

	for (string a : args)
		argString.push_back(a);

	for (auto a : argString)
		cout << a << endl;
	/*
	PDDLDriver driver;
    driver.parse("./TestFiles/gripper.pddl");
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    auto preds = domain->predicates;
    vector<string> predStrings;

    for (auto p : preds)
        predStrings.push_back(p.name);
	for (string s : predStrings)
		cout << s << endl;
	/*
	Config config;
	// Do first as it quits on help
	if (config.parseArgs(&config, argc, argv))
		return 0;

	Report report = Report();

	cout << "Running reformulator..." << endl;	
	std::shared_ptr<BaseReformulator> reformulator = std::make_shared<SameOutputReformulator>();
	CommonInterface interface = CommonInterface(config, reformulator);
	auto result = interface.Run(&report);
	cout << "Done!" << endl;

	//FileVerifier verifier;
	//cout << "Verifying PDDL files..." << endl;
	//if (!verifier.VerifyFiles("Data/gripper.pddl", "Data/newDomain.pddl"))
	//	throw invalid_argument("Files not the same!");
	//if (!verifier.VerifyFiles("Data/gripper-4.pddl", "Data/newProblem.pddl"))
	//	throw invalid_argument("Files not the same!");
	//cout << "Done!" << endl;

	//cout << "Verifying SAS file..." << endl;
	//if (!verifier.VerifyFiles("Data/test_sas_plan", "Data/new_sas_plan"))
	//	throw invalid_argument("Files not the same!");
	//cout << "Done!" << endl;

	if (result == CommonInterface::RunResult::RanWithoutErrors)
		report.Print();
	return 0;
	*/
}
