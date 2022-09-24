#include "PDDLDomainCodeGenerator.h"

using namespace std;

void PDDLDomainCodeGenerator::GenerateDomainFile(Domain* domain, string domainFile) {
	ofstream file;
	file.open(domainFile);
	file << "(define (domain " + domain->_name + ")" << endl;
	file << GetRequirements(domain->_requirements) << endl;
	file << endl;
	file << GetPredicates(domain->_predicates) << endl;
	file << endl;
	file << GetActions(domain->_actions) << endl;
	file << endl;
	file << "\n)" << endl;
	file.close();
}

string PDDLDomainCodeGenerator::GetRequirements(StringList* requirements) {
	string retStr = "";
	retStr += "\t(:requirements\n\t\t";
	for (string i : *(requirements)) {
		retStr += " " + i;
	}
	retStr += ")\n";
	return retStr;
}

string PDDLDomainCodeGenerator::GetPredicates(PredicateList* predicates) {
	string retStr = "";
	retStr += "\t(:predicates\n\t\t";
	for (Predicate* i : *(predicates)) {
		retStr += GetPredicate(i);
	}
	retStr += "\n\t)";
	return retStr;
}

string PDDLDomainCodeGenerator::GetPredicate(Predicate* predicate) {
	return " (" + predicate->_name + GetArguments(predicate->_args) + ")";
}

string PDDLDomainCodeGenerator::GetArguments(StringList* list) {
	string retStr = "";
	for (string i : *(list)) {
		retStr += " " + i;
	}
	return retStr;
}

string PDDLDomainCodeGenerator::GetActions(ActionList* actions) {
	string retStr = "";
	for (Action* i : *(actions)) {
		retStr += GetAction(i) + "\n";
	}
	return retStr;
}

string PDDLDomainCodeGenerator::GetAction(Action* action) {
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

string PDDLDomainCodeGenerator::GetPrecondition(Literal* predicate) {
	if (predicate->second) {
		return "(not " + GetPredicate(predicate->first) + ")";
	}
	else
	{
		return GetPredicate(predicate->first);
	}
}

string PDDLDomainCodeGenerator::GetLiteralChain(const vector<pair<Predicate*, bool>*>* chain) {
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