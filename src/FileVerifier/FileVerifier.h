#ifndef FileVerifier_H
#define FileVerifier_H

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

class FileVerifier {
public:
	bool VerifyFiles(string sourceFile, string targetFile);
	bool VerifyFiles(string sourceFile, string targetFile, vector<char> purgeChars);
};

#endif