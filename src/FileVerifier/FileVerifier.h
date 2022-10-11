#ifndef FileVerifier_H
#define FileVerifier_H

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

#include "../Helpers/StringHelper.hh"

class FileVerifier {
public:
	bool VerifyFiles(std::string sourceFile, std::string targetFile);
	bool VerifyFiles(std::string sourceFile, std::string targetFile, std::vector<char> purgeChars);
};

#endif