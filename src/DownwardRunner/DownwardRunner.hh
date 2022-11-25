#ifndef DOWNWARDRUNNER_HH
#define DOWNWARDRUNNER_HH

#include <string>
#include <fstream>
#include <limits>

#include "../Config/Config.hh"

class DownwardRunner {
public:
    enum DownwardRunnerResult { None, FoundPlan, DidNotFindPlan };
    void RunTranslator(Config* config, std::string domainPath, std::string problemPath);
    void RunDownward(Config* config, std::string reformulatedDomain, std::string reformulatedProblem, int timeLimitMs);
    DownwardRunnerResult ParseDownwardLog();

    std::string RunnerLogName = "downwardLog";
};

#endif
