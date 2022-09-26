#include "BaseReformulator.h"

PDDLDocument BaseReformulator::ReformulatePDDL(PDDLDocument* inputPDDL) {
	cout << "Note, this reformulator is only for testing! Simply gives the same result back." << endl;
	// Do Something and transform the input PDDL into a new PDDL format
	Domain* domain = new Domain(inputPDDL->domain->_name);
	domain->_requirements = inputPDDL->domain->_requirements;
	domain->_predicates = inputPDDL->domain->_predicates;
	domain->_actions = inputPDDL->domain->_actions;

	Problem* problem = new Problem(inputPDDL->problem->_name, inputPDDL->problem->_domain);
	problem->_objects = inputPDDL->problem->_objects;
	problem->_init = inputPDDL->problem->_init;
	problem->_goal = inputPDDL->problem->_goal;

	PDDLDocument newDocument(domain, problem);

	return newDocument;
}

Plan BaseReformulator::RebuildSASPlan(Plan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	Plan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
}