#include "DomainCodeGenerator.hh"

using namespace std;
using namespace PDDL;

void DomainCodeGenerator::GenerateDomainFile(string domainFile) {
	ofstream file;
	file.open(domainFile);
	file << GenerateDomainString();
	file.close();
}

string DomainCodeGenerator::GenerateDomainString() {
	string out = "(define (domain " + domain->name + ")\n";
	out += GetRequirements(domain->requirements) + "\n";
	out += "\n";
	out += GetPredicates(domain->predicates) + "\n";
	out += "\n";
	out += GetActions(domain->actions) + "\n";
	out += "\n";
	out += "\n)\n";
	return out;
}

string DomainCodeGenerator::GetRequirements(vector<std::string> requirements) {
	string retStr = "";
	retStr += GetTabs(1) + "(:requirements\n";
	retStr += GetTabs(2);
	for (auto i : requirements) {
		retStr += " " + i;
	}
	retStr += "\n" + GetTabs(1) + ")";
	return retStr;
}

string DomainCodeGenerator::GetPredicates(vector<Predicate> predicates) {
	string retStr = "";
	retStr += GetTabs(1) + "(:predicates\n";
	retStr += GetTabs(2);
	for (int i = 1; i < predicates.size(); i++)
		retStr += GetPredicate(predicates.at(i)) + " ";
	retStr += "\n" + GetTabs(1) + ")";
	return retStr;
}

string DomainCodeGenerator::GetActions(vector<Action> actions) {
	string retStr = "";
	for (auto i : actions) {
		retStr += GetAction(i) + "\n";
	}
	return retStr;
}

string DomainCodeGenerator::GetAction(Action action) {
	string retStr = GetTabs(1) + "(:action " + action.name + "\n";
	retStr += GetTabs(2) + ":parameters (\n";
	retStr += GetTabs(3);
	for (int i = 0; i < action.parameters.size(); i++) {
		retStr += action.parameters[i] + " ";
	}
	retStr += "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(2) + ":precondition (and\n";
	for (auto i : action.preconditions)
		retStr += GetTabs(3) + GetLiteral(action, i) + "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(2) + ":effect (and\n";
	for (auto i : action.effects)
		retStr += GetTabs(3) + GetLiteral(action, i) + "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(1) + ")\n";
	return retStr;
}