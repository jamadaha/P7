#ifndef SAS_REBUILDER_HH
#define SAS_REBUILDER_HH

#include <unordered_set>
#include <string>

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "../SASPlan.hh"
#include "../MacroGenerator/Macro.hh"

namespace SAS {
	class SASRebuilder {
	public:
		int TotalMacrosUsed() { return totalMacrosUsed; }
		int UniqueMacrosUsed() { return uniqueMacrosUsed.size(); }

		SASPlan RebuildSASPlan(PDDLInstance* instance, SASPlan* reformulatedSAS, std::vector<Macro>* macros);
	private:
		int totalMacrosUsed = 0;
		std::unordered_set<std::string> uniqueMacrosUsed;
	};
}

#endif
