#ifndef StringHelper_HH
#define StringHelper_HH

#include <string>
#include <streambuf>
#include <sstream>
#include <memory>
#include <iostream>
#include <fstream>
#include <stdarg.h>  // For va_start, etc.
#include <cstring>
#include <vector>
#include <iterator>
#include <algorithm>

class StringHelper {
public:
	static void RemoveCharacter(std::string* buffer, char character);
	static std::string RemoveCharacter(const std::string buffer, const char character);
	static void Trim(std::string* buffer);
	static std::string Trim(const std::string buffer);
	static std::string StringFormat(const std::string fmt_str, ...);
	static std::vector<std::string> Split(std::string input, const char delimiter);
	static std::string ToUpper(std::string value);
	static std::string Replace(std::string str, const char replace, const char with);
};

#endif