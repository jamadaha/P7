#include "RunReport.hh"

using namespace std;

string RunReport::GetParentIndent(int parentID) {
    string retStr = "  ";
    if (steps[parentID].parent != -1)
        retStr += GetParentIndent(steps[parentID].parent);
    return retStr;
}

int RunReport::Setup(string desc, int parentID) {
    if (parentID != -1)
        desc = GetParentIndent(parentID) + desc;
    steps.emplace_back(ReportStep(desc, parentID));
    return steps.size() - 1;
}

int RunReport::Begin(string desc, int parentID) {
    if (parentID != -1)
        desc = GetParentIndent(parentID) + desc;
    steps.emplace_back(ReportStep(desc, parentID));
    steps[steps.size() - 1].iTime = chrono::steady_clock::now();
    steps[steps.size() - 1].isRunning = true;
    return steps.size() - 1;
}

void RunReport::Pause(int i) {
    if (steps[i].isRunning) {
        steps[i].isRunning = false;
        steps[i].eTime = chrono::steady_clock::now();
        steps[i].time += chrono::duration_cast<chrono::milliseconds>(steps[i].eTime - steps[i].iTime).count();
    }
}

void RunReport::Resume(int i) {
    if (!steps[i].isRunning) {
        steps[i].isRunning = true;
        steps[i].iTime = chrono::steady_clock::now();
    }
}

int64_t RunReport::Stop() {
    return Stop(steps.size() - 1);
}

int64_t RunReport::Stop(int i) {
    if (steps[i].finished)
        return steps[i].time;

    if (steps[i].isRunning) {
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
