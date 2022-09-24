#include "PDDLProblemCodeGenerator.h"

using namespace std;

void PDDLProblemCodeGenerator::GenerateProblemFile(Problem* problem, string problemFile) {
	ofstream file;
	file.open(problemFile);
	file << "(define (problem " + problem->_name + ")\n";
	file << GetTabs(1) + "(:domain " + problem->_domain + ")\n";
	file << "\n";
	file << GetObjects(problem->_objects) + "\n";
	file << "\n";
	file << GetInits(problem->_init) + "\n";
	file << "\n";
	file << GetGoals(problem->_goal) + "\n";
	file << "\n";
	file << ")\n";
	file.close();
}

string PDDLProblemCodeGenerator::GetObjects(StringList* objects) {
	string retStr = GetTabs(1) + "(:objects\n";
	retStr += GetTabs(2);
	for (string i : *(objects)) {
		retStr += " " + i;
	}
	retStr += "\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}

string PDDLProblemCodeGenerator::GetInits(LiteralList* literals) {
	string retStr = GetTabs(1) + "(:init\n";
	retStr += GetTabs(2);
	for (auto i : *(literals)) {
		retStr += GetPredicate(i->first);
	}
	retStr += "\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}

string PDDLProblemCodeGenerator::GetGoals(LiteralList* literals) {
	string retStr = GetTabs(1) + "(:goal\n";
	retStr += GetTabs(2) + "(and \n";
	retStr += GetTabs(3);
	for (auto i : *(literals)) {
		retStr += GetPredicate(i->first);
	}
	retStr += "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}