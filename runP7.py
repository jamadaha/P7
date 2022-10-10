#! /usr/bin/env python

from lab.experiment import Experiment
from lab.experiment import ARGPARSER
from downward.reports.absolute import AbsoluteReport
import shutil
import os
from os import path

ARGPARSER.add_argument(
    "--report",
    required=False,
    help="Foldername for report and eval"
)

ARGPARSER.add_argument(
    "--P7",
    required=False,
    help="Path to project P7 executable"
)

ARGPARSER.add_argument(
    "--downward",
    required=True,
    help="Path to Fast Downward"
)

ARGPARSER.add_argument(
    "--validate",
    required=True,
    help="Path to VAL"
)

ARGPARSER.add_argument(
    "--search",
    required=False,
    default="astar",
    help="Search Fast Downward should use. Ex. astar"
)

ARGPARSER.add_argument(
    "--evaluator",
    required=False,
    default="blind",
    help="Evaluator Fast Downward should use. Ex. blind"
)

ARGPARSER.add_argument(
    "--benchmarks",
    required=False,
    help="Folder where problems are in"
)

ARGPARSER.add_argument(
    "--domain",
    required=False,
    default="gripper_domain.pddl",
    help="Domain pddl file"
)

ARGPARSER.add_argument(
    "--problem",
    required=False,
    default="gripper_problem.pddl",
    help="Problem pddl file"
)

args = ARGPARSER.parse_args()

reportfolder = args.report if args.report else os.path.join(os.path.dirname(os.path.abspath(__file__)),"build/LabReport")

projectfile = args.P7 if args.P7 else os.path.join(os.path.dirname(os.path.abspath(__file__)),"build/P7")
downwardfilepath = args.downward
validatorfilepath = args.validate

search = args.search
evaluator = args.evaluator

benchmarksfolder = args.benchmarks if args.benchmarks else os.path.join(os.path.dirname(os.path.abspath(__file__)),"Data/Classical tracks/Gripper/")
domain = args.domain
problem = args.problem

experiment = Experiment(reportfolder)

arguments = [os.path.join(os.path.dirname(os.path.abspath(__file__)), projectfile)]
arguments += ["-d", benchmarksfolder + domain]
arguments += ["-p", benchmarksfolder + problem]
arguments += ["-f", downwardfilepath]
arguments += ["-v", validatorfilepath]
arguments += ["-s", search]
arguments += ["-e", evaluator]

run = experiment.add_run()
run.add_command("P7", arguments)
run.set_property("id",[search, evaluator, domain, problem])
run.set_property("domain", domain)
run.set_property("problem", problem)
run.set_property("algorithm", search + "(" + evaluator + ")")

if path.exists(reportfolder):
    experiment.add_step("rm-exp-dir", shutil.rmtree, reportfolder)
if path.exists(experiment.eval_dir):
    experiment.add_step("rm-eval-dir", shutil.rmtree, experiment.eval_dir)
experiment.add_step("build", experiment.build)
experiment.add_step("start", experiment.start_runs)
experiment.add_fetcher(name="fetch")

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