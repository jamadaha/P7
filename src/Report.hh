#ifndef REPORT
#define REPORT

#include <string>
#include <vector>
#include <chrono>

enum class TimeScale {
    ms,
    ns
};

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
    // Default is in ms
    int64_t Stop(TimeScale ts = TimeScale::ms) {
        return Stop(steps.size() - 1, ts);
    }

    // Returns time taken
    // Default is in ms
    int64_t Stop(int i, TimeScale ts = TimeScale::ms) {
        steps[i].eTime = std::chrono::steady_clock::now();
        steps[i].time = std::chrono::duration_cast<std::chrono::nanoseconds>(steps[i].eTime - steps[i].iTime).count();

        if (ts == TimeScale::ns)
            return steps[i].time;
        else
            return steps[i].time / 1000000;
    }

    void Print(TimeScale ts = TimeScale::ms) {
        int lDesc = 0;
        double totalTime = 0;
        for (auto step : steps) {
            lDesc = std::max(lDesc, (int) step.desc.size());
            totalTime += step.time;
        }
            
        printf("---- Time Taken ----\n");
        std::string tts = (ts == TimeScale::ns) ? "(ns)" : "(ms)";
        std::string ttl = "Time Taken " + tts;
        printf("%-*s %-*s %s\n", lDesc, "Description", (int) ttl.size(), ttl.c_str(), "Time Taken (%)");
        for (auto step : steps) {
            if (ts == TimeScale::ns)
                printf("%-*s %-*ld %-3.3f\n", lDesc, step.desc.c_str(), (int) ttl.size(), (long) step.time, step.time / totalTime * 100.0);
            else
                printf("%-*s %-*.3f %-3.3f\n", lDesc, step.desc.c_str(), (int) ttl.size(), step.time / 1000000.0, step.time / totalTime * 100.0);
        }
        if (ts == TimeScale::ns)
            printf("%-*s %ld\n", lDesc, "Total Time", (long) totalTime);
        else
            printf("%-*s %.3f\n", lDesc, "Total Time", totalTime / 1000000.0);
        
    }

private:
    std::vector<ReportStep> steps;
};

#endif
