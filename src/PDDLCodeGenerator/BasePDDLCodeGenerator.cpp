#include "BasePDDLCodeGenerator.h"

using namespace std;

string BasePDDLCodeGenerator::GetPredicate(Predicate* predicate) {
	return " (" + predicate->_name + GetStringList(predicate->_args) + ")";
}

string BasePDDLCodeGenerator::GetStringList(StringList* list) {
	string retStr = "";
	for (string i : *(list)) {
		retStr += " " + i;
	}
	return retStr;
}

string BasePDDLCodeGenerator::GetTabs(int count) {
	string retStr = "";
	for (int i = 0; i < count; i++) {
		retStr += "\t";
	}
	return retStr;
}