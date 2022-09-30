#include "SASCodeGenerator.h"

using namespace std;

void SASCodeGenerator::GenerateCode(SASPlan plan, string targetFile) {
	ofstream file;
	file.open(targetFile);
	for (SASAction action : plan.actions)
		file << GetAction(action) + "\n";
	file << "; cost = " << plan.cost << " (general cost)\n";
	file.close();
}

string SASCodeGenerator::GetAction(SASAction action) {
	string retStr = "";
	retStr += "(" + action.name + GetParameters(action.parameters) + ")";
	return retStr;
}

string SASCodeGenerator::GetParameters(vector<string> parameters) {
	string retStr = "";
	for (string str : parameters)
		retStr += " " + str;
	return retStr;
}
