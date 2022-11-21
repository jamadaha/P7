from lab.experiment import Experiment
from lab.environments import LocalEnvironment
from downward import suites
import shutil
import subprocess
import os
import datetime
from distutils.dir_util import copy_tree

from os import path
from Lab.Reports import Reports
from Lab.Benchmarks import get_suite
from Lab.ConfigParser import ConfigParser
from Lab.CSVGenerator import CSVGenerator
from Lab.LabAttributes import ATTRIBUTES
from Lab.LabSettingsParser import LabSettingsParser
from Lab.PathHelper import PathHelper
from Lab.SettingsParser import SettingsParser

class LabSuite():
    _pathHelper : PathHelper
    _reportfolder = ""
    _projectfile = ""
    _benchmarksfolder = ""
    _totalRuns = 0
    _currentRuns = 0
    _labSettings : LabSettingsParser

    def __init__(self, dir):
        self._pathHelper = PathHelper(dir)

    def _PreClean(self):
        if path.exists(self._pathHelper.CombinePath("LabReports")):
            shutil.rmtree(self._pathHelper.CombinePath("LabReports"))

    def RunSuite(self):
        self._PreClean()

        self._reportfolder = self._pathHelper.CombinePath('LabReport')
        self._projectfile = self._pathHelper.CombinePath('src/P7')

        self._labSettings = LabSettingsParser()
        self._labSettings.ParseSettingsFile()

        self._benchmarksfolder = self._pathHelper.CombinePath(self._labSettings.BenchmarksFolder)

        experiments = []

        print("Found a total of " + str(len(self._labSettings.SettingsCollection)) + " settings files to run each " + str(self._labSettings.Rounds) + " times.")
        print("Starting on " + str(self._labSettings.Threads) + " threads.")
        print("")

        for settingsFile in self._labSettings.SettingsCollection:
            settingsFileName = settingsFile + ".ini"
            fileContent = ConfigParser.ParseConfig(self._pathHelper.CombinePath("LabSettings/" + settingsFileName))
            for i in range(1,self._labSettings.Rounds + 1):
                settingsFile_override = settingsFile + "-" + str(i);

                experimentSettings = SettingsParser(self._pathHelper)
                experimentSettings.Parse(fileContent)

                experiment = self._SetupExperiment(experimentSettings, self._labSettings.Threads, settingsFile)
                
                self._SetupExperimentCleanupSteps(experiment, settingsFile_override)
                experiment.add_step("build", experiment.build)
                experiment.add_step("addextralogging", self._AddLoggingToBuid)
                experiment.add_step("start", experiment.start_runs)
                experiment.add_fetcher(name="fetch")

                Reports.AddParsers(experiment)
                Reports.AddAbsoluteReport(experiment, ATTRIBUTES)
                #Reports.AddTaskwiseReport(experiment, experimentSettings.Reformulators)

                experiment.add_step("movereport", self._MoveReport, experiment.eval_dir, self._pathHelper.CombinePath("LabReports/" + settingsFile_override))
                               
                experiments.append(experiment)

        for experiment in experiments:
            self._totalRuns += len(experiment.runs)

        for experiment in experiments:
            experiment.run_steps()
            self._currentRuns += len(experiment.runs)

    def _MoveReport(self, fromDir, toDir):
        shutil.move(fromDir, toDir)

    def _AddLoggingToBuid(self):
        fileName = self._reportfolder + "/run"
        lines = []
        with open(fileName, 'r') as file:
            lines = file.readlines()

        taskIDs = ""
        for line in lines:
            if "SHUFFLED_TASK_IDS =" in line:
                taskIDs = line
        
        replacementFileName = self._reportfolder + "/RunReplacement.py"
        replacementLines = []
        with open(replacementFileName, 'r') as file:
            replacementLines = file.readlines()

        newLines = []
        for line in replacementLines:
            if "SHUFFLED_TASK_IDS =" in line:
                newLines.append(taskIDs)
            elif "counterMax = 0" in line:
                newLines.append("counterMax = " + str(self._totalRuns) + "\n");
            elif "counter = 0" in line:
                newLines.append("counter = " + str(self._currentRuns) + "\n");
            else:
                newLines.append(line)

        os.remove(fileName)
        with open(fileName, 'w') as file:   
            file.writelines(newLines)

    def _SetupExperiment(self, experimentSettings, threads, settingsFile):
        experiment = Experiment(self._reportfolder, LocalEnvironment(threads))
        tasks = suites.build_suite(self._benchmarksfolder, get_suite(experimentSettings.Domains, ""))
        for reformulator in experimentSettings.Reformulators:
            for task in tasks:
                self._SetupTasks(experimentSettings.SettingsContent, task, reformulator, experiment, settingsFile)
        return experiment

    def _SetupTasks(self, content, task, reformulator, experiment : Experiment, settingsFile):
        content += "\nPATH:domain=" + task.domain_file + "\n"
        content += "PATH:problem=" + task.problem_file + "\n"

        content += "LIST<STRING>:reformulator=" + reformulator + "\n"
        
        run = experiment.add_run()
        run.add_new_file("config","TempSettings.ini",content)
        run.add_command("planner", [self._projectfile,"{config}"])
        run.set_property("id",[reformulator, task.domain, task.problem])
        run.set_property("domain", task.domain)
        run.set_property("problem", task.problem)
        run.set_property("algorithm", reformulator)
        run.set_property("p7_settings_file", settingsFile)

    def _SetupExperimentCleanupSteps(self, experiment, settingsFile):
        if path.exists(self._reportfolder):
            experiment.add_step("rm-exp-dir", shutil.rmtree, self._reportfolder)
        if path.exists(experiment.eval_dir):
            experiment.add_step("rm-eval-dir", shutil.rmtree, experiment.eval_dir)
        if path.exists(self._pathHelper.CombinePath("LabReports/" + settingsFile)):
            experiment.add_step("rm-report-dir", shutil.rmtree, self._pathHelper.CombinePath("LabReports/" + settingsFile))

    def CombineReports(self):
        CSVGenerator.AddCSVReport(ATTRIBUTES)
   
    def MakeGraphs(self):
        print("Generating graphs with R")
        shutil.copy("graphGeneration.R", "LabReports/graphGeneration.R")
        newPath = self._pathHelper.CombinePath("LabReports")
        subprocess.call(["Rscript", "graphGeneration.R"], cwd=newPath)

    def MoveResults(self):
        print("Moving Data to results folder")
        now = datetime.datetime.now()
        folderName = now.strftime("%x").replace("/","-") + " - " + now.strftime("%X").replace(":","-")
        os.makedirs(path.join(self._labSettings.ResultsFolder, folderName))

        copy_tree("LabReports", path.join(self._labSettings.ResultsFolder, folderName, "LabReports"))
        copy_tree("LabSettings", path.join(self._labSettings.ResultsFolder, folderName, "LabSettings"))
        shutil.copy("settingsLab.ini", path.join(self._labSettings.ResultsFolder, folderName, "settingsLab.ini"))
        shutil.copy("baseSettings.ini", path.join(self._labSettings.ResultsFolder, folderName, "baseSettings.ini"))
