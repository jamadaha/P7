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
	file << "\n)" << endl;
	file << GetPredicates(domain) << endl;
	file << "\n)" << endl;
	file.close();
}

string PDDLCodeGenerator::GetRequirements(Domain* domain) {
	string retStr = "";
	retStr += "\t(:requirements";
	for (string i : *(domain->_requirements)) {
		retStr += " " + i;
	}
	retStr += "\n\t)";
	return retStr;
}

string PDDLCodeGenerator::GetPredicates(Domain* domain) {
	string retStr = "";
	retStr += "\t(:predicates\n";
	for (Predicate *i : *(domain->_predicates)) {
		retStr += " (" + i->_name + GetArguments(i->_args) + ")";
	}
	retStr += "\n\t)";
	return retStr;
}

string PDDLCodeGenerator::GetArguments(StringList* list) {
	string retStr = "";
	for (string i : *(list)) {
		retStr += " " + i;
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