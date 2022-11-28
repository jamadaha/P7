#include "JointPath.hh"

using namespace std;
using namespace JointPaths;

size_t JointPath::GetHash() {
    if (Hash != 0)
        return Hash;
    Hash = hash<vector<PDDL::ActionInstance>>{}((*this).Chain);
    return Hash;
}