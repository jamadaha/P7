#include "PDDLCodeGenerator.h"

using namespace std;

void PDDLCodeGenerator::GenerateCode(PDDLDriver driver, string domainFile, string problemFile) {
	GenerateDomainFile(driver.domain, domainFile);
	GenerateProblemFile(driver.problem, problemFile);
}

#pragma region Domain File

void PDDLCodeGenerator::GenerateDomainFile(Domain* domain, string domainFile) {
	ofstream file;
	file.open(domainFile);
	file << "(define (domain " + domain->_name + ")" << endl;
	file << GetRequirements(domain) << endl;
	file << endl;
	file << GetPredicates(domain) << endl;
	file << endl;
	file << GetActions(domain) << endl;
	file << endl;
	file << "\n)" << endl;
	file.close();
}

string PDDLCodeGenerator::GetRequirements(Domain* domain) {
	string retStr = "";
	retStr += "\t(:requirements\n\t\t";
	for (string i : *(domain->_requirements)) {
		retStr += " " + i;
	}
	retStr += ")\n";
	return retStr;
}

string PDDLCodeGenerator::GetPredicates(Domain* domain) {
	string retStr = "";
	retStr += "\t(:predicates\n\t\t";
	for (Predicate *i : *(domain->_predicates)) {
		retStr += GetPredicate(i);
	}
	retStr += "\n\t)";
	return retStr;
}

string PDDLCodeGenerator::GetPredicate(Predicate* predicate) {
	return " (" + predicate->_name + GetArguments(predicate->_args) + ")";
}

string PDDLCodeGenerator::GetArguments(StringList* list) {
	string retStr = "";
	for (string i : *(list)) {
		retStr += " " + i;
	}
	return retStr;
}

string PDDLCodeGenerator::GetActions(Domain* domain) {
	string retStr = "";
	for (Action* i : *(domain->_actions)) {
		retStr += GetAction(i) + "\n";
	}
	return retStr;
}

string PDDLCodeGenerator::GetAction(Action* action) {
	string retStr = "(:action " + action->_name + "\n";
	retStr += ":parameters (";
	for (string i : *(action->_params)) {
		retStr += " " + i;
	}
	retStr += ")\n";
	retStr += ":precondition (" + GetLiteralChain(action->_precond) + ")";
	retStr += ")\n";
	retStr += ":effect (" + GetLiteralChain(action->_effects) + ")";
	retStr += ")\n";
	return retStr;
}

string PDDLCodeGenerator::GetPrecondition(Literal* predicate) {
	if (predicate->second) {
		return "(not " + GetPredicate(predicate->first) + ")";
	}
	else
	{
		return GetPredicate(predicate->first);
	}
}

string PDDLCodeGenerator::GetLiteralChain(const vector<pair<Predicate*, bool>*>* chain) {
	string retStr = "";
	if (chain->size() > 1) {
		retStr = "and (\n";
		for (auto i : *(chain))
			retStr += GetPrecondition(i) + " ";
		retStr += ")";
	}
	else
	{
		for (auto i : *(chain))
			retStr = GetPrecondition(i);
	}
	return retStr;
}

#pragma endregion

#pragma region Problem

void PDDLCodeGenerator::GenerateProblemFile(Problem* problem, string problemFile) {
	ofstream file;
	file.open(problemFile);
	file << "(define (problem " + problem->_name + ")" << endl;
	file << ")" << endl;
	file.close();
}

#pragma endregion