from downward.reports.absolute import AbsoluteReport
from downward.reports.taskwise import TaskwiseReport

import os

class Reports():
    def AddAbsoluteReport(experiment, attr):
        experiment.add_report(AbsoluteReport(attributes=attr), outfile="report.html")

    def AddTaskwiseReport(experiment, reformulators):
        for reformulator in reformulators:
            experiment.add_report(TaskwiseReport(attributes=["*_ms"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_ms.html")
            experiment.add_report(TaskwiseReport(attributes=["*_procent"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_procent.html")

    def AddParsers(experiment):
        EXITCODE_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"ExitcodeParser.py")
        PLANNER_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"PlannerParser.py")

        TRANSLATOR_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"TranslatorParser.py")
        SINGLE_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"SingleSearchParser.py")
        ANYTIME_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"AnytimeSearchParser.py")
        P7_LAB_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"P7LabParser.py")

        experiment.add_parser(os.path.join(os.path.dirname(os.path.abspath(__file__)),"RunReplacement.py"))

        #reads from the driver.log file
        experiment.add_parser(EXITCODE_PARSER)

        #reads from the downwardLog file
        experiment.add_parser(SINGLE_SEARCH_PARSER)
        experiment.add_parser(ANYTIME_SEARCH_PARSER)

        experiment.add_parser(TRANSLATOR_PARSER)
        experiment.add_parser(P7_LAB_PARSER)

        #reads from the driver.log but needs coverage in properties file that AnytimeSearchParser or SingleSearchParser gives
        experiment.add_parser(PLANNER_PARSER)

    
    