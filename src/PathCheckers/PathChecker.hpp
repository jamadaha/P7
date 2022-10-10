#ifndef PathChecker_HPP
#define PathChecker_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "../Config/config.h"
#include "../Helpers/FileHelper.h"

class PathsChecker {
public:
	static bool CheckPaths(Config* config);
};

bool PathsChecker::CheckPaths(Config* config) {
	if (config->domainFile.Content != "") {
		if (FileHelper::DoesFileExist(config->domainFile.Content)) {
			cout << "ERROR: Domain file not found!" << endl;
			cout << "Current Path: " + filesystem::current_path().string() << endl;
			cout << "File path: " + config->domainFile.Content << endl;
			return false;
		}
	}
	return true;
}

#endif
