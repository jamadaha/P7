#ifndef PDDL_STATE
#define PDDL_STATE

#include <vector>
#include <unordered_map>

#include "PDDLLiteral.hpp"

// This is a seperate class for future proofing
class PDDLState {
public:
    // Refers to the given problems objects
    std::vector<std::string> *objects;
    std::vector<PDDLLiteral> state;

    bool IsUnaryLiteralTrue(PDDLLiteral literal, std::string object) {
        for (int i = 0; i < state.size(); i++)
            if (literal.predicate.name == state[i].predicate.name && object == state[i].predicate.args[0].name)
                return (literal.state == state[i].state);
        return false;
    }

    bool IsMultiLiteralTrue(PDDLLiteral literal, std::vector<std::string> objects) {
        if (literal.predicate.name == "=")
            return (objects[literal.predicate.args[0].index] == objects[literal.predicate.args[1].index]) == literal.state;
        
        for (int i = 0; i < state.size(); i++) {
            if (literal.predicate.name == state[i].predicate.name) {
                bool sameObjects = true;
                for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++) 
                    if (objects[i] != state[i].predicate.args[i].name)
                        sameObjects == false;
                if (sameObjects) return (literal.state == state[i].state);
            }
        }

        return false;
    }
private:
};

#endif
