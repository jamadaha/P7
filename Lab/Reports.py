from downward.reports.absolute import AbsoluteReport
from downward.reports.taskwise import TaskwiseReport
from downward.reports.scatter import ScatterPlotReport
from lab.experiment import Experiment

import os

class Reports():
    def AddAbsoluteReport(experiment : Experiment, attr):
        experiment.add_report(AbsoluteReport(attributes=attr), outfile="report.html")

    def AddTaskwiseReport(experiment : Experiment, reformulators):
        for reformulator in reformulators:
            experiment.add_report(TaskwiseReport(attributes=["*_ms"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_ms.html")
            experiment.add_report(TaskwiseReport(attributes=["*_procent"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_procent.html")

    def AddPlot(experiment : Experiment, attribute):
        matplotlib_options = {
            "font.family": "serif",
            "font.weight": "normal",
            # Used if more specific sizes not set.
            "font.size": 20,
            "axes.labelsize": 20,
            "axes.titlesize": 30,
            "legend.fontsize": 22,
            "xtick.labelsize": 10,
            "ytick.labelsize": 10,
            "lines.markersize": 10,
            "lines.markeredgewidth": 0.25,
            "lines.linewidth": 1,
            # Width and height in inches.
            "figure.figsize": [8, 8],
            "savefig.dpi": 100,
        }
        experiment.add_report(ScatterPlotReport(attributes=[attribute], get_category=Reports._domain_as_category, matplotlib_options=matplotlib_options), name=attribute)

    def AddParsers(experiment : Experiment):
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

    def _domain_as_category(run1, run2):
        # run2['domain'] has the same value, because we always
        # compare two runs of the same problem.
        return run1["domain"]
    
    