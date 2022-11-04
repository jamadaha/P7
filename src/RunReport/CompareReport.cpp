#include "CompareReport.hh"

using namespace std;

void CompareRunReport::AddReport(RunReport report) {
	runs.push_back(report);
}

void CompareRunReport::Print() {
	printf("\n");
	printf("---- Compare Total Time Taken ----\n");
	int longestReformulator = 7;
	for (int i = 0; i < runs.size(); i++) {
		if (runs.at(i).Reformulator.size() > longestReformulator)
			longestReformulator = runs.at(i).Reformulator.size();
	}
	printf("%*s", longestReformulator + 3, "");
	for (int i = 0; i < runs.size(); i++) {
		printf("%-*s | ", longestReformulator, runs.at(i).Reformulator.c_str());
	}
	printf("\n");
	for (int i = 0; i < runs.size(); i++) {
		printf("%-*s | ", longestReformulator, runs.at(i).Reformulator.c_str());
		for (int j = 0; j < runs.size(); j++) {
			printf("%-*.2f\% | ", longestReformulator - 1, (runs.at(i).TotalTime / runs.at(j).TotalTime) * 100);
		}
		printf("\n");
	}
}