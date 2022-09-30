#ifndef PlanValidator_H
#define PlanValidator_H

#include <string>
#include <iostream>
#include "../Config/config.h"

using namespace std;

class PlanValidator {
public:
	enum ValidatorResult { None, PlanMatch, PlanNotMatch };
	static enum ValidatorResult ValidatePlan(Config config, string domainFile, string problemFile, string planFile);
	
private:
};

#endif