#include "StringHelper.h"

void StringHelper::RemoveCharacter(string* buffer, char character) {
	buffer->erase(remove(buffer->begin(), buffer->end(), character), buffer->end());
}

string StringHelper::Trim(string buffer) {
    std::string::const_iterator it = buffer.begin();
    while (it != buffer.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = buffer.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}