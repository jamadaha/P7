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

template<typename ... Args>
std::string StringHelper::StringFormat(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}