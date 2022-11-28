#ifndef PDDLCodeGenerator_HH
#define PDDLCodeGenerator_HH

#include <string>
#include <fstream>
#include <streambuf>

#include "DomainCodeGenerator.hh"
#include "ProblemCodeGenerator.hh"
#include "../Instance.hh"

namespace PDDL {
	class CodeGenerator {
	public:
		CodeGenerator(DomainCodeGenerator domainGenerator, ProblemCodeGenerator problemGenerator) : domainGenerator(domainGenerator), problemGenerator(problemGenerator) {};
		void GenerateCode(Instance document, std::string domainFile, std::string problemFile);

	private:
		DomainCodeGenerator domainGenerator;
		ProblemCodeGenerator problemGenerator;
	};
}

#endif