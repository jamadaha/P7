#ifndef SAS_REBUILDER_HH
#define SAS_REBUILDER_HH

#include <unordered_set>
#include <string>

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "../Plan.hh"
#include "../MacroGenerator/Macro.hh"
#include "../Helpers/StringHelper.hh"

namespace SAS {
	class Rebuilder {
	public:
		int TotalMacrosUsed() { return totalMacrosUsed; }
		int UniqueMacrosUsed() { return uniqueMacrosUsed.size(); }

		Rebuilder(PDDLInstance* instance, std::vector<Macro>* macros) : instance(instance), macros(macros) {};

		Plan RebuildSASPlan(Plan* reformulatedSAS);
	private:
		void FindMatchingMacro(std::vector<Action>* actions, std::string fromActionName);
		const std::vector<Macro>* macros;
		const PDDLInstance* instance;
		int totalMacrosUsed = 0;
		std::unordered_set<std::string> uniqueMacrosUsed;
	};
}

#endif
