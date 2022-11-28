#ifndef Base_PDDLCodeGenerator_HH
#define Base_PDDLCodeGenerator_HH

#include <fstream>
#include <string>

#include "../Instance.hh"

namespace PDDL {
	class BaseCodeGenerator {
	public:
		BaseCodeGenerator(const Domain* domain) : domain(domain) {};
		std::string GetPredicate(Predicate predicate);
		std::string GetStringList(std::vector<std::string> list);
		std::string GetTabs(int count);
		std::string GetLiteral(Action action, Literal predicate);
	protected:
		const Domain* domain;
	};
}

#endif