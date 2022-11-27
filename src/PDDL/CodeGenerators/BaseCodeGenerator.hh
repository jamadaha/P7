#ifndef Base_PDDLCodeGenerator_HH
#define Base_PDDLCodeGenerator_HH

#include <fstream>
#include <string>

#include "../IntermediatePDDL/PDDLInstance.hh"

class BasePDDLCodeGenerator {
public:
	BasePDDLCodeGenerator(const PDDLDomain *domain) : domain(domain) {};
	std::string GetPredicate(PDDLPredicate predicate);
	std::string GetStringList(std::vector<std::string> list);
	std::string GetTabs(int count);
	std::string GetLiteral(PDDLAction action, PDDLLiteral predicate);
protected:
	const PDDLDomain *domain;
};

#endif