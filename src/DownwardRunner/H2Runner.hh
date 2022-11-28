#ifndef H2_RUNNER
#define H2_RUNNER

#include <string>
#include <fstream>

#include "../Config/Config.hh"
#include "../Helpers/StringHelper.hh"
#include "../PDDL/Instance.hh"
#include "../PDDL/Mutex.hh"

class H2Runner {
public:
    H2Runner(PDDL::Instance *instance) : instance(instance) {};
    PDDL::Mutex RunH2(Config* config);
private:
    PDDL::Instance *instance;
    PDDL::Mutex ParseOutput();
    std::vector<PDDL::MutexVariable> ParseVariables(std::string h2Output);
    PDDL::MutexVariable ParseVariable(std::vector<std::string> variableInfo);
};

#endif
