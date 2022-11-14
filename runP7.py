from Lab.LabSuite import LabSuite
from os import path

newSuite = LabSuite(path.dirname(__file__))

print("Running Lab Suite")
newSuite.RunSuite()
print("Lab Suite run complete!")
