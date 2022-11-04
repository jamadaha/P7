#include "DownwardRunner.hh"
using namespace std;

void DownwardRunner::RunDownward(Config config, string reformulatedDomain, string reformulatedProblem, int timeLimit) {
	string path = config.GetItem<filesystem::path>("downwardpath").c_str();
	string command;
	if (timeLimit == -1)
		timeLimit = std::numeric_limits<int>::max();
	else
		timeLimit /= 1000;
	if (config.GetItem<string>("downwardheuristic").find("[") == std::string::npos)
		command = path + " --search-time-limit " + to_string(timeLimit) + "s --translate-time-limit " + to_string(timeLimit) + "s " + reformulatedDomain + " " + reformulatedProblem + " --search \"" + config.GetItem<string>("downwardsearch") + "(" + config.GetItem<string>("downwardheuristic") + "())\"" + " > " + RunnerLogName;
	else
		command = path + " --search-time-limit " + to_string(timeLimit) + "s --translate-time-limit " + to_string(timeLimit) + "s " + reformulatedDomain + " " + reformulatedProblem + " --search \"" + config.GetItem<string>("downwardsearch") + "(" + config.GetItem<string>("downwardheuristic") + ")\"" + " > " + RunnerLogName;
	system(command.c_str());
}

DownwardRunner::DownwardRunnerResult DownwardRunner::ParseDownwardLog() {
	ifstream stream(RunnerLogName);
	string content((istreambuf_iterator<char>(stream)),
		(istreambuf_iterator<char>()));
	stream.close();
	if (content.find("Solution found.") != string::npos)
		return DownwardRunnerResult::FoundPlan;
	if (content.find("Search stopped without finding a solution.") != string::npos)
		return DownwardRunnerResult::DidNotFindPlan;
	return DownwardRunnerResult::None;
}