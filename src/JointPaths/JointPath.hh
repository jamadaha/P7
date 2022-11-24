#ifndef JOINT_PATH_HH
#define JOINT_PATH_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

namespace JointPaths {
    struct JointPath {
    public:
        size_t GetHash();
        std::vector<PDDLActionInstance> Chain;
        int ChainSize = 0;
        int Occurance;
        double Quality = 1;

        JointPath(std::vector<PDDLActionInstance*> chain, size_t hash) : Occurance(2), Hash(hash), ChainSize(chain.size()) {
            for (auto instance : chain)
                Chain.push_back(*instance);
        };
        JointPath(std::vector<PDDLActionInstance*> chain, size_t hash, int occurance, int chainSize, double quality) : JointPath(chain, hash) {
            Occurance = occurance;
            Quality = quality;
            ChainSize = chainSize;
        };
    private:
        size_t Hash = 0;
    };
}

#endif