#ifndef SASCodeGenerator_H
#define SASCodeGenerator_H

#include "../SASParser/SASParser.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

class SASCodeGenerator {
public:
	void GenerateCode(Plan* plan, string targetFile);

private:
	string GetAction(SASAction* action);
	string GetParameters(vector<string>* parameters);
};

#endif