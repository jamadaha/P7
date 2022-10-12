#include "P7.hh"

#include <catch2/catch_test_macros.hpp>
#include <string>

#include "Config/config.hh"
#include "DownwardRunner/DownwardRunner.hh"

using namespace std;

const string TAG = "DownwardRunner ";
const string domain = "./TestFiles/gripper.pddl";
const string problem = "./TestFiles/gripper-4.pddl";


int main(int argc, char** argv){
	DownwardRunner downward = DownwardRunner();
    Config config;
    auto x = downward.RunDownward(config, domain, problem);
	printf("%d", x==DownwardRunner::DownwardRunnerResult::None);

	/*
	Config config;
	// Do first as it quits on help
	if (config.ParseArgs(&config, argc, argv))
		return 0;

	RunReport report = RunReport();

	cout << "Running reformulator..." << endl;	
	std::shared_ptr<BaseReformulator> reformulator = std::make_shared<SameOutputReformulator>();
	CommonInterface interface = CommonInterface(config, reformulator);
	auto result = interface.Run(&report);
	cout << "Done!" << endl;
	if (result == CommonInterface::RunResult::RanWithoutErrors)
		report.Print();
	return 0;
	*/
}