#ifndef PDDL_MUTEX_INFO
#define PDDL_MUTEX_INFO

#include <string>
#include <vector>

struct PDDLMutexVariable {
    struct Atom {
        const unsigned int predicate;
        // Used for debugging
        const std::string predicateS;
        const std::vector<unsigned int> objects;
        // Used for debugging
        const std::vector<std::string> objectsS;

        Atom(
            unsigned int predicate, 
            std::string predicateS,
            std::vector<unsigned int> objects,
            std::vector<std::string> objectsS) 
            : predicate(predicate), predicateS(predicateS), objects(objects), objectsS(objectsS) {};
    };
    
    // Each atom consists of a predicate, and a list of objects
    const std::vector<Atom> atoms;

    PDDLMutexVariable(std::vector<Atom> atoms) : atoms(atoms) {};
};

struct PDDLMutex {
    const std::vector<PDDLMutexVariable> variables;
    
    PDDLMutex() {};
    PDDLMutex(std::vector<PDDLMutexVariable> variables) : variables(variables) {};
    
};

#endif
