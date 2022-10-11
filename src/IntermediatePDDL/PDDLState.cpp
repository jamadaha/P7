#include "PDDLState.hh"

using namespace std;

bool PDDLState::IsUnaryLiteralTrue(PDDLLiteral literal, string object) {
    return HasPredicate(literal.predicate, std::vector<string>{object}) == literal.state;
}

bool PDDLState::IsMultiLiteralTrue(PDDLLiteral literal, vector<string> objects) {
    if (literal.predicate.name == "=")
        return AreEqual(objects[literal.predicate.args[0].index], objects[literal.predicate.args[1].index]) == literal.state;
    return HasPredicate(literal.predicate, objects) == literal.state;

    return false;
}

bool PDDLState::HasPredicate(PDDLPredicate predicate, std::vector<std::string> objects) {
    for (int i = 0; i < state.size(); i++) {
        if (state[i].name == predicate.name && state[i].args.size() == predicate.args.size() && state[i].args.size() == objects.size()) {
            bool found = true;
            for (int o = 0; o < objects.size(); o++) {
                if (objects[o] != state[i].args[o].name) {
                    found = false;
                    break;
                }
            }
            if (found)
                return true;
        }
    }
    return false;
}

bool PDDLState::AreEqual(std::string arg1, std::string arg2) {
    return arg1 == arg2;
}
