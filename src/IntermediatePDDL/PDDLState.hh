#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>

#include "PDDLActionInstance.hh"
#include "../Helpers/Hashes.hh"

struct PDDLInstance;

struct PDDLState {
    // Key - Index of predicate | Value - Set of objects which the predicate is true for
    std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
    std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts;

    PDDLState() {};
    PDDLState(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts, 
              std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts) :
        unaryFacts(unaryFacts), binaryFacts(binaryFacts) {};
    PDDLState(const PDDLState &state) : unaryFacts(state.unaryFacts), binaryFacts(state.binaryFacts) {};

#pragma region ContainsFact

    bool ContainsFact(const unsigned int &key, const unsigned int *value) const {
        return unaryFacts.at(key).contains(*value);
    };
    bool ContainsFact(const unsigned int &key, const unsigned int &value) const {
        return unaryFacts.at(key).contains(value);
    };

    bool ContainsFact(const unsigned int &key, const std::pair<unsigned int, unsigned int> &value) const {
        if (key == 0)
            return value.first == value.second;
        return binaryFacts.at(key).contains(value);
    }
#pragma endregion ContainsFact

    void DoAction(const PDDLActionInstance *action);
    void UndoAction(const PDDLActionInstance *action);

    std::string ToString(const PDDLInstance* instance);

    // Very slow, please only use with caution
    friend bool operator== (const PDDLState &lhs, const PDDLState &rhs) {
        return (lhs.unaryFacts == rhs.unaryFacts && lhs.binaryFacts == rhs.binaryFacts);
    };
    
};

namespace std {
    template <>
    struct hash<PDDLState> {
        auto operator()(const PDDLState& s) const -> size_t {
            size_t h1 = s.unaryFacts.size();
            size_t h2 = s.binaryFacts.size();
            return (h1 ^ (h2 << 1));
        }
    };
}

#endif
