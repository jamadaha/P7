#include "ProgressBarHelper.hh"

using namespace std;

void ProgressBarHelper::Update(int by) {
	if (Value > To)
		return;
	Value += by;
	int newIndex = Value * StepValue;
	for (int i = CurrentDisplayIndex; i < newIndex; i++) {
		cout << "X";
		cout.flush();
		if (Value >= To) {
			cout << endl;
			break;
		}
	}
	CurrentDisplayIndex = newIndex;
}

void ProgressBarHelper::SetTo(int value) {
	if (value > Value)
		Update(value - Value);
}

void ProgressBarHelper::End() {
	Update(To);
}