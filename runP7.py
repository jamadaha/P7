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
projectfile = get_from_argument(args.P7,__file__, "build/src/P7")

downwardfilepath = args.downward
validatorfilepath = args.validate
search = args.search
heuristic = args.heuristic
reformulator = args.reformulator
reformulatorTime = args.timelimit

#decide if labs method to find domains and problems should be used
#since lab wants the benchmarksfolder to have a specific structure
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

"""
Each task contains a domain file and problem file
For each task a settingsLab.ini file is made and P7 is given this file as argument
"""
for task in tasks:
    settingscontent = "PATH:downwardpath=" + downwardfilepath + "\n"
    settingscontent += "PATH:validatorpath=" + validatorfilepath + "\n"

    settingscontent += "PATH:domain=" + task.domain_file + "\n"
    settingscontent += "PATH:problem=" + task.problem_file + "\n"
    
    settingscontent += "STRING:downwardsearch=" + search + "\n"
    settingscontent += "STRING:downwardheuristic=" + heuristic + "\n"

    settingscontent += "STRING:reformulator=" + reformulator + "\n"
    settingscontent += "INT:timelimit=" + reformulatorTime + "\n"

    settingscontent += "BOOL:printwalkersteps=false\n"
    settingscontent += "BOOL:printentanglersteps=false\n"
    settingscontent += "BOOL:debugmode=false\n"

    run = experiment.add_run()
    run.add_new_file("config","settings.ini",settingscontent)
    run.add_command("planner", [abs_path(__file__,projectfile),"{config}"])

    run.set_property("id",[search, heuristic, task.domain, task.problem])
    run.set_property("domain", task.domain)
    run.set_property("problem", task.problem)
    run.set_property("algorithm", search + "(" + heuristic + ")")
    
if path.exists(reportfolder):
    experiment.add_step("rm-exp-dir", shutil.rmtree, reportfolder)
if path.exists(experiment.eval_dir):
    experiment.add_step("rm-eval-dir", shutil.rmtree, experiment.eval_dir)
experiment.add_step("build", experiment.build)
experiment.add_step("start", experiment.start_runs)
experiment.add_fetcher(name="fetch")

add_reports(experiment)

experiment.run_steps()