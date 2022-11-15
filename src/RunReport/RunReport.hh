#ifndef REPORT_HH
#define REPORT_HH

#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <algorithm>

struct ReportData {
    std::string stringValue;
    std::string intValue;
    std::string boolValue;

    ReportData(std::string stringValue = "None", std::string intValue = "-1", std::string boolValue = "None") : stringValue(stringValue), intValue(intValue), boolValue(boolValue){}
};

struct ReportStep {
    bool isRunning;
    int indent = 0;
    std::string desc;
    ReportData Data;
    // How long the step took in nano seconds
    int64_t time = 0;
    // Initial time
    std::chrono::_V2::steady_clock::time_point iTime;
    // End time
    std::chrono::_V2::steady_clock::time_point eTime;
    bool finished;
    int parent = -1;
    ReportStep(std::string desc) : desc(desc), finished(false) {}
    ReportStep(std::string desc, int parent) : desc(desc), parent(parent), finished(false) {}
    ReportStep(std::string desc, int parent, int indent) : desc(desc), parent(parent), indent(indent), finished(false) {}
};

class RunReport {
public:
    double TotalTime = 0;
    std::string Reformulator;

    RunReport(std::string reformulator) : Reformulator(reformulator){};

    int Setup(std::string desc, int parentID = -1);
    int Begin(std::string desc, int parentID = -1);

    void Pause(int i);
    void Resume(int i);

    // Returns time taken
    // Default is in ms
    int64_t Stop(ReportData data = ReportData());

    // Returns time taken
    // Default is in ms
    int64_t Stop(int i, ReportData data = ReportData());



    void Print();
private:
    int GetParentIndent(int parentID);
    double GetTotalChildrenTime(int parentID);
    std::vector<ReportStep> steps;
};

#endif
