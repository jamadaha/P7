#include "ObjectActionDepthFunction.h"

int ObjectActionDepthFunction::GetDepth(PDDLInstance instance) {
	int retValue = 0;
	retValue = instance.problem->objects.size() * instance.domain->actions.size();
	return retValue * Modifier;
}