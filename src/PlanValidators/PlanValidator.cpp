#include "PlanValidator.h"

const string ValidatorLogName = "validatorLog";

enum PlanValidator::ValidatorResult PlanValidator::ValidatePlan(Config config, string domainFile, string problemFile, string planFile) {
	string command = config.validatorPath + " " + domainFile + " " + problemFile + " " + planFile + " > " + ValidatorLogName;
	system(command.c_str());

	ifstream stream(ValidatorLogName);
	string content((istreambuf_iterator<char>(stream)),
		(istreambuf_iterator<char>()));
	if (content.find("Plan Valid") != string::npos)
		return PlanValidator::ValidatorResult::PlanMatch;
	if (content.find("Plan failed to execute") != string::npos)
		return PlanValidator::ValidatorResult::PlanNotMatch;
	return PlanValidator::ValidatorResult::None;
}