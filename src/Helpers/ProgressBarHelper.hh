#ifndef ProgressBarHelper_HH
#define ProgressBarHelper_HH

#include <iostream>
#include <string>

class ProgressBarHelper {
public:
	int DisplayWidth = 50;

	ProgressBarHelper(int to, std::string desc) : To(to) {
		StepValue = ((double)DisplayWidth / ((double)To - 1));
		std::cout << desc << std::endl;
		std::cout << "|";
		for (int i = 0; i < DisplayWidth; i++)
			std::cout << " ";
		std::cout << "|" << std::endl;
		std::cout << " ";
	};

	void SetTo(int value);
	void Update(int by = 1);
	void End();

private:
	int Value = 0;

	double StepValue = 0;
	int CurrentDisplayIndex = 0;
	int To = 1;
};

#endif