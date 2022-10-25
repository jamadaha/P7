#include "FileHelper.hh"

using namespace std;

bool FileHelper::DoesFileExist(filesystem::path fileName) {
	bool exists = filesystem::exists(filesystem::canonical(filesystem::absolute(fileName).lexically_normal()));
	return exists;
}