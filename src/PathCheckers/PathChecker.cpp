#include "PathChecker.hh"

bool PathsChecker::IsPathsOk(Config* config) {
	if (!CheckItem(config->domainFile))
		return false;
	if (!CheckItem(config->problemFile))
		return false;
	if (!CheckItem(config->downwardPath))
		return false;
	if (!CheckItem(config->validatorPath))
		return false;
	return true;
}

template <typename T>
bool PathsChecker::CheckItem(ConfigItem<T> item) {
	if (item.Content != "") {
		if (!FileHelper::DoesFileExist(item.Content)) {
			cout << "ERROR: File not found!" << endl;
			cout << "Current Path: " + filesystem::current_path().string() << endl;
			cout << "File path: " + item.Content << endl;
			return false;
		}
	}
	else {
		if (!FileHelper::DoesFileExist(item.DefaultContent)) {
			cout << "ERROR: File (USING DEFAULT) not found!" << endl;
			cout << "Current Path: " + filesystem::current_path().string() << endl;
			cout << "File path: " + item.DefaultContent << endl;
			return false;
		}
	}
	return true;
}