#ifndef H2_RUNNER
#define H2_RUNNER

#include <string>
#include <fstream>

#include "../Config/Config.hh"
#include "../Helpers/StringHelper.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

struct MutexVariable {
    struct Atom {
        const unsigned int predicate;
        const std::vector<unsigned int> objects;

        Atom(unsigned int predicate, std::vector<unsigned int> objects) : predicate(predicate), objects(objects) {};
    };
    
    // Each atom consists of a predicate, and a list of objects
    const std::vector<Atom> atoms;

    MutexVariable(std::vector<Atom> atoms) : atoms(atoms) {};
};

struct MutexInformation {
    const std::vector<MutexVariable> variables;
    
    MutexInformation(std::vector<MutexVariable> variables) : variables(variables) {};
};

class H2Runner {
public:
    H2Runner(PDDLInstance *instance) : instance(instance) {};
    MutexInformation RunH2(Config config);
private:
    PDDLInstance *instance;
    MutexInformation ParseOutput();
    std::vector<MutexVariable> ParseVariables(std::string h2Output);
    MutexVariable ParseVariable(std::vector<std::string> variableInfo);
};

#endif
