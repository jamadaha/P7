#ifndef StringHelper_H
#define StringHelper_H

#include <string>
#include <streambuf>
#include <memory>
#include <iostream>

class StringHelper {
public:
	static void RemoveCharacter(std::string* buffer, char character);
	static std::string RemoveCharacter(std::string buffer, char character);
	static void Trim(std::string* buffer);
	static std::string Trim(std::string buffer);
	template<typename ... Args>
	static std::string StringFormat(const std::string& format, Args ... args);
};

#endif