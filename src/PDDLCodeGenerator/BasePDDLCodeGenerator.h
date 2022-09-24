#ifndef Base_PDDLCodeGenerator_H
#define Base_PDDLCodeGenerator_H

#include "../PDDLParser/pddldriver.hh"
#include <fstream>

using namespace std;

class BasePDDLCodeGenerator {
public:
	string GetPredicate(Predicate* predicate);
	string GetStringList(StringList* list);
	string GetTabs(int count);
};

#endif