from downward.reports.absolute import AbsoluteReport
from downward.reports.taskwise import TaskwiseReport

import os

def add_absolute_report(experiment):
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
                            'unsolvable']

    ATTRIBUTES = ERROR_ATTRIBUTES + PREDEFINED_ATTRIBUTES
    experiment.add_report(AbsoluteReport(attributes=ATTRIBUTES), outfile="report.html")

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

    #reads from the downwardLog file
    experiment.add_parser(P7_LAB_PARSER)
    experiment.add_parser(TRANSLATOR_PARSER)
    experiment.add_parser(ANYTIME_SEARCH_PARSER)
    experiment.add_parser(SINGLE_SEARCH_PARSER)

    #reads from the driver.log file
    experiment.add_parser(EXITCODE_PARSER)
    experiment.add_parser(PLANNER_PARSER)

    
    