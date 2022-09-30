#ifndef PDDLCodeGenerator_Domain_H
#define PDDLCodeGenerator_Domain_H

#include "../PDDLParser/pddldriver.hh"
#include "BasePDDLCodeGenerator.h"
#include <fstream>

using namespace std;

class PDDLDomainCodeGenerator : public BasePDDLCodeGenerator {
public:
	void GenerateDomainFile(Domain* domain, string domainFile);
	string GenerateDomainString(Domain* domain);

private:
	string GetRequirements(StringList* requirements);
	string GetPredicates(PredicateList* predicates);
	string GetActions(ActionList* actions);
	string GetAction(Action* action);
	string GetPrecondition(Literal* predicate);
	string GetLiteralChain(const vector<pair<Predicate*, bool>*>* effects);
};

#endif