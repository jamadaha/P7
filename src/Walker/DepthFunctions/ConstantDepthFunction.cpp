#include "ConstantDepthFunction.h"

int ConstantDepthFunction::GetDepth(PDDLInstance instance) {
	return ConstantDepth * Modifier;
}
