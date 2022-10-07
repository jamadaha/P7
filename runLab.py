#! /usr/bin/env python

from lab.experiment import ARGPARSER
from downward.experiment import FastDownwardExperiment
from downward.reports.absolute import AbsoluteReport
from lab.environments import LocalEnvironment

#Parse args giving to lab
ARGPARSER.add_argument(
    "--downward",
    required=True,
    help="Path to fastdownward"
    )

ARGPARSER.add_argument(
    "--benchmarks",
    required=True,
    help="Folder where tests are in"
    )

ARGPARSER.add_argument(
    "--problem",
    required=True,
    help="Test only one problem ex. gripper:prob01.pddl. Test a whole domain of problems ex. gripper"
    )

ARGPARSER.add_argument(
    "--report",
    required=True,
    help="Folder to report and eval"
    )

ARGPARSER.add_argument(
    "--algorithm",
    required=False,
    default="astar(ipdb())",
    help="Algorithm fastdownward should use. Ex. astar(ipdb())"
    )

args = ARGPARSER.parse_args()
#--------------------------------------------
evaluationfolder = args.report
algorithm = args.algorithm
downwardfilepath = args.downward
problem = args.problem
benchmarksfolder = args.benchmarks

experiment = FastDownwardExperiment(evaluationfolder)

run = experiment.add_run()
run.add_command("solver", ["mysolver", "runP7.py"])

experiment.add_step("build", experiment.build)
experiment.add_step("start", experiment.start_runs)
experiment.add_fetcher(name="fetch")

#Parsers
experiment.add_parser(experiment.EXITCODE_PARSER)
experiment.add_parser(experiment.TRANSLATOR_PARSER)
experiment.add_parser(experiment.SINGLE_SEARCH_PARSER)
experiment.add_parser(experiment.ANYTIME_SEARCH_PARSER)
experiment.add_parser(experiment.PLANNER_PARSER)
#---

experiment.add_algorithm(
    algorithm,
    downwardfilepath,
    "main",
    ["--search", algorithm]
)
experiment._algorithms[algorithm].driver_options.remove("--validate")

experiment.add_suite(benchmarksfolder, [problem])

#Settings for the report from lab
ATTRIBUTES = [
    "error",
    "run_dir",
    "search_start_time",
    "search_start_memory",
    "total_time",
    "h_values",
    "coverage",
    "expansions",
    "memory",
]
experiment.add_report(AbsoluteReport(attributes=ATTRIBUTES), outfile="report.html")

experiment.run_steps()