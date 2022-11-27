#include "MacroVerifyer.hh"

using namespace std;

vector<BadMacro> MacroVerifyer::VerifyMacros(vector<Macro>* macros, PDDL::Domain* domain) {
	vector<BadMacro> badMacros;

	for (int i = 0; i < macros->size(); i++) {
		const auto macro = &macros->at(i);
		vector<PDDL::ActionInstance> path = macro->path;
		// Check params
		unordered_set<unsigned int> expectedParameters;
		for (auto action : path)
			for (auto object : action.objects)
				expectedParameters.emplace(object);

		if (macro->groundedAction.parameters != expectedParameters) {
			badMacros.push_back(BadMacro(*macro, "Parameters did now match expected parameters!"));
		}

		// Check preconditions and effects indexes
		// To simply comparisons, we simply make a set of vectors, where the first element in the vector
		// corresponds to the predicate index, and the following elements are the object indexes
		unordered_set<vector<unsigned int>> expectedPreconditions;
		unordered_set<vector<unsigned int>> expectedEffects;
		for (auto action : path) {
			for (auto precon : action.action->preconditions) {
				if (!domain->staticPredicates.contains(precon.predicateIndex)) {
					vector<unsigned int> newSet = EncodePredicateActionRef(precon.predicateIndex, precon.args, action.objects);
					if (!expectedEffects.contains(newSet))
						expectedPreconditions.emplace(newSet);
				}
			}
			for (auto precon : action.action->effects)
				if (!domain->staticPredicates.contains(precon.predicateIndex))
					expectedEffects.emplace(EncodePredicateActionRef(precon.predicateIndex, precon.args, action.objects));
		}

		unordered_set<vector<unsigned int>> actualPreconditions;
		for (auto precon : macro->groundedAction.preconditions)
			actualPreconditions.emplace(EncodePredicate(precon.first.predicate, precon.first.objects));

		unordered_set<vector<unsigned int>> actualEffects;
		for (auto precon : macro->groundedAction.effects)
			actualEffects.emplace(EncodePredicate(precon.first.predicate, precon.first.objects));

		if (actualPreconditions != expectedPreconditions)
			badMacros.push_back(BadMacro(*macro, "Preconditions did now match expected preconditions!"));

		if (actualEffects != expectedEffects)
			badMacros.push_back(BadMacro(*macro, "Effects did now match expected effects!"));
	}
	return badMacros;
}

vector<unsigned int> MacroVerifyer::EncodePredicate(unsigned int predicateIndex, vector<unsigned int> objectIndexes) {
	vector<unsigned int> newSet;
	newSet.push_back(predicateIndex);
	for (auto i : objectIndexes)
		newSet.push_back(i);
	return newSet;
}

vector<unsigned int> MacroVerifyer::EncodePredicateActionRef(unsigned int predicateIndex, vector<unsigned int> paramIndexes, vector<unsigned int> objectIndexes) {
	vector<unsigned int> newSet;
	newSet.push_back(predicateIndex);
	for (auto i : paramIndexes)
		newSet.push_back(objectIndexes.at(i));
	return newSet;
}