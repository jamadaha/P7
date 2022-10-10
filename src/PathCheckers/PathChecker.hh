#ifndef PathChecker_H
#define PathChecker_H

#include <iostream>

#include "../Config/config.h"
#include "../Helpers/FileHelper.h"

class PathsChecker {
public:
	static bool IsPathsOk(Config* config);
private:
	template <typename T>
	static bool CheckItem(ConfigItem<T> item);
};

#endif
