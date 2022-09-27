#ifndef DOWNWARDRUNNER
#define DOWNWARDRUNNER

#include <string>
#include "../Config/config.h"

struct DownwardRunner {
    static void runDownward(Config config, string reformulatedDomain, string reformulatedProblem);
};

#endif
