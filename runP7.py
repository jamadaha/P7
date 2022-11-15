from Lab.LabSuite import LabSuite
from os import path

newSuite = LabSuite(path.dirname(__file__))

print("Running Lab Suite")
print("")
newSuite.RunSuite()
print("")
newSuite.CombineReports()
print("")
print("Lab Suite run complete!")
