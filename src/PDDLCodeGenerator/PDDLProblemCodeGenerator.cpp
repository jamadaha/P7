#include "PDDLProblemCodeGenerator.h"

using namespace std;

void PDDLProblemCodeGenerator::GenerateProblemFile(Problem* problem, string problemFile) {
	ofstream file;
	file.open(problemFile);
	file << GenerateProblemString(problem);
	file.close();
}

string PDDLProblemCodeGenerator::GenerateProblemString(Problem* problem) {
	string out = "(define (problem " + problem->_name + ")\n";
	out += GetTabs(1) + "(:domain " + problem->_domain + ")\n";
	out += "\n";
	out += GetObjects(problem->_objects) + "\n";
	out += "\n";
	out += GetInits(problem->_init) + "\n";
	out += "\n";
	out += GetGoals(problem->_goal) + "\n";
	out += "\n";
	out += ")\n";
	return out;
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