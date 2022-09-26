#include "BaseReformulator.h"

PDDLDriver* BaseReformulator::ReformulatePDDL(PDDLDriver* inputPDDL) {
	// Do Something and transform the input PDDL into a new PDDL format
	return inputPDDL;
}

Plan* BaseReformulator::RebuildSASPlan(Plan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	return reformulatedSAS;
}