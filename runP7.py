#! /usr/bin/env python

from lab.experiment import Experiment
from downward import suites
import shutil
from os import path
from Lab.ArgumentParser import *
from Lab.Reports import add_reports
from Lab.Benchmarks import get_suite, make_tasks

args = set_arguments()

with open(args.settings, 'r') as file:
    lines = file.readlines()

search = ""
heuristic = ""
domainline = ""
problemline = ""

reportline = ""
projectline = ""
benchmarksline = ""

settingscontent = ""

for line in lines:
    if "downwardsearch" in line:
        search = line.split("=")[1].strip("\n")
        settingscontent += line
    elif "downwardheuristic" in line:
        heuristic = line.split("=")[1].strip("\n")
        settingscontent += line
    elif "domain" in line:
        domainline = line.split("=")[1].strip("\n")
    elif "problem" in line:
        problemline = line.split("=")[1].strip("\n")
    elif "benchmarks" in line:
        benchmarksline = line.split("=")[1].strip("\n")
    elif "project" in line:
        projectline = line.split("=")[1].strip("\n")
    elif "P7" in line:
        project = line.split("=")[1].strip("\n")
    else:
        settingscontent += line

reportfolder = get_from_argument(reportline,__file__, "build/LabReport")
projectfile = get_from_argument(projectline,__file__, "build/src/P7")

#decide if labs method to find domains and problems should be used
#since lab wants the benchmarksfolder to have a specific structure
lab_build_suite = False
defaultfolder = ""
if ".pddl" in domainline:
    defultfolder = "Data/Classical tracks/Gripper/"
else:
    lab_build_suite = True
    defultfolder = "Data/benchmarks/"

benchmarksfolder = get_from_argument(benchmarksline,__file__, defultfolder)

domains = domainline.split(":")
problemsindomains = problemline.split(":")

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
    settingscontent += "\nPATH:domain=" + task.domain_file + "\n"
    settingscontent += "PATH:problem=" + task.problem_file + "\n"

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