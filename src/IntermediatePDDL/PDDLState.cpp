#include "PDDLState.hh"

using namespace std;

bool PDDLState::IsUnaryLiteralTrue(PDDLLiteral literal, string object) {
    for (int i = 0; i < state.size(); i++)
        if (literal.predicate.name == state[i].predicate.name && object == state[i].predicate.args[0].name)
            return (literal.state == state[i].state);
    return false;
}

bool PDDLState::IsMultiLiteralTrue(PDDLLiteral literal, vector<string> objects) {
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