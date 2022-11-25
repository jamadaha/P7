#ifndef SASCodeGenerator_HH
#define SASCodeGenerator_HH

#include <string>
#include <fstream>
#include <streambuf>

#include "../Plan.hh"

namespace SAS {
	class CodeGenerator {
	public:
		void GenerateCode(Plan plan, std::string targetFile);
		std::string GenerateCodeString(Plan plan, std::string targetFile);

	private:
		std::string GetAction(Action action);
		std::string GetParameters(std::vector<std::string> parameters);
	};

}

#endif