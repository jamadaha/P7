#include "ConstantDepthFunction.hh"

using namespace std;

int ConstantDepthFunction::GetDepth(PDDLInstance instance) {
	return ConstantDepth * Modifier;
}
