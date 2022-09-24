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

    sourceBuffer.erase(remove(sourceBuffer.begin(), sourceBuffer.end(), '\n'), sourceBuffer.end());
    sourceBuffer.erase(remove(sourceBuffer.begin(), sourceBuffer.end(), '\r'), sourceBuffer.end());
    sourceBuffer.erase(remove(sourceBuffer.begin(), sourceBuffer.end(), '\t'), sourceBuffer.end());
    sourceBuffer.erase(remove(sourceBuffer.begin(), sourceBuffer.end(), ' '), sourceBuffer.end());

    generatedBuffer.erase(remove(generatedBuffer.begin(), generatedBuffer.end(), '\n'), generatedBuffer.end());
    generatedBuffer.erase(remove(generatedBuffer.begin(), generatedBuffer.end(), '\r'), generatedBuffer.end());
    generatedBuffer.erase(remove(generatedBuffer.begin(), generatedBuffer.end(), '\t'), generatedBuffer.end());
    generatedBuffer.erase(remove(generatedBuffer.begin(), generatedBuffer.end(), ' '), generatedBuffer.end());

    if (sourceBuffer != generatedBuffer)
        return false;
    return true;
}