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

	if (config.GetStringList("reformulator").size() > 1) {
		CompareRunReport compareReport;
		bool isAllGood = true;
		for (int i = 0; i < config.GetStringList("reformulator").size(); i++) {
			RunReport report = RunReport(config.GetStringList("reformulator").at(i));
			CommonInterface interface = CommonInterface(config);
			auto runResult = interface.Run(&report, i);
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
		RunReport report = RunReport(config.GetStringList("reformulator").at(0));
		CommonInterface interface = CommonInterface(config);
		auto runResult = interface.Run(&report);
		if (runResult == CommonInterface::RunResult::RanWithoutErrors)
			report.Print();
	}
	return 0;
}