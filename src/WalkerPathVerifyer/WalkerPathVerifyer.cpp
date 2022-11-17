#include "WalkerPathVerifyer.hh"

using namespace std;

vector<BadPath> WalkerPathVerifyer::VerifyPaths(vector<Path>* paths, PDDLInstance* instance, Config* config) {
	vector<BadPath> badPaths;

	for (auto path = paths->begin(); path != paths->end(); path++) {
		vector<SASAction> actions;
		for (auto step : path->steps) {
			actions.push_back(GenerateSASActionFromActionInstance(step, instance));
		}
		SASPlan checkPlan(actions, actions.size(), 0);

		SASCodeGenerator sasGenerator;
		sasGenerator.GenerateCode(checkPlan, "sas_verify.sas");

		PDDLInstance newInstance(
			instance->domain,
			new PDDLProblem(instance->problem->name, instance->domain, instance->problem->objects, instance->problem->objectMap, path->startState, path->endState));

		PDDLDomainCodeGenerator domainGenerator(newInstance.domain);
		PDDLProblemCodeGenerator problemGenerator(newInstance.domain, newInstance.problem);
		PDDLCodeGenerator generator(domainGenerator, problemGenerator);

		generator.GenerateCode(newInstance, "domain_verify.pddl", "problem_verify.pddl");

		auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(*config, "domain_verify.pddl", "problem_verify.pddl", "sas_verify.sas");
		if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
			//badPaths.push_back(BadPath(*path, "Reason"));
		}
	}

	return badPaths;
}

SASAction WalkerPathVerifyer::GenerateSASActionFromActionInstance(PDDLActionInstance action, PDDLInstance *instance) {
	vector<string> params;
	for (auto param : action.objects)
		params.push_back(instance->problem->objects.at(param));
	return SASAction(action.action->name, params);
}