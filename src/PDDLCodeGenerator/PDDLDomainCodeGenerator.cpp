#include "PDDLDomainCodeGenerator.h"

using namespace std;

void PDDLDomainCodeGenerator::GenerateDomainFile(Domain* domain, string domainFile) {
	ofstream file;
	file.open(domainFile);
	file << "(define (domain " + domain->_name + ")\n";
	file << GetRequirements(domain->_requirements) + "\n";
	file << "\n";
	file << GetPredicates(domain->_predicates) + "\n";
	file << "\n";
	file << GetActions(domain->_actions) + "\n";
	file << "\n";
	file << "\n)\n";
	file.close();
}

string PDDLDomainCodeGenerator::GetRequirements(StringList* requirements) {
	string retStr = "";
	retStr += GetTabs(1) + "(:requirements\n";
	retStr += GetTabs(2);
	for (string i : *(requirements)) {
		retStr += " " + i;
	}
	retStr += "\n" + GetTabs(1) + ")";
	return retStr;
}

string PDDLDomainCodeGenerator::GetPredicates(PredicateList* predicates) {
	string retStr = "";
	retStr += GetTabs(1) + "(:predicates\n";
	retStr += GetTabs(2);
	for (Predicate* i : *(predicates)) {
		retStr += GetPredicate(i);
	}
	retStr += "\n" + GetTabs(1) + ")";
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
	string retStr = GetTabs(1) + "(:action " + action->_name + "\n";
	retStr += GetTabs(2) + ":parameters (\n";
	retStr += GetTabs(3);
	for (string i : *(action->_params)) {
		retStr += " " + i;
	}
	retStr += "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(2) + ":precondition (\n";
	retStr += GetTabs(3) + GetLiteralChain(action->_precond) + "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(2) + ":effect (\n";
	retStr += GetTabs(3) + GetLiteralChain(action->_effects) + "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(1) + ")\n";
	return retStr;
}

string PDDLDomainCodeGenerator::GetPrecondition(Literal* predicate) {
	if (!predicate->second) {
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
		retStr = "and ";
		for (auto i : *(chain))
			retStr += GetPrecondition(i) + " ";
	}
	else
	{
		for (auto i : *(chain))
			retStr = GetPrecondition(i);
	}
	return retStr;
}