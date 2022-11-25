#ifndef PARTIAL_ACTION
#define PARTIAL_ACTION

#include <unordered_map>

#include "../../IntermediatePDDL/PDDLAction.hh"

class PartialAction {
public:
    const PDDLAction *action;
    // The action instance, a nullptr means the given parameter is partial
    // A partial parameter allows any object that fulfill the action preconditions
    std::vector<unsigned int*> parameters;
    PartialAction(const PDDLAction *action, std::vector<unsigned int*> parameters) : action(action), parameters(parameters) {};
    PartialAction(const PartialAction &partialAction) : action(partialAction.action), parameters(partialAction.parameters) {};

    bool friend operator==(const PartialAction &lhs, const PartialAction &rhs) {
        if (lhs.action != rhs.action)
            return false;

        if (lhs.parameters.size() != rhs.parameters.size())
            return false;

        for (int i = 0; i < lhs.parameters.size(); i++)
            if ((lhs.parameters.at(i) == nullptr && rhs.parameters.at(i) != nullptr) ||
                (lhs.parameters.at(i) != nullptr && rhs.parameters.at(i) == nullptr))
                return false;
            else if (lhs.parameters.at(i) != nullptr && rhs.parameters.at(i) != nullptr &&
                     *(lhs.parameters.at(i)) != *(rhs.parameters.at(i)))
                return false;
        return true;
    }

private:

};

namespace std {
    template <>
    struct hash<PartialAction> {
        auto operator()(const PartialAction& s) const -> size_t {
            // Do something better later
            return 0;
        }
    };
}

#endif
