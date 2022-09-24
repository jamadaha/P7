#include "BasePDDLCodeGenerator.h"

using namespace std;

string BasePDDLCodeGenerator::GetPredicate(Predicate* predicate) {
	return " (" + predicate->_name + GetArguments(predicate->_args) + ")";
}

string BasePDDLCodeGenerator::GetArguments(StringList* list) {
	string retStr = "";
	for (string i : *(list)) {
		retStr += " " + i;
	}
	return retStr;
}