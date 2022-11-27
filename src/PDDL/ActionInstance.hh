#ifndef PDDL_ACTION_INSTANCE_HH
#define PDDL_ACTION_INSTANCE_HH

#include <vector>
#include <unordered_set>
#include <string>

#include "Action.hh"
#include "../Helpers/Hashes.hh"

namespace PDDL {
    struct Instance;

    class ActionInstance {
    public:
        size_t GetHash();

        const Action* action = nullptr;
        std::vector<unsigned int> objects;
        ActionInstance() {};
        ActionInstance(const Action* action, const std::vector<unsigned int> objects) : action(action), objects(objects) {};
        ActionInstance(const ActionInstance& instance) : action(instance.action), objects(instance.objects) {};
        std::string ToString(const Instance* instance);
        std::string LiteralsToString(std::vector<Literal> literals, const Instance* instance);

        friend bool operator==(const ActionInstance& lhs, const ActionInstance& rhs) {
            if (lhs.action != rhs.action)
                return false;
            if (lhs.objects != rhs.objects)
                return false;
            return true;
        }

    private:
        size_t Hash = 0;
    };
}

namespace std {
    template <>
    struct hash<PDDL::ActionInstance> {
        auto operator()(const PDDL::ActionInstance& s) const -> size_t {
            std::size_t h1 = std::hash<const PDDL::Action*>{}(s.action);
            std::size_t h2 = hash<vector<unsigned int>>{}(s.objects);
            return h1 ^ (h2 << 1);
        }
    };

    template <>
    struct hash<vector<PDDL::ActionInstance*>> {
        auto operator()(vector<PDDL::ActionInstance*>& vec) -> size_t {
            std::size_t seed = vec.size();
            for (int i = 0; i < vec.size(); i++)
                seed ^= 0x8e3471b5 + vec.at(i)->GetHash() + (seed >> 3);
            return seed;
        }
    };

    template <>
    struct hash<vector<PDDL::ActionInstance>> {
        auto operator()(vector<PDDL::ActionInstance>& vec) -> size_t {
            std::size_t seed = vec.size();
            for (int i = 0; i < vec.size(); i++)
                seed ^= 0x8e3471b5 + vec.at(i).GetHash() + (seed >> 3);
            return seed;
        }
    };
}

#endif
