#include "PDDLCodeGenerator.h"

using namespace std;

void PDDLCodeGenerator::GenerateCode(PDDLDriver driver, string domainFile, string problemFile) {
	GenerateDomainFile(driver.domain, domainFile);
	GenerateProblemFile(driver.problem, problemFile);
}

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
	for (StringList::iterator t = domain->_requirements->begin(); t != domain->_requirements->end(); ++t)
		retStr += " " + * t;
	retStr += "\n\t)";
	return retStr;
}

string PDDLCodeGenerator::GetPredicates(Domain* domain) {
	string retStr = "";
	retStr += "\t(:predicates\n";
	for (PredicateList::iterator t = domain->_predicates->begin(); t != domain->_predicates->end(); ++t) {
		retStr += " (" + (*t)->_name + GetArguments((*t)->_args) + ")";
	}
	retStr += "\n\t)";
	return retStr;
}

string PDDLCodeGenerator::GetArguments(StringList* list) {
	string retStr = "";
	for (StringList::iterator t = list->begin(); t != list->end(); ++t) {
		retStr += " " + (*t);
	}
	return retStr;
}

void PDDLCodeGenerator::GenerateProblemFile(Problem* problem, string problemFile) {
	ofstream file;
	file.open(problemFile);
	file << "(define (problem " + problem->_name + ")" << endl;
	file << ")" << endl;
	file.close();
}