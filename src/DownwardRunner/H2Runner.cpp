#include "H2Runner.hh"

using namespace std;

PDDLMutex H2Runner::RunH2(Config config) {
    const string h2Path = config.GetItem<filesystem::path>("h2path").c_str();
	string command = h2Path + " --no_bw_h2 < output.sas" + " > nul";
	system(command.c_str());
    return ParseOutput();
}

PDDLMutex H2Runner::ParseOutput() {
    ifstream stream("output.sas");
    string content( (istreambuf_iterator<char>(stream) ),
                       (istreambuf_iterator<char>()    ) );
    stream.close();

    std::vector<PDDLMutexVariable> variables = ParseVariables(content);
    return PDDLMutex(variables);
}

std::vector<PDDLMutexVariable> H2Runner::ParseVariables(std::string h2Output) {
    std::vector<PDDLMutexVariable> variables;
    stringstream ss(h2Output);
    std::vector<std::string> variableInfo;
    string line;
    while (getline(ss, line)) {
        line = StringHelper::Trim(line);
        if (variableInfo.size() == 0 && line != "begin_variable")
            continue;
        if (line == "end_variable") {
            variableInfo.push_back(line);
            variables.push_back(ParseVariable(variableInfo));
            variableInfo.clear();
        } else
            variableInfo.push_back(line);
    }
    return variables;
}

PDDLMutexVariable H2Runner::ParseVariable(std::vector<std::string> variableInfo) {
    std::string variableName = variableInfo.at(1);
    int numOfAtoms = std::atoi(variableInfo.at(3).c_str());
    // Vector of predicate + object
    std::vector<PDDLMutexVariable::Atom> atoms;
    // 4 is the first atom
    for (int i = 4; i < variableInfo.size() - 1; i++) {
        auto atom = variableInfo.at(i);
        atom = atom.substr(5);
        std::string predicate = "";
        // Get predicate, and remove from atom
        // at-robby(rooma) => predicate = at-robby & atom = rooma)
        for (int i = 0; i < atom.size(); i++)
            if (atom.at(i) != '(')
                predicate += atom.at(i);
            else {
                atom = atom.substr(i + 1);
                unsigned int predicateIndex = instance->domain->predicateMap.at(StringHelper::ToUpper(predicate));
                std::vector<unsigned int> objects;
                std::vector<std::string> objectsS;
                std::string workingObject = "";
                for (int i = 0; i < atom.size(); i++) {
                    if (atom.at(i) == ' ')
                        continue;
                    if (atom.at(i) == ',' || atom.at(i) == ')') {
                        objects.push_back(instance->problem->objectMap.at(workingObject));
                        objectsS.push_back(workingObject);
                        workingObject.clear();
                    } else
                        workingObject += atom.at(i);
                }
                atoms.push_back(PDDLMutexVariable::Atom(predicateIndex, predicate, objects, objectsS));
                break;
            }
    }
    return PDDLMutexVariable(atoms);
}
