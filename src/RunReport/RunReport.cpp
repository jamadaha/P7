#include "RunReport.hh"

using namespace std;

int RunReport::GetParentIndent(int parentID) {
    int indentCount = 1;
    if (steps[parentID].parent != -1)
        indentCount += GetParentIndent(steps[parentID].parent);
    return indentCount;
}

int RunReport::Setup(string desc, int parentID) {
    int indent = 0;
    if (parentID != -1)
        indent = GetParentIndent(parentID);
    steps.emplace_back(ReportStep(desc, parentID, indent));
    return steps.size() - 1;
}

int RunReport::Begin(string desc, int parentID) {
    int indent = 0;
    if (parentID != -1)
        indent = GetParentIndent(parentID);
    steps.emplace_back(ReportStep(desc, parentID, indent));
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

double RunReport::GetTotalChildrenTime(int parentID) {
    double totalTime = 0;
    for (auto step : steps) {
        if (step.parent == parentID)
            totalTime += step.time;
    }
    return totalTime;
}

void RunReport::Print() {
    int lDesc = 0;
    map<int, double> totalTimeMap;
    for (auto step : steps) {
        lDesc = max(lDesc, (int)step.desc.size() + step.indent);
        if (step.parent != -1 && !totalTimeMap.contains(step.parent)) {
            totalTimeMap.emplace(step.parent, GetTotalChildrenTime(step.parent));
        }
    }

    printf("---- Time Taken ----\n");
    string ttl = "Time Taken (ms)";
    printf("%-*s %-*s %s\n", lDesc, "Description", (int)ttl.size(), ttl.c_str(), "Time Taken (%)");
    for (auto step : steps) {
        if (step.parent != -1) {
            printf("%-*s%-*s %-*.2f %-3.2f\n", step.indent, "", lDesc, step.desc.c_str(), (int)ttl.size() + step.indent, (float)step.time, (step.time / (float)totalTimeMap.at(step.parent)) * 100.0);
        }
        else
            printf("%-*s %-*.2f %-3.2f\n", lDesc, step.desc.c_str(), (int)ttl.size(), (float)step.time, (step.time / (float)TotalTime) * 100.0);
    }
    printf("%-*s %.3f\n", lDesc, "Total Time", (float)TotalTime);
}
