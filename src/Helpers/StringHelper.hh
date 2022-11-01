#ifndef StringHelper_HH
#define StringHelper_HH

#include <string>
#include <streambuf>
#include <memory>
#include <iostream>
#include <stdarg.h>  // For va_start, etc.
#include <cstring>
#include <vector>

class StringHelper {
public:
	static void RemoveCharacter(std::string* buffer, char character);
	static std::string RemoveCharacter(std::string buffer, char character);
	static void Trim(std::string* buffer);
	static std::string Trim(std::string buffer);
	static std::string StringFormat(const std::string fmt_str, ...);
	static std::vector<std::string> Split(std::string input, char delimiter);
	static std::string ToUpper(std::string value);
};

#endif