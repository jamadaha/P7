#ifndef DOWNWARDRUNNER_HH
#define DOWNWARDRUNNER_HH

#include <string>
#include <fstream>

#include "../Config/config.hh"

class DownwardRunner {
public:
    enum DownwardRunnerResult { None, FoundPlan, DidNotFindPlan };
    enum DownwardRunnerResult RunDownward(Config config, std::string reformulatedDomain, std::string reformulatedProblem);

    std::string RunnerLogName = "downwardLog";
};

#endif
