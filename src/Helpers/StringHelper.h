#ifndef StringHelper_H
#define StringHelper_H

#include <string>
#include <streambuf>
#include <memory>
#include <iostream>

using namespace std;

class StringHelper {
public:
	static void RemoveCharacter(string* buffer, char character);
	static string Trim(string buffer);
	template<typename ... Args>
	static string StringFormat(const string& format, Args ... args);
};

#endif