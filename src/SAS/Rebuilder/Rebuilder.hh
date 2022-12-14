#ifndef SAS_REBUILDER_HH
#define SAS_REBUILDER_HH

#include <unordered_set>
#include <string>

#include "../../PDDL/Instance.hh"
#include "../Plan.hh"
#include "../Macros/Macro.hh"
#include "../Helpers/StringHelper.hh"

namespace SAS {
	class Rebuilder {
	public:
		int TotalMacrosUsed() { return totalMacrosUsed; }
		int UniqueMacrosUsed() { return uniqueMacrosUsed.size(); }

		Rebuilder(PDDL::Instance* instance, std::vector<Macros::Macro>* macros) : instance(instance), macros(macros) {};

		Plan RebuildSASPlan(Plan* reformulatedSAS);
	private:
		void FindMatchingMacro(std::vector<Action>* actions, std::string fromActionName);
		const std::vector<Macros::Macro>* macros;
		const PDDL::Instance* instance;
		int totalMacrosUsed = 0;
		std::unordered_set<std::string> uniqueMacrosUsed;
	};
}

#endif
