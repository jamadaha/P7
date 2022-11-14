from lab.experiment import Experiment
from lab.environments import LocalEnvironment
from downward import suites
import shutil
from os import path
from Lab.Reports import Reports
from Lab.Benchmarks import get_suite
from Lab.ConfigParser import ConfigParser
from Lab.CSVGenerator import CSVGenerator
from Lab.LabAttributes import ATTRIBUTES
from Lab.LabSettingsParser import LabSettingsParser
from Lab.PathHelper import PathHelper
from Lab.SettingsParser import SettingsParser

pathHelper = PathHelper(path.dirname(__file__))

labSettings = LabSettingsParser()
labSettings.ParseSettingsFile()

experiments = []

if path.exists("LabReports/"):
    shutil.rmtree("LabReports/")

print("Found a total of " + str(len(labSettings.SettingsCollection)) + " settings files to run")
print("Starting on " + str(labSettings.Threads) + " threads.")

for settingsFile in labSettings.SettingsCollection:
    print("Begining run of settings file " + settingsFile)

    if ".ini" not in settingsFile:
        settingsFile = settingsFile + ".ini"
    fileContent = ConfigParser.ParseConfig("LabSettings/" + settingsFile)

    experimentSettings = SettingsParser(pathHelper)
    experimentSettings.Parse(fileContent)
    
    #if not found in config file the default values are used
    reportfolder = pathHelper.CombinePath('LabReport')
    projectfile = pathHelper.CombinePath('src/P7')

    #decide if labs method to find domains and problems should be used
    #since lab wants the benchmarksfolder to have a specific structure
    benchmarksfolder = pathHelper.CombinePath("Data/benchmarks/")

    experiment = Experiment(reportfolder, LocalEnvironment(labSettings.Threads))
    
    tasks = suites.build_suite(benchmarksfolder, get_suite(experimentSettings.Domains, ""))

    """
    Each task contains a domain file and problem file
    For each task a settings.ini file is made and P7 is given this file as argument
    """
    for reformulator in experimentSettings.Reformulators:
        for task in tasks:
            content = experimentSettings.SettingsContent
            content += "\nPATH:domain=" + task.domain_file + "\n"
            content += "PATH:problem=" + task.problem_file + "\n"

            content += "LIST<STRING>:reformulator=" + reformulator + "\n"

            run = experiment.add_run()
            run.add_new_file("config","TempSettings.ini",content)
            run.add_command("planner", [projectfile,"{config}"])

            run.set_property("id",[reformulator, task.domain, task.problem])
            run.set_property("domain", task.domain)
            run.set_property("problem", task.problem)
            run.set_property("algorithm", reformulator)
            run.set_property("p7_settings_file", settingsFile.replace(".ini",""))

    experiment.set_property("p7_settings_file", settingsFile.replace(".ini",""));
    if path.exists(reportfolder):
        experiment.add_step("rm-exp-dir", shutil.rmtree, reportfolder)
    if path.exists(experiment.eval_dir):
        experiment.add_step("rm-eval-dir", shutil.rmtree, experiment.eval_dir)
    if path.exists("LabReports/" + settingsFile.replace(".ini","")):
        experiment.add_step("rm-report-dir", shutil.rmtree, "LabReports/" + settingsFile.replace(".ini",""))
    experiment.add_step("build", experiment.build)
    experiment.add_step("start", experiment.start_runs)
    experiment.add_fetcher(name="fetch")

    Reports.AddParsers(experiment)
    Reports.AddAbsoluteReport(experiment, ATTRIBUTES)
    Reports.AddTaskwiseReport(experiment, experimentSettings.Reformulators)

    experiment.run_steps()

    shutil.move(experiment.eval_dir, "LabReports/" + settingsFile.replace(".ini",""))

    experiments.append(experiment)

CSVGenerator.AddCSVReport(ATTRIBUTES)