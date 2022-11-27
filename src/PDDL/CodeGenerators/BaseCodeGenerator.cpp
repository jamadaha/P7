#include "BasePDDLCodeGenerator.hh"

using namespace std;

string BasePDDLCodeGenerator::GetPredicate(PDDLPredicate predicate) {
	// This is to handle predicate =, which is internally a predicate, but not in PDDL
	if (predicate.arguments.size() == 0)
		return "";
	return "(" + predicate.name + GetStringList(predicate.arguments) + ")";
}

string BasePDDLCodeGenerator::GetStringList(vector<string> list) {
	string retStr = "";
	for (auto i : list) {
		retStr += " " + i;
	}
	return retStr;
}

string BasePDDLCodeGenerator::GetLiteral(PDDLAction action, PDDLLiteral predicate) {
	std::string returnString = "(";
	if (!predicate.value)
		returnString += "not (";
	
	returnString += domain->predicates.at(predicate.predicateIndex).name;

	for (int i = 0; i < predicate.args.size(); i++) {
		returnString += " " + action.parameters.at(predicate.args.at(i));
	}
	if (!predicate.value)
		returnString += ")";
	return returnString + ")";
}

string BasePDDLCodeGenerator::GetTabs(int count) {
	string retStr = "";
	for (int i = 0; i < count; i++) {
		retStr += "\t";
	}
	return retStr;
} 