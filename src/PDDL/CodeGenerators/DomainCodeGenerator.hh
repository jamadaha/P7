#ifndef PDDLCodeGenerator_Domain_HH
#define PDDLCodeGenerator_Domain_HH

#include <fstream>

#include "../Domain.hh"
#include "BaseCodeGenerator.hh"

namespace PDDL {
	class DomainCodeGenerator : public BaseCodeGenerator {
	public:
		DomainCodeGenerator(const Domain* domain) : BaseCodeGenerator(domain) {};
		void GenerateDomainFile(std::string domainFile);
		std::string GenerateDomainString();

	private:
		std::string GetRequirements(std::vector<std::string> requirements);
		std::string GetPredicates(std::vector<Predicate> predicates);
		std::string GetActions(std::vector<Action> actions);
		std::string GetAction(Action action);
	};
}

#endif