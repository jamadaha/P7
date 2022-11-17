#include "WalkerPathVerifyer.hh"

using namespace std;

vector<BadPath> WalkerPathVerifyer::VerifyPaths(vector<Path>* paths, PDDLInstance* instance) {
	vector<BadPath> badPaths;

	for (auto path = paths->begin(); path != paths->end(); path++) {
		vector<PDDLAction> newActions = instance->domain->actions;

		if (path->states.at(0) != instance->problem->initState) {

		}

		vector<SASAction> actions;
		for (auto step : path->steps) {
			actions.push_back(GenerateSASActionFromActionInstance(step, instance));
		}

		if (path->states.at(path->states.size()) != instance->problem->goalState) {
			vector<string> params;
			vector<PDDLLiteral> preconditions;
			vector<PDDLLiteral> effects;
			int paramIndex = 0;

			for (auto precon : path->states.at(path->states.size()).unaryFacts) {
				vector<unsigned int> args;
				for (auto param : precon.second) {
					params.push_back(to_string(paramIndex) + "?");
					args.push_back(paramIndex++);
				}

				preconditions.push_back(PDDLLiteral(precon.first, args, true));
			}

			PDDLAction finalAction("macro-final", params, preconditions, effects);
			newActions.push_back(finalAction);
			vector<unsigned int> objects;

			PDDLActionInstance finalActionInstance(&finalAction, objects);
			actions.push_back(GenerateSASActionFromActionInstance(finalActionInstance, instance));
		}

		PDDLInstance newInstance(new PDDLDomain(instance->domain->name, instance->domain->requirements, instance->domain->predicates, instance->domain->predicateMap, newActions), instance->problem);

		SASPlan checkPlan(actions, 1, 1);

	}

	return badPaths;
}

SASAction WalkerPathVerifyer::GenerateSASActionFromActionInstance(PDDLActionInstance action, PDDLInstance *instance) {
	vector<string> params;
	for (auto param : action.objects)
		params.push_back(instance->problem->objects.at(param));
	return SASAction(action.action->name, params);
}