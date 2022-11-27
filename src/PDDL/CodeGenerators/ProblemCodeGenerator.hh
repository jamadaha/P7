#ifndef PDDLCodeGenerator_Problem_HH
#define PDDLCodeGenerator_Problem_HH

#include <fstream>

#include "BaseCodeGenerator.hh"

namespace PDDL {
	class ProblemCodeGenerator : public BaseCodeGenerator {
	public:
		ProblemCodeGenerator(const Domain* domain, const Problem* problem) : BaseCodeGenerator(domain), problem(problem) {};
		void GenerateProblemFile(std::string problemFile);
		std::string GenerateProblemString();

	private:
		const Problem* problem;
		std::string GetObjects(std::vector<std::string> objects);
		std::string GetInits(State literals);
		std::string GetGoals(State literals);
		std::string GetFacts(State literals);
	};
}

#endif