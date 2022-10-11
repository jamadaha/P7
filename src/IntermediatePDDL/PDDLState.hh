#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>

#include "PDDLLiteral.hh"

// This is a seperate class for future proofing
class PDDLState {
public:
    // Refers to the given problems objects
    std::vector<std::string> *objects;
    std::vector<PDDLLiteral> state;

    bool IsUnaryLiteralTrue(PDDLLiteral literal, std::string object);
    bool IsMultiLiteralTrue(PDDLLiteral literal, std::vector<std::string> objects);
private:
};

#endif
