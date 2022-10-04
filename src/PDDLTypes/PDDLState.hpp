#ifndef PDDL_STATE
#define PDDL_STATE

#include <vector>
#include <unordered_map>

#include "PDDLLiteral.hpp"

// This is a seperate class for future proofing
class PDDLState {
public:
    std::vector<PDDLLiteral> state;
private:
};

#endif
