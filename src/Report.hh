#ifndef REPORT
#define REPORT

#include <string>
#include <vector>
#include <chrono>

struct ReportStep {
    std::string desc;
    // How long the step took in nano seconds
    int64_t time; 
    // Initial time
    std::chrono::_V2::steady_clock::time_point iTime;
    // End time
    std::chrono::_V2::steady_clock::time_point eTime;
    ReportStep(std::string desc) : desc(desc) {}
};

class Report {
public:
    int Begin(std::string desc) {
        steps.emplace_back(ReportStep(desc));
        steps[steps.size() - 1].iTime = std::chrono::steady_clock::now();
        return steps.size() - 1;
    }
    // Returns time taken
    int64_t Stop() {
        return Stop(steps.size() - 1);
    }

    int64_t Stop(int i) {
        steps[i].eTime = std::chrono::steady_clock::now();
        steps[i].time = std::chrono::duration_cast<std::chrono::nanoseconds>(steps[i].eTime - steps[i].iTime).count();
        return steps[i].time / 1000000;
    }
private:
    std::vector<ReportStep> steps;
};

#endif
