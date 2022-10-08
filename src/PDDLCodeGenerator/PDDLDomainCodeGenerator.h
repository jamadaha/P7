#ifndef PDDLCodeGenerator_Domain_H
#define PDDLCodeGenerator_Domain_H

#include "../PDDLTypes/PDDLDomain.hpp"
#include "BasePDDLCodeGenerator.h"
#include <fstream>

using namespace std;

class PDDLDomainCodeGenerator : public BasePDDLCodeGenerator {
public:
	void GenerateDomainFile(PDDLDomain* domain, string domainFile);
	string GenerateDomainString(PDDLDomain* domain);

private:
	string GetRequirements(vector<std::string> requirements);
	string GetPredicates(vector<PDDLPredicate> predicates);
	string GetActions(vector<PDDLAction> actions);
	string GetAction(PDDLAction action);
};

#endif