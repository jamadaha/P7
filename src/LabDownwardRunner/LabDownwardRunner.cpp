#include "LabDownwardRunner.h"
#include <iostream>

const string RunnerLogName = "downwardLog";

DownwardRunner::DownwardRunnerResult LabDownwardRunner::RunDownward(Config config, string reformulatedDomain, string reformulatedProblem)
{
	string path = config.path;
	string search = config.opt.search;
	string heuristic = config.opt.heuristic;

	//Lab can't handle the full path for downward (it has to have the folder with .git inside)
	std::string folder = path.substr(0, path.find_last_of("/"));

	//Lab can only handle benchmarks that are folder with name = domain, inside folder domain.pddl and problem
	string command = "rm -rf ../data/runLab ../data/runLab-eval && mkdir -p temp && cp " + reformulatedDomain + " " + reformulatedProblem + " temp && mv temp/" + reformulatedDomain + " temp/domain.pddl > " + RunnerLogName;
	cout << command;
	system(command.c_str());
	
	command = "python3 ../runLab.py --all --downward " + folder + " --benchmarks ''" + " --problem temp:" + reformulatedProblem + " > " + RunnerLogName;
	cout << command;
	system(command.c_str());

	command = "rm -rf temp";
	cout << command;
	system(command.c_str());

	ifstream stream(RunnerLogName);
	string content((istreambuf_iterator<char>(stream)),(istreambuf_iterator<char>()));
	stream.close();
	if (content.find("Solution found.") != string::npos)
		return DownwardRunner::DownwardRunnerResult::FoundPlan;
	if (content.find("Search stopped without finding a solution.") != string::npos)
		return DownwardRunner::DownwardRunnerResult::DidNotFindPlan;
	return DownwardRunner::DownwardRunnerResult::None;
}
