#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>

#include "ActionInstance.hh"
#include "../Helpers/Hashes.hh"

namespace PDDL {
    struct Instance;

    struct DoActionChanges {
        std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, bool>>> unaryChanges;
        std::unordered_map<unsigned int, std::unordered_set<std::pair<std::pair<unsigned int, unsigned int>, bool>>> binaryChanges;
    };

    struct State {
        // Key - Index of predicate | Value - Set of objects which the predicate is true for
        std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts;
        std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts;

        State() {};
        State(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts,
            std::unordered_map<unsigned int, std::unordered_set<std::pair<unsigned int, unsigned int>>> binaryFacts) :
            unaryFacts(unaryFacts), binaryFacts(binaryFacts) {};
        State(const State& state) : unaryFacts(state.unaryFacts), binaryFacts(state.binaryFacts) {};

#pragma region ContainsFact

        bool ContainsFact(const unsigned int& key, const unsigned int* value) const {
            return unaryFacts.at(key).contains(*value);
        };
        bool ContainsFact(const unsigned int& key, const unsigned int& value) const {
            return unaryFacts.at(key).contains(value);
        };

        bool ContainsFact(const unsigned int& key, const std::pair<unsigned int, unsigned int>& value) const {
            if (key == 0)
                return value.first == value.second;
            return binaryFacts.at(key).contains(value);
        }
#pragma endregion ContainsFact

        DoActionChanges DoAction(const ActionInstance* action);
        void UndoAction(const DoActionChanges* changes);

        std::string ToString(const Instance* instance);

        // Very slow, please only use with caution
        friend bool operator== (const State& lhs, const State& rhs) {
            return (lhs.unaryFacts == rhs.unaryFacts && lhs.binaryFacts == rhs.binaryFacts);
        };

    };
}

namespace std {
    template <>
    struct hash<PDDL::State> {
        auto operator()(const PDDL::State& s) const -> size_t {
            size_t h1 = s.unaryFacts.size();
            size_t h2 = s.binaryFacts.size();
            return (h1 ^ (h2 << 1));
        }
    };
}

#endif
