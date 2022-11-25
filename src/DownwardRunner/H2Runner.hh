#ifndef H2_RUNNER
#define H2_RUNNER

#include <string>
#include <fstream>

#include "../Config/Config.hh"
#include "../Helpers/StringHelper.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../IntermediatePDDL/PDDLMutex.hh"

class H2Runner {
public:
    H2Runner(PDDLInstance *instance) : instance(instance) {};
    PDDLMutex RunH2(Config* config);
private:
    PDDLInstance *instance;
    PDDLMutex ParseOutput();
    std::vector<PDDLMutexVariable> ParseVariables(std::string h2Output);
    PDDLMutexVariable ParseVariable(std::vector<std::string> variableInfo);
};

#endif
