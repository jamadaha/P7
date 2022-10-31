#include "CompareReport.hh"

using namespace std;

void CompareRunReport::AddReport(RunReport report) {
	runs.push_back(report);
}

void CompareRunReport::Print() {
	cout << "---- Compare Time Taken ----" << endl;
	for (int i = 0; i < runs.size(); i++) {
		for (int j = i + 1; j < runs.size(); j++) {
			
		}
		cout << "Run " + to_string(i) << endl;
	}
}