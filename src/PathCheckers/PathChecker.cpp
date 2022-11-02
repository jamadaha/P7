#include "PathChecker.hh"

using namespace std;

string PathsChecker::IsPathsOk(Config* config) {
	if (!CheckItem(config->GetItem<filesystem::path>("domain")))
		return config->GetItem<filesystem::path>("domain");
	if (!CheckItem(config->GetItem<filesystem::path>("problem")))
		return config->GetItem<filesystem::path>("problem");
	if (!CheckItem(config->GetItem<filesystem::path>("downwardpath")))
		return config->GetItem<filesystem::path>("downwardpath");
	if (!CheckItem(config->GetItem<filesystem::path>("validatorpath")))
		return config->GetItem<filesystem::path>("validatorpath");
	return "";
}

bool PathsChecker::CheckItem(filesystem::path path) {
	if (!FileHelper::DoesFileExist(path)) {
		return false;
	}
	return true;
}