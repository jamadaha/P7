#include "FileHelper.hh"

bool FileHelper::DoesFileExist(filesystem::path fileName) {
	bool exists = filesystem::exists(fileName);
	return exists;
}