#include "RandomWalkerReformulator.hh"

using namespace std;

PDDLInstance RandomWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {

	// Walk (Temp)
	RandomHeuristic<PDDLActionInstance>* heu = new RandomHeuristic<PDDLActionInstance>(PDDLContext(instance->domain, instance->problem));
	Walker walker = Walker(instance,
		ActionGenerator(instance->domain),
		heu,
		new ConstantDepthFunction(1, *instance));
	walker.Walk();

	// Do Something and transform the input PDDL into a new PDDL format
	PDDLInstance newInstance(instance->domain, instance->problem);

	return newInstance;
}

SASPlan RandomWalkerReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
}