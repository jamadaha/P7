import json
import csv

import os
from os import path

class CSVGenerator():
    def AddCSVReport(self, attributes):
        basePath = os.path.dirname(__file__)
        if path.exists(os.path.join(basePath, "../LabReports/")):
            print("Generating csv file")
            outputCSVFileName = os.path.join(basePath, "../LabReports/report.csv")
            outputCSVFile = open(outputCSVFileName, 'w')
            outputCSVWriter = csv.writer(outputCSVFile)

            outputCSVWriter.writerow(attributes)

            reports = os.listdir(os.path.join(basePath, "../LabReports/"))
            count = 0
            for folder in reports:
                propertiesFileName = os.path.join(basePath, "../LabReports/" + folder + "/properties")
                if os.path.isfile(propertiesFileName):
                    propertiesFile = open(propertiesFileName)
                    jsonData = json.load(propertiesFile)

                    for key in jsonData:
                        row = [" "] * len(attributes)
                        for checkKey in jsonData[key]:
                            if checkKey in attributes:
                                row[attributes.index(checkKey)] = jsonData[key][checkKey]
                        outputCSVWriter.writerow(row)

                    propertiesFile.close()
                    count += 1

            print("Combined a total of " + str(count) + " reports.")

            outputCSVFile.close()