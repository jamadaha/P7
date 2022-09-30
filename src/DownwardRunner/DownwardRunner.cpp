#include "DownwardRunner.h"
#include <iostream>

const string RunnerLogName = "downwardLog";

DownwardRunner::DownwardRunnerResult DownwardRunner::RunDownward(Config config, string reformulatedDomain, string reformulatedProblem) {
    string path = config.path;
    string search = config.opt.search;
    string heuristic = config.opt.heuristic;

    string command = path + " " + reformulatedDomain + " " + reformulatedProblem + " --search \"" + search + "(" + heuristic + "())\"" + " > " + RunnerLogName;
    system(command.c_str());

	ifstream stream(RunnerLogName);
	string content((istreambuf_iterator<char>(stream)),
		(istreambuf_iterator<char>()));
	if (content.find("Solution found.") != string::npos)
		return DownwardRunner::DownwardRunnerResult::FoundPlan;
	if (content.find("Search stopped without finding a solution.") != string::npos)
		return DownwardRunner::DownwardRunnerResult::DidNotFindPlan;
	return DownwardRunner::DownwardRunnerResult::None;
}
