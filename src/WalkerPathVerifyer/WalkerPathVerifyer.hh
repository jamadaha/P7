#ifndef WALKER_PATH_VERIFIER_HH
#define WALKER_PATH_VERIFIER_HH

#include <string>
#include <vector>

#include "../Walker/Path.hpp"
#include "../SASCodeGenerator/SASCodeGenerator.hh"
#include "../SASParser/SASParser.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

struct BadPath {
	std::string Reason;
	Path path;
};

class WalkerPathVerifyer {
public:
	std::vector<BadPath> VerifyPaths(std::vector<Path>* paths, PDDLInstance* instance);
private:
	SASAction GenerateSASActionFromActionInstance(PDDLActionInstance action, PDDLInstance* instance);
};

#endif
