#ifndef BaseWidthFunction_HH
#define BaseWidthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"

class BaseWidthFunction {
public:
    virtual bool Iterate() = 0;
};

#endif