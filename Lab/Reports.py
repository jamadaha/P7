from downward.reports.absolute import AbsoluteReport
from downward.reports.taskwise import TaskwiseReport

import json
import csv

import os

ERROR_ATTRIBUTES= ['domain', 
                    'problem', 
                    'algorithm', 
                    'unexplained_errors', 
                    'error', 
                    'planner_wall_clock_time', 
                    'raw_memory', 
                    'node']

PREDEFINED_ATTRIBUTES= ['cost', 
                        'coverage', 
                        'dead_ends', 
                        'evaluations', 
                        'expansions', 
                        'generated', 
                        'initial_h_value', 
                        'plan_length', 
                        'planner_time', 
                        'quality', 
                        'score_*', 
                        'search_time', 
                        'total_time', 
                        'unsolvable',
                        'p7_solving_problem_ms',
                        'p7_validating_reformulated_plan',
                        'p7_validating_rebuilded_plan']

ATTRIBUTES = ERROR_ATTRIBUTES + PREDEFINED_ATTRIBUTES

def add_absolute_report(experiment):
    experiment.add_report(AbsoluteReport(attributes=ATTRIBUTES), outfile="report.html")

def add_csv_report(experiment):
    basePath = os.path.dirname(__file__)
    propertiesFileName = os.path.join(basePath, '../LabReport-eval/properties')
    outputCSVFileName = os.path.join(basePath, '../LabReport-eval/report.csv')
    propertiesFile = open(propertiesFileName)
    jsonData = json.load(propertiesFile)

    outputCSVFile = open(outputCSVFileName, 'w')
    outputCSVWriter = csv.writer(outputCSVFile)

    outputCSVWriter.writerow(ATTRIBUTES)

    for key in jsonData:
        row = [" "] * len(ATTRIBUTES)
        for checkKey in jsonData[key]:
            if checkKey in ATTRIBUTES:
                row[ATTRIBUTES.index(checkKey)] = jsonData[key][checkKey]
        outputCSVWriter.writerow(row)

    propertiesFile.close()
    outputCSVFile.close()

def add_taskwise_reports(experiment, reformulators):
    for reformulator in reformulators:
        experiment.add_report(TaskwiseReport(attributes=["*_ms"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_ms.html")
        experiment.add_report(TaskwiseReport(attributes=["*_procent"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_procent.html")

def add_parsers(experiment):
    EXITCODE_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"ExitcodeParser.py")
    PLANNER_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"PlannerParser.py")

    TRANSLATOR_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"TranslatorParser.py")
    SINGLE_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"SingleSearchParser.py")
    ANYTIME_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"AnytimeSearchParser.py")
    P7_LAB_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"P7LabParser.py")

    #reads from the driver.log file
    experiment.add_parser(EXITCODE_PARSER)

    #reads from the downwardLog file
    experiment.add_parser(SINGLE_SEARCH_PARSER)
    experiment.add_parser(ANYTIME_SEARCH_PARSER)

    experiment.add_parser(TRANSLATOR_PARSER)
    experiment.add_parser(P7_LAB_PARSER)

    #reads from the driver.log but needs coverage in properties file that AnytimeSearchParser or SingleSearchParser gives
    experiment.add_parser(PLANNER_PARSER)

    
    