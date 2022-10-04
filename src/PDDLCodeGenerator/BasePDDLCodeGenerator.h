#ifndef Base_PDDLCodeGenerator_H
#define Base_PDDLCodeGenerator_H

#include "../PDDLTypes/PDDLInstance.hpp"
#include <fstream>

using namespace std;

class BasePDDLCodeGenerator {
public:
	string GetPredicate(PDDLPredicate predicate);
	string GetStringList(vector<string> list);
	string GetTabs(int count);
	string GetPDDLArgs(vector<PDDLArg> args);
	string GetPDDLArg(PDDLArg arg);
	string GetLiteral(PDDLLiteral predicate);
};

#endif