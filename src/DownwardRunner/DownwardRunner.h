#ifndef DOWNWARDRUNNER
#define DOWNWARDRUNNER

#include <string>
#include <fstream>
#include "../Config/config.h"

using namespace std;

struct DownwardRunner {
    enum DownwardRunnerResult { None, FoundPlan, DidNotFindPlan };
    static enum DownwardRunnerResult RunDownward(Config config, string reformulatedDomain, string reformulatedProblem);
};

#endif
