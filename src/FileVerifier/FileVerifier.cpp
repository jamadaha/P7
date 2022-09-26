#include "FileVerifier.h"

using namespace std;

bool FileVerifier::VerifyFiles(string sourceFile, string targetFile) {
    return VerifyFiles(sourceFile, targetFile, {'\n', '\r', '\t', ' '});
}

bool FileVerifier::VerifyFiles(string sourceFile, string targetFile, vector<char> purgeChars) {
    ifstream sourceStream(sourceFile);
    string sourceBuffer((istreambuf_iterator<char>(sourceStream)),
        istreambuf_iterator<char>());
    ifstream targetStream(targetFile);
    string targetBuffer((istreambuf_iterator<char>(targetStream)),
        istreambuf_iterator<char>());

    for(char character : purgeChars)
        RemoveCharacter(&(sourceBuffer), character);
    for (char character : purgeChars)
        RemoveCharacter(&(targetBuffer), character);

    if (sourceBuffer != targetBuffer)
        return false;
    return true;
}

void FileVerifier::RemoveCharacter(string* buffer, char character) {
    buffer->erase(remove(buffer->begin(), buffer->end(), character), buffer->end());
}