#ifndef PlanValidator_H
#define PlanValidator_H

#include <string>
#include <fstream>
#include <iostream>
#include "../Config/config.h"
#include "../Helpers/FileHelper.h"

using namespace std;

class PlanValidator {
public:
	enum ValidatorResult { None, PlanMatch, PlanNotMatch, MissingVAL, MissingDomainFile, MissingProblemFile, MissingPlanFile};
	static enum ValidatorResult ValidatePlan(Config config, string domainFile, string problemFile, string planFile);
	
private:
};

#endif