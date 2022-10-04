#include "LabDownwardRunner.h"
#include <iostream>

const string RunnerLogName = "downwardLog";

DownwardRunner::DownwardRunnerResult LabDownwardRunner::RunDownward(Config config, string reformulatedDomain, string reformulatedProblem)
{
	string path = config.path;
	string search = config.opt.search;
	string heuristic = config.opt.heuristic;

	string labFolder = "labReport";

	//Lab can't handle the full path for downward (it has to have the folder with .git inside)
	std::string folder = path.substr(0, path.find_last_of("/"));

	//Lab can only handle benchmarks where inside folder there is domain.pddl and problem
	string command = "rm -rf " + labFolder + " " + labFolder + "-eval && mkdir -p temp && cp " + reformulatedDomain + " " + reformulatedProblem + " temp && mv temp/" + reformulatedDomain + " temp/domain.pddl";
	system(command.c_str());
	
	//Call downward through lab script
	command = "python3 ../runLab.py --all --downward " + folder + " --benchmarks '' --report " + labFolder + " --problem temp:" + reformulatedProblem + " > " + RunnerLogName;
	system(command.c_str());

	command = "rm -rf temp";
	system(command.c_str());

	command = "mv " + labFolder + "/runs-00001-00100/00001/sas_plan sas_plan";
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
