from lab.experiment import Experiment
from lab.environments import LocalEnvironment
from downward import suites
import shutil
import os
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

    def __init__(self, dir):
        self._pathHelper = PathHelper(dir)

    def _PreClean(self):
        if path.exists(self._pathHelper.CombinePath("LabReports")):
            shutil.rmtree(self._pathHelper.CombinePath("LabReports"))

    def RunSuite(self):
        self._PreClean()

        self._reportfolder = self._pathHelper.CombinePath('LabReport')
        self._projectfile = self._pathHelper.CombinePath('src/P7')
        self._benchmarksfolder = self._pathHelper.CombinePath("Data/benchmarks/")

        labSettings = LabSettingsParser()
        labSettings.ParseSettingsFile()

        experiments = []

        print("Found a total of " + str(len(labSettings.SettingsCollection)) + " settings files to run")
        print("Starting on " + str(labSettings.Threads) + " threads.")
        print("")

        for settingsFile in labSettings.SettingsCollection:
            settingsFileName = settingsFile 
            if ".ini" not in settingsFileName:
                settingsFileName = settingsFileName + ".ini"

            print("Begining run of settings file " + settingsFileName)
            fileContent = ConfigParser.ParseConfig(self._pathHelper.CombinePath("LabSettings/" + settingsFileName))

            experimentSettings = SettingsParser(self._pathHelper)
            experimentSettings.Parse(fileContent)

            experiment = self._SetupExperiment(experimentSettings, labSettings.Threads, settingsFile)

            experiment.set_property("p7_settings_file", settingsFile);  
            self._SetupExperimentCleanupSteps(experiment, settingsFile)
            experiment.add_step("build", experiment.build)
            experiment.add_step("addextralogging", self.AddLoggingToBuid)
            experiment.add_step("start", experiment.start_runs)
            experiment.add_fetcher(name="fetch")

            Reports.AddParsers(experiment)
            Reports.AddAbsoluteReport(experiment, ATTRIBUTES)
            Reports.AddTaskwiseReport(experiment, experimentSettings.Reformulators)

            experiment.run_steps()

            shutil.move(experiment.eval_dir, self._pathHelper.CombinePath("LabReports/" + settingsFile))

            experiments.append(experiment)

    def AddLoggingToBuid(self):
        fileName = self._reportfolder + "/run"
        lines = []
        with open(fileName, 'r') as file:
            lines = file.readlines()
        
        changedLines = []
        for line in lines:
            if "def process_task(task_id):" in line:
                changedLines.append("def process_task(task_id, counter, counterMax):\n")
            elif "result = pool.map_async(process_task, range(1, num_tasks + 1))" in line:
                changedLines.append("    counters = range(1, num_tasks + 1)\n")
                changedLines.append("    counterMaxs = [num_tasks] * num_tasks\n")
                changedLines.append("    result = pool.starmap_async(process_task, zip(SHUFFLED_TASK_IDS, counters, counterMaxs))\n")
            elif "logging.info(f\"Starting run {run_id} (TASK_ID {task_id}) in {run_dir}\")" in line:
                changedLines.append("            logging.info(\"(\" + str(counter) + \"/\" + str(counterMax) + f\") Starting run {run_id} (TASK_ID {task_id}) in {run_dir}\")\n")
            else:
                changedLines.append(line)
            if "def main():" in line:
                changedLines.append("    counter = 0\n")

        os.remove(fileName)

        with open(fileName, 'w') as file:   
            file.writelines(changedLines)

    def CombineReports(self):
        CSVGenerator.AddCSVReport(ATTRIBUTES)

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