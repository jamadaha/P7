#include <iostream>

#include "Config/Config.hh"
#include "CommonInterface/CommonInterface.hh"
#include "RunReport/RunReport.hh"
#include "RunReport/CompareReport.hh"

using namespace std;

int main(int argc, char** argv){
	Config config;

	std::filesystem::path fileName = std::filesystem::path("settings.ini");
	if (argc > 1)
		fileName = std::filesystem::path(argv[1]);
	config.ParseConfigFile(fileName); 

	auto reformulators = config.GetItem<vector<string>>("reformulator");
	auto reformulatorsRunStyles = config.GetItem<vector<bool>>("runDirect");

	if (reformulators.size() > 1) {
		CompareRunReport compareReport;
		bool isAllGood = true;
		for (int i = 0; i < reformulators.size(); i++) {
			RunReport report = RunReport(reformulators.at(i));
			CommonInterface interface = CommonInterface(config, &report, reformulatorsRunStyles.at(i));
			auto runResult = interface.Run(i);
			if (runResult != CommonInterface::RunResult::RanWithoutErrors) {
				isAllGood = false;
				break;
			}
			report.Print();
			compareReport.AddReport(report);
		}
		if (isAllGood)
			compareReport.Print();
	}
	else 
	{
		RunReport report = RunReport(reformulators.at(0));
		CommonInterface interface = CommonInterface(config, &report, reformulatorsRunStyles.at(0));
		auto runResult = interface.Run();
		if (runResult == CommonInterface::RunResult::RanWithoutErrors)
			report.Print();
	}

	config.Clear();

	return 0;
}