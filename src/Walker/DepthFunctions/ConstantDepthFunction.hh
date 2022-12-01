#ifndef ConstantDepthFunction_HH
#define ConstantDepthFunction_HH

#include "../../PDDL/Instance.hh"
#include "BaseDepthFunction.hh"

class ConstantDepthFunction : public BaseDepthFunction {
public:
    ConstantDepthFunction(int depth, PDDL::Instance* instance, double modifier = 1) : ConstantDepth(depth * modifier), BaseDepthFunction(instance, modifier) {}
    inline int GetDepth() override {
        return ConstantDepth;
    }
private:
    const int ConstantDepth;
};

#endif
