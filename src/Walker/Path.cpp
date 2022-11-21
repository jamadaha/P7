#include "Path.hh"

using namespace std;

string Path::ToString() {
	string retStr = "";
	for (auto step : steps) {
		retStr += "(" + step.action->name + ", [";
		for (auto object : step.objects)
			retStr += to_string(object) + ", ";
		retStr = retStr.substr(0, retStr.length() - 2);
		retStr += "]) => ";
	}
	retStr = retStr.substr(0, retStr.length() - 4);

	return retStr;
}

string Path::ToString(const PDDLProblem *problem) {
	string retStr = "";
	for (auto step : steps) {
		retStr += "(" + step.action->name + ", [";
		for (auto object : step.objects)
			retStr += problem->objects.at(object) + ", ";
		retStr = retStr.substr(0, retStr.length() - 2);
		retStr += "]) => ";
	}
	retStr = retStr.substr(0, retStr.length() - 4);

	return retStr;
}
