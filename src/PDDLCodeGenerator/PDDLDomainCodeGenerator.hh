#ifndef PDDLCodeGenerator_Domain_HH
#define PDDLCodeGenerator_Domain_HH

#include <fstream>

#include "../IntermediatePDDL/PDDLDomain.hh"
#include "BasePDDLCodeGenerator.hh"

class PDDLDomainCodeGenerator : public BasePDDLCodeGenerator {
public:
	PDDLDomainCodeGenerator(const PDDLDomain *domain) : BasePDDLCodeGenerator(domain) {};
	void GenerateDomainFile(std::string domainFile);
	std::string GenerateDomainString();

private:
	std::string GetRequirements(std::vector<std::string> requirements);
	std::string GetPredicates(std::vector<PDDLPredicate> predicates);
	std::string GetActions(std::vector<PDDLAction> actions);
	std::string GetAction(PDDLAction action);
};

#endif