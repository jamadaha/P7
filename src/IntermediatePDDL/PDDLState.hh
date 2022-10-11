#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>

#include "PDDLPredicate.hh"
#include "PDDLLiteral.hh"

// This is a seperate class for future proofing
class PDDLState {
public:
    // Refers to the given problems objects
    std::vector<std::string> *objects;
    std::vector<PDDLPredicate> state;

    bool IsUnaryLiteralTrue(PDDLLiteral literal, std::string object);
    bool IsMultiLiteralTrue(PDDLLiteral literal, std::vector<std::string> objects);
private:
    bool HasPredicate(PDDLPredicate predicate, std::vector<std::string> objects);
    bool AreEqual(std::string arg1, std::string arg2);
};

#endif
