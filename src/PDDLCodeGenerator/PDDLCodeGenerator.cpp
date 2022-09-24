#include "PDDLCodeGenerator.h"

using namespace std;

void PDDLCodeGenerator::GenerateCode(PDDLDriver* driver, string domainFile, string problemFile) {
	domainGenerator.GenerateDomainFile(driver->domain, domainFile);
	problemGenerator.GenerateProblemFile(driver->problem, problemFile);
}

void PDDLCodeGenerator::GenerateAndVerifyCode(PDDLDriver* driver, string sourceDomainFile, string targetDomainFile, string sourceProblemFile, string targetProblemFile) {
    GenerateCode(driver, targetDomainFile, targetProblemFile);
    if (!VerifyCodeGeneration(sourceDomainFile, targetDomainFile))
        throw invalid_argument("Input and output files was not the same!");
    if (!VerifyCodeGeneration(sourceProblemFile, targetProblemFile))
        throw invalid_argument("Input and output files was not the same!");
}

bool PDDLCodeGenerator::VerifyCodeGeneration(string sourceFile, string generatedFile) {
    ifstream sourceStream(sourceFile);
    string sourceBuffer((   istreambuf_iterator<char>(sourceStream)),
                            istreambuf_iterator<char>());
    ifstream generatedStream(generatedFile);
    string generatedBuffer((istreambuf_iterator<char>(generatedStream)),
                            istreambuf_iterator<char>());

    RemoveCharacter(&(sourceBuffer), '\n');
    RemoveCharacter(&(sourceBuffer), '\r');
    RemoveCharacter(&(sourceBuffer), '\t');
    RemoveCharacter(&(sourceBuffer), ' ');

    RemoveCharacter(&(generatedBuffer), '\n');
    RemoveCharacter(&(generatedBuffer), '\r');
    RemoveCharacter(&(generatedBuffer), '\t');
    RemoveCharacter(&(generatedBuffer), ' ');

    if (sourceBuffer != generatedBuffer)
        return false;
    return true;
}

void PDDLCodeGenerator::RemoveCharacter(string* buffer, char character) {
    buffer->erase(remove(buffer->begin(), buffer->end(), character), buffer->end());
}