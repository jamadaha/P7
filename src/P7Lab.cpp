#include <iostream>
#include <memory>

#include "Report.hh"

using namespace std;

int main(int argc, char** argv)
{
	string argString = "python3 runP7.py ";
	for(int i = 1; i < argc; i++)
		argString += string(argv[i]) + " ";
	cout << system(argString.c_str()) << endl;
	return 0;
}
