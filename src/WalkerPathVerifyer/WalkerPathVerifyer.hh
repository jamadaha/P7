#ifndef WALKER_PATH_VERIFIER_HH
#define WALKER_PATH_VERIFIER_HH

#include <string>
#include <vector>

#include "../Walker/Path.hpp"

struct BadPath {
	std::string Reason;
	Path path;
};

class WalkerPathVerifyer {
public:
	std::vector<BadPath> VerifyPaths(std::vector<Path>* paths);
};

#endif
