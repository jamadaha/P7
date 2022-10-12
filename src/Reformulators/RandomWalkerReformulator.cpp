#include "RandomWalkerReformulator.hh"

using namespace std;

// Move this to config?
// Or generate it based on something?
#define RUN_COUNT 10


PDDLInstance RandomWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	RandomHeuristic<PDDLActionInstance>* heu = new RandomHeuristic<PDDLActionInstance>(PDDLContext(instance->domain, instance->problem));
	std::vector<Path> paths;
	for (int i = 0; i < RUN_COUNT; i++) {
		Walker walker = Walker(instance,
		ActionGenerator(instance->domain),
		heu,
		new ObjectActionDepthFunction(*instance));
		Path path = walker.Walk();
		paths.push_back(path);
	}
	

	// Do Something and transform the input PDDL into a new PDDL format
	PDDLInstance newInstance(instance->domain, instance->problem);

	return newInstance;
}

SASPlan RandomWalkerReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
}