#include "PDDLProblemCodeGenerator.h"

using namespace std;

void PDDLProblemCodeGenerator::GenerateProblemFile(Problem* problem, string problemFile) {
	ofstream file;
	file.open(problemFile);
	file << "(define (problem " + problem->_name + ")" << endl;
	file << "\t(:domain " + problem->_domain + ")" << endl;
	file << endl;
	file << GetObjects(problem->_objects) << endl;
	file << endl;
	file << GetInits(problem->_init) << endl;
	file << endl;
	file << GetGoals(problem->_goal) << endl;
	file << endl;
	file << ")" << endl;
	file.close();
}

string PDDLProblemCodeGenerator::GetObjects(StringList* objects) {
	string retStr = "(:objects\n";
	for (string i : *(objects)) {
		retStr += " " + i;
	}
	retStr += ")";
	return retStr;
}

string PDDLProblemCodeGenerator::GetInits(LiteralList* literals) {
	string retStr = "(:init\n";
	for (auto i : *(literals)) {
		retStr += GetPredicate(i->first);
	}
	retStr += ")";
	return retStr;
}

string PDDLProblemCodeGenerator::GetGoals(LiteralList* literals) {
	string retStr = "(:goal\n";
	retStr += "(and \n";
	for (auto i : *(literals)) {
		retStr += GetPredicate(i->first);
	}
	retStr += ")";
	retStr += ")";
	return retStr;
}

string PDDLProblemCodeGenerator::GetPredicate(Predicate* predicate) {
	return " (" + predicate->_name + GetArguments(predicate->_args) + ")";
}

string PDDLProblemCodeGenerator::GetArguments(StringList* list) {
	string retStr = "";
	for (string i : *(list)) {
		retStr += " " + i;
	}
	return retStr;
}