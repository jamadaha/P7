#include "StringHelper.h"

void StringHelper::RemoveCharacter(string* buffer, char character) {
	buffer->erase(remove(buffer->begin(), buffer->end(), character), buffer->end());
}

string StringHelper::RemoveCharacter(string buffer, char character) {
    string newBuffer = buffer;
    StringHelper::RemoveCharacter(&newBuffer, character);
    return newBuffer;
}

void StringHelper::Trim(string* buffer) {
    string::const_iterator it = buffer->begin();
    int from = 0;
    int length = buffer->size();

    while (it != buffer->end() && isspace(*it)) {
        it++;
        from++;
    }

    string::const_reverse_iterator rit = buffer->rbegin();
    while (rit.base() != it && isspace(*rit)) {
        rit++;
        length--;
    }

    *buffer = buffer->substr(from, length - from);
}

string StringHelper::Trim(string buffer) {
    string newBuffer = buffer;
    StringHelper::Trim(&newBuffer);
    return newBuffer;
}