#ifndef NAIVE_REGRESSOR
#define NAIVE_REGRESSOR

#include "BaseRegressor.hh"

class NaiveRegressor : BaseRegressor {
public:
    PartialRegressor(const PDDLInstance *instance) : BaseRegressor(instance) {};
    std::vector<Path> Regress(const PDDLState *state) override;
    
private:

};

#endif
