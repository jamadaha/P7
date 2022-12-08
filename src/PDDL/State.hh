#ifndef STATE
#define STATE

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
    
        void AddChange(unsigned int predicate, unsigned int object, bool value) {
            if (!unaryChanges.contains(predicate))
                unaryChanges[predicate] = std::unordered_set<std::pair<unsigned int, bool>>{ std::make_pair(object, value) };
            else
                unaryChanges.at(predicate).emplace(std::make_pair(object, value));
        }

        void AddChange(unsigned int predicate, std::pair<unsigned int, unsigned int> objects, bool value) {
            if (!binaryChanges.contains(predicate))
                binaryChanges[predicate] = std::unordered_set<std::pair<std::pair<unsigned int, unsigned int>, bool>>{ std::make_pair(objects, value) };
            else
                binaryChanges.at(predicate).emplace(std::make_pair(objects, value));
        }
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
            if (!unaryFacts.contains(key))
                return false;
            return unaryFacts.at(key).contains(*value);
        };
        bool ContainsFact(const unsigned int& key, const unsigned int& value) const {
            if (!unaryFacts.contains(key))
                return false;
            return unaryFacts.at(key).contains(value);
        };

        bool ContainsFact(const unsigned int& key, const std::pair<unsigned int, unsigned int>& value) const {
            if (key == 0)
                return value.first == value.second;
            if (!binaryFacts.contains(key))
                return false;
            return binaryFacts.at(key).contains(value);
        }
#pragma endregion ContainsFact

        DoActionChanges DoAction(const ActionInstance* action);
        void DoEffect(const Literal* lit, const std::vector<unsigned int> *objects, DoActionChanges *changes);
        void DoUnaryEffect(const Literal* lit, const std::vector<unsigned int> *objects, DoActionChanges *changes);
        void DoBinaryEffect(const Literal* lit, const std::vector<unsigned int> *objects, DoActionChanges *changes);
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

#endif // STATE
