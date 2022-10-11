#ifndef SASCodeGenerator_H
#define SASCodeGenerator_H

#include <string>
#include <fstream>
#include <streambuf>

#include "../SASParser/SASParser.h"

class SASCodeGenerator {
public:
	void GenerateCode(SASPlan plan, std::string targetFile);
	std::string GenerateCodeString(SASPlan plan, std::string targetFile);

private:
	std::string GetAction(SASAction action);
	std::string GetParameters(vector<string> parameters);
};

#endif