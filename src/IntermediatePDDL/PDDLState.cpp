#include "PDDLState.hh"

using namespace std;

bool PDDLState::IsUnaryLiteralTrue(PDDLAction *action, PDDLLiteral literal, string object) {
    for (auto s : this->state)
        if (literal.predicate.name == s.name && object == s.args[0].name)
            return literal.state;
    return !literal.state;
}

bool PDDLState::IsMultiLiteralTrue(PDDLAction *action, PDDLLiteral literal, vector<string> objects) {
    if (literal.predicate.name == "=")
        return AreEqual(objects[action->GetParamIndex(literal.predicate.args[0].name)], objects[action->GetParamIndex(literal.predicate.args[1].name)]) == literal.state;
    return HasPredicate(action, literal.predicate, objects) == literal.state;

    return false;
}

bool PDDLState::Update(PDDLLiteral literal) {
    return literal.state;
}

bool PDDLState::HasPredicate(PDDLAction *action, PDDLPredicate predicate, std::vector<std::string> objects) {
    for (int i = 0; i < state.size(); i++) {
        if (state[i].name == predicate.name && state[i].args.size() == predicate.args.size() && state[i].args.size() == objects.size()) {
            bool found = true;
            for (int o = 0; o < objects.size(); o++) {
                int index = action->GetParamIndex(predicate.args[o].name);
                if (objects[index] != state[i].args[o].name) {
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
