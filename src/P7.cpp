#include "P7.hh"

using namespace std;

int main(int argc, char** argv)
{
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
}