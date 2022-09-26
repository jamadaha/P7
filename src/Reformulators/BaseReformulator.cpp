#include "BaseReformulator.h"

PDDLDriver BaseReformulator::ReformulatePDDL(PDDLDriver inputPDDL) {
	// Do Something and transform the input PDDL into a new PDDL format
	BaseReformulator::ReformulatedPDDL = inputPDDL;
	return BaseReformulator::ReformulatedPDDL;
}

Plan BaseReformulator::RebuildSASPlan(Plan reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	BaseReformulator::OutputSAS = reformulatedSAS;
	return BaseReformulator::OutputSAS;
}