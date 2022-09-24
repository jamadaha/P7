#ifndef PDDLCodeGenerator_Domain_H
#define PDDLCodeGenerator_Domain_H

#include "../PDDLParser/pddldriver.hh"
#include <fstream>

using namespace std;

class PDDLDomainCodeGenerator {
public:
	void GenerateDomainFile(Domain* domain, string domainFile);

private:
	string GetRequirements(StringList* requirements);
	string GetPredicates(PredicateList* predicates);
	string GetPredicate(Predicate* predicate);
	string GetArguments(StringList* list);
	string GetActions(ActionList* actions);
	string GetAction(Action* action);
	string GetPrecondition(Literal* predicate);
	string GetLiteralChain(const vector<pair<Predicate*, bool>*>* effects);
};

#endif