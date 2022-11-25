#include "JointPath.hh"

using namespace std;
using namespace JointPaths;

size_t JointPath::GetHash() {
    if (Hash != 0)
        return Hash;
    Hash = hash<vector<PDDLActionInstance>>{}((*this).Chain);
    return Hash;
}