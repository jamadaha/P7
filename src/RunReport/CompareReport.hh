#ifndef COMPAREREPORT_HH
#define COMPAREREPORT_HH

#include <string>
#include <vector>
#include <iostream>

#include "RunReport.hh"

class CompareRunReport {
public:
    void AddReport(RunReport report);
    void Print();
private:
    std::vector<RunReport> runs;
};

#endif
