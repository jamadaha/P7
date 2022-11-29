#include "Rebuilder.hh"

using namespace std;
using namespace SAS;

Plan Rebuilder::RebuildSASPlan(Plan* reformulatedSAS) {
	vector<Action> actions;

	totalMacrosUsed = 0;
	uniqueMacrosUsed.clear();

	for (int i = 0; i < reformulatedSAS->actions.size(); i++) {
		auto sasAction = reformulatedSAS->actions.at(i);
		if (sasAction.name.starts_with("macro")) {
			string fromActionName = StringHelper::ToUpper(sasAction.name);
			FindMatchingMacro(&actions, fromActionName);
		}
		else {
			actions.push_back(sasAction);
		}
	}
	Plan newPlan = Plan(actions, actions.size(), totalMacrosUsed, uniqueMacrosUsed.size());
	return newPlan;
}

void Rebuilder::FindMatchingMacro(vector<Action>* actions, string fromActionName) {
	bool wasFound = false;
	for (auto macro = macros->begin(); macro != macros->end(); macro++) {
		auto tempMacroName = StringHelper::ToUpper(macro->name);
		if (fromActionName == tempMacroName) {
			wasFound = true;
			totalMacrosUsed++;
			uniqueMacrosUsed.emplace(fromActionName);
			for (auto macroAction : macro->path) {
				vector<string> args; args.reserve(macroAction.objects.size());
				for (auto object : macroAction.objects)
					args.push_back(instance->problem->objects.at(object));
				actions->push_back(Action(macroAction.action->name, args));
			}
			break;
		}
	}
	if (!wasFound)
		throw invalid_argument("Error! No matching macro found for " + fromActionName);
}