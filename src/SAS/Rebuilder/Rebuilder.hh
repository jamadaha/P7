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

		Plan RebuildSASPlan(PDDLInstance* instance, Plan* reformulatedSAS, std::vector<Macro>* macros);
	private:
		int totalMacrosUsed = 0;
		std::unordered_set<std::string> uniqueMacrosUsed;
	};
}

#endif
