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

int64_t RunReport::Stop(ReportData data) {
    return Stop(steps.size() - 1, data);
}

int64_t RunReport::Stop(int i, ReportData data) {
    if (steps[i].finished)
        return steps[i].time;

    if (steps[i].isRunning) {
        steps[i].eTime = chrono::steady_clock::now();
        steps[i].time += chrono::duration_cast<chrono::milliseconds>(steps[i].eTime - steps[i].iTime).count();
    }
    steps[i].finished = true;
    steps[i].Data = data;

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
    string descriptionLabel = "Description";
    string timeTakenMsLabel = "Time Taken (ms)";
    string timeTakenPercentLabel = "Time Taken (%)";
    string notesLabel = "Notes";
    string intValueLabel = "Int Values";
    string boolValueLabel = "Bool Values";

    int lDesc = descriptionLabel.size();
    int lTimeTakenMs = timeTakenMsLabel.size();
    int lTimeTakenPercent = timeTakenPercentLabel.size();
    int lNotes = notesLabel.size();
    int lintValue = intValueLabel.size();
    int lboolValue = boolValueLabel.size();

    map<int, double> totalTimeMap;
    for (auto step : steps) {
        lDesc = max(lDesc, (int)step.desc.size() + step.indent);
        lNotes = max(lNotes, (int)step.Data.stringValue.size());
        lintValue = max(lintValue, (int)step.Data.intValue.size());
        lboolValue = max(lboolValue, (int)step.Data.boolValue.size());
        lTimeTakenMs = max(lTimeTakenMs, (int)to_string(step.time).size() + step.indent);
        lTimeTakenPercent = max(lTimeTakenPercent, 6 + step.indent);
        if (step.parent != -1 && !totalTimeMap.contains(step.parent)) {
            totalTimeMap.emplace(step.parent, GetTotalChildrenTime(step.parent));
        }
    }

    printf("---- Run Report ----\n");
    printf(
        "%-*s %-*s %-*s %-*s %-*s %-*s\n", 
        lDesc, 
        descriptionLabel.c_str(), 
        lTimeTakenMs, 
        timeTakenMsLabel.c_str(), 
        lTimeTakenPercent, 
        timeTakenPercentLabel.c_str(), 
        lNotes, 
        notesLabel.c_str(),
        lintValue,
        intValueLabel.c_str(),
        lboolValue,
        boolValueLabel.c_str()
    );
    for (auto step : steps) {
        if (step.parent != -1) {
            printf(
                "%-*s%-*s %-*.2f %-*.2f %-*s %-*s %-*s\n", 
                step.indent, 
                "", 
                lDesc, 
                step.desc.c_str(), 
                lTimeTakenMs, 
                (float)step.time, 
                lTimeTakenPercent, 
                (step.time / (float)totalTimeMap.at(step.parent)) * 100.0, 
                lNotes, 
                step.Data.stringValue.c_str(),
                lintValue,
                step.Data.intValue.c_str(),
                lboolValue,
                step.Data.boolValue.c_str()
            );
        }
        else
            printf(
                "%-*s %-*.2f %-*.2f %-*s %-*s %-*s\n", 
                lDesc, 
                step.desc.c_str(),
                lTimeTakenMs, 
                (float)step.time, 
                lTimeTakenPercent, 
                (step.time / (float)TotalTime) * 100.0, 
                lNotes,
                step.Data.stringValue.c_str(),
                lintValue,
                step.Data.intValue.c_str(),
                lboolValue,
                step.Data.boolValue.c_str()
            );
    }
    printf("%-*s %.3f\n", lDesc, "Total Time", (float)TotalTime);
}
