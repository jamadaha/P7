#ifndef PDDLCodeGenerator_Problem_HH
#define PDDLCodeGenerator_Problem_HH

#include <fstream>

#include "BasePDDLCodeGenerator.hh"

class PDDLProblemCodeGenerator : public BasePDDLCodeGenerator {
public:
	PDDLProblemCodeGenerator(const PDDLDomain *domain, const PDDLProblem *problem) : BasePDDLCodeGenerator(domain), problem(problem) {};
	void GenerateProblemFile(std::string problemFile);
	std::string GenerateProblemString();

private:
	const PDDLProblem *problem;
	std::string GetObjects(std::vector<std::string> objects);
	std::string GetInits(PDDLState literals);
	std::string GetGoals(PDDLState literals);
	std::string GetFacts(PDDLState literals);
};

#endif