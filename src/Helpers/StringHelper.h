#ifndef StringHelper_H
#define StringHelper_H

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

class StringHelper {
public:
	static void RemoveCharacter(string* buffer, char character);
	static string RemoveCharacter(string buffer, char character);
	static void Trim(string* buffer);
	static string Trim(string buffer);
};

#endif