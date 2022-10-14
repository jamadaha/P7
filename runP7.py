#! /usr/bin/env python

from lab.experiment import Experiment
from downward import suites
import shutil
from os import path
from Lab.ArgumentParser import *
from Lab.Reports import add_reports
from Lab.Benchmarks import get_suite, make_tasks

args = set_arguments()

reportfolder = get_from_argument(args.report,__file__, "build/LabReport")
projectfile = get_from_argument(args.P7,__file__, "build/P7")

downwardfilepath = args.downward
validatorfilepath = args.validate
search = args.search
evaluator = args.evaluator

lab_build_suite = False
folder = ""
if ".pddl" in args.domain:
    folder = "Data/Classical tracks/Gripper/"
else:
    lab_build_suite = True
    folder = "Data/benchmarks/"
benchmarksfolder = get_from_argument(args.benchmarks,__file__, folder)

domains = args.domain.split(":")
problemsindomains = args.problem.split(":")

experiment = Experiment(reportfolder)

tasks = []
if lab_build_suite:
    tasks = suites.build_suite(benchmarksfolder, get_suite(domains, problemsindomains))
else:
    tasks = make_tasks(benchmarksfolder, domains, problemsindomains)

for task in tasks:
    print(task.domain_file)
    print(task.problem_file)

    arguments = [abs_path(__file__,projectfile)]
    arguments += ["-f", downwardfilepath]
    arguments += ["-v", validatorfilepath]
    arguments += ["-s", search]
    arguments += ["-e", evaluator]

    arguments += ["-d", task.domain_file]
    arguments += ["-p", task.problem_file]

    run = experiment.add_run()
    run.add_command("planner", arguments)
    run.set_property("id",[search, evaluator, task.domain, task.problem])
    run.set_property("domain", task.domain)
    run.set_property("problem", task.problem)
    run.set_property("algorithm", search + "(" + evaluator + ")")
    
if path.exists(reportfolder):
    experiment.add_step("rm-exp-dir", shutil.rmtree, reportfolder)
if path.exists(experiment.eval_dir):
    experiment.add_step("rm-eval-dir", shutil.rmtree, experiment.eval_dir)
experiment.add_step("build", experiment.build)
experiment.add_step("start", experiment.start_runs)
experiment.add_fetcher(name="fetch")

add_reports(experiment)

experiment.run_steps()