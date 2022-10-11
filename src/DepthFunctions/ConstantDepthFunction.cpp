#include "ConstantDepthFunction.h"

using namespace std;

int ConstantDepthFunction::GetDepth(PDDLInstance instance) {
	return ConstantDepth * Modifier;
}
