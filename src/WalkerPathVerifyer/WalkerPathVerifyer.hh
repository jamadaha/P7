#ifndef WALKER_PATH_VERIFIER_HH
#define WALKER_PATH_VERIFIER_HH

#include <string>
#include <vector>

#include "../Walker/Path.hh"
#include "../SAS/Action.hh"
#include "../SAS/CodeGenerator/CodeGenerator.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../PDDLCodeGenerator/PDDLCodeGenerator.hh"
#include "../PlanValidators/PlanValidator.hh"
#include "../Config/Config.hh"

struct BadPath {
	std::string Reason;
	Path path;

	BadPath(Path path, std::string reason) : path(path), Reason(reason) {};
};

class WalkerPathVerifyer {
public:
	std::vector<BadPath> VerifyPaths(std::vector<Path>* paths, PDDLInstance* instance, Config* config);
private:
	SAS::Action GenerateSASActionFromActionInstance(PDDLActionInstance action, PDDLInstance* instance);
};

#endif
