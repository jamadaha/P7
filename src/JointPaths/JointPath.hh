#ifndef JOINT_PATH_HH
#define JOINT_PATH_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

namespace JointPaths {
    struct JointPath {
    public:
        size_t GetHash();
        std::vector<PDDLActionInstance> Chain;
        int Occurance;
        double Quality = 1;

        JointPath(std::vector<PDDLActionInstance*> chain, size_t hash) : Occurance(2), Hash(hash) {
            for (auto instance : chain)
                Chain.push_back(*instance);
        };
    private:
        size_t Hash = 0;
    };
}

#endif