from Lab.LabSuite import LabSuite
from os import path

newSuite = LabSuite(path.abspath(path.dirname(__file__)))

print("Running Lab Suite")
print("")
newSuite.RunSuite()
print("")
newSuite.CombineReports()
print("")
newSuite.MakeGraphs()
print("")
newSuite.MoveResults()
print("")
print("Lab Suite run complete!")
