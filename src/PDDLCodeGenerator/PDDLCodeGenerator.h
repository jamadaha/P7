#ifndef PDDLCodeGenerator_H
#define PDDLCodeGenerator_H

#include "../PDDLParser/pddldriver.hh"
#include <fstream>

using namespace std;

class PDDLCodeGenerator {
public:
	void GenerateCode(PDDLDriver driver, string domainFile, string problemFile);

private:
	void GenerateDomainFile(Domain* domain, string domainFile);
	string GetRequirements(Domain* domain);
	string GetPredicates(Domain* domain);
	string GetPredicate(Predicate* predicate);
	string GetArguments(StringList* list);
	string GetActions(Domain* domain);
	string GetAction(Action* action);
	string GetPreconditions(const PreconditionList* list);
	string GetPrecondition(Literal* predicate);
	string GetEffects(const EffectList* effects);
	string GetLiteralChain(const vector<pair<Predicate*, bool>*>* effects);

	void GenerateProblemFile(Problem* problem, string problemFile);
};

#endif