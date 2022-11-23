#include "Rebuilder.hh"

using namespace std;
using namespace SAS;

SASPlan SASRebuilder::RebuildSASPlan(PDDLInstance* instance, SASPlan* reformulatedSAS, vector<Macro>* macros) {
	vector<SASAction> actions;

	totalMacrosUsed = 0;
	uniqueMacrosUsed.clear();

	for (int i = 0; i < reformulatedSAS->actions.size(); i++) {
		auto sasAction = reformulatedSAS->actions.at(i);
		if (sasAction.name.starts_with("macro")) {
			for (auto macro = macros->begin(); macro != macros->end(); macro++) {
				auto tempActionName = StringHelper::ToUpper(sasAction.name);
				auto tempMacroName = StringHelper::ToUpper(macro->name);
				if (tempActionName == tempMacroName) {
					totalMacrosUsed++;
					uniqueMacrosUsed.emplace(tempActionName);
					for (auto macroAction : macro->path) {
						vector<string> args; args.reserve(macroAction.objects.size());
						for (auto object : macroAction.objects)
							args.push_back(instance->problem->objects.at(object));
						actions.push_back(SASAction(macroAction.action->name, args));
					}
					break;
				}
			}
		}
		else {
			actions.push_back(sasAction);
		}
	}
	SASPlan newPlan = SASPlan(actions, actions.size(), totalMacrosUsed);
	return newPlan;
}
