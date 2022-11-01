#include "RunReport.hh"

using namespace std;

int RunReport::Setup(string desc, int parentID) {
    steps.emplace_back(ReportStep(desc, parentID));
    return steps.size() - 1;
}

int RunReport::Begin(string desc, int parentID) {
    steps.emplace_back(ReportStep(desc, parentID));
    steps[steps.size() - 1].iTime = chrono::steady_clock::now();
    return steps.size() - 1;
}

void RunReport::Pause(int i) {
    steps[i].eTime = chrono::steady_clock::now();
    steps[i].time += chrono::duration_cast<chrono::milliseconds>(steps[i].eTime - steps[i].iTime).count();
}

void RunReport::Resume(int i) {
    steps[i].iTime = chrono::steady_clock::now();
}

int64_t RunReport::Stop() {
    return Stop(steps.size() - 1);
}

int64_t RunReport::Stop(int i) {
    if (steps[i].finished)
        return steps[i].time;

    if (steps[i].time == 0) {
        steps[i].eTime = chrono::steady_clock::now();
        steps[i].time += chrono::duration_cast<chrono::milliseconds>(steps[i].eTime - steps[i].iTime).count();
    }
    steps[i].finished = true;

    if (steps[i].parent == -1)
        TotalTime += steps[i].time;
    return steps[i].time;
}

void RunReport::Print() {
    int lDesc = 0;
    for (auto step : steps) {
        lDesc = max(lDesc, (int)step.desc.size());
    }

    printf("---- Time Taken ----\n");
    string ttl = "Time Taken (ms)";
    printf("%-*s %-*s %s\n", lDesc, "Description", (int)ttl.size(), ttl.c_str(), "Time Taken (%)");
    for (auto step : steps) {
        printf("%-*s %-*.2f %-3.2f\n", lDesc, step.desc.c_str(), (int)ttl.size(), (float)step.time, (step.time / (float)TotalTime) * 100.0);
    }
    printf("%-*s %.3f\n", lDesc, "Total Time", (float)TotalTime);
}
