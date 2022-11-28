#ifndef PDDL_MUTEX_VARIABLE
#define PDDL_MUTEX_VARIABLE

#include <string>
#include <vector>

namespace PDDL {
    struct MutexVariable {
        struct Atom {
            const unsigned int predicate;
            // Used for debugging
            const std::string predicateS;
            const std::vector<unsigned int> objects;
            // Used for debugging
            const std::vector<std::string> objectsS;
            const bool value;

            Atom(
                unsigned int predicate,
                std::string predicateS,
                std::vector<unsigned int> objects,
                std::vector<std::string> objectsS,
                const bool value)
                : predicate(predicate), predicateS(predicateS), objects(objects), objectsS(objectsS), value(value) {};
        };

        // Each atom consists of a predicate, and a list of objects
        const std::vector<Atom> atoms;
        // This is true if atleast one of the atoms need to be true
        const bool minimumOneActive;

        MutexVariable(std::vector<Atom> atoms, bool minimumOne) : atoms(atoms), minimumOneActive(minimumOne) {};
    };
}

#endif
