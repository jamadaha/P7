#include "MacroVerifyer.hh"

using namespace std;

vector<BadMacro> MacroVerifyer::VerifyMacros(vector<Macro>* macros, PDDLDomain* domain) {
	vector<BadMacro> badMacros;
	for (auto macro = macros->begin(); macro != macros->end(); macro++) {
		auto path = macro->path;
		// Check params
		unordered_set<unsigned int> expectedParameters;
		for (auto action : path)
			for (auto object : action.objects)
				expectedParameters.emplace(object);

		if (macro->groundedAction.parameters != expectedParameters) {
			badMacros.push_back(BadMacro(*macro, "Parameters did now match expected parameters!"));
		}

		// Check preconditions and effects indexes
		std::unordered_set<unsigned int> expectedPreconditions;
		std::unordered_set<unsigned int> expectedEffects;
		for (auto action : path) {
			for (auto precon : action.action->effects) {
				if (!domain->staticPredicates.contains(precon.predicateIndex))
					expectedPreconditions.emplace(precon.predicateIndex);
			}
			for (auto precon : action.action->preconditions)
				if (!domain->staticPredicates.contains(precon.predicateIndex))
					if (!expectedEffects.contains(precon.predicateIndex))
						expectedPreconditions.emplace(precon.predicateIndex);
		}
		std::unordered_set<unsigned int> actualPreconditions;
		for (auto precons : macro->groundedAction.preconditions)
			actualPreconditions.emplace(precons.first.predicate);

		if (actualPreconditions != expectedPreconditions) {
			badMacros.push_back(BadMacro(*macro, "Preconditions did now match expected preconditions!"));
		}

		std::unordered_set<unsigned int> actualEffects;
		for (auto precons : macro->groundedAction.preconditions)
			actualEffects.emplace(precons.first.predicate);

		if (actualEffects != expectedEffects) {
			badMacros.push_back(BadMacro(*macro, "Effects did now match expected effects!"));
		}

	}
	return badMacros;
}