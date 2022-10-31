#include "RunReport.hh"

using namespace std;

int RunReport::Begin(string desc) {
    int parent = -1;
    for (int i = steps.size() - 1; i >= 0; i--)
        if (!steps[i].finished) {
            parent = i; break;
        }
    steps.emplace_back(ReportStep(desc, parent));
    steps[steps.size() - 1].iTime = chrono::steady_clock::now();
    return steps.size() - 1;
}

void RunReport::Pause(int i) {
    steps[i].eTime = chrono::steady_clock::now();
    steps[i].time += chrono::duration_cast<chrono::nanoseconds>(steps[i].eTime - steps[i].iTime).count();
}

void RunReport::Resume(int i) {
    steps[i].iTime = chrono::steady_clock::now();
}

int64_t RunReport::Stop(RunReport::TimeScale ts) {
    return Stop(steps.size() - 1, ts);
}

int64_t RunReport::Stop(int i, RunReport::TimeScale ts) {
    steps[i].eTime = chrono::steady_clock::now();
    if (steps[i].time == 0)
        steps[i].time += chrono::duration_cast<chrono::nanoseconds>(steps[i].eTime - steps[i].iTime).count();
    steps[i].finished = true;

    if (ts == RunReport::TimeScale::ns) {
        TotalTime += steps[i].time;
        return steps[i].time;
    }
    else {
        TotalTime += steps[i].time / 1000000;
        return steps[i].time / 1000000;
    }
}

void RunReport::Print(RunReport::TimeScale ts) {
    int lDesc = 0;
    double totalTime = 0;
    for (auto step : steps) {
        lDesc = max(lDesc, (int)step.desc.size());
        if (step.parent == -1)
            totalTime += step.time;
    }

    printf("---- Time Taken ----\n");
    string tts = (ts == TimeScale::ns) ? "(ns)" : "(ms)";
    string ttl = "Time Taken " + tts;
    printf("%-*s %-*s %s\n", lDesc, "Description", (int)ttl.size(), ttl.c_str(), "Time Taken (%)");
    for (auto step : steps) {
        if (ts == TimeScale::ns)
            printf("%-*s %-*ld %-3.3f\n", lDesc, step.desc.c_str(), (int)ttl.size(), (long)step.time, step.time / totalTime * 100.0);
        else
            printf("%-*s %-*.3f %-3.3f\n", lDesc, step.desc.c_str(), (int)ttl.size(), step.time / 1000000.0, step.time / totalTime * 100.0);
    }
    if (ts == TimeScale::ns)
        printf("%-*s %ld\n", lDesc, "Total Time", (long)totalTime);
    else
        printf("%-*s %.3f\n", lDesc, "Total Time", totalTime / 1000000.0);
}
