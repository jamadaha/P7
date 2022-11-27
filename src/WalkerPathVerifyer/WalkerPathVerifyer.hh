#ifndef WALKER_PATH_VERIFIER_HH
#define WALKER_PATH_VERIFIER_HH

#include <string>
#include <vector>

#include "../Walker/Path.hh"
#include "../SAS/Action.hh"
#include "../SAS/CodeGenerator/CodeGenerator.hh"
#include "../PDDL/Instance.hh"
#include "../PDDL/CodeGenerators/CodeGenerator.hh"
#include "../PlanValidators/PlanValidator.hh"
#include "../Config/Config.hh"

struct BadPath {
	std::string Reason;
	Path path;

	BadPath(Path path, std::string reason) : path(path), Reason(reason) {};
};

class WalkerPathVerifyer {
public:
	std::vector<BadPath> VerifyPaths(std::vector<Path>* paths, PDDL::Instance* instance, Config* config);
private:
	SAS::Action GenerateSASActionFromActionInstance(PDDL::ActionInstance action, PDDL::Instance* instance);
};

#endif
