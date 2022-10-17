#ifndef TimeWidthFunction_HH
#define TimeWidthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "BaseWidthFunction.hh"
#include <chrono>

class TimeWidthFunction : public BaseWidthFunction {
public:
    TimeWidthFunction(int limitmSec) : LimitmSec(limitmSec), BaseWidthFunction() {}
    int GetWidth() override;
private:
    int64_t LimitmSec = 0;
    bool IsStarted = false;
    std::chrono::_V2::steady_clock::time_point StartTime;
};

#endif
