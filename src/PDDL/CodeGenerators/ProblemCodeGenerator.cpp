#include "ProblemCodeGenerator.hh"

using namespace std;
using namespace PDDL;
 
void ProblemCodeGenerator::GenerateProblemFile(string problemFile) {
	ofstream file;
	file.open(problemFile);
	file << GenerateProblemString();
	file.close();
}

string ProblemCodeGenerator::GenerateProblemString() {
	string out = "(define (problem " + problem->name + ")\n";
	out += GetTabs(1) + "(:domain " + problem->domain->name + ")\n";
	out += "\n";
	out += GetObjects(problem->objects) + "\n";
	out += "\n";
	out += GetInits(problem->initState) + "\n";
	out += "\n";
	out += GetGoals(problem->goalState) + "\n";
	out += "\n";
	out += ")\n";
	return out;
}

string ProblemCodeGenerator::GetObjects(vector<string> objects) {
	string retStr = GetTabs(1) + "(:objects\n";
	retStr += GetTabs(2) + GetStringList(objects);
	retStr += "\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}

string ProblemCodeGenerator::GetInits(State literals) {
	string retStr = GetTabs(1) + "(:init\n";
	retStr += GetTabs(2);
	retStr += GetFacts(literals);
	retStr += "\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}

string ProblemCodeGenerator::GetGoals(State literals) {
	string retStr = GetTabs(1) + "(:goal\n";
	retStr += GetTabs(2) + "(and \n";
	retStr += GetTabs(3);
	retStr += GetFacts(literals);
	retStr += "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}

std::string ProblemCodeGenerator::GetFacts(State literals) {
	string retStr = "";
	auto AddParen = [](std::string x) {
		return "(" + x + ") ";
	};

	// Unary Facts
	for (auto uItr = literals.unaryFacts.begin(); uItr != literals.unaryFacts.end(); uItr++) {
		for (auto itr = (*uItr).second.begin(); itr != (*uItr).second.end(); itr++) {
			std::string tempString = domain->predicates.at((*uItr).first).name + " " + problem->objects.at(*itr);
			retStr += AddParen(tempString);
		}
	}

	// Binary Facts
	for (auto uItr = literals.binaryFacts.begin(); uItr != literals.binaryFacts.end(); uItr++) {
		for (auto itr = (*uItr).second.begin(); itr != (*uItr).second.end(); itr++) {
			std::string tempString = domain->predicates.at((*uItr).first).name;
			tempString += " " + problem->objects.at((*itr).first);
			tempString += " " + problem->objects.at((*itr).second);
			retStr += AddParen(tempString);
		}
	}

	return retStr;
}