#include "CodeGenerator.hh"

using namespace std;
using namespace SAS;

void CodeGenerator::GenerateCode(Plan plan, string targetFile) {
	ofstream file;
	file.open(targetFile);
	file << GenerateCodeString(plan, targetFile);
	file.close();
}

string CodeGenerator::GenerateCodeString(Plan plan, string targetFile) {
	string returnValue = "";
	for (auto const& action : plan.actions)
		returnValue += GetAction(action) + "\n";
	returnValue += "; cost = " + to_string(plan.cost) + " (general cost)\n";
	return returnValue;
}

string CodeGenerator::GetAction(Action action) {
	string retStr = "";
	retStr += "(" + action.name + GetParameters(action.parameters) + ")";
	return retStr;
}

string CodeGenerator::GetParameters(vector<string> parameters) {
	string retStr = "";
	for (string str : parameters)
		retStr += " " + str;
	return retStr;
}
