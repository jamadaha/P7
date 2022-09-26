#include "StringHelper.h"

void StringHelper::RemoveCharacter(string* buffer, char character) {
	buffer->erase(remove(buffer->begin(), buffer->end(), character), buffer->end());
}