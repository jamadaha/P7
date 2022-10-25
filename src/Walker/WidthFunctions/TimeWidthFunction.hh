#ifndef TimeWidthFunction_HH
#define TimeWidthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "BaseWidthFunction.hh"
#include <chrono>

class TimeWidthFunction : public BaseWidthFunction {
public:
    TimeWidthFunction(unsigned int timeLimitMs) : limitMs(timeLimitMs) {};
    bool Iterate() override {
        if (!started) {
            started = true;
            startTime = std::chrono::steady_clock::now();
        }

        auto ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
        if (ellapsed >= limitMs)
            return false;
        return true;
    }
private:
    const unsigned int limitMs;
    bool started = false;
    std::chrono::_V2::steady_clock::time_point startTime;
};

#endif
