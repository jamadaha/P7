#ifndef SAS_REBUILDER_HH
#define SAS_REBUILDER_HH

#include <unordered_set>
#include <string>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../SASParser/SASParser.hh"
#include "../MacroGenerator/Macro.hh"

class SASRebuilder {
public:
	int TotalMacrosUsed() { return totalMacrosUsed; }
	int UniqueMacrosUsed() { return uniqueMacrosUsed.size(); }

	SASPlan RebuildSASPlan(PDDLInstance* instance, SASPlan* reformulatedSAS, std::vector<Macro>* macros);
private:
	int totalMacrosUsed = 0;
	std::unordered_set<std::string> uniqueMacrosUsed;
};

#endif
